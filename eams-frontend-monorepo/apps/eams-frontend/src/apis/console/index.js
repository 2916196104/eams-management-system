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
/**
 * 获取课表详细信息 - J5
 */
export const getCourseDetailApi = (id) => {
	return http.get(`${currBaseUrlJ5}/detail/${id}`);
};
/**
 * 删除课次 - J5
 * @param ids 课程安排ID数组
 */
export const deleteCoursesApi = (ids) => {
	return http.delete(`${currBaseUrlJ5}/delete-courses`, {
		data: { ids },
	});
};
/**
 * 停止/恢复课次 - J5
 * @param courseIds 课次ID列表
 * @param isResume "stop" 停止课程 | "resume" 恢复课程
 */
export const putCourseStatusApi = (courseIds, isResume) => {
	return http.put(`${currBaseUrlJ5}/resume`, { courseIds, isResume });
};
