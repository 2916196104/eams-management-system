import { useHttp } from "@/plugins/http";
const http = useHttp();
const currBaseUrl = "/console";
const currBaseUrlJ5 = "/j5/courseschedule";
/**
 * 获取统计面板数据-j1
 */
export const getStatisticsApi = () => {
	return http.get(currBaseUrl + "/statistics");
};

/**
 * 获取课表日历(条件)-j5
 */
export const getScheduleCalendarApi = (params = {}) => {
	return http.get(currBaseUrlJ5 + "/calendar", params);
};
