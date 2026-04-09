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
import type { CuiRadioEnumProps, CuiRadioEnumEmits, CuiRadioEnumOption } from "./types";

const props = withDefaults(defineProps<CuiRadioEnumProps>(), {
	disabled: false,
});

const emit = defineEmits<CuiRadioEnumEmits>();

const options = ref<CuiRadioEnumOption[]>([]);

/* 获取枚举选项 */
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
