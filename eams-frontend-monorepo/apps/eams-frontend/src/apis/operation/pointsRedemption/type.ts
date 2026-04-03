export interface RedemptionApplicationList {
	endDate?: string; // 结束日期（格式：yyyy-MM-dd）
	giftName?: string; // 礼品名称（模糊搜索）
	pageIndex?: number; // 查询页码
	pageNum?: number; // 当前页码
	pageSize?: number; // 每页条数
	startDate?: string; // 开始日期（格式：yyyy-MM-dd）
	verifyState?: number; // 审核状态：1-待审核，2-通过，3-驳回
}
export interface AuditParams {
	/**
	 * 审核结果：2-通过，3-驳回 (必填)
	 */
	auditResult: number; // 2: 通过, 3: 驳回

	/**
	 * 兑换记录 ID (必填)
	 */
	id: number;

	/**
	 * 审核说明 (可选，驳回时建议填写)
	 */
	remark?: string;
}
