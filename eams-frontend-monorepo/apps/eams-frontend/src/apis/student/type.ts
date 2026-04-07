/**
 * 课程列表项
 */
export interface CourseItemDTO {
	/** 课程ID */
	id?: string;
	/** 课程名称 */
	name?: string;
	/** 课程编码 */
	code?: string;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 课时汇总查询参数
 */
export interface ClassSummaryQueryDTO {
	/** 年级 ID */
	gradeId?: number;
	/** 学员姓名 */
	name?: string;
	/** 手机号 */
	mobile?: string;
	/** 阶段 */
	stage?: string;
	/** 状态 */
	status?: string;
	/** 课程 ID */
	courseId?: number;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}

/**
 * 课时汇总数据项（LessonSummaryVO）
 */
export interface ClassSummaryItemDTO {
	/** 主键 ID */
	id?: number;
	/** 班级 ID */
	classId?: number;
	/** 学员 ID */
	studentId?: string;
	/** 学员姓名 */
	name?: string;
	/** 手机号 */
	mobile?: string;
	/** 课时 ID */
	lessonId?: number;
	/** 课时数 */
	lessonCount?: number;
	/** 递减课时数 */
	decLessonCount?: number;
	/** 教师 ID */
	teacherId?: number;
	/** 签到状态 */
	signState?: number;
	/** 签到时间 */
	signTime?: string;
	/** 签到类型 */
	signType?: number;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 报名记录查询参数
 */
export interface SignupRecordQueryDTO {
	/** 回调 ID */
	callBackId?: number;
	/** 变更类型 */
	changeType?: number;
	/** 课程名称 */
	courseName?: string;
	/** 报名结束时间 */
	endTime?: string;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
	/** 报名开始时间 */
	startTime?: string;
	/** 学生姓名 */
	studentName?: string;
	/** 经办人 */
	operatorName?: string;
}

/**
 * 报名记录数据项
 */
export interface SignupRecordItemDTO {
	/** 报名 ID */
	id?: number;
	/** 报名时间 */
	addTime?: string;
	/** 金额 */
	amount?: number;
	/** 已完成课时数 */
	countLessonComplete?: number;
	/** 总课时数 */
	countLessonTotal?: number;
	/** 课程名称 */
	courseName?: string;
	/** 经办人 */
	operatorName?: string;
	/** 剩余课次 */
	remainingLessons?: number;
	/** 学生姓名 */
	studentName?: string;
	/** 学生 ID */
	studentId?: string;
	/** 科目名称 */
	subjectName?: string;
	/** 审核状态 */
	verifyState?: number;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 批量报名请求参数
 */
export interface BatchSignupRequest {
	/** 报名记录 ID 列表 */
	ids: number[];
}

/**
 * 批量删除请求参数
 */
export interface BatchDeleteRequest {
	/** 报名记录 ID 列表 */
	ids: number[];
}

/**
 * 导出报名记录请求参数
 */
export interface ExportSignupRecordRequest {
	/** 学生姓名 */
	studentName?: string;
	/** 报名开始时间 */
	startTime?: string;
	/** 报名结束时间 */
	endTime?: string;
	/** 课程名称 */
	courseName?: string;
	/** 经办人 */
	operatorName?: string;
}

/**
 * 分校区列表项
 */
export interface CampusItemDTO {
	/** 分校区 ID */
	id?: string;
	/** 分校区名称 */
	name?: string;
	/** 分校区编码 */
	code?: string;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 跟进记录查询参数
 */
export interface FollowRecordQueryDTO {
	/** 跟进人 ID/姓名 */
	creator?: string;
	/** 结束日期 */
	endTime?: string;
	/** 学员姓名或电话（模糊查询） */
	keyword?: string;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
	/** 进展阶段 */
	stage?: number;
	/** 开始日期 */
	startTime?: string;
	/** 学生 ID */
	studentId?: number;
}

/**
 * 跟进记录数据项
 */
export interface FollowRecordItemDTO {
	/** 主键 ID */
	id?: number;
	/** 创建时间 */
	addTime?: string;
	/** 下次联系时间 */
	contactNextTime?: string;
	/** 联系电话 */
	contactPhone?: string;
	/** 联系时间 */
	contactTime?: string;
	/** 联系方式 (1:电话 2:微信 3:面谈 4:其他) */
	contactType?: number;
	/** 创建者/跟进人 ID */
	creator?: number;
	/** 跟进人姓名 */
	creatorName?: string;
	/** 跟进记录 */
	info?: string;
	/** 所属组织 ID */
	orgId?: number;
	/** 进展阶段 (1:潜在客户 2:意向客户 3:成交客户) */
	stage?: number;
	/** 学生 ID */
	studentId?: number;
	/** 学员姓名 */
	studentName?: string;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 跟进阶段列表项
 */
export interface FollowStageItemDTO {
	/** 阶段 ID */
	id?: string;
	/** 阶段名称 */
	name?: string;
	/** 允许其他字段 */
	[property: string]: any;
}
