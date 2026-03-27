<template>
	<div class="schedule-calendar-container">
		<div class="schedule-calendar-content">
			<div class="filter-area">
				<div class="filter-row">
					<div class="filter-item">
						<label class="filter-label">周期:</label>
						<el-select v-model="filters.cycle" placeholder="请选择" clearable class="filter-input">
							<el-option label="本周" :value="1" />
							<el-option label="上周" :value="2" />
							<el-option label="本周及以后" :value="3" />
						</el-select>
					</div>
					<div class="filter-item">
						<label class="filter-label">班级:</label>
						<el-input v-model="filters.className" placeholder="请输入班级名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">课程:</label>
						<el-input v-model="filters.courseName" placeholder="请输入课程名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">老师:</label>
						<el-input v-model="filters.teacherName" placeholder="请输入老师姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">学生:</label>
						<el-input v-model="filters.studentName" placeholder="请输入学生姓名" clearable class="filter-input" />
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
					<el-button circle @click="handleRefresh">
						<IconifyIconOffline icon="ep/refresh" width="16" height="16" />
					</el-button>
				</div>
			</div>

			<my-calendar
				title="课程表"
				v-model:selected-date="selectedCalendarDate"
				v-model:view-mode="calendarViewMode"
				@date-select="onDateSelect"
			>
				<template #cell="{ cell }">
					<div v-if="getCoursesByDate(cell.date).length > 0" class="course-dots">
						<div
							v-for="course in getCoursesByDate(cell.date).slice(0, 3)"
							:key="course.id"
							class="course-dot"
							:style="{ backgroundColor: getCourseColor(course.courseName) }"
						></div>
					</div>
				</template>

				<template #week-cell="{ date, hour }">
					<div
						v-for="course in getCoursesByDateAndHour(date, hour)"
						:key="course.id"
						class="week-cell-course"
						:style="{ backgroundColor: getCourseColor(course.courseName) + '20', borderLeftColor: getCourseColor(course.courseName) }"
					>
						<div class="week-cell-course-name">{{ course.courseName }}</div>
						<div class="week-cell-course-class">{{ course.className }} - {{ course.classroomName }}</div>
					</div>
				</template>

				<template #day-cell="{ date, hour }">
					<div
						v-for="course in getCoursesByDateAndHour(date, hour)"
						:key="course.id"
						class="day-cell-course"
						:style="{ backgroundColor: getCourseColor(course.courseName) + '20', borderLeftColor: getCourseColor(course.courseName) }"
					>
						<div class="day-cell-course-header">
							<span class="day-cell-course-name">{{ course.courseName }}</span>
							<span class="day-cell-course-time">{{ formatCourseTime(course.lessonTimeText) }}</span>
						</div>
						<div class="day-cell-course-info">
							<span>{{ course.className }}</span>
							<span>{{ course.teacherNames }}</span>
							<span>{{ course.classroomName }}</span>
						</div>
					</div>
				</template>
			</my-calendar>

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
import { computed, onMounted, reactive, ref } from "vue";
import { ElMessage } from "element-plus";
import { IconifyIconOffline } from "@/components/ReIcon";
import MyCalendar from "@/components/mycalendar/MyCalendar.vue";
import { getCourseListPage } from "@/apis/academic";
import type { CourseListVO } from "@/apis/academic/type";

const filters = reactive({
	cycle: undefined as number | undefined,
	className: "",
	courseName: "",
	teacherName: "",
	studentName: "",
	startDate: "",
	endDate: "",
});

const selectedCalendarDate = ref<Date>(new Date());
const calendarViewMode = ref<"month" | "week" | "day">("month");
const allCourses = ref<CourseListVO[]>([]);
const loading = ref(false);

// 课程颜色映射
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

function getCourseColor(courseName: string | undefined): string {
	if (!courseName) return "#6b7280";
	return courseColorMap[courseName] || "#6b7280";
}

function getCoursesByDate(date: Date): CourseListVO[] {
	const dateStr = `${date.getFullYear()}-${String(date.getMonth() + 1).padStart(2, "0")}-${String(date.getDate()).padStart(2, "0")}`;
	return allCourses.value.filter((course) => {
		if (!course.lessonTimeText) return false;
		return course.lessonTimeText.startsWith(dateStr);
	});
}

function getCoursesByDateAndHour(date: Date, hour: number): CourseListVO[] {
	const dateStr = `${date.getFullYear()}-${String(date.getMonth() + 1).padStart(2, "0")}-${String(date.getDate()).padStart(2, "0")}`;
	return allCourses.value.filter((course) => {
		if (!course.lessonTimeText) return false;
		const courseDate = course.lessonTimeText.split(" ")[0];
		if (courseDate !== dateStr) return false;

		const timePart = course.lessonTimeText.split(" ")[1];
		if (!timePart) return false;

		const courseHour = parseInt(timePart.split(":")[0], 10);
		return courseHour === hour;
	});
}

function formatCourseTime(timeText: string | undefined): string {
	if (!timeText) return "--:--";
	const parts = timeText.split(" ");
	if (parts.length < 2) return "--:--";
	const time = parts[1].split(":");
	if (time.length < 2) return "--:--";
	return `${time[0]}:${time[1]}`;
}

const uniqueCourseNames = computed(() => {
	const names = new Set<string>();
	allCourses.value.forEach((course) => {
		if (course.courseName) {
			names.add(course.courseName);
		}
	});
	return Array.from(names);
});

function onDateSelect(date: Date) {
	console.log("选中日期:", date);
}

async function loadData() {
	loading.value = true;
	try {
		const params: any = {
			pageIndex: 1,
			pageSize: 1000,
		};

		if (filters.cycle) params.cycle = filters.cycle;
		if (filters.className) params.className = filters.className;
		if (filters.courseName) params.courseName = filters.courseName;
		if (filters.teacherName) params.teacherName = filters.teacherName;
		if (filters.studentName) params.studentName = filters.studentName;
		if (filters.startDate) params.startDate = filters.startDate;
		if (filters.endDate) params.endDate = filters.endDate;

		const res = await getCourseListPage(params);

		if (res.rows) {
			allCourses.value = res.rows;
		} else {
			allCourses.value = [];
		}
	} catch (error) {
		console.error("加载课程数据失败:", error);
		ElMessage.error("加载课程数据失败");
		allCourses.value = [];
	} finally {
		loading.value = false;
	}
}

function handleSearch() {
	loadData();
	ElMessage.success("筛选条件已应用");
}

function handleReset() {
	Object.assign(filters, {
		cycle: undefined,
		className: "",
		courseName: "",
		teacherName: "",
		studentName: "",
		startDate: "",
		endDate: "",
	});
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
