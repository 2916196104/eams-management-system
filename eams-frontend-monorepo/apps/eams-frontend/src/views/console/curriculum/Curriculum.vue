<template>
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
			<div v-for="item in getWeekEvents(date, hour)" :key="item.id">{{ item.courseName }} - {{ item.teacherName }}</div>
		</template>
		<!-- 日视图 -->
		<template #day-cell="{ date, hour }">
			<div v-for="item in getDayEvents(date, hour)" :key="item.id">{{ item.courseName }} - {{ item.teacherName }}</div>
		</template>
	</my-calendar>
</template>
<script setup lang="ts">
import { ref, onMounted } from "vue";
import { useScheduleStore } from "@/stores/console";
import CalendarText from "../../dashboard/components/CalendarText.vue";
const scheduleStore = useScheduleStore();
const calendar = ref();
/* 加载数据 */
onMounted(async () => {
	calendar.value = await scheduleStore.fetchAllSchedule();
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
<style lang="css" scoped></style>
