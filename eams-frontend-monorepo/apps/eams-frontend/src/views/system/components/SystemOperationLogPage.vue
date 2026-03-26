<template>
	<section class="panel-card log-page">
		<div class="log-page__toolbar">
			<el-form :inline="true" class="log-page__filters">
				<el-form-item label="操作内容">
					<el-input v-model="filters.content" placeholder="请输入操作内容" clearable />
				</el-form-item>
				<el-form-item label="操作类型">
					<el-input v-model="filters.type" placeholder="请输入操作类型" clearable />
				</el-form-item>
				<el-form-item label="操作人ID">
					<el-input v-model="filters.operator" placeholder="请输入操作人ID" clearable />
				</el-form-item>
				<el-form-item>
					<el-button type="primary" @click="applyFilters">查询</el-button>
					<el-button @click="resetFilters">重置</el-button>
				</el-form-item>
			</el-form>

			<div class="log-page__actions">
				<el-button circle :icon="RefreshRight" @click="refreshPage" />
				<el-button circle :icon="Printer" />
				<el-button circle :icon="Grid" />
			</div>
		</div>

		<el-table v-loading="loading" :data="tableRows" border>
			<el-table-column prop="time" label="日志时间" min-width="170" />
			<el-table-column prop="operator" label="操作人" min-width="100" />
			<el-table-column prop="type" label="操作类型" min-width="120" />
			<el-table-column prop="content" label="操作内容" min-width="240" />
			<el-table-column prop="path" label="请求路径" min-width="220" />
			<el-table-column prop="system" label="系统" min-width="100" />
			<el-table-column prop="ip" label="IP地址" min-width="140" />
			<el-table-column prop="browser" label="浏览器" min-width="150" />
			<el-table-column prop="responseTime" label="响应时间" min-width="120" />
		</el-table>

		<div class="log-page__pagination">
			<el-pagination
				background
				layout="total, sizes, prev, pager, next"
				:current-page="pageState.pageIndex"
				:page-size="pageState.pageSize"
				:page-sizes="[10, 20, 50, 100]"
				:total="pageState.total"
				@current-change="handleCurrentChange"
				@size-change="handleSizeChange"
			/>
		</div>
	</section>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref } from "vue";
import { ElMessage } from "element-plus";
import { Grid, Printer, RefreshRight } from "@element-plus/icons-vue";
import { listOperationLogs } from "@/apis/system";
import type { OptlogDTO } from "@/apis/system/type";

interface OperationLogTableRow {
	time: string;
	operator: string;
	type: string;
	content: string;
	path: string;
	system: string;
	ip: string;
	browser: string;
	responseTime: string;
}

const loading = ref(false);
const tableRows = ref<OperationLogTableRow[]>([]);

const filters = reactive({
	content: "",
	type: "",
	operator: "",
});

const submittedFilters = reactive({
	content: "",
	type: "",
	operator: "",
});

const pageState = reactive({
	pageIndex: 1,
	pageSize: 10,
	total: 0,
});

function mapOperationLog(item: OptlogDTO): OperationLogTableRow {
	const responseTime = String(item.time_cost ?? "");
	return {
		time: item.add_time || "",
		operator: item.operator != null ? String(item.operator) : "",
		type: item.type || "",
		content: item.info || "",
		path: item.org_id != null ? String(item.org_id) : "",
		system: item.os_name || "",
		ip: item.browser_ver || "",
		browser: item.broswer_name != null ? String(item.broswer_name) : "",
		responseTime: responseTime && /^\d+$/.test(responseTime) ? `${responseTime}ms` : responseTime,
	};
}

async function loadLogs() {
	loading.value = true;
	try {
		const operatorValue = submittedFilters.operator.trim();
		if (operatorValue && Number.isNaN(Number(operatorValue))) {
			ElMessage.warning("操作人目前按 ID 查询，请输入数字");
			return;
		}

		const res = await listOperationLogs({
			info: submittedFilters.content.trim() || undefined,
			type: submittedFilters.type.trim() || undefined,
			operator: operatorValue ? Number(operatorValue) : undefined,
			pageIndex: pageState.pageIndex,
			pageSize: pageState.pageSize,
		});

		tableRows.value = (res.rows || []).map(mapOperationLog);
		pageState.pageIndex = res.pageIndex;
		pageState.pageSize = res.pageSize;
		pageState.total = res.total;
	} finally {
		loading.value = false;
	}
}

function applyFilters() {
	submittedFilters.content = filters.content;
	submittedFilters.type = filters.type;
	submittedFilters.operator = filters.operator;
	pageState.pageIndex = 1;
	loadLogs();
}

function resetFilters() {
	filters.content = "";
	filters.type = "";
	filters.operator = "";
	submittedFilters.content = "";
	submittedFilters.type = "";
	submittedFilters.operator = "";
	pageState.pageIndex = 1;
	loadLogs();
}

function refreshPage() {
	loadLogs();
}

function handleCurrentChange(page: number) {
	pageState.pageIndex = page;
	loadLogs();
}

function handleSizeChange(size: number) {
	pageState.pageSize = size;
	pageState.pageIndex = 1;
	loadLogs();
}

onMounted(() => {
	loadLogs();
});
</script>

<style scoped>
.panel-card {
	padding: 18px;
	margin: 16px;
	background: #fff;
	border: 1px solid #edf0f5;
	box-shadow: 0 1px 2px rgb(31 45 61 / 4%);
}

.log-page__toolbar {
	margin-bottom: 14px;
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 16px;
}

.log-page__filters {
	flex: 1;
}

.log-page__actions {
	display: flex;
	gap: 12px;
}

.log-page__pagination {
	margin-top: 16px;
	display: flex;
	justify-content: flex-end;
}

@media (max-width: 1280px) {
	.log-page__toolbar {
		flex-direction: column;
	}

	.log-page__actions {
		justify-content: flex-end;
		width: 100%;
	}
}
</style>
