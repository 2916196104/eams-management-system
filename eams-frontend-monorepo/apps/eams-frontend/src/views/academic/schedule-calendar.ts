import type { LessonCalendarVO } from "@/apis/academic/type";

export type ScheduleCalendarViewMode = "month" | "week" | "day";
export type ScheduleCalendarPeriod = "本月" | "本周" | "自定义";

// 下拉选项数据类型
export interface SelectOption {
	value: number;
	label: string;
}

// 课程日历筛选器字段
// 根据后端接口文档：/j5-course-schedule/calendar
// 支持的参数：classId, courseId, endDate, onTrial, pageIndex, pageSize, roomId, startDate, state, teacherId
export type ScheduleCalendarFilters = {
	// ID 字段（后端接口期望的类型）
	classId?: number; // 班级 ID ✅ 新增
	courseId?: number; // 课程 ID ✅ 新增
	teacherId?: number; // 教师 ID ✅ 新增
	roomId?: number; // 教室 ID ✅ 新增
	
	// 名称字段（用于显示，不直接传递给后端）
	className?: string; // 班级名称
	courseName?: string; // 课程名称
	teacherName?: string; // 老师名称
	classroomName?: string; // 教室名称
	
	// 日期范围
	startDate: string; // 开始日期
	endDate: string; // 结束日期
	
	// 周期选择
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

// 格式化日期为后端要求的 LocalDate 格式 (yyyy-MM-dd)
// 根据接口文档：/j5-course-schedule/calendar 期望 string(date) 格式
export function formatLocalDate(dateString: string): string {
	if (!dateString) return "";
	// 验证格式是否为 YYYY-MM-DD
	const dateRegex = /^\d{4}-\d{2}-\d{2}$/;
	if (dateRegex.test(dateString)) {
		// 格式正确，直接返回
		return dateString;
	}
	// 格式不正确，尝试解析并重新格式化
	const date = new Date(dateString);
	if (Number.isNaN(date.getTime())) return dateString;
	return formatDate(date);
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

/**
 * 构建课程日历查询参数
 * 接口地址：/j5-course-schedule/calendar
 * 请求方式：GET
 * 数据类型：application/x-www-form-urlencoded
 *
 * @param filters - 筛选条件
 * @param viewMode - 视图模式（month/week/day）
 * @param selectedDate - 选中的日期
 * @param year - 当前年份
 * @param month - 当前月份
 * @returns 符合后端接口要求的查询参数对象
 */
export function buildLessonCalendarQuery(
	filters: ScheduleCalendarFilters,
	viewMode: ScheduleCalendarViewMode,
	selectedDate: Date,
	year: number,
	month: number,
) {
	const visibleRange = getVisibleCalendarRange(viewMode, selectedDate, year, month);
	const customRangeReady = filters.period === "自定义" && !!filters.startDate && !!filters.endDate;

	// 无论是自定义还是可见范围，都需要转换日期格式为 yyyy-MM-dd
	const startDate = customRangeReady ? formatLocalDate(filters.startDate) : formatLocalDate(visibleRange.startDate);
	const endDate = customRangeReady ? formatLocalDate(filters.endDate) : formatLocalDate(visibleRange.endDate);

	// 构建查询参数，严格按照后端接口文档定义
	// 接口支持的参数：
	// - classId: 班级 ID (integer)
	// - courseId: 课程 ID (integer)
	// - endDate: 结束日期 (string, yyyy-MM-dd)
	// - onTrial: 是否试听 (integer, 0/1)
	// - pageIndex: 查询页码 (integer)
	// - pageSize: 查询条数 (integer)
	// - roomId: 教室 ID (integer)
	// - startDate: 开始日期 (string, yyyy-MM-dd)
	// - state: 课次状态 (integer)
	// - teacherId: 教师 ID (integer)
	const params: Record<string, any> = {};

	// 分页参数（必需）
	params.pageIndex = 1;
	params.pageSize = 1000; // 获取全部数据，前端进行分页展示

	// 日期范围参数（核心筛选条件）
	if (startDate) params.startDate = startDate;
	if (endDate) params.endDate = endDate;

	// ID 筛选参数（后端接口要求的格式）
	if (filters.classId) params.classId = filters.classId;
	if (filters.courseId) params.courseId = filters.courseId;
	if (filters.teacherId) params.teacherId = filters.teacherId;
	if (filters.roomId) params.roomId = filters.roomId;

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

// 导出 API 调用函数（从单独的文件）
export {
	getClassSelectOptions,
	getCourseSelectOptions,
	getTeacherSelectOptions,
	getClassroomSelectOptions,
} from "./schedule-calendar-api";
