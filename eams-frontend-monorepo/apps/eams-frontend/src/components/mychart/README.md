# MyChart 图表组件库

基于 ECharts 5 封装的 Vue 3 + TypeScript 图表组件库，提供简洁、易用的图表组件。

## 组件列表

- **LineChart** - 折线图组件
- **BarChart** - 柱状图组件
- **PieChart** - 饼图组件

## 快速开始

### 导入组件

```typescript
import LineChart from "@/components/mychart/LineChart.vue";
import BarChart from "@/components/mychart/BarChart.vue";
import PieChart from "@/components/mychart/PieChart.vue";
```

## LineChart 折线图

```vue
<LineChart 引入对应属性即可使用></LineChart>
```

### 基本用法

```vue
<template>
	<LineChart
		title="本月报名走势"
		:x-axis-data="xAxisData"
		:series-data="seriesData"
		height="400px"
		:show-label="true"
		@click="handleChartClick"
	/>
</template>

<script setup lang="ts">
import { ref } from "vue";
import LineChart from "@/components/mychart/LineChart.vue";

const xAxisData = ref(["03-10", "03-11", "03-12", "03-13", "03-14"]);
const seriesData = ref([
	{
		name: "报名人数",
		data: [122205, 880000, 1296957.12, 950000, 325439],
		color: "#5470c6",
	},
]);
//需要自行绑定点击事件
function handleChartClick(params: any) {
	console.log("图表点击:", params);
}
</script>
```

### 属性说明

| 属性       | 类型              | 默认值  | 说明             |
| ---------- | ----------------- | ------- | ---------------- |
| title      | string            | ''      | 图表标题         |
| xAxisData  | Array             | \[]     | X 轴数据         |
| seriesData | Array             | \[]     | Y 轴系列数据     |
| theme      | 'light' \| 'dark' | 'light' | 主题             |
| showSymbol | boolean           | true    | 是否显示数据点   |
| smooth     | boolean           | true    | 是否平滑曲线     |
| showArea   | boolean           | false   | 是否显示区域填充 |
| showLabel  | boolean           | false   | 是否显示数据标签 |
| height     | string \| number  | '100%'  | 图表高度         |
| width      | string \| number  | '100%'  | 图表宽度         |

### 事件

| 事件名      | 参数   | 说明           |
| ----------- | ------ | -------------- |
| chart-ready | chart  | 图表初始化完成 |
| click       | params | 点击图表       |

### 暴露方法

| 方法名             | 说明              |
| ------------------ | ----------------- |
| getChartInstance() | 获取 ECharts 实例 |
| refresh()          | 刷新图表          |
| resize()           | 调整图表大小      |

## BarChart 柱状图

### 基本用法

```vue
<template>
	<BarChart title="月度销售统计" :x-axis-data="xAxisData" :series-data="seriesData" height="400px" :show-label="true" />
</template>

<script setup lang="ts">
import { ref } from "vue";
import BarChart from "@/components/mychart/BarChart.vue";

const xAxisData = ref(["1月", "2月", "3月", "4月", "5月", "6月"]);
const seriesData = ref([
	{
		name: "销售额",
		data: [820, 932, 901, 934, 1290, 1330],
		color: "#5470c6",
	},
]);
</script>
```

### 属性说明

| 属性       | 类型              | 默认值  | 说明             |
| ---------- | ----------------- | ------- | ---------------- |
| title      | string            | ''      | 图表标题         |
| xAxisData  | Array             | \[]     | X 轴数据         |
| seriesData | Array             | \[]     | Y 轴系列数据     |
| theme      | 'light' \| 'dark' | 'light' | 主题             |
| horizontal | boolean           | false   | 是否横向柱状图   |
| showLabel  | boolean           | false   | 是否显示数据标签 |
| height     | string \| number  | '100%'  | 图表高度         |
| width      | string \| number  | '100%'  | 图表宽度         |

### 事件和方法

同 LineChart 组件。

## PieChart 饼图

### 基本用法

```vue
<template>
	<PieChart title="订单来源分布" :series-data="seriesData" height="400px" />
</template>

<script setup lang="ts">
import { ref } from "vue";
import PieChart from "@/components/mychart/PieChart.vue";

const seriesData = ref([
	{ name: "直接访问", value: 335 },
	{ name: "邮件营销", value: 310 },
	{ name: "联盟广告", value: 234 },
	{ name: "视频广告", value: 135 },
	{ name: "搜索引擎", value: 1548 },
]);
</script>
```

### 属性说明

| 属性       | 类型                        | 默认值  | 说明               |
| ---------- | --------------------------- | ------- | ------------------ |
| title      | string                      | ''      | 图表标题           |
| seriesData | Array                       | \[]     | 数据系列           |
| theme      | 'light' \| 'dark'           | 'light' | 主题               |
| radius     | string \| \[string, string] | '60%'   | 饼图半径           |
| roseType   | boolean \| 'area'           | false   | 是否南丁格尔玫瑰图 |
| showLabel  | boolean                     | true    | 是否显示标签       |
| height     | string \| number            | '100%'  | 图表高度           |
| width      | string \| number            | '100%'  | 图表宽度           |

### 事件和方法

同 LineChart 组件。

# 后端数据交互

后期 axios 按需求编写 api

## &#x20;综合示例

```vue
<template>
	<div class="chart-demo">
		<h2>图表组件综合示例</h2>

		<div class="chart-card">
			<LineChart
				title="本月报名走势"
				:x-axis-data="['03-10', '03-11', '03-12', '03-13', '03-14']"
				:series-data="lineData"
				height="400px"
				:show-label="true"
			/>
		</div>

		<div class="chart-card">
			<BarChart
				title="部门业绩对比"
				:x-axis-data="['销售部', '技术部', '运营部', '市场部']"
				:series-data="barData"
				height="400px"
			/>
		</div>

		<div class="chart-card">
			<PieChart title="用户性别分布" :series-data="pieData" height="400px" />
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import LineChart from "@/components/mychart/LineChart.vue";
import BarChart from "@/components/mychart/BarChart.vue";
import PieChart from "@/components/mychart/PieChart.vue";

const lineData = ref([
	{
		name: "报名人数",
		data: [122205, 880000, 1296957.12, 950000, 325439],
		color: "#5470c6",
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
	{ name: "男性", value: 1048, color: "#5470c6" },
	{ name: "女性", value: 735, color: "#fac858" },
]);
</script>

<style scoped>
.chart-demo {
	padding: 20px;
}

.chart-card {
	margin-bottom: 30px;
	border: 1px solid #e0e0e0;
	border-radius: 8px;
	padding: 20px;
}
</style>
```
