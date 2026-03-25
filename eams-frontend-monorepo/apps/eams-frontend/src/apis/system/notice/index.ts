import { useHttp } from "@/plugins/http";
import type { INoticeDel, INoticeList, INoticeSave } from "./type";

const http = useHttp();
const currBaseUrl = "/notice";

/**
 * 获取公告详情
 */
export const getNoticeDetail = (id: number) => {
	return http.get(`${currBaseUrl}/get-by-id/:id`, {
		params: { id },
	});
};

export const delNotice = (ids: INoticeDel) => {
	return http.delete(`${currBaseUrl}/delete/:ids`, {
		params: {
			ids,
		},
	});
};

export const getNoticeList = (data: INoticeList) => {
	return http.get(`${currBaseUrl}/get-by-id/`, {
		params: {
			data,
		},
	});
};

export const editNotice = (data: INoticeSave) => {
	return http.post(`${currBaseUrl}/save/`, data);
};
