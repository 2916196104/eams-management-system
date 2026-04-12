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

export const COURSE_STATUS_COLOR_MAP: Record<string, string> = {
	正常: "#67c23a",
	待上课: "#409eff",
	进行中: "#e6a23c",
	调课: "#8b5cf6",
	停课: "#f56c6c",
	已完成: "#909399",
};

export function formatDate(date: Date) {
	const year = date.getFullYear();
	const month = String(date.getMonth() + 1).padStart(2, "0");
	const day = String(date.getDate()).padStart(2, "0");
	return `${year}-${month}-${day}`;
}

// 格式化日期为后端要求的 LocalDate 格式
// 后端可能期望 yyyyMMdd 格式（无分隔符）
export function formatLocalDate(dateString: string): string {
	if (!dateString) return "";
	// 验证格式是否为 YYYY-MM-DD
	const dateRegex = /^\d{4}-\d{2}-\d{2}$/;
	if (dateRegex.test(dateString)) {
		// 将 YYYY-MM-DD 转换为 YYYYMMDD 格式（无分隔符）
		return dateString.replace(/-/g, "");
	}
	// 格式不正确，尝试解析并重新格式化
	const date = new Date(dateString);
	if (Number.isNaN(date.getTime())) return dateString;
	const year = date.getFullYear();
	const month = String(date.getMonth() + 1).padStart(2, "0");
	const day = String(date.getDate()).padStart(2, "0");
	return `${year}${month}${day}`;
}

export function normalizeLessonCalendarRows(rows: LessonCalendarVO[] | undefined): CalendarCourse[] {
	return (rows || []).map((item) => {
		// 处理日期字段，兼容 date 和 Date
		const lessonDate = item.date || item.Date || "";

		// 处理时间字段，兼容字符串和对象格式
		let startTime = item.startTime || "";
		if (typeof startTime === "object" && startTime !== null) {
			const h = String(startTime.hour ?? 0).padStart(2, "0");
			const m = String(startTime.minute ?? 0).padStart(2, "0");
			startTime = `${h}:${m}`;
		}

		let endTime = item.endTime || "";
		if (typeof endTime === "object" && endTime !== null) {
			const h = String(endTime.hour ?? 0).padStart(2, "0");
			const m = String(endTime.minute ?? 0).padStart(2, "0");
			endTime = `${h}:${m}`;
		}

		return {
			id: item.id,
			courseName: item.courseName || item.title || "-",
			className: item.className || "-",
			classroomName: item.classroomName || "-",
			teacherName: item.teacherName || "-",
			studentName: item.studentNameList?.[0] || item.studentName || "",
			courseStatus: item.courseStatus || "",
			lessonDate,
			startTime,
			endTime,
			title: item.title || item.courseName || "-",
		};
	});
}

export function getCourseStatusLabel(status?: string) {
	return (status || "").trim() || "未设置";
}

export function getCourseStatusColor(status?: string) {
	const label = getCourseStatusLabel(status);
	if (COURSE_STATUS_COLOR_MAP[label]) return COURSE_STATUS_COLOR_MAP[label];
	if (label.includes("停")) return COURSE_STATUS_COLOR_MAP.停课;
	if (label.includes("正常") || label.includes("开")) return COURSE_STATUS_COLOR_MAP.正常;
	if (label.includes("进行")) return COURSE_STATUS_COLOR_MAP.进行中;
	if (label.includes("完成") || label.includes("结束")) return COURSE_STATUS_COLOR_MAP.已完成;
	return "#6b7280";
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
	const visibleRange = getVisibleCalendarRange(viewMode, selectedDate, year, month);
	const customRangeReady = filters.period === "自定义" && !!filters.startDate && !!filters.endDate;

	// 无论是自定义还是可见范围，都需要转换日期格式
	const startDate = customRangeReady ? formatLocalDate(filters.startDate) : formatLocalDate(visibleRange.startDate);
	const endDate = customRangeReady ? formatLocalDate(filters.endDate) : formatLocalDate(visibleRange.endDate);

	// 调试日志：检查日期格式
	console.log("[buildLessonCalendarQuery] 原始日期:", {
		startDate: filters.startDate,
		endDate: filters.endDate,
	});
	console.log("[buildLessonCalendarQuery] 转换后日期:", {
		startDate,
		endDate,
	});

	// 构建查询参数，只传递 API 需要的字段（根据接口文档）
	const params: Record<string, any> = {};

	// 只在日期有值时才添加
	if (startDate) params.startDate = startDate;
	if (endDate) params.endDate = endDate;

	// 可选参数，有值时才添加（只传递接口定义的参数）
	if (filters.className) params.className = filters.className;
	if (filters.courseName) params.courseName = filters.courseName;
	if (filters.teacherName) params.teacherName = filters.teacherName;
	if (filters.subjectName) params.subjectName = filters.subjectName;
	if (filters.classroomName) params.classroomName = filters.classroomName;

	return params;
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
