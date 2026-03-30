<template>
	<div ref="chartRef" class="funnel-chart"></div>
</template>

<script setup lang="ts">
import { ref, onMounted, onUnmounted, watch } from "vue";
import * as echarts from "echarts/core";
import { FunnelChart as EChartsFunnel } from "echarts/charts";
import { TitleComponent, TooltipComponent, LegendComponent } from "echarts/components";
import { CanvasRenderer } from "echarts/renderers";
import type { ChartEvents } from "./type";

echarts.use([TitleComponent, TooltipComponent, LegendComponent, EChartsFunnel, CanvasRenderer]);

export interface FunnelSeriesItem {
	name: string;
	value: number;
	color?: string;
}

export interface FunnelChartProps {
	title?: string;
	theme?: "light" | "dark";
	seriesData: FunnelSeriesItem[];
	height?: number | string;
	width?: number | string;
	showLabel?: boolean;
}

const props = withDefaults(defineProps<FunnelChartProps>(), {
	title: "",
	theme: "light",
	seriesData: () => [],
	showLabel: true,
	height: "100%",
	width: "100%",
});

const emit = defineEmits<ChartEvents>();

const chartRef = ref<HTMLElement>();
let chartInstance: echarts.ECharts | null = null;

function renderChart() {
	if (!chartInstance) return;
	const maxValue = Math.max(...props.seriesData.map((item) => item.value), 1);

	const option = {
		title: {
			text: props.title,
			left: "left",
			textStyle: { fontSize: 16, fontWeight: "bold" },
		},
		tooltip: {
			trigger: "item",
			backgroundColor: "rgba(255, 255, 255, 0.95)",
			borderColor: "#ddd",
			borderWidth: 1,
			textStyle: { color: "#333" },
		},
		legend: {
			show: true,
			top: props.title ? 44 : 12,
			left: "center",
		},
		series: [
			{
				type: "funnel",
				name: props.title || "数据",
				left: "10%",
				right: "10%",
				top: props.title ? 84 : 40,
				bottom: 16,
				width: "80%",
				min: 0,
				max: maxValue,
				sort: "none",
				orient: "vertical",
				gap: 2,
				label: props.showLabel
					? {
							show: true,
							position: "inside",
							color: "#ffffff",
							fontSize: 16,
							fontWeight: "bold",
							formatter: (p: any) => `${p.name}`,
						}
					: { show: false },
				labelLine: {
					show: false,
				},
				itemStyle: {
					borderWidth: 1,
					borderColor: "#f4f4f4",
					borderRadius: 2,
				},
				data: props.seriesData.map((item) => ({
					name: item.name,
					value: item.value,
					itemStyle: {
						color: item.color,
					},
				})),
			},
		],
	};

	chartInstance.setOption(option, true);
}

function initChart() {
	if (!chartRef.value) return;
	chartInstance = echarts.init(chartRef.value, props.theme);
	chartInstance.on("click", (params: any) => emit("click", params));
	renderChart();
	emit("chart-ready", chartInstance);
}

function handleResize() {
	chartInstance?.resize();
}

watch(
	() => [props.title, props.theme, props.seriesData, props.showLabel],
	() => renderChart(),
	{ deep: true },
);

onMounted(() => {
	initChart();
	window.addEventListener("resize", handleResize);
});

onUnmounted(() => {
	window.removeEventListener("resize", handleResize);
	chartInstance?.dispose();
	chartInstance = null;
});

defineExpose({
	refresh: () => renderChart(),
	resize: () => handleResize(),
	getChartInstance: () => chartInstance,
});
</script>

<style scoped>
.funnel-chart {
	width: 100%;
	height: 100%;
	min-height: 320px;
}
</style>

