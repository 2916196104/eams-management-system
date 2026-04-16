<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import TeacherSectionCard from "@/components/teacher/TeacherSectionCard.vue";

definePage({
	name: "teacherClassStudentDetail",
	style: {
		navigationBarTitleText: "学员详情",
		titleNView: false,
	},
});

interface ClassStudentDetailInfo {
	id: number | string;
	classId: number | string;
	studentId: number | string;
	consumeCourseId?: number | string;
	userId?: number | string;
	name: string;
	mobile: string;
	gender: number;
	birthday: string;
	age: number | string;
	stage: number | string;
	headImg: string;
	remark: string;
	classStudentRemark: string;
}

interface StudentCourseItem {
	id: number | string;
	studentId: number | string;
	courseId: number | string;
	courseName: string;
	subjectName: string;
	startDate: string;
	expireDate: string;
	countLessonTotal: number;
	countLessonComplete: number;
	countLessonRefund: number;
	countLessonRemaining: number;
	progress: string;
	defaultConsumeCourse: number;
}

const route = useRoute() as { query?: Record<string, string | string[] | undefined> };

const loading = ref(false);
const courseLoading = ref(false);
const courseLoadingMore = ref(false);
const detail = ref<ClassStudentDetailInfo | null>(null);
const courses = ref<StudentCourseItem[]>([]);
const pageIndex = ref(1);
const pages = ref(0);
const total = ref(0);
const pageSize = 10;

const hasMore = computed(() => pageIndex.value < pages.value);

