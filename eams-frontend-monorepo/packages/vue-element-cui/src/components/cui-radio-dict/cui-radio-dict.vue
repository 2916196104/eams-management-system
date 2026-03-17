<template>
	<el-radio-group :model-value="modelValue" :disabled="disabled" @update:model-value="handleChange">
		<el-radio v-for="option in options" :key="option.value" :label="option.value">
			{{ option.label }}
		</el-radio>
	</el-radio-group>
</template>

<script setup lang="ts">
import { ref, onMounted } from "vue";
import { ElRadioGroup, ElRadio } from "element-plus";
import type { CuiRadioDictProps, CuiRadioDictEmits, CuiRadioDictOption } from "./types";

const props = withDefaults(defineProps<CuiRadioDictProps>(), {
	disabled: false,
});

const emit = defineEmits<CuiRadioDictEmits>();

const options = ref<CuiRadioDictOption[]>([]);

/* 字典缓存 */
const dictCache = new Map<string, CuiRadioDictOption[]>();

/* 加载字典选项 */
const loadCuiRadioDictOptions = async () => {
	/* 检查缓存 */
	if (dictCache.has(props.dictCode)) {
		options.value = dictCache.get(props.dictCode)!;
		return;
	}

	/* TODO: 根据 dictCode 从 API 获取字典选项 */
	/* 这是一个示例实现，实际应该调用字典服务 */
	const mockOptions: CuiRadioDictOption[] = [
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
	loadCuiRadioDictOptions();
});
</script>
