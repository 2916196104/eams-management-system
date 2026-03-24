<template>
	<el-dialog :model-value="modelValue" title="修改员工" width="760px" destroy-on-close @close="emit('update:modelValue', false)">
		<el-form ref="formRef" :model="formModel" :rules="rules" label-width="96px">
			<el-form-item label="姓名" prop="name" required><el-input v-model="formModel.name" /></el-form-item>
			<el-form-item label="电话/登录账号" prop="account" required><el-input v-model="formModel.account" /></el-form-item>
			<el-form-item label="所属机构" prop="orgId" required>
				<el-select v-model="formModel.orgId" class="full-width">
					<el-option v-for="item in orgOptions" :key="item.id" :label="item.label" :value="item.id" />
				</el-select>
			</el-form-item>
			<el-form-item label="所属职位" prop="position" required><el-input v-model="formModel.position" /></el-form-item>
			<el-row :gutter="12">
				<el-col :span="12">
					<el-form-item label="性别" prop="gender" required>
						<el-select v-model="formModel.gender" class="full-width">
							<el-option label="未知" value="未知" />
							<el-option label="男" value="男" />
							<el-option label="女" value="女" />
						</el-select>
					</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="学历"><el-input v-model="formModel.education" /></el-form-item>
				</el-col>
			</el-row>
			<el-form-item label="简介"><el-input v-model="formModel.intro" type="textarea" :rows="3" /></el-form-item>
			<el-form-item label="是否内部人员"><el-switch v-model="formModel.isInternal" /></el-form-item>
			<el-form-item label="是否是管理者"><el-switch v-model="formModel.isManager" /></el-form-item>
		</el-form>
		<template #footer>
			<el-button @click="emit('update:modelValue', false)">取消</el-button>
			<el-button type="primary" :loading="submitting" @click="handleSubmit">提交</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { ref, watch } from "vue";
import { ElMessage, type FormInstance, type FormRules } from "element-plus";
import type { EmployeeItem, EmployeeUpdatePayload } from "@/apis/org/employeeManage";

const props = defineProps<{
	modelValue: boolean;
	submitting: boolean;
	orgOptions: Array<{ id: string; label: string }>;
	data: EmployeeItem | null;
}>();

const emit = defineEmits<{
	(e: "update:modelValue", v: boolean): void;
	(e: "submit", payload: EmployeeUpdatePayload): void;
}>();

const formRef = ref<FormInstance>();
const formModel = ref<EmployeeUpdatePayload>({
	id: "",
	name: "",
	account: "",
	orgId: "",
	position: "",
	gender: "未知",
	education: "",
	birthday: "",
	graduateSchool: "",
	hireDate: "",
	intro: "",
	isInternal: true,
	isManager: false,
	photoUrl: "",
});

watch(
	() => props.data,
	(val) => {
		if (!val) return;
		formModel.value = {
			...formModel.value,
			id: val.id,
			name: val.name,
			account: val.account,
			orgId: val.orgId,
			position: val.position,
			gender: val.gender,
			isInternal: val.personType === "内部",
			isManager: val.roleName.includes("管理员"),
			hireDate: val.hireDate,
		};
	},
	{ immediate: true },
);

const rules: FormRules = {
	name: [{ required: true, message: "请输入姓名", trigger: "blur" }],
	account: [{ required: true, message: "请输入电话/登录账号", trigger: "blur" }],
	orgId: [{ required: true, message: "请选择机构", trigger: "change" }],
	position: [{ required: true, message: "请输入职位", trigger: "blur" }],
};

async function handleSubmit() {
	try {
		await formRef.value?.validate();
		emit("submit", { ...formModel.value });
	} catch {
		ElMessage.warning("请完善必填项");
	}
}
</script>

<style scoped>
.full-width {
	width: 100%;
}
</style>

