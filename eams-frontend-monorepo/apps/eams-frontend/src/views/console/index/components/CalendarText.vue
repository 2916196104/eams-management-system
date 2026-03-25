<template>
	<el-tooltip transition="none" effect="light" placement="right">
		<template #content>
			<div class="calendar-tooltip">
				<div>标题：{{ info.title }}</div>
				<div>课程：{{ info.courseName }}</div>
				<div>老师：{{ info.teacherName }}</div>
				<div v-if="!info.courseCalendarType">学生：{{ info.studentName }}</div>
				<div>类型：{{ info.classType }}</div>
				<div>日期：{{ info.Date }}</div>
				<div>时间：{{ info.startTime }}~{{ info.endTime }}</div>
				<div>班级：{{ info.className }}</div>
				<div>教室：{{ info.classroomName }}</div>
				<div>状态：{{ info.courseStatus }}</div>
			</div>
		</template>
		<el-button @click="showDialog" text class="calendar-text">
			<div class="dot"></div>
			<slot name="default"></slot>
		</el-button>
	</el-tooltip>
	<course-info-dialog
		ref="courseDialog"
		@edit="openEdit"
		@delete="handleDelete"
		@stop="handleStop"
		@rollCall="onRollCall"
	/>
	<edit-course-dialog ref="editDialogRef" />
	<attendance-management
		ref="attendanceDialogRef"
		title="点名管理"
		:tip="tip"
		:tableData="tableData"
		:columns="columns"
		:actions="actions"
		@selection-change="handleSelectionChange"
	>
		<template #default="{}"></template>
	</attendance-management>
</template>
<script setup>
import { ref } from "vue";
import CourseInfoDialog from "./CourseInfoDialog.vue";
import EditCourseDialog from "./EditCourseDialog.vue";
import AttendanceManagement from "@/components/attendanceManagement/AttendanceManagement.vue";
import { useCourseDetailStore } from "@/stores/console";
const courseDetailStore = useCourseDetailStore();
const courseDialog = ref();
const editDialogRef = ref();
const attendanceDialogRef = ref();

const props = defineProps({
	info: {
		type: Object,
		default: () => ({}),
	},
});
const showDialog = async () => {
	// 调用 store 请求课程详情
	await courseDetailStore.fetchCourseDetail(props.info.id);
	// 弹窗显示获取到的详情
	courseDialog.value.open({
		...courseDetailStore.courseDetail, // 展开 courseDetail 对象
		id: props.info.id,
	});
};

const openEdit = (info) => {
	editDialogRef.value.open(info); // 再开编辑
};
const handleDelete = async (info) => {
	await courseDetailStore.deleteCourses([info.id]);
};

const handleStop = async (info) => {
	await courseDetailStore.toggleCourseStatus([info.id], "stop");
};
const onRollCall = () => {
	attendanceDialogRef.value.showDialog();
};
/** 提示文字 */
const tip = `【已签到】和【补签】会消课；【旷课】是否消课取决于默认配置；【请假】不会消课`;
/** 按钮操作 */
const actions = ref([
	{
		label: "随到随学",
		type: "success",
		onClick: (rows) => {
			console.log("已添加:", rows);
		},
	},
	{
		label: "设为已签到",
		type: "primary",
		onClick: (rows) => {
			console.log("已签到:", rows);
		},
	},
	{
		label: "设为补签",
		onClick: (rows) => {
			console.log("补签:", rows);
		},
	},
	{
		label: "设为旷课",
		onClick: (rows) => {
			console.log("旷课:", rows);
		},
	},
	{
		label: "设为请假",
		onClick: (rows) => {
			console.log("请假:", rows);
		},
	},
]);
/** 表格数据 */
const tableData = ref([
	{ id: 1, name: "张三", age: 20 },
	{ id: 2, name: "李四", age: 22 },
]);

/** 表格列 */
const columns = ref([
	{ label: "学生姓名", prop: "studentName" },
	{ label: "电话", prop: "age" },
	{ label: "消费课程", prop: "name" },
	{ label: "应扣课树", prop: "age" },
	{ label: "实扣课数", prop: "name" },
	{ label: "签到方式", prop: "age" },
	{ label: "签到状态", prop: "name" },
	{ label: "到课信息", prop: "age" },
]);
</script>
<style scoped>
.calendar-tooltip {
	width: 220px;
	padding: 8px;
	font-size: 14px;
	line-height: 150%;
	color: #666666;
}
.calendar-text:hover {
	background-color: var(--el-button-hover-bg-color) !important;
}
.calendar-text {
	display: inline-flex;
	align-items: center; /* 垂直居中圆点和文本 */
	justify-content: flex-start; /* 水平靠左 */
	white-space: nowrap;
	overflow: hidden;
	max-width: 150px; /* 根据需要设置最大宽度 */
	padding: 0;
	height: auto;
}
.dot {
	width: 10px;
	height: 10px;
	border-radius: 50%;
	background-color: rgb(103, 194, 58);
	flex-shrink: 0;
	margin-right: 5px;
}
</style>
