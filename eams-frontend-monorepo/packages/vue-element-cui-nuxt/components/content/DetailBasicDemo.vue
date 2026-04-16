<template>
	<div class="space-y-4">
		<CuiDetail :fields="fields" :data="detail" :columns="2" />
		<p class="text-sm text-muted-foreground">演示多列布局、render 函数状态映射与标签宽度配置。</p>
	</div>
</template>

<script setup lang="ts">
import { CuiDetail } from "@eams-monorepo/vue-element-cui";
import type { CuiDetailField } from "@eams-monorepo/vue-element-cui";

const fields: CuiDetailField[] = [
	{ label: "资产名称", prop: "name" },
	{ label: "归属部门", prop: "dept" },
	{ label: "负责人", prop: "owner" },
	{ label: "资产编号", prop: "code" },
	{
		label: "资产状态",
		prop: "status",
		render: (row) => (row.status === 1 ? "在用" : "闲置"),
	},
	{ label: "登记时间", prop: "createdAt" },
];

const detail = {
	name: "固定资产台账",
	dept: "财务共享中心",
	owner: "张三",
	code: "ASSET-2026-001",
	status: 1,
	createdAt: "2026-03-01",
};
</script>
