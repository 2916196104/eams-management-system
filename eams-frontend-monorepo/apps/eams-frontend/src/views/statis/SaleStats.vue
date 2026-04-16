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
					@change="loadTrendData"
				/>
			</div>
			<line-chart
				title="本月报名趋势"
				:x-axis-data="trendXAxis"
				:series-data="trendSeries"
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
					@change="loadCourseSalesData"
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
import { onMounted, ref } from "vue";
import { ElMessage } from "element-plus";
import LineChart from "@/components/mychart/LineChart.vue";
import BarChart from "@/components/mychart/BarChart.vue";
import { queryCourseSalesTotal, querySaleTrend } from "@/apis/finance";

const trendRange = ref(["2026-03-01", "2026-03-31"]);
const courseRange = ref(["2026-01-01", "2026-03-31"]);

const trendXAxis = ref<string[]>([]);
const trendSeries = ref([
	{ name: "报名数", data: [] as number[], color: "#3b82f6" },
	{ name: "收入", data: [] as number[], color: "#10b981" },
]);

const courseSalesXAxis = ref<string[]>([]);
const courseSalesSeries = ref([
	{ name: "报名数", data: [] as number[], color: "#f59e0b" },
	{ name: "收入", data: [] as number[], color: "#6366f1" },
]);

// 转换日期为ISO 8601格式
function formatDate(dateStr: string) {
	if (!dateStr) return undefined;
	const date = new Date(dateStr);
	// 设置为当天的开始时间
	date.setHours(0, 0, 0, 0);
	return date.toISOString();
}

async function loadTrendData() {
	try {
		const data = await querySaleTrend({
			startDate: formatDate(trendRange.value?.[0]),
			endDate: formatDate(trendRange.value?.[1]),
		});
		trendXAxis.value = data.map((item) => item.dates);
		trendSeries.value = [
			{ name: "报名数", data: data.map((item) => Number(item.totalCount || 0)), color: "#3b82f6" },
			{ name: "收入", data: data.map((item) => Number(item.totalAmount || 0)), color: "#10b981" },
		];
	} catch (error: any) {
		ElMessage.error(error?.message || "报名趋势加载失败");
	}
}

async function loadCourseSalesData() {
	try {
		const data = await queryCourseSalesTotal({
			startDate: formatDate(courseRange.value?.[0]),
			endDate: formatDate(courseRange.value?.[1]),
		});
		courseSalesXAxis.value = data.map((item) => item.courseName);
		courseSalesSeries.value = [
			{ name: "报名数", data: data.map((item) => Number(item.totalCount || 0)), color: "#f59e0b" },
			{ name: "收入", data: data.map((item) => Number(item.totalAmount || 0)), color: "#6366f1" },
		];
	} catch (error: any) {
		ElMessage.error(error?.message || "课程销量加载失败");
	}
}

onMounted(() => {
	loadTrendData();
	loadCourseSalesData();
});
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
