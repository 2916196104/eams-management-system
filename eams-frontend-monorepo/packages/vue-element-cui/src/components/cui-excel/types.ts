/**
 * CuiExcel 组件类型定义
 */

/**
 * Excel 导入组件 Props
 */
export interface CuiExcelProps {
	/** 对话框是否显示 */
	modelValue: boolean;
	/** 对话框标题 */
	title?: string;
	/** 上传 URL */
	uploadUrl: string;
	/** 模板下载 URL */
	templateUrl?: string;
	/** 上传请求头 */
	headers?: Record<string, string>;
	/** 上传额外参数 */
	params?: Record<string, any>;
	/** 接受的文件类型 */
	accept?: string;
}

/**
 * Excel 导入事件
 */
export interface CuiExcelEmits {
	/** 对话框显示状态更新 */
	"update:modelValue": [value: boolean];
	/** 上传成功 */
	success: [response: any, file: any, fileList: any];
	/** 上传失败 */
	error: [error: any];
}
