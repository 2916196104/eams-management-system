export interface SearchField {
	label: string;
	prop: string;
	component?: "input" | "select" | "date";
	placeholder?: string;
	options?: {
		label: string;
		value: any;
	}[];
}

export interface TableColumn {
	label: string;
	prop: string;
	width?: number | string;
	minWidth?: number | string;
}

export interface SelectionTablePopoverProps {
	/** 输入框展示文本（v-model） */
	modelValue?: string;
	/** 占位符 */
	placeholder?: string;
	/** 选中行后展示字段，默认取表格第一列 prop */
	displayProp?: string;
	searchFields: SearchField[];
	columns: TableColumn[];
	data: any[];
	total?: number;
	loading?: boolean;
	/** 弹层宽度 */
	width?: number;
	/** 分页可选 page-size */
	pageSizes?: number[];
	/** 默认每页条数 */
	defaultPageSize?: number;
	/** 是否多选（预留，当前仍为行内「选择」） */
	multiple?: boolean;
}
