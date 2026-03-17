// CuiSearch 组件类型定义

/**
 * 搜索字段配置
 */
export interface CuiSearchField {
	/** 字段属性名（对应数据对象的 key） */
	prop: string;
	/** 字段标签 */
	label: string;
	/** 字段类型 */
	type: "input" | "select" | "date" | "daterange";
	/** 占位符文本 */
	placeholder?: string;
	/** 选项列表（用于 select 类型） */
	options?: Array<{ label: string; value: any }>;
	/** 是否为高级搜索字段 */
	advanced?: boolean;
}

/**
 * 搜索组件 Props
 */
export interface CuiSearchProps {
	/** 搜索字段配置 */
	fields: CuiSearchField[];
	/** 表单值（支持 v-model） */
	modelValue: Record<string, any>;
	/** 是否内联布局 */
	inline?: boolean;
	/** 是否可折叠高级搜索 */
	collapsible?: boolean;
}
