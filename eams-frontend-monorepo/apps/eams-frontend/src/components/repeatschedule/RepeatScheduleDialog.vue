<template>
	<el-dialog
		v-model="dialogVisible"
		:title="TEXT.dialogTitle"
		width="860px"
		:close-on-click-modal="false"
		@closed="handleDialogClosed"
	>
		<div class="repeat-schedule-form">
			<div class="form-tip">{{ TEXT.formTip }}</div>

			<el-form ref="formRef" :model="formData" :rules="formRules" label-width="96px">
				<el-row :gutter="20">
					<el-col :span="24">
						<el-form-item :label="TEXT.sourceLessonLabel" prop="sourceScheduleId">
							<el-select
								v-model="formData.sourceScheduleId"
								:placeholder="TEXT.selectPlaceholder"
								class="w-100"
								filterable
								@change="handleSourceScheduleChange"
							>
								<el-option
									v-for="option in sourceScheduleOptions"
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
						<el-form-item :label="TEXT.classLabel" prop="classId">
							<el-select
								v-model="formData.classId"
								:placeholder="TEXT.selectPlaceholder"
								class="w-100"
								filterable
								clearable
							>
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
						<el-form-item :label="TEXT.teacherLabel" prop="teacherId">
							<el-select
								v-model="formData.teacherId"
								:placeholder="TEXT.selectPlaceholder"
								class="w-100"
								filterable
								clearable
							>
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
						<el-form-item :label="TEXT.assistantLabel">
							<el-select
								v-model="formData.assistantId"
								:placeholder="TEXT.selectPlaceholder"
								class="w-100"
								filterable
								clearable
							>
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
						<el-form-item :label="TEXT.roomLabel">
							<el-select
								v-model="formData.roomId"
								:placeholder="TEXT.selectPlaceholder"
								class="w-100"
								filterable
								clearable
							>
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
						<el-form-item :label="TEXT.startDateLabel" prop="startDate">
							<el-date-picker
								v-model="formData.startDate"
								type="date"
								:placeholder="TEXT.selectPlaceholder"
								class="w-100"
								format="YYYY-MM-DD"
								value-format="YYYY-MM-DD"
							/>
						</el-form-item>
					</el-col>
					<el-col :span="12">
						<el-form-item :label="TEXT.endDateLabel" prop="endDate">
							<el-date-picker
								v-model="formData.endDate"
								type="date"
								:placeholder="TEXT.selectPlaceholder"
								class="w-100"
								format="YYYY-MM-DD"
								value-format="YYYY-MM-DD"
							/>
						</el-form-item>
					</el-col>
				</el-row>

				<el-row :gutter="20">
					<el-col :span="12">
						<el-form-item :label="TEXT.reserveLabel">
							<el-switch v-model="formData.canReserve" />
						</el-form-item>
					</el-col>
					<el-col :span="12">
						<el-form-item :label="TEXT.excludeHolidayLabel">
							<el-switch v-model="formData.excludeHoliday" />
						</el-form-item>
					</el-col>
				</el-row>

				<div class="periods-container">
					<div v-for="(period, index) in formData.periods" :key="period.id" class="period-card">
						<div class="period-header">
							<span class="period-title">{{ `${TEXT.periodTitle} ${index + 1}` }}</span>
							<el-button
								v-if="formData.periods.length > 1"
								link
								type="danger"
								size="small"
								@click="handleDeletePeriod(index)"
							>
								{{ TEXT.deletePeriod }}
							</el-button>
						</div>
						<el-row :gutter="20">
							<el-col :span="24">
								<el-form-item :label="index === 0 ? TEXT.weeksLabel : ' '" label-width="96px">
									<el-select v-model="period.weeks" :placeholder="TEXT.selectPlaceholder" class="w-100">
										<el-option v-for="option in weekOptions" :key="option.value" :label="option.label" :value="option.value" />
									</el-select>
								</el-form-item>
							</el-col>
						</el-row>
						<el-row :gutter="20">
							<el-col :span="12">
								<el-form-item :label="index === 0 ? TEXT.startTimeLabel : ' '" label-width="96px">
									<el-time-picker
										v-model="period.startTime"
										:placeholder="TEXT.selectPlaceholder"
										class="w-100"
										format="HH:mm"
										value-format="HH:mm"
									/>
								</el-form-item>
							</el-col>
							<el-col :span="12">
								<el-form-item :label="index === 0 ? TEXT.endTimeLabel : ' '" label-width="96px">
									<el-time-picker
										v-model="period.endTime"
										:placeholder="TEXT.selectPlaceholder"
										class="w-100"
										format="HH:mm"
										value-format="HH:mm"
									/>
								</el-form-item>
							</el-col>
						</el-row>
					</div>
				</div>

				<el-row :gutter="20">
					<el-col :span="12">
						<el-form-item :label="TEXT.descLessonCountLabel">
							<el-input-number v-model="formData.descLessonCount" :min="1" class="w-100" />
						</el-form-item>
					</el-col>
					<el-col :span="12">
						<el-form-item :label="TEXT.timesLabel">
							<el-input-number v-model="formData.times" :min="1" class="w-100" />
						</el-form-item>
					</el-col>
				</el-row>

				<div class="period-actions">
					<el-button type="primary" plain @click="handleAddPeriod">{{ TEXT.addPeriod }}</el-button>
				</div>
			</el-form>
		</div>

		<template #footer>
			<div class="dialog-footer">
				<el-button @click="dialogVisible = false">{{ TEXT.cancelAction }}</el-button>
				<el-button type="primary" :loading="submitting" @click="handleSubmit">{{ TEXT.submitAction }}</el-button>
			</div>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { nextTick, reactive, ref } from "vue";
