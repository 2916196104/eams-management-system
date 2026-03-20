/**
 * 公用数据接口相关类型在这里声明
 */

/**
 * 字典项
 */
export interface DictItem {
	/** 唯一标识 */
	id: string;
	/** 显示文字 */
	label: string;
	/** 字典编码 */
	code?: string;
}

/**
 * 字典
 */
export interface Dict {
	/** 唯一标识 */
	id: string;
	/** 字典名称 */
	name: string;
	/** 类型编码 */
	code: string;
	/** 字典项 */
	items: Array<DictItem>;
}
