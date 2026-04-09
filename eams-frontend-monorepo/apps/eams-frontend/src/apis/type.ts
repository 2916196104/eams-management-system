/**
 * 这里声明通用类型、接口、常量、枚举等等
 */

/**
 * 后端响应数据类型
 */
export { type JsonVO } from "./http";

/**
 * 分页数据模型
 */
export { type PageDTO, createPageDTO } from "@/components/mytable/type";

/**
 * 分页查询数据模型
 */
export interface PageQuery {
	/** 页码 */
	pageIndex: number;
	/** 每页数据条数 */
	pageSize: number;
}

/**
 * 下拉选项模型
 */
export interface SelectItem {
	/** 选项值 */
	value: string | number;
	/** 选项显示文本 */
	label: string;
}
