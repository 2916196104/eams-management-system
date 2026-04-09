//	学员请假接口
import { DataUpType, useHttp } from "@/plugins/http";
import type {
	BatchUpdateCoursesDTO,
	BatchUpdateCoursesResponseDTO,
	CourseListQueryDTO,
	CourseDetailVO,
	CourseListVO,
	DeleteCoursesResponseDTO,
	EvaluationQueryDTO,
	EvaluationSaveDTO,
	EvaluationSaveResponseDTO,
	EvaluationVO,
	LessonCalendarQueryDTO,
	LessonCalendarVO,
	RepeatScheduleRequestDTO,
	RepeatScheduleResponseDTO,
	FreeScheduleRequestDTO,
	FreeScheduleResponseDTO,
	ResumeCoursesResponseDTO,
	SwitchScheduleRequestDTO,
	SwitchScheduleResponseDTO,
	StudentLeaveItemDTO,
	StudentLeaveQueryDTO,
	UpdateCourseDTO,
	UpdateCourseResponseDTO,
} from "./type";

const http = useHttp();
const currBaseUrl = "/student";

function buildCourseListQueryParams(params: CourseListQueryDTO) {
	const queryParams: Record<string, number | string> = {};

	const assignIfDefined = (key: string, value: number | string | undefined) => {
		if (value === undefined || value === "") return;
		queryParams[key] = value;
	};

	assignIfDefined("pageIndex", params.pageIndex);
	assignIfDefined("pageSize", params.pageSize);
	assignIfDefined("cycle", params.cycle);
	assignIfDefined("className", params.className);
	assignIfDefined("courseName", params.courseName);
	assignIfDefined("teacherName", params.teacherName);
	assignIfDefined("studentName", params.studentName);
	assignIfDefined("startDate", params.startDate);
	assignIfDefined("endDate", params.endDate);

	return queryParams;
}

function buildRepeatScheduleQueryParams(params: RepeatScheduleRequestDTO) {
	const queryParams: Record<string, number | string> = {};

	const assignIfDefined = (key: string, value: number | string | undefined) => {
		if (value === undefined || value === "") return;
		queryParams[key] = value;
	};

	// 重复排课参数
	assignIfDefined("id", params.id);
	assignIfDefined("classId", params.classId);
	assignIfDefined("className", params.className);
	assignIfDefined("teacherId", params.teacherId);
	assignIfDefined("teacherName", params.teacherName);
	assignIfDefined("assistantId", params.assistantId);
	assignIfDefined("assistantName", params.assistantName);
	assignIfDefined("startTime", params.startTime);
	assignIfDefined("endTime", params.endTime);
	assignIfDefined("descLessonCount", params.descLessonCount);
	assignIfDefined("times", params.times);
	assignIfDefined("excludeHoliday", params.excludeHoliday);
	assignIfDefined("status", params.status);

	params.lessonScheduleSettingDtos.forEach((item, index) => {
		assignIfDefined(`lessonScheduleSettingDtos[${index}].scheduleId`, item.scheduleId);
		assignIfDefined(`lessonScheduleSettingDtos[${index}].weeks`, item.weeks);
		assignIfDefined(`lessonScheduleSettingDtos[${index}].startTime`, item.startTime);
		assignIfDefined(`lessonScheduleSettingDtos[${index}].endTime`, item.endTime);
		assignIfDefined(`lessonScheduleSettingDtos[${index}].roomId`, item.roomId);
	});

	return queryParams;
}

/**
 * 获取学员请假列表
 * @param params 查询参数
 */
export const getStudentLeavePage = async (params: StudentLeaveQueryDTO) => {
	const res = await http.get<StudentLeaveItemDTO[]>(currBaseUrl + "/student-leave/list", params);
	return res;
};

/**
 * 撤销请假
 * @param ids 请假 ID 列表
 */
export const cancelStudentLeave = async (ids: number[]) => {
	const res = await http.put<{ code?: number; message?: string; data?: number }>(
		currBaseUrl + "/student-leave/cancel",
		ids,
	);
	return res;
};

/**
 * 获取课程表列表
 * @param params 查询参数
 */
export const getCourseListPage = async (params: CourseListQueryDTO) => {
	const res = await http.get<{
		pageIndex?: number;
		pageSize?: number;
		total?: number;
		pages?: number;
		rows?: CourseListVO[];
	}>("/j5/courseschedule/list", buildCourseListQueryParams(params));
	return res;
};

/**
 * 获取课次详情
 * Apifox 文档同时出现 path 和 query 两种写法，这里两者都带上以兼容后端实现。
 * @param id 课次 ID
 */
export const getCourseDetail = async (id: number | string) => {
	const res = await http.get<CourseDetailVO>(`/j5/courseschedule/detail/${id}`, { id });
	return res;
};

