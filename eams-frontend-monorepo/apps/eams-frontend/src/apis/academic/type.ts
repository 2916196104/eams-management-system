/**
 * 学员请假查询参数
 */
export interface StudentLeaveQueryDTO {
	/** 学员姓名 */
	studentName?: string;
	/** 任课老师 */
	teacherName?: string;
	/** 开始日期 */
	startDate?: string;
	/** 结束日期 */
	endDate?: string;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}

/**
 * 学员请假数据项
 */
export interface StudentLeaveItemDTO {
	/** 学员姓名 */
	studentName?: string;
	/** 电话 */
	phone?: string;
	/** 请假课次 */
	leaveLessons?: string;
	/** 任课老师 */
	teacherName?: string;
	/** 请假原因 */
	leaveReason?: string;
	/** 请假时间 */
	leaveTime?: string;
	/** 请假照片 */
	leavePhotos?: string[];
	/** 状态 */
	status?: string;
	/** 允许其他字段 */
	[property: string]: any;
}
