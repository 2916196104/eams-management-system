/**
 * 教评学模块 - 类型定义
 */

/** 教师点评列表查询参数 */
export interface CourseCommentListQuery {
	/** 评价内容（模糊匹配） */
	content?: string;
	/** 课次标题（模糊匹配，前端搜索用） */
	courseTitle?: string;
	/** 点评老师ID */
	creator?: number;
	/** 点评老师姓名（前端搜索用） */
	creatorName?: string;
	/** 学生ID */
	studentId?: number;
	/** 学生姓名（前端搜索用） */
	studentName?: string;
	/** 点评开始时间（yyyy-MM-dd HH:mm:ss） */
	addTimeStart?: string;
	/** 点评结束时间（yyyy-MM-dd HH:mm:ss） */
	addTimeEnd?: string;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}

/** 教师评价学生 - 列表视图对象 */
export interface CourseCommentVO {
	/** 序号 */
	serialNumber?: number;
	/** 学员姓名 */
	studentName: string;
	/** 课次标题 */
	courseTitle: string;
	/** 点评得分 */
	score: number;
	/** 点评内容 */
	content: string;
	/** 点评老师 */
	creatorName: string;
	/** 点评时间 */
	addTime: string;
}
