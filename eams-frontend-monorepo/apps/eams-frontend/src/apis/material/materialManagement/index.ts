import { useHttp } from "@/plugins/http";
import type { PageDTO } from "@/components/mytable/type";
import type { MaterialListItem, InboundAndOutbound } from "./type";
const http = useHttp();
export const getMaterialList = (params?: MaterialListItem) => {
	return http.get<PageDTO<MaterialListItem>>("/j3/ms/records", params);
};
export const MaterialInboundAndOutbound = (params?: InboundAndOutbound) => {
	return http.put<InboundAndOutbound>("/j3/ms/change", params);
};
