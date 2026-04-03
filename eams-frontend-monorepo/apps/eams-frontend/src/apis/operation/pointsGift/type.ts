// type.ts
export interface GiftList {
	/**
	 * 礼品名称
	 */
	name?: string;

	/**
	 * 查询页码
	 */
	pageIndex?: number;

	/**
	 * 查询条数
	 */
	pageSize?: number;

	/**
	 * 状态(是否可以兑换)
	 */
	state?: number;
}
export interface SaveGiftParams {
	categoryId?: number; // 分类id，可选
	content?: string; // 礼品说明，可选
	cover?: string; // 图片，可选
	credit?: number; // 兑换积分，必填
	materialId?: string; // 物料id，可选
	name?: string; // 礼品名称，必填
}
export interface UseOrbanGiftParams {
	name?: string[]; // 可选，字符串数组
}
export interface GetGiftDetailParams {
	id: string; // 必需，礼品ID
}
export interface DeleteGiftParams {
	name?: string[]; // 可选，字符串数组
}
