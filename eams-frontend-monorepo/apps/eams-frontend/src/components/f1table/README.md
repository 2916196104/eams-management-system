# 表格组件使用说明

此表格组件是对 Element Plus el-table 的封装，主要实现了分页、复选、操作栏等功能的配置化开发，**封装的主要思路是通过配置驱动表格渲染，减少重复的界面代码**，组件演示代码在 sample 中已经书写，可以自己运行观察效果。

## 1 整体使用步骤

### 1.1 导入组件

导入组件关键代码如下

```html
<script setup lang="ts">
	import F1Table from "@/components/f1table/F11Table.vue";
	import type { TableConfig } from "@/components/f1table/type";
	import { TableType } from "@/components/f1table/type";
</script>
```

### 1.2 类型定义

组件依赖的类型定义在 `type.ts` 中，主要包括以下类型：

#### 1.2.1 TableType 枚举

```js
export enum TableType {
	selection = "selection", // 复选列
	index = "index", // 序号列
	custom = "custom", // 自定义列（插槽）
	normal = "normal", // 普通列
	handler = "handler", // 操作列
}
```

#### 1.2.2 tableList 接口

```js
export interface tableList {
	type: string // 列类型，对应 TableType 枚举
	prop?: string // 列字段名
	label: string // 列标题
	width?: string // 列宽度
	slotName?: string // 自定义插槽名称（仅 custom 类型使用）
	[key: string]: any // 允许任意其他属性
}
```

#### 1.2.3 PaginationConfig 接口

```js
export interface PaginationConfig {
	enabled?: boolean // 是否启用分页
	currentPage?: number // 当前页码
	pageSize?: number // 每页条数
	pageSizes?: number[] // 可选每页条数
	total?: number // 数据总条数
	layout?: string // 分页布局
	onPageChange?: (page: number, size: number) => void // 分页变化回调
}
```

#### 1.2.4 HandlerConfig 接口

```js
export interface HandlerConfig {
	edit?: boolean // 是否显示编辑按钮
	delete?: boolean // 是否显示删除按钮
	view?: boolean // 是否显示查看按钮
	custom?: boolean // 是否显示自定义按钮
	editText?: string // 编辑按钮文本
	deleteText?: string // 删除按钮文本
	viewText?: string // 查看按钮文本
	onEdit?: (row: any) => void // 编辑点击回调
	onDelete?: (row: any) => void // 删除点击回调
	onView?: (row: any) => void // 查看点击回调
}
```

#### 1.2.5 TableConfig 接口

```js
export interface TableConfig {
	pageName?: string // 网络接口名称
	tableProperties?: object // el-table 属性配置
	tableList: tableList[] // 表格列配置
	pagination?: PaginationConfig // 分页配置
	handler?: HandlerConfig // 操作栏配置
	rowKey?: string // 行唯一标识字段
	loading?: boolean // 加载状态
	onSelectionChange?: (selection: any[]) => void // 复选变化回调
}
```

### 1.3 定义表格配置

使用表格组件需要定义 `TableConfig` 配置对象，包括表格列、分页、操作栏等。

```html
<script setup lang="ts">
	import { ref, reactive } from "vue";
	import F1Table from "@/components/f1table/F1Table.vue";
	import type { TableConfig } from "@/components/f1table/type";
	import { TableType } from "@/components/f1table/type";

	// 定义表格数据
	const tableData = ref<any[]>([]);

	// 定义表格配置
	const tableConfig = reactive<TableConfig>({
		// el-table 属性
		tableProperties: {
			stripe: true, // 斑马纹
			border: true, // 纵向边框
			height: 400, // 表格高度
		},
		// 表格列配置
		tableList: [
			{
				type: TableType.selection, // 复选列
				width: "50px",
				label: "选择",
				fixed: true,
			},
			{
				type: TableType.index, // 序号列
				width: "60px",
				label: "序号",
				fixed: true,
			},
			{
				type: TableType.normal, // 普通列
				label: "用户名",
				prop: "name",
				width: "120px",
			},
			{
				type: TableType.normal,
				label: "真实名",
				prop: "realname",
				width: "100px",
			},
			{
				type: TableType.custom, // 自定义列（需要插槽配合）
				label: "状态",
				prop: "enable",
				width: "80px",
				slotName: "status", // 插槽名称
			},
			{
				type: TableType.handler, // 操作列
				label: "操作",
				width: "180px",
				fixed: "right",
			},
		],
		// 分页配置
		pagination: {
			enabled: true,
			currentPage: 1,
			pageSize: 10,
			total: 0,
			pageSizes: [5, 10, 20, 50],
		},
		// 操作栏配置
		handler: {
			edit: true,
			delete: true,
			view: true,
			editText: "编辑",
			deleteText: "删除",
			viewText: "查看",
		},
		// 其他配置
		loading: false,
		rowKey: "id",
	});
</script>
```

### 1.4 绑定事件

表格组件支持以下事件：

```html
<script setup lang="ts">
	// 分页变化事件
	function handlePageChange(page: number, size: number) {
		console.log("分页变化:", page, size);
		// 重新加载数据
	}

	// 复选变化事件
	function handleSelectionChange(selection: any[]) {
		console.log("选中项:", selection);
	}

	// 操作按钮事件
	function handleEdit(row: any) {
		console.log("编辑:", row);
	}

	function handleDelete(row: any) {
		console.log("删除:", row);
	}

	function handleView(row: any) {
		console.log("查看:", row);
	}
</script>
```

### 1.5 编写组件标签

在 template 中编写组件标签，并绑定配置、数据和事件：

