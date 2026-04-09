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
					<!-- 月视图：显示当天的所有课程 -->
					<div v-if="getCellCourses(cell.date).length > 0" class="month-cell-courses">
						<div
							v-for="course in getCellCourses(cell.date).slice(0, 34)"
							:key="`${course.id}-${course.startTime}`"
							class="month-course-item"
							:style="{
								backgroundColor: `${getCourseStatusColor(course.courseStatus)}20`,
								borderLeftColor: getCourseStatusColor(course.courseStatus),
							}"
							:title="`${course.courseName} - ${course.startTime}-${course.endTime}`"
							@click="handleCourseClick(course)"
						>
							<span class="course-name">{{ course.courseName }}</span>
							<span class="course-time">{{ course.startTime }} - {{ course.endTime }}</span>
						</div>
						<div v-if="getCellCourses(cell.date).length > 34" class="more-courses">
							+{{ getCellCourses(cell.date).length - 34 }} 更多
						</div>
					</div>
				</template>

				<template #week-cell="{ date, hour }">
					<!-- 周视图：显示对应时段课程 -->
					<div
						v-for="course in getCoursesByDateAndHour(date, hour)"
						:key="`${course.id}-${course.startTime}`"
						class="week-cell-course"
						:style="{
							backgroundColor: `${getCourseStatusColor(course.courseStatus)}20`,
							borderLeftColor: getCourseStatusColor(course.courseStatus),
						}"
						@click="handleCourseClick(course)"
					>
						<div class="week-course-name">{{ course.courseName }}</div>
						<div class="week-course-info">{{ course.className }} · {{ course.classroomName }}</div>
					</div>
				</template>

				<template #day-cell="{ date, hour }">
					<!-- 日视图：显示对应时段课程 -->
					<div
						v-for="course in getCoursesByDateAndHour(date, hour)"
						:key="`${course.id}-${course.startTime}`"
						class="day-cell-course"
						:style="{
							backgroundColor: `${getCourseStatusColor(course.courseStatus)}20`,
							borderLeftColor: getCourseStatusColor(course.courseStatus),
						}"
						@click="handleCourseClick(course)"
					>
						<div class="day-course-header">
							<span class="course-name">{{ course.courseName }}</span>
							<span class="course-time">{{ formatCourseTime(course) }}</span>
						</div>
						<div class="day-course-info">
							<span>{{ course.className }}</span>
							<span>{{ course.teacherName }}</span>
							<span>{{ course.classroomName }}</span>
						</div>
					</div>
				</template>
			</my-calendar>

			<!-- 课程详情弹窗 -->
			<CourseDetailDialog ref="courseDetailDialogRef" @deleted="handleCourseDeleted" />

			<div class="calendar-meta">
				<span class="calendar-range">当前查询范围：{{ currentRangeText }}</span>
				<span class="calendar-count">共 {{ allCourses.length }} 条课次</span>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref, watch } from "vue";
import { ElMessage } from "element-plus";
import { IconifyIconOffline } from "@/components/ReIcon";
import MyCalendar from "@/components/mycalendar/MyCalendar.vue";
import CourseDetailDialog from "@/components/coursedetail/CourseDetailDialog.vue";
import { getLessonCalendar, getCourseDetail } from "@/apis/academic";
import type { LessonCalendarQueryDTO, CourseDetailVO } from "@/apis/academic/type";
import type { CalendarCourse, ScheduleCalendarPeriod, ScheduleCalendarViewMode } from "./schedule-calendar";
import {
	buildLessonCalendarQuery,
	formatDate,
	getCourseStatusColor,
	getPeriodOptions,
	isCourseInHour,
	normalizeLessonCalendarRows,
} from "./schedule-calendar";

// 是否使用模拟数据（开发环境测试用）
// 切换到真实 API 时，将此值改为 false
const USE_MOCK_DATA = false;

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
const courseDetailDialogRef = ref<InstanceType<typeof CourseDetailDialog>>();

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

const currentRangeText = computed(
	() => `${currentQuery.value.startDate || "-"} 至 ${currentQuery.value.endDate || "-"}`,
);

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

