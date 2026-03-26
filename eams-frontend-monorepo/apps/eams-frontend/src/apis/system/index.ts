import type { PageDTO } from "../type";
import { useHttp } from "@/plugins/http";
import type {
	DatadictVO,
	DictTypeDTO,
	DictionaryCategory,
	DictionaryItem,
	HolidayDTO,
	NoticeSettingDTO,
	OptlogDTO,
	PermissionDTO,
	PermissionGroupVO,
	PermissionNode,
	RolePermissionTreeData,
	RoleRecord,
	RolepermDTO,
	RolepermStaffDTO,
	SettingDTO,
	SettingOptionDTO,
	SystemSettingGroup,
} from "./type";

function cloneValue<T>(value: T): T {
	if (typeof structuredClone === "function") return structuredClone(value);
	return JSON.parse(JSON.stringify(value)) as T;
}

function delay(ms = 80) {
	return new Promise((resolve) => setTimeout(resolve, ms));
}

let dictCategories: DictionaryCategory[] = [
	{ id: "dict-1", label: "客户来源", code: "customer_source", itemCount: 4 },
	{ id: "dict-2", label: "请款类型", code: "payment_type", itemCount: 3 },
	{ id: "dict-3", label: "退款类型", code: "refund_type", itemCount: 3 },
];

let dictItems: DictionaryItem[] = [
	{ id: "item-1", categoryId: "dict-1", name: "抖音平台", info: "抖音", sortNum: 1 },
	{ id: "item-2", categoryId: "dict-1", name: "微信登记", info: "企业微信与公众号", sortNum: 2 },
	{ id: "item-3", categoryId: "dict-2", name: "课程退款", info: "退课退款", sortNum: 1 },
	{ id: "item-4", categoryId: "dict-2", name: "物料采购", info: "教具物料采购", sortNum: 2 },
	{ id: "item-5", categoryId: "dict-3", name: "余额退款", info: "课次余额", sortNum: 1 },
];

let noticeSetting: NoticeSettingDTO = {
	id: 1,
	name: "weixingtongzhi",
	emailon: false,
	messageId_eg: "SMS_EXAMPLE",
	messageon: true,
	noticewechatId: "WECHAT_TEMPLATE_EXAMPLE",
	tips: "模板提示",
	wechaton: true,
};

const settingGroups: SystemSettingGroup[] = [
	{
		id: "system",
		label: "系统设置",
		items: [
			{
				id: "auto-finish-class",
				label: "班级结业时班内学员自动结业",
				description: "如果学员课次有余量则不会自动结业",
				type: "switch",
				value: false,
			},
			{
				id: "auto-create-group",
				label: "报名 1V1 课程时自动生成班级",
				type: "switch",
				value: true,
			},
			{
				id: "parent-default-password",
				label: "家长端初始密码",
				description: "添加学生时的默认登录密码",
				type: "input",
				value: "111111",
			},
			{
				id: "finance-reminder-account",
				label: "新订单默认提醒账号",
				description: "学员在线购课后，若无顾问则通知该账号",
				type: "input",
				value: "admin",
			},
		],
	},
	{
		id: "course",
		label: "课时设置",
		items: [
			{
				id: "course-insufficient-count",
				label: "课次数不足预警数量",
				description: "课次不足时可以按设置给学员和负责老师发通知",
				type: "number",
				value: 1,
			},
			{
				id: "next-day-remind-time",
				label: "次日上课提醒时间",
				type: "time",
				value: "19:50",
			},
			{
				id: "student-signin-enabled",
				label: "学生端开启签到功能",
				description: "关闭后只能在管理端通过老师点名消课",
				type: "switch",
				value: true,
			},
		],
	},
	{
		id: "wechat",
		label: "微信公众号设置",
		items: [
			{
				id: "wechat-appid",
				label: "公众号 AppId",
				type: "input",
				value: "appid",
			},
			{
				id: "wechat-secret",
				label: "公众号 Secret",
				type: "input",
				value: "secret",
			},
			{
				id: "wechat-token",
				label: "公众号 Token",
				type: "input",
				value: "token",
			},
		],
	},
];

let systemSettingOptionMap: Record<string, SettingOptionDTO> = {};

