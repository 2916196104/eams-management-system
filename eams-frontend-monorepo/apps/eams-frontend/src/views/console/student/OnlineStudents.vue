<template>
	<section class="online-students-page">
		<!-- 筛选区 -->
		<section class="filter-panel">
			<div class="filter-grid">
				<div class="filter-item">
					<label class="filter-label">姓名:</label>
					<el-input v-model="query.keyword" placeholder="姓名或电话" clearable />
				</div>
				<div class="filter-item">
					<label class="filter-label">分校:</label>
					<el-input v-model="query.branchSchool" placeholder="分校名称（若后端支持）" clearable />
				</div>
				<div class="filter-item">
					<label class="filter-label">年级:</label>
					<el-input v-model="query.gradeId" placeholder="年级ID（数字）" clearable />
				</div>
				<div class="filter-item">
					<label class="filter-label">授课老师:</label>
					<el-input v-model="query.teacherName" placeholder="老师姓名（若后端支持）" clearable />
				</div>
			</div>
			<div class="filter-actions">
				<el-button :icon="Search" circle :loading="loading" @click="handleSearch" />
				<el-button :icon="CircleClose" circle @click="handleReset" />
				<el-button :icon="Download" :loading="exporting" @click="handleExport">导出</el-button>
			</div>
		</section>

		<!-- 工具栏 -->
		<section class="toolbar-panel">
			<div class="toolbar-left compact-actions">
				<el-button type="primary" size="small" :icon="Plus" @click="tipBatch('添加学员')">添加学员</el-button>
				<el-button size="small" @click="tipBatch('转校')">转校</el-button>
				<el-button size="small" @click="tipBatch('转为意向学员')">转为意向学员</el-button>
				<el-button size="small" @click="tipBatch('结业')">结业</el-button>
				<el-button size="small" @click="tipBatch('删除')">删除</el-button>
				<el-button size="small" :icon="Upload" @click="tipBatch('导入在学学员')">导入在学学员</el-button>
				<el-button size="small" @click="tipBatch('修改顾问')">修改顾问</el-button>
			</div>
			<div class="toolbar-right compact-actions">
				<el-button :icon="RefreshRight" circle size="small" @click="loadList" />
				<el-button :icon="Printer" circle size="small" @click="tipBatch('打印')" />
				<el-button :icon="Grid" circle size="small" @click="tipBatch('列设置')" />
			</div>
		</section>

		<!-- 表格 -->
		<section class="table-panel">
			<el-table
				v-loading="loading"
				:data="tableRows"
				stripe
				border
				size="small"
				row-key="id"
				@selection-change="onSelectionChange"
			>
				<el-table-column type="selection" width="48" fixed />
				<el-table-column prop="id" label="编号" width="100" fixed />
				<el-table-column prop="name" label="学员姓名" min-width="110" show-overflow-tooltip>
					<template #default="{ row }">
						<el-button link type="primary" @click="openDetail(row)">{{ row.name || "-" }}</el-button>
					</template>
				</el-table-column>
				<el-table-column prop="schoolName" label="分校" min-width="100" show-overflow-tooltip />
				<el-table-column prop="parentName" label="家长姓名" min-width="100" show-overflow-tooltip />
				<el-table-column prop="familyRel" label="亲属关系" width="90" />
				<el-table-column prop="mobile" label="联系电话" min-width="120" />
				<el-table-column prop="counselorName" label="顾问" min-width="100" show-overflow-tooltip />
				<el-table-column prop="gradeName" label="年级" min-width="90" />
				<el-table-column label="课时数" width="120" align="center">
					<template #default="{ row }">
						<el-button link type="primary" class="hour-link" @click="openCourseTimes(row)">
							{{ row.countLessonRemaining ?? 0 }}
						</el-button>
						<el-button
							class="hour-refresh"
							link
							type="primary"
							:icon="RefreshRight"
							:loading="refreshingId === row.id"
							@click.stop="refreshCourseTimes(row)"
						/>
					</template>
				</el-table-column>
				<el-table-column prop="credit" label="积分" width="80" align="center" />
				<el-table-column prop="gender" label="性别" width="70" />
				<el-table-column prop="age" label="年龄" width="70" align="center" />
				<el-table-column prop="remark" label="备注" min-width="120" show-overflow-tooltip />
				<el-table-column label="操作" width="140" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="openDetail(row)">查看</el-button>
						<el-button link type="primary" @click="openEnroll(row)">报名</el-button>
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

		<!-- 课时 / 课次摘要 -->
		<el-dialog v-model="hourVisible" title="课时信息" width="520px" destroy-on-close>
			<el-skeleton v-if="hourLoading" :rows="4" animated />
			<el-descriptions v-else-if="hourData" :column="1" border size="small">
				<el-descriptions-item label="学员ID">{{ hourData.studentId ?? "-" }}</el-descriptions-item>
				<el-descriptions-item label="学员姓名">{{ hourData.studentName ?? "-" }}</el-descriptions-item>
				<el-descriptions-item label="课程总次数">{{ hourData.courseTimes ?? "-" }}</el-descriptions-item>
				<el-descriptions-item label="剩余次数">{{ hourData.remainingTimes ?? "-" }}</el-descriptions-item>
			</el-descriptions>
			<el-empty v-else description="暂无数据" />
		</el-dialog>

		<!-- 报名签单 -->
		<el-dialog v-model="enrollVisible" title="录入报名签单信息" width="960px" destroy-on-close>
			<section class="enroll-form">
				<div class="enroll-row">
					<span class="row-label">学生姓名</span>
					<span class="row-value">{{ enrollStudent?.name || "-" }}</span>
				</div>
				<div class="enroll-row">
					<span class="row-label required">选择课程</span>
					<el-input
						:model-value="selectedCourse ? selectedCourse.courseName : ''"
						placeholder="请选择"
						readonly
					>
						<template #append>
							<el-button @click="coursePickerVisible = true">选择</el-button>
						</template>
					</el-input>
				</div>

				<div class="money-row">
					<span>课程总额</span>
					<strong>￥{{ courseTotalAmount.toFixed(2) }}</strong>
				</div>
				<div class="money-row">
					<span>优惠金额</span>
					<strong>￥{{ discountAmount.toFixed(2) }}</strong>
				</div>
				<div class="money-row">
					<span>实收金额</span>
					<strong>￥{{ receiveAmount.toFixed(2) }}</strong>
				</div>

				<div class="notice-row">经财务中心审核通过的报名课时数才会生效。</div>
			</section>
			<template #footer>
				<el-button @click="enrollVisible = false">取消</el-button>
				<el-button type="primary" :loading="submittingEnroll" @click="submitEnroll">提交</el-button>
			</template>
		</el-dialog>

		<!-- 选择课程 -->
		<el-dialog v-model="coursePickerVisible" title="选择课程" width="980px" destroy-on-close @open="loadCourseList">
			<section class="course-picker">
				<div class="picker-filter">
					<label>搜名称:</label>
					<el-input v-model="courseKeyword" placeholder="请输入课程名称" clearable />
					<el-button :icon="IconSearch" @click="handleCourseSearch" />
					<el-button :icon="IconClose" @click="resetCourseSearch" />
				</div>

				<el-table v-loading="courseLoading" :data="courseRows" stripe border>
					<el-table-column prop="courseName" label="课程名称" min-width="220" show-overflow-tooltip />
					<el-table-column prop="courseTimes" label="课时" width="90" />
					<el-table-column prop="unitPrice" label="单价" width="100" />
					<el-table-column prop="totalPrice" label="总价" width="110" />
					<el-table-column prop="unitName" label="单位" width="80" />
					<el-table-column label="操作" width="120" fixed="right">
						<template #default="{ row }">
							<el-button link type="primary" @click="chooseCourse(row)">选择</el-button>
						</template>
					</el-table-column>
				</el-table>
				<div class="pager-wrap">
					<el-pagination
						v-model:current-page="coursePageIndex"
						v-model:page-size="coursePageSize"
						background
						layout="total, sizes, prev, pager, next"
						:page-sizes="[10, 20, 50]"
						:total="courseTotal"
						@current-change="loadCourseList"
						@size-change="onCoursePageSizeChange"
					/>
				</div>
			</section>
		</el-dialog>
	</section>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref } from "vue";
