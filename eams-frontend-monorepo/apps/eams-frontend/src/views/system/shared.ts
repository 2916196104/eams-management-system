import {
	deleteDictionaryItems,
	listDictionaryCategories,
	listDictionaryItems,
	listNotificationTemplates,
	saveDictionaryItem,
	updateNotificationTemplate,
} from "@/apis/system";
import type { DictionaryCategory, DictionaryItem, NoticeSettingDTO } from "@/apis/system/type";

export interface SystemTableColumn {
	prop: string;
	label: string;
	minWidth?: number | string;
	width?: number | string;
}

export interface SystemFormField {
	prop: string;
	label: string;
	type?: "input" | "textarea";
	rows?: number;
	maxlength?: number;
	showWordLimit?: boolean;
}

export interface SystemDictionaryPageConfig {
	categoryCountSuffix: string;
	columns: SystemTableColumn[];
	createButtonText: string;
	deleteButtonText: string;
	createDialogTitle: string;
	editDialogTitle: string;
	formFields: SystemFormField[];
	loadCategories: () => Promise<DictionaryCategory[]>;
	loadItems: (categoryId: string) => Promise<DictionaryItem[]>;
	saveItem: (
		data: Partial<DictionaryItem> & Pick<DictionaryItem, "categoryId" | "name">,
	) => Promise<DictionaryItem>;
	deleteItems: (ids: string[]) => Promise<void>;
}

export interface SystemNotificationPageConfig {
	title: string;
	settingName: string;
	saveButtonText: string;
	loadSetting: (name: string) => Promise<NoticeSettingDTO>;
	saveSetting: (data: NoticeSettingDTO) => Promise<void>;
}

export const dataDictionaryConfig: SystemDictionaryPageConfig = {
	categoryCountSuffix: "项",
	columns: [
		{ prop: "name", label: "名称", minWidth: 220 },
		{ prop: "info", label: "说明", minWidth: 260 },
		{ prop: "sortNum", label: "排序", minWidth: 120 },
	],
	createButtonText: "新增",
	deleteButtonText: "删除",
	createDialogTitle: "新增字典项",
	editDialogTitle: "编辑字典项",
	formFields: [
		{ prop: "name", label: "名称" },
		{ prop: "info", label: "说明", type: "textarea", rows: 3 },
		{ prop: "sortNum", label: "排序" },
	],
	loadCategories: listDictionaryCategories,
	loadItems: listDictionaryItems,
	saveItem: saveDictionaryItem,
	deleteItems: deleteDictionaryItems,
};

export const notificationSettingConfig: SystemNotificationPageConfig = {
	title: "通知设置",
	settingName: "weixingtongzhi",
	saveButtonText: "保存设置",
	loadSetting: listNotificationTemplates,
	saveSetting: updateNotificationTemplate,
};