import { ElMessage, type FormInstance, type FormRules } from "element-plus";
import { getCourseDetail, repeatSchedule, switchSchedule } from "@/apis/academic";
import type { CourseDetailVO, CourseListVO, RepeatScheduleRequestDTO } from "@/apis/academic/type";

interface SelectOption {
	value: number;
	label: string;
}

interface SourceScheduleOption extends SelectOption {
	row: CourseListVO;
}

interface RepeatPeriodForm {
	id: number;
	weeks?: number;
	startTime: string;
	endTime: string;
}

interface RepeatScheduleFormData {
	sourceScheduleId?: number;
	classId?: number;
	teacherId?: number;
	assistantId?: number;
	roomId?: number;
	startDate: string;
	endDate: string;
	descLessonCount: number;
	times?: number;
	canReserve: boolean;
	excludeHoliday: boolean;
	periods: RepeatPeriodForm[];
}

interface OpenDialogPayload {
	selectedRow?: CourseListVO;
	candidateRows?: CourseListVO[];
}

const TEXT = {
	dialogTitle: "\u91CD\u590D\u6392\u8BFE",
	formTip: "\u5927\u6279\u91CF\u6392\u8BFE\u63A8\u8350\u4F7F\u7528\u6392\u8BFE\u8BA1\u5212\u3002",
	selectPlaceholder: "\u8BF7\u9009\u62E9",
	sourceLessonLabel: "\u9009\u62E9\u8BFE\u6B21",
	classLabel: "\u9009\u62E9\u73ED\u7EA7",
	teacherLabel: "\u4E0A\u8BFE\u8001\u5E08",
	assistantLabel: "\u52A9\u6559\u8001\u5E08",
	roomLabel: "\u9009\u62E9\u6559\u5BA4",
	startDateLabel: "\u5F00\u59CB\u65E5\u671F",
	endDateLabel: "\u7ED3\u675F\u65E5\u671F",
	reserveLabel: "\u5F00\u542F\u9884\u7EA6",
	excludeHolidayLabel: "\u8DF3\u8FC7\u8282\u5047\u65E5",
	periodTitle: "\u5468\u671F",
	deletePeriod: "\u5220\u9664",
	weeksLabel: "\u5468\u51E0\u4E0A\u8BFE",
	startTimeLabel: "\u4E0A\u8BFE\u65F6\u95F4",
	endTimeLabel: "\u4E0B\u8BFE\u65F6\u95F4",
	descLessonCountLabel: "\u6D88\u8BFE\u8BFE\u65F6",
	timesLabel: "\u6392\u8BFE\u6B21\u6570",
	addPeriod: "\u6DFB\u52A0\u5468\u671F",
	cancelAction: "\u53D6\u6D88",
	submitAction: "\u63D0\u4EA4",
	requiredSourceLesson: "\u8BF7\u5148\u9009\u62E9\u4E00\u6761\u8BFE\u6B21\u6570\u636E",
	requiredClass: "\u8BF7\u9009\u62E9\u73ED\u7EA7",
	requiredTeacher: "\u8BF7\u9009\u62E9\u4E0A\u8BFE\u8001\u5E08",
	requiredStartDate: "\u8BF7\u9009\u62E9\u5F00\u59CB\u65E5\u671F",
	requiredEndDate: "\u8BF7\u9009\u62E9\u7ED3\u675F\u65E5\u671F",
	periodWeekWarning: "\u8BF7\u4E3A\u5468\u671F {index} \u9009\u62E9\u4E0A\u8BFE\u661F\u671F",
	periodTimeWarning: "\u8BF7\u4E3A\u5468\u671F {index} \u9009\u62E9\u5B8C\u6574\u7684\u4E0A\u8BFE\u65F6\u95F4",
	periodTimeOrderWarning: "\u5468\u671F {index} \u7684\u4E0B\u8BFE\u65F6\u95F4\u5FC5\u987B\u665A\u4E8E\u4E0A\u8BFE\u65F6\u95F4",
	dateRangeWarning: "\u7ED3\u675F\u65E5\u671F\u4E0D\u80FD\u65E9\u4E8E\u5F00\u59CB\u65E5\u671F",
	periodRequiredWarning: "\u8BF7\u81F3\u5C11\u6DFB\u52A0\u4E00\u4E2A\u5468\u671F",
	success: "\u91CD\u590D\u6392\u8BFE\u6210\u529F",
	failed: "\u91CD\u590D\u6392\u8BFE\u5931\u8D25",
	reservationSyncFailed: "\u91CD\u590D\u6392\u8BFE\u5DF2\u6210\u529F\uff0c\u4F46\u9884\u7EA6\u5F00\u5173\u540C\u6B65\u5931\u8D25\uff0c\u8BF7\u7A0D\u540E\u624B\u52A8\u8C03\u6574",
	reservationSyncSkipped:
		"\u91CD\u590D\u6392\u8BFE\u5DF2\u6210\u529F\uff0c\u4F46\u5F53\u524D\u8BFE\u8868\u7F3A\u5C11\u8BFE\u7A0B\u7F16\u53F7\uff0c\u65E0\u6CD5\u540C\u6B65\u9884\u7EA6\u5F00\u5173",
	monday: "\u5468\u4E00",
	tuesday: "\u5468\u4E8C",
	wednesday: "\u5468\u4E09",
	thursday: "\u5468\u56DB",
	friday: "\u5468\u4E94",
	saturday: "\u5468\u516D",
	sunday: "\u5468\u65E5",
	reserveOn: "1",
	reserveTrue: "true",
	reserveYes: "\u662F",
	reserveOpen: "\u5F00\u542F",
	reserveAvailable: "\u53EF\u9884\u7EA6",
} as const;

