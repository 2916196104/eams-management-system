<template>
	<section class="follow-page">
		<!-- 筛选区 -->
		<section class="filter-panel">
			<div class="filter-grid">
				<div class="filter-item">
					<label class="filter-label">学员姓名:</label>
					<el-input v-model="query.customerName" placeholder="请输入学员姓名" clearable />
				</div>

				<div class="filter-item">
					<label class="filter-label">跟进阶段:</label>
					<el-select v-model="query.followStatus" placeholder="请选择" clearable style="width: 180px">
						<el-option label="待跟进" :value="0" />
						<el-option label="已跟进" :value="1" />
					</el-select>
				</div>

				<div class="filter-item">
					<label class="filter-label">开始日期:</label>
					<el-date-picker
						v-model="query.startDate"
						type="date"
						placeholder="选择开始日期"
						clearable
						format="YYYY-MM-DD"
						value-format="YYYY-MM-DD"
					/>
				</div>

				<div class="filter-item">
					<label class="filter-label">结束日期:</label>
					<el-date-picker
						v-model="query.endDate"
						type="date"
						placeholder="选择结束日期"
						clearable
						format="YYYY-MM-DD"
						value-format="YYYY-MM-DD"
					/>
				</div>
			</div>

			<div class="filter-actions">
				<el-button circle :icon="Search" :loading="loading" @click="handleSearch" />
				<el-button circle :icon="CircleClose" @click="handleReset" />
			</div>
		</section>

		<!-- 工具栏 + 表格 -->
		<section class="table-panel">
			<div class="table-tools">
				<el-tooltip content="刷新" placement="top">
					<el-button link :icon="RefreshRight" circle @click="handleRefresh" />
				</el-tooltip>
				<el-tooltip content="打印" placement="top">
					<el-button link :icon="Printer" circle @click="handlePrint" />
				</el-tooltip>
				<el-popover v-model:visible="columnPopoverVisible" placement="bottom-end" :width="640" trigger="click">
					<section class="column-popover">
						<div class="column-title">自定义显示列：</div>
						<div class="column-options">
							<el-checkbox v-model="columnDraft.followTime">跟进时间</el-checkbox>
							<el-checkbox v-model="columnDraft.customer">客户</el-checkbox>
							<el-checkbox v-model="columnDraft.stage">阶段</el-checkbox>
							<el-checkbox v-model="columnDraft.followMethod">跟进方式</el-checkbox>
							<el-checkbox v-model="columnDraft.nextFollow">下次跟进</el-checkbox>
							<el-checkbox v-model="columnDraft.recordTime">记录时间</el-checkbox>
							<el-checkbox v-model="columnDraft.followContent">跟进内容</el-checkbox>
						</div>
						<div class="column-actions">
							<el-button link @click="restoreColumns">恢复</el-button>
							<el-button link type="primary" @click="confirmColumns">确认</el-button>
						</div>
					</section>

					<template #reference>
						<span class="column-trigger-wrap">
							<el-tooltip content="自定义列" placement="top">
								<el-button link :icon="Grid" circle @click="openColumnPopover" />
							</el-tooltip>
						</span>
					</template>
				</el-popover>
			</div>

			<el-table v-loading="loading" :data="rows" stripe border size="small" row-key="followId">
				<el-table-column v-if="visibleColumns.followTime" label="跟进时间" min-width="160">
					<template #default="{ row }">
						{{ row.lastFollowTime ?? row.followTime ?? row.recordTime ?? "-" }}
					</template>
				</el-table-column>

				<el-table-column v-if="visibleColumns.customer" label="客户" min-width="140" show-overflow-tooltip>
					<template #default="{ row }">
						{{ row.customerName ?? row.customer ?? row.clientName ?? row.phone ?? "-" }}
					</template>
				</el-table-column>

				<el-table-column v-if="visibleColumns.stage" label="阶段" min-width="140" show-overflow-tooltip>
					<template #default="{ row }">
						{{
							row.statusDesc ??
							row.stage ??
							(row.followStatus === 0 ? "待跟进" : row.followStatus === 1 ? "已跟进" : "-")
						}}
					</template>
				</el-table-column>

				<el-table-column v-if="visibleColumns.followMethod" label="跟进方式" min-width="130" show-overflow-tooltip>
					<template #default="{ row }">
						{{ row.followMethod ?? row.method ?? row.followWay ?? "-" }}
					</template>
				</el-table-column>

				<el-table-column v-if="visibleColumns.nextFollow" label="下次跟进" min-width="160" show-overflow-tooltip>
					<template #default="{ row }">
						{{ row.planTime ?? row.nextFollowTime ?? row.nextFollow ?? "-" }}
					</template>
				</el-table-column>

				<el-table-column v-if="visibleColumns.recordTime" label="记录时间" min-width="160" show-overflow-tooltip>
					<template #default="{ row }">
						{{ row.recordTime ?? row.lastFollowTime ?? "-" }}
					</template>
				</el-table-column>

				<el-table-column v-if="visibleColumns.followContent" label="跟进内容" min-width="220" show-overflow-tooltip>
					<template #default="{ row }">
						{{ row.followContent ?? row.content ?? row.followRemark ?? row.interestedCourse ?? row.remark ?? "-" }}
					</template>
				</el-table-column>
			</el-table>
		</section>
	</section>
