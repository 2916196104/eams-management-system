<template>
	<div class="schedule-calendar-container">
		<div class="schedule-calendar-content">
			<div class="filter-area">
				<div class="filter-row">
					<div class="filter-item">
						<label class="filter-label">周期:</label>
						<el-select v-model="filters.period" placeholder="请选择" class="filter-input">
							<el-option v-for="option in periodOptions" :key="option" :label="option" :value="option" />
						</el-select>
					</div>
					<div class="filter-item">
						<label class="filter-label">班级:</label>
						<el-input v-model="filters.className" placeholder="请输入班级名称" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">课程:</label>
						<el-input v-model="filters.courseName" placeholder="请输入课程名称" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">老师:</label>
						<el-input v-model="filters.teacherName" placeholder="请输入老师姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">科目:</label>
						<el-input v-model="filters.subjectName" placeholder="请输入科目名称" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">教室:</label>
						<el-input v-model="filters.classroomName" placeholder="请输入教室名称" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">开始日期:</label>
						<el-date-picker
							v-model="filters.startDate"
							type="date"
							placeholder="请选择"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
							:disabled="filters.period !== '自定义'"
						/>
					</div>
					<div class="filter-item">
						<label class="filter-label">结束日期:</label>
						<el-date-picker
							v-model="filters.endDate"
							type="date"
							placeholder="请选择"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
							:disabled="filters.period !== '自定义'"
						/>
					</div>
					<div class="filter-buttons">
						<el-button circle @click="handleSearch">
							<IconifyIconOffline icon="ep/search" width="16" height="16" />
						</el-button>
						<el-button circle @click="handleReset">
							<IconifyIconOffline icon="ep/close" width="16" height="16" />
						</el-button>
					</div>
				</div>
				<div class="filter-actions">
					<el-button circle :loading="loading" @click="handleRefresh">
						<IconifyIconOffline icon="ep/refresh" width="16" height="16" />
					</el-button>
				</div>
			</div>

			<my-calendar
				title="课程日历"
				v-model:selected-date="selectedCalendarDate"
				v-model:view-mode="calendarViewMode"
				v-model:year="calendarYear"
				v-model:month="calendarMonth"
				@date-select="onDateSelect"
			>
				<template #cell="{ cell }">
					<div v-if="getCoursesByDate(cell.date).length > 0" class="course-dots">
						<div
							v-for="course in getCoursesByDate(cell.date).slice(0, 3)"
							:key="`${course.id}-${course.startTime}`"
							class="course-dot"
							:style="{ backgroundColor: getCourseColor(course.courseName) }"
						></div>
					</div>
				</template>

				<template #week-cell="{ date, hour }">
					<div
						v-for="course in getCoursesByDateAndHour(date, hour)"
						:key="`${course.id}-${course.startTime}`"
						class="week-cell-course"
						:style="{ backgroundColor: `${getCourseColor(course.courseName)}20`, borderLeftColor: getCourseColor(course.courseName) }"
					>
						<div class="week-cell-course-name">{{ course.courseName }}</div>
						<div class="week-cell-course-class">{{ course.className }} - {{ course.classroomName }}</div>
					</div>
				</template>

				<template #day-cell="{ date, hour }">
					<div
						v-for="course in getCoursesByDateAndHour(date, hour)"
						:key="`${course.id}-${course.startTime}`"
						class="day-cell-course"
						:style="{ backgroundColor: `${getCourseColor(course.courseName)}20`, borderLeftColor: getCourseColor(course.courseName) }"
					>
						<div class="day-cell-course-header">
							<span class="day-cell-course-name">{{ course.courseName }}</span>
							<span class="day-cell-course-time">{{ formatCourseTime(course) }}</span>
						</div>
						<div class="day-cell-course-info">
							<span>{{ course.className }}</span>
							<span>{{ course.teacherName }}</span>
							<span>{{ course.classroomName }}</span>
						</div>
					</div>
				</template>
			</my-calendar>

			<div class="calendar-meta">
				<span class="calendar-range">当前查询范围：{{ currentRangeText }}</span>
				<span class="calendar-count">共 {{ allCourses.length }} 条课次</span>
			</div>

			<div class="calendar-legend">
				<span class="legend-title">图例：</span>
				<div v-for="name in uniqueCourseNames" :key="name" class="legend-item">
					<div class="legend-dot" :style="{ backgroundColor: getCourseColor(name) }"></div>
					<span>{{ name }}</span>
				</div>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref, watch } from "vue";
