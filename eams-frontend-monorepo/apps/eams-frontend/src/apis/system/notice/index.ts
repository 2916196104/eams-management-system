import { DataUpType } from "@/apis/http";
import { useHttp } from "@/plugins/http";
import type { INoticeDel, INoticeList, INoticeSave } from "./type";

const http = useHttp();
const currBaseUrl = "/j3-system";
const legacyBaseUrl = "/notice";

function appendQuery(
	path: string,
	params?: Record<string, unknown | Array<string | number | boolean | null | undefined>>,
) {
	if (!params) return path;

	const search = new URLSearchParams();
	for (const [key, value] of Object.entries(params)) {
		if (Array.isArray(value)) {
			value.forEach((item) => {
				if (item === undefined || item === null || item === "") return;
				search.append(key, String(item));
			});
			continue;
		}

		if (value === undefined || value === null || value === "") continue;
		search.append(key, String(value));
	}

	const query = search.toString();
	return query ? `${path}?${query}` : path;
}

/**
 * 获取公告详情
 */
export const getNoticeDetail = (id: number) => {
	return http.get(`${currBaseUrl}/detail/${id}`).catch(() => http.get(`${legacyBaseUrl}/get-by-id/${id}`));
};

/**
 * 删除公告
 */
export const delNotice = (data: INoticeDel) => {
	return http
		.delete(appendQuery(`${currBaseUrl}/delete`, { ids: data.ids }), undefined, { upType: DataUpType.form })
		.catch(() => http.delete(`${legacyBaseUrl}/delete`, data.ids));
};

/**
 * 获取公告列表
 */
export const getNoticeList = (data: INoticeList) => {
	return http
		.get(`${currBaseUrl}/detail_list`, {
			title: data.title,
			creator: data.creator,
			pageNum: data.pageNum,
			pageSize: data.pageSize,
		})
		.catch(() => http.get(`${legacyBaseUrl}/get-by-id`, data));
};

/**
 * 保存公告
 */
export const editNotice = (data: INoticeSave) => {
	return http.post(`${currBaseUrl}/save`, data).catch(() => http.post(`${legacyBaseUrl}/save`, data));
};
