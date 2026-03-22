<template>
	<section class="stats-page">
		<section class="chart-card">
			<div class="card-header">
				<h3>本月报名趋势</h3>
				<el-date-picker
					v-model="trendRange"
					type="daterange"
					range-separator="至"
					start-placeholder="开始日期"
					end-placeholder="结束日期"
					value-format="YYYY-MM-DD"
				/>
			</div>
			<line-chart
				title="本月报名趋势"
				:x-axis-data="saleTrendXAxis"
				:series-data="saleTrendSeries"
				height="360px"
				:show-area="true"
			/>
		</section>

		<section class="chart-card">
			<div class="card-header">
				<h3>课程历史总销量</h3>
				<el-date-picker
					v-model="courseRange"
					type="daterange"
					range-separator="至"
					start-placeholder="开始日期"
					end-placeholder="结束日期"
					value-format="YYYY-MM-DD"
				/>
			</div>
			<bar-chart
				title="课程历史总销量"
				:x-axis-data="courseSalesXAxis"
				:series-data="courseSalesSeries"
				height="360px"
				:show-label="true"
			/>
		</section>
	</section>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import LineChart from '@/components/mychart/LineChart.vue'
import BarChart from '@/components/mychart/BarChart.vue'
import {
	courseSalesSeries,
	courseSalesXAxis,
	saleTrendSeries,
	saleTrendXAxis
} from '@/views/finance/shared'

const trendRange = ref(['2026-03-01', '2026-03-31'])
const courseRange = ref(['2026-01-01', '2026-03-31'])
</script>

<style scoped>
.stats-page {
	padding: 16px;
	display: flex;
	flex-direction: column;
	gap: 16px;
}

.chart-card {
	background: #fff;
	border-radius: 6px;
	padding: 20px;
}

.card-header {
	display: flex;
	justify-content: space-between;
	align-items: center;
	gap: 16px;
	margin-bottom: 16px;
}

.card-header h3 {
	margin: 0;
	font-size: 24px;
	color: #111827;
}

@media (max-width: 960px) {
	.card-header {
		flex-direction: column;
		align-items: stretch;
	}
}
</style>