function getCoursesByDateAndHour(date: Date, hour: number): CalendarCourse[] {
	const dateStr = formatDate(date);
	return allCourses.value.filter((course) => course.lessonDate === dateStr && isCourseInHour(course, hour));
}

// 获取某天的所有课程（月视图使用）
function getCellCourses(date: Date): CalendarCourse[] {
	const dateStr = formatDate(date);
	return allCourses.value.filter((course) => course.lessonDate === dateStr);
}

// 格式化课程时间显示
function formatCourseTime(course: CalendarCourse) {
	return `${course.startTime.substring(0, 5)}-${course.endTime.substring(0, 5)}`;
}

function onDateSelect(date: Date) {
	selectedCalendarDate.value = new Date(date);
}

// 点击课程，弹出详情
async function handleCourseClick(course: CalendarCourse) {
	if (!course.id) {
		ElMessage.warning("课程 ID 不存在");
		return;
	}

	try {
		const res = await getCourseDetail(course.id);
		if (res.data) {
			const detailData: CourseDetailVO = res.data;
			if (courseDetailDialogRef.value) {
				courseDetailDialogRef.value.openDialog(detailData);
			}
		}
	} catch (error) {
		console.error("获取课程详情失败:", error);
		ElMessage.error("获取课程详情失败");
	}
}

// 删除课程后的处理
function handleCourseDeleted(deletedId: number) {
	allCourses.value = allCourses.value.filter((course) => course.id !== deletedId);
	ElMessage.success("课程已删除");
}

