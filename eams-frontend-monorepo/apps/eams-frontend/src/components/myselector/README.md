# 人员选择器组件使用说明

人员选择器组件是一个通过点击输入框弹出选择面板的组件，支持搜索、分页、选择人员等功能。

## 组件特性

- 点击输入框弹出选择面板
- 实时搜索过滤（按姓名）
- 表格展示人员信息（序号、姓名、部门、手机号）
- 支持分页，可自定义每页显示条数
- 点击选择按钮将选中人员信息回填到输入框
- 支持静态数据和动态数据加载
- 点击外部区域自动关闭选择面板

## 基础使用

### 1. 导入组件

```html
<script setup lang="ts">
	import MyPersonSelector from "@/components/myselector/MyPersonSelector.vue";
	import type { PersonData } from "@/components/myselector/type";
</script>
```

### 2. 定义数据

```html
<script setup lang="ts">
	// 定义选中的人员数据
	const selectedPerson = ref<PersonData | null>(null);

	// 定义静态人员数据
	const personData = [
		{
			id: 1,
			name: "张三",
			department: "技术部",
			phone: "13800138001",
		},
		{
			id: 2,
			name: "李四",
			department: "产品部",
			phone: "13800138002",
		},
		{
			id: 3,
			name: "王五",
			department: "市场部",
			phone: "13800138003",
		},
		// ... 更多数据
	];
</script>
```

### 3. 使用组件

```html
<template>
	<!-- 使用静态数据 -->
	<my-person-selector
		v-model="selectedPerson"
		:data="personData"
		placeholder="请选择人员"
		search-placeholder="请输入姓名关键字搜索"
	/>
</template>
```

## 高级用法

### 1. 动态数据加载

如果需要从后端 API 动态加载数据，可以使用 `dataLoader` 属性：

```html
<script setup lang="ts">
	import { ref } from "vue";
	import MyPersonSelector from "@/components/myselector/MyPersonSelector.vue";
	import type { PersonData } from "@/components/myselector/type";

	const selectedPerson = ref<PersonData | null>(null);

	// 定义数据加载函数
	async function loadPersonData(): Promise<PersonData[]> {
		// 从API获取数据
		const response = await fetch("/api/persons");
		const data = await response.json();
		return data.map((item: any) => ({
			id: item.id,
			name: item.name,
			department: item.department,
			phone: item.phone,
		}));
	}
</script>

<template>
	<my-person-selector v-model="selectedPerson" :data-loader="loadPersonData" />
</template>
```

### 2. 自定义样式

可以通过属性自定义选择器的样式：

```html
<template>
	<my-person-selector
		v-model="selectedPerson"
		:data="personData"
		panel-width="600px"
		table-height="500px"
		:page-sizes="[5, 10, 20, 30]"
		:default-page-size="20"
	/>
</template>
```

### 3. 监听选择事件

```html
<script setup lang="ts">
	function handlePersonSelected(person: PersonData) {
		console.log("选中的人员:", person);
		// 在这里处理选中后的逻辑
	}
</script>

<template>
	<my-person-selector v-model="selectedPerson" :data="personData" @select="handlePersonSelected" />
</template>
```

### 4. 手动控制选择器

通过组件引用可以手动控制选择器的打开和关闭：

```html
<script setup lang="ts">
	const selectorRef = ref();

	function openSelector() {
		selectorRef.value.openSelector();
	}

	function closeSelector() {
		selectorRef.value.closeSelector();
	}

	function reload() {
		selectorRef.value.loadData();
	}
</script>

<template>
	<my-person-selector ref="selectorRef" v-model="selectedPerson" :data="personData" />
	<el-button @click="openSelector">打开选择器</el-button>
	<el-button @click="closeSelector">关闭选择器</el-button>
	<el-button @click="reload">重新加载数据</el-button>
</template>
```

## 组件属性

