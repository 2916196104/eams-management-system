<script setup lang="ts">
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import TeacherSectionCard from "@/components/teacher/TeacherSectionCard.vue";
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import { Apis } from "@/api";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "teacherCourseList",
	style: {
		navigationBarTitleText: "课程列表",
		titleNView: false,
	},
});

type CourseStatus = "all" | "ongoing" | "upcoming" | "finished";

interface CourseItem {
	id: string;
	name: string;
	subject: string;
	teacher: string;
	className: string;
	schedule: string;
	remaining: number;
	total: number;
	status: Exclude<CourseStatus, "all">;
	description: string;
}

const toast = useGlobalToast();
const activeStatus = ref<CourseStatus>("all");
const loading = ref(false);
const courseList = ref<CourseItem[]>([]);
const userStore = useUserStore();

const statusOptions = [
	{ label: "全部", value: "all" },
	{ label: "进行中", value: "ongoing" },
	{ label: "待开课", value: "upcoming" },
	{ label: "已结课", value: "finished" },
] as const;

function normalizeCourseData(source: any): CourseItem[] {
	const payload = source?.data?.data ?? source?.data ?? source ?? [];
	const rows = Array.isArray(payload) ? payload : Array.isArray(payload.list) ? payload.list : [];

	return rows.map((item: any, index: number) => {
		const status = item.status || item.courseStatus || "ongoing";
		return {
			id: String(item.id ?? item.courseId ?? `course-${index}`),
			name: item.name || item.courseName || `课程${index + 1}`,
			subject: item.subject || item.subjectName || item.courseType || "未知科目",
			teacher: item.teacher || item.teacherName || "未知老师",
			className: item.className || item.class_name || "未知班级",
			schedule: item.schedule || item.classTime || item.courseTime || "暂无安排",
			remaining: Number(item.remaining ?? item.remainingLessons ?? item.leftCount ?? 0),
			total: Number(item.total ?? item.totalLessons ?? item.totalCount ?? 0),
			status: (status === "1" || status === "ongoing" || status === "进行中") ? "ongoing" :
				(status === "2" || status === "upcoming" || status === "待开课") ? "upcoming" :
				"finished",
			description: item.description || item.remark || "暂无描述",
		} satisfies CourseItem;
	});
}

async function loadCourses() {
	loading.value = true;
	try {
		if (!userStore.teacherInfo.id) {
			await userStore.loadCurrentUserInfo();
		}
		
		const response = await (Apis as any).workbench.get_workbench_courseList();
		courseList.value = normalizeCourseData(response);
	} catch (error) {
		console.error("加载课程列表失败:", error);
		toast.show("课程列表加载失败");
		courseList.value = [];
	} finally {
		loading.value = false;
	}
}

const filteredCourses = computed(() => {
	if (activeStatus.value === "all") return courseList.value;
	return courseList.value.filter((item) => item.status === activeStatus.value);
});

const summaryText = computed(() => {
	if (activeStatus.value === "all") return `课程 ${courseList.value.length} 门`;
	return `筛选结果 ${filteredCourses.value.length} 门`;
});

function statusText(status: CourseItem["status"]) {
	switch (status) {
		case "ongoing":
			return "进行中";
		case "upcoming":
			return "待开课";
		default:
			return "已结课";
	}
}

function statusClass(status: CourseItem["status"]) {
	switch (status) {
		case "ongoing":
			return "teacher-course-card__badge--ongoing";
		case "upcoming":
			return "teacher-course-card__badge--upcoming";
		default:
			return "teacher-course-card__badge--finished";
	}
}

function refreshPage() {
	void loadCourses();
}

onShow(() => {
	void loadCourses();
});
</script>

