/**
 * CuiRadioEnum 组件类型定义
 */

/**
 * 单选框选项
 */
export interface CuiRadioEnumOption {
	/** 选项标签 */
	label: string;
	/** 选项值 */
	value: any;
}

/**
 * 单选框组件 Props
 */
export interface CuiRadioEnumProps {
	/** 选中的值 */
	modelValue: any;
	/** 枚举代码 */
	enumCode: string;
	/** 是否禁用 */
	disabled?: boolean;
}

/**
 * 单选框事件
 */
export interface CuiRadioEnumEmits {
	/** 选中值更新 */
	"update:modelValue": [value: any];
	/** 值变化事件 */
	change: [value: any];
}
