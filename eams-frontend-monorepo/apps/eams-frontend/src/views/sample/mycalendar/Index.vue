<template>
	<section class="root-container">
		<my-calendar
			title="课程表(预约管理、预约管理)"
			:year="currentYear"
			:month="currentMonth"
			v-model:selected-date="selectedDate"
			@date-select="onDateSelect"
		/>
	</section>
</template>

<script setup lang="ts">
import { ref, onMounted } from "vue";
import MyCalendar from "@/components/mycalendar/MyCalendar.vue";

const currentYear = ref(2026);
const currentMonth = ref(2);
const selectedDate = ref<Date | null>(new Date(2026, 2, 12));

onMounted(() => {
	// 可选：首次打开时使用当前年月与今天，便于日常测试
	// currentYear.value = new Date().getFullYear()
	// currentMonth.value = new Date().getMonth()
	// selectedDate.value = new Date()
});

function onDateSelect(date: Date) {
	console.log("选中日期", date);
}
</script>

<style scoped>
.root-container {
	width: 100%;
	padding: 10px;
	box-sizing: border-box;
}
</style>
