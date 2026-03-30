<template>
	<el-dialog
		v-model="visible"
		destroy-on-close
		:close-on-click-modal="false"
		title="课程信息"
		width="600px"
		class="course-dialog"
	>
		<!-- 内容 -->
		<div style="margin: 10px">
			<ul style="line-height: 180%">
				<li v-for="(item, index) in infoList" :key="index">{{ item.label }}: {{ info[item.prop] }}</li>
			</ul>
		</div>

		<!-- 按钮 -->
		<div style="text-align: right">
			<el-button text type="primary" size="small" @click="handleEdit" :icon="EditPen">修 改</el-button>
			<el-button text type="primary" size="small" @click="handleDelete" :icon="Delete">删 除</el-button>
			<el-button text type="primary" size="small" @click="handleStop" :icon="Close">停 课</el-button>
			<el-button text type="primary" size="small" @click="handleRollCall" :icon="Finished">点名消课</el-button>
		</div>
		<template #footer>
			<el-button @click="close">关 闭</el-button>
		</template>
	</el-dialog>
</template>

<script setup>
import { ref, reactive } from "vue";
import { EditPen, Delete, Close, Finished } from "@element-plus/icons-vue";
/* 弹窗显示 */
const visible = ref(false);

/* 课程信息 */
const info = reactive({
	id: 0,
	title: "",
	courseName: "",
	className: "",
	courseType: "",
	lessonTimeText: "",
	classroomName: "",
	teacherName: "",
	assistantName: "",
	attendInfo: 0,
	decLessonCount: 0,
	canReserve: "",
	status: "",
});
/* 信息列表，用于循环渲染 */
const infoList = [
	{ label: "标 题", prop: "title" },
	{ label: "课 程", prop: "courseName" },
	{ label: "班 级", prop: "className" },
	{ label: "类 型", prop: "courseType" },
	{ label: "时 间", prop: "lessonTimeText" },
	{ label: "教 室", prop: "classroomName" },
	{ label: "老 师", prop: "teacherName" },
	{ label: "助 教", prop: "assistantName" },
	{ label: "实到/应到", prop: "attendInfo" },
	{ label: "消课基数", prop: "decLessonCount" },
	{ label: "是否可预约", prop: "canReserve" },
	{ label: "状 态", prop: "status" },
];

/* 打开弹窗 */
const open = (data) => {
	Object.assign(info, data);
	visible.value = true;
};

/* 关闭弹窗 */
const close = () => {
	visible.value = false;
};

/* 按钮事件（向外抛） */
const emit = defineEmits(["edit", "delete", "stop", "mm            "]);

const handleEdit = () => emit("edit", info);
const handleDelete = async () => {
	try {
		await ElMessageBox.confirm("确认要删除这条课程吗？", "删除确认", {
			confirmButtonText: "确定",
			cancelButtonText: "取消",
			type: "error",
		});
		// 用户点击确定，触发删除事件
		emit("delete", info);
		ElMessage({
			type: "success",
			message: "已删除课程",
		});
	} catch {}
};
const handleStop = async () => {
	try {
		await ElMessageBox.confirm("确认要停止这条课程吗？", "停课确认", {
			confirmButtonText: "确定",
			cancelButtonText: "取消",
			type: "warning",
		});
		// 用户点击确定，触发删除事件
		emit("stop", info);
		ElMessage({
			type: "success",
			message: "已停止课程",
		});
	} catch {}
};
const handleRollCall = () => emit("rollCall", info);

/* 对外暴露方法 */
defineExpose({
	open,
	close,
});
</script>

<style>
.course-dialog {
	padding: 0;
}
.course-dialog .el-dialog__header {
	background-color: #e4f2ff;
	padding-top: 6px;
	padding-bottom: 6px;
	padding-left: 15px;
	padding-right: 15px;
}
.course-dialog .el-dialog__body {
	padding: 15px;
}
.course-dialog .el-dialog__footer {
	padding: 20px;
	padding-top: 10px;
}
</style>
