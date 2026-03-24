<template>
	<el-dialog :model-value="modelValue" title="转出员工的学员" width="720px" @close="emit('update:modelValue', false)">
		<el-form label-width="100px">
			<el-form-item label="请选择人员">
				<el-input :model-value="selectedEmployeeName" readonly />
			</el-form-item>
		</el-form>
		<div class="tip-text">转换后，学员的顾问将改变为此人</div>
		<template #footer>
			<el-button @click="emit('update:modelValue', false)">取消</el-button>
			<el-button type="primary" :loading="submitting" @click="emit('submit')">提交</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
defineProps<{
	modelValue: boolean;
	selectedEmployeeName: string;
	submitting: boolean;
}>();

const emit = defineEmits<{
	(e: "update:modelValue", v: boolean): void;
	(e: "submit"): void;
}>();
</script>

<style scoped>
.tip-text {
	color: #909399;
	padding-left: 12px;
}
</style>

