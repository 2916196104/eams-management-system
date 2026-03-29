<template>
	<el-dialog v-model="dialogVisible" title="自由排课" width="800px" :close-on-click-modal="false">
		<div class="free-schedule-form">
			<div class="form-tip">大批量排课推荐使用排课计划。</div>

			<el-form :model="formData" :rules="formRules" ref="formRef" label-width="96px">
				<el-row :gutter="20">
					<el-col :span="12">
						<el-form-item label="选择班级" prop="classId">
							<el-select v-model="formData.classId" placeholder="请选择" class="w-100" filterable clearable>
								<el-option
									v-for="option in classOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
						</el-form-item>
					</el-col>
					<el-col :span="12">
						<el-form-item label="上课老师" prop="teacherId">
							<el-select v-model="formData.teacherId" placeholder="请选择" class="w-100" filterable clearable>
								<el-option
									v-for="option in teacherOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
						</el-form-item>
					</el-col>
				</el-row>

				<el-row :gutter="20">
					<el-col :span="12">
						<el-form-item label="助教老师">
							<el-select v-model="formData.assistantId" placeholder="请选择" class="w-100" filterable clearable>
								<el-option
									v-for="option in assistantOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
						</el-form-item>
					</el-col>
					<el-col :span="12">
						<el-form-item label="选择教室">
							<el-select v-model="formData.roomId" placeholder="请选择" class="w-100" filterable clearable>
								<el-option
									v-for="option in roomOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
						</el-form-item>
					</el-col>
				</el-row>

				<el-row :gutter="20">
					<el-col :span="12">
						<el-form-item label="上课日期" prop="classDate">
							<el-date-picker
								v-model="formData.classDate"
								type="date"
								placeholder="请选择"
								class="w-100"
								format="YYYY-MM-DD"
								value-format="YYYY-MM-DD"
							/>
						</el-form-item>
					</el-col>
					<el-col :span="12"></el-col>
				</el-row>

				<el-row :gutter="20">
					<el-col :span="12">
						<el-form-item label="开始时间" prop="startTime">
							<el-time-picker
								v-model="formData.startTime"
								placeholder="请选择"
								class="w-100"
								format="HH:mm"
								value-format="HH:mm"
							/>
						</el-form-item>
					</el-col>
					<el-col :span="12">
						<el-form-item label="结束时间" prop="endTime">
							<el-time-picker
								v-model="formData.endTime"
								placeholder="请选择"
								class="w-100"
								format="HH:mm"
								value-format="HH:mm"
							/>
						</el-form-item>
					</el-col>
				</el-row>

				<el-row :gutter="20">
					<el-col :span="12">
						<el-form-item label="消课基数">
							<el-input-number v-model="formData.descLessonCount" :min="1" :max="10" class="w-100" />
							<div class="form-tip">表示签到消课量</div>
						</el-form-item>
					</el-col>
					<el-col :span="12">
						<el-form-item label="开启预约">
							<el-switch v-model="formData.canReserve" />
						</el-form-item>
					</el-col>
				</el-row>
			</el-form>
		</div>

		<template #footer>
			<div class="dialog-footer">
				<el-button @click="dialogVisible = false">取消</el-button>
				<el-button type="primary" @click="handleSubmit" :loading="submitting">提交</el-button>
			</div>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { reactive, ref } from "vue";
import { ElMessage } from "element-plus";
import type { FormRules } from "element-plus";
import { freeSchedule } from "@/apis/academic";
import type { FreeScheduleRequestDTO } from "@/apis/academic/type";

interface FreeScheduleFormData {
	classId: number | undefined;
	className: string;
	teacherId: number | undefined;
	teacherName: string;
	assistantId: number | undefined;
	assistantName: string;
	roomId: number | undefined;
	classDate: string;
	startTime: string;
	endTime: string;
	descLessonCount: number | undefined;
	canReserve: boolean;
}

interface SelectOption {
	value: number;
	label: string;
}

const dialogVisible = ref(false);
const formRef = ref();
const submitting = ref(false);
const emit = defineEmits<{
	(event: "success"): void;
}>();

// 模拟数据 - 实际应该从 API 获取
const classOptions: SelectOption[] = [
	{ value: 1, label: "1 班" },
	{ value: 2, label: "2 班" },
	{ value: 3, label: "3 班" },
];

