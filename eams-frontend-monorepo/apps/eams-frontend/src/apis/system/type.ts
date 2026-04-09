import type { PageQuery } from "../type";

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
	id: number | string;
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
	staffId: number;
	roleId?: number;
	name: string;
	mobile?: string;
}

export interface RolepermStaffQuery extends PageQuery {
	roleId: string;
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
	remark?: string;
	sortNum?: number;
	value?: string;
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
	sortNum?: number;
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

export interface HolidayDTO {
	id?: string;
	holidayTime: string;
}

export interface OptlogDTO {
	add_time?: string;
	broswer_name?: string | number;
	browser_ver?: string;
	info?: string;
	operator?: number | string;
	org_id?: number | string;
	os_name?: string;
	time_cost?: string | number;
	type?: string;
}
