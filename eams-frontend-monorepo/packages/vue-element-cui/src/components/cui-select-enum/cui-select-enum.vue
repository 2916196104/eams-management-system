<template>
	<el-select
		:model-value="modelValue"
		:placeholder="placeholder"
		:disabled="disabled"
		:clearable="clearable"
		:filterable="filterable"
		@update:model-value="handleChange"
	>
		<el-option v-for="option in options" :key="option.value" :label="option.label" :value="option.value" />
	</el-select>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from "vue";
import { ElSelect, ElOption } from "element-plus";
import type { CuiSelectEnumProps, CuiSelectEnumEmits, CuiSelectEnumOption } from "./types";

const props = withDefaults(defineProps<CuiSelectEnumProps>(), {
	placeholder: "请选择",
	disabled: false,
	clearable: true,
	filterable: true,
});

const emit = defineEmits<CuiSelectEnumEmits>();

const options = ref<CuiSelectEnumOption[]>([]);

/* 获取枚举选项（这里需要根据实际的枚举系统实现） */
const loadEnumOptions = () => {
	/* TODO: 根据 enumCode 从枚举系统获取选项 */
	/* 这是一个示例实现，实际应该调用枚举服务 */
	options.value = [
		{ label: "选项 1", value: "1" },
		{ label: "选项 2", value: "2" },
		{ label: "选项 3", value: "3" },
	];
};

const handleChange = (value: any) => {
	emit("update:modelValue", value);
	emit("change", value);
};

onMounted(() => {
	loadEnumOptions();
});
</script>
