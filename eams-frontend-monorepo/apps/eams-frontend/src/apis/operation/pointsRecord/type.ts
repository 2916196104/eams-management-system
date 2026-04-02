export interface PointsRecordListItem {
	name?: string; // 学生名称
	pageIndex?: number; // 查询页码
	pageSize?: number; // 查询条数
	phone?: number; // 手机号
	reason?: string; // 变动原因
}
export interface AdjustPointsRecordRequest {
	name?: string; // 学生名称
	point?: number; // 变动积分
	content?: string; // 变动原因
}