const emit = defineEmits<{
	(event: "success"): void;
}>();

const dialogVisible = ref(false);
const submitting = ref(false);
const formRef = ref<FormInstance>();
const sourceRow = ref<CourseListVO | undefined>();
const sourceDetail = ref<CourseDetailVO>();
const initialCanReserve = ref(false);
const periodIdCounter = ref(0);
const sourceScheduleOptions = ref<SourceScheduleOption[]>([]);

const classOptions = ref<SelectOption[]>([]);
const teacherOptions = ref<SelectOption[]>([]);
const assistantOptions = ref<SelectOption[]>([]);
const roomOptions = ref<SelectOption[]>([]);

const weekOptions: Array<{ label: string; value: number }> = [
	{ label: TEXT.monday, value: 1 },
	{ label: TEXT.tuesday, value: 2 },
	{ label: TEXT.wednesday, value: 3 },
	{ label: TEXT.thursday, value: 4 },
	{ label: TEXT.friday, value: 5 },
	{ label: TEXT.saturday, value: 6 },
	{ label: TEXT.sunday, value: 7 },
];

const formData = reactive<RepeatScheduleFormData>({
	sourceScheduleId: undefined,
	classId: undefined,
	teacherId: undefined,
	assistantId: undefined,
	roomId: undefined,
	startDate: "",
	endDate: "",
	descLessonCount: 1,
	times: undefined,
	canReserve: false,
	excludeHoliday: true,
	periods: [],
});

