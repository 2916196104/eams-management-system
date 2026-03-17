import type { CuiFormField, CuiFormProps } from "../cui-form/types";

/**
 * 对话框表单组件 Props
 */
export interface CuiDialogFormProps<T = any> {
	/** 对话框是否显示 */
	visible: boolean;
	/** 表单数据 */
	modelValue: T;
	/** 对话框标题 */
	title?: string;
	/** 对话框宽度 */
	width?: string | number;
	/** 是否显示关闭按钮 */
	showClose?: boolean;
	/** 点击遮罩层是否关闭对话框 */
	closeOnClickModal?: boolean;
	/** 表单字段配置 */
	fields: CuiFormField<T>[];
	/** 标签宽度 */
	labelWidth?: string | number;
	/** 是否行内表单 */
	inline?: boolean;
	/** 是否禁用整个表单 */
	disabled?: boolean;
	/** 标签位置 */
	labelPosition?: "left" | "right" | "top";
	/** 确认按钮文本 */
	confirmText?: string;
	/** 取消按钮文本 */
	cancelText?: string;
	/** 是否禁用确认按钮 */
	confirmDisabled?: boolean;
	/** 是否显示加载状态 */
	loading?: boolean;
}

/**
 * 对话框表单事件
 */
export interface CuiDialogFormEmits<T = any> {
	/** 对话框显示状态更新 */
	"update:visible": [value: boolean];
	/** 表单数据更新 */
	"update:modelValue": [value: T];
	/** 表单提交 */
	submit: [value: T];
	/** 取消按钮点击 */
	cancel: [];
	/** 对话框打开 */
	open: [];
	/** 对话框关闭 */
	close: [];
}
