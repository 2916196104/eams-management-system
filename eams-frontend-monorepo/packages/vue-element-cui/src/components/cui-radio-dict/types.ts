/**
 * CuiRadioDict 组件类型定义
 */

/**
 * 字典单选框选项
 */
export interface CuiRadioDictOption {
	/** 选项标签 */
	label: string;
	/** 选项值 */
	value: any;
}

/**
 * 字典单选框组件 Props
 */
export interface CuiRadioDictProps {
	/** 选中的值 */
	modelValue: any;
	/** 字典代码 */
	dictCode: string;
	/** 是否禁用 */
	disabled?: boolean;
}

/**
 * 字典单选框事件
 */
export interface CuiRadioDictEmits {
	/** 选中值更新 */
	"update:modelValue": [value: any];
	/** 值变化事件 */
	change: [value: any];
}
