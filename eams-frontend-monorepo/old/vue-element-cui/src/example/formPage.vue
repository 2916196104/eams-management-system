<template>
	<div>
		<cui-form ref="formRef" :config="formConfig" @update="formUpdate"></cui-form>
		<el-button @click="formSubmit()">提交</el-button>
	</div>
</template>
<script>
const initData = {
	id: "",
	classId: "",
	courseId: "",
	teacherIds: "",
	assistantIds: "",
	startDate: "",
	endDate: "",
	roomId: "",
	images: null,
	files: null,
	decCount: 1,
};
export default {
	name: "CreateLesson",
	components: {},
	data() {
		return {
			// 表单参数
			formConfig: {
				fields: [
					{ label: "标题", name: "title", type: "input", info: "标题字数要50字以内" },
					{
						label: "选择班级",
						name: "classId",
						span: 12,
						type: "selectBox",
						code: "class",
						limit: 1,
						condition: { over: true },
					},
					{
						label: "上课老师",
						name: "teacherIds",
						span: 12,
						type: "selectBox",
						code: "teacher",
						info: "支持多个老师，第一位为主讲人",
					},
					{ label: "助教老师", name: "assistantIds", span: 12, type: "selectBox", code: "teacher" },
					{ label: "类型", name: "typeName", span: 12, type: "enum", code: "TeachTypeEnum" },
					{ label: "上课日期", name: "date", type: "date", span: 8 },
					{ label: "开始时间", name: "startTime", type: "time", span: 8 },
					{ label: "结束时间", name: "endTime", type: "time", minTime: "startTime", span: 8 },
					{ label: "选择教室", name: "roomId", type: "selectBox", code: "classroom", limit: 1 },
					{ label: "消课次数", name: "decCount", type: "number" },
					{ label: "上传图片", name: "images", type: "img", limit: 1 },
					{ label: "上传文件", name: "files", type: "file", limit: 1 },
				],
				rules: {
					classId: [{ required: true, message: "请选择班级", trigger: "change" }],
					teacherIds: [{ required: true, message: "请选择上课老师", trigger: "change" }],
					date: [{ required: true, message: "请设置上课日期" }],
					startTime: [{ required: true, message: "请选择开始日期" }],
					endTime: [{ required: true, message: "请选择结束日期" }],
				},
			},
			formData: Object.assign({}, initData),
		};
	},
	computed: {
		dialogVisible: {
			get: function () {
				return !!this.visible;
			},
			set: function (val) {
				this.$emit("update:visible", val);
			},
		},
	},
	created() {},
	methods: {
		// 表单数据更新
		formUpdate(value) {
			this.formData = value;
		},
		formSubmit: async function () {
			var postData = Object.assign({}, this.formData);
			console.log("提交参数");
			console.log(postData);
			const valid = await this.$refs.formRef.onValidate();
			if (valid !== true) return;
		},
		// 表单初始化数据方法
		initData: async function (data) {
			if (typeof data === "undefined") {
				data = initData;
			}
			setTimeout(() => {
				this.$refs.formRef.setInitData(data);
			}, 50);
		},
	},
};
</script>
