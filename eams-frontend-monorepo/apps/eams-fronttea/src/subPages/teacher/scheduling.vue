<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";

definePage({
	name: "teacherScheduling",
	style: {
		navigationBarTitleText: "排课",
		titleNView: false,
	},
});

interface TeacherOption {
	id: string;
	name: string;
	position: string;
}

interface ClassOption {
	id: string;
	name: string;
	course: string;
	teacher: string;
	room: string;
	grade: string;
	createTime: string;
	updateTime: string;
	number: number;
	courseCount: number;
	description: string;
	courseId?: string;
	classroomId?: string;
}

interface PickerChangeEvent {
	detail?: {
		value?: string;
	};
}

const toast = useGlobalToast();

const mode = ref<"repeat" | "free">("repeat");
const isRepeatMode = computed(() => mode.value === "repeat");
const weekdayOptions = [
	{ label: "一", value: 1 },
	{ label: "二", value: 2 },
	{ label: "三", value: 3 },
	{ label: "四", value: 4 },
	{ label: "五", value: 5 },
	{ label: "六", value: 6 },
	{ label: "日", value: 7 },
];
const selectedWeekdays = ref<number[]>([1]);
const skipHoliday = ref(true);
const bookable = ref(false);
const conflict = ref(true);
const submitting = ref(false);

const pageSize = 10;

const teacherKeyword = ref("");
const teacherPopupVisible = ref(false);
const teacherLoading = ref(false);
const teacherLoadingMore = ref(false);
const teacherPageIndex = ref(1);
const teacherPages = ref(0);
const teacherTotal = ref(0);
const teacherOptions = ref<TeacherOption[]>([]);
const teacherField = ref<"main" | "assistant">("main");

const classKeyword = ref("");
const classPopupVisible = ref(false);
const classLoading = ref(false);
const classLoadingMore = ref(false);
const classPageIndex = ref(1);
const classPages = ref(0);
const classTotal = ref(0);
const classOptions = ref<ClassOption[]>([]);

const scheduleForm = reactive({
	classId: "",
	className: "",
	courseId: "",
	mainTeacherId: "",
	mainTeacherName: "",
	assistantTeacherId: "",
	assistantTeacherName: "",
	classroomId: "",
	classroomName: "",
	startDate: "",
	endDate: "",
	classDate: "",
	startTime: "",
	endTime: "",
	limitNum: "0",
});

const teacherFieldTitle = computed(() => (teacherField.value === "main" ? "上课老师" : "助教老师"));
const hasMoreTeachers = computed(() => teacherPageIndex.value < teacherPages.value);
const hasMoreClasses = computed(() => classPageIndex.value < classPages.value);

function toggleWeekday(day: number) {
	if (selectedWeekdays.value.includes(day)) {
		selectedWeekdays.value = selectedWeekdays.value.filter((item) => item !== day);
		return;
	}

	selectedWeekdays.value = [...selectedWeekdays.value, day].sort((a, b) => a - b);
}

function normalizeTeacherPayload(source: any) {
	const payload = source?.data?.data ?? source?.data ?? source ?? {};
	const rows = Array.isArray(payload.rows)
		? payload.rows
		: Array.isArray(payload.list)
			? payload.list
			: Array.isArray(payload.records)
				? payload.records
				: [];

	return {
		pageIndex: Number(payload.pageIndex ?? 1),
		pages: Number(payload.pages ?? payload.total_page ?? 0),
		total: Number(payload.total ?? rows.length),
		rows: rows.map((item: any) => ({
			id: String(item.id ?? ""),
			name: item.name ?? "未命名教师",
			position: item.position ?? "",
		} satisfies TeacherOption)),
	};
}

function normalizeClassPayload(source: any) {
	const payload = source?.data?.data ?? source?.data ?? source ?? {};
	const rows = Array.isArray(payload.rows)
		? payload.rows
		: Array.isArray(payload.list)
			? payload.list
			: Array.isArray(payload.records)
				? payload.records
				: [];

	return {
		pageIndex: Number(payload.pageIndex ?? 1),
		pages: Number(payload.pages ?? payload.total_page ?? 0),
		total: Number(payload.total ?? rows.length),
		rows: rows.map((item: any) => ({
			id: String(item.id ?? ""),
			name: item.name ?? item.className ?? item.classname ?? "未命名班级",
			course: item.course ?? item.courseName ?? item.course_name ?? item.subject ?? "",
			teacher: item.teacher ?? item.teacherName ?? item.homeroom_teacher ?? "",
			room: item.room ?? item.classroom ?? item.classroomName ?? item.classroom_name ?? "",
			grade: item.grade ?? "",
			createTime: item.createTime ?? item.CreateTime ?? "",
			updateTime: item.updateTime ?? "",
			number: Number(item.number ?? item.studentCount ?? item.num_of_people ?? item.maxStudentCount ?? 0),
			courseCount: Number(item.courseCount ?? 0),
			description: item.description ?? "",
			courseId: String(item.course_id ?? item.courseId ?? ""),
			classroomId: String(item.classroom_id ?? item.classroomId ?? ""),
		} satisfies ClassOption)),
	};
}

