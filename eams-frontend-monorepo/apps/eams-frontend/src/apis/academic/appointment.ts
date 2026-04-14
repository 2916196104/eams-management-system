import { useHttp } from "@/plugins/http";

const http = useHttp();

export interface JsonVo<T> {
	code: number;
	message: string;
	data: T;
}

export interface PageDtoAppointmentDto {
	rows: AppointmentItem[];
	total: number;
	size: number;
	current: number;
}

export interface AppointmentItem {
	id: number;
	studentId: number;
	studentName: string;
	studentMobile: string;
	lessonId: number;
	lessonTitle: string;
	lessonTime: string;
	addTime: string;
	verifyState: string;
	remark?: string;
}

export interface AppointmentCalendarVo {
	id: number;
	studentId: number;
	studentName: string;
	studentMobile: string;
	lessonId: number;
	lessonTitle: string;
	lessonTime: string;
	addTime: string;
	verifyState: string;
}

export interface AppointmentDetailVo {
	id: number;
	studentId: number;
	studentName: string;
	studentMobile: string;
	lessonId: number;
	lessonTitle: string;
	lessonTime: string;
	addTime: string;
	verifyState: string;
	verifyRemark?: string;
	remark?: string;
}

export interface AppointmentListParams {
	pageIndex?: number;
	pageSize?: number;
	studentNames?: string[];
	courseNames?: string[];
	startDate?: string;
	endDate?: string;
}

export interface CalendarParams {
	startDate?: string;
	endDate?: string;
}

// 获取预约列表（修复点：使用 { params } 包裹）
export const getAppointmentList = (params: AppointmentListParams) => {
	return http.get<JsonVo<PageDtoAppointmentDto>>("/j5-appoint", params);
};

// 获取预约日历（修复点：使用 { params } 包裹）
export const getAppointmentCalendar = (params: CalendarParams) => {
	return http.get<JsonVo<AppointmentCalendarVo[]>>("/j5-appoint/calendar", params);
};

// 获取预约详情（无参数，无需改动）
export const getAppointmentDetail = (id: number) => {
	return http.get<JsonVo<AppointmentDetailVo>>(`/j5-appoint/${id}`);
};

// 确认预约（POST 请求，数组作为请求体，保持原样）
export const approveAppointment = (ids: number[]) => {
	return http.post<JsonVo<number[]>>("/j5-appoint/confirm", ids);
};

// 取消预约
export const cancelAppointment = (ids: number[]) => {
	return http.post<JsonVo<number[]>>("/j5-appoint/cancel", ids);
};