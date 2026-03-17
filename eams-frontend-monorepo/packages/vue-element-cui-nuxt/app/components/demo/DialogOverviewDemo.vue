<template>
	<div class="space-y-4">
		<div class="flex flex-wrap gap-3">
			<el-button type="primary" @click="visible = true">打开确认弹层</el-button>
			<el-tag type="info">最近操作：{{ lastAction }}</el-tag>
		</div>

		<CuiDialog
			v-model="visible"
			title="提交资产处置申请"
			confirm-text="确认提交"
			cancel-text="暂不提交"
			@confirm="handleConfirm"
			@cancel="handleCancel"
		>
			<p class="text-sm leading-6 text-muted-foreground">
				对话框内部直接承载业务确认信息，适合搭配 `CuiDialogForm` 继续扩展为表单流程。
			</p>
		</CuiDialog>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";

import { CuiDialog } from "@eams-monorepo/vue-element-cui";

const visible = ref(false);
const lastAction = ref("尚未执行");

const handleConfirm = () => {
	lastAction.value = "已确认提交";
	visible.value = false;
};

const handleCancel = () => {
	lastAction.value = "已取消";
	visible.value = false;
};
</script>
