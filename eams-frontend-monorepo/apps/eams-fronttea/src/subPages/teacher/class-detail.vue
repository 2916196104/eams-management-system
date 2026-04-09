<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { withTeacherBackQuery } from "@/utils/teacherNavigation";

definePage({
	name: "teacherClassDetail",
	style: {
		navigationBarTitleText: "班级详情",
		titleNView: false,
	},
});

interface ClassStudentItem {
	id: number | string;
	classId: number | string;
	studentId: number | string;
	studentName: string;
	gender: number;
	headImg: string;
	countLessonRemaining: number;
}

const router = useRouter();
const route = useRoute() as { query?: Record<string, string | string[] | undefined> };

const loading = ref(false);
const loadingMore = ref(false);
const keyword = ref("");
const pageIndex = ref(1);
const pages = ref(0);
const total = ref(0);
const pageSize = 10;
const students = ref<ClassStudentItem[]>([]);

const hasMore = computed(() => pageIndex.value < pages.value);

function readQuery(key: string) {
	const value = route.query?.[key];
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

const classId = computed(() => readQuery("classId"));
const className = computed(() => readQuery("name") || "班级详情");
const classTeacher = computed(() => readQuery("teacher") || "--");
const classCourse = computed(() => readQuery("course") || "--");
const classNumber = computed(() => readQuery("number") || "--");

function normalizeRows(source: unknown) {
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
			id: item.id ?? `${item.studentId ?? item.student_id ?? index}`,
			classId: item.classId ?? item.class_id ?? classId.value,
			studentId: item.studentId ?? item.student_id ?? index,
			studentName: item.studentName ?? item.student_name ?? item.name ?? `学员${index + 1}`,
			gender: Number(item.gender ?? 0),
			headImg: item.headImg ?? item.head_img ?? "",
			countLessonRemaining: Number(item.countLessonRemaining ?? item.remainingLessonCount ?? item.lesson_count ?? 0),
		} satisfies ClassStudentItem;
	});
}

function genderText(gender: number) {
	if (gender === 1) return "男";
	if (gender === 2) return "女";
	return "未知";
}

async function loadStudents(nextPage = 1, append = false) {
	if (!classId.value) return;

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const response = await (Apis as any).class.get_class_query_class_student_list({
			params: {
				pageIndex: nextPage,
				pageSize,
				classId: Number(classId.value),
				studentName: keyword.value || undefined,
			},
		});

		const payload = (response as any)?.data?.data ?? (response as any)?.data ?? response ?? {};
		const rows = normalizeRows(response);
		pageIndex.value = Number(payload.pageIndex ?? nextPage);
		pages.value = Number(payload.pages ?? payload.total_page ?? (rows.length ? 1 : 0));
		total.value = Number(payload.total ?? rows.length);
		students.value = append ? [...students.value, ...rows] : rows;
	} catch {
		if (!append) students.value = [];
		uni.showToast({ title: "班级学员加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

function openStudentDetail(item: ClassStudentItem) {
	router.push({
		name: "teacherClassStudentDetail",
		query: withTeacherBackQuery(route, {
			id: String(item.id),
			classId: String(item.classId),
			studentId: String(item.studentId),
			name: item.studentName,
		}),
	} as any);
}

async function refreshPage() {
	await loadStudents(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function searchStudents() {
	await loadStudents(1, false);
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadStudents(pageIndex.value + 1, true);
}

onShow(() => {
	void loadStudents(1, false);
});
</script>

<template>
  <view class="teacher-class-detail-page">
    <teacher-nav-bar title="班级详情" @refresh="refreshPage" />

    <view class="teacher-class-detail-page__content">
      <view class="teacher-class-info">
        <view class="teacher-class-info__title">
          {{ className }}
        </view>
        <view class="teacher-class-info__meta">
          课程：{{ classCourse }}
        </view>
        <view class="teacher-class-info__meta">
          班主任：{{ classTeacher }}
        </view>
        <view class="teacher-class-info__meta">
          人数：{{ classNumber }}
        </view>
      </view>

      <view class="teacher-class-search">
        <input v-model="keyword" class="teacher-class-search__input" placeholder="搜索学员姓名" confirm-type="search" @confirm="searchStudents">
        <view class="teacher-class-search__button" @click="searchStudents">
          搜索
        </view>
      </view>

      <view v-if="students.length" class="teacher-class-detail-page__summary">
        共 {{ total }} 名学员
      </view>

      <view v-if="students.length" class="teacher-class-student-list">
        <view v-for="item in students" :key="item.id" class="teacher-class-student" @click="openStudentDetail(item)">
          <view class="teacher-class-student__main">
            <view class="teacher-class-student__avatar">
              <image v-if="item.headImg" :src="item.headImg" mode="aspectFill" class="teacher-class-student__image" />
              <text v-else>
                {{ item.studentName.slice(0, 1) }}
              </text>
            </view>
            <view class="teacher-class-student__info">
              <view class="teacher-class-student__name">
                {{ item.studentName }}
              </view>
              <view class="teacher-class-student__meta">
                {{ genderText(item.gender) }} / 剩余课次 {{ item.countLessonRemaining }}
              </view>
            </view>
          </view>
          <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
        </view>
      </view>

      <teacher-empty-state v-else :title="loading ? '加载中...' : '暂无班级学员'" compact />

      <view v-if="hasMore" class="teacher-class-detail-page__more" @click="loadMore">
        {{ loadingMore ? "加载中..." : "加载更多" }}
      </view>
    </view>
  </view>
</template>

<style scoped>
.teacher-class-detail-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-class-detail-page__content {
	padding: 12px;
}

.teacher-class-info {
	border-radius: 18px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-class-info__title {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.teacher-class-info__meta {
	margin-top: 10px;
	font-size: 13px;
	color: #667085;
}

.teacher-class-search {
	display: flex;
	align-items: center;
	gap: 10px;
	margin-top: 12px;
}

.teacher-class-search__input {
	flex: 1;
	height: 42px;
	box-sizing: border-box;
	border-radius: 12px;
	background: #fff;
	padding: 0 14px;
	font-size: 14px;
	color: #344054;
}

.teacher-class-search__button {
	display: flex;
	align-items: center;
	justify-content: center;
	width: 72px;
	height: 42px;
	border-radius: 12px;
	background: #31c7a5;
	font-size: 14px;
	font-weight: 600;
	color: #fff;
}

.teacher-class-detail-page__summary {
	margin: 12px 0 10px;
	padding: 0 2px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-class-student-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.teacher-class-student {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
	border-radius: 18px;
	background: #fff;
	padding: 14px 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-class-student__main {
	display: flex;
	align-items: center;
	gap: 12px;
	min-width: 0;
}

.teacher-class-student__avatar {
	display: flex;
	align-items: center;
	justify-content: center;
	width: 42px;
	height: 42px;
	border-radius: 50%;
	background: #e8f8f4;
	font-size: 16px;
	font-weight: 700;
	color: #1ca386;
	overflow: hidden;
}

.teacher-class-student__image {
	width: 100%;
	height: 100%;
}

.teacher-class-student__info {
	min-width: 0;
}

.teacher-class-student__name {
	font-size: 15px;
	font-weight: 600;
	color: #111827;
}

.teacher-class-student__meta {
	margin-top: 6px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-class-detail-page__more {
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
