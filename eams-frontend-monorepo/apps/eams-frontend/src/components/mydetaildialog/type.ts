export interface MyDetailDialogColumn {
	/** 列字段名，对应数据中的键名 */
	prop: string;
	/** 列标题 */
	label: string;
	/** 列宽度，可选 */
	width?: string | number;
	/** 列最小宽度，可选（用于小屏自适应） */
	minWidth?: string | number;
	/** 列对齐方式，默认 center */
	align?: "left" | "center" | "right";
}

/**
 * 详情对话框组件属性
 */
export interface MyDetailDialogProps<T = Record<string, any>> {
	/** 对话框标题，默认“详情” */
	title?: string;
	/** 对话框宽度，默认 900px */
	width?: string | number;
	/** 表格列配置 */
	columns: MyDetailDialogColumn[];
	/** 表格数据 */
	data: T[];
}
