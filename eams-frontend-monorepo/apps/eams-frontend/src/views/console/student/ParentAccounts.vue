<template>
	<section class="parent-accounts-page">
		<section class="filter-panel">
			<div class="filter-grid">
				<div class="filter-item">
					<label class="filter-label">姓名/手机号:</label>
					<el-input v-model="query.keyword" placeholder="请输入" clearable />
				</div>
				<div class="filter-item">
					<label class="filter-label">微信昵称:</label>
					<el-input v-model="query.wxName" placeholder="请输入" clearable />
				</div>
			</div>
			<div class="filter-actions">
				<el-button type="primary" :icon="Search" :loading="loading" @click="handleSearch">查询</el-button>
				<el-button :icon="CircleClose" @click="handleReset">重置</el-button>
			</div>
		</section>

		<section class="table-panel">
			<div class="table-tools">
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
							<el-checkbox v-model="columnDraft.mobile">手机号/账号</el-checkbox>
							<el-checkbox v-model="columnDraft.name">家长姓名</el-checkbox>
							<el-checkbox v-model="columnDraft.students">关联学生</el-checkbox>
							<el-checkbox v-model="columnDraft.wxName">微信昵称</el-checkbox>
							<el-checkbox v-model="columnDraft.loginTimes">登录次数</el-checkbox>
							<el-checkbox v-model="columnDraft.latestLoginTime">上次登录时间</el-checkbox>
							<el-checkbox v-model="columnDraft.latestLoginIp">上次登录IP</el-checkbox>
							<el-checkbox v-model="columnDraft.addTime">注册时间</el-checkbox>
							<el-checkbox v-model="columnDraft.state">状态</el-checkbox>
						</div>
						<div class="column-actions">
							<el-button link @click="restoreColumns">恢复</el-button>
							<el-button link type="primary" @click="confirmColumns">确认</el-button>
						</div>
					</section>
				</el-popover>
			</div>
			<el-table v-loading="loading" :data="tableRows" stripe border row-key="id" :row-class-name="tableRowClassName">
				<el-table-column v-if="visibleColumns.mobile" prop="mobile" label="账号(手机号)" min-width="140" />
				<el-table-column v-if="visibleColumns.name" prop="name" label="姓名" min-width="100" />
				<el-table-column v-if="visibleColumns.students" label="关联学生" min-width="130">
					<template #default="{ row }">
						<el-button link type="primary" @click="openStudentsDialog(row)">
							{{ getStudentCountText(row) }}
						</el-button>
					</template>
				</el-table-column>
				<el-table-column v-if="visibleColumns.wxName" label="微信昵称" min-width="140">
					<template #default="{ row }">
						<span>{{ row.wxName || "-" }}</span>
						<el-button link type="primary" @click="openBindDialog(row)">绑定</el-button>
					</template>
				</el-table-column>
				<el-table-column v-if="visibleColumns.loginTimes" prop="loginTimes" label="登录次数" width="95" />
				<el-table-column
					v-if="visibleColumns.latestLoginTime"
					prop="latestLoginTime"
					label="上次登录时间"
					min-width="165"
				/>
				<el-table-column v-if="visibleColumns.latestLoginIp" prop="latestLoginIp" label="上次登录IP" min-width="130" />
				<el-table-column v-if="visibleColumns.addTime" prop="addTime" label="注册时间" min-width="165" />
				<el-table-column v-if="visibleColumns.state" label="状态" width="90">
					<template #default="{ row }">
						<el-tag :type="Number(row.state) === 1 ? 'success' : 'info'">
							{{ Number(row.state) === 1 ? "正常" : "禁用" }}
						</el-tag>
					</template>
				</el-table-column>
				<el-table-column label="操作" width="130" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="openAccountDialog(row)">修改</el-button>
						<el-button link type="primary" @click="openPasswordDialog(row)">改密</el-button>
					</template>
				</el-table-column>
			</el-table>

			<div class="pager-wrap">
				<el-pagination
					v-model:current-page="pageNum"
					v-model:page-size="pageSize"
					background
					layout="total, sizes, prev, pager, next, jumper"
					:page-sizes="[10, 20, 50]"
					:total="total"
					@current-change="loadList"
					@size-change="onPageSizeChange"
				/>
			</div>
		</section>
	</section>

	<el-dialog v-model="accountVisible" title="账号信息" width="960px" destroy-on-close>
		<el-form ref="accountFormRef" :model="accountForm" :rules="accountRules" label-width="110px">
			<el-form-item label="手机号:" prop="mobile" required>
				<el-input v-model="accountForm.mobile" />
			</el-form-item>
			<el-form-item label="家长姓名:" prop="name" required>
				<el-input v-model="accountForm.name" />
			</el-form-item>
			<el-form-item label="账号状态:" prop="state">
				<el-switch v-model="accountForm.state" :active-value="1" :inactive-value="0" />
			</el-form-item>
		</el-form>
		<template #footer>
			<el-button @click="accountVisible = false">取消</el-button>
			<el-button type="primary" :loading="submittingAccount" @click="submitAccountChange">提交</el-button>
		</template>
	</el-dialog>

	<el-dialog v-model="passwordVisible" title="重置密码" width="960px" destroy-on-close>
		<el-form ref="passwordFormRef" :model="passwordForm" :rules="passwordRules" label-width="90px">
			<el-form-item label="输入新密码:" prop="newPassword" required>
				<el-input v-model="passwordForm.newPassword" type="password" show-password />
			</el-form-item>
		</el-form>
		<template #footer>
			<el-button @click="passwordVisible = false">取消</el-button>
			<el-button type="primary" :loading="submittingPassword" @click="submitPasswordChange">提交</el-button>
		</template>
	</el-dialog>

	<el-dialog v-model="bindVisible" title="绑定微信" width="560px" destroy-on-close>
		<el-form ref="bindFormRef" :model="bindForm" :rules="bindRules" label-width="110px">
			<el-form-item label="请选择微信用户:" prop="wxName">
				<el-select
					v-model="bindForm.wxName"
					filterable
					allow-create
					default-first-option
					placeholder="请选择"
					style="width: 100%"
				>
					<el-option v-for="item in wxCandidates" :key="item" :label="item" :value="item" />
				</el-select>
			</el-form-item>
		</el-form>
		<template #footer>
			<el-button @click="bindVisible = false">取消</el-button>
			<el-button type="primary" :loading="submittingBind" @click="submitBindWechat">提交</el-button>
		</template>
	</el-dialog>

	<el-dialog v-model="studentsVisible" title="学生列表" width="1100px" destroy-on-close>
		<el-table v-loading="studentsLoading" :data="studentsRows" stripe border>
			<el-table-column prop="id" label="编号" width="90" />
			<el-table-column prop="name" label="学员姓名" min-width="120" />
			<el-table-column prop="familyRelText" label="亲属关系" min-width="100" />
			<el-table-column prop="stage" label="阶段" min-width="100" />
			<el-table-column prop="gender" label="性别" width="70" />
			<el-table-column prop="age" label="年龄" width="70" />
			<el-table-column prop="birthday" label="出生年月" min-width="110" />
			<el-table-column prop="addTime" label="添加时间" min-width="160" />
			<el-table-column prop="remark" label="备注" min-width="120" />
		</el-table>
		<div class="pager-wrap">
			<el-pagination
				v-model:current-page="studentPageNum"
				v-model:page-size="studentPageSize"
				background
				layout="total, sizes, prev, pager, next"
				:page-sizes="[10, 20, 50]"
				:total="studentsTotal"
				@current-change="reloadStudentsDialog"
				@size-change="reloadStudentsPageSize"
			/>
		</div>
		<template #footer>
			<el-button @click="studentsVisible = false">关闭</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { CircleClose, Grid, Printer, RefreshRight, Search } from "@element-plus/icons-vue";
