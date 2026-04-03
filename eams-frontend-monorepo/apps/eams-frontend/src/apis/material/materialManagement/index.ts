import { useHttp } from "@/plugins/http";
import type { MaterialListItem, InboundAndOutbound } from "./type";
const http = useHttp();
export const getMaterialList = (params?: MaterialListItem) => {
	return http.get<MaterialListItem[]>("/j3/ms/records", params);
};
export const MaterialInboundAndOutbound = (params?: InboundAndOutbound) => {
	return http.put<InboundAndOutbound>("/j3/ms/change", params);
};