async function loadData() {
	loading.value = true;
	try {
		if (USE_MOCK_DATA) {
			// 使用模拟数据
			const mockCourses = generateMockCourses(currentQuery.value);
			allCourses.value = mockCourses;
			console.log(`[Mock] 生成${mockCourses.length}条课程数据`);
			return;
		}

		// 使用真实 API
		const res = await getLessonCalendar(currentQuery.value);

		// 检查响应码是否为成功
		if (res.code === 10000 || res.code === 0) {
			allCourses.value = normalizeLessonCalendarRows(res.data);
		} else {
			console.error("加载课程日历失败:", res.message);
			ElMessage.error(res.message || "加载课程日历失败");
			allCourses.value = [];
		}
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

// 生成模拟课程数据
function generateMockCourses(query: LessonCalendarQueryDTO): CalendarCourse[] {
	const courses: CalendarCourse[] = [];
	const { startDate, endDate } = query;

	if (!startDate || !endDate) return courses;

	const start = new Date(startDate);
	const end = new Date(endDate);
	const days = Math.ceil((end.getTime() - start.getTime()) / (1000 * 60 * 60 * 24)) + 1;

	// 模拟课程名称
	const courseNames = ["数学基础", "英语进阶", "编程入门", "物理实验", "化学原理", "历史人文", "艺术鉴赏"];
	// 模拟班级
	const classNames = ["高一 (1) 班", "高一 (2) 班", "高二 (1) 班", "高二 (2) 班", "高三 (1) 班"];
	// 模拟老师
	const teacherNames = ["张老师", "李老师", "王老师", "赵老师", "刘老师"];
	// 模拟教室
	const classrooms = ["A101", "A102", "B201", "B202", "C301", "实验室 1", "实验室 2"];
	// 模拟学生
	const studentNames = ["张三", "李四", "王五", "赵六", "钱七", "孙八", "周九", "吴十"];
	// 课程状态
	const statuses = ["正常", "待上课", "进行中", "已完成"];
	// 时间段
	const timeSlots = [
		{ start: "08:00:00", end: "09:00:00" },
		{ start: "09:10:00", end: "10:10:00" },
		{ start: "10:30:00", end: "11:30:00" },
		{ start: "14:00:00", end: "15:00:00" },
		{ start: "15:10:00", end: "16:10:00" },
		{ start: "16:30:00", end: "17:30:00" },
	];

	for (let i = 0; i < days; i++) {
		const currentDate = new Date(start);
		currentDate.setDate(start.getDate() + i);

		// 跳过周末（可选）
		const dayOfWeek = currentDate.getDay();
		if (dayOfWeek === 0 || dayOfWeek === 6) continue;

		// 每天生成 2-4 条课程
		const coursesPerDay = Math.floor(Math.random() * 3) + 2;

		for (let j = 0; j < coursesPerDay; j++) {
			const courseIndex = Math.floor(Math.random() * courseNames.length);
			const classIndex = Math.floor(Math.random() * classNames.length);
			const teacherIndex = Math.floor(Math.random() * teacherNames.length);
			const classroomIndex = Math.floor(Math.random() * classrooms.length);
			const studentIndex = Math.floor(Math.random() * studentNames.length);
			const statusIndex = Math.floor(Math.random() * statuses.length);
			const timeSlotIndex = Math.floor(Math.random() * timeSlots.length);

			const courseName = courseNames[courseIndex];
			const className = classNames[classIndex];
			const teacherName = teacherNames[teacherIndex];
			const classroomName = classrooms[classroomIndex];
			const studentName = studentNames[studentIndex];
			const status = statuses[statusIndex];
			const timeSlot = timeSlots[timeSlotIndex];

			courses.push({
				id: courses.length + 1,
				courseName,
				className,
				classroomName,
				teacherName,
				studentName,
				courseStatus: status,
				lessonDate: formatDate(currentDate),
				startTime: timeSlot.start,
				endTime: timeSlot.end,
				title: `${courseName} - ${className}`,
			});
		}
	}

	// 按日期和时间排序
	courses.sort((a, b) => {
		if (a.lessonDate !== b.lessonDate) {
			return a.lessonDate.localeCompare(b.lessonDate);
		}
		return a.startTime.localeCompare(b.startTime);
	});

	return courses;
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

.month-cell-placeholder {
	display: none;
}

.week-cell-placeholder {
	display: none;
}

/* 月视图：课程列表 */
.month-cell-courses {
	display: flex;
	flex-direction: column;
	gap: 4px;
	margin-top: 4px;
}

.month-course-item {
	display: flex;
	flex-direction: column;
	gap: 2px;
	padding: 4px 6px;
	border-left: 3px solid;
	border-radius: 4px;
	font-size: 11px;
	background: rgba(255, 255, 255, 0.9);
	cursor: pointer;
	transition: all 0.2s;
}

.month-course-item:hover {
	background: rgba(245, 247, 250, 0.95);
	transform: translateX(2px);
}

.course-name {
	font-weight: 500;
	color: #303133;
	overflow: hidden;
	text-overflow: ellipsis;
	white-space: nowrap;
}

.course-time {
	font-size: 10px;
	color: #909399;
}

.more-courses {
	font-size: 10px;
	color: #606266;
	text-align: center;
	padding: 2px;
}

/* 周视图：课程块 */
.week-cell-course {
	min-height: 32px;
	padding: 4px;
	border-left: 3px solid;
	border-radius: 4px;
	margin-bottom: 4px;
	font-size: 11px;
	cursor: pointer;
	transition: all 0.2s;
}

.week-cell-course:hover {
	background: rgba(245, 247, 250, 0.95);
	transform: translateX(2px);
}

.week-course-name {
	font-weight: 500;
	color: #303133;
	margin-bottom: 2px;
}

.week-course-info {
	font-size: 10px;
	color: #909399;
}

/* 日视图：课程块 */
.day-cell-course {
	min-height: 48px;
	padding: 6px 8px;
	border-left: 4px solid;
	border-radius: 6px;
	margin-bottom: 6px;
	background: rgba(255, 255, 255, 0.95);
	cursor: pointer;
	transition: all 0.2s;
}

.day-cell-course:hover {
	background: rgba(245, 247, 250, 0.98);
	transform: translateX(3px);
	box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
}

.day-course-header {
	display: flex;
	justify-content: space-between;
	align-items: center;
	margin-bottom: 4px;
}

.day-course-info {
	display: flex;
	gap: 8px;
	font-size: 11px;
	color: #909399;
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
