<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { withTeacherBackQuery } from "@/utils/teacherNavigation";
import { Apis } from "@/api";
import { useUserStore } from "@/store/userStore";
import { computed, ref } from "vue";
import { useRouter, useRoute } from "vue-router";
import { storeToRefs } from "pinia";
import { onShow } from "@dcloudio/uni-app";

definePage({
	name: "teacherAttendanceRecord",
	style: {
		navigationBarTitleText: "点名记录",
		titleNView: false,
	},
});

type AttendanceStatusKey = "signed" | "makeup" | "absent" | "leave" | "change" | "pending";
type AttendanceActionKey = Exclude<AttendanceStatusKey, "change" | "pending">;

interface AttendanceDetail {
	lessonId: number;
	lessonDate: string;
	startTime: string;
	endTime: string;
	periodCount: number;
	courseTitle: string;
	teacherName: string;
	normalCount: number;
	leaveCount: number;
	absentCount: number;
	makeupCount: number;
	canCommentAfterClass: boolean;
	canAddStudent: boolean;
}

interface AttendanceStudentItem {
	id: string;
	studentId: number;
	studentName: string;
	statusKey: AttendanceStatusKey;
}

interface AttendanceStatusOption {
	key: AttendanceActionKey;
	label: string;
	type: number;
	state: number;
	defaultCountMode: "period" | "zero";
}

interface RollCallRecordItem {
	id: string;
	studentName: string;
	checkinDate: string;
	checkinResult?: number;
}

interface RollCallCourseOption {
	id: string;
	name: string;
}

const statusOptions: AttendanceStatusOption[] = [
	{ key: "signed", label: "已签到", type: 1, state: 1, defaultCountMode: "period" },
	{ key: "makeup", label: "补签", type: 2, state: 2, defaultCountMode: "period" },
	{ key: "absent", label: "旷课", type: 3, state: 3, defaultCountMode: "period" },
	{ key: "leave", label: "请假", type: 4, state: 4, defaultCountMode: "zero" },
];

const router = useRouter();
const route = useRoute() as { query?: Record<string, string | string[] | undefined> };
const userStore = useUserStore();
const { getScheduleByDate, teacherInfo } = storeToRefs(userStore);

const today = formatDate(new Date());
const loading = ref(false);
const studentLoading = ref(false);
const studentLoadingMore = ref(false);
const statusSubmitting = ref(false);
const statusPopupVisible = ref(false);
const selectedLessonId = ref<number | undefined>(undefined);
const activeDate = ref(readQueryString("date") || today);
const attendanceDetail = ref<AttendanceDetail | null>(null);
const studentList = ref<AttendanceStudentItem[]>([]);
const currentStudent = ref<AttendanceStudentItem | null>(null);
const studentPageIndex = ref(1);
const studentTotalPage = ref(0);
const studentTotal = ref(0);
const unsignedCount = ref(0);
const studentPageSize = 10;
const rollCallLoading = ref(false);
const rollCallLoadingMore = ref(false);
const rollCallPageIndex = ref(1);
const rollCallPages = ref(0);
const rollCallTotal = ref(0);
const selectedCourseId = ref(readQueryString("course_id") || "");
const rollCallList = ref<RollCallRecordItem[]>([]);

const statusForm = reactive({
	statusKey: "signed" as AttendanceActionKey,
	countText: "1",
});

const routeLessonId = computed(() => {
	const value = Number(readQueryString("lesson_id") || 0);
	return Number.isFinite(value) && value > 0 ? value : undefined;
});
const isLessonMode = computed(() => Boolean(routeLessonId.value));
const dateLessons = computed(() => getScheduleByDate.value(activeDate.value).filter((item) => item.lessonId));
const rollCallCourseOptions = computed<RollCallCourseOption[]>(() => {
	const map = new Map<string, RollCallCourseOption>();
	for (const item of getScheduleByDate.value(activeDate.value)) {
		const courseId = item.courseId ? String(item.courseId) : "";
		if (!courseId || map.has(courseId)) continue;
		map.set(courseId, {
			id: courseId,
			name: item.courseName || item.className || "未命名课程",
		});
	}
	return Array.from(map.values());
});
const currentLesson = computed(() => {
	return dateLessons.value.find((item) => resolveLessonId(item) === selectedLessonId.value);
});
const hasMoreStudents = computed(() => studentPageIndex.value < studentTotalPage.value);
const hasMoreRollCalls = computed(() => rollCallPageIndex.value < rollCallPages.value);

