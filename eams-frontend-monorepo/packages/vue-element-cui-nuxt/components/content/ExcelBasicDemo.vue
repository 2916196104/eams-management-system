<template>
	<div class="space-y-4">
		<div class="flex items-center gap-2">
			<el-button type="primary" @click="showDialog = true">打开导入对话框</el-button>
			<span class="text-sm text-muted-foreground">点击按钮查看 CuiExcel 导入弹层</span>
		</div>
		<CuiExcel
			v-model="showDialog"
			upload-url="/api/assets/import"
			template-url="/api/assets/template"
			title="导入资产台账"
			@success="handleSuccess"
			@error="handleError"
		/>
		<p v-if="resultMsg" class="text-sm" :class="resultMsg.type === 'success' ? 'text-green-600' : 'text-red-600'">
			{{ resultMsg.text }}
		</p>
		<p class="text-sm text-muted-foreground">
			演示说明：uploadUrl 和 templateUrl 为 mock 地址，此处仅展示 UI 交互流程。
		</p>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { CuiExcel } from "@eams-monorepo/vue-element-cui";

const showDialog = ref(false);
const resultMsg = ref<{ type: "success" | "error"; text: string } | null>(null);

const handleSuccess = (_response: any, file: any) => {
	resultMsg.value = { type: "success", text: `文件 "${file.name}" 上传成功` };
	showDialog.value = false;
};

const handleError = (_error: any) => {
	resultMsg.value = { type: "error", text: "上传失败，请检查文件格式" };
};
</script>
