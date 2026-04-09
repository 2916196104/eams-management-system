<template>
	<section class="finance-page">
		<section class="filter-panel">
			<div class="filter-grid">
				<div v-for="field in visibleFields" :key="field.prop" class="filter-item">
					<label class="filter-label">{{ field.label }}:</label>
					<el-input
						v-if="field.type === 'input'"
						v-model="filters[field.prop]"
						:placeholder="field.placeholder"
						clearable
					/>
					<el-select
						v-else-if="field.type === 'select'"
						v-model="filters[field.prop]"
						:placeholder="field.placeholder"
						clearable
					>
						<el-option
							v-for="option in field.options || []"
							:key="option.value"
							:label="option.label"
							:value="option.value"
						/>
					</el-select>
					<el-date-picker
						v-else
						v-model="filters[field.prop]"
						type="date"
						value-format="YYYY-MM-DD"
						:placeholder="field.placeholder"
					/>
				</div>
			</div>
			<div class="filter-actions">
				<el-button text type="primary" @click="isExpanded = !isExpanded">
					{{ isExpanded ? "收起" : "展开" }}
				</el-button>
				<el-button :icon="Search" circle @click="handleSearch" />
				<el-button :icon="CircleClose" circle @click="handleReset" />
				<el-button :icon="Download" @click="handleExport">导出</el-button>
			</div>
		</section>

		<p v-if="config.description" class="panel-description">{{ config.description }}</p>

		<section class="table-tools">
			<div class="batch-actions">
				<el-button
					v-for="action in config.batchActions || []"
					:key="action.key"
					:type="action.type || 'primary'"
					@click="handleBatchAction(action.key, action.label)"
				>
					{{ action.label }}
				</el-button>
			</div>
			<div class="icon-actions">
				<el-button :icon="RefreshRight" circle @click="handleRefresh" />
				<el-button :icon="Printer" circle @click="handlePrint" />
				<el-button :icon="Grid" circle @click="handleLayout" />
			</div>
		</section>

		<my-table
			:istabmultiple="true"
			:tabattr="tableAttr"
			:tabdatacolumns="config.columns"
			:tabdata="displayPageData"
			:taboperbtns="config.operationButtons || []"
			@page-change="handlePageChange"
			@selection-change="handleSelectionChange"
			@taboper-click="handleOperation"
		>
			<template #customercell="{ prop, row }">
				<template v-if="currencyProps.has(prop)">
					{{ formatCurrency(row[prop]) }}
				</template>
				<template v-else-if="statusProps.has(prop)">
					<el-tag :type="getStatusType(row[prop])" effect="light">{{ row[prop] }}</el-tag>
				</template>
				<template v-else>
					{{ row[prop] }}
				</template>
			</template>
		</my-table>
	</section>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { CircleClose, Download, Grid, Printer, RefreshRight, Search } from "@element-plus/icons-vue";
import MyTable from "@/components/mytable/MyTable.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import type { FinanceListConfig } from "../shared";

const props = defineProps<{
	config: FinanceListConfig<Record<string, any>>;
}>();

const currencyProps = new Set([
	"amount",
	"singleClassFee",
	"classFeeSubtotal",
	"singleAssistantFee",
	"assistantFeeSubtotal",
	"feePerClass",
	"feeSubtotal",
]);
const statusProps = new Set(["verifyStateName", "status", "auditStatus"]);
const filters = reactive<Record<string, any>>({ ...props.config.initialFilters });
const isExpanded = ref(false);
const pageIndex = ref(1);
const pageSize = ref(3);
const selectedRows = ref<Record<string, any>[]>([]);
const pageData = ref(createPageDTO<Record<string, any>>());

const tableAttr: MyTableAttr = {
	"row-key": "id",
	"max-height": 520,
};

const visibleFields = computed(() => (isExpanded.value ? props.config.filters : props.config.filters.slice(0, 4)));

const filteredRows = computed(() => {
	if (props.config.loadPage) return pageData.value.rows || [];
	return (props.config.rows || []).filter((row) =>
		props.config.filters.every((field) => {
			const keyword = String(filters[field.prop] || "").trim();
			if (!keyword) return true;
			const rawValue = row[field.prop];
			return String(rawValue ?? "").includes(keyword);
		}),
	);
});

const displayPageData = computed(() => {
	if (props.config.loadPage) return pageData.value;
	return createPageDTO({
		pageIndex: pageIndex.value,
		pageSize: pageSize.value,
		total: filteredRows.value.length,
		rows: filteredRows.value.slice((pageIndex.value - 1) * pageSize.value, pageIndex.value * pageSize.value),
	});
});

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, props.config.initialFilters);
	pageIndex.value = 1;
	loadData();
}

async function handleExport() {
	if (props.config.exportHandler) {
		const message = await props.config.exportHandler(filters);
		ElMessage.success(message);
		return;
	}
	ElMessage.success(`已准备导出 ${props.config.title} 数据`);
}

function handleRefresh() {
	loadData();
}

