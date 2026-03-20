<template>
	<el-dialog
		class="my-detail-dialog"
		v-model="dialogVisible"
		:title="title"
		:width="width"
		destroy-on-close
		:modal="false"
	>
		<el-table :data="data" border stripe class="my-detail-table">
			<el-table-column
				v-for="column in columns"
				:key="column.prop"
				:prop="column.prop"
				:label="column.label"
				:width="column.width"
				:align="column.align || 'center'"
			/>
		</el-table>

		<template #footer>
			<el-button class="my-detail-close-btn" type="primary" @click="closeDialog">关闭</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts" generic="T extends Record<string, any> = Record<string, any>">
import { ref } from "vue";
import type { MyDetailDialogColumn, MyDetailDialogProps } from "./type";

const props = withDefaults(defineProps<MyDetailDialogProps<T>>(), {
	title: "详情",
	width: "1180px",
});

const dialogVisible = ref(false);

const title = props.title;
const width = props.width;
const data = props.data;
const columns = props.columns as MyDetailDialogColumn[];

function openDialog() {
	dialogVisible.value = true;
}

function closeDialog() {
	dialogVisible.value = false;
}

defineExpose({
	openDialog,
	closeDialog,
});
</script>

<style scoped>
/* 1. 弹窗头部：浅蓝色背景，标题与关闭按钮垂直居中 */
.my-detail-dialog :deep(.el-dialog__header) {
	background-color: #e5f3ff;
	padding: 12px 20px;
	border-bottom: 1px solid #d9ecff;
	display: flex;
	align-items: center;
}

.my-detail-dialog :deep(.el-dialog__title) {
	color: #1f2f3d;
	font-size: 16px;
	font-weight: 600;
	margin: 0;
}

/* 2. 右上角关闭按钮（×） */
.my-detail-dialog :deep(.el-dialog__headerbtn) {
	top: 15px;
	right: 20px;
}

.my-detail-dialog :deep(.el-dialog__headerbtn .el-dialog__close) {
	color: #606266;
	background: transparent;
	width: 24px;
	height: 24px;
	border-radius: 4px;
	display: flex;
	align-items: center;
	justify-content: center;
	transition: all 0.2s ease;
}

.my-detail-dialog :deep(.el-dialog__headerbtn .el-dialog__close:hover) {
	color: #fff;
	background-color: #409eff;
}

/* 3. 弹窗主体内容 */
.my-detail-dialog :deep(.el-dialog__body) {
	padding: 15px 20px;
	overflow: auto;
}

/* 4. 表格样式：轻量化，仅横线 */
.my-detail-table :deep(.el-table) {
	font-size: 13px;
	width: 100% !important;
}

/* 表格：只保留横线分隔，去掉竖线和外边框 */
.my-detail-table :deep(.el-table--border::after),
.my-detail-table :deep(.el-table--group::after),
.my-detail-table :deep(.el-table::before) {
	display: none;
}

.my-detail-table :deep(.el-table__cell) {
	border-right: none;
	border-bottom: 1px solid #e4e7ed;
	padding: 6px 8px !important;
}

.my-detail-table :deep(.el-table__header-wrapper) {
	border-bottom: 1px solid #e4e7ed;
}

.my-detail-table :deep(.el-table th) {
	background-color: transparent;
	color: #909399;
	font-weight: 600;
	border-bottom: 1px solid #e4e7ed;
}

/* 5. 底部关闭按钮：右下角，白色描边 */
.my-detail-dialog :deep(.el-dialog__footer) {
	border-top: none;
	padding: 10px 20px;
	text-align: right;
}

.my-detail-close-btn {
	min-width: 90px;
	height: 32px;
	padding: 0 18px;
	border-radius: 4px;
	border-color: #dcdfe6;
	background-color: #ffffff;
	color: #606266;
	font-size: 14px;
	font-weight: 500;
	transition: all 0.2s ease;
}

.my-detail-close-btn:hover,
.my-detail-close-btn:focus {
	background-color: #ffffff;
	border-color: #409eff;
	color: #409eff;
}

/* 6. 响应式适配：核心避免横向滚动，并保持居中 */
.my-detail-dialog :deep(.el-dialog) {
	width: 1180px !important;
	max-width: 96vw !important;
	margin: auto !important;
}

@media (max-width: 1440px) {
	.my-detail-dialog :deep(.el-dialog) {
		width: 1000px !important;
		max-width: 96vw !important;
	}

	.my-detail-table :deep(.el-table) {
		font-size: 12px;
	}

	.my-detail-table :deep(.el-table__cell) {
		padding: 4px 6px !important;
	}
}

@media (max-width: 1280px) {
	.my-detail-dialog :deep(.el-dialog) {
		width: 920px !important;
		max-width: 98vw !important;
	}

	.my-detail-table :deep(.el-table) {
		font-size: 12px;
	}

	.my-detail-table :deep(.el-table__cell) {
		padding: 3px 6px !important;
	}
}

.my-detail-dialog-table {
	width: 100%;
	box-sizing: border-box;
}

.my-detail-dialog-desc {
	width: 100%;
	box-sizing: border-box;
}

.text-bold {
	font-weight: 600;
}

.text-red {
	color: #f56c6c;
}
</style>
