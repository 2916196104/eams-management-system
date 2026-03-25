<template>
	<div class="student-statistics-page">
		<el-alert v-if="store.error" class="error-alert" type="error" :closable="false" :title="store.error" />

		<el-row :gutter="16" class="section-row">
			<el-col :span="24">
				<StudentStatisticsFunnelAge
					:funnel-stages="store.funnelStages"
					:score-pie-data="store.scorePieData"
					:loading-funnel="store.loading.funnel"
					:loading-age="store.loading.age"
				/>
			</el-col>

			<el-col :span="24">
				<StudentStatisticsLeadTrend
					:lead-trend="store.leadTrend"
					:loading-lead="store.loading.leadTrend"
					:start-date="store.leadRange.startDate"
					:end-date="store.leadRange.endDate"
					@change-range="handleLeadRangeChange"
				/>
			</el-col>

			<el-col :span="24">
				<StudentStatisticsClassHourRank
					:class-hour-rank="store.classHourRank"
					:loading-rank="store.loading.classHourRank"
					:start-date="store.rankRange.startDate"
					:end-date="store.rankRange.endDate"
					@change-range="handleRankRangeChange"
				/>
			</el-col>
		</el-row>
	</div>
</template>

<script setup lang="ts">
import { onMounted } from "vue";
import { ElMessage } from "element-plus";
import { useStudentStatisticsStore } from "@/stores/data/studentStatistics";
import StudentStatisticsFunnelAge from "@/components/data/studentStatistics/StudentStatisticsFunnelAge.vue";
import StudentStatisticsLeadTrend from "@/components/data/studentStatistics/StudentStatisticsLeadTrend.vue";
import StudentStatisticsClassHourRank from "@/components/data/studentStatistics/StudentStatisticsClassHourRank.vue";

const store = useStudentStatisticsStore();

onMounted(async () => {
	store.initFilters();
	await handleQuery();
});

async function handleQuery() {
	try {
		await store.refreshAll();
	} catch (e) {
		const err = e as Error;
		ElMessage.error(err?.message || "查询失败");
	}
}

async function handleLeadRangeChange(payload: { startDate: string; endDate: string }) {
	store.setLeadRange(payload);
	try {
		await store.fetchLeadTrend();
	} catch (e) {
		const err = e as Error;
		ElMessage.error(err?.message || "更新走势失败");
	}
}

async function handleRankRangeChange(payload: { startDate: string; endDate: string }) {
	store.setRankRange(payload);
	try {
		await store.fetchClassHourRank();
	} catch (e) {
		const err = e as Error;
		ElMessage.error(err?.message || "更新排行失败");
	}
}
</script>

<style scoped>
.student-statistics-page {
	padding: 0 8px;
}

.error-alert {
	margin-bottom: 12px;
}

.section-row {
	padding-bottom: 16px;
}
</style>

