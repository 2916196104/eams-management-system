# MyDetailDialog 详情对话框组件

`MyDetailDialog` 是基于 `Element Plus` 封装的通用详情对话框组件，用于以弹窗 + 表格的方式展示一组明细数据（例如课时明细、费用明细等）。

组件只关心“如何把一组数据以表格形式展示出来”，**显示 / 隐藏由内部控制，通过 `ref` 暴露的 `openDialog / closeDialog` 方法操作**。

## 1. 基本用法

```html
<template>
	<el-button type="primary" @click="openDialog">查看课时明细</el-button>

	<my-detail-dialog ref="detailRef" title="课时明细" :columns="columns" :data="rows" />
</template>

<script setup lang="ts">
	import { ref } from "vue";
	import MyDetailDialog from "@/components/mydetaildialog/MyDetailDialog.vue";
	import type { MyDetailDialogColumn } from "@/components/mydetaildialog/type";

	interface CourseDetail {
		courseName: string;
		duration: string;
		mainCount: number;
		assistCount: number;
		totalCount: number;
		mainFee: number;
		assistFee: number;
		mainAmount: number;
		assistAmount: number;
		totalAmount: number;
	}

	const detailRef = ref<InstanceType<typeof MyDetailDialog> | null>(null);

	const columns: MyDetailDialogColumn[] = [
		{ prop: "courseName", label: "课程", align: "left" },
		{ prop: "duration", label: "时长" },
		{ prop: "mainCount", label: "上课课时数" },
		{ prop: "assistCount", label: "助教课时数" },
		{ prop: "totalCount", label: "课时总数" },
		{ prop: "mainFee", label: "单节上课费" },
		{ prop: "assistFee", label: "单节助教费" },
		{ prop: "mainAmount", label: "上课费小计" },
		{ prop: "assistAmount", label: "助教费小计" },
		{ prop: "totalAmount", label: "合计" },
	];

	const rows: CourseDetail[] = [
		{
			courseName: "2025·KET考冲班-第1期",
			duration: "120分钟",
			mainCount: 2,
			assistCount: 0,
			totalCount: 2,
			mainFee: 300,
			assistFee: 0,
			mainAmount: 600,
			assistAmount: 0,
			totalAmount: 600,
		},
	];

	function openDialog() {
		detailRef.value?.openDialog();
	}
</script>
```

## 2. 属性说明

组件属性类型定义在 `type.ts` 中：

```ts
export interface MyDetailDialogColumn {
	prop: string;
	label: string;
	width?: string | number;
	align?: "left" | "center" | "right";
}

export interface MyDetailDialogProps<T = Record<string, any>> {
	title?: string;
	width?: string | number;
	columns: MyDetailDialogColumn[];
	data: T[];
}
```

## 3. 暴露方法

组件通过 `ref` 暴露如下方法：

- `openDialog()`：打开对话框
- `closeDialog()`：关闭对话框

## 4. 示例入口

示例页面路由：`/sample/mydetaildialog`  
对应示例代码：`src/views/sample/mydetaildialog/Index.vue`
