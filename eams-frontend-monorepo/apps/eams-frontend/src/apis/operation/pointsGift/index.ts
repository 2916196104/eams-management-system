import { useHttp } from "@/plugins/http";
import type { PageDTO } from "@/components/mytable/type";
import type { GiftList, SaveGiftParams, UseOrbanGiftParams, GetGiftDetailParams, DeleteGiftParams } from "./type";

const http = useHttp();

export const getGiftList = (params?: GiftList) => {
	return http.get<PageDTO<GiftList>>("/operation/query-list-credit_mall", params);
};

export const saveGift = (params?: SaveGiftParams) => {
	return http.post<Record<string, any>>("/operation/add-credit_mall", params);
};

export const useOrbanGift = (params?: UseOrbanGiftParams) => {
	return http.post<string>("/operation/enable-credit_mall", params);
};

export const getGiftDetail = (params: GetGiftDetailParams) => {
	return http.get<GiftList>(`/operation/query-by-id/${params.id}`, params);
};

export const deleteGift = (params?: DeleteGiftParams) => {
	return http.post<string>("/operation/delete-credit_mall", params);
};
