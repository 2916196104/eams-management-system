/**
 * 公告管理模块 - 类型定义
 */

/** 公告列表查询参数 */
export interface NoticeListQuery {
	/** 公告标题（模糊搜索） */
	title?: string;
	/** 公告类型 */
	type?: string;
	/** 发布人 */
	publisher?: string;
	/** 查询页码 */
	pageIndex?: number;
	/** 查询条数 */
	pageSize?: number;
}

/** 公告保存 DTO */
export interface NoticeSaveDTO {
	/** 公告ID，新增不传，修改必传 */
	id?: string;
	/** 公告标题 */
	title: string;
	/** 公告类型 */
	type?: string;
	/** 文章编码（用于文章引用） */
	articleCode?: string;
	/** 图片URL */
	image?: string;
	/** 公告内容 */
	content?: string;
}

/** 公告视图对象（列表响应） */
export interface NoticeVO {
	/** 公告ID */
	id: string;
	/** 图片URL */
	image?: string;
	/** 公告标题 */
	title: string;
	/** 公告类型（通知/公告/紧急等） */
	type: string;
	/** 公告内容 */
	content?: string;
	/** 文章编码 */
	articleCode?: string;
	/** 发布人 */
	publisher: string;
	/** 状态：1=启用，0=禁用 */
	status: number;
	/** 添加时间 */
	addTime: string;
}
