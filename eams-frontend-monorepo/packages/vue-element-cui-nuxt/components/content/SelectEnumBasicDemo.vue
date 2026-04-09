<template>
	<div class="flex flex-col gap-4 p-4">
		<div>
			<p class="mb-2 text-sm text-muted-foreground">枚举选择（从枚举服务加载选项）</p>
			<CuiSelectEnum v-model="selected" enum-code="ASSET_STATUS" placeholder="请选择资产状态" />
		</div>
		<div>
			<p class="mb-2 text-sm text-muted-foreground">已选中：{{ selected ?? "暂无" }}</p>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { CuiSelectEnum } from "@eams-monorepo/vue-element-cui";

const selected = ref<string | null>(null);
</script>
