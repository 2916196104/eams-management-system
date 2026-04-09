<template>
	<el-form
		ref="formRef"
		:model="modelValue"
		:label-width="labelWidth"
		:inline="inline"
		:disabled="disabled"
		:label-position="labelPosition"
		v-bind="$attrs"
	>
		<el-form-item
			v-for="field in fields"
			:key="field.prop"
			:label="field.label"
			:prop="field.prop"
			:rules="getFieldRules(field)"
		>
			<!-- 自定义插槽 -->
			<template v-if="field.slot">
				<slot
					:name="field.slot"
					:field="field"
					:value="modelValue[field.prop]"
					:update-value="(val: any) => updateFieldValue(field.prop, val)"
				/>
			</template>

			<!-- 文本输入框 -->
			<el-input
				v-else-if="field.type === 'input'"
				:model-value="modelValue[field.prop]"
				:placeholder="field.placeholder"
				:disabled="field.disabled"
				@update:model-value="(val) => updateFieldValue(field.prop, val)"
			/>

			<!-- 多行文本框 -->
			<el-input
				v-else-if="field.type === 'textarea'"
				:model-value="modelValue[field.prop]"
				type="textarea"
				:placeholder="field.placeholder"
				:disabled="field.disabled"
				@update:model-value="(val) => updateFieldValue(field.prop, val)"
			/>

			<!-- 数字输入框 -->
			<el-input-number
				v-else-if="field.type === 'number'"
				:model-value="modelValue[field.prop]"
				:placeholder="field.placeholder"
				:disabled="field.disabled"
				@update:model-value="(val) => updateFieldValue(field.prop, val)"
			/>

			<!-- 选择框 -->
			<el-select
				v-else-if="field.type === 'select'"
				:model-value="modelValue[field.prop]"
				:placeholder="field.placeholder"
				:disabled="field.disabled"
				@update:model-value="(val) => updateFieldValue(field.prop, val)"
			>
				<el-option
					v-for="option in field.options"
					:key="option.value"
					:label="option.label"
					:value="option.value"
					:disabled="option.disabled"
				/>
			</el-select>

			<!-- 日期选择器 -->
			<el-date-picker
				v-else-if="field.type === 'date'"
				:model-value="modelValue[field.prop]"
				:placeholder="field.placeholder"
				:disabled="field.disabled"
				@update:model-value="(val) => updateFieldValue(field.prop, val)"
			/>
		</el-form-item>
	</el-form>
</template>

<script setup lang="ts" generic="T extends Record<string, any> = Record<string, any>">
import { ref, computed } from "vue";
import { ElForm, ElFormItem, ElInput, ElInputNumber, ElSelect, ElOption, ElDatePicker } from "element-plus";
import type { FormInstance, FormItemRule } from "element-plus";
import type { CuiFormProps, CuiFormField, CuiFormValidateResult } from "./types";

/* 定义 Props */
const props = withDefaults(defineProps<CuiFormProps<T>>(), {
	labelWidth: "100px",
	inline: false,
	disabled: false,
	labelPosition: "right",
});

/* 定义 Emits */
const emit = defineEmits<{
	"update:modelValue": [value: T];
	submit: [value: T];
	reset: [];
}>();

/* 表单引用 */
const formRef = ref<FormInstance>();

/* 更新字段值 */
const updateFieldValue = (prop: keyof T, value: any) => {
	const newValue = { ...props.modelValue, [prop]: value };
	emit("update:modelValue", newValue);
};

/* 获取字段验证规则 */
const getFieldRules = (field: CuiFormField<T>): FormItemRule[] => {
	const rules: FormItemRule[] = [];

	/* 必填规则 */
	if (field.required) {
		rules.push({
			required: true,
			message: `请输入${field.label}`,
			trigger: ["blur", "change"],
		});
	}

	/* 自定义规则 */
	if (field.rules) {
		rules.push(...field.rules);
	}

	return rules;
};

/* 验证表单 */
const validate = async (): Promise<CuiFormValidateResult> => {
	if (!formRef.value) {
		return { valid: false };
	}

	try {
		await formRef.value.validate();
		return { valid: true };
	} catch (error: any) {
		return {
			valid: false,
			errors: error,
		};
	}
};

/* 验证指定字段 */
const validateField = async (prop: keyof T): Promise<boolean> => {
	if (!formRef.value) {
		return false;
	}

	try {
		await formRef.value.validateField(prop as string);
		return true;
	} catch {
		return false;
	}
};

/* 重置表单 */
const resetFields = () => {
	formRef.value?.resetFields();
	emit("reset");
};

/* 清除验证 */
const clearValidate = (props?: string | string[]) => {
	formRef.value?.clearValidate(props);
};

/* 提交表单 */
const submit = async () => {
	const result = await validate();
	if (result.valid) {
		emit("submit", props.modelValue);
	}
	return result;
};

/* 暴露方法给父组件 */
defineExpose({
	validate,
	validateField,
	resetFields,
	clearValidate,
	submit,
});

/* 启用属性继承以透传其他 ElForm 的 props 和事件 */
defineOptions({
	inheritAttrs: false,
});
</script>
