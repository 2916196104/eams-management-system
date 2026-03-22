<template>
	<!-- 柱状图组件 -->
	<div ref="chartRef" class="bar-chart"></div>
</template>

<script setup lang="ts">
import { ref, onMounted, watch, onUnmounted } from "vue"; // 引入vue的响应式ref、挂载、监听、卸载函数
import * as echarts from "echarts/core"; // 引入echarts的核心模块
import { BarChart } from "echarts/charts"; // 引入柱状图组件
import {
	TitleComponent, // 引入标题组件
	TooltipComponent, // 引入提示组件
	GridComponent, // 引入网格组件
	LegendComponent, // 引入图例组件
} from "echarts/components";
import { LabelLayout, UniversalTransition } from "echarts/features"; // 引入标签布局和通用转换功能
import { CanvasRenderer } from "echarts/renderers"; // 引入canvas渲染器
import type { BarChartProps, ChartEvents } from "./type"; // 引入柱状图组件的属性类型和事件类型

//注册echarts组件
echarts.use([
	TitleComponent, // 引入标题组件
	TooltipComponent, // 引入提示组件
	GridComponent, // 引入网格组件
	LegendComponent, // 引入图例组件
	BarChart, // 引入柱状图组件
	LabelLayout, // 引入标签布局功能
	UniversalTransition, // 引入通用转换功能
	CanvasRenderer, // 引入canvas渲染器
]);
// 定义组件的属性，设置默认值
const props = withDefaults(defineProps<BarChartProps>(), {
	title: "", // 标题
	xAxisData: () => [], // X轴数据
	seriesData: () => [], // 数据系列
	theme: "light", // 主题
	horizontal: false, // 是否水平柱状图
	showLabel: true, // 是否显示标签 （默认显示）
	height: "100%", // 高度
	width: "100%", // 宽度
});

// 定义组件的事件，设置默认值
const emit = defineEmits<ChartEvents>(); // 引入事件类型

const chartRef = ref<HTMLElement>(); // DOM元素引入图表实例的引用
let chartInstance: echarts.ECharts | null = null; // 引入图表实例

// 默认颜色数组
const defaultColors = ["#5470c6", "#91cc75", "#fac858", "#ee6666", "#73c0de", "#3ba272", "#fc8452", "#9a60b4"];

// 初始化图表
function initChart() {
	if (!chartRef.value) return; // 如果图表实例不存在，返回

	chartInstance = echarts.init(chartRef.value, props.theme); // 初始化图表实例

	// 绑定点击事件（确保 chartInstance 存在）
	chartInstance.on("click", handleChartClick);

	renderChart(); // 渲染图表
	emit("chart-ready", chartInstance); // 触发图表准备事件，传递图表实例
}

// 渲染图表
function renderChart() {
	if (!chartInstance) return; // 如果图表实例不存在，返回

	const option = {
		// 1. 标题配置
		title: {
			text: props.title,
			left: "left",
			textStyle: {
				fontSize: 16,
				fontWeight: "bold",
			},
		},

		// 2. 提示组件配置
		tooltip: {
			trigger: "axis",
			axisPointer: {
				type: "shadow",
			},
			backgroundColor: "rgba(255, 255, 255, 0.95)",
			borderColor: "#ddd",
			borderWidth: 1,
			textStyle: {
				color: "#333",
			},
		},

		// 3. 图例配置
		legend: {
			data: props.seriesData.map((item) => item.name),
			top: 0,
			right: 10,
		},
		grid: {
			left: "3%",
			right: "4%",
			bottom: "3%",
			top: props.title ? 60 : 30,
			containLabel: true,
		},

		// 4. X轴配置
		xAxis: {
			type: props.horizontal ? "value" : "category",
			data: props.horizontal ? undefined : props.xAxisData,
			axisLine: {
				lineStyle: {
					color: "#ddd",
				},
			},
			axisLabel: {
				color: "#666",
			},
		},

		// 5. Y轴配置
		yAxis: {
			type: props.horizontal ? "category" : "value",
			data: props.horizontal ? props.xAxisData : undefined,
			splitLine: {
				lineStyle: {
					color: "#f0f0f0",
					type: "dashed",
				},
			},
			axisLine: {
				show: false,
			},
			axisTick: {
				show: false,
			},
			axisLabel: {
				color: "#666",
			},
		},

		// 6. 数据系列配置
		series: props.seriesData.map((item, index) => {
			const color = item.color || defaultColors[index % defaultColors.length];
			return {
				name: item.name,
				type: "bar",
				data: item.data,
				barWidth: "40%",
				itemStyle: {
					color: color,
					borderRadius: [4, 4, 0, 0],
				},
				label: props.showLabel
					? {
							show: true,
							position: props.horizontal ? "right" : "top",
							color: color,
						}
					: undefined,
			};
		}),
	};

	chartInstance.setOption(option, true); // 设置图表选项，合并配置项
}

// 处理图表大小调整事件
function handleResize() {
	chartInstance?.resize(); //
}

//监听属性变化，实时更新图表
watch(
	() => [props.xAxisData, props.seriesData, props.title, props.horizontal, props.showLabel],
	() => {
		renderChart(); // 渲染图表
	},
	{ deep: true }, // 深度监听属性变化
);

// 处理图表点击事件
function handleChartClick(params: any) {
	emit("click", params);
}

//生命钩子函数，在组件挂载时初始化图表和事件监听
onMounted(() => {
	initChart(); //挂载时初始化图表
	window.addEventListener("resize", handleResize); // 挂载时添加窗口大小调整事件监听
});

//组件卸载时移除事件监听和释放图表实例
onUnmounted(() => {
	window.removeEventListener("resize", handleResize); // 组件卸载时移除窗口大小调整事件监听
	if (chartInstance) {
		chartInstance.dispose(); // 组件卸载时释放图表实例
		chartInstance = null;
	}
});

//暴露的方法
// 1. getChartInstance: 返回图表实例，用于调用 echarts 提供的方法
// 2. refresh: 刷新图表，重新渲染数据
// 3. resize: 处理图表大小调整事件，重新调整图表大小
defineExpose({
	getChartInstance: () => chartInstance,
	refresh: () => renderChart(),
	resize: () => handleResize(),
});
</script>

<style scoped>
.bar-chart {
	width: 100%;
	height: 100%;
	min-height: 300px;
}
</style>
