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
	FollowStageItemDTO,
} from "./type";
import type { PageDTO } from "@/components/mytable/type";

const http = useHttp();
const currBaseUrl = "/student";

/**
 * 获取课时汇总分页数据
 * @param params 查询参数
 */
export const getClassSummaryPage = async (params: ClassSummaryQueryDTO) => {
	const res = await http.post<PageDTO<ClassSummaryItemDTO>>(currBaseUrl + "/getCourseCounter", params);
	return res;
};

/**
 * 获取报名记录分页数据
 * @param params 查询参数
 */
export const getSignupRecordPage = async (params: SignupRecordQueryDTO) => {
	const res = await http.get<PageDTO<SignupRecordItemDTO>>(currBaseUrl + "/getSignupRecordList", params);
	return res;
};

/**
 * 获取课程列表
 */
export const getCourseList = async () => {
	const res = await http.get<CourseItemDTO[]>(currBaseUrl + "/getCourseList");
	return res;
};

/**
 * 批量报名
 * @param params 批量报名请求参数
 */
export const batchSignup = async (params: BatchSignupRequest) => {
	const res = await http.post(currBaseUrl + "/batchSignup", params);
	return res;
};

/**
 * 批量删除
 * @param params 批量删除请求参数
 */
export const batchDelete = async (params: BatchDeleteRequest) => {
	const res = await http.post(currBaseUrl + "/batchDelete", params);
	return res;
};

/**
 * 导出报名记录
 * @param params 导出请求参数
 */
export const exportSignupRecord = async (params: ExportSignupRecordRequest) => {
	const res = await http.post(currBaseUrl + "/exportSignupRecord", params, { responseType: "blob" });
	return res;
};

/**
 * 获取分校区列表
 */
export const getCampusList = async () => {
	const res = await http.get<CampusItemDTO[]>(currBaseUrl + "/getCampusList");
	return res;
};

/**
 * 获取课程列表（课时汇总用）
 */
export const getCourseListForClassSummary = async () => {
	const res = await http.get<CourseItemDTO[]>(currBaseUrl + "/getCourseList");
	return res;
};

/**
 * 获取跟进记录列表
 * @param params 查询参数
 */
export const getFollowRecordPage = async (params: FollowRecordQueryDTO) => {
	const res = await http.get<PageDTO<FollowRecordItemDTO>>(currBaseUrl + "/follow-up/page", params);
	return res;
};

/**
 * 获取跟进阶段列表
 */
export const getFollowStageList = async () => {
	const res = await http.get<FollowStageItemDTO[]>(currBaseUrl + "/follow-up/stage-list");
	return res;
};
