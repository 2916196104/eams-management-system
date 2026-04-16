/**
 * CuiSelectEnum 组件类型定义
 */

/**
 * 选择框选项
 */
export interface CuiSelectEnumOption {
	/** 选项标签 */
	label: string;
	/** 选项值 */
	value: any;
}

/**
 * 选择框组件 Props
 */
export interface CuiSelectEnumProps {
	/** 选中的值 */
	modelValue: any;
	/** 枚举代码 */
	enumCode: string;
	/** 占位符 */
	placeholder?: string;
	/** 是否禁用 */
	disabled?: boolean;
	/** 是否可清空 */
	clearable?: boolean;
	/** 是否可搜索 */
	filterable?: boolean;
}

/**
 * 选择框事件
 */
export interface CuiSelectEnumEmits {
	/** 选中值更新 */
	"update:modelValue": [value: any];
	/** 值变化事件 */
	change: [value: any];
}
