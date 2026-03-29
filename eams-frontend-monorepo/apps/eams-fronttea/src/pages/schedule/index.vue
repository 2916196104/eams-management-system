<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherMonthCalendar from "@/components/teacher/TeacherMonthCalendar.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import TeacherSectionCard from "@/components/teacher/TeacherSectionCard.vue";
import { withTeacherBackQuery } from "@/utils/teacherNavigation";

definePage({
	name: "schedule",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "课表",
		titleNView: false,
	},
});

const router = useRouter();
const currentRoute = useRoute();
const userStore = useUserStore();
const { getScheduleByDate } = storeToRefs(userStore);

const selectedDate = ref(formatDate(new Date()));
const isScheduleLoading = ref(false);

const selectedSchedules = computed(() => getScheduleByDate.value(selectedDate.value));
const sectionTitle = computed(() => `${selectedDate.value}课表`);
const sectionExtra = computed(() => {
	if (isScheduleLoading.value) return "加载中";
	return selectedSchedules.value.length ? `${selectedSchedules.value.length}节` : "本日无课";
});

function formatDate(date: Date) {
	const year = date.getFullYear();
	const month = String(date.getMonth() + 1).padStart(2, "0");
	const day = String(date.getDate()).padStart(2, "0");
	return `${year}-${month}-${day}`;
}

async function loadSchedule(date: string) {
	isScheduleLoading.value = true;
	try {
		await userStore.loadScheduleByDate(date);
	} finally {
		isScheduleLoading.value = false;
	}
}

async function refreshPage() {
	await loadSchedule(selectedDate.value);
	uni.showToast({ title: "已刷新", icon: "none" });
}

function openAttendanceDetail(lessonId?: number | string, date = selectedDate.value) {
	if (!lessonId) return;

	router.push({
		path: "/subPages/teacher/attendance-record",
		query: withTeacherBackQuery(currentRoute, {
			lesson_id: String(lessonId),
			date,
		}),
	} as any);
}

watch(
	selectedDate,
	(value) => {
		void loadSchedule(value);
	},
	{ immediate: true },
);

onShow(() => {
	void loadSchedule(selectedDate.value);
});
</script>

<template>
	<view class="teacher-schedule">
		<teacher-nav-bar title="课表" @refresh="refreshPage" />

		<!-- 月历选择器 -->
		<teacher-month-calendar v-model="selectedDate" />

		<!-- 中间拖拽提示条 -->
		<view class="teacher-schedule__handle">
			<view class="i-carbon:chevron-up text-18px text-#c1c8d5" />
		</view>

		<!-- 指定日期课表 -->
		<teacher-section-card :title="sectionTitle" :extra="sectionExtra">
			<view v-if="selectedSchedules.length" class="teacher-schedule__list">
				<view
					v-for="item in selectedSchedules"
					:key="item.id"
					class="teacher-schedule__item"
					@click="openAttendanceDetail(item.lessonId, selectedDate)"
				>
					<text class="teacher-schedule__time">{{ item.startTime }}-{{ item.endTime }}</text>
					<view class="teacher-schedule__main">
						<text class="teacher-schedule__course">{{ item.courseName }}</text>
						<text class="teacher-schedule__meta">{{ item.className }} · {{ item.classroom }}</text>
					</view>
				</view>
			</view>
			<teacher-empty-state v-else :title="isScheduleLoading ? '加载中...' : '本日无课'" compact />
		</teacher-section-card>
	</view>
</template>

<style scoped>
.teacher-schedule {
	min-height: 100vh;
	padding: 0 12px 18px;
	background: #f5f6fa;
}

.teacher-schedule__handle {
	display: flex;
	align-items: center;
	justify-content: center;
	padding: 8px 0 2px;
}

.teacher-schedule__list {
	padding: 12px 16px;
}

.teacher-schedule__item {
	display: flex;
	gap: 12px;
	padding: 12px 0;
	border-bottom: 1px solid #eef1f6;
}

.teacher-schedule__item:last-child {
	border-bottom: 0;
}

.teacher-schedule__time {
	flex-shrink: 0;
	font-size: 14px;
	font-weight: 600;
	color: #344054;
}

.teacher-schedule__main {
	display: flex;
	flex-direction: column;
	gap: 4px;
}

.teacher-schedule__course {
	font-size: 15px;
	font-weight: 600;
	color: #111827;
}

.teacher-schedule__meta {
	font-size: 13px;
	color: #98a2b3;
}
</style>
