<template>
	<section class="graduated-students-page">
		<!-- 筛选区 -->
		<section class="filter-panel">
			<div class="filter-grid">
				<div class="filter-item">
					<label class="filter-label">姓名:</label>
					<el-input v-model="query.keyword" placeholder="姓名或电话" clearable />
				</div>
				<div class="filter-item">
					<label class="filter-label">分校:</label>
					<el-input v-model="query.branchSchool" placeholder="分校名称" clearable />
				</div>
				<div class="filter-item">
					<label class="filter-label">年级:</label>
					<el-input v-model="query.gradeId" placeholder="年级ID（数字）" clearable />
				</div>
				<div class="filter-item">
					<label class="filter-label">授课老师:</label>
					<el-input v-model="query.teacherName" placeholder="老师姓名" clearable />
				</div>
			</div>
			<div class="filter-actions">
				<el-button :icon="Search" circle :loading="loading" @click="handleSearch" />
				<el-button :icon="CircleClose" circle @click="handleReset" />
				<el-button :icon="Download" :loading="exporting" @click="handleExport">导出</el-button>
			</div>
		</section>

		<!-- 工具栏：左侧批量操作 + 右侧通用按钮 -->
		<section class="toolbar-panel">
			<div class="toolbar-left compact-actions">
				<el-tooltip content="转为在学" placement="top">
					<el-button
						circle
						link
						type="primary"
						:disabled="selection.length === 0 || stageSwitching"
						:icon="Back"
						@click="handleSwitchToStudying"
					/>
				</el-tooltip>
				<el-tooltip content="删除所选" placement="top">
					<el-button
						circle
						link
						type="danger"
						:disabled="selection.length === 0 || deleting"
						:icon="Delete"
						@click="handleDeleteSelected"
					/>
				</el-tooltip>
				<el-tooltip content="导入结业学员" placement="top">
					<el-button circle link type="success" :icon="UploadFilled" :loading="importing" @click="handleOpenImport" />
				</el-tooltip>
			</div>

			<div class="toolbar-right table-tools">
				<el-tooltip content="刷新" placement="top">
					<el-button link :icon="RefreshRight" @click="handleRefresh" />
				</el-tooltip>
				<el-tooltip content="打印" placement="top">
					<el-button link :icon="Printer" @click="handlePrint" />
				</el-tooltip>
				<el-popover v-model:visible="columnPopoverVisible" placement="bottom-end" :width="640" trigger="click">
					<template #reference>
						<span class="column-trigger-wrap">
							<el-tooltip content="自定义列" placement="top">
								<el-button link :icon="Grid" @click="openColumnPopover" />
							</el-tooltip>
						</span>
					</template>
					<section class="column-popover">
						<div class="column-title">自定义显示列：</div>
						<div class="column-options">
							<el-checkbox v-model="columnDraft.id">编号</el-checkbox>
							<el-checkbox v-model="columnDraft.name">学员姓名</el-checkbox>
							<el-checkbox v-model="columnDraft.schoolName">分校</el-checkbox>
							<el-checkbox v-model="columnDraft.familyRel">亲属关系</el-checkbox>
							<el-checkbox v-model="columnDraft.mobile">联系电话</el-checkbox>
							<el-checkbox v-model="columnDraft.counselorName">顾问</el-checkbox>
							<el-checkbox v-model="columnDraft.gradeName">年级</el-checkbox>
							<el-checkbox v-model="columnDraft.countLessonRemaining">课时数</el-checkbox>
							<el-checkbox v-model="columnDraft.credit">积分</el-checkbox>
							<el-checkbox v-model="columnDraft.gender">性别</el-checkbox>
							<el-checkbox v-model="columnDraft.age">年龄</el-checkbox>
							<el-checkbox v-model="columnDraft.remark">备注</el-checkbox>
						</div>
						<div class="column-actions">
							<el-button link @click="restoreColumns">恢复</el-button>
							<el-button link type="primary" @click="confirmColumns">确认</el-button>
						</div>
					</section>
				</el-popover>
			</div>
		</section>

		<!-- 表格 -->
		<section class="table-panel">
			<el-table
				ref="tableRef"
				v-loading="loading"
				:data="tableRows"
				stripe
				border
				size="small"
				row-key="id"
				@selection-change="onSelectionChange"
			>
				<el-table-column type="selection" width="48" fixed />
				<el-table-column v-if="visibleColumns.id" prop="id" label="编号" width="90" fixed />

				<el-table-column v-if="visibleColumns.name" prop="name" label="学员姓名" min-width="120" show-overflow-tooltip>
					<template #default="{ row }">
						<el-button link type="primary" @click="openDetail(row)">{{ row.name || "-" }}</el-button>
					</template>
				</el-table-column>

				<el-table-column
					v-if="visibleColumns.schoolName"
					prop="schoolName"
					label="分校"
					min-width="100"
					show-overflow-tooltip
				/>
				<el-table-column v-if="visibleColumns.familyRel" prop="familyRel" label="亲属关系" width="90" />
				<el-table-column
					v-if="visibleColumns.mobile"
					prop="mobile"
					label="联系电话"
					min-width="130"
					show-overflow-tooltip
				/>
				<el-table-column
					v-if="visibleColumns.counselorName"
					prop="counselorName"
					label="顾问"
					min-width="110"
					show-overflow-tooltip
				/>
				<el-table-column v-if="visibleColumns.gradeName" prop="gradeName" label="年级" min-width="90" />

				<el-table-column v-if="visibleColumns.countLessonRemaining" label="课时数" width="120" align="center">
					<template #default="{ row }">
						<el-button link type="primary" class="hour-link">{{ row.countLessonRemaining ?? 0 }}</el-button>
					</template>
				</el-table-column>

				<el-table-column v-if="visibleColumns.credit" prop="credit" label="积分" width="80" align="center" />
				<el-table-column v-if="visibleColumns.gender" prop="gender" label="性别" width="70" />
				<el-table-column v-if="visibleColumns.age" prop="age" label="年龄" width="70" align="center" />
				<el-table-column
					v-if="visibleColumns.remark"
					prop="remark"
					label="备注"
					min-width="150"
					show-overflow-tooltip
				/>

				<el-table-column label="操作" width="120" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="openDetail(row)">查看</el-button>
					</template>
				</el-table-column>
			</el-table>

			<div class="pager-wrap">
				<el-pagination
					v-model:current-page="pageIndex"
					v-model:page-size="pageSize"
					background
					layout="total, sizes, prev, pager, next, jumper"
					:page-sizes="[10, 20, 50, 100]"
					:total="total"
					@current-change="loadList"
					@size-change="handlePageSizeChange"
				/>
			</div>
		</section>

		<FileImportDialog
			v-model="graduatedImportVisible"
			:title="importTitle"
			mode="backend"
			:action="STUDENT_IMPORT_ACTIONS.graduation"
			:headers="uploadHeaders"
			template-file-name="结业学员导入模板.xlsx"
			@import-success="handleImportSuccess"
		/>
	</section>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import {
	Back,
	CircleClose,
	Delete,
	Download,
	Grid,
	Printer,
	RefreshRight,
	Search,
	UploadFilled,
} from "@element-plus/icons-vue";
import { useRouter } from "vue-router";
import FileImportDialog from "@/components/FileImportDialog/index.vue";
import {
	STUDENT_IMPORT_ACTIONS,
	exportGraduatedStudentsFile,
	getStudentConsolePage,
	modifyStudentStage,
} from "@/apis/student";
import type { StudentConsoleRowDTO } from "@/apis/student/type";

