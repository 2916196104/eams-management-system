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
		info: "新增节假日“2026-05-01”",
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
	{
		add_time: "2026-03-26 15:09:37",
		broswer_name: "Safari 18",
		browser_ver: "192.168.1.42",
		info: "登录后台系统",
		operator: 4,
		org_id: "/auth/login",
		os_name: "iPadOS",
		time_cost: "68",
		type: "老师登录",
	},
];

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

function mapDictionaryItem(item: Partial<DatadictVO>): DictionaryItem {
	return {
		id: String(item.id ?? ""),
		categoryId: String(item.dictId ?? ""),
		name: item.name || "",
		info: item.info || "",
		sortNum: item.softNum ?? 0,
	};
}
