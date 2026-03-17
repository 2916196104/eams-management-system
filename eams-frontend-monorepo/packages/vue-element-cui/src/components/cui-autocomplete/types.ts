/**
 * CuiAutocomplete 组件类型定义
 */

/**
 * 建议选项
 */
export interface CuiAutocompleteSuggestion {
	/** 建议值 */
	value: string;
	/** 其他自定义属性 */
	[key: string]: any;
}

/**
 * 自动完成组件 Props
 */
export interface CuiAutocompleteProps {
	/** 输入值 */
	modelValue: string;
	/** 建议列表（用于简单场景） */
	suggestions?: CuiAutocompleteSuggestion[];
	/** 获取建议的方法（用于复杂场景，如远程搜索） */
	fetchSuggestions?: (queryString: string, cb: (suggestions: CuiAutocompleteSuggestion[]) => void) => void;
	/** 占位符 */
	placeholder?: string;
	/** 是否禁用 */
	disabled?: boolean;
	/** 是否可清空 */
	clearable?: boolean;
	/** 输入建议的去抖延时（毫秒） */
	debounce?: number;
	/** 是否在输入框聚焦时显示建议 */
	triggerOnFocus?: boolean;
}

/**
 * 自动完成事件
 */
export interface CuiAutocompleteEmits {
	/** 输入值更新 */
	"update:modelValue": [value: string];
	/** 选中建议事件 */
	select: [item: CuiAutocompleteSuggestion];
}
