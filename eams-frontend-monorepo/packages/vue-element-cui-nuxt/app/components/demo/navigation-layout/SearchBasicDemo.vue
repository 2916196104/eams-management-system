<template>
	<div class="space-y-4">
		<CuiSearch v-model="formData" :fields="fields" collapsible @search="handleSearch" @reset="handleReset" />

		<div class="rounded-xl border border-dashed border-border bg-muted/20 p-3 text-sm text-muted-foreground">
			当前查询：{{ resultText }}
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, ref } from "vue";

import { CuiSearch } from "@eams-monorepo/vue-element-cui";
import type { CuiSearchField } from "@eams-monorepo/vue-element-cui";

const formData = ref({
	keyword: "固定资产",
	status: "active",
	owner: "",
});

const lastSearch = ref<Record<string, unknown> | null>(null);

const fields: CuiSearchField[] = [
	{
		prop: "keyword",
		label: "关键词",
		type: "input",
		placeholder: "请输入资产名称",
	},
	{
		prop: "status",
		label: "状态",
		type: "select",
		options: [
			{ label: "启用", value: "active" },
			{ label: "停用", value: "inactive" },
		],
	},
	{
		prop: "owner",
		label: "维护团队",
		type: "input",
		placeholder: "请输入维护团队",
		advanced: true,
	},
];

const resultText = computed(() => {
	return lastSearch.value ? JSON.stringify(lastSearch.value) : "点击搜索后查看当前筛选条件。";
});

const handleSearch = (value: Record<string, unknown>) => {
	lastSearch.value = value;
};

const handleReset = () => {
	lastSearch.value = {};
};
</script>
