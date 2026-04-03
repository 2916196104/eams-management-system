import { useHttp } from "@/plugins/http";
import type { TrialCard, TrialCardDetail, TrialCardRecord, SaveCard, deleteCard } from "./type";
const http = useHttp();
//获取试听卡列表
export const getTrialCardList = (params?: TrialCard) => {
	return http.post<TrialCard>("/trial/trialList", params);
};
//获取试听卡详情
export const getTrialCardDetail = (id: number) => {
	return http.get<TrialCardDetail>(`/trial/query-detail/${id}`);
};
//保存试听卡
export const saveTrialCard = (params: SaveCard) => {
	return http.post<SaveCard>("/trial", params);
};
//获取试听卡领取记录
export const getTrialCardRecord = (params?: TrialCardRecord) => {
	return http.get<TrialCardRecord>("/trial/recordsList", params);
};

//deleteTrialCard 删除试听卡
export const deleteTrialCard = (params?: deleteCard) => {
	return http.post<deleteCard>("/trial/removeTrialCard", params);
};
