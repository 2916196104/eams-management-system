<template>
	<el-dialog :model-value="modelValue" title="修改员工" width="760px" destroy-on-close @close="emit('update:modelValue', false)">
		<el-form ref="formRef" :model="formModel" :rules="rules" label-width="120px">
			<el-form-item label="姓名" prop="name" required>
				<el-input v-model="formModel.name" maxlength="20" placeholder="请输入员工姓名" />
			</el-form-item>
			<el-form-item label="电话/登录账号" prop="account" required>
				<el-input v-model="formModel.account" maxlength="20" placeholder="请输入手机号或账号" />
			</el-form-item>
			<el-form-item label="所属机构" prop="orgId" required>
				<el-select v-model="formModel.orgId" class="full-width" placeholder="请选择机构">
					<el-option v-for="item in orgOptions" :key="item.id" :label="item.label" :value="item.id" />
				</el-select>
			</el-form-item>
			<el-form-item label="所属职位" prop="position" required>
				<el-input v-model="formModel.position" maxlength="30" placeholder="请输入职位" />
			</el-form-item>

			<el-row :gutter="12">
				<el-col :span="12">
					<el-form-item label="性别" prop="gender" required>
						<el-select v-model="formModel.gender" class="full-width" placeholder="请选择性别">
							<el-option label="未知" value="未知" />
							<el-option label="男" value="男" />
							<el-option label="女" value="女" />
						</el-select>
					</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="学历" prop="education">
						<el-select v-model="formModel.education" class="full-width" placeholder="请选择学历">
							<el-option label="未知" value="未知" />
							<el-option label="本科" value="本科" />
							<el-option label="硕士" value="硕士" />
							<el-option label="博士" value="博士" />
						</el-select>
					</el-form-item>
				</el-col>
			</el-row>

			<el-row :gutter="12">
				<el-col :span="12">
					<el-form-item label="生日">
						<el-date-picker
							v-model="formModel.birthday"
							type="date"
							value-format="YYYY-MM-DD"
							class="full-width"
							placeholder="请选择生日"
						/>
					</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="入职日期">
						<el-date-picker
							v-model="formModel.hireDate"
							type="date"
							value-format="YYYY-MM-DD"
							class="full-width"
							placeholder="请选择入职日期"
						/>
					</el-form-item>
				</el-col>
			</el-row>

			<el-form-item label="毕业院校">
				<el-input v-model="formModel.graduateSchool" maxlength="40" placeholder="请输入毕业院校" />
			</el-form-item>

			<el-form-item label="简介">
				<el-input v-model="formModel.intro" type="textarea" :rows="3" maxlength="200" show-word-limit placeholder="请输入简介" />
			</el-form-item>

			<el-form-item label="是否内部人员">
				<el-switch v-model="formModel.isInternal" />
			</el-form-item>

			<el-form-item label="是否管理员">
				<el-switch v-model="formModel.isManager" disabled />
				<span class="hint-text">管理者不会出现在师资列表里</span>
			</el-form-item>

			<el-form-item label="照片">
				<div class="upload-wrap">
					<el-image v-if="formModel.photoUrl" class="preview-img" :src="formModel.photoUrl" fit="cover" />
					<div v-else class="preview-img placeholder">暂无</div>
					<el-upload :auto-upload="false" :show-file-list="false" :before-upload="handleBeforeUpload">
						<el-button type="primary" plain>上传</el-button>
					</el-upload>
				</div>
			</el-form-item>
		</el-form>
		<template #footer>
			<el-button @click="emit('update:modelValue', false)">取消</el-button>
			<el-button type="primary" :loading="submitting" @click="handleSubmit">提交</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { ref, watch } from "vue";
import { ElMessage, type FormInstance, type FormRules, type UploadRawFile } from "element-plus";
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
	education: "未知",
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
	gender: [{ required: true, message: "请选择性别", trigger: "change" }],
	education: [{ required: true, message: "请选择学历", trigger: "change" }],
};

async function handleSubmit() {
	try {
		await formRef.value?.validate();
		emit("submit", { ...formModel.value });
	} catch {
		ElMessage.warning("请完善必填项");
	}
}

function handleBeforeUpload(file: UploadRawFile) {
	// 仅用于前端展示；真实上传由后端编辑接口处理
	if (!file.type.startsWith("image/")) {
		ElMessage.warning("仅支持图片文件");
		return false;
	}
	formModel.value.photoUrl = URL.createObjectURL(file);
	return false;
}
</script>

<style scoped>
.full-width {
	width: 100%;
}

.hint-text {
	margin-left: 8px;
	color: #909399;
	font-size: 12px;
}

.upload-wrap {
	display: flex;
	align-items: flex-end;
	gap: 12px;
}

.preview-img {
	width: 100px;
	height: 100px;
	border: 1px dashed #dcdfe6;
	border-radius: 6px;
	overflow: hidden;
}

.placeholder {
	display: flex;
	align-items: center;
	justify-content: center;
	color: #c0c4cc;
}
</style>