let roles: RoleRecord[] = [
	{
		id: "role-1",
		name: "超级管理员",
		code: "superadmin",
		description: "拥有系统全部操作权限",
		memberCount: 2,
		members: [
			{ id: 1, name: "陈校长" },
			{ id: 2, name: "运营负责人" },
		],
		permissionIds: [
			"system.notice",
			"system.setting",
			"system.role",
			"system.dict",
			"system.notification",
			"student.read",
			"student.write",
		],
	},
	{
		id: "role-2",
		name: "教务主管",
		code: "edu_manager",
		description: "负责课程、排课与通知配置",
		memberCount: 2,
		members: [
			{ id: 3, name: "王老师" },
			{ id: 4, name: "赵老师" },
		],
		permissionIds: ["system.notice", "system.setting", "system.notification", "student.read"],
	},
	{
		id: "role-3",
		name: "前台顾问",
		code: "consultant",
		description: "负责咨询与基础资料维护",
		memberCount: 2,
		members: [
			{ id: 5, name: "周顾问" },
			{ id: 6, name: "许顾问" },
		],
		permissionIds: ["system.notice", "student.read"],
	},
];

const permissionTree: PermissionNode[] = [
	{
		id: "system",
		label: "系统管理",
		children: [
			{ id: "system.notice", label: "内部公告" },
			{ id: "system.setting", label: "系统参数" },
			{ id: "system.role", label: "角色与权限" },
			{ id: "system.dict", label: "数据字典" },
			{ id: "system.notification", label: "通知设置" },
		],
	},
	{
		id: "student",
		label: "学员管理",
		children: [
			{ id: "student.read", label: "查看学员" },
			{ id: "student.write", label: "编辑学员" },
		],
	},
];

let holidayRecords: HolidayDTO[] = [
	{ id: "holiday-1", holidayTime: "2026-01-01" },
	{ id: "holiday-2", holidayTime: "2026-05-01" },
	{ id: "holiday-3", holidayTime: "2026-10-01" },
	{ id: "holiday-4", holidayTime: "2026-10-02" },
];

const operationLogRecords: OptlogDTO[] = [
	{
		add_time: "2026-03-26 09:10:22",
		broswer_name: "Chrome 134",
		browser_ver: "192.168.1.20",
		info: "新增节假日 2026-05-01",
		operator: 1,
		org_id: "/sys/holiday",
		os_name: "Windows 11",
		time_cost: "85",
		type: "新增",
	},
	{
		add_time: "2026-03-26 10:18:43",
		broswer_name: "Edge 135",
		browser_ver: "192.168.1.31",
		info: "更新通知设置模板参数",
		operator: 2,
		org_id: "/noticesetting/savesetting",
		os_name: "Windows 10",
		time_cost: "102",
		type: "修改",
	},
	{
		add_time: "2026-03-26 11:02:08",
		broswer_name: "Chrome 134",
		browser_ver: "192.168.1.18",
		info: "删除字典项“试听课”",
		operator: 1,
		org_id: "/sys/dict/delete-dict",
		os_name: "Windows 11",
		time_cost: "97",
		type: "删除",
	},
	{
		add_time: "2026-03-26 13:21:16",
		broswer_name: "Firefox 136",
		browser_ver: "192.168.1.25",
		info: "导出操作日志列表",
		operator: 3,
		org_id: "/system/operation-log/export",
		os_name: "macOS",
		time_cost: "156",
		type: "导出",
	},
];

export async function listSystemSettingGroups(): Promise<SystemSettingGroup[]> {
	const http = useHttp();
	try {
		const res = await http.get<SettingDTO[]>("/sys/sysparam");
		const groups = [...(res.data || [])].sort((a, b) => (a.sortNum ?? 0) - (b.sortNum ?? 0));
		const detailList = await Promise.all(
			groups.map(async (group) => {
				const detailRes = await http.get<SettingOptionDTO[]>(`/sys/sysparam/${group.id}`);
				return {
					group,
					items: [...(detailRes.data || [])].sort((a, b) => (a.sortNum ?? 0) - (b.sortNum ?? 0)),
				};
			}),
		);

		systemSettingOptionMap = {};
		return detailList.map(({ group, items }) => ({
			id: String(group.id),
			label: group.name || group.code || `设置组${group.id}`,
			code: group.code,
			description: group.remark || undefined,
			sortNum: group.sortNum,
			items: items.map((item) => {
				systemSettingOptionMap[String(item.id)] = item;
				return mapSystemSettingItem(item);
			}),
		}));
	} catch {
		await delay();
		return cloneValue(settingGroups);
	}
}