import { ElMessage } from "element-plus";
import { CircleClose, Download, Grid, Plus, Printer, RefreshRight, Search, Upload } from "@element-plus/icons-vue";
import { useRouter } from "vue-router";
import {
	addStudentEnroll,
	exportOnlineStudentsFile,
	getStudentConsolePage,
	getStudentCoursePage,
	getStudentCourseTimesSummary,
} from "@/apis/student";
import type {
	StudentConsoleRowDTO,
	StudentCourseRowDTO,
	StudentCourseTimesSummaryDTO,
} from "@/apis/student/type";

/** 列表行（对齐 openapi StudentListVO） */
type StudentListRow = StudentConsoleRowDTO;

/** 后端/Mock 分页结构差异较大，解析时尽量兼容 */
interface PagePayload {
	pageIndex?: number;
	pageSize?: number;
	total?: number;
	totalCount?: number;
	totalElements?: number;
	rows?: StudentListRow[];
	list?: StudentListRow[];
	records?: StudentListRow[];
	/** Spring Data 风格 */
	content?: StudentListRow[];
	data?: unknown;
}

type CourseTimesData = StudentCourseTimesSummaryDTO;

type CourseRow = StudentCourseRowDTO & {
	id: string | number;
	courseName: string;
	courseTimes: number;
	unitPrice: number;
	totalPrice: number;
	unitName: string;
};

