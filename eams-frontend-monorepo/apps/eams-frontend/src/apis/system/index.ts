import { createPageDTO, type PageDTO } from "../type";
import { useHttp } from "@/plugins/http";
import type {
	DatadictVO,
	DictTypeDTO,
	DictionaryCategory,
	DictionaryItem,
	InternalAnnouncement,
	InternalAnnouncementQuery,
	NoticeSettingDTO,
	NotificationTemplate,
	PermissionDTO,
	PermissionGroupVO,
	PermissionNode,
	RoleRecord,
	RolePermissionTreeData,
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

let announcementSeed = 4;
let announcements: InternalAnnouncement[] = [
	{
		id: 1,
		title: "关于 2026 春季教学资料归档的通知",
		content: "请各部门于本周五前完成教学资料归档并上传至共享目录。",
		createdAt: "2026-03-10 09:30:00",
		updatedAt: "2026-03-18 11:20:00",
		publisher: "系统管理员",
	},
	{
		id: 2,
		title: "清明节放假及值班安排",
		content: "节假日期间前台、教务、财务需各安排一名值班人员。",
		createdAt: "2026-03-13 14:00:00",
		updatedAt: "2026-03-13 14:00:00",
		publisher: "行政部",
	},
	{
		id: 3,
		title: "下周例会时间调整",
		content: "原定周二的部门例会调整至周三上午 10:00 进行。",
		createdAt: "2026-03-15 18:10:00",
		updatedAt: "2026-03-20 08:40:00",
		publisher: "校区负责人",
	},
];

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
				id: "auto-join-course",
				label: "学员预约后自动入课",
				description: "管理端可以取消预约",
				type: "switch",
				value: true,
			},
			{
				id: "trial-rule",
				label: "体验卡使用规则说明",
				type: "input",
				value: "体验卡仅限未报名学员使用，每人仅限一次。",
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
				id: "course-insufficient-remind-times",
				label: "课次数不足提醒次数",
				type: "number",
				value: 2,
			},
			{
				id: "next-day-remind-time",
				label: "次日上课提醒时间",
				type: "time",
				value: "19:50",
			},
			{
				id: "daily-insufficient-remind-time",
				label: "每天课次数不足预警时间",
				description: "课次不足时可以按设置给学员和负责老师发通知",
				type: "time",
				value: "15:44",
			},
			{
				id: "student-signin-enabled",
				label: "学生端开启签到功能",
				description: "关闭后只能在管理端通过老师点名消课",
				type: "switch",
				value: true,
			},
			{
				id: "student-signin-all-day",
				label: "学生端可签到全天的课",
				description: "学生端开启签到功能后才生效",
				type: "switch",
				value: false,
			},
			{
				id: "deduct-hours-after-rollcall",
				label: "默认点名旷课时是否扣课时",
				type: "switch",
				value: true,
			},
			{
				id: "student-leave-hour-limit",
				label: "学生在上课前多少小时可以请假",
				description: "学生在上课前多少小时可以请假(0表示上课前都可以)",
				type: "number",
				value: 2,
			},
			{
				id: "teacher-rollcall-before-class-limit",
				label: "老师在上课前多少小时可点名",
				description: "留空表示不限制",
				type: "number",
				value: 0,
			},
			{
				id: "teacher-rollcall-after-class-limit",
				label: "老师在下课后多少小时可点名",
				description: "留空表示不限制",
				type: "number",
				value: 0,
			},
		],
	},
	{
		id: "sms",
		label: "短信设置",
		items: [
			{
				id: "sms-access-key",
				label: "短信接口KEY",
				type: "input",
				value: "w",
			},
			{
				id: "sms-access-secret",
				label: "短信接口秘钥",
				type: "input",
				value: "",
			},
			{
				id: "sms-sign",
				label: "短信签名",
				type: "input",
				value: "宏之博",
			},
			{
				id: "sms-verify-template-id",
				label: "验证码短信模板ID",
				type: "input",
				value: "SMS_223835183哦、",
			},
		],
	},
	{
		id: "wechat",
		label: "微信公众号设置",
		items: [
			{
				id: "wechat-appid",
				label: "公众号AppId",
				type: "input",
				value: "appid",
			},
			{
				id: "wechat-secret",
				label: "公众号Secret",
				type: "input",
				value: "d3a",
			},
			{
				id: "wechat-token",
				label: "公众号Token",
				type: "input",
				value: "iop（34与或576ure",
			},
			{
				id: "wechat-aes-key",
				label: "公众号AesKey",
				type: "input",
				value: "方法委屈。",
			},
			{
				id: "wechat-pay-merchant-id",
				label: "微信支付商户号",
				type: "input",
				value: "让他给我woide",
			},
			{
				id: "wechat-pay-merchant-secret",
				label: "微信支付商户密钥",
				type: "input",
				value: "1",
			},
			{
				id: "wechat-service-sub-appid",
				label: "服务商模式子商户公众号ID",
				type: "input",
				value: "1",
			},
			{
				id: "wechat-service-sub-merchant-id",
				label: "服务商模式子商户号",
				type: "input",
				value: "1",
			},
			{
				id: "wechat-api-client-cert-path",
				label: "apiclient_cert.p12文件的绝对路径",
				type: "input",
				value: "1",
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
			"finance.read",
		],
	},
	{
		id: "role-2",
		name: "教务主管",
		code: "edu_manager",
		description: "负责课程、签到、排课及通知配置",
		memberCount: 3,
		members: [
			{ id: 3, name: "王老师" },
			{ id: 4, name: "赵老师" },
			{ id: 5, name: "李老师" },
		],
		permissionIds: ["system.notice", "system.dict", "system.notification", "student.read", "student.write"],
	},
	{
		id: "role-3",
		name: "前台顾问",
		code: "consultant",
		description: "负责招生、咨询与基础资料维护",
		memberCount: 4,
		members: [
			{ id: 6, name: "周顾问" },
			{ id: 7, name: "许顾问" },
			{ id: 8, name: "周静" },
			{ id: 9, name: "方圆" },
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
	{
		id: "finance",
		label: "财务管理",
		children: [{ id: "finance.read", label: "查看财务数据" }],
	},
];

let dictCategories: DictionaryCategory[] = [
	{ id: "dict-1", label: "客户来源", code: "customer_source", itemCount: 4 },
	{ id: "dict-2", label: "请款类型", code: "payment_type", itemCount: 3 },
	{ id: "dict-3", label: "退款类型", code: "refund_type", itemCount: 3 },
	{ id: "dict-4", label: "积分商城分类", code: "score_shop", itemCount: 4 },
	{ id: "dict-5", label: "物料分类", code: "material_type", itemCount: 3 },
];

let dictItems: DictionaryItem[] = [
	{ id: "item-1", categoryId: "dict-1", name: "抖音平台", value: "douyin", remark: "抖音" },
	{ id: "item-2", categoryId: "dict-1", name: "微信登记", value: "wechat", remark: "企业微信与公众号" },
	{ id: "item-3", categoryId: "dict-1", name: "活动报名", value: "activity", remark: "线下活动" },
	{ id: "item-4", categoryId: "dict-1", name: "主动咨询", value: "consulting", remark: "电话或到店咨询" },
	{ id: "item-5", categoryId: "dict-2", name: "课程退费", value: "course_refund", remark: "退课退费" },
	{ id: "item-6", categoryId: "dict-2", name: "物料采购", value: "material_buy", remark: "教具物料采购" },
	{ id: "item-7", categoryId: "dict-2", name: "场地费用", value: "venue_cost", remark: "场地租赁与维护" },
	{ id: "item-8", categoryId: "dict-3", name: "余额退款", value: "balance_refund", remark: "课次余额" },
	{ id: "item-9", categoryId: "dict-3", name: "重复缴费", value: "duplicate_refund", remark: "重复支付" },
	{ id: "item-10", categoryId: "dict-3", name: "活动取消", value: "activity_cancel", remark: "活动取消退款" },
];

const notificationTemplates: NotificationTemplate[] = [
	{
		id: "notice-1",
		group: "学员通知",
		title: "学员上课提醒",
		description: "上课前一天自动发送上课提醒给学员",
		emailEnabled: false,
		wechatEnabled: true,
		wechatTemplateId: "VPRMRW8分店2ib",
		smsEnabled: true,
		smsTemplateId: "无",
		hint: "模板提示",
	},
	{
		id: "notice-2",
		group: "学员通知",
		title: "学员签到与点名通知",
		description: "点名后自动发送点名信息给学员",
		emailEnabled: false,
		wechatEnabled: true,
		wechatTemplateId: "65vkd9GGQBREbC",
		smsEnabled: true,
		smsTemplateId: "无",
		hint: "",
	},
	{
		id: "notice-3",
		group: "学员通知",
		title: "课次状态变更通知给学员",
		description: "课次状态变化后发送通知给学员",
		emailEnabled: true,
		wechatEnabled: true,
		wechatTemplateId: "A4ZQe57VBkPxPz",
		smsEnabled: true,
		smsTemplateId: "无",
		hint: "",
	},
	{
		id: "notice-4",
		group: "学员通知",
		title: "报名通知",
		description: "报名后自动发送课程签约信息给学员",
		emailEnabled: true,
		wechatEnabled: true,
		wechatTemplateId: "Ildxil55g0IPVs6VE",
		smsEnabled: false,
		smsTemplateId: "无",
		hint: "",
	},
	{
		id: "notice-5",
		group: "老师通知",
		title: "老师上课提醒",
		description: "上课前一天自动发送上课提醒给上课老师",
		emailEnabled: true,
		wechatEnabled: true,
		wechatTemplateId: "VPRMRW82ibUYaC",
		smsEnabled: false,
		smsTemplateId: "无",
		hint: "参数样例",
	},
	{
		id: "notice-6",
		group: "老师通知",
		title: "学员请假提醒",
		description: "学员发起请假后自动发送提醒给上课老师",
		emailEnabled: true,
		wechatEnabled: true,
		wechatTemplateId: "v956MOdVrribWTl",
		smsEnabled: false,
		smsTemplateId: "无",
		hint: "参数样例",
	},
	{
		id: "notice-7",
		group: "老师通知",
		title: "学员课次不足提醒",
		description: "学员剩余课时不足时发送提醒给负责老师",
		emailEnabled: true,
		wechatEnabled: true,
		wechatTemplateId: "yr8ezeT9cAhjjGcQ",
		smsEnabled: false,
		smsTemplateId: "无",
		hint: "参数样例",
	},
];

export async function listInternalAnnouncements(query: InternalAnnouncementQuery): Promise<PageDTO<InternalAnnouncement>> {
	await delay();
	const keyword = query.title?.trim();
	const filtered = keyword
		? announcements.filter((item) => item.title.includes(keyword) || item.content.includes(keyword))
		: announcements;
	const start = (query.pageIndex - 1) * query.pageSize;
	const rows = filtered.slice(start, start + query.pageSize);
	return createPageDTO({
		pageIndex: query.pageIndex,
		pageSize: query.pageSize,
		total: filtered.length,
		rows: cloneValue(rows),
	});
}

export async function saveInternalAnnouncement(
	data: Partial<InternalAnnouncement> & Pick<InternalAnnouncement, "title" | "content">,
): Promise<InternalAnnouncement> {
	await delay();
	const now = "2026-03-22 10:00:00";
	if (data.id) {
		const index = announcements.findIndex((item) => item.id === data.id);
		if (index !== -1) {
			announcements[index] = {
				...announcements[index],
				...data,
				updatedAt: now,
			};
			return cloneValue(announcements[index]);
		}
	}

	const record: InternalAnnouncement = {
		id: announcementSeed++,
		title: data.title,
		content: data.content,
		createdAt: now,
		updatedAt: now,
		publisher: data.publisher || "系统管理员",
	};
	announcements = [record, ...announcements];
	return cloneValue(record);
}

export async function deleteInternalAnnouncements(ids: number[]): Promise<void> {
	await delay();
	announcements = announcements.filter((item) => !ids.includes(item.id));
}

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
			.filter((item): item is PermissionDTO => typeof item?.id === "number")
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
		if (typeof permission?.id === "number") {
			permissionMap[String(permission.id)] = permission;
		}
	}

	return {
		tree,
		checkedKeys: Array.from(
			new Set(
				selectedPermissions
					.filter((item): item is PermissionDTO => typeof item?.id === "number")
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
				id: Number.isNaN(Number(key)) ? 0 : Number(key),
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

function mapFallbackDictionaryItem(item: DictionaryItem): DictionaryItem {
	return {
		...item,
		info: item.info || item.remark || "",
		sortNum: item.sortNum ?? 0,
	};
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
		return cloneValue(dictItems.filter((item) => item.categoryId === categoryId).map(mapFallbackDictionaryItem));
	}
}

export async function saveDictionaryItem(
	data: Partial<DictionaryItem> & Pick<DictionaryItem, "categoryId" | "name">,
): Promise<DictionaryItem> {
	const http = useHttp();
	const payload = {
		dictId: Number(data.categoryId),
		id: data.id ? Number(data.id) : undefined,
		info: data.info || data.remark || "",
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
					info: data.info || data.remark || dictItems[index].info || dictItems[index].remark,
					sortNum: typeof data.sortNum === "number" ? data.sortNum : Number(data.sortNum || 0),
				};
				return cloneValue(dictItems[index]);
			}
		}

		const record: DictionaryItem = {
			id: `item-${Date.now()}`,
			categoryId: data.categoryId,
			name: data.name,
			info: data.info || data.remark || "",
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
		return mapFallbackNoticeSetting(name);
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
		const fallback = notificationTemplates[0];
		if (fallback) {
			fallback.emailEnabled = Boolean(data.emailon);
			fallback.wechatEnabled = Boolean(data.wechaton);
			fallback.wechatTemplateId = data.noticewechatId || "";
			fallback.smsEnabled = Boolean(data.messageon);
			fallback.smsTemplateId = data.messageId_eg || "";
			fallback.hint = data.tips || "";
		}
	}
}

function mapFallbackNoticeSetting(name: string): NoticeSettingDTO {
	const fallback = notificationTemplates[0];
	return {
		id: fallback ? Number(fallback.id.replace(/[^\d]/g, "")) || 1 : 1,
		name,
		emailon: fallback?.emailEnabled ?? false,
		messageId_eg: fallback?.smsTemplateId || "",
		messageon: fallback?.smsEnabled ?? false,
		noticewechatId: fallback?.wechatTemplateId || "",
		tips: fallback?.hint || "",
		wechaton: fallback?.wechatEnabled ?? false,
	};
}
