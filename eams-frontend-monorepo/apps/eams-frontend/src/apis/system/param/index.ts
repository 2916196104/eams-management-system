import { useHttp } from "@/plugins/http";
import type { SysParamOptionDTO } from "./type";

const http = useHttp();
const currBaseUrl = "/j2-sys/sysparam";
const legacyBaseUrl = "/sys/sysparam";

/**
 * 获取设置列表
 */
export const getParamList = () => {
	return http.get(`${currBaseUrl}/list`).catch(() => http.get(legacyBaseUrl));
};

/**
 * 获取设置详情
 * @param id 设置分类 ID
 */
export const getParamDetail = (id: number) => {
	return http.get(`${currBaseUrl}/${id}`).catch(() => http.get(`${legacyBaseUrl}/${id}`));
};

/**
 * 保存设置
 * @param data 设置选项数据
 */
export const updateParam = (data: SysParamOptionDTO) => {
	return http.put(`${currBaseUrl}/update`, data).catch(() => http.put(legacyBaseUrl, data));
};