export async function updateSystemSetting(groupId: string, itemId: string, value: string | number | boolean): Promise<void> {
	const http = useHttp();
	const cached = systemSettingOptionMap[itemId];
	if (cached) {
		await http.put("/sys/sysparam", {
			code: cached.code,
			id: cached.id,
			info: cached.info,
			name: cached.name,
			settingId: cached.settingId ?? Number(groupId),
			sortNum: cached.sortNum ?? 0,
			value: normalizeSettingRequestValue(value, cached),
			valueType: cached.valueType,
		});
		systemSettingOptionMap[itemId] = {
			...cached,
			value: normalizeSettingRequestValue(value, cached),
		};
		return;
	}

	await delay();
	const group = settingGroups.find((item) => item.id === groupId);
	const setting = group?.items.find((item) => item.id === itemId);
	if (setting) setting.value = value;
}

export async function listRoles(): Promise<RoleRecord[]> {
	const http = useHttp();
	try {
		const res = await http.get<RolepermDTO[] | PageDTO<RolepermDTO>>("/sys/roleperm/nameList");
		return normalizeRoleRecords(res.data);
	} catch {
		await delay();
		return cloneValue(roles);
	}
}

export async function saveRole(data: Partial<RoleRecord> & Pick<RoleRecord, "name" | "code">): Promise<RoleRecord> {
	const http = useHttp();
	const payload: Partial<RolepermDTO> = {
		code: data.code,
		name: data.name,
	};
	if (data.id) payload.id = Number(data.id);

	try {
		const res = await http.post<RolepermDTO>("/sys/roleperm/save", payload);
		return mapRoleRecord(res.data || payload);
	} catch {
		await delay();
		if (data.id) {
			const index = roles.findIndex((item) => item.id === data.id);
			if (index !== -1) {
				roles[index] = {
					...roles[index],
					...data,
					memberCount: data.members?.length ?? roles[index].members.length,
					permissionIds: data.permissionIds ?? roles[index].permissionIds,
					members: data.members ?? roles[index].members,
				};
				return cloneValue(roles[index]);
			}
		}

		const record: RoleRecord = {
			id: `role-${Date.now()}`,
			name: data.name,
			code: data.code,
			description: data.description || "",
			memberCount: data.members?.length ?? 0,
			members: data.members ?? [],
			permissionIds: data.permissionIds ?? [],
		};
		roles = [...roles, record];
		return cloneValue(record);
	}
}

export async function deleteRole(roleId: string): Promise<void> {
	const http = useHttp();
	try {
		await http.delete(`/sys/roleperm/delete/role/${roleId}`);
	} catch {
		await delay();
		roles = roles.filter((item) => item.id !== roleId);
	}
}

export async function listRoleMembers(roleId: string, keyword = ""): Promise<RolepermStaffDTO[]> {
	const http = useHttp();
	try {
		const res = await http.get<PageDTO<RolepermStaffDTO>>("/sys/roleperm", {
			roleId: Number(roleId),
			pageIndex: 1,
			pageSize: 100,
			name: keyword || undefined,
		});
		return normalizeRoleMembers(res.data?.rows || []);
	} catch {
		await delay();
		const role = roles.find((item) => item.id === roleId);
		const members = role?.members || [];
		if (!keyword.trim()) return cloneValue(members);
		return cloneValue(members.filter((item) => item.name.includes(keyword.trim())));
	}
}

export async function addRoleMember(roleId: string, staffId: string): Promise<void> {
	const http = useHttp();
	try {
		await http.post(`/sys/roleperm?roleId=${Number(roleId)}`, {
			staffId: Number(staffId),
		});
	} catch {
		await delay();
		const role = roles.find((item) => item.id === roleId);
		if (!role) return;
		if (role.members.some((item) => String(item.id) === staffId)) return;
		role.members = [...role.members, { id: Number(staffId), name: `员工${staffId}` }];
		role.memberCount = role.members.length;
	}
}