const teacherOptions: SelectOption[] = [
	{ value: 1, label: "王老师" },
	{ value: 2, label: "李老师" },
	{ value: 3, label: "张老师" },
];

const assistantOptions: SelectOption[] = [
	{ value: 1, label: "助教 A" },
	{ value: 2, label: "助教 B" },
];

const roomOptions: SelectOption[] = [
	{ value: 101, label: "101 教室" },
	{ value: 102, label: "102 教室" },
	{ value: 201, label: "201 教室" },
];

const formData = reactive<FreeScheduleFormData>({
	classId: undefined,
	className: "",
	teacherId: undefined,
	teacherName: "",
	assistantId: undefined,
	assistantName: "",
	roomId: undefined,
	classDate: "",
	startTime: "",
	endTime: "",
	descLessonCount: undefined,
	canReserve: false,
});

const formRules: FormRules<FreeScheduleFormData> = {
	classId: [{ required: true, message: "请选择班级", trigger: "change" }],
	teacherId: [{ required: true, message: "请选择上课老师", trigger: "change" }],
	classDate: [{ required: true, message: "请选择上课日期", trigger: "change" }],
	startTime: [{ required: true, message: "请选择开始时间", trigger: "change" }],
	endTime: [{ required: true, message: "请选择结束时间", trigger: "change" }],
};

function getOptionLabel(options: SelectOption[], value?: number) {
	if (typeof value !== "number") return "";
	return options.find((option) => option.value === value)?.label || "";
}

function getWeekValue(dateText: string) {
	if (!dateText) return "";
	const date = new Date(`${dateText}T00:00:00`);
	if (Number.isNaN(date.getTime())) return "";
	const day = date.getDay();
	return String(day === 0 ? 7 : day);
}

function buildRequestPayload(): FreeScheduleRequestDTO {
	const payload: FreeScheduleRequestDTO = {
		classId: formData.classId!,
		className: getOptionLabel(classOptions, formData.classId),
		teacherId: formData.teacherId!,
		teacherName: getOptionLabel(teacherOptions, formData.teacherId),
		startTime: `${formData.classDate} ${formData.startTime}:00`,
		endTime: `${formData.classDate} ${formData.endTime}:00`,
		lessonScheduleSettingDtos: [
			{
				weeks: getWeekValue(formData.classDate),
				startTime: formData.startTime + ":00",
				endTime: formData.endTime + ":00",
				roomId: formData.roomId,
			},
		],
	};

	if (formData.assistantId) {
		payload.assistantId = formData.assistantId;
		payload.assistantName = getOptionLabel(assistantOptions, formData.assistantId);
	}

	if (formData.descLessonCount) {
		payload.descLessonCount = formData.descLessonCount;
	}

	return payload;
}

async function handleSubmit() {
	if (!formRef.value) return;

	await formRef.value.validate(async (valid: boolean) => {
		if (!valid) return;

		if (formData.startTime >= formData.endTime) {
			ElMessage.warning("结束时间必须晚于开始时间");
			return;
		}

		submitting.value = true;
		try {
			const res = await freeSchedule(buildRequestPayload());

			if (res.code === undefined || res.code === 0 || res.code === 10000) {
				ElMessage.success(res.message || "排课成功");
				dialogVisible.value = false;
				emit("success");
				return;
			}

			ElMessage.error(res.message || "排课失败");
		} catch (error) {
			console.error("排课失败:", error);
			ElMessage.error("排课失败");
		} finally {
			submitting.value = false;
		}
	});
}

// 暴露方法
defineExpose({
	openDialog() {
		dialogVisible.value = true;
		// 重置表单
		Object.assign(formData, {
			classId: undefined,
			className: "",
			teacherId: undefined,
			teacherName: "",
			assistantId: undefined,
			assistantName: "",
			roomId: undefined,
			classDate: "",
			startTime: "",
			endTime: "",
			descLessonCount: undefined,
			canReserve: false,
		});
	},
	closeDialog() {
		dialogVisible.value = false;
	},
});
</script>

<style scoped>
.free-schedule-form {
	padding: 10px;
}

.form-tip {
	font-size: 12px;
	color: #909399;
	margin-bottom: 16px;
}

.form-tip {
	font-size: 12px;
	color: #909399;
	margin-top: 4px;
}

.w-100 {
	width: 100%;
}

.dialog-footer {
	display: flex;
	justify-content: flex-end;
	gap: 12px;
}
</style>