const loading = ref(false);
const exporting = ref(false);
const pageIndex = ref(1);
const pageSize = ref(10);
const total = ref(0);
const tableRows = ref<StudentListRow[]>([]);
const selection = ref<StudentListRow[]>([]);
const latestRequestSeq = ref(0);

const query = reactive({
	keyword: "",
	branchSchool: "",
	gradeId: "",
	teacherName: "",
});

const hourVisible = ref(false);
const hourLoading = ref(false);
const hourData = ref<CourseTimesData | null>(null);
const refreshingId = ref<number | string | null>(null);
const router = useRouter();
const IconSearch = Search;
const IconClose = CircleClose;

const enrollVisible = ref(false);
const coursePickerVisible = ref(false);
const submittingEnroll = ref(false);
const enrollStudent = ref<StudentListRow | null>(null);
const selectedCourse = ref<CourseRow | null>(null);
const discountAmount = ref(0);

const courseLoading = ref(false);
const courseRows = ref<CourseRow[]>([]);
const coursePageIndex = ref(1);
const coursePageSize = ref(20);
const courseTotal = ref(0);
const courseKeyword = ref("");

const courseTotalAmount = ref(0);
const receiveAmount = ref(0);

function onSelectionChange(rows: StudentListRow[]) {
	selection.value = rows;
}

function tipBatch(name: string) {
	const n = selection.value.length;
	ElMessage.info(`${name} 需对接批量接口；当前已选 ${n} 条`);
}

/** Apifox 等 Mock 常用拉丁随机串填 message，避免用户把假文当成真实业务错误 */
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
			if (value !== undefined && value !== null && value !== "") {
				search.append(key, String(value));
			}
		});
		const qs = search.toString();
		if (qs) requestUrl += `?${qs}`;
	} else {
		headers["Content-Type"] = "application/json;charset=UTF-8";
		body = JSON.stringify(options.body || {});
	}

	const resp = await fetch(requestUrl, { method: options.method, headers, body });
	if (!resp.ok) {
		throw new Error(`请求失败（HTTP ${resp.status}）`);
	}

	const rawText = await resp.text();
	let json: { code?: number; message?: string; msg?: string; data?: T; success?: boolean };
	try {
		json = rawText ? (JSON.parse(rawText) as typeof json) : {};
	} catch {
		throw new Error(
			`响应不是合法 JSON（HTTP ${resp.status}）。网关/函数计算可能返回了错误页，请在「网络 → 响应」查看正文。`,
		);
	}
	if (!json || typeof json !== "object") {
		throw new Error("接口返回格式错误");
	}

	if (!("data" in json)) {
		throw new Error(userFacingApiMessage(json.message || json.msg, "接口缺少 data 字段"));
	}

	/** Apifox 等 Mock 常把 code 填成随机数（如 26），与 pages 混淆；约定成功码仍为 0 / 10000 / 200 */
	const c = json.code;
	const dataPayload = json.data;
	const hasPagedList =
		dataPayload != null &&
		typeof dataPayload === "object" &&
		!Array.isArray(dataPayload) &&
		["rows", "list", "records", "content"].some((k) =>
			Array.isArray((dataPayload as Record<string, unknown>)[k]),
		);

	/** 部分代理（如云函数）会在响应头写 Success: false，仍返回 HTTP 200。
	 * 若 data 中已经有列表，则按成功渲染，仅开发环境告警。 */
	const headerSuccess = resp.headers.get("success");
	if (headerSuccess === "false" || headerSuccess === "0") {
		if (!hasPagedList) {
			throw new Error(
				userFacingApiMessage(
					json.message || json.msg,
					"响应标头 Success: false，表示网关判定本次调用失败（业务未成功）。请查看响应体或 Apifox/Mock 配置。",
				),
			);
		}
		if (import.meta.env.DEV) {
			console.warn("[在学学员] 响应头 success=false，但 data 含列表，已按成功渲染。");
		}
	}
	/** 响应体里常见 success 字段。若 data 含列表，也继续渲染。 */
	if (json.success === false) {
		if (!hasPagedList) {
			throw new Error(userFacingApiMessage(json.message || json.msg, "接口返回 success: false"));
		}
		if (import.meta.env.DEV) {
			console.warn("[在学学员] 响应体 success=false，但 data 含列表，已按成功渲染。");
		}
	}

	if (c !== undefined && c !== null && Number(c) !== 0 && Number(c) !== 10000 && Number(c) !== 200) {
		if (hasPagedList) {
			if (import.meta.env.DEV) {
				console.warn(
					`[在学学员] 响应 body.code=${c} 非约定成功码，但 data 内存在分页列表字段，已按成功解析。请在 Apifox 成功示例中将 code 改为 0 或 10000。`,
				);
			}
		} else {
			throw new Error(userFacingApiMessage(json.message || json.msg, `业务错误 code=${json.code}`));
		}
	}
	return (json.data as T) ?? (null as T);
}

