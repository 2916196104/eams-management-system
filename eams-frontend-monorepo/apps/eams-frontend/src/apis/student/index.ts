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
import type { PageDTO } from "@/components/mytable/type";

const http = useHttp();

/**
 * 获取课时汇总分页数据
 * @param params 查询参数
 */
export const getClassSummaryPage = async (params: ClassSummaryQueryDTO) => {
	const res = await http.get<PageDTO<ClassSummaryItemDTO>>("/student/list-hour-summary", params);
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
 * 获取课程列表（课时汇总用）
 */
export const getCourseListForClassSummary = async () => {
	const res = await http.get<CourseItemDTO[]>("/student/getCourseList");
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