import { ElMessage } from "element-plus";
import type { FormInstance, FormRules } from "element-plus";
import { computed, onMounted, reactive, ref } from "vue";

interface StudentSimple {
	id?: number;
	name?: string;
	familyRel?: number | string;
	stage?: string;
	stageName?: string;
	gender?: string | number;
	age?: number;
	birthday?: string;
	addTime?: string;
	remark?: string;
	[key: string]: unknown;
}

type StudentDisplayRow = Omit<StudentSimple, "stage" | "gender" | "age" | "birthday" | "addTime" | "remark"> & {
	familyRelText: string;
	stage: string;
	gender: string;
	age: number | string;
	birthday: string;
	addTime: string;
	remark: string;
};

interface ParentAccountRow {
	id?: number;
	userId?: number;
	name?: string;
	mobile?: string;
	email?: string;
	remark?: string;
	state?: number;
	wxName?: string;
	loginTimes?: number;
	latestLoginTime?: string;
	latestLoginIp?: string;
	addTime?: string;
	students?: StudentSimple[];
	studentName?: string;
}

interface PageResponse<T> {
	rows?: T[];
	list?: T[];
	records?: T[];
	total?: number;
	totalCount?: number;
}

const loading = ref(false);
const pageNum = ref(1);
const pageSize = ref(10);
const total = ref(0);
const tableRows = ref<ParentAccountRow[]>([]);
const sourceRows = ref<ParentAccountRow[]>([]);
const columnPopoverVisible = ref(false);
const defaultColumns = {
	mobile: true,
	name: true,
	students: true,
	wxName: true,
	loginTimes: true,
	latestLoginTime: true,
	latestLoginIp: true,
	addTime: true,
	state: true,
};
const visibleColumns = reactive({ ...defaultColumns });
const columnDraft = reactive({ ...defaultColumns });

