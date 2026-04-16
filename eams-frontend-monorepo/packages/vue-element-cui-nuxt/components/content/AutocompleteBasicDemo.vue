<template>
	<div class="flex flex-col gap-4 p-4">
		<div>
			<p class="mb-2 text-sm text-muted-foreground">自动补全（静态建议）</p>
			<CuiAutocomplete
				v-model="keyword"
				:suggestions="suggestions"
				placeholder="请输入资产编号"
				@select="handleSelect"
			/>
		</div>
		<div>
			<p class="mb-2 text-sm text-muted-foreground">已输入：{{ keyword || "暂无" }}</p>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { CuiAutocomplete } from "@eams-monorepo/vue-element-cui";

const keyword = ref("");
const suggestions = [
	{ value: "ASSET-001", label: "ASSET-001 服务器A" },
	{ value: "ASSET-002", label: "ASSET-002 服务器B" },
	{ value: "ASSET-003", label: "ASSET-003 交换机A" },
];

const handleSelect = (item: any) => {
	console.log("选中：", item);
};
</script>