export async function removeRoleMember(roleId: string, staffId: string): Promise<void> {
	const http = useHttp();
	try {
		await http.delete(`/sys/roleperm/${staffId}`, {
			roleId: Number(roleId),
		});
	} catch {
		await delay();
		const role = roles.find((item) => item.id === roleId);
		if (!role) return;
		role.members = role.members.filter((item) => String(item.id) !== staffId);
		role.memberCount = role.members.length;
	}
}

export async function getPermissionTree(roleId: string): Promise<RolePermissionTreeData> {
	const http = useHttp();
	try {
		const [allRes, selectedRes] = await Promise.all([
			http.get<PermissionGroupVO | PermissionGroupVO[]>("/sys/roleperm/query/list/permission"),
			roleId
				? http.get<PermissionGroupVO | PermissionGroupVO[]>(`/sys/roleperm/query/list/select/${roleId}`)
				: Promise.resolve({ data: [] as PermissionGroupVO[] }),
		]);

		return buildPermissionTreeData(allRes.data, selectedRes.data);
	} catch {
		await delay();
		return {
			tree: cloneValue(permissionTree),
			checkedKeys: cloneValue(roles.find((item) => item.id === roleId)?.permissionIds || []),
			permissionMap: createFallbackPermissionMap(permissionTree),
		};
	}
}

export async function updateRolePermissions(roleId: string, permissions: PermissionDTO[]): Promise<void> {
	const http = useHttp();
	try {
		await http.post(`/sys/roleperm/modify/${roleId}`, permissions);
	} catch {
		await delay();
		const role = roles.find((item) => item.id === roleId);
		if (role) role.permissionIds = permissions.map((item) => String(item.id));
	}
}

export async function listDictionaryCategories(): Promise<DictionaryCategory[]> {
	const http = useHttp();
	try {
		const res = await http.get<DictTypeDTO[]>("/sys/dict/type-name-list");
		const categories = [...(res.data || [])].sort((a, b) => Number(a.sortNum || 0) - Number(b.sortNum || 0));
		const categoriesWithCount = await Promise.all(
			categories.map(async (item) => {
				const detailRes = await http.get<PageDTO<DatadictVO>>("/sys/dict/list-by-dict-id", {
					dictId: item.id,
					pageIndex: 1,
					pageSize: 1,
				});
				return {
					id: String(item.id),
					label: item.name || item.code || `字典类型${item.id}`,
					code: item.code,
					itemCount: detailRes.data?.total ?? detailRes.data?.rows?.length ?? 0,
					remark: item.remark,
					sortNum: Number(item.sortNum || 0),
				} satisfies DictionaryCategory;
			}),
		);
		return categoriesWithCount;
	} catch {
		await delay();
		return cloneValue(dictCategories);
	}
}

export async function listDictionaryItems(categoryId: string): Promise<DictionaryItem[]> {
	const http = useHttp();
	try {
		const res = await http.get<PageDTO<DatadictVO>>("/sys/dict/list-by-dict-id", {
			dictId: Number(categoryId),
			pageIndex: 1,
			pageSize: 1000,
		});
		return (res.data?.rows || []).map(mapDictionaryItem).sort((a, b) => (a.sortNum ?? 0) - (b.sortNum ?? 0));
	} catch {
		await delay();
		return cloneValue(dictItems.filter((item) => item.categoryId === categoryId));
	}
}