const query = reactive({
	keyword: "",
	wxName: "",
});

const passwordVisible = ref(false);
const submittingPassword = ref(false);
const passwordFormRef = ref<FormInstance>();
const passwordForm = reactive({
	id: 0,
	newPassword: "",
});

const accountVisible = ref(false);
const submittingAccount = ref(false);
const accountFormRef = ref<FormInstance>();
const editingAccountId = ref(0);
const accountForm = reactive({
	id: 0,
	name: "",
	mobile: "",
	state: 1,
});

const bindVisible = ref(false);
const submittingBind = ref(false);
const bindFormRef = ref<FormInstance>();
const bindForm = reactive({
	id: 0,
	wxName: "",
});

const studentsVisible = ref(false);
const studentsLoading = ref(false);
const studentsRows = ref<StudentDisplayRow[]>([]);
const studentsTotal = ref(0);
const currentStudentRow = ref<ParentAccountRow | null>(null);
const studentPageNum = ref(1);
const studentPageSize = ref(20);

const wxCandidates = computed(() => {
	const set = new Set<string>();
	for (const row of tableRows.value) {
		const n = String(row.wxName || "").trim();
		if (n) set.add(n);
	}
	return Array.from(set);
});

const passwordRules: FormRules = {
	newPassword: [{ required: true, message: "请输入密码", trigger: "blur" }],
};

const accountRules: FormRules = {
	name: [{ required: true, message: "请输入姓名", trigger: "blur" }],
	mobile: [{ required: true, message: "请输入手机号", trigger: "blur" }],
};

const bindRules: FormRules = {
	wxName: [{ required: true, message: "请选择微信用户", trigger: "change" }],
};

function extractRows<T>(pageData: unknown): T[] {
	if (Array.isArray(pageData)) return pageData as T[];
	if (!pageData || typeof pageData !== "object") return [];
	const obj = pageData as PageResponse<T>;
	return obj.rows || obj.list || obj.records || [];
}

