<template>
	<el-dialog
		:model-value="modelValue"
		:title="title"
		:width="width"
		:show-close="showClose"
		:close-on-click-modal="closeOnClickModal"
		:before-close="beforeClose"
		@update:model-value="$emit('update:modelValue', $event)"
		@open="$emit('open')"
		@close="$emit('close')"
	>
		<!-- 对话框内容 -->
		<slot />

		<!-- 底部按钮栏 -->
		<template v-if="showFooter" #footer>
			<div class="cui-dialog-footer">
				<slot name="footer-left" />
				<div class="cui-dialog-actions">
					<slot name="footer-center" />
					<el-button @click="handleCancel">{{ cancelText }}</el-button>
					<el-button type="primary" :loading="loading" :disabled="confirmDisabled" @click="handleConfirm">
						{{ confirmText }}
					</el-button>
				</div>
			</div>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { ElDialog, ElButton } from "element-plus";
import type { CuiDialogProps, CuiDialogEmits } from "./types";

const props = withDefaults(defineProps<CuiDialogProps>(), {
	title: "提示",
	width: "50%",
	showClose: true,
	closeOnClickModal: false,
	showFooter: true,
	confirmText: "确认",
	cancelText: "取消",
	confirmDisabled: false,
	loading: false,
});

const emit = defineEmits<CuiDialogEmits>();

const handleConfirm = () => {
	emit("confirm");
};

const handleCancel = () => {
	emit("cancel");
	emit("update:modelValue", false);
};
</script>

<style scoped lang="scss">
.cui-dialog-footer {
	display: flex;
	justify-content: space-between;
	align-items: center;
}

.cui-dialog-actions {
	display: flex;
	gap: 8px;
	justify-content: flex-end;
}
</style>
