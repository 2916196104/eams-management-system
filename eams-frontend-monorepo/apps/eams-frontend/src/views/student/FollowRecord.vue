<template>
	<div class="follow-record-container">
		<div class="follow-record-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学员姓名或电话:</label>
						<el-input v-model="filters.keyword" placeholder="请输入学员姓名或电话" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">跟进人:</label>
						<el-input v-model="filters.creator" placeholder="请输入跟进人 ID/姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">跟进状态:</label>
						<el-select v-model="filters.stage" placeholder="请选择跟进状态" clearable class="filter-input">
							<el-option label="潜在客户" :value="1" />
							<el-option label="意向客户" :value="2" />
							<el-option label="成交客户" :value="3" />
						</el-select>
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
								<el-checkbox v-model="columnDraft.contactTime">联系时间</el-checkbox>
								<el-checkbox v-model="columnDraft.creatorName">跟进人</el-checkbox>
								<el-checkbox v-model="columnDraft.studentName">学员</el-checkbox>
								<el-checkbox v-model="columnDraft.contactPhone">联系电话</el-checkbox>
								<el-checkbox v-model="columnDraft.stage">阶段</el-checkbox>
								<el-checkbox v-model="columnDraft.contactType">联系方式</el-checkbox>
								<el-checkbox v-model="columnDraft.contactNextTime">下次联系</el-checkbox>
								<el-checkbox v-model="columnDraft.addTime">创建时间</el-checkbox>
								<el-checkbox v-model="columnDraft.info">跟进记录</el-checkbox>
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
						<el-button link type="primary" @click="openDetailDialog(row)">{{ row.studentName || "-" }}</el-button>
					</template>
					<template v-else-if="['contactTime', 'contactNextTime', 'addTime'].includes(prop)">
						<span :class="getCellClass(prop, row)">{{ row[prop] }}</span>
					</template>
					<template v-else-if="prop === 'contactType'">
						{{ getContactTypeLabel(row[prop]) }}
					</template>
					<template v-else-if="prop === 'stage'">
						<el-tag :type="getStageTagType(row[prop])">{{ getStageLabel(row[prop]) }}</el-tag>
					</template>
					<template v-else>
						{{ row[prop] }}
					</template>
				</template>
			</my-table>
		</div>
	</div>
	<!-- 跟进记录详情弹窗 -->
	<el-dialog v-model="detailDialogVisible" title="跟进记录详情" width="600px">
		<el-descriptions :column="1" border>
			<el-descriptions-item label="学员">{{ currentRecord.studentName || "-" }}</el-descriptions-item>
			<el-descriptions-item label="联系电话">{{ currentRecord.contactPhone || "-" }}</el-descriptions-item>
			<el-descriptions-item label="跟进人">{{ currentRecord.creatorName || "-" }}</el-descriptions-item>
			<el-descriptions-item label="跟进状态">
				<el-tag :type="getStageTagType(currentRecord.stage)">{{ getStageLabel(currentRecord.stage) }}</el-tag>
			</el-descriptions-item>
			<el-descriptions-item label="联系方式">{{ getContactTypeLabel(currentRecord.contactType) }}</el-descriptions-item>
			<el-descriptions-item label="跟进时间">{{ currentRecord.contactTime || "-" }}</el-descriptions-item>
			<el-descriptions-item label="下次联系时间">{{ currentRecord.contactNextTime || "-" }}</el-descriptions-item>
			<el-descriptions-item label="创建时间">{{ currentRecord.addTime || "-" }}</el-descriptions-item>
			<el-descriptions-item label="跟进内容" :span="1">
				<div class="detail-info">{{ currentRecord.info || "暂无跟进内容" }}</div>
			</el-descriptions-item>
		</el-descriptions>
		<template #footer>
			<el-button @click="detailDialogVisible = false">关闭</el-button>
			<el-button type="danger" @click="handleDelete(currentRecord.id)">删除</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { IconifyIconOffline } from "@/components/ReIcon";
import MyTable from "@/components/mytable/MyTable.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import { getFollowRecordPage, deleteFollowUp } from "@/apis/student";
import type { FollowRecordItemDTO } from "@/apis/student/type";

const filters = reactive({
	keyword: "",
	creator: "",
	stage: undefined as number | undefined,
	startTime: "",
	endTime: "",
});

// 详情弹窗状态
const detailDialogVisible = ref(false);
const currentRecord = ref<FollowRecordItemDTO>({});

const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};

const baseTableColumns: MyTableColumn[] = [
	{ prop: "contactTime", label: "联系时间", width: "160px", align: "center" },
	{ prop: "creatorName", label: "跟进人", "min-width": 100 },
	{ prop: "studentName", label: "学员", "min-width": 120 },
	{ prop: "contactPhone", label: "联系电话", width: "130px", align: "center" },
	{ prop: "stage", label: "跟进状态", "min-width": 100, align: "center" },
	{ prop: "contactType", label: "联系方式", "min-width": 100 },
	{ prop: "contactNextTime", label: "下次联系", width: "160px", align: "center" },
	{ prop: "addTime", label: "创建时间", width: "160px", align: "center" },
	{ prop: "info", label: "跟进记录", "min-width": 200, "show-overflow-tooltip": true },
];

