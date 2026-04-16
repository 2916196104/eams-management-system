<template>
	<!-- 顶部统计面板 -->
	<el-row class="statistics-row" v-if="!statisticsLoading">
		<el-col v-for="item in statisticsList" :key="item.targetText" :xs="12" :sm="12" :md="6">
			<statistics v-bind="item" />
		</el-col>
	</el-row>
	<!-- 下方内容区域 -->
	<el-row class="content-row">
		<!-- 左侧 -->
		<el-col :span="16">
			<el-card>
				<!-- Tabs -->
				<el-tabs v-model="calendar" class="calendar-tabs">
					<el-tab-pane label="我的课表" name="my" />
					<el-tab-pane label="全部课表" name="all" />
				</el-tabs>
				<!-- 只保留一个 Calendar -->
				<my-calendar>
					<!-- 月视图 -->
					<template #cell="{ cell }">
						<div v-for="item in getEvents(cell.date)" :key="item.id">
							<calendar-text :info="item">
								{{ item.startTime }}
								{{ item.courseName }}
								({{ item.teacherName }})
							</calendar-text>
						</div>
					</template>
					<!-- 周视图 -->
					<template #week-cell="{ date, hour }">
						<div v-for="item in getWeekEvents(date, hour)" :key="item.id">
							{{ item.courseName }} - {{ item.teacherName }}
						</div>
					</template>
					<!-- 日视图 -->
					<template #day-cell="{ date, hour }">
						<div v-for="item in getDayEvents(date, hour)" :key="item.id">
							{{ item.courseName }} - {{ item.teacherName }}
						</div>
					</template>
				</my-calendar>
			</el-card>
		</el-col>
		<!-- 右侧 -->
		<el-col :span="8">
			<school-notice :data="noticeStore.noticeList" />
			<el-card style="margin-left: 10px">
				<line-chart
					title="本月报名走势"
					:x-axis-data="echartsStore.trendXAxis"
					:series-data="echartsStore.trendSeries"
					height="400px"
				/>
			</el-card>
			<el-card style="margin-left: 10px; margin-top: 10px">
				<bar-chart
					title="课程报名前5"
					:x-axis-data="barStore.barXAxis"
					:series-data="barStore.barSeries"
					height="400px"
					:show-label="true"
				/>
			</el-card>
		</el-col>
	</el-row>
</template>

<script setup lang="ts">
import { ref, onMounted, computed, watch } from "vue";
import { useStatisticsStore, useScheduleStore, useNoticeStore, useEchartsStore } from "@/stores/console";
import Statistics from "@/components/statistics/statistics.vue";
import MyCalendar from "@/components/mycalendar/MyCalendar.vue";
import LineChart from "@/components/mychart/LineChart.vue";
import BarChart from "@/components/mychart/BarChart.vue";
import CalendarText from "./components/CalendarText.vue";
import SchoolNotice from "./components/SchoolNotice.vue";

/* store */
const statisticsStore = useStatisticsStore();
const scheduleStore = useScheduleStore();
const noticeStore = useNoticeStore();
const echartsStore = useEchartsStore();
const barStore = useEchartsStore();
/* 统计面板 */
const statisticsLoading = ref(true);
onMounted(async () => {
	await statisticsStore.fetchStatistics(); // 获取统计数据
	statisticsLoading.value = false;
	await scheduleStore.fetchMySchedule(); // 默认加载我的课表
	await noticeStore.fetchNoticeList(); // 获取学校公告
	await echartsStore.fetchMonthlyTrend(); // 获取本月报名走势
	await barStore.fetchCourseTop5(); // 获取课程报名前5
});
// 统计数据
const statisticsList = computed(() => [
	{
		targetText: "学员数",
		targetNumber: statisticsStore.totalStudents,
		iconName: "mdi:people",
		iconColor: "#40C9C6",
		hoverIconColor: "white",
		hoverBgColor: "#40C9C6",
	},
	{
		targetText: "师资人数",
		targetNumber: statisticsStore.totalTeachers,
		iconName: "streamline-ultimate:hierarchy-5-organize-bold",
		iconColor: "#34bfa3",
		hoverIconColor: "white",
		hoverBgColor: "#34bfa3",
	},
	{
		targetText: "总课次",
		targetNumber: statisticsStore.totalLessons,
		iconName: "akar-icons:book",
		iconColor: "#36a3f7",
		hoverIconColor: "white",
		hoverBgColor: "#36a3f7",
	},
	{
		targetText: "本月报名数",
		targetNumber: statisticsStore.monthEnrollmentAmount,
		iconName: "hugeicons:money-bag-02",
		iconColor: "#f4516c",
		hoverIconColor: "white",
		hoverBgColor: "#f4516c",
	},
]);
/* 课表 */
const calendar = ref("my");
/* 防止重复加载课表 */
const loadedAll = ref(false);
/* 切换 Tab 加载数据 */
watch(calendar, async (val) => {
	if (val === "all" && !loadedAll.value) {
		await scheduleStore.fetchAllSchedule();
		loadedAll.value = true;
	}
});
/* 调用 store 的方法 */
function getEvents(date: Date) {
	return scheduleStore.getMonthEvents(date, calendar.value);
}
function getWeekEvents(date: Date, hour: number) {
	return scheduleStore.getWeekEvents(date, hour, calendar.value);
}
function getDayEvents(date: Date, hour: number) {
	return scheduleStore.getDayEvents(date, hour, calendar.value);
}
</script>

<style scoped>
.statistics-row :deep(.statistics) {
	margin: 10px;
}

.content-row {
	margin: 10px;
}

.calendar-tabs {
	width: 100%;
}
</style>
