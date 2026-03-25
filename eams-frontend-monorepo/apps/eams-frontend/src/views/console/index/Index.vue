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
			<!-- 预约课表 -->
			<el-card style="margin-top: 10px">
				<el-tabs v-model="reserveCalendar">
					<el-tab-pane label="预约课表" name="reserve">
						<my-calendar />
					</el-tab-pane>
				</el-tabs>
			</el-card>
		</el-col>
		<!-- 右侧 -->
		<el-col :span="8"></el-col>
	</el-row>
</template>

<script setup lang="ts">
import { ref, onMounted, computed, watch } from "vue";
import { useStatisticsStore, useScheduleStore } from "@/stores/console";
import Statistics from "@/components/statistics/Statistics.vue";
import MyCalendar from "@/components/mycalendar/MyCalendar.vue";
import CalendarText from "./components/CalendarText.vue";

/* store */
const statisticsStore = useStatisticsStore();
const scheduleStore = useScheduleStore();

/* 统计面板 */
const statisticsLoading = ref(true);
onMounted(async () => {
	await statisticsStore.fetchStatistics(); // 获取统计数据
	await scheduleStore.fetchMySchedule(); // 默认加载我的课表
	statisticsLoading.value = false;
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
		targetNumber: statisticsStore.totalCourses,
		iconName: "akar-icons:book",
		iconColor: "#36a3f7",
		hoverIconColor: "white",
		hoverBgColor: "#36a3f7",
	},
	{
		targetText: "本月报名数",
		targetNumber: statisticsStore.monthEnrollments,
		iconName: "hugeicons:money-bag-02",
		iconColor: "#f4516c",
		hoverIconColor: "white",
		hoverBgColor: "#f4516c",
	},
]);

/* 课表 */
const calendar = ref("my");
const reserveCalendar = ref("reserve");

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
