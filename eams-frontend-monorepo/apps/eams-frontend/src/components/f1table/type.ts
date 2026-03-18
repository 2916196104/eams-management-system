export enum TableType {
	selection = "selection",
	index = "index",
	custom = "custom",
	normal = "normal",
	handler = "handler",
}

export interface tableList {
	type: string;
	prop?: string;
	label: string;
	width?: string;
	slotName?: string;
	[key: string]: any;
}

export interface PaginationConfig {
	enabled?: boolean;
	currentPage?: number;
	pageSize?: number;
	pageSizes?: number[];
	total?: number;
	layout?: string;
	onPageChange?: (page: number, size: number) => void;
}

export interface HandlerConfig {
	edit?: boolean;
	delete?: boolean;
	view?: boolean;
	custom?: boolean;
	editText?: string;
	deleteText?: string;
	viewText?: string;
	onEdit?: (row: any) => void;
	onDelete?: (row: any) => void;
	onView?: (row: any) => void;
}

export interface TableConfig {
	pageName?: string;
	tableProperties?: object;
	tableList: tableList[];
	pagination?: PaginationConfig;
	handler?: HandlerConfig;
	rowKey?: string;
	loading?: boolean;
	onSelectionChange?: (selection: any[]) => void;
}
export const F1TableConfig: TableConfig = {
	tableProperties: {
		stripe: true,
		border: true,
	},
	tableList: [
		{
			type: TableType.selection,
			width: "50px",
			label: "选择",
			fixed: true,
		},
		{
			type: TableType.index,
			width: "60px",
			label: "序号",
			fixed: true,
		},
		{
			type: TableType.normal,
			label: "用户名",
			prop: "name",
		},
		{
			type: TableType.normal,
			label: "真实名",
			prop: "realname",
		},
		{
			type: TableType.normal,
			label: "手机号码",
			prop: "cellphone",
		},
		{
			type: TableType.custom,
			label: "状态",
			prop: "enable",
			width: "80px",
			slotName: "status",
		},
		{
			type: TableType.handler,
			label: "操作",
			width: "130px",
		},
	],
};
