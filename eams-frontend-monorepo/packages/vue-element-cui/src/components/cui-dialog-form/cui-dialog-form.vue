<template>
	<cui-dialog
		:model-value="visible"
		:title="title"
		:width="width"
		:show-close="showClose"
		:close-on-click-modal="closeOnClickModal"
		:show-footer="true"
		:confirm-text="confirmText"
		:cancel-text="cancelText"
		:confirm-disabled="confirmDisabled || loading"
		:loading="loading"
		@update:model-value="$emit('update:visible', $event)"
		@confirm="handleConfirm"
		@cancel="handleCancel"
		@open="$emit('open')"
		@close="$emit('close')"
	>
		<!-- 对话框顶部内容 -->
		<slot />

		<!-- 表单 -->
		<cui-form
			ref="formRef"
			:fields="fields"
			:model-value="modelValue"
			:label-width="labelWidth"
			:inline="inline"
			:disabled="disabled || loading"
			:label-position="labelPosition"
			@update:model-value="$emit('update:modelValue', $event)"
		>
			<!-- 传递表单字段插槽 -->
			<template v-for="field in fields" :key="field.prop" #[field.slot]="slotProps">
				<slot :name="`field-${field.prop}`" v-bind="slotProps" />
			</template>
		</cui-form>

		<!-- 底部按钮中间的自定义内容 -->
		<template #footer-center>
			<slot name="footer-center" />
		</template>
	</cui-dialog>
</template>

<script setup lang="ts">
import { ref, watch } from "vue";
import { CuiDialog } from "../cui-dialog";
import { CuiForm } from "../cui-form";
import type { CuiDialogFormProps, CuiDialogFormEmits } from "./types";

const props = withDefaults(defineProps<CuiDialogFormProps>(), {
	title: "表单对话框",
	width: "50%",
	showClose: true,
	closeOnClickModal: false,
	confirmText: "确认",
	cancelText: "取消",
	confirmDisabled: false,
	loading: false,
	disabled: false,
	labelWidth: "100px",
	inline: false,
	labelPosition: "right",
});

const emit = defineEmits<CuiDialogFormEmits>();

const formRef = ref();

/* 处理确认 */
const handleConfirm = async () => {
	if (!formRef.value) return;

	try {
		const valid = await formRef.value.validate();
		if (valid) {
			emit("submit", props.modelValue);
			emit("update:visible", false);
		}
	} catch (error) {
		console.error("Form validation failed:", error);
	}
};

/* 处理取消 */
const handleCancel = () => {
	emit("cancel");
	emit("update:visible", false);
};

/* 暴露方法给父组件 */
const resetForm = () => {
	if (formRef.value) {
		formRef.value.resetFields();
	}
};

const setFormData = (data: any) => {
	emit("update:modelValue", data);
};

defineExpose({
	resetForm,
	setFormData,
	formRef,
});
</script>
