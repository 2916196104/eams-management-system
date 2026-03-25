import type { PageDTO } from "@/apis/type";
import {
	addRoleMember,
	deleteDictionaryItems,
	deleteInternalAnnouncements,
	deleteRole,
	getPermissionTree,
	listDictionaryCategories,
	listDictionaryItems,
	listInternalAnnouncements,
	listNotificationTemplates,
	listRoleMembers,
	listRoles,
	listSystemSettingGroups,
	removeRoleMember,
	saveDictionaryItem,
	saveInternalAnnouncement,
	saveRole,
	updateNotificationTemplate,
	updateRolePermissions,
	updateSystemSetting,
} from "@/apis/system";
import type {
	DictionaryCategory,
	DictionaryItem,
	InternalAnnouncement,
	NoticeSettingDTO,
	PermissionDTO,
	RoleRecord,
	RolePermissionTreeData,
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

export interface SystemAnnouncementPageConfig {
	search: {
		prop: "title";
		label: string;
	};
	columns: SystemTableColumn[];
	pageSizes: number[];
	createButtonText: string;
	deleteButtonText: string;
	createDialogTitle: string;
	editDialogTitle: string;
	defaultPublisher: string;
	formFields: SystemFormField[];
	loadPage: (query: { title: string; pageIndex: number; pageSize: number }) => Promise<PageDTO<InternalAnnouncement>>;
	saveItem: (
		data: Partial<InternalAnnouncement> & Pick<InternalAnnouncement, "title" | "content">,
	) => Promise<InternalAnnouncement>;
	deleteItems: (ids: number[]) => Promise<void>;
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

export const internalAnnouncementConfig: SystemAnnouncementPageConfig = {
	search: {
		prop: "title",
		label: "搜索标题",
	},
	columns: [
		{ prop: "title", label: "标题", minWidth: 380 },
		{ prop: "createdAt", label: "添加时间", minWidth: 220 },
		{ prop: "updatedAt", label: "修改时间", minWidth: 220 },
	],
	pageSizes: [10, 20, 30, 50],
	createButtonText: "新增",
	deleteButtonText: "删除",
	createDialogTitle: "新增公告",
	editDialogTitle: "编辑公告",
	defaultPublisher: "系统管理员",
	formFields: [
		{ prop: "title", label: "标题", maxlength: 60, showWordLimit: true },
		{ prop: "publisher", label: "发布人" },
		{ prop: "content", label: "内容", type: "textarea", rows: 6, maxlength: 300, showWordLimit: true },
	],
	loadPage: listInternalAnnouncements,
	saveItem: saveInternalAnnouncement,
	deleteItems: deleteInternalAnnouncements,
};

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
	addRoleMember: addRoleMember,
	removeRoleMember: removeRoleMember,
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