function handlePrint() {
	const printableColumns = props.config.columns.filter((column) => column.prop !== "operate" && column.visible !== false);

	if (!printableColumns.length) {
		ElMessage.warning("当前没有可打印的列");
		return;
	}

	const tableHeader = printableColumns.map((column) => `<th>${escapeHtml(column.label)}</th>`).join("");
	const rowsHtml = (displayPageData.value.rows || [])
		.map((row) => {
			const cells = printableColumns.map((column) => `<td>${formatPrintCell(row, column)}</td>`).join("");
			return `<tr>${cells}</tr>`;
		})
		.join("");
	const html = `
	<!doctype html>
	<html>
	<head>
		<meta charset="utf-8" />
		<title>${escapeHtml(props.config.title)}列表</title>
		<style>
			body { font-family: Arial, "Microsoft YaHei", sans-serif; padding: 20px; color: #303133; }
			h2 { margin: 0 0 12px; color: #303133; }
			p { margin: 0 0 16px; color: #606266; font-size: 12px; }
			table { border-collapse: collapse; width: 100%; }
			th, td { border: 1px solid #dcdfe6; padding: 8px; text-align: left; font-size: 12px; vertical-align: top; }
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
		<h2>${escapeHtml(props.config.title)}列表</h2>
		<p>打印时间：${escapeHtml(new Date().toLocaleString("zh-CN"))}</p>
		<table>
			<thead><tr>${tableHeader}</tr></thead>
			<tbody>${rowsHtml || `<tr><td colspan="${printableColumns.length}">暂无数据</td></tr>`}</tbody>
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

function handleLayout() {
	ElMessage.info("布局切换已预留，可继续扩展为卡片视图");
}

function handleSelectionChange(rows: Record<string, any>[]) {
	selectedRows.value = rows;
}

async function handleBatchAction(key: string, label: string) {
	if (!selectedRows.value.length) {
		ElMessage.warning(`请先勾选需要${label}的记录`);
		return;
	}
	if (props.config.batchActionHandler) {
		const message = await props.config.batchActionHandler(key, selectedRows.value);
		ElMessage.success(message);
		loadData();
		return;
	}
	ElMessage.success(`已对 ${selectedRows.value.length} 条记录执行${label}`);
}

function handlePageChange(data: PageDTO<Record<string, any>>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

async function handleOperation(_: number, row: Record<string, any>, evtname: string) {
	if (props.config.operationHandler) {
		const message = await props.config.operationHandler(evtname, row);
		if (evtname === "detail") {
			ElMessageBox.alert(message, `${props.config.title}详情`, {
				confirmButtonText: "关闭",
			});
		} else {
			ElMessage.success(message);
			loadData();
		}
		return;
	}

	const actionMap: Record<string, string> = {
		detail: "查看详情",
		approve: "通过",
		reject: "驳回",
	};
	ElMessage.success(`${actionMap[evtname] || "处理"}：${row.project || row.title}`);
}

function formatCurrency(value: number | string) {
	const amount = Number(value || 0);
	return `￥${amount.toLocaleString("zh-CN")}`;
}

function formatPrintCell(row: Record<string, any>, column: MyTableColumn) {
	const value = row[column.prop];
	if (currencyProps.has(column.prop)) {
		return escapeHtml(formatCurrency(value));
	}
	if (statusProps.has(column.prop)) {
		return escapeHtml(String(value || "-"));
	}
	return escapeHtml(formatPrintValue(value));
}

function formatPrintValue(value: unknown) {
	if (value == null || value === "") return "-";
	if (Array.isArray(value)) return value.length ? value.map((item) => String(item)).join("、") : "-";
	return String(value);
}

function escapeHtml(value: string) {
	return value
		.replaceAll("&", "&amp;")
		.replaceAll("<", "&lt;")
		.replaceAll(">", "&gt;")
		.replaceAll("\"", "&quot;")
		.replaceAll("'", "&#39;");
}

function getStatusType(status: string) {
	if (!status) return "info";
	if (status.includes("通过") || status.includes("认款") || status.includes("已审核")) return "success";
	if (status.includes("驳回") || status.includes("拒绝") || status.includes("作废")) return "danger";
	return "warning";
}

async function loadData() {
	if (!props.config.loadPage) return;
	try {
		const data = await props.config.loadPage({
			...filters,
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
		});
		pageData.value = createPageDTO(data);
	} catch (error: any) {
		ElMessage.error(error?.message || `${props.config.title}加载失败`);
	}
}

onMounted(() => {
	loadData();
});
</script>

<style scoped>
.finance-page {
	padding: 16px;
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.filter-panel,
.table-tools {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
}

.filter-panel {
	display: flex;
	justify-content: space-between;
	align-items: flex-start;
	gap: 16px;
}

.filter-grid {
	flex: 1;
	display: grid;
	grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
	gap: 14px 20px;
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

.filter-actions,
.icon-actions,
.table-tools,
.batch-actions {
	display: flex;
	align-items: center;
	gap: 10px;
}

.table-tools {
	justify-content: space-between;
}

.panel-description {
	margin: -4px 0 0;
	padding: 0 4px;
	color: #909399;
	font-size: 13px;
}

@media (max-width: 960px) {
	.filter-panel,
	.table-tools {
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

	.filter-actions,
	.icon-actions,
	.batch-actions {
		flex-wrap: wrap;
	}
}
</style>
