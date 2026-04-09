// CuiForm 组件类型定义
import type { FormItemRule } from "element-plus";

/**
 * 表单字段类型
 */
export type CuiFormFieldType = "input" | "select" | "date" | "textarea" | "number";

/**
 * 选择框选项
 */
export interface CuiFormSelectOption {
	/** 选项标签 */
	label: string;
	/** 选项值 */
	value: any;
	/** 是否禁用 */
	disabled?: boolean;
}

/**
 * 表单字段配置
 */
export interface CuiFormField<T = any> {
	/** 字段属性名（对应数据对象的 key） */
	prop: keyof T & string;
	/** 字段标签 */
	label: string;
	/** 字段类型 */
	type: CuiFormFieldType;
	/** 占位符文本 */
	placeholder?: string;
	/** 是否必填 */
	required?: boolean;
	/** 验证规则 */
	rules?: FormItemRule[];
	/** 选择框选项（type 为 select 时使用） */
	options?: CuiFormSelectOption[];
	/** 是否禁用 */
	disabled?: boolean;
	/** 默认值 */
	defaultValue?: any;
	/** 自定义插槽名称（用于复杂的自定义渲染） */
	slot?: string;
}

/**
 * 表单组件 Props
 */
export interface CuiFormProps<T = any> {
	/** 表单字段配置 */
	fields: CuiFormField<T>[];
	/** 表单数据（双向绑定） */
	modelValue: T;
	/** 标签宽度 */
	labelWidth?: string | number;
	/** 是否行内表单 */
	inline?: boolean;
	/** 是否禁用整个表单 */
	disabled?: boolean;
	/** 标签位置 */
	labelPosition?: "left" | "right" | "top";
}

/**
 * 表单验证结果
 */
export interface CuiFormValidateResult {
	/** 是否验证通过 */
	valid: boolean;
	/** 验证错误信息 */
	errors?: Record<string, string[]>;
}
