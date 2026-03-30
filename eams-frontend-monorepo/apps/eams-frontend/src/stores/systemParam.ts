import { defineStore } from "pinia";
import { ref } from "vue";
import { getParamList, getParamDetail, updateParam } from "@/apis/system/param";
import type { SysParamDTO, SysParamOptionDTO } from "@/apis/system/param/type";

/** 设置分类（页面展示用） */
export interface ParamCategory {
	id: number;
	code: string;
	name: string;
	remark?: string;
	sortNum: number;
}

/** 设置选项（页面展示用） */
export interface ParamOption {
	id: number;
	code: string;
	name: string;
	info?: string;
	settingId: number;
	sortNum: number;
	value: boolean | number | string;
	valueType: string;
}

function normalizeCategories(rows: SysParamDTO[]): ParamCategory[] {
	return rows
		.map((item) => ({
			id: item.id,
			code: item.code,
			name: item.name,
			remark: item.remark,
			sortNum: item.sortNum ?? 0,
		}))
		.sort((a, b) => a.sortNum - b.sortNum);
}

function normalizeOptions(rows: SysParamOptionDTO[]): ParamOption[] {
	return rows
		.map((item) => ({
			id: item.id,
			code: item.code,
			name: item.name,
			info: item.info,
			settingId: item.settingId,
			sortNum: item.sortNum ?? 0,
			value: item.value,
			valueType: item.valueType,
		}))
		.sort((a, b) => a.sortNum - b.sortNum);
}

function extractRows<T>(data: unknown): T[] {
	if (Array.isArray(data)) {
		return data;
	}

	if (data && typeof data === "object") {
		const source = data as {
			rows?: T[];
			list?: T[];
			data?: unknown;
		};
		const rows = source.rows ?? source.list;
		return Array.isArray(rows) ? rows : [];
	}

	return [];
}

function unwrapPayload(input: unknown): unknown {
	let current = input;

	while (current && typeof current === "object" && "data" in (current as Record<string, unknown>)) {
		const next = (current as { data?: unknown }).data;
		if (next === undefined || next === current) {
			break;
		}
		current = next;
	}

	return current;
}

function hasServerPayload(input: unknown) {
	return Boolean(
		input &&
		typeof input === "object" &&
		("data" in (input as Record<string, unknown>) || "status" in (input as Record<string, unknown>)),
	);
}

export const useSystemParamStore = defineStore("systemParam", () => {
	/** 设置分类列表 */
	const categories = ref<ParamCategory[]>([]);
	/** 当前选中的分类 ID */
	const currentCategoryId = ref<number | null>(null);
	/** 当前分类下的参数选项列表 */
	const options = ref<ParamOption[]>([]);
	/** 分类加载状态 */
	const categoriesLoading = ref(false);
	/** 选项加载状态 */
	const optionsLoading = ref(false);

	/** 获取设置分类列表 */
	async function fetchCategories() {
		categoriesLoading.value = true;
		try {
			const res = await getParamList();
			const data = unwrapPayload(res);
			const rows = extractRows<SysParamDTO>(data);
			categories.value = normalizeCategories(rows);

			if (categories.value.length === 0) {
				currentCategoryId.value = null;
				options.value = [];
			} else if (currentCategoryId.value == null) {
				await selectCategory(categories.value[0].id);
			} else {
				const currentExists = categories.value.some((item) => item.id === currentCategoryId.value);
				if (currentExists) {
					await fetchOptions(currentCategoryId.value);
				} else {
					await selectCategory(categories.value[0].id);
				}
			}

			return true;
		} catch (error) {
			const rows = extractRows<SysParamDTO>(unwrapPayload(error));
			if (rows.length > 0) {
				categories.value = normalizeCategories(rows);

				if (categories.value.length === 0) {
					currentCategoryId.value = null;
					options.value = [];
				} else if (currentCategoryId.value == null) {
					await selectCategory(categories.value[0].id);
				} else {
					const currentExists = categories.value.some((item) => item.id === currentCategoryId.value);
					if (currentExists) {
						await fetchOptions(currentCategoryId.value);
					} else {
						await selectCategory(categories.value[0].id);
					}
				}

				return true;
			}

			categories.value = [];
			options.value = [];
			currentCategoryId.value = null;
			return false;
		} finally {
			categoriesLoading.value = false;
		}
	}

	/** 获取设置选项详情 */
	async function fetchOptions(categoryId: number) {
		optionsLoading.value = true;
		try {
			const res = await getParamDetail(categoryId);
			const data = unwrapPayload(res);
			const rows = extractRows<SysParamOptionDTO>(data);
			options.value = normalizeOptions(rows);
			return true;
		} catch (error) {
			const rows = extractRows<SysParamOptionDTO>(unwrapPayload(error));
			if (rows.length > 0) {
				options.value = normalizeOptions(rows);
				return true;
			}

			options.value = [];
			return false;
		} finally {
			optionsLoading.value = false;
		}
	}

	/** 选中分类 */
	async function selectCategory(categoryId: number) {
		currentCategoryId.value = categoryId;
		return fetchOptions(categoryId);
	}

	/** 保存参数选项 */
	async function saveOption(data: ParamOption) {
		try {
			await updateParam({
				id: data.id,
				code: data.code,
				name: data.name,
				info: data.info,
				settingId: data.settingId,
				sortNum: data.sortNum,
				value: data.value,
				valueType: data.valueType,
			});
			await fetchOptions(data.settingId);
			return true;
		} catch (error) {
			if (!hasServerPayload(error)) {
				return false;
			}

			return fetchOptions(data.settingId);
		}
	}

	return {
		categories,
		currentCategoryId,
		options,
		categoriesLoading,
		optionsLoading,
		fetchCategories,
		fetchOptions,
		selectCategory,
		saveOption,
	};
});
