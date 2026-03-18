<template>
	<div class="flex flex-col gap-4 p-4">
		<div>
			<p class="mb-2 text-sm text-muted-foreground">字典选择（从字典服务加载选项）</p>
			<CuiSelectDict v-model="selected" dict-code="DEPT_TYPE" placeholder="请选择部门类型" />
		</div>
		<div>
			<p class="mb-2 text-sm text-muted-foreground">已选中：{{ selected ?? "暂无" }}</p>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { CuiSelectDict } from "@eams-monorepo/vue-element-cui";

const selected = ref<string | null>(null);
</script>
