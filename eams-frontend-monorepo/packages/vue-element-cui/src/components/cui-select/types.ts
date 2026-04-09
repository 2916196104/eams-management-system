/**
 * CuiSelect 组件类型定义
 */

/**
 * 选择框选项
 */
export interface CuiSelectOption {
	/** 选项标签 */
	label: string;
	/** 选项值 */
	value: any;
	/** 是否禁用 */
	disabled?: boolean;
}

/**
 * 选择框组件 Props
 */
export interface CuiSelectProps {
	/** 选中的值 */
	modelValue: any;
	/** 选项数组 */
	options?: CuiSelectOption[];
	/** 占位符 */
	placeholder?: string;
	/** 是否禁用 */
	disabled?: boolean;
	/** 是否可清空 */
	clearable?: boolean;
	/** 是否可搜索 */
	filterable?: boolean;
	/** 是否支持远程搜索 */
	remote?: boolean;
	/** 远程搜索方法 */
	remoteMethod?: (query: string) => void;
	/** 是否正在加载 */
	loading?: boolean;
}

/**
 * 选择框事件
 */
export interface CuiSelectEmits {
	/** 选中值更新 */
	"update:modelValue": [value: any];
	/** 值变化事件 */
	change: [value: any];
}
