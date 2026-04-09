<template>
	<div class="flex flex-col gap-4 p-4">
		<div>
			<p class="mb-2 text-sm text-muted-foreground">弹层选择框（selector 插槽演示）</p>
			<CuiSelectBox v-model="selected" type="user" placeholder="请选择负责人">
				<template #selector="{ condition, onSubmit }">
					<div class="p-4">
						<p class="mb-2 text-sm">此处放置自定义的人员选择列表</p>
						<el-button type="primary" @click="onSubmit('user-001')">选择张三</el-button>
					</div>
				</template>
			</CuiSelectBox>
		</div>
		<div>
			<p class="mb-2 text-sm text-muted-foreground">已选中：{{ selected ?? "暂无" }}</p>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { CuiSelectBox } from "@eams-monorepo/vue-element-cui";

const selected = ref<string | null>(null);
</script>
