<script setup lang="ts">
import { ref } from "vue";
import { CuiForm, CuiSearch, CuiDialog } from "@eams-monorepo/vue-element-cui";
import type { CuiFormField, CuiSearchField, CuiDialogProps } from "@eams-monorepo/vue-element-cui";

type SearchModel = {
	keyword: string;
	status: string;
};

const formModel = ref<SearchModel>({
	keyword: "",
	status: "",
});

const formFields: CuiFormField<SearchModel>[] = [
	{ prop: "keyword", label: "关键字", type: "input" },
	{
		prop: "status",
		label: "状态",
		type: "select",
		options: [
			{ label: "启用", value: "enabled" },
			{ label: "停用", value: "disabled" },
		],
	},
];

const searchFields: CuiSearchField[] = [{ prop: "keyword", label: "关键字", type: "input" }];

const dialogProps: CuiDialogProps = {
	modelValue: true,
	title: "详情",
	showFooter: false,
};
</script>

<template>
	<section>
		<CuiSearch :fields="searchFields" :model-value="formModel" />
		<CuiForm :fields="formFields" :model-value="formModel" />
		<CuiDialog v-bind="dialogProps" />
	</section>
</template>
