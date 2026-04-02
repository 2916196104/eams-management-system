import { useHttp } from "@/plugins/http";
import type { GiftList, SaveGiftParams, UseOrbanGiftParams, GetGiftDetailParams, DeleteGiftParams } from "./type.ts";
const http = useHttp();
export const getGiftList = (params?: GiftList) => {
	return http.get<GiftList[]>("/operation/query-list-credit_mall", params);
};
export const saveGift = (params?: SaveGiftParams) => {
	return http.post<GiftList[]>("/operation/add-credit_mall", params);
};

//启用或禁用礼品
export const useOrbanGift = (params?: UseOrbanGiftParams) => {
	return http.post<UseOrbanGiftParams[]>("/operation/enable-credit_mall", params);
};
//获取礼品详情
export const getGiftDetail = (params: GetGiftDetailParams) => {
	return http.get<GetGiftDetailParams>(`/operation/query-by-id/${params.id}`, params);
};

//删除礼品
export const deleteGift = (params?: DeleteGiftParams) => {
	return http.post<DeleteGiftParams[]>("/operation/delete-credit_mall", params);
};
