<template>
	<div class="student-leave-container">
		<div class="student-leave-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学生姓名/电话:</label>
						<el-input v-model="filters.nameOrPhone" placeholder="请输入学生姓名或电话" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">开始日期:</label>
						<el-date-picker
							v-model="filters.startDate"
							type="date"
							placeholder="请选择开始日期"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
						/>
					</div>
					<div class="filter-item">
						<label class="filter-label">结束日期:</label>
						<el-date-picker
							v-model="filters.endDate"
							type="date"
							placeholder="请选择结束日期"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
						/>
					</div>
					<div class="filter-buttons">
						<el-button circle @click="handleSearch">
							<IconifyIconOffline icon="ep/search" width="16" height="16" />
						</el-button>
						<el-button circle @click="handleReset">
							<IconifyIconOffline icon="ep/close" width="16" height="16" />
						</el-button>
					</div>
				</div>
				<div class="action-buttons">
					<el-button circle @click="handleRefresh">
						<IconifyIconOffline icon="ep/refresh" width="16" height="16" />
					</el-button>
					<el-button circle @click="handlePrint">
						<IconifyIconOffline icon="ep/printer" width="16" height="16" />
					</el-button>
					<el-popover v-model:visible="columnPopoverVisible" placement="bottom-end" :width="640">
						<template #reference>
							<span class="column-trigger-wrap">
								<el-button circle @click="openColumnPopover">
									<IconifyIconOffline icon="ep/menu" width="16" height="16" />
								</el-button>
							</span>
						</template>
						<div class="column-popover">
							<div class="column-title">自定义显示列：</div>
							<div class="column-options">
								<el-checkbox v-model="columnDraft.studentName">学员姓名</el-checkbox>
								<el-checkbox v-model="columnDraft.mobile">电话</el-checkbox>
								<el-checkbox v-model="columnDraft.courseInfo">请假课次</el-checkbox>
								<el-checkbox v-model="columnDraft.teacherNames">任课老师</el-checkbox>
								<el-checkbox v-model="columnDraft.reason">请假原因</el-checkbox>
								<el-checkbox v-model="columnDraft.addTime">请假时间</el-checkbox>
								<el-checkbox v-model="columnDraft.state">请假状态</el-checkbox>
							</div>
							<div class="column-actions">
								<el-button link @click="restoreColumns">恢复</el-button>
								<el-button link type="primary" @click="confirmColumns">确认</el-button>
							</div>
						</div>
					</el-popover>
				</div>
			</div>
			<!-- 批量操作栏：使用 icon 插槽实现图标与文字对齐 -->
			<div class="batch-actions">
				<el-button @click="handleRevoke">
					<!-- 使用 #icon 插槽包裹图标，Element Plus 会自动处理图标与文本的间距和对齐 -->
					<template #icon>
						<IconifyIconOffline icon="ep/refresh-right" width="14" height="14" />
					</template>
					请假撤销
				</el-button>
			</div>
			<my-table
				:istabmultiple="true"
				:tabattr="tableAttr"
				:tabdatacolumns="tableColumns"
				:tabdata="displayPageData"
				@page-change="handlePageChange"
				@selection-change="handleSelectionChange"
			>
				<template #customercell="{ prop, row }">
					<template v-if="['addTime', 'state'].includes(prop)">
						<span :class="getCellClass(prop, row)">{{ row[prop] }}</span>
					</template>
					<template v-else>
						{{ row[prop] }}
					</template>
				</template>
			</my-table>
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { IconifyIconOffline } from "@/components/ReIcon";
import MyTable from "@/components/mytable/MyTable.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import { getStudentLeavePage, cancelStudentLeave } from "@/apis/academic";
import type { StudentLeaveItemDTO } from "@/apis/academic/type";

const filters = reactive({
	pageIndex: 1,
	pageSize: 20,
	nameOrPhone: "",
	teacherId: undefined as number | undefined,
	startDate: "",
	endDate: "",
});

const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};

