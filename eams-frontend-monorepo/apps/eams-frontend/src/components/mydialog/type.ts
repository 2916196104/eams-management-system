/**
 * 对话框属性模型，注意：这里将model-value/v-model before-close属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/dialog.html#attributes
 */
export interface MyDialogProps<T> {
	/** 渲染需要用到的数据 */
	data: T;
	/** 对话框的标题 */
	title?: string;
	/** 对话框的宽度，默认值为50% */
	width?: string | number;
	/** 是否为全屏 */
	fullscreen?: boolean;
	/** 为Dialog启用可拖拽功能 */
	draggable?: boolean;
	/** 是否可以通过点击modal关闭Dialog */
	"close-on-click-modal"?: boolean;
	/** 是否可以通过按下ESC关闭Dialog */
	"close-on-press-escape"?: boolean;
	/** 是否显示关闭按钮 */
	"show-close"?: boolean;
	/** 是否让Dialog的header和footer部分居中排列 */
	center?: boolean;
	/** 是否水平垂直对齐对话框 */
	"align-center"?: boolean;
}

import type { MyFormAttr, MyFormItemAttr } from "@/components/myform/type";
import type { FormRules } from "element-plus";

/**
 * 表单对话框属性，基于对话框扩展属性
 */
export interface MyFormDialogProps<T extends Record<string, any>> extends MyDialogProps<T> {
	/** 提交按钮文字 */
	submitText?: string;
	/** 取消按钮文字 */
	cancelText?: string;
	/** 提交按钮是否为危险按钮 */
	danger?: boolean;
	/** 是否开启重置按钮 */
	reset?: boolean;
	/** 是否禁用默认before-close逻辑 */
	disableBeforeClose?: boolean;
	/** 表单校验规则数据 */
	rules?: FormRules<T>;
	/** 表单属性数据 */
	formattr?: MyFormAttr;
	/** 表单域数据 */
	formitemdata: Array<MyFormItemAttr>;
}