async function loadTeachers(nextPage = 1, append = false) {
	const targetLoading = append ? teacherLoadingMore : teacherLoading;
	targetLoading.value = true;

	try {
		const res: any = await (Apis as any).workbench.get_workbench_selectteacher({
			params: {
				name: teacherKeyword.value || undefined,
				pageIndex: nextPage,
				pageSize,
			},
		});

		const payload = normalizeTeacherPayload(res);
		teacherPageIndex.value = payload.pageIndex;
		teacherPages.value = payload.pages;
		teacherTotal.value = payload.total;
		teacherOptions.value = append ? [...teacherOptions.value, ...payload.rows] : payload.rows;
	} catch {
		if (!append) teacherOptions.value = [];
		uni.showToast({ title: "教师列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function loadClasses(nextPage = 1, append = false) {
	const targetLoading = append ? classLoadingMore : classLoading;
	targetLoading.value = true;

	try {
		const res: any = await (Apis as any).workbench.get_workbench_selectclass({
			params: {
				className: classKeyword.value || undefined,
				pageIndex: nextPage,
				pageSize,
			},
		});

		const payload = normalizeClassPayload(res);
		classPageIndex.value = payload.pageIndex;
		classPages.value = payload.pages;
		classTotal.value = payload.total;
		classOptions.value = append ? [...classOptions.value, ...payload.rows] : payload.rows;
	} catch {
		if (!append) classOptions.value = [];
		uni.showToast({ title: "班级列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function refreshTeachers() {
	await loadTeachers(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function refreshClasses() {
	await loadClasses(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMoreTeachers() {
	if (!hasMoreTeachers.value || teacherLoadingMore.value) return;
	await loadTeachers(teacherPageIndex.value + 1, true);
}

async function loadMoreClasses() {
	if (!hasMoreClasses.value || classLoadingMore.value) return;
	await loadClasses(classPageIndex.value + 1, true);
}

async function openTeacherPopup(field: "main" | "assistant") {
	teacherField.value = field;
	teacherPopupVisible.value = true;

	if (!teacherOptions.value.length) {
		await loadTeachers(1, false);
	}
}

async function openClassPopup() {
	classPopupVisible.value = true;

	if (!classOptions.value.length) {
		await loadClasses(1, false);
	}
}

function selectTeacher(item: TeacherOption) {
	if (teacherField.value === "main") {
		scheduleForm.mainTeacherId = item.id;
		scheduleForm.mainTeacherName = item.name;
	} else {
		scheduleForm.assistantTeacherId = item.id;
		scheduleForm.assistantTeacherName = item.name;
	}

	teacherPopupVisible.value = false;
}

function selectClass(item: ClassOption) {
	scheduleForm.classId = item.id;
	scheduleForm.className = item.name;
	scheduleForm.courseId = item.courseId || "";
	scheduleForm.classroomId = item.classroomId || "";
	scheduleForm.classroomName = item.room || "";
	classPopupVisible.value = false;
}

function teacherDisplayName(field: "main" | "assistant") {
	return field === "main" ? scheduleForm.mainTeacherName || "请选择" : scheduleForm.assistantTeacherName || "请选择";
}

function applyPickerValue(field: "startDate" | "endDate" | "classDate" | "startTime" | "endTime", event: PickerChangeEvent) {
	scheduleForm[field] = event?.detail?.value || "";
}

function _resolveNumericId(value: string, label: string) {
	const parsed = Number(value);
	if (!value || !Number.isFinite(parsed) || parsed <= 0) {
		toast.show(`${label}缺失或格式不正确`);
		return null;
	}

	return parsed;
}

function resolveRequiredId(value: string, label: string) {
	const trimmed = value?.trim?.() ?? value;
	if (!trimmed) {
		toast.show(`${label}缺失或格式不正确`);
		return null;
	}

	return trimmed;
}

async function submitRepeatSchedule() {
	if (!scheduleForm.startDate || !scheduleForm.endDate) {
		toast.show("请选择开始和结束日期");
		return;
	}

	if (!selectedWeekdays.value.length) {
		toast.show("请至少选择一个上课日");
		return;
	}

	const classId = resolveRequiredId(scheduleForm.classId, "班级ID");
	if (!classId) return;

	const courseId = resolveRequiredId(scheduleForm.courseId, "课程ID");
	if (!courseId) return;

	const teacherId = resolveRequiredId(scheduleForm.mainTeacherId, "上课老师ID");
	if (!teacherId) return;

	const classroomId = scheduleForm.classroomId?.trim?.() ? scheduleForm.classroomId.trim() : undefined;
	const assistantId = scheduleForm.assistantTeacherId?.trim?.() ? scheduleForm.assistantTeacherId.trim() : undefined;
	const limitNum = Number(scheduleForm.limitNum || 0);

	await (Apis as any).workbench.post_workbench_RepeatCoursesArrange({
		data: {
			classId,
			courseId,
			teacherId,
			assistantId,
			classroomId,
			startDate: scheduleForm.startDate,
			endDate: scheduleForm.endDate,
			limitNum: Number.isFinite(limitNum) ? limitNum : 0,
			skipHoliday: skipHoliday.value,
			enableBooking: bookable.value,
			checkConflict: String(conflict.value),
			periods: [
				{
					weekDays: selectedWeekdays.value,
					startTime: scheduleForm.startTime,
					endTime: scheduleForm.endTime,
				},
			],
		},
	});
}

async function submitFreeSchedule() {
	if (!scheduleForm.classDate) {
		toast.show("请选择上课日期");
		return;
	}

	const classId = resolveRequiredId(scheduleForm.classId, "班级ID");
	if (!classId) return;

	const courseId = resolveRequiredId(scheduleForm.courseId, "课程ID");
	if (!courseId) return;

	const teacherId = resolveRequiredId(scheduleForm.mainTeacherId, "上课老师ID");
	if (!teacherId) return;

	const classroomId = scheduleForm.classroomId?.trim?.() ? scheduleForm.classroomId.trim() : undefined;
	const assistantId = scheduleForm.assistantTeacherId?.trim?.() ? scheduleForm.assistantTeacherId.trim() : undefined;
	const limitNum = Number(scheduleForm.limitNum || 0);

	await (Apis as any).workbench.post_workbench_FreeCoursesArrange({
		data: {
			classId,
			courseId,
			teacherId,
			assistantId,
			classroomId,
			startDate: scheduleForm.classDate,
			startTime: scheduleForm.startTime,
			endTime: scheduleForm.endTime || undefined,
			limitNum: Number.isFinite(limitNum) ? limitNum : 0,
			enableBooking: bookable.value,
			checkConflict: String(conflict.value),
		},
	});
}

async function submitForm() {
	if (!scheduleForm.className) {
		toast.show("请先选择班级");
		return;
	}

	if (!scheduleForm.mainTeacherName) {
		toast.show("请先选择上课老师");
		return;
	}

	if (!scheduleForm.startTime || !scheduleForm.endTime) {
		toast.show("请选择上课和下课时间");
		return;
	}

	submitting.value = true;
	try {
		if (isRepeatMode.value) {
			await submitRepeatSchedule();
			uni.showToast({ title: "重复排课创建成功", icon: "none" });
		} else {
			await submitFreeSchedule();
			uni.showToast({ title: "自由排课创建成功", icon: "none" });
		}
	} catch {
		uni.showToast({ title: `${isRepeatMode.value ? "重复" : "自由"}排课创建失败`, icon: "none" });
	} finally {
		submitting.value = false;
	}
}
</script>

<template>
  <view class="teacher-scheduling-page">
    <teacher-nav-bar title="排课" :show-refresh="false" />
    <view class="teacher-scheduling-card">
      <view class="teacher-scheduling-mode">
        <view
          class="teacher-scheduling-mode__item"
          :class="{ 'teacher-scheduling-mode__item--active': mode === 'repeat' }"
          @click="mode = 'repeat'"
        >
          重复排课
        </view>
        <view
          class="teacher-scheduling-mode__item"
          :class="{ 'teacher-scheduling-mode__item--active': mode === 'free' }"
          @click="mode = 'free'"
        >
          自由排课
        </view>
      </view>

      <view class="teacher-scheduling-row" @click="openClassPopup">
        <text class="teacher-scheduling-required">
          选择班级
        </text>
        <view class="teacher-scheduling-row__value">
          <text>{{ scheduleForm.className || "请选择" }}</text>
          <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
        </view>
      </view>
      <view class="teacher-scheduling-row" @click="openTeacherPopup('main')">
        <text class="teacher-scheduling-required">
          上课老师
        </text>
        <view class="teacher-scheduling-row__value">
          <text>{{ teacherDisplayName("main") }}</text>
          <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
        </view>
      </view>
      <view class="teacher-scheduling-row" @click="openTeacherPopup('assistant')">
        <text>助教老师</text>
        <view class="teacher-scheduling-row__value">
          <text>{{ teacherDisplayName("assistant") }}</text>
          <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
        </view>
      </view>

      <view class="teacher-scheduling-row">
        <text class="teacher-scheduling-required">
          课程ID
        </text>
        <input v-model="scheduleForm.courseId" class="teacher-scheduling-row__input" type="number" placeholder="班级未带出时手动填写">
      </view>
      <view class="teacher-scheduling-row">
        <text class="teacher-scheduling-required">
          教室ID
        </text>
        <input v-model="scheduleForm.classroomId" class="teacher-scheduling-row__input" type="number" placeholder="班级未带出时手动填写">
      </view>
      <view class="teacher-scheduling-row">
        <text>教室名称</text>
        <text>{{ scheduleForm.classroomName || "待班级带出" }}</text>
      </view>

      <template v-if="isRepeatMode">
        <picker mode="date" :value="scheduleForm.startDate" @change="applyPickerValue('startDate', $event)">
          <view class="teacher-scheduling-row">
            <text class="teacher-scheduling-required">
              开始日期
            </text>
            <view class="teacher-scheduling-row__value">
              <text>{{ scheduleForm.startDate || "请选择" }}</text>
              <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
            </view>
          </view>
        </picker>
        <picker mode="date" :value="scheduleForm.endDate" @change="applyPickerValue('endDate', $event)">
          <view class="teacher-scheduling-row">
            <text class="teacher-scheduling-required">
              结束日期
            </text>
            <view class="teacher-scheduling-row__value">
              <text>{{ scheduleForm.endDate || "请选择" }}</text>
              <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
            </view>
          </view>
        </picker>
      </template>
      <picker v-else mode="date" :value="scheduleForm.classDate" @change="applyPickerValue('classDate', $event)">
        <view class="teacher-scheduling-row">
          <text class="teacher-scheduling-required">
            上课日期
          </text>
          <view class="teacher-scheduling-row__value">
            <text>{{ scheduleForm.classDate || "请选择" }}</text>
            <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
          </view>
        </view>
      </picker>

      <view class="teacher-scheduling-box">
        <template v-if="isRepeatMode">
          <text class="teacher-scheduling-required">
            周几上课
          </text>
          <view class="teacher-scheduling-weekdays">
            <view
              v-for="day in weekdayOptions"
              :key="day.value"
              class="teacher-scheduling-weekday"
              :class="{ 'teacher-scheduling-weekday--active': selectedWeekdays.includes(day.value) }"
              @click="toggleWeekday(day.value)"
            >
              {{ day.label }}
            </view>
          </view>
        </template>

        <picker mode="time" :value="scheduleForm.startTime" @change="applyPickerValue('startTime', $event)">
          <view class="teacher-scheduling-box__row">
            <text class="teacher-scheduling-required">
              上课时间
            </text>
            <view class="teacher-scheduling-row__value">
              <text>{{ scheduleForm.startTime || "请选择" }}</text>
              <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
            </view>
          </view>
        </picker>
        <picker mode="time" :value="scheduleForm.endTime" @change="applyPickerValue('endTime', $event)">
          <view class="teacher-scheduling-box__row">
            <text class="teacher-scheduling-required">
              下课时间
            </text>
            <view class="teacher-scheduling-row__value">
              <text>{{ scheduleForm.endTime || "请选择" }}</text>
              <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
            </view>
          </view>
        </picker>
        <view class="teacher-scheduling-box__row teacher-scheduling-box__row--input">
          <text>限制人数</text>
          <input v-model="scheduleForm.limitNum" class="teacher-scheduling-row__input" type="number" placeholder="默认 0">
        </view>
      </view>

      <template v-if="isRepeatMode">
        <view class="teacher-scheduling-switch">
          <text>跳过节假日</text>
          <view class="teacher-switch" :class="{ 'teacher-switch--active': skipHoliday }" @click="skipHoliday = !skipHoliday">
            <view class="teacher-switch__thumb" />
          </view>
        </view>
        <view class="teacher-scheduling-switch">
          <text>开启预约</text>
          <view class="teacher-switch" :class="{ 'teacher-switch--active': bookable }" @click="bookable = !bookable">
            <view class="teacher-switch__thumb" />
          </view>
        </view>
        <view class="teacher-scheduling-switch">
          <text>冲突检测</text>
          <view class="teacher-switch" :class="{ 'teacher-switch--active': conflict }" @click="conflict = !conflict">
            <view class="teacher-switch__thumb" />
          </view>
        </view>
      </template>

      <view class="teacher-scheduling-placeholder"></view>
    </view>

    <view class="teacher-scheduling-action">
      <wd-button type="primary" block :loading="submitting" @click="submitForm">
        提交
      </wd-button>
    </view>

    <wd-popup v-model="classPopupVisible" position="bottom" custom-class="teacher-selector-popup">
      <view class="teacher-selector-popup__body">
        <view class="teacher-selector-popup__title">
          选择班级
        </view>

        <view class="teacher-selector-popup__search">
          <input
            v-model="classKeyword"
            class="teacher-selector-popup__search-input"
            type="text"
            placeholder="搜索班级名称"
            confirm-type="search"
            @confirm="refreshClasses"
          >
          <view class="teacher-selector-popup__search-button" @click="refreshClasses">
            搜索
          </view>
        </view>

        <view v-if="classOptions.length" class="teacher-selector-popup__summary">
          共 {{ classTotal }} 个班级
        </view>

        <view v-if="classOptions.length" class="teacher-selector-popup__list">
          <view
            v-for="item in classOptions"
            :key="item.id"
            class="teacher-selector-popup__item"
            @click="selectClass(item)"
          >
            <view>
              <view class="teacher-selector-popup__name">
                {{ item.name }}
              </view>
              <view class="teacher-selector-popup__meta">
                {{ [item.course, item.grade, item.teacher, item.room].filter(Boolean).join(" / ") || "暂无班级说明" }}
              </view>
            </view>
            <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
          </view>
        </view>

        <teacher-empty-state v-else :title="classLoading ? '加载中...' : '暂无班级数据'" compact />

        <view v-if="hasMoreClasses" class="teacher-selector-popup__more" @click="loadMoreClasses">
          {{ classLoadingMore ? "加载中..." : "加载更多" }}
        </view>
      </view>
    </wd-popup>

    <wd-popup v-model="teacherPopupVisible" position="bottom" custom-class="teacher-selector-popup">
      <view class="teacher-selector-popup__body">
        <view class="teacher-selector-popup__title">
          选择{{ teacherFieldTitle }}
        </view>

        <view class="teacher-selector-popup__search">
          <input
            v-model="teacherKeyword"
            class="teacher-selector-popup__search-input"
            type="text"
            placeholder="搜索教师姓名"
            confirm-type="search"
            @confirm="refreshTeachers"
          >
          <view class="teacher-selector-popup__search-button" @click="refreshTeachers">
            搜索
          </view>
        </view>

        <view v-if="teacherOptions.length" class="teacher-selector-popup__summary">
          共 {{ teacherTotal }} 位教师
        </view>

        <view v-if="teacherOptions.length" class="teacher-selector-popup__list">
          <view
            v-for="item in teacherOptions"
            :key="item.id"
            class="teacher-selector-popup__item"
            @click="selectTeacher(item)"
          >
            <view>
              <view class="teacher-selector-popup__name">
                {{ item.name }}
              </view>
              <view v-if="item.position" class="teacher-selector-popup__meta">
                {{ item.position }}
              </view>
            </view>
            <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
          </view>
        </view>

        <teacher-empty-state v-else :title="teacherLoading ? '加载中...' : '暂无教师数据'" compact />

        <view v-if="hasMoreTeachers" class="teacher-selector-popup__more" @click="loadMoreTeachers">
          {{ teacherLoadingMore ? "加载中..." : "加载更多" }}
        </view>
      </view>
    </wd-popup>
  </view>
</template>

<style scoped>
.teacher-scheduling-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-scheduling-card {
	margin-top: 10px;
	background: #fff;
	padding: 14px 12px 20px;
}

.teacher-scheduling-mode {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 8px;
	margin-bottom: 14px;
	padding: 4px;
	border-radius: 12px;
	background: #eef2f7;
}

.teacher-scheduling-mode__item {
	border-radius: 10px;
	padding: 10px 0;
	text-align: center;
	font-size: 15px;
	color: #667085;
}

.teacher-scheduling-mode__item--active {
	background: #fff;
	color: #111827;
	font-weight: 600;
}

.teacher-scheduling-row,
.teacher-scheduling-switch,
.teacher-scheduling-box__row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	padding: 14px 4px;
	border-bottom: 1px solid #edf0f5;
	font-size: 15px;
	color: #111827;
}

.teacher-scheduling-box__row--input {
	align-items: center;
}

.teacher-scheduling-row__value {
	display: flex;
	align-items: center;
	gap: 6px;
	color: #98a2b3;
}

.teacher-scheduling-row__input {
	flex: 1;
	max-width: 180px;
	height: 28px;
	text-align: right;
	font-size: 14px;
	color: #111827;
}

.teacher-scheduling-required::before {
	content: "*";
	margin-right: 2px;
	color: #f04438;
}

.teacher-scheduling-box {
	margin-top: 14px;
	border-radius: 14px;
	background: #f6f7fb;
	padding: 14px 12px 4px;
}

.teacher-scheduling-weekdays {
	display: flex;
	flex-wrap: wrap;
	gap: 10px;
	margin: 14px 0;
}

.teacher-scheduling-weekday {
	min-width: 34px;
	border-radius: 8px;
	padding: 6px 10px;
	text-align: center;
	font-size: 14px;
	color: #667085;
	background: #fff;
}

.teacher-scheduling-weekday--active {
	background: #eef4ff;
	color: #3e7bfa;
	font-weight: 600;
}

.teacher-switch {
	display: flex;
	align-items: center;
	width: 46px;
	height: 26px;
	padding: 3px;
	border-radius: 999px;
	background: #d0d5dd;
	transition: background 0.2s ease;
}

.teacher-switch--active {
	background: #3e7bfa;
}

.teacher-switch__thumb {
	width: 20px;
	height: 20px;
	border-radius: 50%;
	background: #fff;
	transition: transform 0.2s ease;
}

.teacher-switch--active .teacher-switch__thumb {
	transform: translateX(20px);
}

.teacher-scheduling-action {
	position: fixed;
	right: 12px;
	bottom: calc(env(safe-area-inset-bottom) + 18px);
	left: 12px;
}

.teacher-selector-popup__body {
	padding: 18px 16px calc(env(safe-area-inset-bottom) + 18px);
}

.teacher-selector-popup__title {
	text-align: center;
	font-size: 17px;
	font-weight: 700;
	color: #111827;
}

.teacher-selector-popup__search {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-top: 16px;
}

.teacher-selector-popup__search-input {
	flex: 1;
	height: 40px;
	border-radius: 12px;
	background: #f5f6fa;
	padding: 0 14px;
	font-size: 14px;
	color: #111827;
}

.teacher-selector-popup__search-button {
	display: flex;
	align-items: center;
	justify-content: center;
	min-width: 72px;
	height: 40px;
	border-radius: 12px;
	background: rgba(62, 123, 250, 0.1);
	font-size: 14px;
	font-weight: 600;
	color: #3e7bfa;
}

.teacher-selector-popup__summary {
	margin-top: 14px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-selector-popup__list {
	display: flex;
	flex-direction: column;
	gap: 10px;
	margin-top: 12px;
}

.teacher-selector-popup__item {
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-radius: 14px;
	background: #fff;
	padding: 14px 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.teacher-selector-popup__name {
	font-size: 15px;
	font-weight: 600;
	color: #111827;
}

.teacher-selector-popup__meta {
	margin-top: 6px;
	font-size: 12px;
	color: #98a2b3;
}

.teacher-selector-popup__more {
	display: flex;
	align-items: center;
	justify-content: center;
	height: 40px;
	margin-top: 14px;
	border-radius: 999px;
	background: #fff;
	font-size: 14px;
	font-weight: 600;
	color: #31c7a5;
}

.teacher-scheduling-placeholder {
	height: 80px;
}
</style>