const baseTableColumns: MyTableColumn[] = [
	{ prop: "studentName", label: "学员姓名", "min-width": 120 },
	{ prop: "mobile", label: "电话", width: "130px", align: "center" },
	{ prop: "courseInfo", label: "请假课次", "min-width": 200, "show-overflow-tooltip": true },
	{ prop: "teacherNames", label: "任课老师", "min-width": 150, "show-overflow-tooltip": true },
	{ prop: "reason", label: "请假原因", "min-width": 150, "show-overflow-tooltip": true },
	{ prop: "addTime", label: "请假时间", width: "160px", align: "center" },
	{ prop: "state", label: "请假状态", width: "100px", align: "center" },
];

const tableColumns = computed(() => {
	return baseTableColumns.filter((col) => visibleColumns[col.prop as keyof typeof visibleColumns] !== false);
});

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<StudentLeaveItemDTO>());
const selectedRows = ref<StudentLeaveItemDTO[]>([]);

// 自定义列状态管理
const columnPopoverVisible = ref(false);
const defaultColumns = {
	studentName: true,
	mobile: true,
	courseInfo: true,
	teacherNames: true,
	reason: true,
	addTime: true,
	state: true,
};
const visibleColumns = reactive({ ...defaultColumns });
const columnDraft = reactive({ ...defaultColumns });

const displayPageData = computed(() => {
	return pageData.value;
});

function getCellClass(prop: string, _row: StudentLeaveItemDTO) {
	if (prop === "addTime") return "cell-add-time";
	if (prop === "state") return "cell-state";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		pageIndex: 1,
		pageSize: 20,
		nameOrPhone: "",
		teacherId: undefined,
		startDate: "",
		endDate: "",
	});
	loadData();
}

function handleRefresh() {
	loadData();
}

function openColumnPopover() {
	Object.assign(columnDraft, visibleColumns);
	columnPopoverVisible.value = true;
}

function restoreColumns() {
	Object.assign(columnDraft, defaultColumns);
	Object.assign(visibleColumns, defaultColumns);
	columnPopoverVisible.value = false;
}

function confirmColumns() {
	const picked = Object.values(columnDraft).some(Boolean);
	if (!picked) {
		ElMessage.warning("至少保留一列");
		return;
	}
	Object.assign(visibleColumns, columnDraft);
	columnPopoverVisible.value = false;
}

function handlePrint() {
	// 生成表头
	const tableHeader = tableColumns.value.map((col) => `<th>${col.label}</th>`).join("");

	// 生成表格数据行
	const rowsHtml = (pageData.value.rows || [])
		.map((row) => {
			const tds = tableColumns.value
				.map((col) => {
					const value = (row as any)[col.prop];
					return `<td>${String(value ?? "-")}</td>`;
				})
				.join("");
			return `<tr>${tds}</tr>`;
		})
		.join("");

	// 生成完整的 HTML 文档
	const html = `
	<!doctype html>
	<html>
	<head>
		<meta charset="utf-8" />
		<title>学生请假列表</title>
		<style>
			body { font-family: Arial, "Microsoft YaHei", sans-serif; padding: 20px; }
			h2 { margin: 0 0 12px; color: #303133; }
			table { border-collapse: collapse; width: 100%; }
			th, td { border: 1px solid #dcdfe6; padding: 8px; text-align: left; font-size: 12px; }
			th { background: #f5f7fa; color: #606266; font-weight: 600; }
			tr:nth-child(even) { background: #fafafa; }
			.cell-add-time { color: #e6a23c; font-weight: bold; }
			.cell-state { color: #67c23a; font-weight: bold; }
			@media print {
				body { padding: 0; }
				h2 { font-size: 16px; }
				table { font-size: 10px; }
				th, td { padding: 4px; }
			}
		</style>
	</head>
	<body>
		<h2>学生请假列表</h2>
		<table>
			<thead><tr>${tableHeader}</tr></thead>
			<tbody>${rowsHtml || `<tr><td colspan="${tableColumns.value.length}">暂无数据</td></tr>`}</tbody>
		</table>
	</body>
	</html>
	`;

	const win = window.open("", "_blank");
	if (!win) {
		ElMessage.warning("浏览器阻止了打印窗口，请允许弹窗后重试");
		return;
	}
	win.document.open();
	win.document.write(html);
	win.document.close();
	win.focus();
	win.print();
}