export async function saveDictionaryItem(
	data: Partial<DictionaryItem> & Pick<DictionaryItem, "categoryId" | "name">,
): Promise<DictionaryItem> {
	const http = useHttp();
	const payload = {
		dictId: Number(data.categoryId),
		id: data.id ? Number(data.id) : undefined,
		info: data.info || "",
		name: data.name,
		softNum: typeof data.sortNum === "number" ? data.sortNum : Number(data.sortNum || 0),
	};

	try {
		if (data.id) {
			await http.put("/sys/dict/update-dict", payload);
			const detail = await http.get<DatadictVO>(`/sys/dict/${data.id}`);
			return mapDictionaryItem(detail.data || payload);
		}
		await http.post("/sys/dict/save-dict", payload);
		return mapDictionaryItem(payload);
	} catch {
		await delay();
		if (data.id) {
			const index = dictItems.findIndex((item) => item.id === data.id);
			if (index !== -1) {
				dictItems[index] = {
					...dictItems[index],
					...data,
					info: data.info || dictItems[index].info || "",
					sortNum: typeof data.sortNum === "number" ? data.sortNum : Number(data.sortNum || 0),
				};
				return cloneValue(dictItems[index]);
			}
		}

		const record: DictionaryItem = {
			id: `item-${Date.now()}`,
			categoryId: data.categoryId,
			name: data.name,
			info: data.info || "",
			sortNum: typeof data.sortNum === "number" ? data.sortNum : Number(data.sortNum || 0),
		};
		dictItems = [...dictItems, record];
		dictCategories = dictCategories.map((item) =>
			item.id === data.categoryId ? { ...item, itemCount: item.itemCount + 1 } : item,
		);
		return cloneValue(record);
	}
}

export async function deleteDictionaryItems(ids: string[]): Promise<void> {
	const http = useHttp();
	try {
		await http.delete("/sys/dict/delete-dict", ids.map((item) => Number(item)));
	} catch {
		await delay();
		const removed = dictItems.filter((item) => ids.includes(item.id));
		dictItems = dictItems.filter((item) => !ids.includes(item.id));
		dictCategories = dictCategories.map((item) => ({
			...item,
			itemCount: item.itemCount - removed.filter((row) => row.categoryId === item.id).length,
		}));
	}
}

export async function saveDictionaryCategory(
	data: Partial<DictionaryCategory> & Pick<DictionaryCategory, "label">,
): Promise<boolean> {
	const http = useHttp();
	const res = await http.post<boolean>("/sys/dict/save-dict-type", {
		code: data.code,
		id: data.id ? Number(data.id) : undefined,
		name: data.label,
		remark: data.remark,
		sortNum: data.sortNum != null ? String(data.sortNum) : undefined,
	});
	return Boolean(res.data);
}

export async function deleteDictionaryCategories(ids: string[]): Promise<boolean> {
	const http = useHttp();
	const res = await http.delete<boolean>("/sys/dict/remove-dict-type", {
		ids: ids.map((item) => Number(item)),
	});
	return Boolean(res.data);
}

export async function listNotificationTemplates(name: string): Promise<NoticeSettingDTO> {
	const http = useHttp();
	try {
		const res = await http.get<NoticeSettingDTO>("/noticesetting", {
			name,
			pageIndex: 1,
			pageSize: 10,
		});
		return {
			...res.data,
			name,
			emailon: Boolean(res.data?.emailon),
			messageon: Boolean(res.data?.messageon),
			wechaton: Boolean(res.data?.wechaton),
		};
	} catch {
		await delay();
		return cloneValue({
			...noticeSetting,
			name,
		});
	}
}

export async function updateNotificationTemplate(data: NoticeSettingDTO): Promise<void> {
	const http = useHttp();
	try {
		await http.post("/noticesetting/savesetting", {
			emailon: Boolean(data.emailon),
			id: data.id,
			messageId_eg: data.messageId_eg || "",
			messageon: Boolean(data.messageon),
			noticewechatId: data.noticewechatId || "",
			tips: data.tips || "",
			wechaton: Boolean(data.wechaton),
		});
	} catch {
		await delay();
		noticeSetting = {
			...data,
			name: data.name || noticeSetting.name,
		};
	}
}

