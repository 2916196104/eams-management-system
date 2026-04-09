<template>
	<div class="flex flex-col gap-4 p-4">
		<div>
			<p class="mb-2 text-sm text-muted-foreground">枚举多选（从枚举服务加载选项）</p>
			<CuiCheckboxEnum v-model="selected" enum-code="ASSET_TYPE" />
		</div>
		<div>
			<p class="mb-2 text-sm text-muted-foreground">已选中：{{ selected.join(", ") || "暂无" }}</p>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { CuiCheckboxEnum } from "@eams-monorepo/vue-element-cui";

const selected = ref<string[]>([]);
</script>
