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
import type { PageDTO } from "@/components/mytable/type";

const http = useHttp();

function buildCourseListQueryParams(params: CourseListQueryDTO) {
	const queryParams: Record<string, number | string> = {};

	const assignIfDefined = (key: string, value: number | string | undefined) => {
		if (value === undefined || value === null || value === "") return;
		// 数字类型直接赋值，字符串类型需要转换
		if (typeof value === "number") {
			queryParams[key] = value;
		} else {
			queryParams[key] = String(value);
		}
	};

	assignIfDefined("pageIndex", params.pageIndex);
	assignIfDefined("pageSize", params.pageSize);
	assignIfDefined("classId", params.classId);
	assignIfDefined("courseId", params.courseId);
	assignIfDefined("startDate", params.startDate);
	assignIfDefined("endDate", params.endDate);
	assignIfDefined("teacherId", params.teacherId);
	assignIfDefined("roomId", params.roomId);
	assignIfDefined("state", params.state);
	assignIfDefined("onTrial", params.onTrial);
	// 兼容旧字段
	assignIfDefined("cycle", params.cycle);
	assignIfDefined("className", params.className);
	assignIfDefined("courseName", params.courseName);
	assignIfDefined("teacherName", params.teacherName);
	assignIfDefined("studentName", params.studentName);

	return queryParams;
}