function buildEvaluationListQueryParams(params: EvaluationQueryDTO) {
	const queryParams: Record<string, string> = {};

	const assignIfDefined = (key: string, value: string | undefined) => {
		if (!value) return;
		queryParams[key] = value;
	};

	assignIfDefined("startDate", params.startDate);
	assignIfDefined("endDate", params.endDate);
	assignIfDefined("teacherId", params.teacherId);
	assignIfDefined("teacherName", params.teacherName);
	assignIfDefined("id", params.id);
	assignIfDefined("name", params.name);

	return queryParams;
}

/**
 * 获取课后点评列表
 * Apifox 文档标记为 GET + requestBody，浏览器环境下改为 query 参数提交更稳妥。
 * @param params 查询参数
 */
export const getEvaluationList = async (params: EvaluationQueryDTO) => {
	const res = await http.get<{
		pageIndex?: number;
		pageSize?: number;
		total?: number;
		pages?: number;
		rows?: EvaluationVO[];
	}>("/j5/courseschedule/evaluation/list", buildEvaluationListQueryParams(params));
	return res;
};

/**
 * 保存点评
 * @param data 点评数据
 */
export const saveEvaluation = async (data: EvaluationSaveDTO): Promise<EvaluationSaveResponseDTO> => {
	return http.post<number>("/j5/courseschedule/evaluation", data);
};

/**
 * 删除课次
 * Apifox 定义为 query 数组参数，这里直接拼到 URL 上，避免不同序列化格式造成后端不识别。
 * @param ids 课次 ID 列表
 */
export const deleteCourses = async (ids: number[]): Promise<DeleteCoursesResponseDTO> => {
	const query = ids.map((id) => `ids=${encodeURIComponent(String(id))}`).join("&");
	return http.delete<string>(`/j5/courseschedule/delete-courses?${query}`, undefined, {
		upType: DataUpType.form,
	});
};

/**
 * 获取课表日历
 * @param params 查询参数
 */
export const getLessonCalendar = async (params: LessonCalendarQueryDTO) => {
	const res = await http.get<LessonCalendarVO[]>("/j5/courseschedule/calendar", params);
	return res;
};

/**
 * 重复排课
 * Apifox 将参数定义为 query 参数，这里按 query 方式提交。
 * 同时兼容接口返回 `code: 0` 的场景，避免被全局响应拦截误判成失败。
 * @param params 查询参数
 */
export const repeatSchedule = async (params: RepeatScheduleRequestDTO): Promise<RepeatScheduleResponseDTO> => {
	try {
		return await http.post<string>("/j5/courseschedule/repeat-schedule", undefined, {
			params: buildRepeatScheduleQueryParams(params),
			upType: DataUpType.form,
		});
	} catch (error: any) {
		if (error?.data && typeof error.data === "object") {
			return error.data as RepeatScheduleResponseDTO;
		}
		throw error;
	}
};

function buildSwitchScheduleQueryParams(params: SwitchScheduleRequestDTO) {
	const queryParams: Record<string, string> = {};

	if (params.id) {
		queryParams.id = params.id;
	}
	if (params.status) {
		queryParams.status = params.status;
	}

	return queryParams;
}

/**
 * 预约课程开关
 * Apifox 将参数定义为 query 参数，这里按 query 方式提交。
 * @param params 查询参数
 */
export const switchSchedule = async (params: SwitchScheduleRequestDTO): Promise<SwitchScheduleResponseDTO> => {
	try {
		return await http.post<string>("/j5/courseschedule/switch-schedule", undefined, {
			params: buildSwitchScheduleQueryParams(params),
			upType: DataUpType.form,
		});
	} catch (error: any) {
		if (error?.data && typeof error.data === "object") {
			return error.data as SwitchScheduleResponseDTO;
		}
		throw error;
	}
};

/**
 * 停/复课
 * Apifox 定义为 query 数组参数，这里直接拼到 URL 上，避免序列化格式差异。
 * @param courseIds 课次 ID 列表
 * @param isResume true=复课 false=停课
 */
export const resumeCourses = async (courseIds: number[], isResume: boolean): Promise<ResumeCoursesResponseDTO> => {
	const idsQuery = courseIds.map((id) => `courseIds=${encodeURIComponent(String(id))}`).join("&");
	const query = `${idsQuery}&isResume=${encodeURIComponent(String(isResume))}`;
	return http.put<number>(`/j5/courseschedule/resume?${query}`, undefined, {
		upType: DataUpType.form,
	});
};

