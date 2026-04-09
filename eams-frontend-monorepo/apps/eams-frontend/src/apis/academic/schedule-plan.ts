import { useHttp } from "@/plugins/http";

const http = useHttp();

export interface JsonVo<T> {
	code: number;
	message: string;
	data: T;
}

export interface PageDtoSchedulePlanVo {
	records: SchedulePlanItem[];
	total: number;
	size: number;
	current: number;
}

export interface SchedulePlanItem {
	id: number;
	classId: number;
	className: string;
	courseId: number;
	courseName: string;
	teacherIds: string;
	teacherNames: string;
	assistantIds: string;
	assistantNames: string;
	startDate: string;
	endDate: string;
	decLessonCount: number;
	times: number;
	excludeHoliday: boolean;
}

export interface SchedulePlanListParams {
	pageIndex?: number;
	pageSize?: number;
	classId?: number;
	courseName?: string;
}

export interface SaveSchedulePlanParams {
	id?: number;
	classId: number;
	assistantIds: number[];
	decLessonCount: number;
	endDate: string;
	excludeHoliday: boolean;
	setting: Array<{
		weeks: number[];
		startTime: string;
		endTime: string;
		roomId: number;
	}>;
	startDate: string;
	teacherIds: number[];
	times: number;
}

export interface BatchGenerateLessonDto {
	scheduleIds: number[];
	excludeHoliday?: boolean;
	overwrite?: boolean;
}

export interface ConflictCheckDto {
	scheduleIds: number[];
}

// 获取排课计划列表
export const getSchedulePlanList = (params: SchedulePlanListParams) => {
	return http.get<JsonVo<PageDtoSchedulePlanVo>>("/j5/courseplan/plan/list", params);
};

// 获取计划详情
export const getSchedulePlanDetail = (id: number) => {
	return http.get<JsonVo<SchedulePlanItem>>(`/j5/courseplan/${id}`);
};

// 保存排课计划
export const saveSchedulePlan = (data: SaveSchedulePlanParams) => {
	return http.post<JsonVo<number>>("/j5/courseplan/plan", data);
};

// 删除排课计划
export const deleteSchedulePlan = (ids: number[]) => {
	return http.delete<JsonVo<number[]>>("/j5/courseplan/plan", { data: ids });
};

// 批量生成课表
export const batchGenerateLesson = (data: BatchGenerateLessonDto) => {
	return http.post<JsonVo<any>>("/j5/courseplan/batch-generate", data);
};

// 冲突检查
export const checkConflict = (data: ConflictCheckDto) => {
	return http.post<JsonVo<any>>("/j5/courseplan/conflict-check", data);
};

// 获取教师/助教下拉列表
export const getTeacherList = (params: {
	pageIndex?: number;
	pageSize?: number;
	type?: number;
	courseId?: number;
	teacherName?: string;
}) => {
	return http.get<JsonVo<PageDtoSchedulePlanVo>>("/j5/courseplan/teachers", { params });
};
