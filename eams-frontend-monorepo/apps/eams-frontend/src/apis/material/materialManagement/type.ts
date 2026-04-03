// d:\01项目\zero-one-eams2603\eams-frontend-monorepo\apps\eams-frontend\src\apis\material\materialManagement\type.ts

/**
 * 物料变动记录列表项
 */
export interface MaterialListItem {
	/**
	 * 申请员工ID
	 */
	applyStaffId?: number;

	/**
	 * 开始日期，格式：yyyy-MM-dd
	 */
	beginDate?: string;

	/**
	 * 变动类型 1入库 2出库 3积分商城出库
	 */
	changeType?: number;

	/**
	 * 结束日期，格式：yyyy-MM-dd
	 */
	endDate?: string;

	/**
	 * 查询页码
	 */
	pageIndex?: number;

	/**
	 * 查询条数
	 */
	pageSize?: number;

	/**
	 * 涉及学生ID
	 */
	studentId?: number;
}
export interface InboundAndOutbound {
	/**
	 * 变动数量
	 */
	amount: number;

	/**
	 * 变动类型 1入库 2出库 3积分商城出库
	 */
	changeType: number;

	/**
	 * 物料id
	 */
	materialId: number;

	/**
	 * 变动原因说明
	 */
	reason: string;
}
