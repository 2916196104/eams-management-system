/**
 * CuiSelectDict 组件类型定义
 */

/**
 * 字典选择框组件 Props
 */
export interface CuiSelectDictProps {
	/** 选中的值 */
	modelValue: any;
	/** 字典代码 */
	dictCode: string;
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
 * 字典选择框事件
 */
export interface CuiSelectDictEmits {
	/** 选中值更新 */
	"update:modelValue": [value: any];
	/** 值变化事件 */
	change: [value: any];
}

/**
 * 字典选项
 */
export interface CuiSelectDictOption {
	/** 选项标签 */
	label: string;
	/** 选项值 */
	value: any;
}
