import type { LessonCalendarVO } from "@/apis/academic/type";

export type ScheduleCalendarViewMode = "month" | "week" | "day";
export type ScheduleCalendarPeriod = "本月" | "本周" | "自定义";

export type ScheduleCalendarFilters = {
	className: string;
	courseName: string;
	teacherName: string;
	subjectName: string;
	classroomName: string;
	startDate: string;
	endDate: string;
	period: ScheduleCalendarPeriod;
};

export type CalendarCourse = {
	id?: number;
	courseName: string;
	className: string;
	classroomName: string;
	teacherName: string;
	studentName: string;
	courseStatus: string;
	lessonDate: string;
	startTime: string;
	endTime: string;
	title: string;
};

export function formatDate(date: Date) {
	const year = date.getFullYear();
	const month = String(date.getMonth() + 1).padStart(2, "0");
	const day = String(date.getDate()).padStart(2, "0");
	return `${year}-${month}-${day}`;
}

export function normalizeLessonCalendarRows(rows: LessonCalendarVO[] | undefined): CalendarCourse[] {
	return (rows || []).map((item) => ({
		id: item.id,
		courseName: item.courseName || item.title || "-",
		className: item.className || "-",
		classroomName: item.classroomName || "-",
		teacherName: item.teacherName || "-",
		studentName: item.studentName || "",
		courseStatus: item.courseStatus || "",
		lessonDate: item.Date || "",
		startTime: item.startTime || "",
		endTime: item.endTime || "",
		title: item.title || item.courseName || "-",
	}));
}

export function mapViewModeToViewType(viewMode: ScheduleCalendarViewMode) {
	if (viewMode === "month") return 1;
	if (viewMode === "week") return 2;
	return 3;
}

export function getWeekRange(date: Date) {
	const current = new Date(date);
	current.setHours(0, 0, 0, 0);
	const day = current.getDay();
	const diff = day === 0 ? -6 : 1 - day;
	const start = new Date(current);
	start.setDate(current.getDate() + diff);
	const end = new Date(start);
	end.setDate(start.getDate() + 6);
	return {
		startDate: formatDate(start),
		endDate: formatDate(end),
	};
}

export function getMonthRange(year: number, month: number) {
	const start = new Date(year, month, 1);
	const end = new Date(year, month + 1, 0);
	return {
		startDate: formatDate(start),
		endDate: formatDate(end),
	};
}

export function getVisibleCalendarRange(
	viewMode: ScheduleCalendarViewMode,
	selectedDate: Date,
	year: number,
	month: number,
) {
	if (viewMode === "month") {
		return getMonthRange(year, month);
	}
	if (viewMode === "week") {
		return getWeekRange(selectedDate);
	}
	const dateText = formatDate(selectedDate);
	return {
		startDate: dateText,
		endDate: dateText,
	};
}

export function getPeriodOptions(viewMode: ScheduleCalendarViewMode): ScheduleCalendarPeriod[] {
	if (viewMode === "month") return ["本月", "自定义"];
	if (viewMode === "week") return ["本周", "自定义"];
	return ["自定义"];
}

export function buildLessonCalendarQuery(
	filters: ScheduleCalendarFilters,
	viewMode: ScheduleCalendarViewMode,
	selectedDate: Date,
	year: number,
	month: number,
) {
	const options = getPeriodOptions(viewMode);
	const period = options.includes(filters.period) ? filters.period : options[0];

	const visibleRange = getVisibleCalendarRange(viewMode, selectedDate, year, month);
	const customRangeReady = period === "自定义" && !!filters.startDate && !!filters.endDate;

	return {
		className: filters.className || undefined,
		courseName: filters.courseName || undefined,
		teacherName: filters.teacherName || undefined,
		subjectName: filters.subjectName || undefined,
		classroomName: filters.classroomName || undefined,
		startDate: customRangeReady ? filters.startDate : visibleRange.startDate,
		endDate: customRangeReady ? filters.endDate : visibleRange.endDate,
		viewType: mapViewModeToViewType(viewMode),
		period,
	};
}

export function getCourseHourRange(course: CalendarCourse) {
	const startHour = Number.parseInt(course.startTime.split(":")[0] || "", 10);
	const endHour = Number.parseInt(course.endTime.split(":")[0] || "", 10);
	const endMinute = Number.parseInt(course.endTime.split(":")[1] || "", 10);

	return {
		startHour: Number.isFinite(startHour) ? startHour : -1,
		endHour: Number.isFinite(endHour) ? endHour : -1,
		endMinute: Number.isFinite(endMinute) ? endMinute : 0,
	};
}

export function isCourseInHour(course: CalendarCourse, hour: number) {
	const { startHour, endHour, endMinute } = getCourseHourRange(course);
	if (startHour < 0 || endHour < 0) return false;
	if (startHour === endHour) return startHour === hour;
	if (hour < startHour) return false;
	if (hour > endHour) return false;
	if (hour === endHour) return endMinute > 0;
	return true;
}