export async function listHolidays(params?: {
	pageIndex?: number;
	pageSize?: number;
	year?: number;
}): Promise<PageDTO<HolidayDTO>> {
	const http = useHttp();
	const pageIndex = params?.pageIndex ?? 1;
	const pageSize = params?.pageSize ?? 366;
	const year = params?.year;

	try {
		const query: Record<string, any> = {
			pageIndex,
			pageSize,
		};
		if (year != null) {
			query["holidayList[0].year"] = year;
		}

		const res = await http.get<PageDTO<HolidayDTO>>("/sys/holiday", query);
		return {
			pageIndex: res.data?.pageIndex ?? pageIndex,
			pageSize: res.data?.pageSize ?? pageSize,
			pages: res.data?.pages ?? 1,
			total: res.data?.total ?? res.data?.rows?.length ?? 0,
			rows: (res.data?.rows || []).map((item) => ({
				id: item.id != null ? String(item.id) : undefined,
				holidayTime: item.holidayTime,
			})),
		};
	} catch {
		await delay();
		const rows = holidayRecords.filter((item) => (year != null ? item.holidayTime.startsWith(`${year}-`) : true));
		return {
			pageIndex,
			pageSize,
			pages: 1,
			total: rows.length,
			rows: cloneValue(rows),
		};
	}
}

export async function addHoliday(holidayTime: string): Promise<void> {
	const http = useHttp();
	try {
		await http.post("/sys/holiday", undefined, {
			params: {
				holidayTime,
			},
			upType: 0,
		});
	} catch {
		await delay();
		if (!holidayRecords.some((item) => item.holidayTime === holidayTime)) {
			holidayRecords = [
				...holidayRecords,
				{
					id: `holiday-${Date.now()}`,
					holidayTime,
				},
			];
		}
	}
}

export async function deleteHoliday(id: string): Promise<void> {
	const http = useHttp();
	try {
		await http.delete(`/sys/holiday/${id}`);
	} catch {
		await delay();
		holidayRecords = holidayRecords.filter((item) => item.id !== id);
	}
}

export async function listOperationLogs(params?: {
	info?: string;
	operator?: number;
	pageIndex?: number;
	pageSize?: number;
	type?: string;
}): Promise<PageDTO<OptlogDTO>> {
	const http = useHttp();
	const pageIndex = params?.pageIndex ?? 1;
	const pageSize = params?.pageSize ?? 10;

	try {
		const res = await http.get<PageDTO<OptlogDTO>>("/sys/optlog", {
			info: params?.info,
			operator: params?.operator,
			pageIndex,
			pageSize,
			type: params?.type,
		});
		return {
			pageIndex: res.data?.pageIndex ?? pageIndex,
			pageSize: res.data?.pageSize ?? pageSize,
			pages: res.data?.pages ?? 1,
			total: res.data?.total ?? res.data?.rows?.length ?? 0,
			rows: res.data?.rows || [],
		};
	} catch {
		await delay();
		const filtered = operationLogRecords.filter((item) => {
			const infoMatched = !params?.info || String(item.info || "").includes(params.info);
			const typeMatched = !params?.type || String(item.type || "") === params.type;
			const operatorMatched = params?.operator == null || Number(item.operator) === params.operator;
			return infoMatched && typeMatched && operatorMatched;
		});
		const start = (pageIndex - 1) * pageSize;
		const rows = filtered.slice(start, start + pageSize);
		return {
			pageIndex,
			pageSize,
			pages: Math.max(1, Math.ceil(filtered.length / pageSize)),
			total: filtered.length,
			rows: cloneValue(rows),
		};
	}
}

function normalizeRoleRecords(data?: RolepermDTO[] | PageDTO<RolepermDTO>): RoleRecord[] {
	const rows = Array.isArray(data) ? data : data?.rows || [];
	return rows.map(mapRoleRecord);
}

function normalizeRoleMembers(data: RolepermStaffDTO[]): RolepermStaffDTO[] {
	return data.map((item) => ({
		id: Number(item.id),
		name: item.name || `员工${item.id}`,
		mobile: item.mobile,
	}));
}

function mapRoleRecord(item?: Partial<RolepermDTO>): RoleRecord {
	return {
		id: String(item?.id ?? ""),
		name: item?.name || "",
		code: item?.code || "",
		memberCount: 0,
		members: [],
		permissionIds: [],
	};
}

