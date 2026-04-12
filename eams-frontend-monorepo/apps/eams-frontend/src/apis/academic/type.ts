/**
 * 学员请假查询参数
 */
export interface StudentLeaveQueryDTO {
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
	/** 学员姓名/电话 */
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
	/** 请假课程 */
	courseInfo?: string;
	/** 任课老师 */
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
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
	/** 班级 ID */
	classId?: number;
	/** 课程 ID */
	courseId?: number;
	/** 开始日期 */
	startDate?: string;
	/** 结束日期 */
	endDate?: string;
	/** 教师 ID */
	teacherId?: number;
	/** 教室 ID */
	roomId?: number;
	/** 课次状态 */
	state?: number;
	/** 是否试听 */
	onTrial?: number;
	/** 周期（兼容旧字段） */
	cycle?: number;
	/** 班级名称（兼容旧字段） */
	className?: string;
	/** 课程名字（兼容旧字段） */
	courseName?: string;
	/** 老师姓名（兼容旧字段） */
	teacherName?: string;
	/** 学生姓名（兼容旧字段） */
	studentName?: string;
}

/**
 * 课程表数据项（课次列表 VO）
 */
export interface CourseListVO {
	/** 课表 ID */
	id?: number;
	/** 上课日期 */
	date?: string;
	/** 开始时间 */
	startTime?: {
		hour?: number;
		minute?: number;
		second?: number;
		nano?: number;
	};
	/** 结束时间 */
	endTime?: {
		hour?: number;
		minute?: number;
		second?: number;
		nano?: number;
	};
	/** 课程 ID */
	courseId?: number;
	/** 课程名称 */
	courseName?: string;
	/** 班级 ID */
	classId?: number;
	/** 班级名称 */
	className?: string;
	/** 教师名称 */
	teacherName?: string;
	/** 序号 */
	sn?: number;
	/** 应到人数 */
	shouldCount?: number;
	/** 实到人数 */
	realCount?: number;
	/** 状态 */
	state?: number;
	/** 标题 */
	title?: string;
	/** 上课时间（文本格式，兼容旧字段） */
	lessonTimeText?: string;
	/** 老师 ID 列表 */
	teacherIds?: string;
	/** 老师名称列表 */
	teacherNames?: string;
	/** 课程类型 */
	courseType?: string;
	/** 助教 ID 列表 */
	assistantIds?: string;
	/** 助教名称列表 */
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
	/** 课程状态 */
	lessonStatus2?: string;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 课表日历查询参数
 */
export interface LessonCalendarQueryDTO {
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
	/** 班级 ID */
	classId?: number;
	/** 课程 ID */
	courseId?: number;
	/** 开始日期 */
	startDate?: string;
	/** 结束日期 */
	endDate?: string;
	/** 教师 ID */
	teacherId?: number;
	/** 教室 ID */
	roomId?: number;
	/** 课次状态 */
	state?: number;
	/** 是否试听 */
	onTrial?: number;
	/** 班级名称（兼容旧字段） */
	className?: string;
	/** 课程名称（兼容旧字段） */
	courseName?: string;
	/** 老师名称（兼容旧字段） */
	teacherName?: string;
	/** 科目名称（兼容旧字段） */
	subjectName?: string;
	/** 教室名称（兼容旧字段） */
	classroomName?: string;
	/** 视图类型（兼容旧字段） */
	viewType?: number;
	/** 周期（兼容旧字段） */
	period?: string;
	/** 用户唯一 ID（兼容旧字段） */
	userId?: number;
}

/**
 * 课表日历数据项
 */
export interface LessonCalendarVO {
	/** 课表 ID */
	id?: number;
	/** 标题 */
	title?: string;
	/** 课程名称 */
	courseName?: string;
	/** 老师名称 */
	teacherName?: string;
	/** 学生 ID 列表 */
	studentIdList?: string[];
	/** 学生名称列表 */
	studentNameList?: string[];
	/** 班级类型 */
	classType?: string;
	/** 上课日期 */
	date?: string;
	/** 开始时间 */
	startTime?:
		| string
		| {
				hour?: number;
				minute?: number;
				second?: number;
				nano?: number;
		  };
	/** 结束时间 */
	endTime?:
		| string
		| {
				hour?: number;
				minute?: number;
				second?: number;
				nano?: number;
		  };
	/** 班级名称 */
	className?: string;
	/** 教室名称 */
	classroomName?: string;
	/** 课程状态 */
	courseStatus?: string;
	/** 课表日历类型 */
	courseCalendarType?: boolean;
	/** 兼容旧字段 */
	studentName?: string;
	Date?: string;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 课次详情数据项
 */
export interface CourseDetailVO {
	/** ID */
	id?: number;
	/** 标题 */
	title?: string;
	/** 课程名称 */
	courseName?: string;
	/** 班级名称 */
	className?: string;
	/** 教师名称 */
	teacherName?: string;
	/** 上课日期 */
	date?: string;
	/** 开始时间 */
	startTime?:
		| string
		| {
				hour?: number;
				minute?: number;
				second?: number;
				nano?: number;
		  };
	/** 结束时间 */
	endTime?:
		| string
		| {
				hour?: number;
				minute?: number;
				second?: number;
				nano?: number;
		  };
	/** 序号 */
	sn?: number;
	/** 应到人数 */
	shouldCount?: number;
	/** 实到人数 */
	realCount?: number;
	/** 状态 */
	state?: number;
	/** 教室名称 */
	roomName?: string;
	/** 备注 */
	remark?: string;
	/** 兼容旧字段 */
	courseNo?: string;
	classNo?: string;
	courseType?: string;
	lessonTimeText?: string;
	classroomName?: string;
	classroomNo?: string;
	teacherNo?: string;
	assistantName?: string;
	assistantNo?: string;
	attendInfo?: string;
	decLessonCount?: number;
	canReserve?: string;
	status?: string;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 课后点评查询参数
 */
export interface EvaluationQueryDTO {
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
	/** 课程 ID（课次 ID） */
	lessonId?: number;
	/** 是否仅查询已评价的记录 */
	onlyEvaluate?: boolean;
}

/**
 * 课后点评数据项
 */
export interface EvaluationVO {
	/** 点评记录 ID */
	id?: number;
	/** 学员 ID */
	studentId?: number;
	/** 学员姓名 */
	studentName?: string;
	/** 学员手机号（脱敏） */
	studentPhone?: string;
	/** 点评老师 ID */
	teacherId?: number;
	/** 点评老师姓名 */
	teacherName?: string;
	/** 课次 ID */
	lessonId?: number;
	/** 点评得分 */
	commentScore?: number;
	/** 点评内容 */
	commentContent?: string;
	/** 点评时间 */
	commentTime?: string;
	/** 兼容旧字段 */
	courseTitle?: string;
	overallScore?: number;
	atmosphereScore?: number;
	attitudeScore?: number;
	effectScore?: number;
	content?: string;
	/** 允许其他字段 */
	[property: string]: any;
}

/**
 * 保存点评请求参数
 */
export interface EvaluationSaveDTO {
	/** Id（是每一条信息的id，不是学生id） */
	id?: number;
	/** 老师 id */
	teacherId?: number;
	/** 老师姓名 */
	teacherName?: string;
	/** 学生 id */
	studentId?: number;
	/** 学生姓名 */
	studentName?: string;
	/** 课次 id */
	lessonId?: number;
	/** 课程标题 */
	courseTitle?: string;
	/** 综合评分 */
	overallScore?: number;
	/** 课堂气氛 */
	atmosphereScore?: number;
	/** 授课态度 */
	attitudeScore?: number;
	/** 教学效果 */
	effectScore?: number;
	/** 评语 */
	content?: string;
}

/**
 * 保存点评响应
 */
export interface EvaluationSaveResponseDTO {
	code?: number;
	message?: string;
	data?: number;
}

/**
 * 删除课次响应
 */
export interface DeleteCoursesResponseDTO {
	code?: number;
	message?: string;
	data?: string;
}

/**
 * 停/复课响应
 */
export interface ResumeCoursesResponseDTO {
	code?: number;
	message?: string;
	data?: number;
}

/**
 * 停/复课请求参数
 */
export interface CoursePauseResumeDTO {
	/** 课次 ID 列表（必需） */
	lessonIds: number[];
	/** 是否复课（必需）true=复课 false=停课 */
	isResume: boolean;
}

/**
 * 批量修改课次请求参数
 */
export interface BatchUpdateCoursesDTO {
	/** 课程 ID 列表（必需） */
	updateIds: number[];
	/** 增减天数（可选） */
	changeDays?: number;
	/** 主讲老师 id 集合（可选） */
	teacherIds?: number[];
	/** 助教老师 id 集合（可选） */
	assistantIds?: number[];
	/** 教室 ID（可选） */
	roomId?: number;
	/** 开始时间对象（可选） */
	startTime?: {
		hour: number;
		minute: number;
		second: number;
		nano: number;
	};
	/** 结束时间对象（可选） */
	endTime?: {
		hour: number;
		minute: number;
		second: number;
		nano: number;
	};
}

/**
 * 批量修改课次响应
 */
export interface BatchUpdateCoursesResponseDTO {
	code?: number;
	message?: string;
	data?: string;
}

/**
 * 修改课次请求参数
 */
export interface UpdateCourseDTO {
	/** 课程 ID */
	id: number;
	/** 课程标题 */
	title?: string;
	/** 班级名 */
	className?: string;
	/** 班级 ID */
	classId?: number;
	/** 教师姓名 */
	teacherName?: string;
	/** 教师 ID */
	teacherId?: number;
	/** 助教姓名 */
	assistantName?: string;
	/** 助教 ID */
	assistantId?: number;
	/** 开始时间 */
	startDate?: string;
	/** 结束时间 */
	endDate?: string;
	/** 教室 ID */
	roomId?: number;
	/** 教室名称 */
	roomName?: string;
	/** 消课基数 */
	decCount?: number;
	/** 是否开启预约 */
	enableReserve?: boolean;
	/** 是否批量同步后续相同时间课程 */
	batchSyncTime?: boolean;
	/** 是否检查排课冲突 */
	checkConflict?: boolean;
}

/**
 * 修改课次响应
 */
export interface UpdateCourseResponseDTO {
	code?: number;
	message?: string;
	data?: string;
}

/**
 * 重复排课的单个周期配置
 */
export interface RepeatScheduleSettingDTO {
	/** 课程表编号 */
	scheduleId?: string;
	/** 星期几上课 */
	weeks: string;
	/** 上课开始时间 */
	startTime: string;
	/** 上课结束时间 */
	endTime: string;
	/** 教室编号 */
	roomId?: number;
}

/**
 * 重复排课请求参数
 */
export interface RepeatScheduleRequestDTO {
	/** 课程编号 */
	id?: string;
	/** 班级编号 */
	classId: number;
	/** 班级名称 */
	className: string;
	/** 老师 ID */
	teacherId: number;
	/** 上课老师 */
	teacherName: string;
	/** 助教 ID */
	assistantId?: number;
	/** 助教老师 */
	assistantName?: string;
	/** 课程开始时间 */
	startTime: string;
	/** 课程结束时间 */
	endTime: string;
	/** 学员扣课次数 */
	descLessonCount?: number;
	/** 排课次数 */
	times?: number;
	/** 排除节日 */
	excludeHoliday?: string;
	/** 课程状态 */
	status?: string;
	/** 创建人 ID（可选） */
	creator?: number;
	/** 创建时间（可选） */
	addTime?: string;
	/** 更新时间（可选） */
	editTime?: string;
	/** 更新人 ID（可选） */
	editor?: number;
	/** 周期配置 */
	lessonScheduleSettingDtos: RepeatScheduleSettingDTO[];
}

/**
 * 重复排课响应
 */
export interface RepeatScheduleResponseDTO {
	code?: number;
	message?: string;
	data?: string;
}

/**
 * 预约课程开关请求参数
 */
export interface SwitchScheduleRequestDTO {
	/** 课程编号 */
	id?: string;
	/** 课程预约开关 */
	status?: string;
	/** 更新时间（兼容 API 文档） */
	editTime?: string;
	/** 更新人 ID（兼容 API 文档） */
	editor?: number;
}

/**
 * 预约课程开关响应
 */
export interface SwitchScheduleResponseDTO {
	code?: number;
	message?: string;
	data?: string;
}

/**
 * 自由排课请求参数
 */
export interface FreeScheduleRequestDTO {
	/** 课程编号 */
	id?: string;
	/** 班级编号 */
	classId: number;
	/** 班级名称 */
	className: string;
	/** 老师 ID */
	teacherId: number;
	/** 上课老师 */
	teacherName: string;
	/** 助教 ID */
	assistantId?: number;
	/** 助教老师 */
	assistantName?: string;
	/** 课程开始时间 */
	startTime: string;
	/** 课程结束时间 */
	endTime: string;
	/** 学员扣课次数 */
	descLessonCount?: number;
	/** 排课次数 */
	times?: number;
	/** 排除节日 */
	excludeHoliday?: string;
	/** 课程状态 */
	status?: string;
	/** 创建人 ID（可选） */
	creator?: number;
	/** 创建时间（可选） */
	addTime?: string;
	/** 更新时间（可选） */
	editTime?: string;
	/** 更新人 ID（可选） */
	editor?: number;
	/** 周期配置 */
	lessonScheduleSettingDtos: RepeatScheduleSettingDTO[];
}

/**
 * 自由排课响应
 */
export interface FreeScheduleResponseDTO {
	code?: number;
	message?: string;
	data?: string;
}