function buildBatchUpdateCoursesQuery(params: BatchUpdateCoursesDTO) {
	const queryParts: string[] = [];

	params.lessonIds.forEach((id) => {
		queryParts.push(`lessonIds=${encodeURIComponent(String(id))}`);
	});

	const appendIfDefined = (key: string, value: string | number | undefined) => {
		if (value === undefined || value === "") return;
		queryParts.push(`${key}=${encodeURIComponent(String(value))}`);
	};

	appendIfDefined("dayOffset", params.dayOffset);
	appendIfDefined("teacherId", params.teacherId);
	appendIfDefined("teacherName", params.teacherName);
	appendIfDefined("assistantId", params.assistantId);
	appendIfDefined("assistantName", params.assistantName);
	appendIfDefined("classroomId", params.classroomId);
	appendIfDefined("classroomName", params.classroomName);
	appendIfDefined("startTime", params.startTime);
	appendIfDefined("endTime", params.endTime);

	return queryParts.join("&");
}

/**
 * 批量修改课次
 * @param params 批量修改参数
 */
export const batchUpdateCourses = async (params: BatchUpdateCoursesDTO): Promise<BatchUpdateCoursesResponseDTO> => {
	return http.put<string>(`/j5/courseschedule/batch-update-courses?${buildBatchUpdateCoursesQuery(params)}`, undefined, {
		upType: DataUpType.form,
	});
};

function buildUpdateCourseQuery(params: UpdateCourseDTO) {
	const queryParts: string[] = [`id=${encodeURIComponent(String(params.id))}`];

	const appendIfDefined = (key: string, value: string | number | boolean | undefined) => {
		if (value === undefined || value === "") return;
		queryParts.push(`${key}=${encodeURIComponent(String(value))}`);
	};

	appendIfDefined("title", params.title);
	appendIfDefined("className", params.className);
	appendIfDefined("classId", params.classId);
	appendIfDefined("teacherName", params.teacherName);
	appendIfDefined("teacherId", params.teacherId);
	appendIfDefined("assistantName", params.assistantName);
	appendIfDefined("assistantId", params.assistantId);
	appendIfDefined("startDate", params.startDate);
	appendIfDefined("endDate", params.endDate);
	appendIfDefined("roomId", params.roomId);
	appendIfDefined("roomName", params.roomName);
	appendIfDefined("decCount", params.decCount);
	appendIfDefined("enableReserve", params.enableReserve);
	appendIfDefined("batchSyncTime", params.batchSyncTime);
	appendIfDefined("checkConflict", params.checkConflict);

	return queryParts.join("&");
}

/**
 * 修改课次
 * @param params 修改参数
 */
export const updateCourse = async (params: UpdateCourseDTO): Promise<UpdateCourseResponseDTO> => {
	return http.put<string>(`/j5/courseschedule/update-course?${buildUpdateCourseQuery(params)}`, undefined, {
		upType: DataUpType.form,
	});
};

function buildFreeScheduleQueryParams(params: FreeScheduleRequestDTO) {
	const queryParams: Record<string, number | string | boolean> = {};

	const assignIfDefined = (key: string, value: number | string | boolean | undefined) => {
		if (value === undefined || value === "") return;
		queryParams[key] = value;
	};

	assignIfDefined("id", params.id);
	assignIfDefined("classId", params.classId);
	assignIfDefined("className", params.className);
	assignIfDefined("teacherId", params.teacherId);
	assignIfDefined("teacherName", params.teacherName);
	assignIfDefined("assistantId", params.assistantId);
	assignIfDefined("assistantName", params.assistantName);
	assignIfDefined("startTime", params.startTime);
	assignIfDefined("endTime", params.endTime);
	assignIfDefined("descLessonCount", params.descLessonCount);
	assignIfDefined("times", params.times);
	assignIfDefined("excludeHoliday", params.excludeHoliday);
	assignIfDefined("status", params.status);

	params.lessonScheduleSettingDtos.forEach((item, index) => {
		assignIfDefined(`lessonScheduleSettingDtos[${index}].scheduleId`, item.scheduleId);
		assignIfDefined(`lessonScheduleSettingDtos[${index}].weeks`, item.weeks);
		assignIfDefined(`lessonScheduleSettingDtos[${index}].startTime`, item.startTime);
		assignIfDefined(`lessonScheduleSettingDtos[${index}].endTime`, item.endTime);
		assignIfDefined(`lessonScheduleSettingDtos[${index}].roomId`, item.roomId);
	});

	return queryParams;
}

/**
 * 自由排课
 * Apifox 将参数定义为 query 参数，这里按 query 方式提交。
 * 同时兼容接口返回 `code: 0` 的场景，避免被全局响应拦截误判成失败。
 * @param params 查询参数
 */
export const freeSchedule = async (params: FreeScheduleRequestDTO): Promise<FreeScheduleResponseDTO> => {
	try {
		return await http.post<string>("/j5/courseschedule/free-schedule", undefined, {
			params: buildFreeScheduleQueryParams(params),
			upType: DataUpType.form,
		});
	} catch (error: any) {
		if (error?.data && typeof error.data === "object") {
			return error.data as FreeScheduleResponseDTO;
		}
		throw error;
	}
};
