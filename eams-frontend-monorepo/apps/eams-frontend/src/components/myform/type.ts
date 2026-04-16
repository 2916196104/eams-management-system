import type { FormItemRule } from "element-plus";
import type { Arrayable } from "element-plus/es/utils";
import type { MyFormBaseProps } from "./props/formbase";
import type { FormRules } from "element-plus";

/**
 * 自定义表单属性模型，注意：这里将rule和model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/form.html#form-attributes
 */
export interface MyFormAttr {
	/** 显示表单域个数 */
	"show-count"?: number;
	/** 行内表单模式 */
	inline?: boolean;
	/** 是否禁用表单内所有组件 */
	disabled?: boolean;
	/** 用于控制该表单内组件的尺寸 */
	size?: "large" | "default" | "small" | "";
	/** 表单域标签的位置， 当设置为left或right时，则也需要设置label-width属性 */
	"label-position"?: "left" | "right" | "top";
	/** 标签的长度,例如 '50px'，可以使用 auto */
	"label-width"?: string | number;
	/** 表单域标签的后缀 */
	"label-suffix"?: string;
}
/**
 * 自定义表单域属性模型
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/form.html#formitem-attributes
 */
export interface MyFormItemAttr {
	/** 表单域组件类型 //FIXME 扩充其他表单组件需要在这里添加类型 */
	type:
		| "input"
		| "number"
		| "select"
		| "cascader"
		| "cascader-panel"
		| "date"
		| "checkbox"
		| "checkbox-group"
		| "radio"
		| "radio-group"
		| "file";
	/** 表单组件属性 */
	fprops?: MyFormBaseProps;
	/** 对应model的键名，对应表单数据中的字段名称 */
	prop: string;
	/** 表单域的标签 */
	label?: string;
	/** 是否为必填项，如不设置，则会根据校验规则确认 */
	required?: boolean;
	/** 表单域的提示信息 */
	rules?: Arrayable<FormItemRule>;
	/** 用于控制该表单域下组件的默认尺寸 */
	size?: "large" | "default" | "small" | "";
	/** 表单域标签的位置， 当设置为left或right时，则也需要设置label-width属性 */
	"label-position"?: "left" | "right" | "top";
	/** 标签的长度,例如 '50px'，可以使用 auto */
	"label-width"?: string | number;
}
/**
 * 自定义表单组件属性模型
 * 用于自定义表单组件（MyForm）传递属性和数据的模型
 */
export interface MyFormProps<T> {
	/** 表单数据 */
	model: T;
	/** 表单域数据 */
	items: MyFormItemAttr[];
	/** 组件标题 */
	formtitle?: string;
	/** 表单属性 */
	formattr?: MyFormAttr;
	/** 表单验证规则 */
	rules?: FormRules;
	/** 是否显示返回按钮，默认显示 */
	showback?: boolean;
	/** 是否显示重置按钮，默认显示 */
	showreset?: boolean;
	/** 提交按钮显示文字, 默认为 提交 */
	submittext?: string;
	/** 是否禁用默认before-close逻辑，默认不禁用 */
	disableBeforeClose?: boolean;
}

//FIXME 扩充其他表单组件需要在这里新增对应的扩展属性接口定义导出
export type { MyFormBaseProps };
export type { MyFormInputProps, MyFormInputNumberProps } from "./props/input";
export type {
	MyFormSelectProps,
	MyFormSelectOption,
	MyFormCascaderProps,
	MyFormCascaderPanelProps,
} from "./props/select";
export type { MyFormDatePickerProps } from "./props/date";
export type { MyFormCheckBoxProps, MyFormCheckBoxGroupProps } from "./props/checkbox";
export type { MyFormRadioBoxProps, MyFormRadioBoxGroupProps } from "./props/radio";
