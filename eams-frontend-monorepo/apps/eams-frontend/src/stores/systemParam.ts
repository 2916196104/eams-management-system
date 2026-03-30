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
	value: string | number;
	valueType: string;
}

const mockCategories: ParamCategory[] = [
	{ id: 1, code: "normal_setting", name: "系统设置", remark: "基础系统参数", sortNum: 0 },
	{ id: 2, code: "security_setting", name: "安全设置", remark: "登录与权限相关", sortNum: 1 },
	{ id: 3, code: "notify_setting", name: "通知设置", remark: "消息推送配置", sortNum: 2 },
];

const mockOptions: Record<number, ParamOption[]> = {
	1: [
		{
			id: 1,
			code: "system_name",
			name: "系统名称",
			info: "系统显示名称",
			settingId: 1,
			sortNum: 0,
			value: "EAMS",
			valueType: "str",
		},
		{
			id: 2,
			code: "page_size",
			name: "每页条数",
			info: "列表默认分页大小",
			settingId: 1,
			sortNum: 1,
			value: 10,
			valueType: "int",
		},
		{
			id: 3,
			code: "logo_url",
			name: "系统Logo",
			info: "系统Logo地址",
			settingId: 1,
			sortNum: 2,
			value: "/logo.png",
			valueType: "str",
		},
	],
	2: [
		{
			id: 4,
			code: "pwd_expire_days",
			name: "密码过期天数",
			info: "密码有效期（天）",
			settingId: 2,
			sortNum: 0,
			value: 90,
			valueType: "int",
		},
		{
			id: 5,
			code: "login_retry_count",
			name: "登录重试次数",
			info: "最大登录失败次数",
			settingId: 2,
			sortNum: 1,
			value: 5,
			valueType: "int",
		},
	],
	3: [
		{
			id: 6,
			code: "email_switch",
			name: "邮件通知",
			info: "是否开启邮件通知",
			settingId: 3,
			sortNum: 0,
			value: 1,
			valueType: "int",
		},
		{
			id: 7,
			code: "sms_switch",
			name: "短信通知",
			info: "是否开启短信通知",
			settingId: 3,
			sortNum: 1,
			value: 0,
			valueType: "int",
		},
	],
};

let localMockCategories = [...mockCategories];
let localMockOptions = JSON.parse(JSON.stringify(mockOptions)) as Record<number, ParamOption[]>;

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
			const data = (res as any).data ?? res;
			const rows: SysParamDTO[] = Array.isArray(data) ? data : data.rows || data.list || [];
			categories.value = rows
				.map((item) => ({
					id: item.id,
					code: item.code,
					name: item.name,
					remark: item.remark,
					sortNum: item.sortNum ?? 0,
				}))
				.sort((a, b) => a.sortNum - b.sortNum);

			if (categories.value.length > 0 && currentCategoryId.value == null) {
				await selectCategory(categories.value[0].id);
			}
		} catch {
			categories.value = [...localMockCategories];
			if (categories.value.length > 0 && currentCategoryId.value == null) {
				await selectCategory(categories.value[0].id);
			}
		} finally {
			categoriesLoading.value = false;
		}
	}

	/** 获取设置选项详情 */
	async function fetchOptions(categoryId: number) {
		optionsLoading.value = true;
		try {
			const res = await getParamDetail(categoryId);
			const data = (res as any).data ?? res;
			const rows: SysParamOptionDTO[] = Array.isArray(data) ? data : data.rows || data.list || [];
			options.value = rows
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
		} catch {
			options.value = localMockOptions[categoryId] ? [...localMockOptions[categoryId]] : [];
		} finally {
			optionsLoading.value = false;
		}
	}

	/** 选中分类 */
	async function selectCategory(categoryId: number) {
		currentCategoryId.value = categoryId;
		await fetchOptions(categoryId);
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
		} catch {
			const list = localMockOptions[data.settingId];
			if (list) {
				const idx = list.findIndex((item: ParamOption) => item.id === data.id);
				if (idx !== -1) {
					list[idx] = { ...data };
				}
			}
			await fetchOptions(data.settingId);
			return true;
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
