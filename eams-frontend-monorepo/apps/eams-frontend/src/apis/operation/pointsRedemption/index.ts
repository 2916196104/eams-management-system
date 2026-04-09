import { useHttp } from "@/plugins/http";
import type { RedemptionApplicationList, AuditParams } from "./type";
const http = useHttp();
export const getRedemptionApplicationList = (params?: RedemptionApplicationList) => {
	return http.get<RedemptionApplicationList[]>("/j7/ex", params);
};
export const reviewRedemptionApplication = (params: AuditParams) => {
	return http.post<AuditParams>("/j7/ex", params);
};
