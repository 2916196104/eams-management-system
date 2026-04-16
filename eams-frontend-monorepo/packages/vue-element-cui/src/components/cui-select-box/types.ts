/**
 * CuiSelectBox 组件类型定义
 */

/**
 * 选择框选项
 */
export interface CuiSelectBoxOption {
	/** 选项 ID */
	id: string | number;
	/** 选项标签 */
	label: string;
	/** 其他自定义属性 */
	[key: string]: any;
}

/**
 * 选择框组件 Props
 */
export interface CuiSelectBoxProps {
	/** 选中的值 */
	modelValue: string | string[];
	/** 选择框类型标识 */
	type: string;
	/** 选择限制数量（0 表示不限制） */
	limit?: number;
	/** 是否禁用 */
	disabled?: boolean;
	/** 搜索条件 */
	condition?: Record<string, any>;
	/** 占位符 */
	placeholder?: string;
}

/**
 * 选择框事件
 */
export interface CuiSelectBoxEmits {
	/** 选中值更新 */
	"update:modelValue": [value: string | string[]];
	/** 选择提交 */
	submit: [value: string | string[]];
}
