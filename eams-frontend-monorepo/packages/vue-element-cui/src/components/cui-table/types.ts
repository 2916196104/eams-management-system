// CuiTable 组件类型定义
import type { TableColumnCtx } from "element-plus";

/**
 * 表格列配置
 */
export interface CuiTableColumn<T = any> {
	/** 列属性名（对应数据对象的 key） */
	prop?: string;
	/** 列标题 */
	label: string;
	/** 列宽度 */
	width?: string | number;
	/** 最小列宽度 */
	minWidth?: string | number;
	/** 是否可排序 */
	sortable?: boolean | "custom";
	/** 列是否固定 */
	fixed?: boolean | "left" | "right";
	/** 对齐方式 */
	align?: "left" | "center" | "right";
	/** 格式化函数（用于简单的文本格式化） */
	formatter?: (row: T, column: any, cellValue: any, index: number) => any;
	/** 自定义插槽名称（用于复杂的自定义渲染） */
	slot?: string;
}

/**
 * 表格组件 Props
 */
export interface CuiTableProps<T = any> {
	/** 表格数据 */
	data: T[];
	/** 列配置 */
	columns: CuiTableColumn<T>[];
	/** 是否显示加载状态 */
	loading?: boolean;
	/** 是否显示索引列 */
	showIndex?: boolean;
	/** 是否显示选择列 */
	showSelection?: boolean;
	/** 是否显示斑马纹 */
	stripe?: boolean;
	/** 是否显示边框 */
	border?: boolean;
	/** 表格高度 */
	height?: string | number;
	/** 表格最大高度 */
	maxHeight?: string | number;
}

/**
 * 排序变化事件参数
 */
export interface SortChangeEvent {
	/** 排序列的属性名 */
	prop: string;
	/** 排序顺序 */
	order: "ascending" | "descending" | null;
}

/**
 * 选择变化事件参数
 */
export type SelectionChangeEvent<T = any> = T[];
