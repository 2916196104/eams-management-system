/**
 * 课后作业模块 - 类型定义
 */

/** 作业列表查询参数 */
export interface HomeworkListQuery {
	/** 标题关键词（模糊搜索） */
	title?: string;
	/** 班级名称（模糊搜索） */
	className?: string;
	/** 教师名称（模糊搜索） */
	teacherName?: string;
	/** 班级ID */
	classId?: number;
	/** 教师ID */
	teacherId?: number;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}

/** 作业保存 DTO */
export interface HomeworkSaveDTO {
	/** 作业ID，新增不传，修改必传 */
	id?: number;
	/** 作业标题 */
	title: string;
	/** 作业内容 */
	content: string;
	/** 班级ID */
	classId: number;
}

/** 作业删除 DTO */
export interface HomeworkDeleteDTO {
	/** 作业ID */
	id?: number;
	name?: string;
}

/** 点评作业 DTO */
export interface HomeworkCommentDTO {
	/** 提交记录ID */
	id?: number;
	/** 点评内容 */
	name?: string;
}

/** 作业视图对象（列表响应） */
export interface HomeworkVO {
	/** 作业ID */
	id: number;
	/** 标题 */
	title: string;
	/** 内容 */
	content: string;
	/** 班级ID */
	classId: number;
	/** 班级名称 */
	className: string;
	/** 教师姓名 */
	teacherName: string;
	/** 创建人ID（教师） */
	creator: number;
	/** 已提交人数 */
	completeCount: number;
	/** 当前学生是否已完成 */
	completed: boolean;
	/** 添加时间 */
	addTime: string;
	/** 提交记录列表（详情接口嵌套返回） */
	recordList?: HomeworkRecordVO[];
}

/** 作业提交记录视图对象 */
export interface HomeworkRecordVO {
	/** 提交记录ID */
	id: number;
	/** 所属作业ID */
	homeworkId: number;
	/** 学生ID */
	studentId: number;
	/** 学生姓名 */
	studentName: string;
	/** 提交内容 */
	content: string;
	/** 附件图片URL */
	images?: string;
	/** 评分 */
	score?: number | null;
	/** 点评内容 */
	comment?: string | null;
	/** 点评老师姓名 */
	commentTeacherName?: string | null;
	/** 点评时间 */
	commentTime?: string | null;
	/** 提交时间 */
	addTime: string;
}

/** 作业提交列表查询参数 */
export interface HomeworkRecordsQuery {
	/** 作业ID（必填） */
	homeworkId: number;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}
