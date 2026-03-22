<template>
	<AttendanceManagement
		ref="attendanceManagementRef"
		v-model="visible"
		:tip="tip"
		:columns="columns"
		:tableData="tableData"
		:actions="actions"
		@selection-change="handleSelectionChange"
	>
		<!-- 操作列插槽 -->
		<template #action="{ row }">
			<el-button type="text" @click="editRow(row)">编辑</el-button>
		</template>
	</AttendanceManagement>

	<el-button @click="showDialog">打开弹窗</el-button>
</template>

<script setup lang="ts">
import { ref } from "vue";
import AttendanceManagement from "@/components/attendanceManagement/AttendanceManagement.vue";
import type ActionItem from "@/components/attendanceManagement/type";
const visible = ref(false);

/** 提示文字 */
const tip = `【已签到】和【补签】会消课；【旷课】是否消课取决于默认配置；【请假】不会消课`;

/** 表头 */
const columns = [
	{ label: "学生姓名", prop: "name" },
	{ label: "电话", prop: "phone" },
	{ label: "消费课程", prop: "course" },
	{ label: "应扣课数", prop: "should" },
	{ label: "实扣课数", prop: "actual" },
	{ label: "签到方式", prop: "method" },
	{ label: "签到状态", prop: "status" },
	{ label: "到课信息", prop: "info" },
];

/** 表格数据 */
const tableData = ref([
	{
		name: "张三",
		phone: "13800000000",
		course: "数学",
		should: 2,
		actual: 2,
		method: "扫码",
		status: "已签到",
		info: "正常",
	},
]);

const actions: ActionItem[] = [
	{
		label: "设为已签到",
		type: "primary",
		onClick: (rows: any[]) => {
			console.log("已签到:", rows);
		},
	},
	{
		label: "设为补签",
		onClick: (rows: any[]) => {
			console.log("补签:", rows);
		},
	},
	{
		label: "设为旷课",
		onClick: (rows: any[]) => {
			console.log("旷课:", rows);
		},
	},
	{
		label: "设为请假",
		onClick: (rows: any[]) => {
			console.log("请假:", rows);
		},
	},
	{
		label: "一键点名",
		type: "primary",
		onClick: (rows: any[]) => {
			console.log("一键点名:", rows);
		},
	},
	{
		label: "添加学生",
		type: "success",
		onClick: () => {
			console.log("添加学生");
		},
	},
];

const handleSelectionChange = (rows: any[]) => {
	console.log("父组件拿到选中数据:", rows);
};

const editRow = (row: any) => {
	console.log("编辑:", row);
};
const attendanceManagementRef = ref();
const showDialog = () => {
	attendanceManagementRef.value.showDialog();
};
</script>