import { ElMessage } from "element-plus";
import { IconifyIconOffline } from "@/components/ReIcon";
import MyCalendar from "@/components/mycalendar/MyCalendar.vue";
import { getLessonCalendar } from "@/apis/academic";
import type { LessonCalendarQueryDTO } from "@/apis/academic/type";
import type { CalendarCourse, ScheduleCalendarPeriod, ScheduleCalendarViewMode } from "./schedule-calendar";
import {
	buildLessonCalendarQuery,
	formatDate,
	getPeriodOptions,
	isCourseInHour,
	normalizeLessonCalendarRows,
} from "./schedule-calendar";

type FilterState = {
	className: string;
	courseName: string;
	teacherName: string;
	subjectName: string;
	classroomName: string;
	startDate: string;
	endDate: string;
	period: ScheduleCalendarPeriod;
};

const defaultFilters = (): FilterState => ({
	className: "",
	courseName: "",
	teacherName: "",
	subjectName: "",
	classroomName: "",
	startDate: "",
	endDate: "",
	period: "本月",
});

const filters = reactive<FilterState>(defaultFilters());
const appliedFilters = reactive<FilterState>(defaultFilters());

const today = new Date();
today.setHours(0, 0, 0, 0);

const selectedCalendarDate = ref<Date>(new Date(today));
const calendarViewMode = ref<ScheduleCalendarViewMode>("month");
const calendarYear = ref(today.getFullYear());
const calendarMonth = ref(today.getMonth());
const allCourses = ref<CalendarCourse[]>([]);
const loading = ref(false);

const courseColorMap: Record<string, string> = {
	语文: "#409eff",
	数学: "#67c23a",
	英语: "#e6a23c",
	物理: "#f56c6c",
	化学: "#909399",
	生物: "#06b6d4",
	地理: "#8b5cf6",
	历史: "#ec4899",
	政治: "#14b8a6",
	体育: "#84cc16",
	音乐: "#f97316",
	美术: "#a855f7",
};

const periodOptions = computed(() => getPeriodOptions(calendarViewMode.value));

const currentQuery = computed<LessonCalendarQueryDTO>(() =>
	buildLessonCalendarQuery(
		appliedFilters,
		calendarViewMode.value,
		selectedCalendarDate.value,
		calendarYear.value,
		calendarMonth.value,
	),
);

const currentRangeText = computed(() => `${currentQuery.value.startDate || "-"} 至 ${currentQuery.value.endDate || "-"}`);

const uniqueCourseNames = computed(() => {
	const names = new Set<string>();
	allCourses.value.forEach((course) => {
		if (course.courseName) {
			names.add(course.courseName);
		}
	});
	return Array.from(names);
});

watch(
	periodOptions,
	(options) => {
		if (!options.includes(filters.period)) {
			filters.period = options[0];
		}
		if (!options.includes(appliedFilters.period)) {
			appliedFilters.period = options[0];
		}
	},
	{ immediate: true },
);

watch(
	[selectedCalendarDate, calendarViewMode, calendarYear, calendarMonth],
	() => {
		loadData();
	},
	{ deep: false },
);

function getCourseColor(courseName: string | undefined): string {
	if (!courseName) return "#6b7280";
	return courseColorMap[courseName] || "#6b7280";
}

function getCoursesByDate(date: Date): CalendarCourse[] {
	const dateStr = formatDate(date);
	return allCourses.value.filter((course) => course.lessonDate === dateStr);
}

function getCoursesByDateAndHour(date: Date, hour: number): CalendarCourse[] {
	const dateStr = formatDate(date);
	return allCourses.value.filter((course) => course.lessonDate === dateStr && isCourseInHour(course, hour));
}

function formatCourseTime(course: CalendarCourse): string {
	if (!course.startTime || !course.endTime) return "--:--";
	return `${course.startTime.slice(0, 5)} - ${course.endTime.slice(0, 5)}`;
}

function onDateSelect(date: Date) {
	selectedCalendarDate.value = new Date(date);
}