function extractTotal(pageData: unknown, rowsLen: number): number {
	if (!pageData || typeof pageData !== "object") return rowsLen;
	const obj = pageData as PageResponse<unknown>;
	return Number(obj.total || obj.totalCount || rowsLen);
}

async function requestApiRaw<T = unknown>(
	url: string,
	options: {
		method: "GET" | "POST" | "PUT";
		params?: Record<string, string | number | undefined>;
		body?: Record<string, unknown>;
	},
): Promise<T> {
	const token = localStorage.getItem("token");
	const headers: Record<string, string> = { Accept: "application/json" };
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
	const json = (await resp.json()) as { code?: number; message?: string; msg?: string; data?: T };
	if (!json || typeof json !== "object") throw new Error("接口返回格式错误");
	if (!("data" in json)) throw new Error(json.message || json.msg || "接口缺少 data 字段");
	return (json.data as T) ?? (null as T);
}

async function loadList() {
	loading.value = true;
	try {
		const raw = await requestApiRaw<unknown>("/stu/parent-account/list", {
			method: "GET",
			params: {
				pageNum: pageNum.value,
				pageSize: pageSize.value,
			},
		});
		const rows = extractRows<ParentAccountRow>(raw);
		sourceRows.value = rows;
		applyLocalSearch();
	} catch (error: any) {
		ElMessage.error(error?.message || "加载家长账号失败");
		sourceRows.value = [];
		tableRows.value = [];
		total.value = 0;
	} finally {
		loading.value = false;
	}
}

function handleSearch() {
	// 云端 Mock 每次请求会产生新数据，查询只在当前已加载列表内过滤。
	applyLocalSearch();
}

function handleReset() {
	query.keyword = "";
	query.wxName = "";
	applyLocalSearch();
}

