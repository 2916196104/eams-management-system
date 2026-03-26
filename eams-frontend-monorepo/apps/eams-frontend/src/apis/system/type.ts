import type { PageQuery } from "../type";

export interface InternalAnnouncement {
	id: number;
	title: string;
	content: string;
	createdAt: string;
	updatedAt: string;
	publisher: string;
}

export interface InternalAnnouncementQuery extends PageQuery {
	title?: string;
}

export type SettingValueType = "switch" | "input" | "textarea" | "number" | "time";

export interface SystemSettingItem {
	id: string;
	label: string;
	description?: string;
	type: SettingValueType;
	value: string | number | boolean;
	placeholder?: string;
	code?: string;
	settingId?: string;
	sortNum?: number;
	valueType?: string;
}

export interface SystemSettingGroup {
	id: string;
	label: string;
	code?: string;
	description?: string;
	sortNum?: number;
	items: SystemSettingItem[];
}

export interface SettingDTO {
	id: number;
	code?: string;
	name?: string;
	remark?: string;
	sortNum?: number;
}

export interface SettingOptionDTO {
	id: number;
	code?: string;
	info?: string;
	name?: string;
	settingId?: number;
	sortNum?: number;
	value?: string | number | boolean | null;
	valueType?: string;
}

export interface RoleRecord {
	id: string;
	name: string;
	code: string;
	description?: string;
	memberCount: number;
	members: RolepermStaffDTO[];
	permissionIds: string[];
}

export interface PermissionNode {
	id: string;
	label: string;
	children?: PermissionNode[];
}

export interface RolepermDTO {
	id: number;
	code: string;
	name: string;
}

export interface PermissionDTO {
	enabled?: number;
	groupName?: string;
	id: number;
	name: string;
}

export interface PermissionGroupVO {
	groupName?: string;
	permissions?: PermissionDTO[];
	selectedPermissions?: PermissionDTO[];
}

export interface RolePermissionTreeData {
	tree: PermissionNode[];
	checkedKeys: string[];
	permissionMap: Record<string, PermissionDTO>;
}

export interface RolepermStaffDTO {
	id: number;
	name: string;
	mobile?: string;
}

export interface RolepermStaffQuery {
	roleId: string;
	pageIndex?: number;
	pageSize?: number;
	name?: string;
}

export interface DictionaryCategory {
	id: string;
	label: string;
	code?: string;
	itemCount: number;
	remark?: string;
	sortNum?: number;
}

export interface DictionaryItem {
	id: string;
	categoryId: string;
	name: string;
	info?: string;
	sortNum?: number;
	value?: string;
	remark?: string;
}

export interface DictTypeDTO {
	id: number;
	code?: string;
	name?: string;
	remark?: string;
	sortNum?: string | number;
}

export interface DatadictVO {
	id: number;
	dictId?: number;
	info?: string;
	name?: string;
	softNum?: number;
}

export interface NoticeSettingDTO {
	id?: number;
	emailon: boolean;
	messageId_eg?: string;
	messageon: boolean;
	noticewechatId?: string;
	tips?: string;
	wechaton: boolean;
	name?: string;
}

export interface NotificationTemplate {
	id: string;
	group: string;
	title: string;
	description: string;
	emailEnabled: boolean;
	wechatEnabled: boolean;
	wechatTemplateId: string;
	smsEnabled: boolean;
	smsTemplateId: string;
	hint: string;
}
