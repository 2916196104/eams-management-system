<template>
	<el-dialog :model-value="modelValue" title="重置密码" width="520px" @close="emit('update:modelValue', false)">
		<el-form ref="formRef" :model="formModel" :rules="rules" label-width="110px">
			<el-form-item label="输入新密码" prop="newPassword" required>
				<el-input v-model="formModel.newPassword" type="password" show-password placeholder="请输入新密码" />
			</el-form-item>
		</el-form>
		<template #footer>
			<el-button @click="emit('update:modelValue', false)">取消</el-button>
			<el-button type="primary" :loading="submitting" @click="handleSubmit">提交</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { ElMessage, type FormInstance, type FormRules } from "element-plus";

defineProps<{
	modelValue: boolean;
	submitting: boolean;
}>();

const emit = defineEmits<{
	(e: "update:modelValue", v: boolean): void;
	(e: "submit", newPassword: string): void;
}>();

const formRef = ref<FormInstance>();
const formModel = ref({ newPassword: "" });
const rules: FormRules = {
	newPassword: [
		{ required: true, message: "请输入新密码", trigger: "blur" },
		{ min: 6, message: "密码至少6位", trigger: "blur" },
	],
};

async function handleSubmit() {
	try {
		await formRef.value?.validate();
		emit("submit", formModel.value.newPassword);
		formModel.value.newPassword = "";
	} catch {
		ElMessage.warning("请输入有效密码");
	}
}
</script>

