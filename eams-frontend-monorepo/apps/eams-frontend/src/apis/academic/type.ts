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

/**
 * 课程表查询参数
 */
export interface CourseListQueryDTO {
	/** 当前页码 */
	pageIndex?: number;
	/** 每页显示最大数据条数 */
	pageSize?: number;
	/** 周期 */
	cycle?: number;
	/** 班级名 */
	className?: string;
	/** 课程名字 */
	courseName?: string;
	/** 老师姓名 */
	teacherName?: string;
	/** 学生姓名 */
	studentName?: string;
}

/**
 * 课程表数据项
 */
export interface CourseListVO {
	/** 课表 ID */
	id?: number;
	/** 上课时间（展示文本） */
	lessonTimeText?: string;
	/** 课程 ID */
	courseId?: number;
	/** 课程名称 */
	courseName?: string;
	/** 班级 ID */
	classId?: number;
	/** 班级名称 */
	className?: string;
	/** 老师 ID 列表（逗号分隔） */
	teacherIds?: string;
	/** 老师名称列表（逗号分隔） */
	teacherNames?: string;
	/** 课程类型 */
	courseType?: string;
	/** 助教 ID 列表（逗号分隔） */
	assistantIds?: string;
	/** 助教名称列表（逗号分隔） */
	assistantNames?: string;
	/** 教室 ID */
	classroomId?: number;
	/** 教室名称 */
	classroomName?: string;
	/** 可预约状态 */
	canReserve?: string;
	/** 学生数 */
	studentCount?: number;
	/** 限制人数 */
	maxStudentCount?: number;
	/** 签到数 */
	checkInCount?: number;
	/** 到课率 */
	attendanceRate?: string;
	/** 消课基数 */
	decLessonCount?: number;
	/** 已消课数 */
	consumedCount?: number;
	/** 上课状态 */
	lessonStatus?: string;
	/** 允许其他字段 */
	[property: string]: any;
}