function onPageSizeChange() {
	pageNum.value = 1;
	loadList();
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
		{ key: "mobile", label: "账号(手机号)" },
		{ key: "name", label: "姓名" },
		{ key: "students", label: "关联学生" },
		{ key: "wxName", label: "微信昵称" },
		{ key: "loginTimes", label: "登录次数" },
		{ key: "latestLoginTime", label: "上次登录时间" },
		{ key: "latestLoginIp", label: "上次登录IP" },
		{ key: "addTime", label: "注册时间" },
		{ key: "state", label: "状态" },
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
					if (h.key === "students") return `<td>${getStudentCountText(row)}</td>`;
					if (h.key === "state") return `<td>${Number(row.state) === 1 ? "正常" : "禁用"}</td>`;
					const val = (row as Record<string, unknown>)[h.key];
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
			<title>家长账号列表</title>
			<style>
				body { font-family: Arial, "Microsoft YaHei", sans-serif; padding: 20px; }
				h2 { margin: 0 0 12px; }
				table { border-collapse: collapse; width: 100%; }
				th, td { border: 1px solid #dcdfe6; padding: 8px; text-align: left; font-size: 12px; }
				th { background: #f5f7fa; }
			</style>
		</head>
		<body>
			<h2>家长账号列表</h2>
			<table>
				<thead><tr>${tableHeader}</tr></thead>
				<tbody>${rowsHtml || '<tr><td colspan="' + activeHeaders.length + '">暂无数据</td></tr>'}</tbody>
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

function applyLocalSearch() {
	const keyword = query.keyword.trim();
	const wxKeyword = query.wxName.trim();
	const isMobileKeyword = /^1\d{10}$/.test(keyword);
	let rows = [...sourceRows.value];
	if (keyword) {
		rows = rows.filter((item) => {
			const mobileText = String(item.mobile || "");
			const nameText = String(item.name || "");
			return isMobileKeyword
				? mobileText.includes(keyword)
				: nameText.includes(keyword) || mobileText.includes(keyword);
		});
	}
	if (wxKeyword) {
		rows = rows.filter((item) => String(item.wxName || "").includes(wxKeyword));
	}
	tableRows.value = rows;
	total.value = rows.length;
}

function getStudentCountText(row: ParentAccountRow) {
	const count = Array.isArray(row.students) ? row.students.length : 0;
	if (count > 0) return `${count}人`;
	return row.studentName ? "查看" : "0人";
}

function openPasswordDialog(row: ParentAccountRow) {
	passwordVisible.value = true;
	passwordForm.id = Number(row.id || row.userId || 0);
	passwordForm.newPassword = "";
}

function openAccountDialog(row: ParentAccountRow) {
	accountVisible.value = true;
	accountForm.id = Number(row.id || row.userId || 0);
	editingAccountId.value = accountForm.id;
	accountForm.name = row.name || "";
	accountForm.mobile = row.mobile || "";
	accountForm.state = Number(row.state ?? 1);
}

function openBindDialog(row: ParentAccountRow) {
	bindVisible.value = true;
	bindForm.id = Number(row.id || row.userId || 0);
	bindForm.wxName = row.wxName || "";
}

async function submitPasswordChange() {
	await passwordFormRef.value?.validate();
	submittingPassword.value = true;
	try {
		await requestApiRaw("/stu/parent-account/password", {
			method: "PUT",
			body: {
				id: passwordForm.id,
				oldPassword: passwordForm.newPassword,
				newPassword: passwordForm.newPassword,
				confirmPassword: passwordForm.newPassword,
			},
		});
		ElMessage.success("密码重置成功");
		passwordVisible.value = false;
	} catch (error: any) {
		ElMessage.error(error?.message || "密码修改失败");
	} finally {
		submittingPassword.value = false;
	}
}

async function submitAccountChange() {
	await accountFormRef.value?.validate();
	submittingAccount.value = true;
	try {
		await requestApiRaw("/stu/parent-account/update", {
			method: "PUT",
			body: {
				id: accountForm.id,
				name: accountForm.name,
				mobile: accountForm.mobile,
				state: accountForm.state,
			},
		});
		ElMessage.success("账号修改成功");
		const hit = tableRows.value.find((item) => Number(item.id || item.userId || 0) === editingAccountId.value);
		if (hit) {
			hit.state = accountForm.state;
			hit.name = accountForm.name;
		}
		accountVisible.value = false;
	} catch (error: any) {
		ElMessage.error(error?.message || "账号修改失败");
	} finally {
		submittingAccount.value = false;
	}
}

async function submitBindWechat() {
	await bindFormRef.value?.validate();
	submittingBind.value = true;
	try {
		await requestApiRaw("/stu/parent-account/update", {
			method: "PUT",
			body: {
				id: bindForm.id,
				wxName: bindForm.wxName,
			},
		});
		ElMessage.success("微信绑定成功");
		bindVisible.value = false;
		loadList();
	} catch (error: any) {
		ElMessage.error(error?.message || "微信绑定失败");
	} finally {
		submittingBind.value = false;
	}
}

function mapFamilyRel(value?: number | string): string {
	if (typeof value === "string") {
		const t = value.trim();
		if (!t) return "-";
		if (["父亲", "母亲", "其他"].includes(t)) return t;
		if (["0", "1", "2"].includes(t)) return mapFamilyRel(Number(t));
		return t;
	}
	if (value === 0) return "父亲";
	if (value === 1) return "母亲";
	if (value === 2) return "其他";
	return "-";
}

function mapGender(value?: number | string): string {
	if (value === 1 || value === "1" || value === "男") return "男";
	if (value === 0 || value === "0" || value === 2 || value === "2" || value === "女") return "女";
	return "-";
}

function calcAgeFromBirthday(birthday?: string): number | string {
	if (!birthday) return "-";
	const d = new Date(birthday);
	if (Number.isNaN(d.getTime())) return "-";
	const now = new Date();
	let age = now.getFullYear() - d.getFullYear();
	const m = now.getMonth() - d.getMonth();
	if (m < 0 || (m === 0 && now.getDate() < d.getDate())) age -= 1;
	return age >= 0 ? age : "-";
}

function normalizeStudentRows(rows: StudentSimple[]): StudentDisplayRow[] {
	return rows.map((item) => ({
		...item,
		familyRelText: mapFamilyRel(item.familyRel),
		stage: String(item.stageName || item.stage || "在学学员"),
		gender: mapGender(item.gender),
		age: item.age ?? calcAgeFromBirthday(item.birthday),
		birthday: item.birthday || "-",
		addTime: item.addTime || "-",
		remark: item.remark || "-",
	}));
}

async function fetchStudentDetail(studentId: number) {
	const data = await requestApiRaw<StudentSimple>("/stu/common/stuInformation/get-studentDetail", {
		method: "GET",
		params: { id: studentId },
	});
	return data || {};
}

async function openStudentsDialog(row: ParentAccountRow) {
	currentStudentRow.value = row;
	studentPageNum.value = 1;
	studentsVisible.value = true;
	await reloadStudentsDialog();
}

async function reloadStudentsDialog() {
	if (!currentStudentRow.value) return;
	studentsLoading.value = true;
	try {
		const row = currentStudentRow.value;
		let allStudents = Array.isArray(row.students) ? row.students : [];
		if (allStudents.length === 0) {
			const data = await requestApiRaw<unknown>("/stu/parent-account/list", {
				method: "GET",
				params: {
					pageNum: 1,
					pageSize: 1,
					mobile: row.mobile || undefined,
				},
			});
			const fetchedRows = extractRows<ParentAccountRow>(data);
			const first = fetchedRows[0];
			allStudents = Array.isArray(first?.students) ? first.students : [];
		}
		const start = (studentPageNum.value - 1) * studentPageSize.value;
		const end = start + studentPageSize.value;
		const currentPageStudents = allStudents.slice(start, end);
		const detailRows = await Promise.all(
			currentPageStudents.map(async (item) => {
				const sid = Number(item.id || 0);
				if (!sid) return item;
				try {
					const detail = await fetchStudentDetail(sid);
					return { ...item, ...detail, id: item.id ?? detail.id };
				} catch {
					return item;
				}
			}),
		);
		studentsRows.value = normalizeStudentRows(detailRows);
		studentsTotal.value = allStudents.length;
	} catch (error: any) {
		ElMessage.error(error?.message || "加载关联学生失败");
		studentsRows.value = [];
		studentsTotal.value = 0;
	} finally {
		studentsLoading.value = false;
	}
}

function reloadStudentsPageSize() {
	studentPageNum.value = 1;
	reloadStudentsDialog();
}

function tableRowClassName({ row }: { row: ParentAccountRow }) {
	return Number(row.state) === 0 ? "row-disabled" : "";
}

onMounted(() => {
	loadList();
});
</script>

<style scoped>
.parent-accounts-page {
	padding: 12px;
	display: flex;
	flex-direction: column;
	gap: 10px;
}

.filter-panel,
.table-panel {
	background: #fff;
	border-radius: 4px;
	padding: 12px;
}

.table-tools {
	display: flex;
	justify-content: flex-end;
	gap: 8px;
	margin-bottom: 8px;
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

.filter-panel {
	display: flex;
	gap: 10px;
	justify-content: space-between;
	align-items: flex-start;
	flex-wrap: wrap;
}

.filter-grid {
	flex: 1;
	display: grid;
	grid-template-columns: repeat(2, minmax(220px, 1fr));
	gap: 10px 14px;
}

.filter-item {
	display: flex;
	align-items: center;
	gap: 8px;
}

.filter-label {
	min-width: 86px;
	text-align: right;
	color: #303133;
	font-size: 13px;
	white-space: nowrap;
}

.filter-actions {
	display: flex;
	gap: 8px;
}

.pager-wrap {
	margin-top: 10px;
	display: flex;
	justify-content: flex-end;
}

.table-panel :deep(.el-table .row-disabled td.el-table__cell) {
	background-color: #fff6cc !important;
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
