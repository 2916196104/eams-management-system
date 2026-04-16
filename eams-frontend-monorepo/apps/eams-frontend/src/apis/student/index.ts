import { useHttp } from "@/plugins/http";
import type {
	ClassSummaryQueryDTO,
	ClassSummaryItemDTO,
	SignupRecordQueryDTO,
	SignupRecordItemDTO,
	CourseItemDTO,
	BatchSignupRequest,
	BatchDeleteRequest,
	ExportSignupRecordRequest,
	CampusItemDTO,
	FollowRecordQueryDTO,
	FollowRecordItemDTO,
} from "./type";
import type {
	ResultDTO,
	StudentConsolePageDTO,
	StudentConsoleQueryDTO,
	StudentConsoleRowDTO,
	StudentCoursePageDTO,
	StudentCourseQueryDTO,
	StudentCourseRowDTO,
	StudentCourseTimesItemDTO,
	StudentCourseTimesSummaryDTO,
	StudentDetailDTO,
	StudentEnrollRequestDTO,
	StudentGraduationExportQueryDTO,
	StudentStageUpdateDTO,
} from "./type";
import type { PageDTO } from "@/components/mytable/type";

const http = useHttp();

/**
 * 获取课时汇总分页数据
 * @param params 查询参数
 */
export const getClassSummaryPage = async (params: ClassSummaryQueryDTO) => {
	const res = await http.get<PageDTO<ClassSummaryItemDTO>>("/student/list-hour-summary", params, {
		showLoading: false,
	});
	return res;
};

/**
 * 获取报名记录分页数据
 * @param params 查询参数
 */
export const getSignupRecordPage = async (params: SignupRecordQueryDTO) => {
	const res = await http.get<PageDTO<SignupRecordItemDTO>>("/student/enroll/list", params);
	return res;
};

/**
 * 获取课程列表
 */
export const getCourseList = async () => {
	const res = await http.get<CourseItemDTO[]>("/student/getCourseList");
	return res;
};

/**
 * 批量报名
 * @param params 批量报名请求参数
 */
export const batchSignup = async (params: BatchSignupRequest) => {
	const res = await http.post("/student/batchSignup", params);
	return res;
};

/**
 * 批量删除
 * @param params 批量删除请求参数
 */
export const batchDelete = async (params: BatchDeleteRequest) => {
	const res = await http.post("/student/batchDelete", params);
	return res;
};

/**
 * 导出报名记录
 * @param params 导出请求参数
 */
export const exportSignupRecord = async (params: ExportSignupRecordRequest) => {
	const res = await http.post("/student/exportSignupRecord", params, { responseType: "blob" });
	return res;
};

/**
 * 获取分校区列表
 */
export const getCampusList = async () => {
	const res = await http.get<CampusItemDTO[]>("/student/getCampusList");
	return res;
};

/**
 * 获取跟进记录列表
 * @param params 查询参数
 */
export const getFollowRecordPage = async (params: FollowRecordQueryDTO) => {
	const res = await http.get<PageDTO<FollowRecordItemDTO>>("/student/follow-up/page", params);
	return res;
};

/**
 * 保存跟进记录
 * @param params 跟进记录请求参数
 */
export const saveFollowUp = async (params: FollowRecordItemDTO) => {
	const res = await http.post("/student/follow-up/save", params);
	return res;
};

/**
 * 删除跟进记录
 * @param id 跟进记录 ID
 */
export const deleteFollowUp = async (id: number) => {
	const res = await http.post("/student/follow-up/delete", { id });
	return res;
};

const unwrapResult = <T>(payload: ResultDTO<T> | null | undefined, fallback: T): T => {
	if (payload?.errMsg) {
		throw new Error(payload.errMsg);
	}
	return payload?.result ?? fallback;
};

const getBlobData = async (url: string, params?: Record<string, any>) => {
	const response = await http.getFile(url, params, {
		responseType: "blob",
		showLoading: false,
	});
	return response.data as Blob;
};

export const STUDENT_IMPORT_ACTIONS = {
	online: "/api/student/importOnlineStudents",
	intention: "/api/student/import-intention",
	graduation: "/api/student/graduation/import",
} as const;

// The current admin student stage pages still read from the legacy list API.
export const getStudentConsolePage = async (params: StudentConsoleQueryDTO) => {
	const res = await http.get<StudentConsolePageDTO>("/stu/common/stuInformation/query-studentlist", params, {
		showLoading: false,
	});
	return (res.data ?? {}) as StudentConsolePageDTO;
};

// The course picker still depends on the legacy course page API.
export const getStudentCoursePage = async (params: StudentCourseQueryDTO) => {
	const res = await http.get<StudentCoursePageDTO>("/j4/course/list", params, {
		showLoading: false,
	});
	return (res.data ?? {}) as StudentCoursePageDTO;
};

export const getStudentDetailById = async (id: number) => {
	const res = (await http.get<any>("/student/query-detail/id", { id }, { showLoading: false })) as ResultDTO<StudentDetailDTO>;
	const detail = unwrapResult<StudentDetailDTO>(res, {});
	return {
		...detail,
		avatar: detail.avatar ?? detail.headImg,
	};
};

export const getStudentCourseTimesList = async (studentId: string) => {
	const res = await http.get<StudentCourseTimesItemDTO[]>("/student/query-course-times", { studentId }, { showLoading: false });
	return (res.data ?? []) as StudentCourseTimesItemDTO[];
};

export const summarizeStudentCourseTimes = (
	rows: StudentCourseTimesItemDTO[],
): StudentCourseTimesSummaryDTO => {
	const first = rows[0];
	return {
		studentId: first?.studentId,
		studentName: first?.studentName,
		courseTimes: rows.reduce((sum, item) => sum + Number(item.countLessonTotal ?? 0), 0),
		remainingTimes: rows.reduce((sum, item) => sum + Number(item.remainingTimes ?? 0), 0),
		details: rows,
	};
};

export const getStudentCourseTimesSummary = async (studentId: string) => {
	const rows = await getStudentCourseTimesList(studentId);
	return summarizeStudentCourseTimes(rows);
};

export const getStudentEnrollPage = async (params: SignupRecordQueryDTO) => {
	const res = await http.get<PageDTO<SignupRecordItemDTO>>("/student/enroll/list", params, {
		showLoading: false,
	});
	return (res.data ?? {}) as PageDTO<SignupRecordItemDTO>;
};

export const addStudentEnroll = async (params: StudentEnrollRequestDTO) => {
	const res = (await http.post<any>("/student/add-enroll", params)) as ResultDTO<boolean>;
	return unwrapResult<boolean>(res, false);
};

export const saveStudentInfo = async (params: StudentDetailDTO) => {
	const res = await http.post<string>("/student/save-student", params);
	return res.data ?? "";
};

export const modifyStudentStage = async (params: StudentStageUpdateDTO) => {
	const res = (await http.put<any>("/student/modify-stage", params)) as ResultDTO<boolean>;
	return unwrapResult<boolean>(res, false);
};

export const modifyStudentConsultant = async (params: StudentConsoleRowDTO) => {
	const res = (await http.post<any>("/student/modifyConsultant", params)) as ResultDTO<boolean>;
	return unwrapResult<boolean>(res, false);
};

export const exportIntentionStudentsFile = async () => {
	return getBlobData("/student/export-intention");
};

export const exportOnlineStudentsFile = async () => {
	return getBlobData("/student/exportOnlineStudents");
};

export const exportGraduatedStudentsFile = async (params?: StudentGraduationExportQueryDTO) => {
	return getBlobData("/student/graduation/export", params);
};
