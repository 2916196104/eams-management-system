<template>
	<cui-dialog
		:model-value="modelValue"
		:title="title"
		confirm-text="上传"
		@update:model-value="$emit('update:modelValue', $event)"
		@confirm="handleUpload"
	>
		<div v-if="templateUrl" class="template-download">
			<el-button type="text" @click="downloadTemplate">点击此处下载模板</el-button>
			<small>，模板中*开头的列为必填列</small>
		</div>

		<el-upload
			ref="uploadRef"
			class="excel-upload"
			drag
			:action="uploadUrl"
			:headers="headers"
			:data="params"
			:accept="accept"
			:auto-upload="false"
			@success="handleSuccess"
			@error="handleError"
		>
			<el-icon class="el-icon--upload"><upload-filled /></el-icon>
			<div class="el-upload__text">
				将文件拖到此处，或
				<em>点击此处</em>
				开始导入
			</div>
			<template #tip>
				<div class="el-upload__tip">请上传 .xls 或 .xlsx 文件</div>
			</template>
		</el-upload>
	</cui-dialog>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { ElUpload, ElButton, ElIcon } from "element-plus";
import { UploadFilled } from "@element-plus/icons-vue";
import { CuiDialog } from "../cui-dialog";
import type { CuiExcelProps, CuiExcelEmits } from "./types";

const props = withDefaults(defineProps<CuiExcelProps>(), {
	title: "导入 Excel",
	accept: ".xls,.xlsx",
	headers: () => ({}),
	params: () => ({}),
});

const emit = defineEmits<CuiExcelEmits>();

const uploadRef = ref();

const handleUpload = () => {
	if (uploadRef.value) {
		uploadRef.value.submit();
	}
};

const handleSuccess = (response: any, file: any, fileList: any) => {
	emit("success", response, file, fileList);
	emit("update:modelValue", false);
};

const handleError = (error: any) => {
	emit("error", error);
};

const downloadTemplate = () => {
	if (props.templateUrl) {
		window.open(props.templateUrl, "_blank");
	}
};
</script>

<style scoped lang="scss">
.template-download {
	margin-bottom: 20px;
	padding-bottom: 20px;
	border-bottom: 1px solid #ebeef5;
}

.excel-upload {
	width: 100%;
}
</style>
