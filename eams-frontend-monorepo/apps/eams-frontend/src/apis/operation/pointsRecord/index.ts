import { useHttp } from "@/plugins/http";
import type { PointsRecordListItem, AdjustPointsRecordRequest } from "./type.ts";
const http = useHttp();
export const getPointsRecordList = (params?: PointsRecordListItem) => {
	return http.get<PointsRecordListItem[]>("/pointsRecord/query-list-points_record", params);
};
export const adjustPointsRecord = (params: AdjustPointsRecordRequest) => {
	return http.delete<PointsRecordListItem>("/pointsRecord/update-points", {
		params: params, // 关键：把 query 参数放到这里
	});
};
