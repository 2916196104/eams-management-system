<template>
	<div class="space-y-4">
		<CuiSelect v-model="selectedValue" :options="options" placeholder="请选择资产分类" clearable filterable />

		<div class="grid gap-3 md:grid-cols-2">
			<div class="rounded-xl border border-border bg-background p-3">
				<p class="text-xs uppercase tracking-[0.16em] text-muted-foreground">当前选择</p>
				<p class="mt-2 text-sm font-medium text-foreground">
					{{ selectedValue || "尚未选择" }}
				</p>
			</div>
			<div class="rounded-xl border border-border bg-background p-3">
				<p class="text-xs uppercase tracking-[0.16em] text-muted-foreground">推荐组合</p>
				<p class="mt-2 text-sm text-muted-foreground">
					当选项来源于枚举或字典时，优先使用 `CuiSelectEnum`、`CuiSelectDict` 等专用组件。
				</p>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";

import { CuiSelect } from "@eams-monorepo/vue-element-cui";
import type { CuiSelectOption } from "@eams-monorepo/vue-element-cui";

const selectedValue = ref("equipment");

const options: CuiSelectOption[] = [
	{ label: "设备资产", value: "equipment" },
	{ label: "库存物料", value: "inventory" },
	{ label: "办公用品", value: "office" },
];
</script>
