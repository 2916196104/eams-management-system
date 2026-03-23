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
	/** 顾问 ID */
	advisorId?: string;
	/** 姓名 */
	name?: string;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
	/** 电话 */
	phone?: string;
	/** 状态 */
	status?: string;
	/** 学员 ID */
	studentId?: string;
	/** 分校区 ID */
	campusId?: string;
	/** 课程 ID */
	courseId?: string;
}

/**
 * 课时汇总数据项
 */
export interface ClassSummaryItemDTO {
	/** 已完成数量 */
	completeCount?: number;
	/** 课程名称 */
	courseName?: string;
	/** 过期日期 */
	expireDate?: string;
	/** 优先级 */
	priority?: number;
	/** 剩余金额 */
	remainingAmount?: number;
	/** 剩余数量 */
	remainingCount?: number;
	/** 科目名称 */
	subjectName?: string;
	/** 总数量 */
	totalCount?: number;
	/** 单价 */
	unitPrice?: number;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 报名记录查询参数
 */
export interface SignupRecordQueryDTO {
	/** 学员姓名 */
	studentName?: string;
	/** 开始日期 */
	startDate?: string;
	/** 结束日期 */
	endDate?: string;
	/** 课程 */
	course?: string;
	/** 经办人 */
	operator?: string;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}

/**
 * 报名记录数据项
 */
export interface SignupRecordItemDTO {
	/** 报名日期 */
	signupDate?: string;
	/** 学员 */
	studentName?: string;
	/** 课程 */
	courseName?: string;
	/** 科目 */
	subjectName?: string;
	/** 经办人 */
	operatorName?: string;
	/** 确认报名 */
	confirmSignup?: string;
	/** 单据 */
	receiptNo?: string;
	/** 总金额 */
	totalAmount?: number;
	/** 实付金额 */
	paidAmount?: number;
	/** 欠费 */
	oweAmount?: number;
	/** 升级日期 */
	upgradeDate?: string;
	/** 有效期至 */
	validUntil?: string;
	/** 审核状态 */
	auditStatus?: string;
	/** 单据状态 */
	receiptStatus?: string;
	/** 退款状态 */
	refundStatus?: string;
	/** 退费说明 */
	refundRemark?: string;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 批量报名请求参数
 */
export interface BatchSignupRequest {
	/** 报名记录 ID 列表 */
	ids: string[];
}

/**
 * 批量删除请求参数
 */
export interface BatchDeleteRequest {
	/** 报名记录 ID 列表 */
	ids: string[];
}

/**
 * 导出报名记录请求参数
 */
export interface ExportSignupRecordRequest {
	/** 学员姓名 */
	studentName?: string;
	/** 开始日期 */
	startDate?: string;
	/** 结束日期 */
	endDate?: string;
	/** 课程 */
	course?: string;
	/** 经办人 */
	operator?: string;
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
	/** 学员姓名 */
	studentName?: string;
	/** 跟进阶段 */
	stage?: string;
	/** 跟进人 */
	follower?: string;
	/** 开始日期 */
	startTime?: string;
	/** 结束日期 */
	endTime?: string;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}

/**
 * 跟进记录数据项
 */
export interface FollowRecordItemDTO {
	/** 跟进时间 */
	followTime?: string;
	/** 跟进人 */
	follower?: string;
	/** 客户 */
	customer?: string;
	/** 阶段 */
	stage?: string;
	/** 跟进方式 */
	followMethod?: string;
	/** 下次跟进 */
	nextFollow?: string;
	/** 记录时间 */
	recordTime?: string;
	/** 跟进内容 */
	followContent?: string;
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
