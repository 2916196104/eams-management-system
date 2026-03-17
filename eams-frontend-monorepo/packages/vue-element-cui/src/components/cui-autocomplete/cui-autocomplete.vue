<template>
	<el-autocomplete
		:model-value="modelValue"
		:fetch-suggestions="internalFetchSuggestions"
		:placeholder="placeholder"
		:disabled="disabled"
		:clearable="clearable"
		:debounce="debounce"
		:trigger-on-focus="triggerOnFocus"
		@update:model-value="handleInput"
		@select="handleSelect"
	/>
</template>

<script setup lang="ts">
import { computed } from "vue";
import { ElAutocomplete } from "element-plus";
import type { CuiAutocompleteProps, CuiAutocompleteEmits, CuiAutocompleteSuggestion } from "./types";

const props = withDefaults(defineProps<CuiAutocompleteProps>(), {
	suggestions: () => [],
	placeholder: "请输入",
	disabled: false,
	clearable: true,
	debounce: 300,
	triggerOnFocus: true,
});

const emit = defineEmits<CuiAutocompleteEmits>();

const handleInput = (value: string | number) => {
	emit("update:modelValue", String(value));
};

const handleSelect = (item: Record<string, any>) => {
	emit("select", item as CuiAutocompleteSuggestion);
};

/* 内部 fetchSuggestions 实现 */
const internalFetchSuggestions = (queryString: string, cb: (suggestions: CuiAutocompleteSuggestion[]) => void) => {
	/* 如果提供了自定义 fetchSuggestions，使用它 */
	if (props.fetchSuggestions) {
		props.fetchSuggestions(queryString, cb);
		return;
	}

	/* 否则使用 suggestions 进行过滤 */
	if (!queryString) {
		cb(props.suggestions || []);
		return;
	}

	const results = (props.suggestions || []).filter((item) => {
		return (
			item.value.toLowerCase().includes(queryString.toLowerCase()) ||
			(item.label && item.label.toLowerCase().includes(queryString.toLowerCase()))
		);
	});
	cb(results);
};

/* 暴露 fetchSuggestions 方法供测试使用 */
defineExpose({
	fetchSuggestions: internalFetchSuggestions,
});
</script>
