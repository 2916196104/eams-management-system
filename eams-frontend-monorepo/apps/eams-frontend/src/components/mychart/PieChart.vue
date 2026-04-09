<template>
	<!-- 饼图容器 -->
	<div ref="chartRef" class="pie-chart"></div>
</template>

<script setup lang="ts">
import { ref, onMounted, watch, onUnmounted } from "vue"; // 引入Vue的响应式ref、挂载钩子、监听钩子、卸载钩子
import * as echarts from "echarts/core"; // 引入ECharts核心模块
import { PieChart } from "echarts/charts"; // 引入饼图组件
import { TitleComponent, TooltipComponent, LegendComponent } from "echarts/components"; // 引入标题、提示框、图例组件
import { LabelLayout, UniversalTransition } from "echarts/features"; // 引入标签布局、通用过渡动画
import { CanvasRenderer } from "echarts/renderers"; // 引入Canvas渲染器
import type { PieChartProps, ChartEvents } from "./type"; // 引入饼图属性类型和事件类型

echarts.use([
	TitleComponent, //引入标题组件
	TooltipComponent, //引入提示框组件
	LegendComponent, //引入图例组件
	PieChart, //引入饼图组件
	LabelLayout, //引入标签布局组件
	UniversalTransition, //引入通用过渡动画组件
	CanvasRenderer, //引入Canvas渲染器
]);

// 定义组件属性props
const props = withDefaults(defineProps<PieChartProps>(), {
	title: "", // 饼图标题
	seriesData: () => [], // 饼图数据
	theme: "light", // 图表主题
	radius: "60%", // 饼图半径
	roseType: false, // 是否显示玫瑰类型
	showLabel: true, // 是否显示标签
	height: "100%", // 图表高度
	width: "100%", // 图表宽度
});

// 定义组件的事件，设置默认值
const emit = defineEmits<ChartEvents>(); // 引入事件类型

const chartRef = ref<HTMLElement>(); //抓取DOM元素//
let chartInstance: echarts.ECharts | null = null; //初始化图表实例//

// 定义默认颜色数组
const defaultColors = ["#5470c6", "#91cc75", "#fac858", "#ee6666", "#73c0de", "#3ba272", "#fc8452", "#9a60b4"];

// 初始化图表
function initChart() {
	if (!chartRef.value) return; //检查DOM是否存在

	chartInstance = echarts.init(chartRef.value, props.theme); //初始化图表实例//

	// 绑定点击事件（确保 chartInstance 存在）
	chartInstance.on("click", handleChartClick); //绑定点击事件//

	renderChart(); //渲染图表//
	emit("chart-ready", chartInstance); //触发图表准备事件//
}

// 渲染图表
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
			trigger: "item",
			backgroundColor: "rgba(255, 255, 255, 0.95)",
			borderColor: "#ddd",
			borderWidth: 1,
			textStyle: {
				color: "#333",
			},
		},

		// 3. 图例配置
		legend: {
			orient: "vertical",
			right: "10%",
			top: "center",
		},

		// 4. 网格配置（图表区域）
		grid: {
			left: "3%",
			right: "4%",
			bottom: "3%",
			top: props.title ? 60 : 30,
			containLabel: true,
		},

		// 5. 系列配置（饼图数据）
		series: [
			{
				name: props.title || "数据",
				type: "pie",
				radius: props.radius,
				roseType: props.roseType,
				center: ["40%", "50%"],
				avoidLabelOverlap: true,
				itemStyle: {
					borderRadius: 8,
					borderColor: "#fff",
					borderWidth: 2,
				},
				label: props.showLabel
					? {
							show: true,
							formatter: "{b}: {c} ({d}%)",
						}
					: { show: false },
				emphasis: {
					label: {
						show: true,
						fontSize: 14,
						fontWeight: "bold",
					},
					itemStyle: {
						shadowBlur: 10,
						shadowOffsetX: 0,
						shadowColor: "rgba(0, 0, 0, 0.5)",
					},
				},
				labelLine: props.showLabel // 是否显示标签线
					? {
							show: true,
							smooth: true,
						}
					: { show: false },
				data: props.seriesData.map((item, index) => ({
					...item,
					itemStyle: {
						color: item.color || defaultColors[index % defaultColors.length],
					},
				})),
			},
		],
	};

	chartInstance.setOption(option, true); //设置图表选项//
}

function handleResize() {
	chartInstance?.resize();
}

// 监听属性变化，重新渲染图表
watch(
	() => [props.seriesData, props.title, props.radius, props.roseType, props.showLabel],
	() => {
		renderChart();
	},
	{ deep: true },
);

// 处理点击事件
function handleChartClick(params: any) {
	emit("click", params);
}

// 组件挂载时初始化图表
onMounted(() => {
	initChart(); //初始化图表//
	window.addEventListener("resize", handleResize); //添加窗口resize事件监听//
});

// 组件卸载时移除事件监听和销毁图表实例
onUnmounted(() => {
	window.removeEventListener("resize", handleResize);
	if (chartInstance) {
		chartInstance.dispose();
		chartInstance = null;
	}
});

// 暴露图表实例和方法，用于外部调用
defineExpose({
	getChartInstance: () => chartInstance, // 获取图表实例
	refresh: () => renderChart(), // 刷新图表
	resize: () => handleResize(), // 调整图表大小
});
</script>

<style scoped>
.pie-chart {
	width: 100%;
	height: 100%;
	min-height: 300px;
}
</style>
