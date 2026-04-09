// 定义 SaveTrialCard 接口类型
export interface TrialCard {
	courseId?: number; // 所属课程ID，可选
	pageIndex?: number; // 查询页码，可选
	pageSize?: number; // 每页条数，可选
	state?: string; // 试听卡状态，可选
	title?: string; // 试听卡名称，可选
}

// type.ts 或对应类型文件中
export interface TrialCardDetail {
	id: number; // 必需，试听卡ID
}

//// type.ts
export interface TrialCardRecord {
	pageIndex?: number; // 查询页码
	pageSize?: number; // 查询条数
	studentId?: number; // 学生ID
	trialId?: number; // 试听卡ID
}

// type.ts
export interface SaveCard {
	courseId: number; // 所属课程ID，必需
	endDate?: string; // 发行结束日期，格式：yyyy-MM-dd，可选
	id: number; // 试听卡ID，必需
	isActive?: boolean; // 是否启用，可选，默认 true
	lessonCount: number; // 包含课时数，必需
	name: string; // 试听卡名称，必需
	totalIssue: number; // 发行数量，必需
	validDays: number; // 有效天数，必需
}
// type.ts
export interface deleteCard {
	value?: number[]; // 要删除的试听卡ID列表，必需
	mediaType?: {
		present?: boolean; // 是否包含媒体类型信息，可选，默认 false
	};
}
