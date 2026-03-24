import { useHttp } from "@/plugins/http";
import type { StudentLeaveQueryDTO, StudentLeaveItemDTO } from "./type";
import type { PageDTO } from "@/components/mytable/type";

const currBaseUrl = "/student";

/**
 * 获取学员请假列表
 * @param params 查询参数
 */
export const getStudentLeavePage = async (params: StudentLeaveQueryDTO) => {
	const res = await http.get<PageDTO<StudentLeaveItemDTO>>(currBaseUrl + "/student-leave/page", params);
	return res;
};
