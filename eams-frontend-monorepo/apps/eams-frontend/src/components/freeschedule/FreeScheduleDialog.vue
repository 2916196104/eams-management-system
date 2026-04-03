<template>
	<el-dialog v-model="dialogVisible" title="自由排课" width="800px" :close-on-click-modal="false">
		<div class="free-schedule-form">
			<div class="form-tip">大批量排课推荐使用排课计划。</div>
			<div v-if="!classOptions.length && !teacherOptions.length" class="form-tip">
				请先查询课程表数据，再从当前结果中复用班级、老师和教室选项。
			</div>

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
					<el-col :span="12"></el-col>
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
import { nextTick, reactive, ref } from "vue";
import { ElMessage } from "element-plus";
import type { FormInstance, FormRules } from "element-plus";
import { freeSchedule } from "@/apis/academic";
import type { CourseListVO, FreeScheduleRequestDTO } from "@/apis/academic/type";

interface FreeScheduleFormData {
	classId?: number;
	teacherId?: number;
	assistantId: number | undefined;
	roomId: number | undefined;
	classDate: string;
	startTime: string;
	endTime: string;
	descLessonCount: number | undefined;
}

interface OpenDialogPayload {
	selectedRow?: CourseListVO;
	candidateRows?: CourseListVO[];
}

interface SelectOption {
	value: number;
	label: string;
}

const dialogVisible = ref(false);
const formRef = ref<FormInstance>();
const submitting = ref(false);
const emit = defineEmits<{
	(event: "success"): void;
}>();

const classOptions = ref<SelectOption[]>([]);
const teacherOptions = ref<SelectOption[]>([]);
const assistantOptions = ref<SelectOption[]>([]);
const roomOptions = ref<SelectOption[]>([]);

const formData = reactive<FreeScheduleFormData>({
	classId: undefined,
	teacherId: undefined,
	assistantId: undefined,
	roomId: undefined,
	classDate: "",
	startTime: "",
	endTime: "",
	descLessonCount: undefined,
});

const formRules: FormRules<FreeScheduleFormData> = {
	classId: [{ required: true, message: "请选择班级", trigger: "change" }],
	teacherId: [{ required: true, message: "请选择上课老师", trigger: "change" }],
	classDate: [{ required: true, message: "请选择上课日期", trigger: "change" }],
	startTime: [{ required: true, message: "请选择开始时间", trigger: "change" }],
	endTime: [{ required: true, message: "请选择结束时间", trigger: "change" }],
};

function splitByComma(value?: string) {
	return (value || "")
		.split(/[,\uFF0C]/)
		.map((item) => item.trim())
		.filter(Boolean);
}

function parseIdNameOptions(idsText?: string, namesText?: string): SelectOption[] {
	const ids = splitByComma(idsText)
		.map((item) => Number(item))
		.filter((item) => Number.isFinite(item));
	const names = splitByComma(namesText);

	return ids.slice(0, names.length).map((value, index) => ({
		value,
		label: names[index],
	}));
}

function uniqueOptions(options: SelectOption[]) {
	const optionMap = new Map<number, string>();

	options.forEach((option) => {
		if (!optionMap.has(option.value)) {
			optionMap.set(option.value, option.label);
		}
	});

	return Array.from(optionMap.entries()).map(([value, label]) => ({ value, label }));
}

function getOptionLabel(options: SelectOption[], value?: number) {
	if (typeof value !== "number") return "";
	return options.find((option) => option.value === value)?.label || "";
}

function buildCandidateOptions(rows: CourseListVO[]) {
	const nextClassOptions: SelectOption[] = [];
	const nextTeacherOptions: SelectOption[] = [];
	const nextAssistantOptions: SelectOption[] = [];
	const nextRoomOptions: SelectOption[] = [];

	rows.forEach((row) => {
		if (typeof row.classId === "number" && row.className) {
			nextClassOptions.push({ value: row.classId, label: row.className });
		}
		if (typeof row.classroomId === "number" && row.classroomName) {
			nextRoomOptions.push({ value: row.classroomId, label: row.classroomName });
		}
		nextTeacherOptions.push(...parseIdNameOptions(row.teacherIds, row.teacherNames));
		nextAssistantOptions.push(...parseIdNameOptions(row.assistantIds, row.assistantNames));
	});

	classOptions.value = uniqueOptions(nextClassOptions);
	teacherOptions.value = uniqueOptions(nextTeacherOptions);
	assistantOptions.value = uniqueOptions(nextAssistantOptions);
	roomOptions.value = uniqueOptions(nextRoomOptions);
}

function getWeekValue(dateText: string) {
	if (!dateText) return "";
	const date = new Date(`${dateText}T00:00:00`);
	if (Number.isNaN(date.getTime())) return "";
	const day = date.getDay();
	return String(day === 0 ? 7 : day);
}

function appendSeconds(time: string) {
	return time.length === 5 ? `${time}:00` : time;
}

function extractLessonMeta(lessonTimeText?: string) {
	const dateText = lessonTimeText?.match(/\d{4}-\d{2}-\d{2}/)?.[0] || "";
	const times = lessonTimeText?.match(/\d{2}:\d{2}(?::\d{2})?/g) || [];
	return {
		date: dateText,
		startTime: times[0]?.slice(0, 5) || "",
		endTime: times[1]?.slice(0, 5) || "",
	};
}

function resetForm(selectedRow?: CourseListVO) {
	const lessonMeta = extractLessonMeta(selectedRow?.lessonTimeText);
	Object.assign(formData, {
		classId: selectedRow?.classId,
		teacherId: parseIdNameOptions(selectedRow?.teacherIds, selectedRow?.teacherNames)[0]?.value,
		assistantId: parseIdNameOptions(selectedRow?.assistantIds, selectedRow?.assistantNames)[0]?.value,
		roomId: selectedRow?.classroomId,
		classDate: lessonMeta.date,
		startTime: lessonMeta.startTime,
		endTime: lessonMeta.endTime,
		descLessonCount: selectedRow?.decLessonCount && selectedRow.decLessonCount > 0 ? selectedRow.decLessonCount : undefined,
	});
}

function buildRequestPayload(): FreeScheduleRequestDTO {
	const payload: FreeScheduleRequestDTO = {
		classId: formData.classId!,
		className: getOptionLabel(classOptions.value, formData.classId),
		teacherId: formData.teacherId!,
		teacherName: getOptionLabel(teacherOptions.value, formData.teacherId),
		startTime: `${formData.classDate} ${appendSeconds(formData.startTime)}`,
		endTime: `${formData.classDate} ${appendSeconds(formData.endTime)}`,
		lessonScheduleSettingDtos: [
			{
				weeks: getWeekValue(formData.classDate),
				startTime: appendSeconds(formData.startTime),
				endTime: appendSeconds(formData.endTime),
				roomId: formData.roomId,
			},
		],
	};

	if (formData.assistantId) {
		payload.assistantId = formData.assistantId;
		payload.assistantName = getOptionLabel(assistantOptions.value, formData.assistantId);
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

defineExpose({
	openDialog(payload: OpenDialogPayload = {}) {
		const rows = [...(payload.candidateRows || [])];
		if (payload.selectedRow) {
			rows.unshift(payload.selectedRow);
		}

		buildCandidateOptions(rows);
		const defaultRow = payload.selectedRow || rows[0];
		resetForm(defaultRow);
		dialogVisible.value = true;

		nextTick(() => {
			formRef.value?.clearValidate();
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
