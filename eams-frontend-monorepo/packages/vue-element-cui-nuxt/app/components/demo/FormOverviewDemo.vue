<template>
	<div class="space-y-4">
		<CuiForm ref="formRef" v-model="formData" :fields="fields" />

		<div class="flex flex-wrap gap-3">
			<el-button type="primary" @click="handleSubmit">提交</el-button>
			<el-button @click="formRef?.resetFields()">重置</el-button>
		</div>

		<div class="rounded-xl border border-dashed border-border bg-muted/20 p-3 text-sm text-muted-foreground">
			当前数据：{{ JSON.stringify(formData, null, 2) }}
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";

import { CuiForm } from "@eams-monorepo/vue-element-cui";
import type { CuiFormField } from "@eams-monorepo/vue-element-cui";

const formRef = ref<InstanceType<typeof CuiForm>>();
const formData = ref({
	name: "资产盘点任务",
	owner: "",
	status: "draft",
});

const fields: CuiFormField[] = [
	{
		prop: "name",
		label: "任务名称",
		type: "input",
		placeholder: "请输入任务名称",
		required: true,
	},
	{
		prop: "owner",
		label: "负责人",
		type: "input",
		placeholder: "请输入负责人",
		required: true,
	},
	{
		prop: "status",
		label: "状态",
		type: "select",
		options: [
			{ label: "草稿", value: "draft" },
			{ label: "执行中", value: "running" },
			{ label: "已归档", value: "archived" },
		],
	},
];

const handleSubmit = async () => {
	await formRef.value?.submit();
};
</script>
