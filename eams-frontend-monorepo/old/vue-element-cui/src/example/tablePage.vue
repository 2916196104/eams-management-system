<template>
	<div class="app-container">
		<!-- 搜索组件 -->
		<cui-search :config="searchConfig" :showExport="true" @handleRequest="handleRequest"></cui-search>
		<!-- 数据表 -->
		<cui-table ref="tableBuilder" :config="tableConfig" :selectedRows.sync="selectedRows"></cui-table>
		<!-- 弹窗表单 -->
		<cui-dialog-form
			ref="cuiDialogForm"
			title="在学学员"
			:formConfig="formConfig"
			:visible.sync="formVisible"
			@onSubmit="onSubmit"
		></cui-dialog-form>
		<!-- excel导入 -->
		<cui-excel
			:visible.sync="excelVisible"
			templateUrl="/common/student/export"
			importUrl="/common/student/import"
			:params="uploadParam"
			@onSuccess="onSuccess"
		/>
		<!-- 弹出框 -->
		<cui-dialog-form
			ref="changeCounselor"
			title="设置顾问"
			:formConfig="formConfig3"
			:visible.sync="formVisible3"
			@onSubmit="onSubmit3"
		></cui-dialog-form>
	</div>
</template>
<script>
import apis from "@/api/apis";

