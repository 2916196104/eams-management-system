<template>
	<div class="upload-container">
		<el-button
			:style="{ background: color, borderColor: color }"
			icon="el-icon-upload"
			size="mini"
			type="primary"
			@click="dialogVisible = true"
		>
			上传
		</el-button>
		<el-dialog
			:visible.sync="dialogVisible"
			:modal="false"
			title="请选择上传文件"
			width="600px"
			custom-class="custom-dialog"
		>
			<el-upload
				:multiple="true"
				:file-list="fileList"
				:show-file-list="true"
				:on-success="handleSuccess"
				:before-upload="beforeUpload"
				:accept="acceptTypes"
				class="editor-slide-upload"
				:action="uploadUrl"
				:headers="headers"
				:list-type="isImg ? 'picture' : 'text'"
			>
				<el-button size="small" type="primary">选择文件</el-button>
			</el-upload>
			<span slot="footer" class="dialog-footer">
				<el-button @click="dialogVisible = false">取 消</el-button>
				<el-button type="primary" @click="handleSubmit">确 定</el-button>
			</span>
		</el-dialog>
	</div>
</template>

<script>
export default {
	name: "EditorSlideUpload",
	props: {
		param: {
			type: Object,
		},
		color: {
			type: String,
			default: "#1890ff",
		},
		isImg: {
			type: Boolean,
			default: false,
		},
		acceptTypes: {
			type: String,
			default: "",
		},
	},
	data() {
		return {
			headers: {},
			uploadUrl: "youruploadurl", // 请自行实现post上传方法
			dialogVisible: false,
			fileList: [],
		};
	},
	methods: {
		// 确认操作
		handleSubmit() {
			var res = [];
			for (var file of this.fileList) {
				res.push({
					name: file.name,
					url: file.response.url,
					attaId: file.response.attaId,
				});
			}
			this.$emit("successCBK", res, this.param);
			this.fileList = [];
			this.dialogVisible = false;
		},
		// 处理上传后返回结果
		handleSuccess(response, file, fileList) {
			if (typeof response.errCode == "undefined") {
				this.fileList = fileList;
			} else {
				for (var idx in fileList) {
					if (fileList[idx].uid == file.uid) {
						fileList.splice(idx, 1);
						return;
					}
				}
			}
		},
		// 上传前验证
		beforeUpload(file) {
			const isLt2M = file.size / 1024 / 1024 < 10;
			if (!isLt2M) {
				this.$message.error("上传文件大小不能超过 10MB!");
				return false;
			}
		},
	},
};
</script>
<style lang="scss" scoped>
.editor-slide-upload {
	margin-bottom: 20px;
	::v-deep .el-upload--picture-card {
		width: 100%;
	}
}
</style>
