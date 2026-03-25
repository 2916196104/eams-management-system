<template>
	<el-dialog
		v-model="visible"
		destroy-on-close
		:close-on-click-modal="false"
		title="修改课次"
		width="700px"
		class="edit-course-dialog"
	>
		<el-form ref="formRef" :model="form" :rules="rules" label-width="90px">
			<el-row :gutter="20">
				<!-- 本课主题 -->
				<el-col :span="24">
					<el-form-item label="本课主题" prop="title">
						<el-input v-model="form.title" />
					</el-form-item>
				</el-col>
				<!-- 所属分校 -->
				<el-col :span="12">
					<el-form-item label="所属分校" prop="schoolId">
						<el-select v-model="form.schoolId" style="width: 100%">
							<el-option label="分校A" value="1" />
						</el-select>
					</el-form-item>
				</el-col>
				<!-- 选择课程 -->
				<el-col :span="12">
					<el-form-item label="选择课程" prop="courseId">
						<el-select v-model="form.courseId" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 上课老师 -->
				<el-col :span="12">
					<el-form-item label="上课老师" prop="teacherId">
						<el-select v-model="form.teacherId" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 助教老师 -->
				<el-col :span="12">
					<el-form-item label="助教老师">
						<el-select v-model="form.assistantId" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 上课日期 -->
				<el-col :span="12">
					<el-form-item label="上课日期" prop="date">
						<el-date-picker v-model="form.date" type="date" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 开始时间 -->
				<el-col :span="6">
					<el-form-item label="开始时间" prop="startTime">
						<el-time-picker v-model="form.startTime" format="HH:mm" value-format="HH:mm" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 结束时间 -->
				<el-col :span="6">
					<el-form-item label="结束时间" prop="endTime">
						<el-time-picker v-model="form.endTime" format="HH:mm" value-format="HH:mm" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 教室 -->
				<el-col :span="12">
					<el-form-item label="选择教室">
						<el-select v-model="form.classroomId" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 消课基数 -->
				<el-col :span="12">
					<el-form-item label="消课基数">
						<el-input-number v-model="form.consumeBase" :min="0" />
						<div class="form-tip">单人单次签到消课量</div>
					</el-form-item>
				</el-col>
				<!-- 限制人数 -->
				<el-col :span="12">
					<el-form-item label="限制人数">
						<el-input-number v-model="form.limitCount" :min="0" />
						<div class="form-tip">0或空表示不限制</div>
					</el-form-item>
				</el-col>
				<!-- 开关 -->
				<el-col :span="12">
					<el-form-item label="开启预约">
						<el-switch v-model="form.enableBooking" />
					</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="批量同步时间">
						<el-switch v-model="form.syncTime" />
						<div class="form-tip">开启后，本班级后续相同时间课程将同步调整</div>
					</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="检查冲突">
						<el-switch v-model="form.checkConflict" />
					</el-form-item>
				</el-col>
			</el-row>
		</el-form>
		<template #footer>
			<el-button @click="visible = false">取消</el-button>
			<el-button type="primary" @click="handleSubmit">提交</el-button>
		</template>
	</el-dialog>
</template>
<script setup>
import { ref } from "vue";

const visible = ref(false);
const formRef = ref();

const form = ref({
	title: "",
	schoolId: "",
	courseId: "",
	teacherId: "",
	assistantId: "",
	date: "",
	startTime: "",
	endTime: "",
	classroomId: "",
	consumeBase: 1,
	limitCount: 0,
	enableBooking: false,
	syncTime: false,
	checkConflict: true,
});

const rules = {
	schoolId: [{ required: true, message: "请选择分校", trigger: "change" }],
	courseId: [{ required: true, message: "请选择课程", trigger: "change" }],
	teacherId: [{ required: true, message: "请选择老师", trigger: "change" }],
	date: [{ required: true, message: "请选择日期", trigger: "change" }],
	startTime: [{ required: true, message: "请选择开始时间", trigger: "change" }],
	endTime: [{ required: true, message: "请选择结束时间", trigger: "change" }],
};

const handleSubmit = () => {
	formRef.value.validate((valid) => {
		if (!valid) return;
		console.log(form.value);
		visible.value = false;
	});
};
/* 打开弹窗 */
const open = (info) => {
	Object.assign(form.value, info);
	visible.value = true;
};

defineExpose({
	open,
});
</script>
<style>
/* dialog挂载在DOM上，body会先加载，所以需使用全局样式 */
.edit-course-dialog {
	padding: 0;
}
.edit-course-dialog .el-dialog__header {
	background-color: #e4f2ff;
	padding-top: 6px;
	padding-bottom: 6px;
	padding-left: 15px;
	padding-right: 15px;
}
.edit-course-dialog .el-dialog__body {
	padding: 15px;
}
.edit-course-dialog .el-dialog__footer {
	padding: 20px;
	padding-top: 10px;
}
.edit-course-dialog .form-tip {
	font-size: 12px;
	color: #999;
	line-height: 16px;
}
</style>
