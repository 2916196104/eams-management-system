<template>
	<el-select
		:model-value="modelValue"
		:placeholder="placeholder"
		:disabled="disabled"
		:clearable="clearable"
		:filterable="filterable"
		:remote="remote"
		:remote-method="remoteMethod"
		:loading="loading"
		@update:model-value="handleChange"
	>
		<el-option
			v-for="option in options"
			:key="option.value"
			:label="option.label"
			:value="option.value"
			:disabled="option.disabled"
		/>
	</el-select>
</template>

<script setup lang="ts">
import { ElSelect, ElOption } from "element-plus";
import type { CuiSelectProps, CuiSelectEmits } from "./types";

const props = withDefaults(defineProps<CuiSelectProps>(), {
	options: () => [],
	placeholder: "请选择",
	disabled: false,
	clearable: true,
	filterable: true,
	remote: false,
	loading: false,
});

const emit = defineEmits<CuiSelectEmits>();

const handleChange = (value: any) => {
	emit("update:modelValue", value);
	emit("change", value);
};
</script>
