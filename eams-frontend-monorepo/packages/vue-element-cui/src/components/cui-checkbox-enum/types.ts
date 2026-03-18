/**
 * CuiCheckboxEnum 组件类型定义
 */

/**
 * 复选框选项
 */
export interface CuiCheckboxEnumOption {
	/** 选项标签 */
	label: string;
	/** 选项值 */
	value: any;
}

/**
 * 复选框组件 Props
 */
export interface CuiCheckboxEnumProps {
	/** 选中的值数组 */
	modelValue: any[];
	/** 枚举代码 */
	enumCode: string;
	/** 是否禁用 */
	disabled?: boolean;
}

/**
 * 复选框事件
 */
export interface CuiCheckboxEnumEmits {
	/** 选中值更新 */
	"update:modelValue": [value: any[]];
	/** 值变化事件 */
	change: [value: any[]];
}
