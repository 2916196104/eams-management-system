<template>
	<!-- 折线图容器 -->
	<div ref="chartRef" class="line-chart"></div>
</template>

<script setup lang="ts">
import { ref, onMounted, watch, onUnmounted } from "vue"; // 引入vue的响应式ref、挂载钩子、监听钩子、卸载钩子
import * as echarts from "echarts/core"; // 引入echarts核心模块
import { LineChart } from "echarts/charts"; // 引入折线图模块
import {
	// 引入组件模块
	TitleComponent, // 引入标题组件
	TooltipComponent, // 引入提示组件
	GridComponent, // 引入网格组件
	LegendComponent, // 引入图例组件
} from "echarts/components";
import { LabelLayout, UniversalTransition } from "echarts/features";
import { CanvasRenderer } from "echarts/renderers";
import type { LineChartProps, ChartEvents } from "./type"; // 引入图表属性和事件类型

//注册Echarts组件
echarts.use([
	TitleComponent, // 标题组件
	TooltipComponent, // 提示框组件
	GridComponent, // 网格组件
	LegendComponent, // 图例组件
	LineChart, // 折线图
	LabelLayout, // 标签布局
	UniversalTransition, // 过渡动画
	CanvasRenderer, // Canvas 渲染器
]);

const props = withDefaults(defineProps<LineChartProps>(), {
	title: "", // 图表标题
	xAxisData: () => [], // X轴数据
	seriesData: () => [], // Y轴数据
	theme: "light", // 主题
	showSymbol: true, // 是否显示数据点
	smooth: true, // 是否平滑曲线
	showArea: false, // 是否显示区域填充
	showLabel: false, // 是否显示数据标签
	height: "100%", // 高度
	width: "100%", // 宽度
});
//定义组件触发事件
const emit = defineEmits<ChartEvents>();

const chartRef = ref<HTMLElement>(); // DOM 引用
let chartInstance: echarts.ECharts | null = null; // 图表实例

// 默认颜色数组
const defaultColors = ["#5470c6", "#91cc75", "#fac858", "#ee6666", "#73c0de", "#3ba272", "#fc8452", "#9a60b4"];

function initChart() {
	if (!chartRef.value) return; //检查DOM是否存在
	//初始化图表实例
	chartInstance = echarts.init(chartRef.value, props.theme);

	// 绑定点击事件（确保 chartInstance 存在）
	chartInstance.on("click", handleChartClick);

	//渲染图表
	renderChart();

	//触发图表准备事件
	emit("chart-ready", chartInstance);
}

function renderChart() {
	if (!chartInstance) return; //检查图表实例是否存在
	// 配置图表选项

	const option = {
		// 1.标题配置
		title: {
			text: props.title,
			left: "left",
			textStyle: {
				fontSize: 16,
				fontWeight: "bold",
			},
		},

		// 2. 提示框配置
		tooltip: {
			trigger: "axis",
			backgroundColor: "rgba(255, 255, 255, 0.95)",
			borderColor: "#ddd",
			borderWidth: 1,
			textStyle: {
				color: "#333",
			},
		},

		//3.图例配置
		legend: {
			data: props.seriesData.map((item) => item.name),
			top: 0,
			right: 10,
		},

		// 4. 网格配置（图表区域）
		grid: {
			left: "3%",
			right: "4%",
			bottom: "3%",
			top: props.title ? 60 : 30,
			containLabel: true,
		},
		// 5. X轴配置
		xAxis: {
			type: "category",
			boundaryGap: false,
			data: props.xAxisData,
			axisLine: {
				lineStyle: {
					color: "#ddd",
				},
			},
			axisLabel: {
				color: "#666",
			},
		},

		// 6. Y轴配置
		yAxis: {
			type: "value",
			splitLine: {
				lineStyle: {
					color: "#f0f0f0",
					type: "dashed",
				},
			},
			axisLine: { show: false },
			axisTick: { show: false },
			axisLabel: { color: "#666" },
		},
		// 7. 数据系列配置
		series: props.seriesData.map((item, index) => {
			const color = item.color || defaultColors[index % defaultColors.length];
			return {
				name: item.name,
				type: "line",
				data: item.data,
				smooth: props.smooth,
				showSymbol: props.showSymbol,
				symbol: "circle",
				symbolSize: 6,
				lineStyle: {
					width: 3,
					color: color,
				},
				itemStyle: {
					color: color,
					borderWidth: 2,
					borderColor: "#fff",
				},
				label: props.showLabel // 是否显示数据标签
					? {
							show: true,
							position: "top",
							color: color,
						}
					: undefined,
				areaStyle: props.showArea // 是否显示区域填充
					? {
							color: new echarts.graphic.LinearGradient(0, 0, 0, 1, [
								{ offset: 0, color: color + "30" },
								{ offset: 1, color: color + "05" },
							]),
						}
					: undefined,
			};
		}),
	};
	// 设置配置到图表
	chartInstance.setOption(option, true);
}

// 处理窗口调整大小事件
function handleResize() {
	chartInstance?.resize();
}

// 监听属性变化，重新渲染图表
watch(
	() => [
		props.xAxisData,
		props.seriesData,
		props.title,
		props.showSymbol,
		props.smooth,
		props.showArea,
		props.showLabel,
	],
	() => {
		renderChart();
	},
	{ deep: true }, // 深度监听
);

// 组件挂载后
onMounted(() => {
	initChart();
	window.addEventListener("resize", handleResize);
});

// 组件卸载前
onUnmounted(() => {
	window.removeEventListener("resize", handleResize);
	if (chartInstance) {
		chartInstance.dispose(); // 销毁图表，释放内存
		chartInstance = null;
	}
});

// 点击事件处理
function handleChartClick(params: any) {
	emit("click", params);
}

// 暴露方法
defineExpose({
	getChartInstance: () => chartInstance, // 获取图表实例
	refresh: () => renderChart(), // 刷新图表
	resize: () => handleResize(), // 调整大小
});
</script>

<style scoped>
.line-chart {
	width: 100%;
	height: 100%;
	min-height: 300px;
}
</style>