function buildPermissionTreeData(
	allData?: PermissionGroupVO | PermissionGroupVO[],
	selectedData?: PermissionGroupVO | PermissionGroupVO[],
): RolePermissionTreeData {
	const permissionMap: Record<string, PermissionDTO> = {};
	const groups = normalizePermissionGroups(allData);
	const tree = groups.map((group, index) => {
		const label = group.groupName?.trim() || `未分组-${index + 1}`;
		const children = (group.permissions || [])
			.filter((item): item is PermissionDTO => item?.id != null)
			.map((item) => {
				const key = String(item.id);
				permissionMap[key] = item;
				return {
					id: key,
					label: item.name,
				} satisfies PermissionNode;
			});

		return {
			id: `group-${index + 1}`,
			label,
			children,
		} satisfies PermissionNode;
	});

	const selectedPermissions = normalizePermissionGroups(selectedData).flatMap(
		(group) => group.selectedPermissions || group.permissions || [],
	);
	for (const permission of selectedPermissions) {
		if (permission?.id != null) {
			permissionMap[String(permission.id)] = permission;
		}
	}

	return {
		tree,
		checkedKeys: Array.from(
			new Set(
				selectedPermissions
					.filter((item): item is PermissionDTO => item?.id != null)
					.map((item) => String(item.id)),
			),
		),
		permissionMap,
	};
}

function normalizePermissionGroups(data?: PermissionGroupVO | PermissionGroupVO[]): PermissionGroupVO[] {
	if (!data) return [];
	return Array.isArray(data) ? data : [data];
}

function createFallbackPermissionMap(tree: PermissionNode[]): Record<string, PermissionDTO> {
	const permissionMap: Record<string, PermissionDTO> = {};
	for (const group of tree) {
		for (const child of group.children || []) {
			const key = String(child.id);
			permissionMap[key] = {
				id: key,
				groupName: group.label,
				name: child.label,
			};
		}
	}
	return permissionMap;
}

function mapSystemSettingItem(item: SettingOptionDTO): SystemSettingGroup["items"][number] {
	return {
		id: String(item.id),
		label: item.name || item.code || `配置项${item.id}`,
		description: item.info || undefined,
		type: inferSettingValueType(item),
		value: parseSettingValue(item.value, item.valueType),
		code: item.code,
		settingId: item.settingId ? String(item.settingId) : undefined,
		sortNum: item.sortNum,
		valueType: item.valueType,
	};
}

function inferSettingValueType(item: SettingOptionDTO): "switch" | "input" | "textarea" | "number" | "time" {
	const valueType = String(item.valueType || "").toLowerCase();
	const rawValue = String(item.value ?? "").trim();
	if (isBooleanSettingType(valueType)) return "switch";
	if (isNumberSettingType(valueType)) return "number";
	if (isTimeSettingValue(rawValue)) return "time";
	if (rawValue.length > 80 || rawValue.includes("\n")) return "textarea";
	return "input";
}

function parseSettingValue(value: SettingOptionDTO["value"], valueType?: string) {
	const text = String(value ?? "").trim();
	if (isBooleanSettingType(String(valueType || "").toLowerCase())) {
		if (text === "1" || text.toLowerCase() === "true") return true;
		if (text === "0" || text.toLowerCase() === "false") return false;
		return Boolean(value);
	}
	if (isNumberSettingType(String(valueType || "").toLowerCase())) {
		const num = Number(value);
		return Number.isNaN(num) ? 0 : num;
	}
	return value ?? "";
}

function normalizeSettingRequestValue(value: string | number | boolean, option: SettingOptionDTO) {
	const valueType = String(option.valueType || "").toLowerCase();
	if (isBooleanSettingType(valueType)) {
		const original = String(option.value ?? "").trim().toLowerCase();
		if (original === "1" || original === "0") return value ? "1" : "0";
		return value ? "true" : "false";
	}
	if (isNumberSettingType(valueType)) return Number(value);
	return String(value ?? "");
}

function isBooleanSettingType(valueType: string) {
	return ["bool", "boolean", "switch"].some((item) => valueType.includes(item));
}

function isNumberSettingType(valueType: string) {
	return ["int", "long", "double", "float", "decimal", "number"].some((item) => valueType.includes(item));
}

function isTimeSettingValue(value: string) {
	return /^\d{2}:\d{2}(:\d{2})?$/.test(value);
}

function mapDictionaryItem(item: Partial<DatadictVO>): DictionaryItem {
	return {
		id: String(item.id ?? ""),
		categoryId: String(item.dictId ?? ""),
		name: item.name || "",
		info: item.info || "",
		sortNum: item.softNum ?? 0,
	};
}
