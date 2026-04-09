<template>
	<el-card class="panel-card" shadow="never">
		<template #header>
			<div class="panel-header">
				<div class="panel-title">学员课时数排行(前20)</div>
				<CompactDateRange
					:start-date="startDate"
					:end-date="endDate"
					:disabled="loadingRank"
					size="small"
					@change="onRangeChange"
				/>
			</div>
		</template>
		<div class="panel-body">
			<el-skeleton v-if="loadingRank" :rows="6" animated />
			<BarChart
				v-else
				:title="'学员课时数排行(前20)'"
				:x-axis-data="classHourRank?.xAxisData ?? []"
				:series-data="classHourRank?.seriesData ?? []"
				:show-label="true"
			/>
		</div>
	</el-card>
</template>

<script setup lang="ts">
import BarChart from "@/components/mychart/BarChart.vue";
import CompactDateRange from "@/components/common/CompactDateRange.vue";
import type { ClassHourRankResult } from "@/apis/data/studentStatistics";

const props = defineProps<{
	classHourRank: ClassHourRankResult | null;
	loadingRank: boolean;
	startDate: string;
	endDate: string;
}>();

const emit = defineEmits<{
	(e: "change-range", payload: { startDate: string; endDate: string }): void;
}>();

function onRangeChange(payload: { startDate: string; endDate: string }) {
	emit("change-range", payload);
}
</script>

<style scoped>
.panel-card {
	width: 100%;
}

.panel-header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.panel-title {
	font-weight: 700;
}

.panel-body {
	padding-top: 8px;
	height: 340px;
}
</style>