/** 列表行（对齐 openapi 的 StudentListVO，尽量容错字段名） */
type StudentListRow = StudentConsoleRowDTO;

interface PagePayload {
	total?: number;
	totalCount?: number;
	totalElements?: number;
	rows?: StudentListRow[];
	list?: StudentListRow[];
	records?: StudentListRow[];
	content?: StudentListRow[];
	data?: unknown;
}

const loading = ref(false);
const exporting = ref(false);
const stageSwitching = ref(false);
const deleting = ref(false);
const importing = ref(false);
const pageIndex = ref(1);
const pageSize = ref(10);
const total = ref(0);
const tableRows = ref<StudentListRow[]>([]);
const selection = ref<StudentListRow[]>([]);
const tableRef = ref<any>();
const latestRequestSeq = ref(0);

const columnPopoverVisible = ref(false);
const defaultColumns = {
	id: true,
	name: true,
	schoolName: true,
	familyRel: true,
	mobile: true,
	counselorName: true,
	gradeName: true,
	countLessonRemaining: true,
	credit: true,
	gender: true,
	age: true,
	remark: true,
};
const visibleColumns = reactive({ ...defaultColumns });
const columnDraft = reactive({ ...defaultColumns });

const query = reactive({
	keyword: "",
	branchSchool: "",
	gradeId: "",
	teacherName: "",
});

