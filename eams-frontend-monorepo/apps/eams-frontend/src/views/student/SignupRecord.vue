<template>
	<div class="signup-record-container">
		<div class="signup-record-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学员姓名:</label>
						<el-input v-model="filters.studentName" placeholder="请输入学员姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">课程名称:</label>
						<el-input v-model="filters.courseName" placeholder="请输入课程名称" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">开始日期:</label>
						<el-date-picker
							v-model="filters.startTime"
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
							v-model="filters.endTime"
							type="date"
							placeholder="请选择结束日期"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
						/>
					</div>
					<div class="filter-item">
						<label class="filter-label">经办人:</label>
						<el-input v-model="filters.operatorName" placeholder="请输入经办人" clearable class="filter-input" />
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
								<el-checkbox v-model="columnDraft.addTime">报名时间</el-checkbox>
								<el-checkbox v-model="columnDraft.studentName">学员</el-checkbox>
								<el-checkbox v-model="columnDraft.courseName">课程</el-checkbox>
								<el-checkbox v-model="columnDraft.subjectName">科目</el-checkbox>
								<el-checkbox v-model="columnDraft.operatorName">经办人</el-checkbox>
								<el-checkbox v-model="columnDraft.amount">金额</el-checkbox>
								<el-checkbox v-model="columnDraft.countLessonComplete">已完成课时</el-checkbox>
								<el-checkbox v-model="columnDraft.countLessonTotal">总课时</el-checkbox>
								<el-checkbox v-model="columnDraft.remainingLessons">剩余课次</el-checkbox>
								<el-checkbox v-model="columnDraft.verifyState">审核状态</el-checkbox>
							</div>
							<div class="column-actions">
								<el-button link @click="restoreColumns">恢复</el-button>
								<el-button link type="primary" @click="confirmColumns">确认</el-button>
							</div>
						</div>
					</el-popover>
					<el-button circle @click="handleExport" :loading="exporting">
						<IconifyIconOffline icon="ep/download" width="16" height="16" />
					</el-button>
				</div>
			</div>
			<!-- 批量操作栏 -->
			<div class="batch-actions">
				<!-- <el-button @click="handleBatchDelete">
					<template #icon>
						<IconifyIconOffline icon="ep/delete" width="14" height="14" />
					</template>
					删除
				</el-button> -->
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
					<template v-else-if="['amount', 'remainingLessons', 'verifyState'].includes(prop)">
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
import { useRouter } from "vue-router";
import * as XLSX from "xlsx";
import MyTable from "@/components/mytable/MyTable.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import { getSignupRecordPage, batchDelete } from "@/apis/student";
import type { SignupRecordItemDTO } from "@/apis/student/type";
import {
	buildSignupRecordExportFilename,
	buildSignupRecordExportRows,
	getSignupRecordExportColumns,
} from "./signup-record-export";

const filters = reactive({
	callBackId: undefined,
	changeType: undefined,
	courseName: "",
	endTime: "",
	startTime: "",
	studentName: "",
	operatorName: "",
});

// 报名记录表格属性
const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};
// 报名记录表格列
const baseTableColumns: MyTableColumn[] = [
	{ prop: "addTime", label: "报名时间", width: "160px", align: "center" },
	{ prop: "studentName", label: "学员", "min-width": 120 },
	{ prop: "courseName", label: "课程", "min-width": 120 },
	{ prop: "subjectName", label: "科目", "min-width": 100 },
	{ prop: "operatorName", label: "经办人", "min-width": 100 },
	{ prop: "amount", label: "金额", width: "100px", align: "center" },
	{ prop: "countLessonComplete", label: "已完成课时", width: "100px", align: "center" },
	{ prop: "countLessonTotal", label: "总课时", width: "100px", align: "center" },
	{ prop: "remainingLessons", label: "剩余课次", width: "100px", align: "center" },
	{ prop: "verifyState", label: "审核状态", width: "100px", align: "center" },
];

const tableColumns = computed(() => {
	return baseTableColumns.filter((col) => visibleColumns[col.prop as keyof typeof visibleColumns] !== false);
});

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<SignupRecordItemDTO>());
const selectedRows = ref<SignupRecordItemDTO[]>([]);
const exporting = ref(false);
const columnPopoverVisible = ref(false);
const defaultColumns = {
	addTime: true,
	studentName: true,
	courseName: true,
	subjectName: true,
	operatorName: true,
	amount: true,
	countLessonComplete: true,
	countLessonTotal: true,
	remainingLessons: true,
	verifyState: true,
};
const visibleColumns = reactive({ ...defaultColumns });
const columnDraft = reactive({ ...defaultColumns });

const displayPageData = computed(() => {
	return pageData.value;
});

const router = useRouter();

function openStudentDetail(row: SignupRecordItemDTO) {
	if (row?.studentId == null) {
		ElMessage.warning("缺少学员编号");
		return;
	}
	router.push({
		path: "/student/detail",
		query: {
			id: String(row.studentId),
			name: row.studentName || "",
			phone: "",
		},
	});
}

// 获取表格单元格类名
function getCellClass(prop: string, _row: SignupRecordItemDTO) {
	if (prop === "amount") return "cell-amount";
	if (prop === "remainingLessons") return "cell-remaining";
	if (prop === "verifyState") return "cell-verify-state";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		callBackId: undefined,
		changeType: undefined,
		courseName: "",
		endTime: "",
		startTime: "",
		studentName: "",
		operatorName: "",
	});
	pageIndex.value = 1;
	loadData();
}
// 刷新数据
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

