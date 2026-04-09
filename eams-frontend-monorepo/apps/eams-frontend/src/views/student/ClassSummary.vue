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
						<label class="filter-label">手机号:</label>
						<el-input v-model="filters.mobile" placeholder="请输入手机号" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">阶段:</label>
						<el-input v-model="filters.stage" placeholder="请输入阶段" clearable class="filter-input" />
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
								<el-checkbox v-model="columnDraft.name">学员姓名</el-checkbox>
								<el-checkbox v-model="columnDraft.mobile">手机号</el-checkbox>
								<el-checkbox v-model="columnDraft.studentId">学员 ID</el-checkbox>
								<el-checkbox v-model="columnDraft.classId">班级 ID</el-checkbox>
								<el-checkbox v-model="columnDraft.lessonId">课时 ID</el-checkbox>
								<el-checkbox v-model="columnDraft.lessonCount">课时数</el-checkbox>
								<el-checkbox v-model="columnDraft.decLessonCount">递减课时数</el-checkbox>
								<el-checkbox v-model="columnDraft.teacherId">教师 ID</el-checkbox>
								<el-checkbox v-model="columnDraft.signState">签到状态</el-checkbox>
								<el-checkbox v-model="columnDraft.signTime">签到时间</el-checkbox>
								<el-checkbox v-model="columnDraft.signType">签到类型</el-checkbox>
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
					<template v-if="prop === 'name'">
						<el-button link type="primary" @click="openStudentDetail(row)">{{ row.name || "-" }}</el-button>
					</template>
					<template v-else-if="prop === 'signState'">
						<el-tag :type="getSignStateType(row.signState)">{{ getSignLabel(row.signState) }}</el-tag>
					</template>
					<template v-else-if="prop === 'signType'">
						<el-tag type="info" size="small">{{ getSignTypeLabel(row.signType) }}</el-tag>
					</template>
					<template v-else-if="prop === 'signTime'">
						<span>{{ formatSignTime(row.signTime) }}</span>
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
	gradeId: undefined as number | undefined,
	name: "",
	mobile: "",
	stage: "",
	status: "",
	courseId: undefined as number | undefined,
});

const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};

const baseTableColumns: MyTableColumn[] = [
	{ prop: "name", label: "学员姓名", "min-width": 120 },
	{ prop: "mobile", label: "手机号", width: "130px", align: "center" },
	{ prop: "studentId", label: "学员 ID", width: "100px", align: "center" },
	{ prop: "classId", label: "班级 ID", width: "100px", align: "center" },
	{ prop: "lessonId", label: "课时 ID", width: "100px", align: "center" },
	{ prop: "lessonCount", label: "课时数", width: "100px", align: "center" },
	{ prop: "decLessonCount", label: "递减课时数", width: "120px", align: "center" },
	{ prop: "teacherId", label: "教师 ID", width: "100px", align: "center" },
	{ prop: "signState", label: "签到状态", width: "100px", align: "center" },
	{ prop: "signTime", label: "签到时间", width: "160px", align: "center" },
	{ prop: "signType", label: "签到类型", width: "100px", align: "center" },
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
	name: true,
	mobile: true,
	studentId: true,
	classId: true,
	lessonId: true,
	lessonCount: true,
	decLessonCount: true,
	teacherId: true,
	signState: true,
	signTime: true,
	signType: true,
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
			name: row.name || "",
			mobile: row.mobile || "",
		},
	});
}

function getSignLabel(signState: number | undefined): string {
	if (signState === undefined || signState === null) return "-";
	const signStateMap: Record<number, string> = {
		0: "未签到",
		1: "已签到",
		2: "迟到",
		3: "早退",
		4: "缺勤",
	};
	return signStateMap[signState] || "-";
}

function getSignStateType(signState: number | undefined): "info" | "success" | "warning" | "danger" {
	if (signState === undefined || signState === null) return "info";
	const typeMap: Record<number, "info" | "success" | "warning" | "danger"> = {
		0: "info",
		1: "success",
		2: "warning",
		3: "warning",
		4: "danger",
	};
	return typeMap[signState] || "info";
}

function getSignTypeLabel(signType: number | undefined): string {
	if (signType === undefined || signType === null) return "-";
	const signTypeMap: Record<number, string> = {
		0: "正常签到",
		1: "补签到",
		2: "签到异常",
	};
	return signTypeMap[signType] || "-";
}

function formatSignTime(signTime: string | undefined): string {
	if (!signTime) return "-";
	const date = new Date(signTime);
	if (isNaN(date.getTime())) return signTime;
	const year = date.getFullYear();
	const month = String(date.getMonth() + 1).padStart(2, "0");
	const day = String(date.getDate()).padStart(2, "0");
	const hours = String(date.getHours()).padStart(2, "0");
	const minutes = String(date.getMinutes()).padStart(2, "0");
	return `${year}-${month}-${day} ${hours}:${minutes}`;
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		gradeId: undefined,
		name: "",
		mobile: "",
		stage: "",
		status: "",
		courseId: undefined,
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
					let value = (row as any)[col.prop];
					// 特殊字段格式化
					if (col.prop === "signState") {
						value = getSignLabel(value);
					} else if (col.prop === "signType") {
						value = getSignTypeLabel(value);
					} else if (col.prop === "signTime") {
						value = formatSignTime(value);
					}
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
			gradeId: filters.gradeId,
			name: filters.name,
			mobile: filters.mobile,
			stage: filters.stage,
			status: filters.status,
			courseId: filters.courseId,
		});
		if (res.data) {
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
