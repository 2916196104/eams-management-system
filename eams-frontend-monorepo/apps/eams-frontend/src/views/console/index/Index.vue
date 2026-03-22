<template>
	<div class="contain">
		<el-row class="statistics-row" v-if="!loading">
			<el-col v-for="item in statisticsList" :key="item.targetText" :xs="12" :sm="12" :md="6">
				<statistics v-bind="item" />
			</el-col>
		</el-row>
	</div>
</template>
<script setup lang="ts">
import { ref, onMounted, computed } from "vue";
import statistics from "@/components/statistics/statistics.vue";
import { useStatisticsStore } from "@/stores/console/statistics";
const statisticsStore = useStatisticsStore();
// 条件渲染
const loading = ref(true);
onMounted(async () => {
	await statisticsStore.fetchStatistics();
	loading.value = false;
});
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
</script>
<style lang="css" scoped>
.statistics-row :deep(.statistics) {
	margin: 10px;
}
</style>
