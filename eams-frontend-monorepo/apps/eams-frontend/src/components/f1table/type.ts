/**
 * ============================================
 * F1Table 表格组件 - 类型定义文件
 * ============================================
 * 该文件定义了 F1Table 表格组件所需的所有类型和枚举
 */

/**
 * ============================================
 * 表格列类型枚举
 * ============================================
 * 用于标识表格列的类型，决定列的渲染方式和功能
 */
export enum TableType {
	/** selection: 复选框列，用于多选功能 */
	selection = "selection",

	/** index: 序号列，显示行号 */
	index = "index",

	/** custom: 自定义列，通过插槽自定义内容 */
	custom = "custom",

	/** normal: 普通列，直接显示数据 */
	normal = "normal",

	/** handler: 操作列，用于放置操作按钮 */
	handler = "handler",
}

/**
 * ============================================
 * 表格列配置接口
 * ============================================
 * 定义表格每一列的配置选项
 */
export interface tableList {
	/**
	 * 列类型，对应 TableType 枚举
	 * - selection: 复选框列
	 * - index: 序号列
	 * - custom: 自定义列
	 * - normal: 普通列
	 * - handler: 操作列
	 */
	type: string;

	/**
	 * 列字段名，对应数据对象的属性名
	 * 注意：selection、index、handler 类型不需要设置 prop
	 */
	prop?: string;

	/** 列标题，显示在表头 */
	label: string;

	/** 列宽度，如 "100px" 或 "10%" */
	width?: string;

	/**
	 * 插槽名称，仅在 type 为 custom 时使用
	 * 用于标识自定义列的插槽名称
	 * 示例：slotName: "status" 对应模板中的 #status 插槽
	 */
	slotName?: string;

	/**
	 * 允许任意其他属性
	 * 支持 Element Plus el-table-column 的所有属性
	 * 如：fixed、align、show-overflow-tooltip 等
	 */
	[key: string]: any;
}

/**
 * ============================================
 * 分页配置接口
 * ============================================
 * 定义分页组件的配置选项
 */
export interface PaginationConfig {
	/** 是否启用分页功能，默认 true */
	enabled?: boolean;

	/** 当前页码，从 1 开始 */
	currentPage?: number;

	/** 每页显示的数据条数 */
	pageSize?: number;

	/** 可选的每页条数数组，用于切换每页显示条数 */
	pageSizes?: number[];

	/** 数据总条数 */
	total?: number;

	/**
	 * 分页组件的布局配置
	 * 可选值：total、sizes、prev、pager、next、jumper
	 * 默认值：'total, sizes, prev, pager, next, jumper'
	 */
	layout?: string;

	/**
	 * 分页变化时的回调函数
	 * @param page 变化后的页码
	 * @param size 变化后的每页条数
	 */
	onPageChange?: (page: number, size: number) => void;
}

/**
 * ============================================
 * 操作栏配置接口
 * ============================================
 * 定义表格操作列（操作栏）的按钮配置
 */
export interface HandlerConfig {
	/** 是否显示查看按钮 */
	view?: boolean;

	/** 是否显示编辑按钮 */
	edit?: boolean;

	/** 是否显示删除按钮 */
	delete?: boolean;

	/** 是否显示自定义按钮（预留） */
	custom?: boolean;

	/** 查看按钮的文本，默认 "查看" */
	viewText?: string;

	/** 编辑按钮的文本，默认 "编辑" */
	editText?: string;

	/** 删除按钮的文本，默认 "删除" */
	deleteText?: string;

	/** 查看按钮点击的回调函数 */
	onView?: (row: any) => void;

	/** 编辑按钮点击的回调函数 */
	onEdit?: (row: any) => void;

	/** 删除按钮点击的回调函数 */
	onDelete?: (row: any) => void;
}

/**
 * ============================================
 * 表格配置接口
 * ============================================
 * 定义 F1Table 组件的完整配置
 */
export interface TableConfig {
	/**
	 * 网络接口名称（预留字段）
	 * 可用于标识当前表格对应的后端接口
	 */
	pageName?: string;

	/**
	 * Element Plus el-table 的属性配置
	 * 支持 el-table 的所有属性
	 * 如：stripe、border、height、maxHeight 等
	 */
	tableProperties?: object;

	/**
	 * 表格列配置数组
	 * 定义表格的每一列
	 */
	tableList: tableList[];

	/** 分页配置 */
	pagination?: PaginationConfig;

	/** 操作栏配置 */
	handler?: HandlerConfig;

	/**
	 * 行数据的唯一标识字段
	 * 用于表格的复选框、展开行等功能
	 * 默认值：'id'
	 */
	rowKey?: string;

	/** 表格加载状态，设置为 true 显示加载遮罩 */
	loading?: boolean;

	/**
	 * 复选框选择变化时的回调函数
	 * @param selection 当前选中的所有行数据
	 */
	onSelectionChange?: (selection: any[]) => void;
}

/**
 * ============================================
 * 默认表格配置实例
 * ============================================
 * 提供一个开箱即用的默认配置示例
 * 包含常见的列配置和基本属性
 */
export const F1TableConfig: TableConfig = {
	/** Element Plus el-table 属性：斑马纹 + 纵向边框 */
	tableProperties: {
		stripe: true,
		border: true,
	},

	/**
	 * 表格列配置
	 * 包含：复选框、序号、用户名、真实名、手机号、状态、操作列
	 */
	tableList: [
		{
			type: TableType.selection, // 复选框列
			width: "50px",
			label: "选择",
			fixed: true, // 固定在左侧
		},
		{
			type: TableType.index, // 序号列
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
			type: TableType.custom, // 自定义列，需要配合插槽使用
			label: "状态",
			prop: "enable",
			width: "80px",
			slotName: "status", // 插槽名称
		},
		{
			type: TableType.handler, // 操作列
			label: "操作",
			width: "130px",
		},
	],
};