```html
<template>
	<F1Table
		:config="tableConfig"
		:data="tableData"
		@page-change="handlePageChange"
		@selection-change="handleSelectionChange"
		@edit="handleEdit"
		@delete="handleDelete"
		@view="handleView"
	>
		<!-- 自定义列插槽 -->
		<template #status="{ row }">
			<el-tag :type="row.enable === 1 ? 'success' : 'danger'">{{ row.enable === 1 ? "启用" : "禁用" }}</el-tag>
		</template>
		<!-- 操作栏额外按钮插槽 -->
		<template #handler-extra="{ row }">
			<el-button type="warning" link @click="handleCustom(row)">自定义</el-button>
		</template>
	</F1Table>
</template>
```

## 2 扩展功能

### 2.1 自定义列

当需要自定义某个单元格的显示内容时，可以使用 `custom` 类型的列配合插槽实现：

```html
<template>
	<F1Table :config="tableConfig" :data="tableData">
		<!-- 自定义列插槽，slotName 与列配置中的 slotName 一致 -->
		<template #status="{ row }">
			<el-tag :type="row.enable === 1 ? 'success' : 'danger'">{{ row.enable === 1 ? "启用" : "禁用" }}</el-tag>
		</template>
	</F1Table>
</template>
<script setup lang="ts">
	// 列配置
	const tableConfig = {
		tableList: [
			{
				type: TableType.custom,
				label: "状态",
				prop: "enable",
				slotName: "status", // 插槽名称
			},
		],
	};
</script>
```

### 2.2 复选功能

开启复选功能需要添加 `selection` 类型的列，并通过 `selection-change` 事件获取选中数据：

```html
<template>
	<F1Table :config="tableConfig" :data="tableData" @selection-change="handleSelectionChange">
		<template #tableList>
			<!-- 添加 selection 类型的列 -->
			{ type: TableType.selection, width: "50px", label: "选择", }
		</template>
	</F1Table>
</template>
<script setup lang="ts">
	const selectionData = ref<any[]>([]);

	function handleSelectionChange(selection: any[]) {
		selectionData.value = selection;
		console.log("选中项:", selection);
	}
</script>
```

### 2.3 操作栏

操作栏通过 `handler` 类型的列配置，支持查看、编辑、删除按钮：

```html
<script setup lang="ts">
	const tableConfig = {
		tableList: [
			{
				type: TableType.handler,
				label: "操作",
				width: "180px",
				fixed: "right",
			},
		],
		handler: {
			view: true, // 显示查看按钮
			edit: true, // 显示编辑按钮
			delete: true, // 显示删除按钮
			viewText: "查看",
			editText: "编辑",
			deleteText: "删除",
		},
	};
</script>
```

操作栏还支持自定义按钮，通过 `handler-extra` 插槽添加：

```html
<template>
	<F1Table :config="tableConfig" :data="tableData">
		<template #handler-extra="{ row }">
			<el-button type="warning" link @click="handleCustom(row)">自定义</el-button>
		</template>
	</F1Table>
</template>
```

### 2.4 分页功能

分页功能默认启用，可通过 `pagination` 配置进行自定义：

```html
<script setup lang="ts">
	const tableConfig = {
		pagination: {
			enabled: true, // 是否启用分页
			currentPage: 1, // 当前页码
			pageSize: 10, // 每页条数
			total: 0, // 数据总条数
			pageSizes: [5, 10, 20, 50], // 可选每页条数
			layout: "total, sizes, prev, pager, next, jumper", // 分页布局
		},
	};
</script>
```

分页变化时触发 `page-change` 事件：

```html
<template>
	<F1Table :config="tableConfig" :data="tableData" @page-change="handlePageChange" />
</template>
<script setup lang="ts">
	function handlePageChange(page: number, size: number) {
		console.log("当前页:", page, "每页条数:", size);
		// 重新请求数据
	}
</script>
```

### 2.5 加载状态

通过 `loading` 属性控制表格的加载状态：

```html
<script setup lang="ts">
	const tableConfig = reactive({
		loading: false,
	});

	// 加载数据时设置 loading
	function loadData() {
		tableConfig.loading = true;
		// 模拟接口请求
		setTimeout(() => {
			tableConfig.loading = false;
		}, 1000);
	}
</script>
```

### 2.6 行唯一标识

通过 `rowKey` 指定行数据的唯一标识字段，用于表格的展开行、树形数据等场景：

```html
<script setup lang="ts">
	const tableConfig = {
		rowKey: "id", // 指定唯一标识字段
	};
</script>
```

## 3 Mock 数据

组件提供了 mock 数据用于测试，位置在 `mock.ts`：

```js
import { getMockData, getAllMockData } from "@/components/f1table/mock";

// 分页获取 mock 数据
const result = getMockData(1, 10);
// 返回: { list: MockData[], total: number }

// 获取全部 mock 数据
const allData = getAllMockData();
// 返回: MockData[]
```

## 4 Props 汇总

| 属性名 | 类型        | 默认值 | 说明         |
| ------ | ----------- | ------ | ------------ |
| config | TableConfig | 必填   | 表格配置对象 |
| data   | any[]       | []     | 表格数据     |

## 5 Events 汇总

| 事件名           | 参数                         | 说明               |
| ---------------- | ---------------------------- | ------------------ |
| page-change      | (page: number, size: number) | 分页变化时触发     |
| selection-change | (selection: any[])           | 复选变化时触发     |
| edit             | (row: any)                   | 编辑按钮点击时触发 |
| delete           | (row: any)                   | 删除按钮点击时触发 |
| view             | (row: any)                   | 查看按钮点击时触发 |

## 6 Slots 汇总

| 插槽名        | 作用域          | 说明                   |
| ------------- | --------------- | ---------------------- |
| 自定义列插槽  | { row, $index } | 通过 slotName 属性指定 |
| handler-extra | { row, $index } | 操作栏额外按钮位置     |