</template>

<script setup lang="ts">
import { reactive, ref, onMounted } from "vue";
import { ElMessage } from "element-plus";
import { CircleClose, Grid, Printer, RefreshRight, Search } from "@element-plus/icons-vue";

type FollowRow = Record<string, any> & {
	followId?: number | string;
	customerName?: string;
	lastFollowTime?: string;
	planTime?: string;
	statusDesc?: string;
	followStatus?: number;
	interestedCourse?: string;
};

type FollowListResponse = {
	followList?: FollowRow[];
	total?: number;
	pendingCount?: number;
	completedCount?: number;
	// 兼容：后端/Mock 未按 openapi 返回分页结构
	rows?: FollowRow[];
	list?: FollowRow[];
	records?: FollowRow[];
	content?: FollowRow[];
};

const loading = ref(false);
const rows = ref<FollowRow[]>([]);
const requestSeq = ref(0);

const query = reactive<{
	customerName: string;
	followStatus?: number | undefined;
	startDate?: string;
	endDate?: string;
}>({
	customerName: "",
	followStatus: undefined,
	startDate: undefined,
	endDate: undefined,
});

const defaultColumns = {
	followTime: true,
	customer: true,
	stage: true,
	followMethod: true,
	nextFollow: true,
	recordTime: true,
	followContent: true,
};

const visibleColumns = reactive({ ...defaultColumns });
const columnDraft = reactive({ ...defaultColumns });
const columnPopoverVisible = ref(false);