async function loadData() {
	loading.value = true;
	try {
		const res = await getLessonCalendar(currentQuery.value);
		allCourses.value = normalizeLessonCalendarRows(res.data);
	} catch (error) {
		console.error("加载课程日历失败:", error);
		ElMessage.error("加载课程日历失败");
		allCourses.value = [];
	} finally {
		loading.value = false;
	}
}

function handleSearch() {
	if (filters.period === "自定义" && (!filters.startDate || !filters.endDate)) {
		ElMessage.warning("自定义周期时请完整选择开始和结束日期");
		return;
	}
	if (filters.period === "自定义" && filters.startDate > filters.endDate) {
		ElMessage.warning("结束日期不能早于开始日期");
		return;
	}

	Object.assign(appliedFilters, filters);
	loadData();
	ElMessage.success("筛选条件已应用");
}

function handleReset() {
	const nextFilters = defaultFilters();
	nextFilters.period = periodOptions.value[0];
	Object.assign(filters, nextFilters);
	Object.assign(appliedFilters, nextFilters);

	selectedCalendarDate.value = new Date(today);
	calendarViewMode.value = "month";
	calendarYear.value = today.getFullYear();
	calendarMonth.value = today.getMonth();

	loadData();
	ElMessage.info("筛选条件已重置");
}

function handleRefresh() {
	loadData();
}

onMounted(() => {
	loadData();
});
</script>

<style scoped>
.schedule-calendar-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.schedule-calendar-content {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
	display: flex;
	flex-direction: column;
	gap: 16px;
	min-height: 0;
}

.filter-area {
	display: flex;
	justify-content: space-between;
	align-items: flex-start;
	gap: 16px;
	flex-wrap: wrap;
}

.filter-row {
	display: flex;
	flex-wrap: wrap;
	gap: 16px;
	flex: 1;
}

.filter-item {
	display: flex;
	align-items: center;
	gap: 8px;
}

.filter-label {
	min-width: 56px;
	color: #303133;
	text-align: right;
	font-size: 14px;
}

.filter-input {
	width: 160px;
}

.filter-buttons {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-left: 8px;
}

.filter-actions {
	display: flex;
	align-items: center;
	gap: 8px;
	flex-shrink: 0;
}

.course-dots {
	display: flex;
	flex-wrap: wrap;
	gap: 2px;
	margin-top: 4px;
}

.course-dot {
	width: 6px;
	height: 6px;
	border-radius: 50%;
}

.week-cell-course {
	margin-bottom: 2px;
	padding: 4px;
	border-left: 3px solid;
	border-radius: 2px;
	cursor: pointer;
}

.week-cell-course-name {
	font-size: 12px;
	font-weight: 500;
	color: #303133;
	white-space: nowrap;
	overflow: hidden;
	text-overflow: ellipsis;
}

.week-cell-course-class {
	font-size: 11px;
	color: #909399;
	white-space: nowrap;
	overflow: hidden;
	text-overflow: ellipsis;
}

.day-cell-course {
	padding: 8px;
	border-left: 4px solid;
	border-radius: 4px;
	margin-bottom: 4px;
}

.day-cell-course-header {
	display: flex;
	justify-content: space-between;
	align-items: center;
	margin-bottom: 4px;
}

.day-cell-course-name {
	font-size: 14px;
	font-weight: 600;
	color: #303133;
}

.day-cell-course-time {
	font-size: 12px;
	color: #909399;
}

.day-cell-course-info {
	display: flex;
	gap: 12px;
	font-size: 12px;
	color: #606266;
	flex-wrap: wrap;
}

.calendar-meta {
	display: flex;
	justify-content: space-between;
	align-items: center;
	gap: 12px;
	flex-wrap: wrap;
	font-size: 13px;
	color: #606266;
}

.calendar-legend {
	display: flex;
	align-items: center;
	gap: 16px;
	flex-wrap: wrap;
	padding-top: 8px;
	border-top: 1px solid #ebeef5;
}

.legend-title {
	font-size: 14px;
	color: #606266;
}

.legend-item {
	display: flex;
	align-items: center;
	gap: 6px;
	font-size: 13px;
	color: #606266;
}

.legend-dot {
	width: 12px;
	height: 12px;
	border-radius: 2px;
}

@media (max-width: 1400px) {
	.filter-row {
		flex-direction: column;
	}

	.filter-item {
		width: 100%;
	}

	.filter-label {
		min-width: 80px;
	}

	.filter-input {
		flex: 1;
	}
}
</style>
