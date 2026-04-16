<template>
	<el-dialog v-model="visible" title="添加请款" width="600px" destroy-on-close>
		<el-form ref="formRef" :model="form" :rules="rules" label-width="120px">
			<el-row :gutter="20">
				<!-- 请款项目 -->
				<el-col :span="12">
					<el-form-item label="请款项目" prop="project">
						<el-input v-model="form.project" />
					</el-form-item>
				</el-col>

				<!-- 请款类型 -->
				<el-col :span="12">
					<el-form-item label="请款类型" prop="type">
						<el-select v-model="form.type" style="width: 100%">
							<el-option v-for="item in typeOptions" :key="item" :label="item" :value="item" />
						</el-select>
					</el-form-item>
				</el-col>

				<!-- 收款人 -->
				<el-col :span="12">
					<el-form-item label="收款人" prop="receiver">
						<el-input v-model="form.receiver" />
					</el-form-item>
				</el-col>

				<!-- 请款金额 -->
				<el-col :span="12">
					<el-form-item label="请款金额" prop="amount">
						<el-input-number v-model="form.amount" :min="0" :step="1" style="width: 100%" />
						<span style="margin-left: 5px">元</span>
					</el-form-item>
				</el-col>

				<!-- 收款账号 -->
				<el-col :span="24">
					<el-form-item label="收款账号" prop="account">
						<el-input v-model="form.account" />
					</el-form-item>
				</el-col>

				<!-- 请款说明 -->
				<el-col :span="24">
					<el-form-item label="请款说明">
						<el-input v-model="form.remark" type="textarea" rows="4" />
					</el-form-item>
				</el-col>

				<!-- 附件 -->
				<el-col :span="24">
					<el-form-item label="附件" prop="attachment">
						<el-upload
							action="#"
							:file-list="form.attachmentList"
							:on-change="handleUploadChange"
							:before-upload="beforeUpload"
							list-type="text"
						>
							<el-button size="small" type="primary">上传附件</el-button>
						</el-upload>
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
	project: "",
	type: "",
	receiver: "",
	amount: null,
	account: "",
	remark: "",
	attachmentList: [],
});

const rules = {
	project: [{ required: true, message: "请输入请款项目", trigger: "blur" }],
	type: [{ required: true, message: "请选择请款类型", trigger: "change" }],
	receiver: [{ required: true, message: "请输入收款人", trigger: "blur" }],
	amount: [{ required: true, message: "请输入请款金额", trigger: "change" }],
	account: [{ required: true, message: "请输入收款账号", trigger: "blur" }],
};

const typeOptions = ["广告宣传", "物业费", "办公耗材", "水费", "差旅费", "其他"];

const handleSubmit = () => {
	formRef.value.validate((valid) => {
		if (!valid) return;

		console.log("提交请款表单", form.value);

		visible.value = false;
	});
};

const open = (data = null) => {
	if (data) {
		Object.assign(form.value, data);
	} else {
		Object.assign(form.value, {
			project: "",
			type: "",
			receiver: "",
			amount: null,
			account: "",
			remark: "",
			attachmentList: [],
		});
	}
	visible.value = true;
};

// 上传处理
const handleUploadChange = ({ file, fileList }) => {
	form.value.attachmentList = fileList;
};
const beforeUpload = (file) => {
	// 这里可以限制文件类型或大小
	return true;
};

defineExpose({
	open,
});
</script>

<style scoped>
.el-upload {
	display: block;
}
</style>
