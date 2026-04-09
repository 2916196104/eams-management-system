<template>
	<div class="flex flex-col gap-4 p-4">
		<div>
			<p class="mb-2 text-sm text-muted-foreground">基础单选</p>
			<CuiSelect v-model="selected" :options="options" placeholder="请选择资产类型" />
		</div>
		<div>
			<p class="mb-2 text-sm text-muted-foreground">已选中：{{ selected ?? "暂无" }}</p>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { CuiSelect } from "@eams-monorepo/vue-element-cui";

const selected = ref<string | null>(null);
const options = [
	{ label: "固定资产", value: "fixed" },
	{ label: "流动资产", value: "current" },
	{ label: "无形资产", value: "intangible" },
	{ label: "在建工程", value: "construction" },
];
</script>
