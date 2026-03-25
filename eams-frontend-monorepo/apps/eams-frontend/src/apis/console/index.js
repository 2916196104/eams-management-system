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

// 教师/助教下拉菜单列表 -j5
export const getTeacherListApi = (params) => {
	return http.get(`/j5/courseplan/teachers`, params);
};

// 获取教室列表（条件+分页）-j4
export const getClassroomListApi = (params) => {
	return http.get(`/j4/classroom/list`, params);
};

// 获取控制台公告列表 - j6
export const getNoticeListApi = (data) => {
	return http.get("/j6/interact/Advertisement/list", data);
};

/**
 * 本月报名走势查询 - j7
 */
export const getMonthlyTrendApi = (params) => {
	return http.get("/j7-console/monthly-trend", {
		params,
	});
};

/**
 * 课程报名查询 top5 - j7
 */
export const getCourseTop5Api = (params) => {
	return http.get("/j7-console/course-registration", {
		params,
	});
};