<template>
	<view class="teacher-course-page">
		<TeacherNavBar title="课程列表" :show-back="true" @refresh="refreshPage" />

		<view class="teacher-course-page__content">
			<TeacherSectionCard v-if="!loading && courseList.length" title="课程概览" :extra="summaryText">
				<view class="teacher-course-summary">
					<view class="teacher-course-summary__item">
						<text class="teacher-course-summary__value">{{ courseList.length }}</text>
						<text class="teacher-course-summary__label">总课程数</text>
					</view>
					<view class="teacher-course-summary__item">
						<text class="teacher-course-summary__value">{{ courseList.filter((item) => item.status === "ongoing").length }}</text>
						<text class="teacher-course-summary__label">进行中</text>
					</view>
					<view class="teacher-course-summary__item">
						<text class="teacher-course-summary__value">{{ courseList.filter((item) => item.status === "upcoming").length }}</text>
						<text class="teacher-course-summary__label">待开课</text>
					</view>
				</view>
			</TeacherSectionCard>

			<TeacherSectionCard v-if="!loading && courseList.length" title="课程列表">
				<view class="teacher-course-filter">
					<view
						v-for="option in statusOptions"
						:key="option.value"
						class="teacher-course-filter__chip"
						:class="{ 'teacher-course-filter__chip--active': activeStatus === option.value }"
						@click="activeStatus = option.value"
					>
						{{ option.label }}
					</view>
				</view>

				<view class="teacher-course-list">
					<view v-for="item in filteredCourses" :key="item.id" class="teacher-course-card">
						<view class="teacher-course-card__header">
							<view>
								<view class="teacher-course-card__title">{{ item.name }}</view>
								<view class="teacher-course-card__meta">{{ item.subject }} / {{ item.className }}</view>
							</view>
							<view class="teacher-course-card__badge" :class="statusClass(item.status)">
								{{ statusText(item.status) }}
							</view>
						</view>

						<view class="teacher-course-card__line">授课老师：{{ item.teacher }}</view>
						<view class="teacher-course-card__line">上课安排：{{ item.schedule }}</view>
						<view class="teacher-course-card__line">课次进度：剩余 {{ item.remaining }} / 总计 {{ item.total }}</view>
						<view class="teacher-course-card__desc">{{ item.description }}</view>
					</view>
				</view>
			</TeacherSectionCard>

			<TeacherEmptyState v-else :title="loading ? '加载中...' : '暂无课程数据'" compact />
		</view>
	</view>
</template>

<style scoped>
.teacher-course-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-course-page__content {
	padding: 12px;
}

.teacher-course-page__tip {
	display: flex;
	align-items: flex-start;
	gap: 8px;
	border-radius: 14px;
	background: #eff6ff;
	padding: 14px 16px;
	font-size: 13px;
	line-height: 1.7;
	color: #1d4ed8;
}

.teacher-course-summary {
	display: grid;
	grid-template-columns: repeat(3, minmax(0, 1fr));
}

.teacher-course-summary__item {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 8px;
	min-height: 100px;
	border-right: 1px solid #eef1f6;
}

.teacher-course-summary__item:last-child {
	border-right: 0;
}

.teacher-course-summary__value {
	font-size: 24px;
	font-weight: 700;
	color: #111827;
}

.teacher-course-summary__label {
	font-size: 13px;
	color: #98a2b3;
}

.teacher-course-filter {
	display: flex;
	flex-wrap: wrap;
	gap: 10px;
	padding: 14px 16px 0;
}

.teacher-course-filter__chip {
	border-radius: 999px;
	padding: 7px 14px;
	background: #f3f4f6;
	font-size: 13px;
	color: #667085;
}

.teacher-course-filter__chip--active {
	background: #e0ecff;
	color: #2563eb;
	font-weight: 600;
}

.teacher-course-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
	padding: 14px 16px 16px;
}

.teacher-course-card {
	border-radius: 16px;
	background: #f8fafc;
	padding: 14px;
}

.teacher-course-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.teacher-course-card__title {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.teacher-course-card__meta {
	margin-top: 6px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-course-card__badge {
	flex-shrink: 0;
	border-radius: 999px;
	padding: 4px 10px;
	font-size: 12px;
	font-weight: 600;
}

.teacher-course-card__badge--ongoing {
	background: rgba(49, 199, 165, 0.14);
	color: #1ca386;
}

.teacher-course-card__badge--upcoming {
	background: rgba(59, 130, 246, 0.14);
	color: #2563eb;
}

.teacher-course-card__badge--finished {
	background: rgba(148, 163, 184, 0.14);
	color: #64748b;
}

.teacher-course-card__line {
	margin-top: 10px;
	font-size: 13px;
	line-height: 1.6;
	color: #475467;
}

.teacher-course-card__desc {
	margin-top: 12px;
	border-radius: 12px;
	background: #fff;
	padding: 10px 12px;
	font-size: 12px;
	line-height: 1.7;
	color: #667085;
}
</style>
