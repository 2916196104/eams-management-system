<template>
	<el-dialog :model-value="modelValue" title="添加员工" width="760px" destroy-on-close @close="handleClose">
		<el-form ref="formRef" :model="formModel" :rules="rules" label-width="96px">
			<el-form-item label="姓名" prop="name" required>
				<el-input v-model="formModel.name" maxlength="20" placeholder="请输入员工姓名" />
			</el-form-item>
			<el-form-item label="电话/登录账号" prop="account" required>
				<el-input v-model="formModel.account" maxlength="20" placeholder="请输入手机号或账号" />
			</el-form-item>
			<el-form-item label="所属机构" prop="orgId" required>
				<el-select v-model="formModel.orgId" placeholder="请选择" class="full-width">
					<el-option v-for="item in orgOptions" :key="item.id" :label="item.label" :value="item.id" />
				</el-select>
			</el-form-item>
			<el-form-item label="所属职位" prop="position" required>
				<el-input v-model="formModel.position" maxlength="30" placeholder="请输入职位" />
			</el-form-item>

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
					<el-form-item label="学历">
						<el-select v-model="formModel.education" class="full-width" placeholder="请选择">
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
						<el-date-picker v-model="formModel.birthday" type="date" value-format="YYYY-MM-DD" class="full-width" />
					</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="入职日期">
						<el-date-picker v-model="formModel.hireDate" type="date" value-format="YYYY-MM-DD" class="full-width" />
					</el-form-item>
				</el-col>
			</el-row>

			<el-form-item label="毕业学校">
				<el-input v-model="formModel.graduateSchool" maxlength="40" placeholder="请输入毕业学校" />
			</el-form-item>
			<el-form-item label="简介">
				<el-input v-model="formModel.intro" type="textarea" :rows="3" maxlength="200" show-word-limit placeholder="请输入简介" />
			</el-form-item>

			<el-form-item label="是否内部人员">
				<el-switch v-model="formModel.isInternal" />
			</el-form-item>
			<el-form-item label="是否是管理者">
				<el-switch v-model="formModel.isManager" />
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
			<el-button @click="handleClose">取消</el-button>
			<el-button type="primary" :loading="submitting" @click="handleSubmit">提交</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { computed, ref, watch } from "vue";
import { ElMessage, type FormInstance, type FormRules, type UploadRawFile } from "element-plus";
import type { EmployeeCreatePayload } from "@/apis/org/employeeManage";

interface OrgOption {
	id: string;
	label: string;
}

const DRAFT_KEY = "employee-manage:add-draft:v1";

const props = defineProps<{
	modelValue: boolean;
	orgOptions: OrgOption[];
	defaultOrgId: string;
	submitting: boolean;
}>();

const emit = defineEmits<{
	(e: "update:modelValue", v: boolean): void;
	(e: "submit", payload: EmployeeCreatePayload): void;
}>();

const formRef = ref<FormInstance>();
const formModel = ref<EmployeeCreatePayload>({
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

const rules: FormRules = {
	name: [{ required: true, message: "请输入姓名", trigger: "blur" }],
	account: [
		{ required: true, message: "请输入电话/登录账号", trigger: "blur" },
		{ min: 6, message: "账号长度至少6位", trigger: "blur" },
	],
	orgId: [{ required: true, message: "请选择机构", trigger: "change" }],
	position: [{ required: true, message: "请输入职位", trigger: "blur" }],
	gender: [{ required: true, message: "请选择性别", trigger: "change" }],
};

const mergedDefaultOrgId = computed(() => props.defaultOrgId || props.orgOptions[0]?.id || "");

watch(
	() => props.modelValue,
	(open) => {
		if (!open) return;
		restoreDraft();
		if (!formModel.value.orgId) formModel.value.orgId = mergedDefaultOrgId.value;
	},
);

watch(
	formModel,
	() => {
		if (!props.modelValue) return;
		try {
			localStorage.setItem(DRAFT_KEY, JSON.stringify(formModel.value));
		} catch {
			// ignore
		}
	},
	{ deep: true },
);

function restoreDraft() {
	try {
		const raw = localStorage.getItem(DRAFT_KEY);
		if (!raw) return;
		formModel.value = { ...formModel.value, ...JSON.parse(raw) };
		ElMessage.info("已恢复上次未提交的表单内容");
	} catch {
		// ignore
	}
}

function resetForm() {
	formModel.value = {
		name: "",
		account: "",
		orgId: mergedDefaultOrgId.value,
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
	};
}

function handleClose() {
	emit("update:modelValue", false);
}

function handleBeforeUpload(file: UploadRawFile) {
	if (!file.type.startsWith("image/")) {
		ElMessage.warning("仅支持图片文件");
		return false;
	}
	formModel.value.photoUrl = URL.createObjectURL(file);
	return false;
}

async function handleSubmit() {
	try {
		await formRef.value?.validate();
		emit("submit", { ...formModel.value });
		try {
			localStorage.removeItem(DRAFT_KEY);
		} catch {
			// ignore
		}
		resetForm();
	} catch {
		ElMessage.warning("请先完成必填项");
	}
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
}

.placeholder {
	display: flex;
	align-items: center;
	justify-content: center;
	color: #c0c4cc;
}
</style>