function handleRefresh() {
	loadList();
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

function getFollowTimeText(row: FollowRow) {
	return String(row.lastFollowTime ?? row.followTime ?? row.recordTime ?? "-");
}

function getCustomerText(row: FollowRow) {
	return String(row.customerName ?? row.customer ?? row.clientName ?? row.phone ?? "-");
}

function getStageText(row: FollowRow) {
	const v =
		row.statusDesc ?? row.stage ?? (row.followStatus === 0 ? "待跟进" : row.followStatus === 1 ? "已跟进" : "-");
	return String(v ?? "-");
}

function getFollowMethodText(row: FollowRow) {
	return String(row.followMethod ?? row.method ?? row.followWay ?? "-");
}

function getNextFollowText(row: FollowRow) {
	return String(row.planTime ?? row.nextFollowTime ?? row.nextFollow ?? "-");
}

function getRecordTimeText(row: FollowRow) {
	return String(row.recordTime ?? row.lastFollowTime ?? "-");
}

function getContentText(row: FollowRow) {
	return String(row.followContent ?? row.content ?? row.followRemark ?? row.interestedCourse ?? row.remark ?? "-");
}

function handlePrint() {
	const headers: Array<{ key: keyof typeof visibleColumns; label: string }> = [
		{ key: "followTime", label: "跟进时间" },
		{ key: "customer", label: "客户" },
		{ key: "stage", label: "阶段" },
		{ key: "followMethod", label: "跟进方式" },
		{ key: "nextFollow", label: "下次跟进" },
		{ key: "recordTime", label: "记录时间" },
		{ key: "followContent", label: "跟进内容" },
	];
	const activeHeaders = headers.filter((h) => visibleColumns[h.key]);
	if (activeHeaders.length === 0) {
		ElMessage.warning("当前没有可打印的列");
		return;
	}

	const tableHeader = activeHeaders.map((h) => `<th>${h.label}</th>`).join("");
	const rowsHtml = rows.value
		.map((row) => {
			const tds = activeHeaders
				.map((h) => {
					if (h.key === "followTime") return `<td>${getFollowTimeText(row)}</td>`;
					if (h.key === "customer") return `<td>${getCustomerText(row)}</td>`;
					if (h.key === "stage") return `<td>${getStageText(row)}</td>`;
					if (h.key === "followMethod") return `<td>${getFollowMethodText(row)}</td>`;
					if (h.key === "nextFollow") return `<td>${getNextFollowText(row)}</td>`;
					if (h.key === "recordTime") return `<td>${getRecordTimeText(row)}</td>`;
					if (h.key === "followContent") return `<td>${getContentText(row)}</td>`;
					return `<td>-</td>`;
				})
				.join("");
			return `<tr>${tds}</tr>`;
		})
		.join("");

	const html = `
	<!doctype html>
	<html>
	<head>
		<meta charset="utf-8" />
		<title>我的跟进列表</title>
		<style>
			body { font-family: Arial, "Microsoft YaHei", sans-serif; padding: 20px; }
			h2 { margin: 0 0 12px; }
			table { border-collapse: collapse; width: 100%; }
			th, td { border: 1px solid #dcdfe6; padding: 8px; text-align: left; font-size: 12px; }
			th { background: #f5f7fa; }
		</style>
	</head>
	<body>
		<h2>我的跟进列表</h2>
		<table>
			<thead><tr>${tableHeader}</tr></thead>
			<tbody>${rowsHtml || `<tr><td colspan="${activeHeaders.length}">暂无数据</td></tr>`}</tbody>
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
	setTimeout(() => {
		try {
			win.print();
		} catch {
			ElMessage.warning("打印失败，请检查浏览器设置");
		}
	}, 100);
}

function buildUrl(url: string) {
	const baseURL = String(import.meta.env.VITE_API_URL ?? "");
	if (!baseURL) return url;
	const a = baseURL.endsWith("/") ? baseURL.slice(0, -1) : baseURL;
	const b = url.startsWith("/") ? url : `/${url}`;
	return `${a}${b}`;
}

function isLikelyMockLoremMessage(text: string): boolean {
	const t = text.trim();
	if (t.length < 6) return false;
	if (/[\u4e00-\u9fff]/.test(t)) return false;
	return /\b(lorem|ipsum|dolor|fugiat|veniam|irure|laborum|proident|laboris|nisi|consectetur|adipiscing|commodo|eiusmod|dolore|magna|mollit|nostrud|nulla|pariatur|ullamco|voluptate|excepteur|culpa|elit|quis|sunt|tempor|ut|velit|officia|deserunt|anim|esse|cillum|eu|incididunt|minim|occaecat|reprehenderit|sint|duis|aute)\b/i.test(
		t,
	);
}

function normalizeApiMessage(raw: string | undefined, fallback: string) {
	const r = raw?.trim();
	if (!r) return fallback;
	if (isLikelyMockLoremMessage(r)) {
		return "接口返回了 Mock/文档自动生成的拉丁假文（不是真实业务说明）。请在 Apifox 中把成功示例改为 code 为 0/10000/200，并把 message 改成可读中文或留空。";
	}
	return r;
}

async function requestApiRaw<T = unknown>(url: string, body: Record<string, any>) {
	const token = localStorage.getItem("token");
	const requestUrl = buildUrl(url);

	const headers: Record<string, string> = {
		Accept: "application/json",
		"Content-Type": "application/json;charset=UTF-8",
	};
	if (token) headers.Authorization = `Bearer ${token}`;

	const resp = await fetch(requestUrl, { method: "POST", headers, body: JSON.stringify(body ?? {}) });
	if (!resp.ok) throw new Error(`请求失败（HTTP ${resp.status}）`);

	const rawText = await resp.text();
	let json: any;
	try {
		json = rawText ? JSON.parse(rawText) : {};
	} catch {
		throw new Error(`响应不是合法 JSON（HTTP ${resp.status}）。`);
	}
	if (!json || typeof json !== "object") throw new Error("接口返回格式错误");

	// 按项目通用 JsonVO：data 在外层
	if (!("data" in json)) {
		throw new Error(normalizeApiMessage(json.message || json.msg, "接口缺少 data 字段"));
	}

	const payload = json.data as any;
	const hasFollowList =
		payload != null && typeof payload === "object" && !Array.isArray(payload) && Array.isArray(payload.followList);

	// Mock 常见：code 随机数、success=false 但仍返回列表。若发现 followList，则按“可渲染”放行。
	const code = json.code;
	if (!hasFollowList && code != null && ![0, 10000, 200].includes(Number(code))) {
		throw new Error(normalizeApiMessage(json.message || json.msg, `业务错误 code=${json.code}`));
	}

	// 部分网关会用 header success=false，仍给 data
	const headerSuccess = resp.headers.get("success");
	if (!hasFollowList && (headerSuccess === "false" || headerSuccess === "0")) {
		throw new Error(normalizeApiMessage(json.message || json.msg, "响应标头 success=false，业务未成功"));
	}

	if (!hasFollowList && json.success === false) {
		throw new Error(normalizeApiMessage(json.message || json.msg, "接口返回 success: false"));
	}

	return payload as T;
}

function parseFollowList(data: FollowListResponse | any): FollowRow[] {
	if (!data) return [];
	if (Array.isArray(data)) return data as FollowRow[];
	if (typeof data !== "object") return [];
	const obj = data as FollowListResponse;
	return (obj.followList ?? obj.rows ?? obj.list ?? obj.records ?? obj.content ?? []) as FollowRow[];
}

function toDateValue(input: unknown): Date | null {
	if (input == null || input === "") return null;
	const d = new Date(String(input).replace("T", " "));
	if (Number.isNaN(d.getTime())) return null;
	return d;
}

function inRange(row: FollowRow) {
	const start = toDateValue(query.startDate);
	const end = toDateValue(query.endDate);
	if (!start && !end) return true;

	const candidate =
		row.lastFollowTime ?? row.followTime ?? row.recordTime ?? row.planTime ?? row.nextFollowTime ?? row.nextFollow;
	const t = toDateValue(candidate);
	if (!t) return false;

	if (start && t < start) return false;
	if (end) {
		const end2 = new Date(end);
		end2.setHours(23, 59, 59, 999);
		if (t > end2) return false;
	}
	return true;
}

async function loadList() {
	const current = ++requestSeq.value;
	loading.value = true;
	try {
		const body: Record<string, any> = {};
		if (query.customerName.trim()) body.customerName = query.customerName.trim();
		if (query.followStatus !== undefined && query.followStatus !== null) body.followStatus = query.followStatus;
		// 截图筛选项不在 openapi 入参里：为了兼容后端/Mock 透传字段，这里一并带上
		if (query.startDate) body.startDate = query.startDate;
		if (query.endDate) body.endDate = query.endDate;

		const data = await requestApiRaw<FollowListResponse>("/console/my-follow", body);
		let list = parseFollowList(data);
		// 前端兜底筛选：确保“开始/结束日期”在 mock 数据透传失败时仍可用
		list = list.filter((r) => inRange(r));

		if (current !== requestSeq.value) return;
		rows.value = list;
	} catch (e: any) {
		if (current !== requestSeq.value) return;
		ElMessage.error(e?.message || "加载我的跟进失败");
		rows.value = [];
	} finally {
		if (current === requestSeq.value) loading.value = false;
	}
}

function handleSearch() {
	loadList();
}

function handleReset() {
	query.customerName = "";
	query.followStatus = undefined;
	query.startDate = undefined;
	query.endDate = undefined;
	loadList();
}

onMounted(() => {
	loadList();
});
</script>

<style scoped>
.follow-page {
	padding: 10px 12px;
	display: flex;
	flex-direction: column;
	gap: 8px;
}

.filter-panel,
.table-panel {
	background: #fff;
	border-radius: 4px;
	padding: 10px 12px;
}

.filter-panel {
	display: flex;
	gap: 10px;
	align-items: flex-start;
	justify-content: space-between;
	flex-wrap: wrap;
}

.filter-grid {
	flex: 1;
	display: grid;
	grid-template-columns: repeat(4, minmax(180px, 1fr));
	gap: 8px 12px;
	min-width: 280px;
}

.filter-item {
	display: flex;
	align-items: center;
	gap: 8px;
}

.filter-label {
	min-width: 66px;
	text-align: right;
	color: #303133;
	white-space: nowrap;
	font-size: 13px;
}

.filter-actions {
	display: flex;
	gap: 6px;
	flex-wrap: wrap;
	align-items: center;
}

.table-tools {
	display: flex;
	justify-content: flex-end;
	align-items: center;
	gap: 6px;
	padding-bottom: 4px;
}

.column-trigger-wrap {
	display: inline-flex;
	align-items: center;
}

.table-panel :deep(.el-table th.el-table__cell),
.table-panel :deep(.el-table td.el-table__cell) {
	padding: 6px 0;
}

.column-popover {
	display: flex;
	flex-direction: column;
	gap: 14px;
}

.column-title {
	font-weight: 600;
}

.column-options {
	display: flex;
	flex-wrap: wrap;
	gap: 12px 18px;
}

.column-actions {
	display: flex;
	justify-content: flex-end;
	gap: 8px;
}

@media (max-width: 960px) {
	.filter-panel {
		flex-direction: column;
	}

	.filter-grid {
		grid-template-columns: 1fr;
	}

	.filter-item {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-label {
		text-align: left;
	}
}
</style>
