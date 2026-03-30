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
				<el-col>
					<el-form-item label="本课主题" prop="title">
						<el-input v-model="form.title" />
					</el-form-item>
				</el-col>
				<!-- 上课老师 -->
				<el-col>
					<el-form-item label="上课老师" prop="teacherId">
						<my-person-selector
							v-model="teacherPerson"
							@select="handleTeacherSelect"
							:data-loader="loadTeacherList"
							:columns="[
								{ prop: 'name', label: '姓名' },
								{ prop: 'position', label: '职位' },
							]"
						/>
					</el-form-item>
				</el-col>
				<!-- 助教老师 -->
				<el-col>
					<el-form-item label="助教老师">
						<my-person-selector
							v-model="assistantPerson"
							@select="handleAssistantSelect"
							:data-loader="loadTeacherList"
							:columns="[
								{ prop: 'name', label: '姓名' },
								{ prop: 'position', label: '职位' },
							]"
						/>
					</el-form-item>
				</el-col>
				<!-- 上课日期 -->
				<el-col>
					<el-form-item label="上课日期" prop="date">
						<el-date-picker v-model="form.date" type="date" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 开始时间 -->
				<el-col>
					<el-form-item label="开始时间" prop="startTime">
						<el-time-picker v-model="form.startTime" format="HH:mm" value-format="HH:mm" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 结束时间 -->
				<el-col>
					<el-form-item label="结束时间" prop="endTime">
						<el-time-picker v-model="form.endTime" format="HH:mm" value-format="HH:mm" style="width: 100%" />
					</el-form-item>
				</el-col>
				<!-- 教室 -->
				<el-col>
					<el-form-item label="选择教室">
						<my-person-selector
							v-model="room"
							@select="handleRoomSelect"
							:data-loader="loadRoomList"
							:columns="[
								{ prop: 'name', label: '名称' },
								{ prop: 'place', label: '地点' },
							]"
						/>
					</el-form-item>
				</el-col>
				<!-- 消课基数 -->
				<el-col>
					<el-form-item label="消课基数">
						<el-input-number v-model="form.decCount" :min="0" />
						<div class="form-tip">单人单次签到消课量</div>
					</el-form-item>
				</el-col>
				<!-- 开关 -->
				<el-col>
					<el-form-item label="开启预约">
						<el-switch v-model="form.enableReserve" />
					</el-form-item>
				</el-col>
				<el-col>
					<el-form-item label="批量同步时间">
						<el-switch v-model="form.syncTime" />
						<div class="form-tip">开启后，本班级后续相同时间课程将同步调整</div>
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
import MyPersonSelector from "@/components/myselector/MyPersonSelector.vue";
import { useBasicDataStore } from "@/stores/console";

const basicDataStore = useBasicDataStore();
const visible = ref(false);
const formRef = ref();

/* 表单 */
const form = ref({
	title: "",
	teacherId: 0,
	teacherName: "",
	assistantId: 0,
	assistantName: "",
	date: "",
	startTime: "",
	endTime: "",
	roomId: 0,
	roomName: "",
	decCount: 1,
	enableReserve: false,
	syncTime: false,
});

/* selector 绑定对象 */
const teacherPerson = ref(null);
const assistantPerson = ref(null);
const room = ref(null);

/* 表单校验 */
const rules = {
	teacherId: [{ required: true, message: "请选择老师", trigger: "change" }],
	date: [{ required: true, message: "请选择日期", trigger: "change" }],
	startTime: [{ required: true, message: "请选择开始时间", trigger: "change" }],
	endTime: [{ required: true, message: "请选择结束时间", trigger: "change" }],
};

/* 选择老师 */
const handleTeacherSelect = (person) => {
	form.value.teacherId = person.id;
	form.value.teacherName = person.name;
};

/* 选择助教 */
const handleAssistantSelect = (person) => {
	form.value.assistantId = person.id;
	form.value.assistantName = person.name;
};

/* 选择教室 */
const handleRoomSelect = (roomData) => {
	form.value.roomId = roomData.id;
	form.value.roomName = roomData.name;
};

/* 加载老师数据 */
const loadTeacherList = async () => {
	// 调用 store 方法加载数据
	await basicDataStore.fetchTeacherList({
		pageIndex: 1,
		pageSize: 10,
		courseId: 3,
		teacherName: "",
		type: 1,
	});
	// 返回列表给 selector 使用，同时改字段
	return (basicDataStore.teacherList.rows || []).map((item) => ({
		...item,
		position: item.positionName, // 将 positionName 改成 position
	}));
};

/* 加载教室数据 */
const loadRoomList = async () => {
	// 调用 store 方法加载数据
	await basicDataStore.fetchClassroomList({
		name: "",
		pageIndex: 1,
		pageSize: 10,
	});
	// 返回列表给 selector 使用，同时改字段
	return (basicDataStore.classroomList.rows || []).map((item) => ({
		...item,
		place: item.address, // 将 positionName 改成 position
	}));
};

/* 提交 */
const handleSubmit = () => {
	formRef.value.validate((valid) => {
		if (!valid) return;
		console.log(form.value);
		visible.value = false;
	});
};

/* 打开弹窗 */
const open = (info) => {
	form.value = {
		title: info.title,
		teacherId: info.teacherNo,
		teacherName: info.teacherName,
		assistantId: info.assistantNo,
		assistantName: info.assistantName,
		date: info.lessonTimeText,
		startTime: info.start_time,
		endTime: info.end_time,
		roomId: info.classroomNo,
		roomName: info.classroomName,
		decCount: info.decLessonCount ?? 1,
		enableReserve: info.canReserve === 1,
		syncTime: info.sync_time === 1,
	};
	// 关键：给 selector 回显对象
	teacherPerson.value = {
		id: info.teacherNo,
		name: info.teacherName,
	};

	assistantPerson.value = {
		id: info.assistantNo,
		name: info.assistantName,
	};

	room.value = {
		id: info.classroomNo,
		name: info.classroomName,
	};
	visible.value = true;
};

defineExpose({
	open,
});
</script>
