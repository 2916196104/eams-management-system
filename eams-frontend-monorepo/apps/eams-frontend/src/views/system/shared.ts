import {
	addRoleMember,
	deleteDictionaryCategories,
	deleteDictionaryItems,
	deleteRole,
	getPermissionTree,
	listDictionaryCategories,
	listDictionaryItems,
	listDictionaryItemsPage,
	listNotificationTemplates,
	listRoleMembers,
	listRoles,
	listSystemSettingGroups,
	removeRoleMember,
	saveDictionaryCategory,
	saveDictionaryItem,
	saveRole,
	updateNotificationTemplate,
	updateRolePermissions,
	updateSystemSetting,
} from "@/apis/system";
import type { PageDTO } from "@/apis/type";
import type {
	DictionaryCategory,
	DictionaryItem,
	NoticeSettingDTO,
	PermissionDTO,
	RolePermissionTreeData,
	RoleRecord,
	RolepermStaffDTO,
	SystemSettingGroup,
} from "@/apis/system/type";

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

export interface SystemSettingsPageConfig {
	headers: {
		item: string;
		value: string;
	};
	loadGroups: () => Promise<SystemSettingGroup[]>;
	updateValue: (groupId: string, itemId: string, value: string | number | boolean) => Promise<void>;
}

export interface SystemRolePermissionPageConfig {
	titles: {
		list: string;
		addRole: string;
		memberSection: string;
		addMember: string;
		memberEmpty: string;
		permissionSection: string;
		empty: string;
		createDialog: string;
		editDialog: string;
	};
	formFields: SystemFormField[];
	loadRoles: () => Promise<RoleRecord[]>;
	loadPermissionTree: (roleId: string) => Promise<RolePermissionTreeData>;
	saveRole: (data: Partial<RoleRecord> & Pick<RoleRecord, "name" | "code">) => Promise<RoleRecord>;
	deleteRole: (roleId: string) => Promise<void>;
	loadRoleMembers: (roleId: string, keyword?: string) => Promise<RolepermStaffDTO[]>;
	addRoleMember: (roleId: string, staffId: string) => Promise<void>;
	removeRoleMember: (roleId: string, staffId: string) => Promise<void>;
	updateRolePermissions: (roleId: string, permissions: PermissionDTO[]) => Promise<void>;
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
	saveCategory: (data: Partial<DictionaryCategory> & Pick<DictionaryCategory, "label">) => Promise<boolean>;
	deleteCategories: (ids: string[]) => Promise<boolean>;
	loadItemsPage: (
		categoryId: string,
		params?: {
			pageIndex?: number;
			pageSize?: number;
			info?: string;
			name?: string;
		},
	) => Promise<PageDTO<DictionaryItem>>;
	loadItems: (categoryId: string) => Promise<DictionaryItem[]>;
	saveItem: (data: Partial<DictionaryItem> & Pick<DictionaryItem, "categoryId" | "name">) => Promise<DictionaryItem>;
	deleteItems: (ids: string[]) => Promise<void>;
}

export interface SystemNotificationPageConfig {
	title: string;
	settingName: string;
	saveButtonText: string;
	loadSetting: (name: string) => Promise<NoticeSettingDTO>;
	saveSetting: (data: NoticeSettingDTO) => Promise<void>;
}

export const systemSettingsConfig: SystemSettingsPageConfig = {
	headers: {
		item: "设置项",
		value: "设置值",
	},
	loadGroups: listSystemSettingGroups,
	updateValue: updateSystemSetting,
};

export const rolePermissionConfig: SystemRolePermissionPageConfig = {
	titles: {
		list: "角色列表",
		addRole: "添加角色",
		memberSection: "已分配人员",
		addMember: "添加员工",
		memberEmpty: "当前角色下暂无员工",
		permissionSection: "角色权限",
		empty: "请选择角色",
		createDialog: "新增角色",
		editDialog: "编辑角色",
	},
	formFields: [
		{ prop: "name", label: "角色名称" },
		{ prop: "code", label: "角色编码" },
	],
	loadRoles: listRoles,
	loadPermissionTree: getPermissionTree,
	saveRole,
	deleteRole,
	loadRoleMembers: listRoleMembers,
	addRoleMember,
	removeRoleMember,
	updateRolePermissions,
};

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
	saveCategory: saveDictionaryCategory,
	deleteCategories: deleteDictionaryCategories,
	loadItemsPage: listDictionaryItemsPage,
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
