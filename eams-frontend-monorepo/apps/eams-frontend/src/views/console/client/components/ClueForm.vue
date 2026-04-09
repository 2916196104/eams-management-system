<template>
	<el-dialog v-model="visible" title="添加线索" width="600px" destroy-on-close>
		<el-form ref="formRef" :model="form" :rules="rules" label-width="100px">
			<el-row :gutter="20">
				<!-- 手机号 -->
				<el-col>
					<el-form-item label="手机号" prop="phone">
						<el-input v-model="form.phone" />
					</el-form-item>
				</el-col>

				<!-- 家长姓名 -->
				<el-col>
					<el-form-item label="家长姓名">
						<el-input v-model="form.parentName" />
					</el-form-item>
				</el-col>

				<!-- 亲属关系 -->
				<el-col>
					<el-form-item label="亲属关系">
						<el-select v-model="form.relation" style="width: 100%">
							<el-option v-for="item in relationOptions" :key="item" :label="item" :value="item" />
						</el-select>
					</el-form-item>
				</el-col>

				<!-- 学员姓名 -->
				<el-col>
					<el-form-item label="学员姓名" prop="studentName">
						<el-input v-model="form.studentName" />
					</el-form-item>
				</el-col>

				<!-- 学生性别 -->
				<el-col>
					<el-form-item label="学生性别" prop="gender">
						<el-select v-model="form.gender" style="width: 100%">
							<el-option label="未知" value="未知" />
							<el-option label="男" value="男" />
							<el-option label="女" value="女" />
						</el-select>
					</el-form-item>
				</el-col>

				<!-- 入学时间 -->
				<el-col>
					<el-form-item label="入学时间">
						<el-date-picker v-model="form.entranceDate" type="date" style="width: 100%" />
					</el-form-item>
				</el-col>

				<!-- 年级 -->
				<el-col>
					<el-form-item label="年级">
						<el-select v-model="form.grade" style="width: 100%">
							<el-option label="2027级" value="2027级" />
							<el-option label="2026级" value="2026级" />
							<el-option label="2025级" value="2025级" />
							<el-option label="2024级" value="2024级" />
							<el-option label="2023级" value="2023级" />
						</el-select>
					</el-form-item>
				</el-col>

				<!-- 出生年月 -->
				<el-col>
					<el-form-item label="出生年月">
						<el-date-picker v-model="form.birthDate" type="month" style="width: 100%" />
					</el-form-item>
				</el-col>

				<!-- 身份证号 -->
				<el-col>
					<el-form-item label="身份证号">
						<el-input v-model="form.idCard" />
					</el-form-item>
				</el-col>

				<!-- 来源 -->
				<el-col>
					<el-form-item label="来源">
						<el-select v-model="form.source" style="width: 100%">
							<el-option label="抖音平台" value="抖音平台" />
							<el-option label="微信登记" value="微信登记" />
							<el-option label="活动报名" value="活动报名" />
							<el-option label="主动咨询" value="主动咨询" />
						</el-select>
					</el-form-item>
				</el-col>

				<!-- 备注 -->
				<el-col :span="24">
					<el-form-item label="备注">
						<el-input v-model="form.remark" type="textarea" rows="3" />
					</el-form-item>
				</el-col>
			</el-row>
		</el-form>

		<template #footer>
			<el-button @click="visible = false">取消</el-button>
			<el-button type="primary" @click="handleSubmit">确定</el-button>
		</template>
	</el-dialog>
</template>

<script setup>
import { ref } from "vue";

const visible = ref(false);
const formRef = ref();

const form = ref({
	phone: "",
	parentName: "",
	relation: "",
	studentName: "",
	gender: "",
	entranceDate: "",
	grade: "",
	birthDate: "",
	idCard: "",
	source: "",
	remark: "",
});

const rules = {
	phone: [{ required: true, message: "请输入手机号", trigger: "blur" }],
	studentName: [{ required: true, message: "请输入学员姓名", trigger: "blur" }],
	gender: [{ required: true, message: "请选择性别", trigger: "change" }],
};

const relationOptions = ["无", "爸爸", "妈妈", "爷爷", "奶奶", "姥爷", "姥姥", "叔叔", "姑姑", "其他"];

const handleSubmit = () => {
	formRef.value.validate((valid) => {
		if (!valid) return;

		console.log("提交表单", form.value);

		visible.value = false;
	});
};

// 暴露方法给父组件
const open = () => {
	visible.value = true;
};

defineExpose({
	open,
});
</script>