export default {
	name: "StudentLearning",
	data() {
		return {
			courseRecord: [],
			tableConfig: {
				url: apis.studentList,
				selectable: true,
				fields: [
					{ title: "编号", name: "id", width: "80px" },
					{
						title: "学员姓名",
						width: "80px",
						content: (row) => {
							return (
								<span class='text-link' onClick={() => {}}>
									{row.name}
								</span>
							);
						},
					},
					{
						title: "家长姓名",
						name: "parentName",
						width: "70px",
						visible: () => {
							return false;
						},
					},
					{ title: "亲属关系", name: "familyRel", width: "70px" },
					{ title: "可编辑电话", name: "mobile", width: "150px", editable: true, editFunc: this.handleEditField },
					{
						title: "可编辑ENUM",
						name: "mobile",
						width: "150px",
						editable: true,
						editFunc: this.handleEditField,
						editConf: { type: "enum", code: "DateRangeNameEnum" },
					},
					{
						title: "可编辑enumCheckbox",
						name: "mobile",
						width: "150px",
						editable: true,
						editFunc: this.handleEditField,
						editConf: { type: "enumCheckbox", code: "DateRangeNameEnum" },
					}, // , disabled: true 可以禁用编辑
					{
						title: "可编辑dict",
						name: "mobile",
						width: "150px",
						editable: true,
						editFunc: this.handleEditField,
						editConf: { type: "dict", code: "DateRangeNameEnum" },
					},
					{ title: "顾问", name: "counselorName", width: "80px" },
					{ title: "性别", name: "gender", width: "50px" },
					{ title: "年龄", name: "age", width: "50px" },
					{ title: "备注", name: "remark" },
				],
				actionWidth: 200,
				actions: [
					{
						title: "查看",
						click: (row) => {
							console.log(row);
						},
					},
					{
						title: "修改",
						pms: "studentsave", // 权限标记，有选择则显示
						click: async (row) => {
							console.log(row);
						},
					},
					{
						title: "操作",
						type: "list",
						options: [
							{
								title: "查看",
								click: (row) => {
									console.log(row);
								},
							},
							{
								title: "修改",
								pms: "studentsave",
								click: async (row) => {
									console.log(row);
								},
							},
						],
					},
				],
				topActions: [
					{
						title: "添加学员",
						type: "primary",
						icon: "el-icon-plus",
						click: () => {
							this.handleAdd();
						},
					},
					{
						title: "结业",
						icon: "el-icon-check",
						click: () => {
							if (this.selectedRows.length == 0) {
								this.$message("请选择");
							}
						},
					},
					{
						title: "导入在学学员",
						icon: "el-icon-upload2",
						click: (rows) => {
							this.uploadParam = { stage: 2 };
							this.excelVisible = true;
						},
					},
					{
						title: "修改顾问",
						icon: "el-icon-user",
						click: () => {
							if (this.selectedRows.length != 1) {
								this.$message("请选择1位学员");
								return;
							}
							this.studentInfo.id = this.selectedRows[0].id;
							this.formVisible3 = true;
						},
					},
				],
				condition: { stage: 2 },
			},
			selectedRows: [],
			searchConfig: {
				fields: [
					{
						label: "学员姓名",
						name: "keyword",
						type: "input",
						placeholder: "姓名或电话",
					},
					{ label: "周期", name: "dateRange", type: "enum", code: "DateRangeNameEnum" },
					{ label: "班级", name: "classIds", type: "selectBox", code: "class" },
					{ label: "课程", name: "courseIds", type: "selectBox", code: "course" },
					{ label: "老师", name: "teacherIds", type: "selectBox", code: "teacher", limit: 1 },
					{ label: "科目", name: "subjectId", type: "select", code: "subject", hidden: true },
					{ label: "开始日期", name: "startDate", type: "date", hidden: true },
					{ label: "结束日期", name: "endDate", type: "date", hidden: true },
				],
			},

			formConfig: {
				fields: [
					{ label: "手机号", name: "mobile", type: "input", cantEdit: true },
					{ label: "家长姓名", name: "parentName", type: "input" },
					{
						label: "亲属关系",
						name: "familyRel",
						type: "enum",
						code: "FamilyRelationshipEnum",
					},
					{ label: "学员姓名", name: "name", type: "input" },
					{
						label: "学生性别",
						name: "gender",
						type: "enum",
						code: "GenderEnum",
					},
					{ label: "出生年月", name: "birthday", type: "date" },
					{ label: "身份证号", name: "idcard", type: "input" },
					{
						label: "来源",
						name: "joinWay",
						type: "dict",
						code: "customer_source",
					},
					{ label: "备注", name: "remark", type: "textarea" },
				],
				rules: {
					name: [{ required: true, message: "请输入姓名" }],
					mobile: [
						{
							required: true,
							validator: async (rule, value) => {
								if (!isPhone(value)) {
									throw new Error("请输入有效手机号");
								}
							},
						},
					],
					gender: [{ required: true, message: "请选择性别" }],
				},
			},
			formVisible: false, // 显示与隐藏

			studentInfo: {
				id: "",
				name: "",
			},
			creatContractVisible: false,

			// 导入
			excelVisible: false,
			uploadParam: {},

			formConfig3: {
				fields: [
					{
						label: "选择顾问",
						name: "staffId",
						type: "selectBox",
						code: "staff",
						limit: 1,
					},
				],
				rules: {
					staffId: [{ required: true, message: "请选择顾问" }],
				},
			},
			formVisible3: false,
		};
	},
	created() {},
	methods: {
		handleEditField(a, b, c) {
			console.log("编辑参数", a, b, c);
		},
		handleEdit: async function (studentId) {
			this.formVisible = true;
			const initData = await getStudentInfo(studentId);
			this.$refs.cuiDialogForm.initFormData(initData);
		},
		handleAdd() {
			this.formVisible = true;
			this.$refs.cuiDialogForm.onReset();
		},
		handleRequest(searchParam) {
			if (searchParam) Object.assign(this.tableConfig.condition, searchParam);
			this.$refs.tableBuilder.loadData();
		},

		onSubmit: async function (formData) {
			formData.stage = "在学学员";
			const res = await saveStudent(formData);
			if (bizSuccess(res)) {
				this.$refs.cuiDialogForm.onReset();
				this.$refs.tableBuilder.loadData();
			}
		},
		onSuccess() {},
		onSubmit() {},
		onSubmit3() {},
	},
};
</script>
