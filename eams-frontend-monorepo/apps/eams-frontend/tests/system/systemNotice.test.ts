import { beforeEach, describe, expect, test, vi } from "vitest";
import { createPinia, setActivePinia } from "pinia";
import { useSystemNoticeStore } from "@/stores/systemNotice";
import { delNotice, editNotice, getNoticeDetail, getNoticeList } from "@/apis/system/notice";

vi.mock("@/apis/system/notice", () => ({
	getNoticeList: vi.fn(),
	editNotice: vi.fn(),
	delNotice: vi.fn(),
	getNoticeDetail: vi.fn(),
}));

describe("useSystemNoticeStore", () => {
	beforeEach(() => {
		setActivePinia(createPinia());
		vi.clearAllMocks();
	});

	test("fetchList 失败时不会回退本地公告 mock", async () => {
		vi.mocked(getNoticeList).mockRejectedValue(new Error("network error"));

		const store = useSystemNoticeStore();
		const success = await store.fetchList();

		expect(success).toBe(false);
		expect(store.tableData).toEqual([]);
		expect(store.total).toBe(0);
	});

	test("fetchList 能兼容 reject 但响应体里仍有列表数据", async () => {
		vi.mocked(getNoticeList).mockRejectedValue({
			status: 200,
			data: {
				data: {
					rows: [{ id: 1, title: "秋季会议纪要", content: "content", createTime: "2023-10-22 16:45" }],
					total: 1,
				},
			},
		});

		const store = useSystemNoticeStore();
		const success = await store.fetchList();

		expect(success).toBe(true);
		expect(store.tableData).toHaveLength(1);
		expect(store.total).toBe(1);
	});

	test("saveNotice 能兼容 reject 但刷新后可读到新公告", async () => {
		vi.mocked(editNotice).mockRejectedValue({
			status: 200,
			data: { message: "ok" },
		});
		vi.mocked(getNoticeList).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: {
				rows: [{ id: 9, title: "新公告", content: "内容", createTime: "2023-10-22 16:45" }],
				total: 1,
			},
		});

		const store = useSystemNoticeStore();
		const success = await store.saveNotice({ id: 9, title: "新公告", content: "内容" });

		expect(success).toBe(true);
		expect(store.tableData[0]?.title).toBe("新公告");
	});

	test("deleteNotice 能兼容 reject 但刷新后列表已更新", async () => {
		vi.mocked(delNotice).mockRejectedValue({
			status: 200,
			data: { message: "ok" },
		});
		vi.mocked(getNoticeList).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: {
				rows: [],
				total: 0,
			},
		});

		const store = useSystemNoticeStore();
		const success = await store.deleteNotice([1]);

		expect(success).toBe(true);
		expect(store.tableData).toEqual([]);
	});

	test("fetchDetail 能兼容 reject 但响应体里仍有详情数据", async () => {
		vi.mocked(getNoticeDetail).mockRejectedValue({
			status: 200,
			data: {
				data: { id: 3, title: "详情公告", content: "详情内容", createTime: "2023-10-22 16:45" },
			},
		});

		const store = useSystemNoticeStore();
		const detail = await store.fetchDetail(3);

		expect(detail?.title).toBe("详情公告");
	});
});
