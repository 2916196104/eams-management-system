<template>
	<el-card class="panel-card" shadow="never">
		<template #header>
			<div class="panel-header">
				<div class="panel-title">本月新线索走势</div>
				<CompactDateRange
					:start-date="startDate"
					:end-date="endDate"
					:disabled="loadingLead"
					size="small"
					@change="onRangeChange"
				/>
			</div>
		</template>
		<div class="panel-body">
			<el-skeleton v-if="loadingLead" :rows="6" animated />
			<LineChart v-else :title="'本月新线索走势'" :x-axis-data="leadTrend?.xAxisData ?? []" :series-data="leadTrend?.seriesData ?? []" :show-symbol="false" :smooth="true" />
		</div>
	</el-card>
</template>

<script setup lang="ts">
import LineChart from "@/components/mychart/LineChart.vue";
import CompactDateRange from "@/components/common/CompactDateRange.vue";
import type { LeadTrendResult } from "@/apis/data/studentStatistics";

const props = defineProps<{
	leadTrend: LeadTrendResult | null;
	loadingLead: boolean;
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
	height: 320px;
}
</style>

