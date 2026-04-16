<template>
	<cui-dialog :title="title" :visible.sync="dialogVisible" @submit="formSubmit" width="400px" submitBtnText="立即上传">
		<div style="margin-bottom: 20px" v-if="templateUrl != ''">
			<el-button type="text" @click="downTemplate">点击此处下载模板</el-button>
			<small>, 模板中*开头的列为必填列</small>
		</div>
		<el-upload
			ref="upload"
			class="upload-demo"
			drag
			:action="uploadUrl"
			:headers="headers"
			multiple
			:on-success="onSuccess"
			:auto-upload="false"
			:data="params"
			accept=".xls,.xlsx"
		>
			<i class="el-icon-upload"></i>
			<div class="el-upload__text">
				将文件拖到此处，或
				<em>点击此处</em>
				开始导入
			</div>
			<div class="el-upload__tip" slot="tip">请上传.xls或.xlsx文件</div>
		</el-upload>
	</cui-dialog>
</template>
<script>
export default {
	props: {
		visible: {
			type: Boolean,
			required: true,
		},
		title: {
			type: String,
			default: "导 入",
		},
		templateUrl: {
			type: String,
			default: "",
		},
		importUrl: {
			type: String,
			default: "",
		},
		params: {
			type: Object,
			default: () => {
				return {};
			},
		},
	},
	data() {
		return {
			headers: {},
			uploadUrl: "yoururlpath",
		};
	},
	computed: {
		dialogVisible: {
			get: function () {
				if (!!this.visible) {
					this.$nextTick(() => {
						this.$refs.upload.clearFiles();
					});
				}
				return !!this.visible;
			},
			set: function (val) {
				this.$emit("update:visible", val);
			},
		},
	},
	methods: {
		// 提交
		formSubmit() {
			this.$refs.upload.submit();
		},
		// 上传成功
		onSuccess(res, file, fileList) {
			console.log(res, file, fileList);
		},
		downTemplate() {
			var url = (window.appBaseUrl || process.env.VUE_APP_BASE_API) + this.templateUrl;
			window.open(url, "_blank", "scrollbars=yes,resizable=1,modal=false,alwaysRaised=yes");
		},
	},
};
</script>
