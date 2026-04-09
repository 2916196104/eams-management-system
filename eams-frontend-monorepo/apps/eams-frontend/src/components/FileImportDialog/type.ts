/**
 * 导入模式
 */
export type ImportMode = 'frontend' | 'backend'

/**
 * 解析后的行数据
 */
export interface ParsedRow {
	/** 行号（从1开始） */
	rowNumber: number
	/** 行数据，key为表头，value为单元格值 */
	data: Record<string, any>
	/** 是否有错误 */
	hasError?: boolean
	/** 错误信息（初始化为空数组） */
	errors: string[]
}

/**
 * 解析结果
 */
export interface ParseResult {
	/** 解析的原始数据 */
	data: ParsedRow[]
	/** 表头 */
	headers: string[]
	/** 总行数 */
	totalRows: number
	/** 错误行数 */
	errorRows: number
}

/**
 * 上传进度
 */
export interface UploadProgress {
	/** 已上传字节数 */
	loaded: number
	/** 总字节数 */
	total: number
	/** 进度百分比 0-100 */
	percent: number
}

/**
 * 文件导入弹窗组件属性
 */
export interface FileImportDialogProps {
	/** 弹窗标题 */
	title?: string
	/** 弹窗宽度 */
	width?: string | number
	/** 导入模式：frontend-前端解析, backend-后端接口 */
	mode?: ImportMode
	/** 模板下载地址或模板文件名 */
	templateUrl?: string
	/** 模板文件名（用于下载时的文件名） */
	templateFileName?: string
	/** 接收文件的后端上传地址（backend模式使用） */
	action?: string
	/** 上传时的请求头 */
	headers?: Record<string, string>
	/** 上传时的额外参数 */
	data?: Record<string, any>
	/** 最大文件大小（MB） */
	maxSize?: number
	/** 接受的文件类型 */
	accept?: string
	/** 是否显示数据预览 */
	showPreview?: boolean
	/** 预览最大显示行数 */
	previewLimit?: number
	/** 是否显示错误汇总 */
 showErrorSummary?: boolean
}

/**
 * 组件事件
 */
export interface FileImportDialogEmits {
	/** 弹窗关闭事件 */
	(e: 'update:visible', value: boolean): void
	/** 文件选择事件（前端模式） */
	(e: 'file-select', file: File): void
	/** 解析完成事件（前端模式） */
	(e: 'parse-success', result: ParseResult): void
	/** 解析失败事件（前端模式） */
	(e: 'parse-error', error: Error): void
	/** 导入成功事件（前端模式：返回数据；后端模式：返回响应） */
	(e: 'import-success', data: ParseResult | any): void
	/** 导入失败事件 */
	(e: 'import-error', error: Error): void
	/** 上传进度事件（后端模式） */
	(e: 'upload-progress', progress: UploadProgress): void
}

/**
 * 文件导入状态
 */
export type ImportStatus = 'idle' | 'selected' | 'parsing' | 'parsed' | 'uploading' | 'success' | 'error'