function readQuery(key: string) {
	const value = route.query?.[key];
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

const relationId = computed(() => readQuery("id"));
const classId = computed(() => readQuery("classId"));
const studentId = computed(() => readQuery("studentId"));

function normalizeDetail(source: unknown): ClassStudentDetailInfo | null {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source;
	if (!payload || Array.isArray(payload)) return null;

	return {
		id: payload.id ?? relationId.value,
		classId: payload.classId ?? payload.class_id ?? classId.value,
		studentId: payload.studentId ?? payload.student_id ?? studentId.value,
		consumeCourseId: payload.consumeCourseId ?? payload.consume_course_id,
		userId: payload.userId,
		name: payload.name || readQuery("name") || "--",
		mobile: payload.mobile || "--",
		gender: Number(payload.gender ?? 0),
		birthday: payload.birthday || "--",
		age: payload.age ?? "--",
		stage: payload.stage ?? "--",
		headImg: payload.headImg || payload.head_img || "",
		remark: payload.remark || "--",
		classStudentRemark: payload.classStudentRemark || payload.class_student_remark || "--",
	};
}

function normalizeCourseRows(source: unknown) {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source ?? {};
	const rawRows = Array.isArray(payload.rows)
		? payload.rows
		: Array.isArray(payload.list)
			? payload.list
			: Array.isArray(payload)
				? payload
				: [];

	return rawRows.map((item: any, index: number) => {
		return {
			id: item.id ?? `${item.courseId ?? item.course_id ?? index}`,
			studentId: item.studentId ?? item.student_id ?? studentId.value,
			courseId: item.courseId ?? item.course_id ?? index,
			courseName: item.courseName || "--",
			subjectName: item.subjectName || item.subject || "--",
			startDate: item.startDate || "--",
			expireDate: item.expireDate || "--",
			countLessonTotal: Number(item.countLessonTotal ?? 0),
			countLessonComplete: Number(item.countLessonComplete ?? 0),
			countLessonRefund: Number(item.countLessonRefund ?? item.refundLessonCount ?? 0),
			countLessonRemaining: Number(item.countLessonRemaining ?? 0),
			progress: item.progress || item.progressText || "--",
			defaultConsumeCourse: Number(item.defaultConsumeCourse ?? item.default_consume_course ?? 0),
		} satisfies StudentCourseItem;
	});
}

function genderText(gender: number) {
	if (gender === 1) return "男";
	if (gender === 2) return "女";
	return "未知";
}

function stageText(stage: number | string) {
	if (stage === 1 || stage === "1") return "意向学员";
	if (stage === 2 || stage === "2") return "在学学员";
	if (stage === 3 || stage === "3") return "结业学员";
	return String(stage || "--");
}

async function loadDetail() {
	if (!studentId.value && !relationId.value) return;

	loading.value = true;
	try {
		const response = await (Apis as any).class.get_class_query_class_student_detail({
			params: {
				studentId: Number(studentId.value || relationId.value),
			},
		});
		detail.value = normalizeDetail(response);
	} catch {
		detail.value = null;
		uni.showToast({ title: "学员详情加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

async function loadCourses(nextPage = 1, append = false) {
	if (!classId.value || !studentId.value) return;

	const targetLoading = append ? courseLoadingMore : courseLoading;
	targetLoading.value = true;

	try {
		const response = await (Apis as any).class.get_class_query_class_student_course_list({
			params: {
				pageIndex: nextPage,
				pageSize,
				studentId: Number(studentId.value),
			},
		});

		const payload = (response as any)?.data?.data ?? (response as any)?.data ?? response ?? {};
		const rows = normalizeCourseRows(response);
		pageIndex.value = Number(payload.pageIndex ?? nextPage);
		pages.value = Number(payload.pages ?? payload.total_page ?? (rows.length ? 1 : 0));
		total.value = Number(payload.total ?? rows.length);
		courses.value = append ? [...courses.value, ...rows] : rows;
	} catch {
		if (!append) courses.value = [];
		uni.showToast({ title: "课程记录加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function refreshPage() {
	await Promise.all([loadDetail(), loadCourses(1, false)]);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!hasMore.value || courseLoadingMore.value) return;
	await loadCourses(pageIndex.value + 1, true);
}

onShow(() => {
	void refreshPage();
});
</script>

<template>
  <view class="teacher-student-detail-page">
    <teacher-nav-bar title="学员详情" @refresh="refreshPage" />

    <view class="teacher-student-detail-page__content">
      <view v-if="detail" class="teacher-student-card">
        <view class="teacher-student-card__header">
          <view class="teacher-student-card__avatar">
            <image v-if="detail.headImg" :src="detail.headImg" mode="aspectFill" class="teacher-student-card__image" />
            <text v-else>
              {{ detail.name.slice(0, 1) }}
            </text>
          </view>
          <view class="teacher-student-card__main">
            <view class="teacher-student-card__name">
              {{ detail.name }}
            </view>
            <view class="teacher-student-card__meta">
              {{ genderText(detail.gender) }} / {{ detail.age }} 岁
            </view>
            <view class="teacher-student-card__meta">
              {{ detail.mobile }}
            </view>
          </view>
        </view>

        <view class="teacher-student-card__grid">
          <view class="teacher-student-card__field">
            <text class="teacher-student-card__label">
              生日
            </text>
            <text class="teacher-student-card__value">
              {{ detail.birthday }}
            </text>
          </view>
          <view class="teacher-student-card__field">
            <text class="teacher-student-card__label">
              学员阶段
            </text>
            <text class="teacher-student-card__value">
              {{ stageText(detail.stage) }}
            </text>
          </view>
          <view class="teacher-student-card__field">
            <text class="teacher-student-card__label">
              默认消费课程ID
            </text>
            <text class="teacher-student-card__value">
              {{ detail.consumeCourseId || "--" }}
            </text>
          </view>
          <view class="teacher-student-card__field">
            <text class="teacher-student-card__label">
              家长用户ID
            </text>
            <text class="teacher-student-card__value">
              {{ detail.userId || "--" }}
            </text>
          </view>
        </view>

        <view class="teacher-student-card__remark">
          <text class="teacher-student-card__label">
            学员备注
          </text>
          <text class="teacher-student-card__remark-text">
            {{ detail.remark }}
          </text>
        </view>
        <view class="teacher-student-card__remark">
          <text class="teacher-student-card__label">
            班级备注
          </text>
          <text class="teacher-student-card__remark-text">
            {{ detail.classStudentRemark }}
          </text>
        </view>
      </view>

      <teacher-empty-state v-else :title="loading ? '加载中...' : '暂无学员详情'" compact />

      <teacher-section-card title="课程记录" :extra="courses.length ? `${total} 条` : ''">
        <view v-if="courses.length" class="teacher-student-course-list">
          <view v-for="item in courses" :key="item.id" class="teacher-student-course">
            <view class="teacher-student-course__header">
              <view>
                <view class="teacher-student-course__title">
                  {{ item.courseName }}
                </view>
                <view class="teacher-student-course__meta">
                  {{ item.subjectName }}
                </view>
              </view>
              <view v-if="item.defaultConsumeCourse" class="teacher-student-course__badge">
                默认消费
              </view>
            </view>

            <view class="teacher-student-course__meta">
              开始时间：{{ item.startDate }}
            </view>
            <view class="teacher-student-course__meta">
              有效期：{{ item.expireDate }}
            </view>
            <view class="teacher-student-course__meta">
              学习进度：{{ item.progress }}
            </view>
            <view class="teacher-student-course__meta">
              总课次 {{ item.countLessonTotal }} / 已上 {{ item.countLessonComplete }} / 退款 {{ item.countLessonRefund }} / 剩余 {{ item.countLessonRemaining }}
            </view>
          </view>
        </view>

        <teacher-empty-state v-else :title="courseLoading ? '加载中...' : '暂无课程记录'" compact />
      </teacher-section-card>

      <view v-if="hasMore" class="teacher-student-detail-page__more" @click="loadMore">
        {{ courseLoadingMore ? "加载中..." : "加载更多" }}
      </view>
    </view>
  </view>
</template>

<style scoped>
.teacher-student-detail-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-student-detail-page__content {
	padding: 12px;
}

.teacher-student-card {
	border-radius: 18px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-student-card__header {
	display: flex;
	align-items: center;
	gap: 14px;
}

.teacher-student-card__avatar {
	display: flex;
	align-items: center;
	justify-content: center;
	width: 60px;
	height: 60px;
	border-radius: 50%;
	background: #e8f8f4;
	font-size: 20px;
	font-weight: 700;
	color: #1ca386;
	overflow: hidden;
}

.teacher-student-card__image {
	width: 100%;
	height: 100%;
}

.teacher-student-card__main {
	display: flex;
	flex-direction: column;
	gap: 6px;
}

.teacher-student-card__name {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.teacher-student-card__meta {
	font-size: 13px;
	color: #667085;
}

.teacher-student-card__grid {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 12px;
	margin-top: 16px;
}

.teacher-student-card__field {
	display: flex;
	flex-direction: column;
	gap: 6px;
	border-radius: 14px;
	background: #f8fafc;
	padding: 12px;
}

.teacher-student-card__label {
	font-size: 12px;
	color: #98a2b3;
}

.teacher-student-card__value {
	font-size: 14px;
	font-weight: 600;
	color: #344054;
}

.teacher-student-card__remark {
	display: flex;
	flex-direction: column;
	gap: 8px;
	margin-top: 14px;
	border-radius: 14px;
	background: #f8fafc;
	padding: 12px;
}

.teacher-student-card__remark-text {
	font-size: 14px;
	line-height: 1.7;
	color: #475467;
	word-break: break-word;
}

.teacher-student-course-list {
	padding: 12px 14px 16px;
}

.teacher-student-course {
	padding: 14px 0;
	border-bottom: 1px solid #edf0f5;
}

.teacher-student-course:last-child {
	border-bottom: 0;
}

.teacher-student-course__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 10px;
}

.teacher-student-course__title {
	font-size: 15px;
	font-weight: 600;
	color: #111827;
}

.teacher-student-course__meta {
	margin-top: 8px;
	font-size: 13px;
	line-height: 1.7;
	color: #667085;
}

.teacher-student-course__badge {
	flex-shrink: 0;
	border-radius: 999px;
	background: rgba(49, 199, 165, 0.12);
	padding: 4px 10px;
	font-size: 12px;
	font-weight: 600;
	color: #1ca386;
}

.teacher-student-detail-page__more {
	display: flex;
	align-items: center;
	justify-content: center;
	height: 40px;
	margin-top: 12px;
	border-radius: 999px;
	background: #fff;
	font-size: 14px;
	font-weight: 600;
	color: #31c7a5;
}
</style>