const formRules: FormRules<RepeatScheduleFormData> = {
	sourceScheduleId: [{ required: true, message: TEXT.requiredSourceLesson, trigger: "change" }],
	classId: [{ required: true, message: TEXT.requiredClass, trigger: "change" }],
	teacherId: [{ required: true, message: TEXT.requiredTeacher, trigger: "change" }],
	startDate: [{ required: true, message: TEXT.requiredStartDate, trigger: "change" }],
	endDate: [{ required: true, message: TEXT.requiredEndDate, trigger: "change" }],
};

function splitByComma(value?: string) {
	return (value || "")
		.split(/[,\uFF0C]/)
		.map((item) => item.trim())
		.filter(Boolean);
}

function createPeriod(seed: Partial<Omit<RepeatPeriodForm, "id">> = {}): RepeatPeriodForm {
	periodIdCounter.value += 1;
	return {
		id: periodIdCounter.value,
		weeks: seed.weeks,
		startTime: seed.startTime || "",
		endTime: seed.endTime || "",
	};
}

function normalizeCanReserve(value?: string) {
	if (!value) return false;
	const enabledValues = new Set<string>([
		TEXT.reserveOn,
		TEXT.reserveTrue,
		TEXT.reserveYes,
		TEXT.reserveOpen,
		TEXT.reserveAvailable,
	]);
	return enabledValues.has(value.trim());
}

