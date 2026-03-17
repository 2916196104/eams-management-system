/**
 * CuiTab 组件类型定义
 */

/**
 * Tab 项配置
 */
export interface CuiTabItem {
	/** Tab 标签 */
	label: string;
	/** Tab 名称（唯一标识） */
	name: string;
	/** Tab 内容 */
	content?: string;
	/** 是否禁用 */
	disabled?: boolean;
	/** 是否可关闭 */
	closable?: boolean;
}

/**
 * Tab 组件 Props
 */
export interface CuiTabProps {
	/** Tab 项列表 */
	tabs: CuiTabItem[];
	/** 当前活跃的 Tab */
	activeTab: string;
	/** Tab 类型：card, border-card */
	type?: "card" | "border-card";
	/** 是否可关闭 */
	closable?: boolean;
	/** 是否可添加 */
	addable?: boolean;
	/** 可编辑类型：add, remove, both */
	editableType?: "add" | "remove" | "both";
}
