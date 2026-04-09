export interface RedemptionApplicationList extends Record<string, any> {
	endDate?: string;
	giftName?: string;
	pageIndex?: number;
	pageNum?: number;
	pageSize?: number;
	startDate?: string;
	verifyState?: number;
	id?: number | string;
	studentName?: string;
	phoneNumber?: string;
	school?: string;
	gift?: string;
	quantity?: number;
	points?: number;
	applyTime?: string;
	createTime?: string;
	auditStatus?: string;
	auditor?: string;
	auditRemark?: string;
	rows?: RedemptionApplicationList[];
	total?: number;
}

export interface AuditParams {
	auditResult: number;
	id: number;
	remark?: string;
}
