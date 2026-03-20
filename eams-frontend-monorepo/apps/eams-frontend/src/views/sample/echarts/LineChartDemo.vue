<template>
	<div class="line-chart-demo">
		<h2>图表组件综合示例</h2>

		<div class="chart-container">
			<h3>报名趋势图(平滑曲线)</h3>
			<LineChart
				title="本月报名走势"
				:x-axis-data="['03-10', '03-11', '03-12', '03-13', '03-14']"
				:series-data="registrationData"
				height="400px"
				@click="handleChartClick"
			/>
		</div>

		<div class="chart-container">
			<h3>单条折线-区域填充</h3>
			<LineChart
				title="用户增长趋势"
				:x-axis-data="['1月', '2月', '3月', '4月', '5月', '6月']"
				:series-data="singleSeries"
				height="400px"
				:showArea="true"
			/>
		</div>

		<div class="chart-container">
			<h3>多条折线对比</h3>
			<LineChart
				title="月度销售对比"
				:x-axis-data="['1月', '2月', '3月', '4月', '5月', '6月']"
				:series-data="multiSeries"
				height="400px"
				@click="handleChartClick"
			/>
		</div>

		<div class="chart-container">
			<h3>柱状图示例</h3>
			<BarChart
				title="部门业绩对比"
				:x-axis-data="['销售部', '技术部', '运营部', '市场部']"
				:series-data="barData"
				height="400px"
				:show-label="true"
			/>
		</div>

		<div class="chart-container">
			<h3>饼图示例</h3>
			<PieChart title="手机销量" :series-data="pieData" height="400px" />
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import LineChart from "@/components/mychart/LineChart.vue";
import BarChart from "@/components/mychart/BarChart.vue";
import PieChart from "@/components/mychart/PieChart.vue";

// 1. 报名趋势图数据
const registrationData = ref([
	{
		name: "报名人数",
		data: [1200000, 880000, 1296957.12, 950000, 325439],
		color: "#5470c6",
	},
]);

const singleSeries = ref([
	{
		name: "新增用户",
		data: [120, 200, 150, 80, 70, 110],
		color: "#5470c6",
	},
]);

// 多条折线对比数据 ref定义对象数据
const multiSeries = ref([
	{
		name: "产品A",
		data: [820, 932, 901, 934, 1290, 1330],
		color: "#5470c6",
	},
	{
		name: "产品B",
		data: [620, 732, 701, 734, 1090, 1130],
		color: "#91cc75",
	},
	{
		name: "产品C",
		data: [420, 532, 501, 534, 890, 930],
		color: "#fac858",
	},
]);

const barData = ref([
	{
		name: "第一季度",
		data: [320, 280, 350, 240],
		color: "#5470c6",
	},
	{
		name: "第二季度",
		data: [380, 320, 400, 290],
		color: "#91cc75",
	},
]);

const pieData = ref([
	{ name: "小米", value: 1041, color: "#5470c6" },
	{ name: "华为", value: 735, color: "#fac858" },
	{ name: "OPPO", value: 500, color: "#ee6666" },
	{ name: "魅族", value: 300, color: "#73c0de" },
]);

function handleChartClick(params: any) {
	console.log("图表点击事件:", params);
}
</script>

<style scoped>
.line-chart-demo {
	padding: 20px;
}

.chart-container {
	margin-bottom: 40px;
	border: 1px solid #e0e0e0;
	border-radius: 8px;
	padding: 20px;
}

h2,
h3 {
	margin-bottom: 20px;
}
</style>
