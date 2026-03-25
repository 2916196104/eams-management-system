import { useHttp } from "@/plugins/http";
import type { StudentLeaveQueryDTO, StudentLeaveItemDTO } from "./type";

const http = useHttp();
const currBaseUrl = "/student";

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