function toNumber(value: unknown, fallback = 0): number {
	const n = Number(value);
	return Number.isFinite(n) ? n : fallback;
}

function looksLikeRowItem(item: unknown): boolean {
	if (!item || typeof item !== "object" || Array.isArray(item)) return false;
	const o = item as Record<string, unknown>;
	return (
		"id" in o ||
		"name" in o ||
		"studentId" in o ||
		"studentName" in o ||
		"mobile" in o ||
		"studentNo" in o
	);
}

function pickRows(obj: Record<string, unknown>): StudentListRow[] {
	const candidates = [
		"rows",
		"list",
		"records",
		"content",
		"items",
		"dataList",
		"students",
		"studentList",
		"result",
		"pageData",
	];
	for (const key of candidates) {
		const v = obj[key];
		if (Array.isArray(v) && v.length > 0) return v as StudentListRow[];
		if (Array.isArray(v)) return v as StudentListRow[];
	}
	// Mock/自定义字段：取第一个「像表格行」的对象数组
	for (const v of Object.values(obj)) {
		if (!Array.isArray(v) || v.length === 0) continue;
		if (looksLikeRowItem(v[0])) return v as StudentListRow[];
	}
	return [];
}

function pickTotal(obj: Record<string, unknown>, rowsLen: number): number {
	const keys = ["total", "totalCount", "totalElements", "totalRow", "count"];
	for (const key of keys) {
		const v = obj[key];
		if (v !== undefined && v !== null && v !== "") {
			const n = Number(v);
			if (!Number.isNaN(n)) return n;
		}
	}
	return rowsLen;
}

function normalizeCourseRow(raw: Record<string, unknown>, idx: number): CourseRow {
	const courseTimes = toNumber(
		raw.courseTimes ?? raw.countLessonTotal ?? raw.lessons ?? raw.lessonCount ?? raw.count ?? raw.hours ?? raw.times,
		0,
	);
	const unitPrice = toNumber(raw.unitPrice ?? raw.price ?? raw.singlePrice ?? raw.classPrice ?? raw.feePerClass, 0);
	const totalPrice = toNumber(raw.totalPrice ?? raw.amount ?? raw.totalAmount ?? raw.feeTotal, unitPrice * courseTimes);
	return {
		id: (raw.id as string | number) ?? idx + 1,
		courseName: String(raw.courseName ?? raw.name ?? raw.title ?? raw.subjectName ?? "-"),
		courseTimes,
		unitPrice,
		totalPrice,
		unitName: String(raw.unitName ?? raw.unit ?? raw.lessonUnit ?? "次"),
	};
}

/**
 * 兼容多种分页 JSON：
 * - data 直接为数组
 * - rows / list / records / content（Spring Page）
 * - 再包一层 data: { rows: ... }
 */