const tableColumns = computed(() => {
	return baseTableColumns.filter((col) => visibleColumns[col.prop as keyof typeof visibleColumns] !== false);
});

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<FollowRecordItemDTO>());
const selectedRows = ref<FollowRecordItemDTO[]>([]);

// 自定义列状态管理
const columnPopoverVisible = ref(false);
const defaultColumns = {
	contactTime: true,
	creatorName: true,
	studentName: true,
	contactPhone: true,
	stage: true,
	contactType: true,
	contactNextTime: true,
	addTime: true,
	info: true,
};
const visibleColumns = reactive({ ...defaultColumns });
const columnDraft = reactive({ ...defaultColumns });

const displayPageData = computed(() => {
	return pageData.value;
});

function getCellClass(prop: string, _row: FollowRecordItemDTO) {
	if (prop === "contactTime") return "cell-contact-time";
	if (prop === "contactNextTime") return "cell-contact-next-time";
	if (prop === "addTime") return "cell-add-time";
	return "";
}

// 获取联系方式标签
function getContactTypeLabel(type?: number) {
	if (!type) return "";
	const typeMap: Record<number, string> = {
		1: "电话",
		2: "微信",
		3: "面谈",
		4: "其他",
	};
	return typeMap[type] || "未知";
}

// 获取跟进状态标签
function getStageLabel(stage?: number) {
	if (!stage) return "";
	const stageMap: Record<number, string> = {
		1: "潜在客户",
		2: "意向客户",
		3: "成交客户",
	};
	return stageMap[stage] || "未知";
}

// 获取跟进状态标签类型
function getStageTagType(stage?: number): "primary" | "success" | "warning" | "danger" | "info" {
	if (!stage) return "info";
	const typeMap: Record<number, "primary" | "success" | "warning" | "danger" | "info"> = {
		1: "info",
		2: "warning",
		3: "success",
	};
	return typeMap[stage] || "info";
}

// 打开详情弹窗
function openDetailDialog(row: FollowRecordItemDTO) {
	currentRecord.value = { ...row };
	detailDialogVisible.value = true;
}

// 删除跟进记录
async function handleDelete(id?: number) {
	if (!id) {
		ElMessage.warning("缺少记录ID");
		return;
	}
	try {
		await ElMessageBox.confirm("确定要删除这条跟进记录吗？", "提示", {
			confirmButtonText: "确定",
			cancelButtonText: "取消",
			type: "warning",
		});
		const res = await deleteFollowUp(id);
		if (res.code === 200 || res.code === 0) {
			ElMessage.success("删除成功");
			detailDialogVisible.value = false;
			loadData();
		} else {
			ElMessage.error(res.message || "删除失败");
		}
	} catch {
		// 用户取消删除
	}
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		keyword: "",
		creator: "",
		stage: undefined,
		startTime: "",
		endTime: "",
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
					// 特殊处理联系方式和阶段字段
					if (col.prop === "contactType") {
						const typeMap: Record<number, string> = { 1: "电话", 2: "微信", 3: "面谈", 4: "其他" };
						value = typeMap[value] || "未知";
					} else if (col.prop === "stage") {
						const stageMap: Record<number, string> = { 1: "潜在客户", 2: "意向客户", 3: "成交客户" };
						value = stageMap[value] || "未知";
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
		<title>跟进记录列表</title>
		<style>
			body { font-family: Arial, "Microsoft YaHei", sans-serif; padding: 20px; }
			h2 { margin: 0 0 12px; color: #303133; }
			table { border-collapse: collapse; width: 100%; }
			th, td { border: 1px solid #dcdfe6; padding: 8px; text-align: left; font-size: 12px; }
			th { background: #f5f7fa; color: #606266; font-weight: 600; }
			tr:nth-child(even) { background: #fafafa; }
			.cell-contact-time { color: #409eff; font-weight: bold; }
			.cell-contact-next-time { color: #e6a23c; font-weight: bold; }
			.cell-add-time { color: #909399; }
			@media print {
				body { padding: 0; }
				h2 { font-size: 16px; }
				table { font-size: 10px; }
				th, td { padding: 4px; }
			}
		</style>
	</head>
	<body>
		<h2>跟进记录列表</h2>
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

function handlePageChange(data: PageDTO<FollowRecordItemDTO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: FollowRecordItemDTO[]) {
	selectedRows.value = rows;
}

async function loadData() {
	try {
		const res = await getFollowRecordPage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			keyword: filters.keyword,
			creator: filters.creator,
			stage: filters.stage,
			startTime: filters.startTime,
			endTime: filters.endTime,
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
.follow-record-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.follow-record-content {
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

:deep(.cell-contact-time) {
	color: #409eff;
	font-weight: bold;
}

:deep(.cell-contact-next-time) {
	color: #e6a23c;
	font-weight: bold;
}

:deep(.cell-add-time) {
	color: #909399;
}

/* 详情弹窗样式 */
.detail-info {
	white-space: pre-wrap;
	word-break: break-all;
	line-height: 1.6;
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