| 属性名            | 类型               | 默认值                 | 说明                       |
| ----------------- | ------------------ | ---------------------- | -------------------------- |
| modelValue        | PersonData \| null | null                   | v-model 绑定的选中人员数据 |
| placeholder       | string             | "请选择人员"           | 输入框占位符文本           |
| searchPlaceholder | string             | "请输入姓名关键字搜索" | 搜索框占位符文本           |
| panelWidth        | string             | "500px"                | 选择器面板宽度             |
| tableHeight       | string             | "400px"                | 表格高度                   |
| pageSizes         | number[]           | [10, 20, 50, 100]      | 每页显示条数选项           |
| defaultPageSize   | number             | 10                     | 默认每页显示条数           |
| data              | PersonData[]       | []                     | 静态数据源                 |
| dataLoader        | Function           | -                      | 动态数据加载函数           |

## 组件事件

| 事件名            | 参数                       | 说明               |
| ----------------- | -------------------------- | ------------------ |
| select            | person: PersonData         | 选择人员时触发     |
| update:modelValue | person: PersonData \| null | 选中人员变化时触发 |

## 数据模型

```typescript
interface PersonData {
	name: string; // 姓名
	department: string; // 部门
	phone: string; // 手机号
	id?: string | number; // 用户ID
	[key: string]: any; // 其他扩展字段
}
```

## 完整示例

```html
<template>
	<div class="person-selector-demo">
		<h2>人员选择器示例</h2>

		<div class="demo-section">
			<h3>基础使用</h3>
			<my-person-selector v-model="selectedPerson1" :data="personData" placeholder="请选择人员" />
			<div v-if="selectedPerson1" class="selected-info">
				选中的是：{{ selectedPerson1.name }} - {{ selectedPerson1.department }}
			</div>
		</div>

		<div class="demo-section">
			<h3>动态加载数据</h3>
			<my-person-selector
				v-model="selectedPerson2"
				:data-loader="loadPersonData"
				panel-width="600px"
				table-height="450px"
			/>
		</div>

		<div class="demo-section">
			<h3>自定义分页</h3>
			<my-person-selector
				v-model="selectedPerson3"
				:data="personData"
				:page-sizes="[5, 10, 20]"
				:default-page-size="5"
				@select="handleSelect"
			/>
		</div>
	</div>
</template>

<script setup lang="ts">
	import { ref } from "vue";
	import MyPersonSelector from "@/components/myselector/MyPersonSelector.vue";
	import type { PersonData } from "@/components/myselector/type";

	const selectedPerson1 = ref<PersonData | null>(null);
	const selectedPerson2 = ref<PersonData | null>(null);
	const selectedPerson3 = ref<PersonData | null>(null);

	const personData: PersonData[] = [
		{ id: 1, name: "张三", department: "技术部", phone: "13800138001" },
		{ id: 2, name: "李四", department: "产品部", phone: "13800138002" },
		{ id: 3, name: "王五", department: "市场部", phone: "13800138003" },
	];

	async function loadPersonData(): Promise<PersonData[]> {
		// 模拟API调用
		return new Promise((resolve) => {
			setTimeout(() => {
				resolve(personData);
			}, 500);
		});
	}

	function handleSelect(person: PersonData) {
		console.log("选中人员:", person);
	}
</script>

<style scoped>
	.person-selector-demo {
		padding: 20px;
	}

	.demo-section {
		margin-bottom: 30px;
		padding: 20px;
		border: 1px solid #eee;
		border-radius: 4px;
	}

	.selected-info {
		margin-top: 10px;
		padding: 10px;
		background: #f0f9ff;
		border-radius: 4px;
		color: #409eff;
	}
</style>
```

## 注意事项

1. 组件需要配合 Element Plus 使用
2. 数据源 `data` 和 `dataLoader` 二选一，如果同时存在，`dataLoader` 优先级更高
3. 搜索功能默认按姓名进行模糊匹配
4. 组件会自动处理点击外部关闭的逻辑
5. 建议为人员数据添加唯一的 `id` 字段
