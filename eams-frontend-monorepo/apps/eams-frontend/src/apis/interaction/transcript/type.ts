/**
 * 成绩单模块 - 类型定义
 */

/** 考核项列表查询参数 */
export interface GradeListQuery {
	/** 考核项名称（模糊搜索） */
	title?: string;
	/** 发布者名称（模糊搜索） */
	creatorName?: string;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}

/** 考核项保存 DTO（新增/修改） */
export interface GradeSaveDTO {
	/** 考核项ID，新增不传，修改必传 */
	id?: number;
	/** 考核项名称 */
	title: string;
	/** 考核项说明 */
	info: string;
}

/** 考核项删除 DTO */
export interface GradeDeleteDTO {
	/** 考核项ID 数组 */
	ids: number[];
}

/** 成绩记录保存 DTO */
export interface GradeRecordSaveDTO {
	/** 记录ID，新增不传，修改必传 */
	id?: number;
	/** 考核项ID */
	gradeId: number;
	/** 学生ID */
	studentId: number;
	/** 分数 */
	score: number;
}

/** 成绩记录删除 DTO */
export interface GradeRecordDeleteDTO {
	/** 记录ID */
	id?: number;
}

/** 考核项视图对象（列表响应） */
export interface GradeVO {
	/** 考核项ID */
	id: number;
	/** 考核项名称 */
	title: string;
	/** 考核项说明 */
	info: string;
	/** 创建人ID */
	creator: number;
	/** 创建人姓名 */
	creatorName: string;
	/** 添加时间 */
	addTime: string;
}

/** 成绩记录视图对象 */
export interface GradeRecordVO {
	/** 记录ID */
	id: number;
	/** 考核项ID */
	gradeId: number;
	/** 学生ID */
	studentId: number;
	/** 学生姓名 */
	studentName: string;
	/** 分数 */
	score: number;
	/** 创建人 */
	creator: number;
	/** 添加时间 */
	addTime: string;
}

/** 成绩记录列表查询参数 */
export interface GradeRecordListQuery {
	/** 考核项ID */
	gradeId?: number;
	/** 学生ID */
	studentId?: number;
	/** 分数 */
	score?: number;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}
