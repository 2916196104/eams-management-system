/**
 * CuiDialog 组件类型定义
 */

/**
 * 对话框组件 Props
 */
export interface CuiDialogProps {
	/** 对话框标题 */
	title?: string;
	/** 对话框是否显示 */
	modelValue: boolean;
	/** 对话框宽度 */
	width?: string | number;
	/** 是否显示关闭按钮 */
	showClose?: boolean;
	/** 点击遮罩层是否关闭对话框 */
	closeOnClickModal?: boolean;
	/** 对话框关闭前的回调 */
	beforeClose?: (done: () => void) => void;
	/** 是否显示底部按钮栏 */
	showFooter?: boolean;
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
 * 对话框事件
 */
export interface CuiDialogEmits {
	/** 对话框显示状态更新 */
	"update:modelValue": [value: boolean];
	/** 确认按钮点击事件 */
	confirm: [];
	/** 取消按钮点击事件 */
	cancel: [];
	/** 对话框打开事件 */
	open: [];
	/** 对话框关闭事件 */
	close: [];
}
