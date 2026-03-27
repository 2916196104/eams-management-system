<template>
	<section class="student-detail-page">
		<section class="left-panel">
			<div class="avatar-wrap">
				<el-avatar :size="88" :src="String(detailData.avatar || '')">
					{{ String(detailData.name || route.query.name || "学员").slice(0, 1) }}
				</el-avatar>
				<div class="name">{{ detailData.name || route.query.name || "-" }}</div>
				<div class="phone">{{ detailData.mobile || route.query.phone || "-" }}</div>
			</div>

			<el-divider>个人信息</el-divider>
			<el-descriptions :column="1" size="small">
				<el-descriptions-item label="性别">{{ detailData.gender || "-" }}</el-descriptions-item>
				<el-descriptions-item label="年龄">{{ detailData.age ?? "-" }}</el-descriptions-item>
				<el-descriptions-item label="年级">{{ detailData.gradeName || "-" }}</el-descriptions-item>
				<el-descriptions-item label="分校">{{ detailData.schoolName || "-" }}</el-descriptions-item>
				<el-descriptions-item label="顾问">{{ detailData.counselorName || "-" }}</el-descriptions-item>
				<el-descriptions-item label="家长">{{ detailData.parentName || "-" }}</el-descriptions-item>
				<el-descriptions-item label="备注">{{ detailData.remark || "-" }}</el-descriptions-item>
			</el-descriptions>
		</section>

		<section class="right-panel">
			<el-tabs v-model="activeTab">
				<el-tab-pane label="报名记录" name="enroll">
					<el-table v-loading="enrollLoading" :data="enrollRows" stripe border>
						<el-table-column prop="addTime" label="报名时间" min-width="160" />
						<el-table-column prop="courseName" label="课程" min-width="140" />
						<el-table-column prop="subjectName" label="科目" min-width="110" />
						<el-table-column prop="amount" label="报名金额" min-width="90" />
						<el-table-column prop="countLessonTotal" label="课时数" min-width="80" />
						<el-table-column prop="stateName" label="状态" min-width="90" />
					</el-table>
					<div class="pager-wrap">
						<el-pagination
							v-model:current-page="enrollPageIndex"
							v-model:page-size="enrollPageSize"
							background
							layout="total, sizes, prev, pager, next"
							:page-sizes="[10, 20, 50]"
							:total="enrollTotal"
							@current-change="loadEnrollRecords"
							@size-change="onEnrollPageSizeChange"
						/>
					</div>
				</el-tab-pane>

				<el-tab-pane label="课时统计" name="hours">
					<el-descriptions :column="2" border>
						<el-descriptions-item label="学员ID">{{ courseData.studentId || route.query.id || "-" }}</el-descriptions-item>
						<el-descriptions-item label="学员姓名">{{ courseData.studentName || detailData.name || "-" }}</el-descriptions-item>
						<el-descriptions-item label="课程总次数">{{ courseData.courseTimes ?? "-" }}</el-descriptions-item>
						<el-descriptions-item label="剩余次数">{{ courseData.remainingTimes ?? "-" }}</el-descriptions-item>
					</el-descriptions>
				</el-tab-pane>
			</el-tabs>
		</section>
	</section>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref } from "vue";
import { useRoute } from "vue-router";
import { ElMessage } from "element-plus";

interface StudentDetailData extends Record<string, unknown> {
	id?: number | string;
	name?: string;
	mobile?: string;
	avatar?: string;
	gender?: string;
	age?: number;
	gradeName?: string;
	schoolName?: string;
	counselorName?: string;
	parentName?: string;
	remark?: string;
}

interface CourseTimesData {
	studentId?: string;
	studentName?: string;
	courseTimes?: number;
	remainingTimes?: number;
}

interface EnrollRecord {
	id?: number | string;
	addTime?: string;
	courseName?: string;
	subjectName?: string;
	amount?: number;
	countLessonTotal?: number;
	stateName?: string;
}

const route = useRoute();
const activeTab = ref("enroll");
const detailData = reactive<StudentDetailData>({});
const courseData = reactive<CourseTimesData>({});

const enrollLoading = ref(false);
const enrollRows = ref<EnrollRecord[]>([]);
const enrollPageIndex = ref(1);
const enrollPageSize = ref(10);
const enrollTotal = ref(0);

async function requestApiRaw<T = unknown>(
	url: string,
	options: { method: "GET" | "POST"; params?: Record<string, string | number | undefined>; body?: Record<string, unknown> },
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
	const json = (await resp.json()) as { code?: number; data?: T; message?: string; msg?: string };
	if (!json || typeof json !== "object" || !("data" in json)) throw new Error("接口返回格式错误");
	return (json.data as T) ?? (null as T);
}

function normalizePage(data: unknown): { rows: EnrollRecord[]; total: number } {
	if (!data || typeof data !== "object") return { rows: [], total: 0 };
	const obj = data as Record<string, unknown>;
	const rows = (obj.rows || obj.list || obj.records || obj.content || []) as EnrollRecord[];
	const total = Number(obj.total || obj.totalCount || obj.totalElements || rows.length) || 0;
	return { rows, total };
}

async function loadDetail() {
	const studentId = route.query.id ? Number(route.query.id) : undefined;
	if (!studentId) return;
	try {
		const data = await requestApiRaw<StudentDetailData>("/stu/common/stuInformation/get-studentDetail", {
			method: "GET",
			params: { id: studentId },
		});
		Object.assign(detailData, data || {});
	} catch (e: any) {
		ElMessage.warning(e?.message || "加载学员详情失败");
	}
}

async function loadCourseTimes() {
	const studentId = route.query.id ? String(route.query.id) : "";
	if (!studentId) return;
	try {
		const data = await requestApiRaw<CourseTimesData>("/j4/student/student/query-course-times", {
			method: "GET",
			params: { studentId },
		});
		Object.assign(courseData, data || {});
	} catch {
		/* 课时摘要非必需，不阻断页面 */
	}
}

async function loadEnrollRecords() {
	enrollLoading.value = true;
	try {
		const data = await requestApiRaw<unknown>("/j4/student/enroll/list", {
			method: "GET",
			params: {
				pageIndex: enrollPageIndex.value,
				pageSize: enrollPageSize.value,
				studentName: String(route.query.name || detailData.name || ""),
			},
		});
		const { rows, total } = normalizePage(data);
		enrollRows.value = rows;
		enrollTotal.value = total;
	} catch (e: any) {
		ElMessage.warning(e?.message || "加载报名记录失败");
		enrollRows.value = [];
		enrollTotal.value = 0;
	} finally {
		enrollLoading.value = false;
	}
}

function onEnrollPageSizeChange() {
	enrollPageIndex.value = 1;
	loadEnrollRecords();
}

onMounted(async () => {
	await loadDetail();
	await Promise.all([loadCourseTimes(), loadEnrollRecords()]);
});
</script>

<style scoped>
.student-detail-page {
	display: grid;
	grid-template-columns: 300px 1fr;
	gap: 12px;
	padding: 12px;
}

.left-panel,
.right-panel {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
}

.avatar-wrap {
	display: flex;
	flex-direction: column;
	align-items: center;
	gap: 8px;
}

.name {
	font-size: 18px;
	font-weight: 600;
}

.phone {
	color: #909399;
}

.pager-wrap {
	margin-top: 12px;
	display: flex;
	justify-content: flex-end;
}
</style>
