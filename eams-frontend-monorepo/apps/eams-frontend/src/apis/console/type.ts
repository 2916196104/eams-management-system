/**
 * 面板数据对象
 */
export interface StatisticsDTO {
	/**
	 * 本月报名数
	 */
	monthEnrollments?: number;
	/**
	 * 待处理事项数量
	 */
	pendingTasks?: number;
	/**
	 * 今日出勤率
	 */
	todayAttendanceRate?: number;
	/**
	 * 班级总数
	 */
	totalClasses?: number;
	/**
	 * 课程总数
	 */
	totalCourses?: number;
	/**
	 * 学生总数
	 */
	totalStudents?: number;
	/**
	 * 教师总数
	 */
	totalTeachers?: number;
	/**
	 * 允许其他字符串
	 */
	[property: string]: any;
}
