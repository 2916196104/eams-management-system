import type { PageDTO } from "../type";
import { useHttp } from "@/plugins/http";
import type { DatadictVO, DictTypeDTO, DictionaryCategory, DictionaryItem, NoticeSettingDTO } from "./type";

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

function mapDictionaryItem(item: Partial<DatadictVO>): DictionaryItem {
	return {
		id: String(item.id ?? ""),
		categoryId: String(item.dictId ?? ""),
		name: item.name || "",
		info: item.info || "",
		sortNum: item.softNum ?? 0,
	};
}