function buildRepeatScheduleQueryParams(params: RepeatScheduleRequestDTO) {
	const queryParams: Record<string, number | string> = {};

	const assignIfDefined = (key: string, value: number | string | undefined) => {
		if (value === undefined || value === null || value === "") return;
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
	// 可选参数
	assignIfDefined("creator", params.creator);
	assignIfDefined("addTime", params.addTime);
	assignIfDefined("editTime", params.editTime);
	assignIfDefined("editor", params.editor);

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
 * 构建学员请假列表查询参数
 */
function buildStudentLeaveQueryParams(params: StudentLeaveQueryDTO) {
	const queryParams: Record<string, number | string> = {};

	const assignIfDefined = (key: string, value: number | string | undefined) => {
		if (value === undefined || value === null || value === "") return;
		// 数字类型直接赋值，字符串类型需要转换
		if (typeof value === "number") {
			queryParams[key] = value;
		} else {
			queryParams[key] = String(value);
		}
	};

	assignIfDefined("pageIndex", params.pageIndex);
	assignIfDefined("pageSize", params.pageSize);
	assignIfDefined("nameOrPhone", params.nameOrPhone);
	assignIfDefined("teacherId", params.teacherId);
	assignIfDefined("startDate", params.startDate);
	assignIfDefined("endDate", params.endDate);

	return queryParams;
}

/**
 * 获取学员请假列表
 * @param params 查询参数
 */
export const getStudentLeavePage = async (params: StudentLeaveQueryDTO) => {
	const res = await http.get<PageDTO<StudentLeaveItemDTO>>(
		"/j5-student-leave/list",
		buildStudentLeaveQueryParams(params),
	);
	return res;
};

/**
 * 撤销请假
 * @param ids 请假 ID 列表
 */
export const cancelStudentLeave = async (ids: number[]) => {
	const res = await http.put<{ code?: number; message?: string; data?: number }>("/j5-student-leave/cancel", ids);
	return res;
};

/**
 * 获取课程表列表
 * @param params 查询参数
 */
export const getCourseListPage = async (params: CourseListQueryDTO) => {
	const res = await http.get<PageDTO<CourseListVO>>("/j5-course-schedule/list", buildCourseListQueryParams(params));
	return res;
};

/**
 * 获取课次详情
 * 请求方式为 GET，id 通过 path 参数传递。
 * @param id 课次 ID
 */
export const getCourseDetail = async (id: number | string) => {
	const res = await http.get<CourseDetailVO>(`/j5-course-schedule/detail/${id}`);
	return res;
};

function buildEvaluationListQueryParams(params: EvaluationQueryDTO) {
	const queryParams: Record<string, number | string | boolean> = {};

	const assignIfDefined = (key: string, value: number | string | boolean | undefined) => {
		if (value === undefined || value === null || value === "") return;
		// 根据类型处理值
		if (typeof value === "boolean") {
			queryParams[key] = value;
		} else if (typeof value === "number") {
			queryParams[key] = value;
		} else {
			queryParams[key] = String(value);
		}
	};

	assignIfDefined("pageIndex", params.pageIndex);
	assignIfDefined("pageSize", params.pageSize);
	assignIfDefined("lessonId", params.lessonId);
	assignIfDefined("onlyEvaluate", params.onlyEvaluate);

	return queryParams;
}

/**
 * 获取课后点评列表
 * Apifox 文档标记为 GET + requestBody，浏览器环境下改为 query 参数提交更稳妥。
 * @param params 查询参数
 */
export const getEvaluationList = async (params: EvaluationQueryDTO) => {
	const res = await http.get<PageDTO<EvaluationVO>>(
		"/j5-course-schedule/evaluation/list",
		buildEvaluationListQueryParams(params),
	);
	return res;
};

/**
 * 保存点评
 * @param data 点评数据
 */
export const saveEvaluation = async (data: EvaluationSaveDTO): Promise<EvaluationSaveResponseDTO> => {
	return http.post<number>("/j5-course-schedule/evaluation", data);
};

/**
 * 删除课次
 * Apifox 定义为 query 数组参数，这里直接拼到 URL 上，避免不同序列化格式造成后端不识别。
 * @param ids 课次 ID 列表
 */
export const deleteCourses = async (ids: number[]): Promise<DeleteCoursesResponseDTO> => {
	const query = ids.map((id) => `ids=${encodeURIComponent(String(id))}`).join("&");
	return http.delete<string>(`/j5-course-schedule/delete-courses?${query}`, undefined, {
		upType: DataUpType.form,
	});
};

function buildLessonCalendarQueryParams(params: LessonCalendarQueryDTO) {
	const queryParams: Record<string, string> = {};

	const assignIfDefined = (key: string, value: number | string | undefined) => {
		if (value === undefined || value === null || value === "") return;
		// 所有参数都转换为字符串（URL query 参数都是字符串格式）
		queryParams[key] = String(value);
	};

	// 分页参数（接口文档定义）
	assignIfDefined("pageIndex", params.pageIndex ?? 1);
	assignIfDefined("pageSize", params.pageSize ?? 1000);
	
	// 核心筛选参数（接口文档定义）
	assignIfDefined("classId", params.classId);
	assignIfDefined("courseId", params.courseId);
	assignIfDefined("startDate", params.startDate);
	assignIfDefined("endDate", params.endDate);
	assignIfDefined("teacherId", params.teacherId);
	assignIfDefined("roomId", params.roomId);
	assignIfDefined("state", params.state);
	assignIfDefined("onTrial", params.onTrial);
	
	// 兼容旧字段
	assignIfDefined("className", params.className);
	assignIfDefined("courseName", params.courseName);
	assignIfDefined("teacherName", params.teacherName);

	return queryParams;
}

/**
 * 获取课表日历
 * 接口地址：/j5-course-schedule/calendar
 * 请求方式：GET
 * 数据类型：application/x-www-form-urlencoded
 * @param params 查询参数
 */
export const getLessonCalendar = async (params: LessonCalendarQueryDTO) => {
	const queryParams = buildLessonCalendarQueryParams(params);
	const res = await http.get<LessonCalendarVO[]>("/j5-course-schedule/calendar", undefined, {
		params: queryParams,
	});
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
		return await http.post<string>("/j5-course-schedule/repeat-schedule", undefined, {
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
	const queryParams: Record<string, string | number> = {};

	const assignIfDefined = (key: string, value: string | number | undefined) => {
		if (value === undefined || value === null || value === "") return;
		queryParams[key] = value;
	};

	assignIfDefined("id", params.id);
	assignIfDefined("status", params.status);
	assignIfDefined("editTime", params.editTime);
	assignIfDefined("editor", params.editor);

	return queryParams;
}

/**
 * 预约课程开关
 * 请求方式为 POST，参数通过 query 传递，使用 form 编码。
 * @param params 查询参数
 */
export const switchSchedule = async (params: SwitchScheduleRequestDTO): Promise<SwitchScheduleResponseDTO> => {
	try {
		return await http.post<string>("/j5-course-schedule/switch-schedule", undefined, {
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
 * 请求方式为 PUT + JSON body。
 * @param lessonIds 课次 ID 列表
 * @param isResume true=复课 false=停课
 */
export const resumeCourses = async (lessonIds: number[], isResume: boolean): Promise<ResumeCoursesResponseDTO> => {
	const res = await http.put<ResumeCoursesResponseDTO>("/j5-course-schedule/pause-resume", {
		lessonIds,
		isResume,
	});
	return res as unknown as ResumeCoursesResponseDTO;
};

/**
 * 批量修改课次
 * 请求方式为 PUT + JSON body。
 * @param params 批量修改参数
 */
export const batchUpdateCourses = async (params: BatchUpdateCoursesDTO): Promise<BatchUpdateCoursesResponseDTO> => {
	const res = await http.put<BatchUpdateCoursesResponseDTO>("/j5-course-schedule/batch-update-courses", params);
	return res as unknown as BatchUpdateCoursesResponseDTO;
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
		if (value === undefined || value === null || value === "") return;
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
	// 可选参数
	assignIfDefined("creator", params.creator);
	assignIfDefined("addTime", params.addTime);
	assignIfDefined("editTime", params.editTime);
	assignIfDefined("editor", params.editor);

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
		return await http.post<string>("/j5-course-schedule/free-schedule", undefined, {
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