function normalizePage(data: unknown): { rows: StudentListRow[]; total: number } {
	if (data == null) return { rows: [], total: 0 };
	if (Array.isArray(data)) {
		return { rows: data as StudentListRow[], total: data.length };
	}
	if (typeof data !== "object") return { rows: [], total: 0 };

	let obj = data as Record<string, unknown>;
	// 嵌套一层 { data: { rows, total } } 或 { data: [...] }
	if ("data" in obj && obj.data != null) {
		const inner = obj.data;
		if (Array.isArray(inner)) {
			return { rows: inner as StudentListRow[], total: inner.length };
		}
		if (typeof inner === "object") {
			const innerObj = inner as Record<string, unknown>;
			if (pickRows(innerObj).length > 0 || "total" in innerObj || "totalElements" in innerObj) {
				obj = innerObj;
			}
		}
	}

	const rows = pickRows(obj);
	const totalVal = pickTotal(obj, rows.length);
	return { rows, total: totalVal };
}

async function loadList() {
	const requestSeq = ++latestRequestSeq.value;
	loading.value = true;
	try {
		const gradeIdNum = query.gradeId.trim() === "" ? undefined : Number(query.gradeId);
		const params: Record<string, string | number | undefined> = {
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			stage: "STUDYING",
			keyword: query.keyword.trim() || undefined,
		};
		if (gradeIdNum !== undefined && !Number.isNaN(gradeIdNum)) {
			params.gradeId = gradeIdNum;
		}
		// 以下参数 openapi 未声明，若网关透传后端可识别
		if (query.branchSchool.trim()) params.branchSchool = query.branchSchool.trim();
		if (query.teacherName.trim()) params.teacherName = query.teacherName.trim();

		const data = await getStudentConsolePage(params);
		const { rows, total: t } = normalizePage(data);
		// 只让最后一次请求落地，避免并发请求导致“页面和Network选中项不一致”
		if (requestSeq !== latestRequestSeq.value) return;
		tableRows.value = rows;
		total.value = t;
		if (import.meta.env.DEV && rows.length === 0 && data != null) {
			console.warn(
				"[在学学员] 接口已返回但解析后列表为空。请对照 Network 里 Response 的 data 结构，或检查是否 data 为 null。原始 payload:",
				data,
			);
		}
	} catch (e: any) {
		if (requestSeq !== latestRequestSeq.value) return;
		ElMessage.error(e?.message || "加载在学学员失败");
		tableRows.value = [];
		total.value = 0;
	} finally {
		if (requestSeq === latestRequestSeq.value) {
			loading.value = false;
		}
	}
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

function downloadBlobFile(filename: string, blob: Blob) {
	const url = URL.createObjectURL(blob);
	const a = document.createElement("a");
	a.href = url;
	a.download = filename;
	a.click();
	URL.revokeObjectURL(url);
}

/** 导出在学学员（二进制流） */
async function handleExport() {
	exporting.value = true;
	try {
		const blob = await exportOnlineStudentsFile();
		downloadBlobFile(`在学学员导出_${Date.now()}.xlsx`, blob);
		ElMessage.success("已开始下载");
	} catch (e: any) {
		ElMessage.error(e?.message || "导出失败");
	} finally {
		exporting.value = false;
	}
}

async function openDetail(row: StudentListRow) {
	if (row.id == null) {
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

async function fetchCourseTimes(row: StudentListRow): Promise<CourseTimesData | null> {
	if (row.id == null) return null;
	return getStudentCourseTimesSummary(String(row.id));
}

async function openCourseTimes(row: StudentListRow) {
	hourVisible.value = true;
	hourLoading.value = true;
	hourData.value = null;
	try {
		hourData.value = await fetchCourseTimes(row);
	} catch (e: any) {
		ElMessage.error(e?.message || "加载课时信息失败");
		hourVisible.value = false;
	} finally {
		hourLoading.value = false;
	}
}

async function refreshCourseTimes(row: StudentListRow) {
	refreshingId.value = row.id ?? null;
	try {
		await loadList();
		ElMessage.success("列表已刷新");
	} catch {
		/* loadList 已提示 */
	} finally {
		refreshingId.value = null;
	}
}

function openEnroll(row: StudentListRow) {
	enrollStudent.value = row;
	enrollVisible.value = true;
	selectedCourse.value = null;
	discountAmount.value = 0;
	courseTotalAmount.value = 0;
	receiveAmount.value = 0;
}

function chooseCourse(row: CourseRow) {
	selectedCourse.value = row;
	courseTotalAmount.value = toNumber(row.totalPrice, 0);
	receiveAmount.value = Math.max(0, courseTotalAmount.value - discountAmount.value);
	coursePickerVisible.value = false;
}

async function loadCourseList() {
	courseLoading.value = true;
	try {
		const data = await getStudentCoursePage({
			pageIndex: coursePageIndex.value,
			pageSize: coursePageSize.value,
			name: courseKeyword.value.trim() || undefined,
		});
		const { rows, total } = normalizePage(data);
		courseRows.value = rows.map((item, idx) => normalizeCourseRow(item as Record<string, unknown>, idx));
		courseTotal.value = total;
	} catch (e: any) {
		ElMessage.error(e?.message || "加载课程列表失败");
		courseRows.value = [];
		courseTotal.value = 0;
	} finally {
		courseLoading.value = false;
	}
}

function handleCourseSearch() {
	coursePageIndex.value = 1;
	loadCourseList();
}

function resetCourseSearch() {
	courseKeyword.value = "";
	coursePageIndex.value = 1;
	loadCourseList();
}

function onCoursePageSizeChange() {
	coursePageIndex.value = 1;
	loadCourseList();
}

async function submitEnroll() {
	if (!enrollStudent.value?.id) {
		ElMessage.warning("缺少学员信息");
		return;
	}
	if (!selectedCourse.value) {
		ElMessage.warning("请先选择课程");
		return;
	}
	submittingEnroll.value = true;
	try {
		await addStudentEnroll({
			studentId: enrollStudent.value.id,
			courseId: selectedCourse.value.id,
			countLessonTotal: selectedCourse.value.courseTimes,
			amount: courseTotalAmount.value,
			paidAmount: receiveAmount.value,
			remark: `优惠金额：${discountAmount.value}`,
		});
		ElMessage.success("报名提交成功");
		enrollVisible.value = false;
	} catch (e: any) {
		ElMessage.error(e?.message || "报名提交失败");
	} finally {
		submittingEnroll.value = false;
	}
}

onMounted(() => {
	loadList();
});
</script>

<style scoped>
.online-students-page {
	padding: 10px 12px;
	display: flex;
	flex-direction: column;
	gap: 8px;
}

.filter-panel,
.toolbar-panel,
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
	min-width: 44px;
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
	padding-top: 6px;
	padding-bottom: 6px;
	display: flex;
	justify-content: space-between;
	gap: 8px;
}

.toolbar-left {
	display: flex;
	flex-wrap: wrap;
	gap: 6px;
	align-items: center;
}

.toolbar-right {
	display: flex;
	gap: 6px;
	align-items: center;
}

.compact-actions :deep(.el-button) {
	height: 26px;
	padding: 0 10px;
}

.compact-actions :deep(.el-button.is-circle) {
	width: 26px;
	padding: 0;
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

.hour-refresh {
	padding: 0 2px;
	margin-left: 2px;
	vertical-align: middle;
}

.enroll-form {
	display: flex;
	flex-direction: column;
	gap: 14px;
}

.enroll-row {
	display: grid;
	grid-template-columns: 90px 1fr;
	align-items: center;
	gap: 10px;
}

.row-label {
	color: #606266;
}

.row-label.required::before {
	content: "* ";
	color: #f56c6c;
}

.row-value {
	font-size: 26px;
	font-weight: 600;
	color: #303133;
}

.money-row {
	display: flex;
	align-items: center;
	gap: 24px;
	font-size: 30px;
	line-height: 1.2;
	color: #606266;
}

.money-row strong {
	font-size: 36px;
	color: #303133;
}

.notice-row {
	background: #f5f7fa;
	color: #909399;
	padding: 14px 18px;
	border-radius: 6px;
}

.picker-filter {
	display: flex;
	align-items: center;
	gap: 12px;
	margin-bottom: 12px;
}

@media (max-width: 960px) {
	.filter-panel {
		flex-direction: column;
	}

	.filter-grid {
		grid-template-columns: 1fr;
	}

	.toolbar-panel {
		flex-direction: column;
		align-items: stretch;
	}

	.toolbar-right {
		justify-content: flex-end;
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
