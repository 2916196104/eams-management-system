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
import { ref, onMounted } from "vue";
import { ElSelect, ElOption } from "element-plus";
import type { CuiSelectDictProps, CuiSelectDictEmits, CuiSelectDictOption } from "./types";

const props = withDefaults(defineProps<CuiSelectDictProps>(), {
	placeholder: "请选择",
	disabled: false,
	clearable: true,
	filterable: true,
});

const emit = defineEmits<CuiSelectDictEmits>();

const options = ref<CuiSelectDictOption[]>([]);

/* 字典缓存 */
const dictCache = new Map<string, CuiSelectDictOption[]>();

/* 加载字典选项 */
const loadCuiSelectDictOptions = async () => {
	/* 检查缓存 */
	if (dictCache.has(props.dictCode)) {
		options.value = dictCache.get(props.dictCode)!;
		return;
	}

	/* TODO: 根据 dictCode 从 API 获取字典选项 */
	/* 这是一个示例实现，实际应该调用字典服务 */
	const mockOptions: CuiSelectDictOption[] = [
		{ label: "选项 1", value: "1" },
		{ label: "选项 2", value: "2" },
		{ label: "选项 3", value: "3" },
	];

	/* 缓存字典数据 */
	dictCache.set(props.dictCode, mockOptions);
	options.value = mockOptions;
};

const handleChange = (value: any) => {
	emit("update:modelValue", value);
	emit("change", value);
};

onMounted(() => {
	loadCuiSelectDictOptions();
});
</script>