function handlePageChange(data: PageDTO<StudentLeaveItemDTO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: StudentLeaveItemDTO[]) {
	selectedRows.value = rows;
}

async function handleRevoke() {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请先选择要撤销的请假记录");
		return;
	}
	try {
		await ElMessageBox.confirm(`确认撤销选中的 ${selectedRows.value.length} 条请假记录吗？`, "请假撤销确认", {
			confirmButtonText: "确定",
			cancelButtonText: "取消",
			type: "warning",
		});
		const ids = selectedRows.value.map((row) => row.id).filter((id): id is number => id !== undefined);
		await cancelStudentLeave(ids);
		ElMessage.success("请假撤销成功");
		loadData();
	} catch (error) {
		if (error === "cancel") {
			return;
		}
		console.error("请假撤销失败:", error);
		ElMessage.error("请假撤销失败");
	}
}

async function loadData() {
	try {
		const res = await getStudentLeavePage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			nameOrPhone: filters.nameOrPhone,
			teacherId: filters.teacherId,
			startDate: filters.startDate,
			endDate: filters.endDate,
		});

		// 检查响应码是否为成功
		if (res.code === 10000 || res.code === 0) {
			pageData.value = res.data || createPageDTO();
		} else {
			console.error("加载请假列表失败:", res.message);
			ElMessage.error(res.message || "加载数据失败");
			pageData.value = createPageDTO();
		}
	} catch (error) {
		console.error("加载数据失败:", error);
		ElMessage.error("加载数据失败");
		pageData.value = createPageDTO();
	}
}

onMounted(() => {
	loadData();
});
</script>

<style scoped>
.student-leave-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.student-leave-content {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
	display: flex;
	flex-direction: column;
	gap: 16px;
	min-height: 0;
}

.top-bar {
	display: flex;
	justify-content: space-between;
	align-items: center;
	gap: 16px;
}

.filter-area {
	display: flex;
	align-items: center;
	gap: 16px;
	flex-wrap: wrap;
}

.filter-item {
	display: flex;
	align-items: center;
	gap: 10px;
}

.filter-label {
	min-width: 72px;
	color: #303133;
	text-align: right;
}

.filter-input {
	width: 200px;
}

.filter-buttons {
	display: flex;
	align-items: center;
	gap: 10px;
}

.action-buttons {
	display: flex;
	align-items: center;
	gap: 10px;
}

/* 批量操作栏样式 */
.batch-actions {
	display: flex;
	gap: 12px;
	margin-top: 12px;
}

/* 按钮使用 inline-flex 布局，确保图标与文本对齐 */
.batch-actions .el-button {
	display: inline-flex;
	align-items: center;
	justify-content: center;
}

/* 图标容器使用 flex 布局，确保 SVG 居中 */
.batch-actions .el-button .el-icon {
	display: inline-flex;
	align-items: center;
	justify-content: center;
}

/* 强制设置 SVG 图标尺寸，并使用 vertical-align 实现垂直居中 */
.batch-actions .el-button .el-icon svg {
	width: 14px !important;
	height: 13px !important;
	vertical-align: middle;
}

:deep(.cell-add-time) {
	color: #e6a23c;
	font-weight: bold;
}

:deep(.cell-state) {
	color: #67c23a;
	font-weight: bold;
}

.column-trigger-wrap {
	display: inline-block;
}

.column-popover {
	.column-title {
		font-size: 14px;
		font-weight: 500;
		color: #303133;
		margin-bottom: 12px;
	}

	.column-options {
		display: grid;
		grid-template-columns: repeat(3, 1fr);
		gap: 12px;
		margin-bottom: 16px;

		.el-checkbox {
			margin-right: 0;
		}
	}

	.column-actions {
		display: flex;
		justify-content: flex-end;
		gap: 12px;
	}
}

@media (max-width: 1200px) {
	.top-bar {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-area {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-item {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-label {
		min-width: auto;
		text-align: left;
	}

	.filter-input {
		width: 100%;
	}

	.filter-buttons,
	.action-buttons {
		flex-wrap: wrap;
		justify-content: flex-start;
	}
}
</style>
