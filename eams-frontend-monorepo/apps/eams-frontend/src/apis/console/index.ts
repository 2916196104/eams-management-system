import { useHttp } from "@/plugins/http";
import type { StatisticsDTO } from "./type";

const http = useHttp();
const currBaseUrl = "/console";

/**
 * 获取统计面板数据
 */
export const getStatistics = async () => {
	const res = await http.get<StatisticsDTO>(currBaseUrl + "/statistics");
	return res;
};
