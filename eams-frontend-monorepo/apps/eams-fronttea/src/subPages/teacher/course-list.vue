<script setup lang="ts">
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import TeacherSectionCard from "@/components/teacher/TeacherSectionCard.vue";

definePage({
	name: "teacherCourseList",
	style: {
		navigationBarTitleText: "课程列表",
		titleNView: false,
	},
});

type CourseStatus = "all" | "ongoing" | "upcoming" | "finished";

interface StaticCourseItem {
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

const courseList: StaticCourseItem[] = [
	{
		id: "course-1",
		name: "零壹硬笔基础班",
		subject: "硬笔书法",
		teacher: "陈老师",
		className: "启蒙一班",
		schedule: "每周二、周四 19:00-20:30",
		remaining: 12,
		total: 24,
		status: "ongoing",
		description: "当前为正式在读班，适合工作台直接查看课程节奏与剩余课次。",
	},
	{
		id: "course-2",
		name: "零壹素描提升班",
		subject: "美术",
		teacher: "林老师",
		className: "周末提升班",
		schedule: "每周六 09:30-11:30",
		remaining: 8,
		total: 16,
		status: "ongoing",
		description: "周末课次较集中，后续接真实接口后可补课消耗与出勤统计。",
	},
	{
		id: "course-3",
		name: "零壹英语拼读营",
		subject: "英语",
		teacher: "王老师",
		className: "暑期集训班",
		schedule: "2026-07-08 开班",
		remaining: 20,
		total: 20,
		status: "upcoming",
		description: "该课程当前只做静态预览，等接口稳定后再接报名与课次明细。",
	},
	{
		id: "course-4",
		name: "零壹围棋体验课",
		subject: "围棋",
		teacher: "赵老师",
		className: "体验课",
		schedule: "已于 2026-03-15 结课",
		remaining: 0,
		total: 4,
		status: "finished",
		description: "已结课课程暂以静态归档形式展示，后续可补历史记录查询。",
	},
];

const statusOptions = [
	{ label: "全部", value: "all" },
	{ label: "进行中", value: "ongoing" },
	{ label: "待开课", value: "upcoming" },
	{ label: "已结课", value: "finished" },
] as const;

const filteredCourses = computed(() => {
	if (activeStatus.value === "all") return courseList;
	return courseList.filter((item) => item.status === activeStatus.value);
});

const summaryText = computed(() => {
	if (activeStatus.value === "all") return `静态课程 ${courseList.length} 门`;
	return `筛选结果 ${filteredCourses.value.length} 门`;
});

function statusText(status: StaticCourseItem["status"]) {
	switch (status) {
		case "ongoing":
			return "进行中";
		case "upcoming":
			return "待开课";
		default:
			return "已结课";
	}
}

function statusClass(status: StaticCourseItem["status"]) {
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
	toast.show("课程接口暂未稳定，当前展示静态页面");
}
</script>

<template>
	<view class="teacher-course-page">
		<TeacherNavBar title="课程列表" :show-back="true" @refresh="refreshPage" />

		<view class="teacher-course-page__content">
			<view class="teacher-course-page__tip">
				<view class="i-carbon:information text-18px text-#2563eb" />
				<text>当前课程接口暂未确认，页面先用静态数据承接工作台入口。</text>
			</view>

			<TeacherSectionCard title="课程概览" :extra="summaryText">
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

			<TeacherSectionCard title="课程列表">
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
