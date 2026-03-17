<template>
	<div class="space-y-4">
		<div class="flex flex-wrap gap-3">
			<el-button type="primary" @click="visible = true">打开弹层表单</el-button>
			<el-tag type="success">最近提交：{{ lastSubmit }}</el-tag>
		</div>

		<CuiDialogForm
			v-model:visible="visible"
			v-model="formData"
			title="新增资产分类"
			:fields="fields"
			@submit="handleSubmit"
		/>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";

import { CuiDialogForm } from "@eams-monorepo/vue-element-cui";
import type { CuiFormField } from "@eams-monorepo/vue-element-cui";

const visible = ref(false);
const lastSubmit = ref("尚未提交");
const formData = ref({
	name: "",
	owner: "",
});

const fields: CuiFormField[] = [
	{
		prop: "name",
		label: "分类名称",
		type: "input",
		placeholder: "请输入分类名称",
		required: true,
	},
	{
		prop: "owner",
		label: "维护团队",
		type: "input",
		placeholder: "请输入维护团队",
		required: true,
	},
];

const handleSubmit = (value: { name: string; owner: string }) => {
	lastSubmit.value = `${value.name} / ${value.owner}`;
};
</script>
