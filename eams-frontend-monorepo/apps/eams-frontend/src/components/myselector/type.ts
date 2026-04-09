/**
 * 人员数据模型
 */
export interface PersonData {
	/** 姓名 */
	name: string;
	/** 部门 */
	department: string;
	/** 手机号 */
	phone: string;
	/** 用户ID */
	id?: string | number;
	/** 其他扩展字段 */
	[key: string]: any;
}
export interface PersonColumn {
	prop: string;
	label: string;
	minWidth?: string | number;
	width?: string | number;
}
/**
 * 人员选择器组件属性模型
 */
export interface MyPersonSelectorProps {
	/** v-model绑定的选中人员数据 */
	modelValue?: PersonData | null;
	/** 输入框占位符文本，默认为"请选择人员" */
	placeholder?: string;
	/** 搜索框占位符文本，默认为"请输入姓名关键字搜索" */
	searchPlaceholder?: string;
	/** 选择器面板宽度，默认为"500px" */
	panelWidth?: string;
	/** 表格高度，默认为"400px" */
	tableHeight?: string;
	/** 每页显示条数选项，默认为[10, 20, 50, 100] */
	pageSizes?: number[];
	/** 默认每页显示条数，默认为10 */
	defaultPageSize?: number;
	/** 静态数据源 */
	data?: PersonData[];
	/** 动态数据加载函数 */
	dataLoader?: () => Promise<PersonData[]>;
	// 新增列配置
	columns?: PersonColumn[];
}