const router = useRouter();
const uploadHeaders = computed(() => {
	const token = localStorage.getItem("token");
	const headers: Record<string, string> = {};
	if (token) {
		headers.Authorization = `Bearer ${token}`;
	}
	return headers;
});

function onSelectionChange(rows: StudentListRow[]) {
	selection.value = rows;
}

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

function handlePrint() {
	const headers: Array<{ key: keyof typeof visibleColumns; label: string }> = [
		{ key: "id", label: "编号" },
		{ key: "name", label: "学员姓名" },
		{ key: "schoolName", label: "分校" },
		{ key: "familyRel", label: "亲属关系" },
		{ key: "mobile", label: "联系电话" },
		{ key: "counselorName", label: "顾问" },
		{ key: "gradeName", label: "年级" },
		{ key: "countLessonRemaining", label: "课时数" },
		{ key: "credit", label: "积分" },
		{ key: "gender", label: "性别" },
		{ key: "age", label: "年龄" },
		{ key: "remark", label: "备注" },
	];
	const activeHeaders = headers.filter((h) => visibleColumns[h.key]);
	if (activeHeaders.length === 0) {
		ElMessage.warning("当前没有可打印的列");
		return;
	}

	const tableHeader = activeHeaders.map((h) => `<th>${h.label}</th>`).join("");
	const rowsHtml = tableRows.value
		.map((row) => {
			const tds = activeHeaders
				.map((h) => {
					if (h.key === "countLessonRemaining") return `<td>${String(row.countLessonRemaining ?? 0)}</td>`;
					const val = (row as any)[h.key];
					return `<td>${String(val ?? "-")}</td>`;
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
		<title>结业学员列表</title>
		<style>
			body { font-family: Arial, "Microsoft YaHei", sans-serif; padding: 20px; }
			h2 { margin: 0 0 12px; }
			table { border-collapse: collapse; width: 100%; }
			th, td { border: 1px solid #dcdfe6; padding: 8px; text-align: left; font-size: 12px; }
			th { background: #f5f7fa; }
		</style>
	</head>
	<body>
		<h2>结业学员列表</h2>
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
	win.print();
}

function getSelectedStudentIds(): number[] {
	return selection.value.map((r) => Number(r.id)).filter((n) => Number.isFinite(n) && n > 0);
}

async function handleSwitchToStudying() {
	const ids = getSelectedStudentIds();
	if (ids.length === 0) {
		ElMessage.warning("请先选择要转为在学的学员");
		return;
	}

	stageSwitching.value = true;
	try {
		await ElMessageBox.confirm(`确认将选中学员从结业转为在学？（共 ${ids.length} 人）`, "转为在学", {
			type: "warning",
		});

		// stage：1=在学，2=结业
		await Promise.all(ids.map((studentId) => modifyStudentStage({ id: studentId, stage: 1 })));

		ElMessage.success("转为在学成功");
		selection.value = [];
		tableRef.value?.clearSelection?.();
		loadList();
	} catch {
		/* 用户取消 */
	} finally {
		stageSwitching.value = false;
	}
}

async function handleDeleteSelected() {
	const ids = getSelectedStudentIds();
	if (ids.length === 0) {
		ElMessage.warning("请先选择要删除的学员");
		return;
	}

	deleting.value = true;
	try {
		await ElMessageBox.confirm(`确认删除所选学员？（共 ${ids.length} 人）`, "删除确认", { type: "warning" });

		// stage：4=退学（当前以“删除”语义实现：从列表移除）
		await Promise.all(ids.map((studentId) => modifyStudentStage({ id: studentId, stage: 4 })));

		ElMessage.success("删除成功");
		selection.value = [];
		tableRef.value?.clearSelection?.();
		loadList();
	} catch {
		/* 用户取消 */
	} finally {
		deleting.value = false;
	}
}

const graduatedImportVisible = ref(false);
const importTitle = "导入结业学员";
function handleOpenImport() {
	graduatedImportVisible.value = true;
}

function handleImportSuccess() {
	graduatedImportVisible.value = false;
	loadList();
}

function isLikelyMockLoremMessage(text: string): boolean {
	const t = text.trim();
	if (t.length < 6) return false;
	if (/[\u4e00-\u9fff]/.test(t)) return false;
	return /\b(lorem|ipsum|dolor|fugiat|veniam|irure|laborum|proident|laboris|nisi|consectetur|adipiscing|commodo|eiusmod|dolore|magna|mollit|nostrud|nulla|pariatur|ullamco|voluptate|excepteur|culpa|elit|quis|sunt|tempor|ut|velit|officia|deserunt|anim|esse|cillum|eu|incididunt|minim|occaecat|reprehenderit|sint|duis|aute)\b/i.test(
		t,
	);
}

function userFacingApiMessage(raw: string | undefined, fallback: string): string {
	const r = raw?.trim();
	if (!r) return fallback;
	if (isLikelyMockLoremMessage(r)) {
		return "接口返回了 Mock/文档自动生成的拉丁假文（不是真实业务说明）。请在 Apifox 中把该接口的成功示例改为：code 为 0 或 10000、data 内含列表，并把 message 改成可读中文或留空。";
	}
	return r;
}

async function requestApiRaw<T = unknown>(
	url: string,
	options: {
		method: "GET" | "POST";
		params?: Record<string, string | number | undefined>;
		body?: Record<string, unknown>;
	},
): Promise<T> {
	const token = localStorage.getItem("token");
	const headers: Record<string, string> = {
		Accept: "application/json",
	};
	if (token) headers.Authorization = `Bearer ${token}`;

	let requestUrl = `/api${url}`;
	let body: string | undefined;
	if (options.method === "GET") {
		const search = new URLSearchParams();
		Object.entries(options.params || {}).forEach(([key, value]) => {
			if (value !== undefined && value !== null && value !== "") search.append(key, String(value));
		});
		const qs = search.toString();
		if (qs) requestUrl += `?${qs}`;
	} else {
		headers["Content-Type"] = "application/json;charset=UTF-8";
		body = JSON.stringify(options.body || {});
	}

	const resp = await fetch(requestUrl, { method: options.method, headers, body });
	if (!resp.ok) throw new Error(`请求失败（HTTP ${resp.status}）`);

	const rawText = await resp.text();
	let json: { code?: number; message?: string; msg?: string; data?: T; success?: boolean };
	try {
		json = rawText ? (JSON.parse(rawText) as typeof json) : {};
	} catch {
		throw new Error(
			`响应不是合法 JSON（HTTP ${resp.status}）。网关/函数计算可能返回了错误页，请在「网络 → 响应」查看正文。`,
		);
	}
	if (!json || typeof json !== "object") throw new Error("接口返回格式错误");
	if (!("data" in json)) throw new Error(userFacingApiMessage(json.message || json.msg, "接口缺少 data 字段"));

	const c = json.code;
	const dataPayload = json.data;
	const hasPagedList =
		dataPayload != null &&
		typeof dataPayload === "object" &&
		!Array.isArray(dataPayload) &&
		["rows", "list", "records", "content"].some((k) => Array.isArray((dataPayload as Record<string, unknown>)[k]));

	if (c !== undefined && c !== null && Number(c) !== 0 && Number(c) !== 10000 && Number(c) !== 200) {
		if (!hasPagedList) throw new Error(userFacingApiMessage(json.message || json.msg, `业务错误 code=${json.code}`));
	}

	return (json.data as T) ?? (null as T);
}

function looksLikeRowItem(item: unknown): boolean {
	if (!item || typeof item !== "object" || Array.isArray(item)) return false;
	const o = item as Record<string, unknown>;
	return "id" in o || "name" in o || "mobile" in o;
}

function pickRows(obj: Record<string, unknown>): StudentListRow[] {
	const candidates = ["rows", "list", "records", "content", "items", "students", "studentList", "pageData", "dataList"];
	for (const key of candidates) {
		const v = obj[key];
		if (Array.isArray(v) && v.length >= 0) return (Array.isArray(v) ? (v as StudentListRow[]) : []) ?? [];
	}
	for (const v of Object.values(obj)) {
		if (!Array.isArray(v) || v.length === 0) continue;
		if (looksLikeRowItem(v[0])) return v as StudentListRow[];
	}
	return [];
}

function pickTotal(obj: Record<string, unknown>, rowsLen: number): number {
	const keys = ["total", "totalCount", "totalElements", "count"];
	for (const key of keys) {
		const v = obj[key];
		if (v !== undefined && v !== null && v !== "") {
			const n = Number(v);
			if (!Number.isNaN(n)) return n;
		}
	}
	return rowsLen;
}

function normalizePage(data: unknown): { rows: StudentListRow[]; total: number } {
	if (data == null) return { rows: [], total: 0 };
	if (Array.isArray(data)) return { rows: data as StudentListRow[], total: data.length };
	if (typeof data !== "object") return { rows: [], total: 0 };

	let obj = data as Record<string, unknown>;
	if ("data" in obj && obj.data != null) {
		const inner = obj.data;
		if (Array.isArray(inner)) return { rows: inner as StudentListRow[], total: inner.length };
		if (typeof inner === "object") obj = inner as Record<string, unknown>;
	}

	const rows = pickRows(obj);
	const totalVal = pickTotal(obj, rows.length);
	return { rows, total: totalVal };
}

function handleSearch() {
	pageIndex.value = 1;
	loadList();
}

function handleReset() {
	query.keyword = "";
	query.branchSchool = "";
	query.gradeId = "";
	query.teacherName = "";
	pageIndex.value = 1;
	loadList();
}

function handlePageSizeChange() {
	pageIndex.value = 1;
	loadList();
}

async function loadList() {
	const requestSeq = ++latestRequestSeq.value;
	loading.value = true;
	try {
		const gradeIdNum = query.gradeId.trim() === "" ? undefined : Number(query.gradeId);

		const params: Record<string, string | number | undefined> = {
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			stage: "GRADUATION",
			keyword: query.keyword.trim() || undefined,
		};

		if (gradeIdNum !== undefined && !Number.isNaN(gradeIdNum)) params.gradeId = gradeIdNum;
		if (query.branchSchool.trim()) params.branchSchool = query.branchSchool.trim();
		if (query.teacherName.trim()) params.teacherName = query.teacherName.trim();

		const data = await getStudentConsolePage(params);
		const { rows, total: t } = normalizePage(data);
		if (requestSeq !== latestRequestSeq.value) return;
		tableRows.value = rows;
		total.value = t;
	} catch (e: any) {
		if (requestSeq !== latestRequestSeq.value) return;
		ElMessage.error(e?.message || "加载结业学员失败");
		tableRows.value = [];
		total.value = 0;
	} finally {
		if (requestSeq === latestRequestSeq.value) loading.value = false;
	}
}

function escapeCsvCell(value: unknown): string {
	const s = String(value ?? "");
	if (/[",\n\r]/.test(s)) return `"${s.replace(/"/g, '""')}"`;
	return s;
}

function downloadTextFile(filename: string, content: string, mime = "text/csv;charset=utf-8") {
	const blob = new Blob([content], { type: mime });
	const url = URL.createObjectURL(blob);
	const a = document.createElement("a");
	a.href = url;
	a.download = filename;
	a.click();
	URL.revokeObjectURL(url);
}

function downloadBlobFile(filename: string, blob: Blob) {
	const url = URL.createObjectURL(blob);
	const a = document.createElement("a");
	a.href = url;
	a.download = filename;
	a.click();
	URL.revokeObjectURL(url);
}

async function handleExport() {
	exporting.value = true;
	try {
		const blob = await exportGraduatedStudentsFile({
			name: query.keyword.trim() || undefined,
		});
		downloadBlobFile(`结业学员导出_${Date.now()}.xlsx`, blob);
		ElMessage.success("已开始下载");
		return;
		const rowsToExport = selection.value.length ? selection.value : tableRows.value;
		const header = [
			"编号",
			"学员姓名",
			"分校",
			"亲属关系",
			"联系电话",
			"顾问",
			"年级",
			"课时数",
			"积分",
			"性别",
			"年龄",
			"备注",
		];
		const csvLines = [
			header.join(","),
			...rowsToExport.map((r) =>
				[
					r.id,
					r.name,
					r.schoolName,
					r.familyRel,
					r.mobile,
					r.counselorName,
					r.gradeName,
					r.countLessonRemaining ?? 0,
					r.credit ?? 0,
					r.gender,
					r.age ?? "",
					r.remark,
				]
					.map(escapeCsvCell)
					.join(","),
			),
		];
		const csv = "\ufeff" + csvLines.join("\n");
		downloadTextFile(`结业学员导出_${Date.now()}.csv`, csv);
		ElMessage.success("导出已开始下载");
	} catch (e: any) {
		ElMessage.error(e?.message || "导出失败");
	} finally {
		exporting.value = false;
	}
}

function openDetail(row: StudentListRow) {
	if (row?.id == null) {
		ElMessage.warning("缺少学员编号");
		return;
	}
	router.push({
		path: "/student/detail",
		query: {
			id: String(row.id),
			name: row.name || "",
			phone: row.mobile || "",
		},
	});
}

onMounted(() => {
	loadList();
});
</script>

<style scoped>
.graduated-students-page {
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
	gap: 6px;
}

.filter-label {
	min-width: 60px;
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

.toolbar-panel {
	display: flex;
	justify-content: space-between;
	align-items: center;
	background: #fff;
	border-radius: 4px;
	padding: 8px 12px;
}

.toolbar-left {
	display: flex;
	gap: 8px;
	align-items: center;
}

.toolbar-right {
	display: flex;
	gap: 8px;
	align-items: center;
}

.compact-actions :deep(.el-button) {
	height: 28px;
	padding: 0 10px;
}

.table-tools {
	display: flex;
	gap: 8px;
	align-items: center;
}

.column-trigger-wrap {
	display: inline-flex;
}

.column-popover {
	display: flex;
	flex-direction: column;
	gap: 10px;
}

.column-title {
	font-size: 16px;
	color: #606266;
	padding-bottom: 8px;
	border-bottom: 1px solid #ebeef5;
}

.column-options {
	display: grid;
	grid-template-columns: repeat(3, minmax(120px, 1fr));
	gap: 10px 14px;
}

.column-actions {
	display: flex;
	justify-content: flex-end;
	gap: 10px;
}

.table-panel :deep(.el-table th.el-table__cell),
.table-panel :deep(.el-table td.el-table__cell) {
	padding: 6px 0;
}

.pager-wrap {
	margin-top: 8px;
	display: flex;
	justify-content: flex-end;
}

.hour-link {
	padding: 0 4px;
	vertical-align: middle;
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

	.toolbar-panel {
		flex-direction: column;
		align-items: stretch;
		gap: 8px;
	}

	.toolbar-right {
		justify-content: flex-end;
	}
}
</style>
