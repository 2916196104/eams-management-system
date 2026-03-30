import { beforeEach, describe, expect, test, vi } from "vitest";
import { createPinia, setActivePinia } from "pinia";
import { useSystemParamStore } from "@/stores/systemParam";
import { getParamDetail, getParamList, updateParam } from "@/apis/system/param";

vi.mock("@/apis/system/param", () => ({
	getParamList: vi.fn(),
	getParamDetail: vi.fn(),
	updateParam: vi.fn(),
}));

describe("useSystemParamStore", () => {
	beforeEach(() => {
		setActivePinia(createPinia());
		vi.clearAllMocks();
	});

	test("fetchCategories 成功后会自动选中首个分类并加载参数项", async () => {
		vi.mocked(getParamList).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: [
				{ id: 2, code: "course", name: "课时设置", sortNum: 2 },
				{ id: 1, code: "system", name: "系统设置", sortNum: 1 },
			],
		});
		vi.mocked(getParamDetail).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: [
				{ id: 20, code: "b", name: "B", settingId: 1, sortNum: 2, value: "2", valueType: "str" },
				{ id: 10, code: "a", name: "A", settingId: 1, sortNum: 1, value: "1", valueType: "str" },
			],
		});

		const store = useSystemParamStore();

		const success = await store.fetchCategories();

		expect(success).toBe(true);
		expect(store.categories.map((item) => item.id)).toEqual([1, 2]);
		expect(store.currentCategoryId).toBe(1);
		expect(store.options.map((item) => item.id)).toEqual([10, 20]);
	});

	test("fetchCategories 失败时不会使用本地 mock 兜底数据", async () => {
		vi.mocked(getParamList).mockRejectedValue(new Error("network error"));

		const store = useSystemParamStore();

		const success = await store.fetchCategories();

		expect(success).toBe(false);
		expect(store.categories).toEqual([]);
		expect(store.options).toEqual([]);
		expect(store.currentCategoryId).toBeNull();
	});

	test("fetchCategories 能兼容被拦截器 reject 但响应体仍含数据的情况", async () => {
		vi.mocked(getParamList).mockRejectedValue({
			data: {
				code: 200,
				message: "ok",
				data: [{ id: 1, code: "system", name: "系统设置", sortNum: 1 }],
			},
		});
		vi.mocked(getParamDetail).mockRejectedValue({
			data: {
				code: 200,
				message: "ok",
				data: [{ id: 10, code: "a", name: "A", settingId: 1, sortNum: 1, value: "1", valueType: "str" }],
			},
		});

		const store = useSystemParamStore();

		const success = await store.fetchCategories();

		expect(success).toBe(true);
		expect(store.categories.map((item) => item.id)).toEqual([1]);
		expect(store.currentCategoryId).toBe(1);
		expect(store.options.map((item) => item.id)).toEqual([10]);
	});

	test("saveOption 失败时返回 false 且保留当前参数值", async () => {
		const store = useSystemParamStore();
		store.options = [
			{
				id: 1,
				code: "system_name",
				name: "系统名称",
				settingId: 1,
				sortNum: 1,
				value: "EAMS",
				valueType: "str",
			},
		];
		vi.mocked(updateParam).mockRejectedValue(new Error("save error"));

		const success = await store.saveOption({
			id: 1,
			code: "system_name",
			name: "系统名称",
			settingId: 1,
			sortNum: 1,
			value: "NEW",
			valueType: "str",
		});

		expect(success).toBe(false);
		expect(store.options[0]?.value).toBe("EAMS");
	});

	test("saveOption 能兼容 reject 但刷新后可读到最新参数值的情况", async () => {
		const store = useSystemParamStore();
		vi.mocked(updateParam).mockRejectedValue({
			status: 200,
			data: {
				message: "ok",
			},
		});
		vi.mocked(getParamDetail).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: [
				{ id: 1, code: "system_name", name: "系统名称", settingId: 1, sortNum: 1, value: "NEW", valueType: "str" },
			],
		});

		const success = await store.saveOption({
			id: 1,
			code: "system_name",
			name: "系统名称",
			settingId: 1,
			sortNum: 1,
			value: "NEW",
			valueType: "str",
		});

		expect(success).toBe(true);
		expect(store.options[0]?.value).toBe("NEW");
	});
});
