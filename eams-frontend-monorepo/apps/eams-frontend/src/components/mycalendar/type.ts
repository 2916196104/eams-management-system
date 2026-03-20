/**
 * 日历视图模式
 */
export type CalendarViewMode = "month" | "week" | "day";

/**
 * 日历单元格数据（月视图下的单格）
 */
export interface CalendarCell {
	/** 日期对象 */
	date: Date;
	/** 是否为当前月 */
	isCurrentMonth: boolean;
	/** 日号 1-31 */
	day: number;
	/** 是否为今天 */
	isToday?: boolean;
	/** 是否为选中日 */
	isSelected?: boolean;
}

/**
 * 日历组件属性
 */
export interface MyCalendarProps {
	/** 组件标题 */
	title?: string;
	/** 当前展示的年份 */
	year?: number;
	/** 当前展示的月份 0-11 */
	month?: number;
	/** 选中的日期 */
	selectedDate?: Date | null;
	/** 视图模式 */
	viewMode?: CalendarViewMode;
}