// 打印
function handlePrint() {
	// 生成表头
	const tableHeader = tableColumns.value.map((col) => `<th>${col.label}</th>`).join("");

	// 生成表格数据行
	const rowsHtml = (pageData.value.rows || [])
		.map((row) => {
			const tds = tableColumns.value
				.map((col) => {
					let value = (row as any)[col.prop];
					// 特殊处理审核状态字段
					if (col.prop === "verifyState") {
						const stateMap: Record<number, string> = {
							0: "待审核",
							1: "已通过",
							2: "已拒绝",
						};
						value = stateMap[value] || "未知";
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
		<title>报名记录列表</title>
		<style>
			body { font-family: Arial, "Microsoft YaHei", sans-serif; padding: 20px; }
			h2 { margin: 0 0 12px; color: #303133; }
			table { border-collapse: collapse; width: 100%; }
			th, td { border: 1px solid #dcdfe6; padding: 8px; text-align: left; font-size: 12px; }
			th { background: #f5f7fa; color: #606266; font-weight: 600; }
			tr:nth-child(even) { background: #fafafa; }
			.cell-amount { color: #409eff; font-weight: bold; }
			.cell-remaining { color: #67c23a; font-weight: bold; }
			.cell-verify-state { color: #e6a23c; font-weight: bold; }
			@media print {
				body { padding: 0; }
				h2 { font-size: 16px; }
				table { font-size: 10px; }
				th, td { padding: 4px; }
			}
		</style>
	</head>
	<body>
		<h2>报名记录列表</h2>
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

function handleExport() {
	const visibleCols = getSignupRecordExportColumns(baseTableColumns, visibleColumns);
	if (!visibleCols.length) {
		ElMessage.warning("没有可导出的列");
		return;
	}

	const rowsToExport = selectedRows.value.length ? selectedRows.value : pageData.value.rows || [];
	if (!rowsToExport.length) {
		ElMessage.warning("没有可导出的数据");
		return;
	}

	exporting.value = true;
	try {
		const exportRows = buildSignupRecordExportRows(rowsToExport, visibleCols);
		const worksheet = XLSX.utils.json_to_sheet(exportRows);
		const workbook = XLSX.utils.book_new();

		// 计算列宽
		const columnWidths = visibleCols.map((column) => {
			const headerText = String(column.label || column.prop || "");
			const maxContentLength = exportRows.reduce((max, row) => {
				const cellText = row[headerText] || "";
				return Math.max(max, cellText.length);
			}, headerText.length);
			return { wch: Math.min(Math.max(maxContentLength + 2, 10), 40) };
		});

		worksheet["!cols"] = columnWidths;
		XLSX.utils.book_append_sheet(workbook, worksheet, "报名记录");
		XLSX.writeFile(workbook, buildSignupRecordExportFilename());
		ElMessage.success("导出成功");
	} catch (error) {
		console.error("导出失败:", error);
		ElMessage.error("导出失败");
	} finally {
		exporting.value = false;
	}
}

function handlePageChange(data: PageDTO<SignupRecordItemDTO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: SignupRecordItemDTO[]) {
	selectedRows.value = rows;
}

async function handleBatchDelete() {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请先选择要删除的记录");
		return;
	}
	try {
		await ElMessageBox.confirm(
			`确认删除选中的 ${selectedRows.value.length} 条记录吗？此操作不可恢复！`,
			"批量删除确认",
			{
				confirmButtonText: "确定",
				cancelButtonText: "取消",
				type: "warning",
			},
		);
		const ids = selectedRows.value.map((row) => row.id).filter((id): id is number => id !== undefined);
		await batchDelete({ ids });
		ElMessage.success("批量删除成功");
		loadData();
	} catch (error) {
		if (error === "cancel") {
			return;
		}
		console.error("批量删除失败:", error);
		ElMessage.error("批量删除失败");
	}
}

// 加载数据
async function loadData() {
	try {
		const res = await getSignupRecordPage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			callBackId: filters.callBackId,
			changeType: filters.changeType,
			courseName: filters.courseName,
			endTime: filters.endTime,
			startTime: filters.startTime,
			studentName: filters.studentName,
			operatorName: filters.operatorName,
		});
		if (res.data) {
			pageData.value = res.data;
		}
	} catch (error) {
		console.error("加载数据失败:", error);
		ElMessage.error("加载数据失败");
	}
}

// 初始化加载数据
onMounted(() => {
	loadData();
});
</script>

<style scoped>
.signup-record-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.signup-record-content {
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

/* 图标容器使用 flex 布局，确保 SVG 居中，并添加右边距 */
.batch-actions .el-button .el-icon {
	display: inline-flex;
	align-items: center;
	justify-content: center;
	margin-right: 6px;
}

/* 强制设置 SVG 图标尺寸，并使用 vertical-align 实现垂直居中 */
.batch-actions .el-button .el-icon svg {
	width: 14px !important;
	height: 11px !important;
	vertical-align: middle;
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

:deep(.cell-amount) {
	color: #409eff;
	font-weight: bold;
}

:deep(.cell-remaining) {
	color: #67c23a;
	font-weight: bold;
}

:deep(.cell-verify-state) {
	color: #e6a23c;
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
