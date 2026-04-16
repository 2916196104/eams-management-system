import { useHttp } from "@/plugins/http";

const http = useHttp();

export interface JsonVo<T> {
	code: number;
	message: string;
	data: T;
}

export interface PageDtoSchedulePlanVo {
	rows: SchedulePlanItem[];
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

// 获取计划列表（修复点：使用 { params } 包裹）
export const getSchedulePlanList = (params: SchedulePlanListParams) => {
	return http.get<JsonVo<PageDtoSchedulePlanVo>>("/j5-course-plan/plan/list", params);
};

// 获取计划详情（路径参数，无需改动）
export const getSchedulePlanDetail = (id: number) => {
	return http.get<JsonVo<SchedulePlanItem>>(`/j5-course-plan/${id}`);
};

// 保存计划（POST，请求体数据，无需改动）
export const saveSchedulePlan = (data: SaveSchedulePlanParams) => {
	return http.post<JsonVo<number>>("/j5-course-plan/plan", data);
};

// 删除计划（DELETE，带请求体 ids，已正确使用 { data }）
export const deleteSchedulePlan = (ids: number[]) => {
	return http.delete<JsonVo<number[]>>("/j5-course-plan/plan", { data: ids });
};

// 批量生成课表（POST，无需改动）
export const batchGenerateLesson = (data: BatchGenerateLessonDto) => {
	return http.post<JsonVo<any>>("/j5-course-plan/batch-generate", data);
};

// 冲突检查（POST，无需改动）
export const checkConflict = (data: ConflictCheckDto) => {
	return http.post<JsonVo<any>>("/j5-course-plan/conflict-check", data);
};

// 删除已生成课表（DELETE，带请求体，已正确使用 { data }）
export const deleteGeneratedLessons = (data: {
	scheduleIds: number[];
	forceDelete?: boolean;
	deleteReason?: string;
}) => {
	return http.delete<JsonVo<any>>("/j5-course-plan/delete-lessons", { data });
};

// 获取教师/助教下拉列表（修复点：使用 { params } 包裹）
export const getTeacherList = (params: {
	pageIndex?: number;
	pageSize?: number;
	type?: number;
	courseId?: number;
	teacherName?: string;
}) => {
	return http.get<JsonVo<PageDtoSchedulePlanVo>>("/j5-course-plan/teachers", params);
};