function parseIdNameOptions(idsText?: string, namesText?: string): SelectOption[] {
	const ids = splitByComma(idsText)
		.map((item) => Number(item))
		.filter((item) => Number.isFinite(item));
	const names = splitByComma(namesText);
	const options: SelectOption[] = [];

	for (let index = 0; index < Math.min(ids.length, names.length); index += 1) {
		options.push({
			value: ids[index],
			label: names[index],
		});
	}

	return options;
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

function uniqueSourceRows(rows: CourseListVO[]) {
	const rowMap = new Map<number, CourseListVO>();

	rows.forEach((row) => {
		if (typeof row.id === "number" && !rowMap.has(row.id)) {
			rowMap.set(row.id, row);
		}
	});

	return Array.from(rowMap.values());
}

function buildSourceScheduleOptions(rows: CourseListVO[]) {
	sourceScheduleOptions.value = uniqueSourceRows(rows).map((row) => ({
		value: row.id as number,
		label: `${row.lessonTimeText || "未设置时间"} | ${row.className || "未设置班级"} | ${row.courseName || "未设置课程"}`,
		row,
	}));
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

function extractLessonMeta(lessonTimeText?: string) {
	const dateMatch = lessonTimeText?.match(/\d{4}-\d{2}-\d{2}/)?.[0] || "";
	const timeMatches = lessonTimeText?.match(/\d{2}:\d{2}(?::\d{2})?/g) || [];
	const startTime = timeMatches[0]?.slice(0, 5) || "";
	const endTime = timeMatches[1]?.slice(0, 5) || "";

	let weeks: number | undefined;
	if (dateMatch) {
		const date = new Date(`${dateMatch}T00:00:00`);
		if (!Number.isNaN(date.getTime())) {
			const day = date.getDay();
			weeks = day === 0 ? 7 : day;
		}
	}

	return { date: dateMatch, startTime, endTime, weeks };
}

function getOptionLabel(options: SelectOption[], value?: number) {
	if (typeof value !== "number") return "";
	return options.find((option) => option.value === value)?.label || "";
}

function appendSeconds(time: string) {
	if (!time) return "";
	return time.length === 5 ? `${time}:00` : time;
}

function getScheduleId(row?: CourseListVO) {
	const scheduleId = row?.scheduleId ?? row?.id;
	if (scheduleId == null) return undefined;
	return String(scheduleId);
}

function getCourseId(row?: CourseListVO) {
	if (row?.courseId == null) return undefined;
	return String(row.courseId);
}

function getCourseCode() {
	return sourceDetail.value?.courseNo || getCourseId(sourceRow.value);
}

function getReservationStatus(value: boolean) {
	return value ? TEXT.reserveOn : "0";
}

function resetForm(selectedRow?: CourseListVO) {
	const lessonMeta = extractLessonMeta(selectedRow?.lessonTimeText);
	const canReserve = normalizeCanReserve(selectedRow?.canReserve);
	periodIdCounter.value = 0;
	initialCanReserve.value = canReserve;
	sourceDetail.value = undefined;

	Object.assign(formData, {
		sourceScheduleId: selectedRow?.id,
		classId: selectedRow?.classId,
		teacherId: parseIdNameOptions(selectedRow?.teacherIds, selectedRow?.teacherNames)[0]?.value,
		assistantId: parseIdNameOptions(selectedRow?.assistantIds, selectedRow?.assistantNames)[0]?.value,
		roomId: selectedRow?.classroomId,
		startDate: lessonMeta.date,
		endDate: lessonMeta.date,
		descLessonCount: selectedRow?.decLessonCount && selectedRow.decLessonCount > 0 ? selectedRow.decLessonCount : 1,
		times: undefined,
		canReserve,
		excludeHoliday: true,
		periods: [createPeriod({ weeks: lessonMeta.weeks, startTime: lessonMeta.startTime, endTime: lessonMeta.endTime })],
	});
}

function handleSourceScheduleChange(value?: number) {
	const picked = sourceScheduleOptions.value.find((option) => option.value === value)?.row;
	if (!picked) return;

	sourceRow.value = picked;
	resetForm(picked);
	void loadSourceDetail(picked);
}

function handleAddPeriod() {
	formData.periods.push(createPeriod());
}

function handleDeletePeriod(index: number) {
	formData.periods.splice(index, 1);
}

function formatIndexedText(template: string, index: number) {
	return template.replace("{index}", String(index));
}

function validatePeriods() {
	for (let index = 0; index < formData.periods.length; index += 1) {
		const period = formData.periods[index];
		const displayIndex = index + 1;

		if (period.weeks === undefined) {
			ElMessage.warning(formatIndexedText(TEXT.periodWeekWarning, displayIndex));
			return false;
		}
		if (!period.startTime || !period.endTime) {
			ElMessage.warning(formatIndexedText(TEXT.periodTimeWarning, displayIndex));
			return false;
		}
		if (period.startTime >= period.endTime) {
			ElMessage.warning(formatIndexedText(TEXT.periodTimeOrderWarning, displayIndex));
			return false;
		}
	}

	return true;
}

function buildRequestPayload(): RepeatScheduleRequestDTO {
	const payload: RepeatScheduleRequestDTO = {
		classId: formData.classId as number,
		className: getOptionLabel(classOptions.value, formData.classId),
		teacherId: formData.teacherId as number,
		teacherName: getOptionLabel(teacherOptions.value, formData.teacherId),
		startTime: `${formData.startDate} 00:00:00`,
		endTime: `${formData.endDate} 23:59:59`,
		descLessonCount: formData.descLessonCount,
		lessonScheduleSettingDtos: formData.periods.map((period) => ({
			scheduleId: getScheduleId(sourceRow.value),
			weeks: String(period.weeks),
			startTime: appendSeconds(period.startTime),
			endTime: appendSeconds(period.endTime),
			roomId: formData.roomId,
		})),
	};

	const courseCode = getCourseCode();
	if (courseCode) {
		payload.id = courseCode;
	}
	if (typeof formData.assistantId === "number") {
		payload.assistantId = formData.assistantId;
		payload.assistantName = getOptionLabel(assistantOptions.value, formData.assistantId);
	}
	if (typeof formData.times === "number" && formData.times > 0) {
		payload.times = formData.times;
	}
	if (formData.excludeHoliday) {
		payload.excludeHoliday = "1";
	}
	if (sourceDetail.value?.status || sourceRow.value?.lessonStatus) {
		payload.status = sourceDetail.value?.status || sourceRow.value?.lessonStatus;
	}

	return payload;
}

function isSuccessCode(code?: number) {
	return code === undefined || code === 0 || code === 10000;
}

async function syncReservationSwitch() {
	if (formData.canReserve === initialCanReserve.value) {
		return;
	}

	const courseId = getCourseCode();
	if (!courseId) {
		ElMessage.warning(TEXT.reservationSyncSkipped);
		return;
	}

	const res = await switchSchedule({
		id: courseId,
		status: getReservationStatus(formData.canReserve),
	});

	if (!isSuccessCode(res.code)) {
		throw new Error(res.message || TEXT.reservationSyncFailed);
	}
}

async function loadSourceDetail(selectedRow?: CourseListVO) {
	if (!selectedRow?.id) return;

	try {
		const res = await getCourseDetail(selectedRow.id);
		if (!res.data) return;

		sourceDetail.value = res.data;

		const canReserve = normalizeCanReserve(res.data.canReserve);
		formData.canReserve = canReserve;
		initialCanReserve.value = canReserve;
	} catch (error) {
		console.error("获取课次详情失败:", error);
	}
}

async function handleSubmit() {
	const valid = await formRef.value?.validate().then(() => true).catch(() => false);
	if (!valid) return;

	if (formData.startDate > formData.endDate) {
		ElMessage.warning(TEXT.dateRangeWarning);
		return;
	}
	if (!formData.periods.length) {
		ElMessage.warning(TEXT.periodRequiredWarning);
		return;
	}
	if (!validatePeriods()) return;

	submitting.value = true;
	try {
		const res = await repeatSchedule(buildRequestPayload());
		if (isSuccessCode(res.code)) {
			try {
				await syncReservationSwitch();
			} catch (error) {
				console.error(TEXT.reservationSyncFailed, error);
				ElMessage.warning(TEXT.reservationSyncFailed);
			}

			ElMessage.success(res.message || TEXT.success);
			dialogVisible.value = false;
			emit("success");
			return;
		}

		ElMessage.error(res.message || TEXT.failed);
	} catch (error) {
		console.error(TEXT.failed, error);
		ElMessage.error(TEXT.failed);
	} finally {
		submitting.value = false;
	}
}

function handleDialogClosed() {
	formRef.value?.clearValidate();
}

defineExpose({
	openDialog(payload: OpenDialogPayload = {}) {
		const rows = [...(payload.candidateRows || [])];
		if (payload.selectedRow) {
			rows.unshift(payload.selectedRow);
		}

		buildSourceScheduleOptions(rows);
		const defaultRow =
			payload.selectedRow ||
			sourceScheduleOptions.value[0]?.row;

		sourceRow.value = defaultRow;
		buildCandidateOptions(rows);
		resetForm(defaultRow);
		dialogVisible.value = true;

		nextTick(() => {
			formRef.value?.clearValidate();
		});

		void loadSourceDetail(defaultRow);
	},
	closeDialog() {
		dialogVisible.value = false;
	},
});
</script>

<style scoped>
.repeat-schedule-form {
	padding: 10px;
}

.form-tip {
	font-size: 12px;
	padding: 12px 16px;
	border-radius: 8px;
	margin-bottom: 16px;
}

.form-tip {
	color: #606266;
	background: #f5f7fa;
}

	.periods-container {
	display: flex;
	flex-direction: column;
	gap: 16px;
	margin-bottom: 16px;
}

.period-card {
	padding: 16px 16px 0;
	border-radius: 8px;
	background: #f5f7fa;
}

.period-header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	margin-bottom: 8px;
}

.period-title {
	font-size: 14px;
	font-weight: 500;
	color: #303133;
}

.period-actions {
	display: flex;
	justify-content: center;
	padding-top: 8px;
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
