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
	<CourseInfoDialog
		ref="courseDialog"
		@edit="openEdit"
		@delete="handleDelete"
		@stop="handleStop"
		@rollCall="onRollCall"
	/>
	<EditCourseDialog ref="editDialogRef" />
</template>
<script setup>
import { ref } from "vue";
import CourseInfoDialog from "./CourseInfoDialog.vue";
import EditCourseDialog from "./EditCourseDialog.vue";
import { useCourseDetailStore } from "@/stores/console";
const courseDetailStore = useCourseDetailStore();
const courseDialog = ref();
const editDialogRef = ref();

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
	console.log("编辑", info);
	editDialogRef.value.open(info); // 再开编辑
};
const handleDelete = async (info) => {
	await courseDetailStore.deleteCourses([info.id]);
};

const handleStop = async (info) => {
	await courseDetailStore.toggleCourseStatus([info.id], "stop");
};
const onRollCall = (row) => console.log("点名消课", row);
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