function formatDate(date: Date) {
	const year = date.getFullYear();
	const month = String(date.getMonth() + 1).padStart(2, "0");
	const day = String(date.getDate()).padStart(2, "0");
	return `${year}-${month}-${day}`;
}

function readQueryString(key: string) {
	const value = route.query?.[key];
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

function resolveLessonId(item: { lessonId?: number | string; id?: number | string }) {
	const raw = item.lessonId ?? item.id;
	const value = Number(raw || 0);
	return Number.isFinite(value) && value > 0 ? value : undefined;
}

function getStatusOption(key: AttendanceActionKey) {
	return statusOptions.find((item) => item.key === key) || statusOptions[0];
}

function inferStatusKey(item: any): AttendanceStatusKey {
	const state = Number(item.state ?? item.study_state ?? item.sign_state ?? 0);
	if (state === 2) return "makeup";
	if (state === 3) return "absent";
	if (state === 4) return "leave";
	if (state === 1) return "signed";
	if (Boolean(item.is_makeup ?? item.isMakeup)) return "makeup";
	if (Boolean(item.is_signed ?? item.isSigned)) return "signed";
	if (Boolean(item.is_leave ?? item.isLeave)) return "leave";
	if (Boolean(item.is_absent ?? item.isAbsent)) return "absent";
	if (Boolean(item.is_change_course ?? item.isChangeCourse)) return "change";
	return "pending";
}

function normalizeAttendanceDetailPayload(source: any): AttendanceDetail | null {
	const payload = source?.data?.data ?? source?.data ?? source;
	if (!payload || Array.isArray(payload)) return null;

	const lessonId = Number(payload.lesson_id ?? payload.lessonId ?? 0);

	return {
		lessonId: Number.isFinite(lessonId) ? lessonId : 0,
		lessonDate: payload.lesson_date ?? payload.lessonDate ?? activeDate.value,
		startTime: payload.start_time ?? payload.startTime ?? "--:--",
		endTime: payload.end_time ?? payload.endTime ?? "--:--",
		periodCount: Number(payload.period_count ?? payload.periodCount ?? 0),
		courseTitle: payload.course_title ?? payload.courseTitle ?? "未命名课次",
		teacherName: payload.teacher_name ?? payload.teacherName ?? "未设置老师",
		normalCount: Number(payload.normal_count ?? payload.normalCount ?? 0),
		leaveCount: Number(payload.leave_count ?? payload.leaveCount ?? 0),
		absentCount: Number(payload.absent_count ?? payload.absentCount ?? 0),
		makeupCount: Number(payload.makeup_count ?? payload.makeupCount ?? 0),
		canCommentAfterClass: Boolean(payload.can_comment_after_class ?? payload.canCommentAfterClass),
		canAddStudent: Boolean(payload.can_add_student ?? payload.canAddStudent),
	};
}

function normalizeStudentListPayload(source: any) {
	const payload = source?.data?.data ?? source?.data ?? source ?? {};
	const rawRows = Array.isArray(payload)
		? payload
		: Array.isArray(payload.rows)
			? payload.rows
			: Array.isArray(payload.list)
				? payload.list
				: Array.isArray(payload.records)
					? payload.records
					: typeof payload.student_id !== "undefined"
						? [payload]
						: [];

	const rows = rawRows.map((item: any, index: number) => {
		const studentId = Number(item.student_id ?? item.studentId ?? item.id ?? 0);
		return {
			id: String(item.id ?? item.student_id ?? item.studentId ?? `${studentId}-${index}`),
			studentId: Number.isFinite(studentId) ? studentId : 0,
			studentName: item.student_name ?? item.studentName ?? item.name ?? `学员${studentId || index + 1}`,
			statusKey: inferStatusKey(item),
		} satisfies AttendanceStudentItem;
	});

	return {
		rows,
		pageIndex: Number(payload.page_index ?? payload.pageIndex ?? 1),
		total: Number(payload.total ?? rows.length),
		totalPage: Number(payload.total_page ?? payload.totalPage ?? 1),
		unsignedCount: Number(payload.unsigned_count ?? payload.unsignedCount ?? 0),
	};
}

function normalizeRollCallPayload(source: any) {
	const payload = source?.data ?? source ?? {};
	const rawRows = Array.isArray(payload.rows)
		? payload.rows
		: Array.isArray(payload.list)
			? payload.list
			: Array.isArray(payload.records)
				? payload.records
				: Array.isArray(payload)
					? payload
					: [];

	return {
		pageIndex: Number(payload.pageIndex ?? payload.page ?? 1),
		pages: Number(payload.pages ?? payload.total_page ?? 0),
		total: Number(payload.total ?? rawRows.length),
		rows: rawRows.map((item: any, index: number) => ({
			id: String(item.id ?? `${item.studentName ?? item.student_name ?? "student"}-${index}`),
			studentName: item.studentName ?? item.student_name ?? "--",
			checkinDate: item.date ?? item.checkinDate ?? item.checkin_date ?? "--",
			checkinResult: item.state === "已签到" ? 1 : item.state === "补签" ? 2 : item.state === "旷课" ? 3 : item.state === "请假" ? 4 : undefined,
		} satisfies RollCallRecordItem)),
	};
}

function resetStudentList() {
	studentList.value = [];
	studentPageIndex.value = 1;
	studentTotal.value = 0;
	studentTotalPage.value = 0;
	unsignedCount.value = 0;
}

function resetRollCallList() {
	rollCallList.value = [];
	rollCallPageIndex.value = 1;
	rollCallPages.value = 0;
	rollCallTotal.value = 0;
}

function syncCountByStatus(key: AttendanceActionKey) {
	const option = getStatusOption(key);
	statusForm.countText = option.defaultCountMode === "zero" ? "0" : String(Math.max(attendanceDetail.value?.periodCount || 1, 1));
}

function studentStatusText(item: AttendanceStudentItem) {
	switch (item.statusKey) {
		case "signed":
			return "已签到";
		case "makeup":
			return "补签";
		case "leave":
			return "请假";
		case "absent":
			return "旷课";
		case "change":
			return "调课";
		default:
			return "未签到";
	}
}

function studentStatusClass(item: AttendanceStudentItem) {
	switch (item.statusKey) {
		case "signed":
			return "teacher-attendance-student__status--signed";
		case "makeup":
			return "teacher-attendance-student__status--makeup";
		case "leave":
			return "teacher-attendance-student__status--leave";
		case "absent":
			return "teacher-attendance-student__status--absent";
		case "change":
			return "teacher-attendance-student__status--change";
		default:
			return "teacher-attendance-student__status--pending";
	}
}

function rollCallResultText(result?: number) {
	switch (result) {
		case 1:
			return "已签到";
		case 2:
			return "补签";
		case 3:
			return "旷课";
		case 4:
			return "请假";
		default:
			return "未知状态";
	}
}

function rollCallResultClass(result?: number) {
	switch (result) {
		case 1:
			return "teacher-rollcall-item__status--signed";
		case 2:
			return "teacher-rollcall-item__status--makeup";
		case 3:
			return "teacher-rollcall-item__status--absent";
		case 4:
			return "teacher-rollcall-item__status--leave";
		default:
			return "teacher-rollcall-item__status--unknown";
	}
}

async function loadDateLessons() {
	if (dateLessons.value.length) return;
	// 移除ensureTeacherInfo调用，避免因为用户信息加载失败导致课程加载失败
	// await Promise.all([userStore.loadScheduleByDate(activeDate.value), ensureTeacherInfo()]);
	await userStore.loadScheduleByDate(activeDate.value);
}

async function ensureTeacherInfo() {
	if (teacherInfo.value.id) return;
	await userStore.loadCurrentUserInfo();
}

async function loadStudentList(nextPage = 1, append = false, lessonId = selectedLessonId.value) {
	if (!lessonId) {
		resetStudentList();
		return;
	}

	const targetLoading = append ? studentLoadingMore : studentLoading;
	targetLoading.value = true;

	try {
		const res: any = await (Apis as any).course.get_course_record_name_get_cs_stu_list({
			params: {
				page_index: nextPage,
				page_size: studentPageSize,
				lesson_id: lessonId,
			},
		});

		const payload = normalizeStudentListPayload(res);
		studentPageIndex.value = payload.pageIndex;
		studentTotal.value = payload.total;
		studentTotalPage.value = payload.totalPage;
		unsignedCount.value = payload.unsignedCount;
		studentList.value = append ? [...studentList.value, ...payload.rows] : payload.rows;
	} catch {
		if (!append) resetStudentList();
		uni.showToast({ title: "学员列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function loadLessonDetail(lessonId?: number) {
	if (!lessonId) {
		selectedLessonId.value = undefined;
		attendanceDetail.value = null;
		resetStudentList();
		return;
	}

	loading.value = true;
	selectedLessonId.value = lessonId;
	try {
		const res: any = await (Apis as any).course.get_course_record_name_get_detail_cs({
			params: {
				lesson_id: lessonId,
			},
		});
		attendanceDetail.value = normalizeAttendanceDetailPayload(res);
		await loadStudentList(1, false, lessonId);
	} catch {
		attendanceDetail.value = null;
		resetStudentList();
		uni.showToast({ title: "课次详情加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

async function loadRollCallRecords(nextPage = 1, append = false) {
	// 移除ensureTeacherInfo调用，避免因为用户信息加载失败导致点名记录加载失败
	// await ensureTeacherInfo();

	const targetLoading = append ? rollCallLoadingMore : rollCallLoading;
	targetLoading.value = true;

	try {
		const res: any = await (Apis as any).workbench.get_workbench_sign({
			params: {
				pageIndex: nextPage,
				pageSize: studentPageSize,
			},
		});

		const payload = normalizeRollCallPayload(res);
		rollCallPageIndex.value = payload.pageIndex;
		rollCallPages.value = payload.pages;
		rollCallTotal.value = payload.total;
		rollCallList.value = append ? [...rollCallList.value, ...payload.rows] : payload.rows;
	} catch (error) {
		console.error("点名记录加载失败:", error);
		if (!append) resetRollCallList();
		uni.showToast({ title: "点名记录加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

function selectCourse(courseId: string) {
	selectedCourseId.value = courseId;
	void loadRollCallRecords(1, false);
}

async function initPage() {
	activeDate.value = readQueryString("date") || today;
	// 移除ensureTeacherInfo调用，避免因为用户信息加载失败导致页面初始化失败
	// await Promise.all([loadDateLessons(), ensureTeacherInfo()]);
	await loadDateLessons();

	if (isLessonMode.value) {
		await loadLessonDetail(routeLessonId.value);
		return;
	}

	selectedLessonId.value = undefined;
	attendanceDetail.value = null;
	resetStudentList();
	await loadRollCallRecords(1, false);
}

async function refreshPage() {
	await userStore.loadScheduleByDate(activeDate.value);
	await initPage();
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMoreStudents() {
	if (!hasMoreStudents.value || studentLoadingMore.value) return;
	await loadStudentList(studentPageIndex.value + 1, true);
}

async function loadMoreRollCalls() {
	if (!hasMoreRollCalls.value || rollCallLoadingMore.value) return;
	await loadRollCallRecords(rollCallPageIndex.value + 1, true);
}

function openStatusPopup(item: AttendanceStudentItem) {
	currentStudent.value = item;
	statusForm.statusKey = item.statusKey === "pending" || item.statusKey === "change" ? "signed" : (item.statusKey as AttendanceActionKey);
	syncCountByStatus(statusForm.statusKey);
	statusPopupVisible.value = true;
}

function closeStatusPopup() {
	statusPopupVisible.value = false;
	currentStudent.value = null;
}

async function submitStatusChange() {
	if (!currentStudent.value) return;

	const count = Math.max(Number(statusForm.countText || 0), 0);
	const option = getStatusOption(statusForm.statusKey);

	statusSubmitting.value = true;
	try {
		const res: any = await (Apis as any).course.put_course_record_name_set_status({
			data: {
				id: currentStudent.value.id,
				count,
				type: option.type,
				state: option.state,
			},
		});

		const resp = res?.data?.data ?? res?.data ?? {};
		if (typeof resp.resp_code !== "undefined" && Number(resp.resp_code) !== 0) {
			uni.showToast({ title: resp.resp_message || "设置状态失败", icon: "none" });
			return;
		}

		uni.showToast({ title: "状态设置成功", icon: "none" });
		closeStatusPopup();
		await loadLessonDetail(selectedLessonId.value);
	} catch {
		uni.showToast({ title: "状态设置失败", icon: "none" });
	} finally {
		statusSubmitting.value = false;
	}
}

function openCommentPage() {
	router.push({
		name: "teacherCommentRecord",
		query: withTeacherBackQuery(route),
	} as any);
}

function openAddStudentPage() {
	router.push({
		name: "teacherAddStudent",
		query: withTeacherBackQuery(route, {
			mode: "select",
			lesson_id: selectedLessonId.value ? String(selectedLessonId.value) : "",
			course_id: currentLesson.value?.courseId ? String(currentLesson.value.courseId) : "",
			date: activeDate.value,
		}),
	} as any);
}

onShow(() => {
	void initPage();
});
</script>

<template>
	<view class="teacher-attendance-page">
		<teacher-nav-bar title="点名记录" @refresh="refreshPage" />

		<view class="teacher-attendance-page__content">
			<template v-if="!isLessonMode">
				<view v-if="rollCallList.length" class="teacher-rollcall">
					<view class="teacher-rollcall__summary">共 {{ rollCallTotal }} 条点名记录</view>

					<view class="teacher-rollcall__list">
						<view v-for="item in rollCallList" :key="item.id" class="teacher-rollcall-item">
							<view class="teacher-rollcall-item__header">
								<view class="teacher-rollcall-item__student">{{ item.studentName }}</view>
								<view class="teacher-rollcall-item__status" :class="rollCallResultClass(item.checkinResult)">
									{{ rollCallResultText(item.checkinResult) }}
								</view>
							</view>
							<view class="teacher-rollcall-item__time">签到时间：{{ item.checkinDate }}</view>
						</view>
					</view>

					<view v-if="hasMoreRollCalls" class="teacher-attendance-student__more" @click="loadMoreRollCalls">
						{{ rollCallLoadingMore ? "加载中..." : "加载更多记录" }}
					</view>
				</view>

				<teacher-empty-state
					v-else
					:title="rollCallLoading ? '加载中...' : '暂无点名记录'"
					:description="'暂无点名记录'"
					compact
				/>
			</template>

			<template v-else>
			<!-- 同日课次切换 -->
			<view v-if="dateLessons.length" class="teacher-attendance-page__lesson-strip">
				<view
					v-for="lesson in dateLessons"
					:key="lesson.id"
					class="teacher-attendance-page__lesson-chip"
					:class="{ 'teacher-attendance-page__lesson-chip--active': selectedLessonId === resolveLessonId(lesson) }"
					@click="loadLessonDetail(resolveLessonId(lesson))"
				>
					{{ lesson.startTime }} {{ lesson.courseName }}
				</view>
			</view>

			<!-- 课次详情卡片 -->
			<view v-if="attendanceDetail" class="teacher-attendance-card">
				<view class="teacher-attendance-card__hero">
					<view class="teacher-attendance-card__title">{{ attendanceDetail.courseTitle }}</view>
					<view class="teacher-attendance-card__meta">
						{{ attendanceDetail.lessonDate }} {{ attendanceDetail.startTime }}-{{ attendanceDetail.endTime }}
					</view>
				</view>

				<view class="teacher-attendance-card__summary">
					<view class="teacher-attendance-card__summary-item">
						<text class="teacher-attendance-card__summary-label">授课老师</text>
						<text class="teacher-attendance-card__summary-value">{{ attendanceDetail.teacherName }}</text>
					</view>
					<view class="teacher-attendance-card__summary-item">
						<text class="teacher-attendance-card__summary-label">课时数</text>
						<text class="teacher-attendance-card__summary-value">{{ attendanceDetail.periodCount }}</text>
					</view>
				</view>

				<view class="teacher-attendance-card__stats">
					<view class="teacher-attendance-card__stat">
						<text class="teacher-attendance-card__stat-value">{{ attendanceDetail.normalCount }}</text>
						<text class="teacher-attendance-card__stat-label">正常</text>
					</view>
					<view class="teacher-attendance-card__stat">
						<text class="teacher-attendance-card__stat-value">{{ attendanceDetail.leaveCount }}</text>
						<text class="teacher-attendance-card__stat-label">请假</text>
					</view>
					<view class="teacher-attendance-card__stat">
						<text class="teacher-attendance-card__stat-value">{{ attendanceDetail.absentCount }}</text>
						<text class="teacher-attendance-card__stat-label">旷课</text>
					</view>
					<view class="teacher-attendance-card__stat">
						<text class="teacher-attendance-card__stat-value">{{ attendanceDetail.makeupCount }}</text>
						<text class="teacher-attendance-card__stat-label">补签</text>
					</view>
				</view>

				<view class="teacher-attendance-card__actions">
					<wd-button v-if="attendanceDetail.canCommentAfterClass" plain @click="openCommentPage">课后点评</wd-button>
					<wd-button v-if="attendanceDetail.canAddStudent" type="primary" @click="openAddStudentPage">添加学员</wd-button>
				</view>
			</view>

			<!-- 学员点名列表 -->
			<view v-if="attendanceDetail" class="teacher-attendance-student">
				<view class="teacher-attendance-student__header">
					<view>
						<view class="teacher-attendance-student__title">课次学员</view>
						<view class="teacher-attendance-student__subtitle">共 {{ studentTotal }} 人，未签到 {{ unsignedCount }} 人</view>
					</view>
				</view>

				<view v-if="studentList.length" class="teacher-attendance-student__list">
					<view v-for="item in studentList" :key="item.id" class="teacher-attendance-student__item">
						<view class="teacher-attendance-student__main">
							<view>
								<view class="teacher-attendance-student__name">{{ item.studentName }}</view>
								<view class="teacher-attendance-student__id">学员ID：{{ item.studentId || "--" }}</view>
							</view>
							<view class="teacher-attendance-student__status" :class="studentStatusClass(item)">
								{{ studentStatusText(item) }}
							</view>
						</view>

						<view class="teacher-attendance-student__actions">
							<wd-button size="small" plain @click="openStatusPopup(item)">设置状态</wd-button>
						</view>
					</view>
				</view>

				<teacher-empty-state v-else :title="studentLoading ? '加载中...' : '暂无学员记录'" compact />

				<view v-if="hasMoreStudents" class="teacher-attendance-student__more" @click="loadMoreStudents">
					{{ studentLoadingMore ? "加载中..." : "加载更多学员" }}
				</view>
			</view>

			<teacher-empty-state
				v-else
				:title="loading ? '加载中...' : dateLessons.length ? '暂无课次详情' : '暂无点名记录'"
				:description="dateLessons.length ? '可从上方切换课次查看详情' : '请先从课表选择课次进入本页'"
				compact
			/>
			</template>
		</view>

		<wd-popup v-model="statusPopupVisible" position="bottom" custom-class="teacher-status-popup">
			<view class="teacher-status-popup__body">
				<view class="teacher-status-popup__title">设置上课状态</view>
				<view class="teacher-status-popup__subtitle">
					{{ currentStudent?.studentName || "当前学员" }}
				</view>

				<view class="teacher-status-popup__group">
					<text class="teacher-status-popup__label">状态选择</text>
					<view class="teacher-status-popup__options">
						<view
							v-for="option in statusOptions"
							:key="option.key"
							class="teacher-status-popup__option"
							:class="{ 'teacher-status-popup__option--active': statusForm.statusKey === option.key }"
							@click="
								statusForm.statusKey = option.key;
								syncCountByStatus(option.key);
							"
						>
							{{ option.label }}
						</view>
					</view>
				</view>

				<view class="teacher-status-popup__group">
					<text class="teacher-status-popup__label">实扣课次</text>
					<input
						v-model="statusForm.countText"
						class="teacher-status-popup__input"
						type="number"
						placeholder="请输入实扣课次"
					/>
					<text class="teacher-status-popup__tip">默认按本课课时数带入，请假默认 0，可按实际情况调整。</text>
				</view>

				<view class="teacher-status-popup__actions">
					<wd-button plain @click="closeStatusPopup">取消</wd-button>
					<wd-button type="primary" :loading="statusSubmitting" @click="submitStatusChange">确认提交</wd-button>
				</view>
			</view>
		</wd-popup>
	</view>
</template>

<style scoped>
.teacher-attendance-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-attendance-page__content {
	padding: 12px;
}

.teacher-attendance-page__lesson-strip {
	display: flex;
	flex-wrap: wrap;
	gap: 8px;
	margin-bottom: 12px;
}

.teacher-attendance-page__lesson-chip {
	border-radius: 999px;
	background: #fff;
	padding: 8px 12px;
	font-size: 13px;
	color: #667085;
	box-shadow: 0 4px 12px rgba(64, 86, 122, 0.06);
}

.teacher-attendance-page__lesson-chip--active {
	background: #eef4ff;
	color: #3e7bfa;
	font-weight: 600;
}

.teacher-rollcall {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.teacher-rollcall__summary {
	padding: 0 2px;
	font-size: 13px;
	color: #8b95a7;
}

.teacher-rollcall__list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.teacher-rollcall-item {
	border-radius: 16px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.teacher-rollcall-item__header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.teacher-rollcall-item__student {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.teacher-rollcall-item__time {
	margin-top: 10px;
	font-size: 13px;
	color: #667085;
}

.teacher-rollcall-item__status {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 700;
}

.teacher-rollcall-item__status--signed {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.teacher-rollcall-item__status--makeup {
	background: rgba(59, 130, 246, 0.12);
	color: #2563eb;
}

.teacher-rollcall-item__status--absent {
	background: rgba(239, 68, 68, 0.12);
	color: #dc2626;
}

.teacher-rollcall-item__status--leave {
	background: rgba(245, 158, 11, 0.12);
	color: #d97706;
}

.teacher-rollcall-item__status--unknown {
	background: rgba(148, 163, 184, 0.12);
	color: #64748b;
}

.teacher-attendance-card {
	overflow: hidden;
	border-radius: 18px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.teacher-attendance-card__hero {
	padding: 20px 18px 18px;
	background: linear-gradient(135deg, #5b7cff 0%, #31c7a5 100%);
}

.teacher-attendance-card__title {
	font-size: 22px;
	font-weight: 700;
	color: #fff;
}

.teacher-attendance-card__meta {
	margin-top: 8px;
	font-size: 14px;
	color: rgba(255, 255, 255, 0.92);
}

.teacher-attendance-card__summary {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 12px;
	padding: 16px;
}

.teacher-attendance-card__summary-item {
	display: flex;
	flex-direction: column;
	gap: 6px;
	border-radius: 14px;
	background: #f8fafc;
	padding: 12px;
}

.teacher-attendance-card__summary-label {
	font-size: 12px;
	color: #94a3b8;
}

.teacher-attendance-card__summary-value {
	font-size: 15px;
	font-weight: 600;
	color: #334155;
}

.teacher-attendance-card__stats {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	border-top: 1px solid #eef1f6;
	border-left: 1px solid #eef1f6;
}

.teacher-attendance-card__stat {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 8px;
	min-height: 88px;
	border-right: 1px solid #eef1f6;
	border-bottom: 1px solid #eef1f6;
}

.teacher-attendance-card__stat-value {
	font-size: 24px;
	font-weight: 700;
	color: #111827;
}

.teacher-attendance-card__stat-label {
	font-size: 13px;
	color: #98a2b3;
}

.teacher-attendance-card__actions {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 12px;
	padding: 16px;
}

.teacher-attendance-student {
	margin-top: 12px;
	border-radius: 18px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.teacher-attendance-student__header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	margin-bottom: 12px;
}

.teacher-attendance-student__title {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.teacher-attendance-student__subtitle {
	margin-top: 4px;
	font-size: 12px;
	color: #98a2b3;
}

.teacher-attendance-student__list {
	display: flex;
	flex-direction: column;
}

.teacher-attendance-student__item {
	padding: 14px 0;
	border-bottom: 1px solid #eef1f6;
}

.teacher-attendance-student__item:last-child {
	border-bottom: 0;
}

.teacher-attendance-student__main {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.teacher-attendance-student__name {
	font-size: 15px;
	font-weight: 600;
	color: #111827;
}

.teacher-attendance-student__id {
	margin-top: 4px;
	font-size: 12px;
	color: #98a2b3;
}

.teacher-attendance-student__status {
	flex-shrink: 0;
	border-radius: 999px;
	padding: 6px 12px;
	font-size: 12px;
	font-weight: 600;
}

.teacher-attendance-student__status--signed {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.teacher-attendance-student__status--makeup {
	background: rgba(91, 124, 255, 0.12);
	color: #4c6fff;
}

.teacher-attendance-student__status--leave {
	background: rgba(245, 158, 11, 0.12);
	color: #d97706;
}

.teacher-attendance-student__status--absent {
	background: rgba(239, 68, 68, 0.12);
	color: #dc2626;
}

.teacher-attendance-student__status--change {
	background: rgba(59, 130, 246, 0.12);
	color: #2563eb;
}

.teacher-attendance-student__status--pending {
	background: rgba(148, 163, 184, 0.12);
	color: #64748b;
}

.teacher-attendance-student__actions {
	display: flex;
	justify-content: flex-end;
	margin-top: 12px;
}

.teacher-attendance-student__more {
	display: flex;
	align-items: center;
	justify-content: center;
	height: 40px;
	margin-top: 12px;
	border-radius: 999px;
	background: #f8fafc;
	font-size: 14px;
	font-weight: 600;
	color: #31c7a5;
}

.teacher-status-popup__body {
	padding: 20px 16px calc(env(safe-area-inset-bottom) + 18px);
	background: #fff;
	border-top-left-radius: 18px;
	border-top-right-radius: 18px;
}

.teacher-status-popup__title {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.teacher-status-popup__subtitle {
	margin-top: 8px;
	font-size: 14px;
	color: #667085;
}

.teacher-status-popup__group {
	margin-top: 18px;
}

.teacher-status-popup__label {
	display: block;
	margin-bottom: 10px;
	font-size: 14px;
	font-weight: 600;
	color: #344054;
}

.teacher-status-popup__options {
	display: flex;
	flex-wrap: wrap;
	gap: 8px;
}

.teacher-status-popup__option {
	border: 1px solid #d9e0ec;
	border-radius: 999px;
	padding: 6px 12px;
	font-size: 13px;
	color: #667085;
}

.teacher-status-popup__option--active {
	border-color: #31c7a5;
	background: rgba(49, 199, 165, 0.1);
	color: #1ca386;
}

.teacher-status-popup__input {
	width: 100%;
	height: 42px;
	box-sizing: border-box;
	border-radius: 12px;
	background: #f8fafc;
	padding: 0 14px;
	font-size: 14px;
	color: #344054;
}

.teacher-status-popup__tip {
	display: block;
	margin-top: 8px;
	font-size: 12px;
	line-height: 1.6;
	color: #98a2b3;
}

.teacher-status-popup__actions {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 12px;
	margin-top: 22px;
}
</style>
