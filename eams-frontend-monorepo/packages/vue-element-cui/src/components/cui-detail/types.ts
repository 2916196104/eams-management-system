/**
 * CuiDetail 组件类型定义
 */

/**
 * 详情字段配置
 */
export interface CuiDetailField {
	/** 字段标签 */
	label: string;
	/** 字段属性名 */
	prop: string;
	/** 字段宽度 */
	width?: string;
	/** 自定义渲染函数 */
	render?: (row: any) => any;
}

/**
 * 详情组件 Props
 */
export interface CuiDetailProps {
	/** 详情字段配置 */
	fields: CuiDetailField[];
	/** 详情数据 */
	data: Record<string, any>;
	/** 标签宽度 */
	labelWidth?: string;
	/** 列数 */
	columns?: number;
}
