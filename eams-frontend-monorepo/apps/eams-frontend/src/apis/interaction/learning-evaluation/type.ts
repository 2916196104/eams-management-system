/**
 * 学评教模块 - 类型定义
 */

/** 学评教列表查询参数 */
export interface LearningEvaluationQuery {
	/** 课次标题（模糊搜索，仅 Mock 使用） */
	lessonTitle?: string;
	/** 评价开始时间（格式：yyyy-MM-dd HH:mm:ss） */
	addTimeStart?: string;
	/** 评价结束时间（格式：yyyy-MM-dd HH:mm:ss） */
	addTimeEnd?: string;
	/** 老师ID */
	teacherId?: number;
	/** 学生ID */
	studentId?: number;
	/** 课次ID */
	lessonId?: number;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}

/** 学评教视图对象（列表响应） */
export interface TeachEvaluationVO {
	/** 序号 */
	serialNumber: number;
	/** 学员姓名 */
	studentName: string;
	/** 老师姓名 */
	teacherName: string;
	/** 课次标题 */
	lessonTitle: string;
	/** 综合评分 */
	overallScore: number;
	/** 课堂气氛评分 */
	atmosphereScore: number;
	/** 授课态度评分 */
	attitudeScore: number;
	/** 教学效果评分 */
	effectScore: number;
	/** 评价内容 */
	content: string;
	/** 评价时间 */
	addTime: string;
}
