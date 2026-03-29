<template>
	<div class="class-summary-container">
		<div class="class-summary-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学员姓名:</label>
						<el-input v-model="filters.name" placeholder="请输入学员姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">课程名称:</label>
						<el-input v-model="filters.courseName" placeholder="请输入课程名称" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">电话:</label>
						<el-input v-model="filters.phone" placeholder="请输入电话" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">状态:</label>
						<el-select v-model="filters.status" placeholder="请选择状态" clearable class="filter-input">
							<el-option label="有效" value="有效" />
							<el-option label="无效" value="无效" />
							<el-option label="过期" value="过期" />
						</el-select>
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
								<el-checkbox v-model="columnDraft.courseName">课程名称</el-checkbox>
								<el-checkbox v-model="columnDraft.subjectName">科目名称</el-checkbox>
								<el-checkbox v-model="columnDraft.totalCount">总数量</el-checkbox>
								<el-checkbox v-model="columnDraft.completeCount">已完成数量</el-checkbox>
								<el-checkbox v-model="columnDraft.remainingCount">剩余数量</el-checkbox>
								<el-checkbox v-model="columnDraft.remainingAmount">剩余金额</el-checkbox>
								<el-checkbox v-model="columnDraft.unitPrice">单价</el-checkbox>
								<el-checkbox v-model="columnDraft.expireDate">过期日期</el-checkbox>
							</div>
							<div class="column-actions">
								<el-button link @click="restoreColumns">恢复</el-button>
								<el-button link type="primary" @click="confirmColumns">确认</el-button>
							</div>
						</div>
					</el-popover>
				</div>
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
					<template v-if="prop === 'studentName'">
						<el-button link type="primary" @click="openStudentDetail(row)">{{ row.studentName || "-" }}</el-button>
					</template>
					<template v-else-if="['totalHours', 'completedHours', 'sickLeave', 'personalLeave'].includes(prop)">
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
import { ElMessage } from "element-plus";
import { IconifyIconOffline } from "@/components/ReIcon";
import { useRouter } from "vue-router";
import MyTable from "@/components/mytable/MyTable.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import { getClassSummaryPage } from "@/apis/student";
import type { ClassSummaryItemDTO } from "@/apis/student/type";

const filters = reactive({
	advisorId: "",
	name: "",
	courseName: "",
	phone: "",
	status: "",
	studentId: "",
});

const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};

const baseTableColumns: MyTableColumn[] = [
	{ prop: "studentName", label: "学员姓名", "min-width": 120 },
	{ prop: "courseName", label: "课程名称", "min-width": 150 },
	{ prop: "subjectName", label: "科目名称", "min-width": 120 },
	{ prop: "totalCount", label: "总数量", width: "100px", align: "center" },
	{ prop: "completeCount", label: "已完成数量", width: "120px", align: "center" },
	{ prop: "remainingCount", label: "剩余数量", width: "100px", align: "center" },
	{ prop: "remainingAmount", label: "剩余金额", width: "120px", align: "center" },
	{ prop: "unitPrice", label: "单价", width: "100px", align: "center" },
	{ prop: "expireDate", label: "过期日期", width: "150px", align: "center" },
];

const tableColumns = computed(() => {
	return baseTableColumns.filter((col) => visibleColumns[col.prop as keyof typeof visibleColumns] !== false);
});

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<ClassSummaryItemDTO>());
const selectedRows = ref<ClassSummaryItemDTO[]>([]);

// 自定义列状态管理
const columnPopoverVisible = ref(false);
const defaultColumns = {
	studentName: true,
	courseName: true,
	subjectName: true,
	totalCount: true,
	completeCount: true,
	remainingCount: true,
	remainingAmount: true,
	unitPrice: true,
	expireDate: true,
};
const visibleColumns = reactive({ ...defaultColumns });
const columnDraft = reactive({ ...defaultColumns });

const displayPageData = computed(() => {
	return pageData.value;
});

const router = useRouter();

function openStudentDetail(row: ClassSummaryItemDTO) {
	if (row?.studentId == null) {
		ElMessage.warning("缺少学员编号");
		return;
	}
	router.push({
		path: "/student/detail",
		query: {
			id: String(row.studentId),
			name: row.studentName || "",
			phone: row.studentPhone || "",
		},
	});
}

function getCellClass(prop: string, _row: ClassSummaryItemDTO) {
	if (prop === "totalCount") return "cell-total";
	if (prop === "completeCount") return "cell-completed";
	if (prop === "remainingCount") return "cell-remaining";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		advisorId: "",
		name: "",
		courseName: "",
		phone: "",
		status: "",
		studentId: "",
	});
	pageIndex.value = 1;
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
		<title>课时汇总列表</title>
		<style>
			body { font-family: Arial, "Microsoft YaHei", sans-serif; padding: 20px; }
			h2 { margin: 0 0 12px; color: #303133; }
			table { border-collapse: collapse; width: 100%; }
			th, td { border: 1px solid #dcdfe6; padding: 8px; text-align: left; font-size: 12px; }
			th { background: #f5f7fa; color: #606266; font-weight: 600; }
			tr:nth-child(even) { background: #fafafa; }
			.cell-total { color: #409eff; font-weight: bold; }
			.cell-completed { color: #67c23a; font-weight: bold; }
			.cell-remaining { color: #f56c6c; font-weight: bold; }
			@media print {
				body { padding: 0; }
				h2 { font-size: 16px; }
				table { font-size: 10px; }
				th, td { padding: 4px; }
			}
		</style>
	</head>
	<body>
		<h2>课时汇总列表</h2>
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

function handlePageChange(data: PageDTO<ClassSummaryItemDTO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: ClassSummaryItemDTO[]) {
	selectedRows.value = rows;
}

// 加载数据
async function loadData() {
	try {
		const res = await getClassSummaryPage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			advisorId: filters.advisorId,
			name: filters.name,
			courseName: filters.courseName,
			phone: filters.phone,
			status: filters.status,
			studentId: filters.studentId,
		});
		console.log("API 返回数据:", res);
		if (res.data) {
			console.log("res.data:", res.data);
			console.log("res.data.rows:", res.data.rows);
			pageData.value = res.data;
		}
	} catch (error) {
		console.error("加载数据失败:", error);
		ElMessage.error("加载数据失败");
	}
}

onMounted(() => {
	loadData();
});
</script>

<style scoped>
.class-summary-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.class-summary-content {
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

:deep(.cell-total) {
	color: #409eff;
	font-weight: bold;
}

:deep(.cell-completed) {
	color: #67c23a;
	font-weight: bold;
}

:deep(.cell-remaining) {
	color: #f56c6c;
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
