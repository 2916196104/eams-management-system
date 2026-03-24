/**
 * 学员请假查询参数
 */
export interface StudentLeaveQueryDTO {
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
	/** 学生姓名/电话 */
	nameOrPhone?: string;
	/** 教师 ID */
	teacherId?: number;
	/** 开始时间 */
	startDate?: string;
	/** 结束时间 */
	endDate?: string;
}

/**
 * 学员请假数据项
 */
export interface StudentLeaveItemDTO {
	/** 请假表 ID */
	id?: number;
	/** 学员姓名 */
	studentName?: string;
	/** 电话 */
	mobile?: string;
	/** 请假课次（包含上课日期时间） */
	courseInfo?: string;
	/** 任课老师（可能多位） */
	teacherNames?: string;
	/** 请假原因 */
	reason?: string;
	/** 请假时间 */
	addTime?: string;
	/** 请假状态 */
	state?: string;
	/** 允许其他字段 */
	[property: string]: any;
}
