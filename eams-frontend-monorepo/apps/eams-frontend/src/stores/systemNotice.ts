import { defineStore } from "pinia";
import { ref } from "vue";
import { getNoticeList, editNotice, delNotice, getNoticeDetail } from "@/apis/system/notice";
import type { INoticeList, INoticeSave } from "@/apis/system/notice/type";

export interface NoticeItem {
	id: number;
	title: string;
	content: string;
	type?: string;
	publisher?: string;
	isTop?: number;
	isEnable?: number;
	createTime: string;
	updateTime?: string;
}

const mockData: NoticeItem[] = [
	{
		id: 1,
		title: "系统升级通知",
		content: "系统将于今晚10点进行升级，请提前保存数据。",
		createTime: "2026-03-20 10:00:00",
		updateTime: "2026-03-20 10:00:00",
	},
	{
		id: 2,
		title: "春季优惠活动",
		content: "春季报名优惠活动开始啦，详情请查看公告栏。",
		createTime: "2026-03-18 14:30:00",
		updateTime: "2026-03-19 09:00:00",
	},
	{
		id: 3,
		title: "课程调整公告",
		content: "部分课程时间有所调整，请注意查看课程表。",
		createTime: "2026-03-15 16:00:00",
		updateTime: "2026-03-15 16:00:00",
	},
	{
		id: 4,
		title: "端午节放假通知",
		content: "端午节放假三天，6月10日至6月12日。",
		createTime: "2026-03-10 08:00:00",
		updateTime: "2026-03-12 10:30:00",
	},
	{
		id: 5,
		title: "新员工入职培训",
		content: "本周五进行新员工培训，地点：会议室A。",
		createTime: "2026-03-08 11:00:00",
		updateTime: "2026-03-08 11:00:00",
	},
];

let localMockData = [...mockData];

export const useSystemNoticeStore = defineStore("systemNotice", () => {
	const tableData = ref<NoticeItem[]>([]);
	const loading = ref(false);
	const total = ref(0);

	const searchParams = ref<INoticeList>({
		title: "",
		pageSize: 10,
		pageNum: 1,
	});

	/** 获取列表 */
	async function fetchList() {
		loading.value = true;
		try {
			const res = await getNoticeList(searchParams.value);
			// res 是 JsonVO 格式 { code, message, data }
			const data = (res as any).data ?? res;
			const rows: NoticeItem[] = data.records || data.list || data.rows || (Array.isArray(data) ? data : []);
			tableData.value = rows;
			total.value = data.total ?? rows.length;
		} catch {
			// API 不可用时使用 mock 数据
			const title = searchParams.value.title ?? "";
			const filtered = localMockData.filter((item) => item.title.includes(title));
			const start = ((searchParams.value.pageNum ?? 1) - 1) * (searchParams.value.pageSize ?? 10);
			tableData.value = filtered.slice(start, start + (searchParams.value.pageSize ?? 10));
			total.value = filtered.length;
		} finally {
			loading.value = false;
		}
	}

	/** 保存公告（新增/编辑） */
	async function saveNotice(data: INoticeSave) {
		try {
			await editNotice(data);
			await fetchList();
			return true;
		} catch {
			// mock 模式：本地操作
			if (data.id === 0) {
				const newId = localMockData.length > 0 ? Math.max(...localMockData.map((i) => i.id)) + 1 : 1;
				const now = new Date().toLocaleString("zh-CN");
				localMockData.unshift({
					id: newId,
					title: data.title,
					content: data.content,
					createTime: now,
					updateTime: now,
				});
			} else {
				const idx = localMockData.findIndex((item) => item.id === data.id);
				if (idx !== -1) {
					localMockData[idx].title = data.title;
					localMockData[idx].content = data.content;
					localMockData[idx].updateTime = new Date().toLocaleString("zh-CN");
				}
			}
			await fetchList();
			return true;
		}
	}

	/** 删除公告 */
	async function deleteNotice(ids: number[]) {
		try {
			await delNotice({ ids });
			await fetchList();
			return true;
		} catch {
			// mock 模式：本地操作
			localMockData = localMockData.filter((item) => !ids.includes(item.id));
			await fetchList();
			return true;
		}
	}

	/** 获取详情 */
	async function fetchDetail(id: number) {
		try {
			const res = await getNoticeDetail(id);
			return ((res as any).data ?? res) as NoticeItem;
		} catch {
			return localMockData.find((item) => item.id === id) ?? null;
		}
	}

	/** 设置搜索参数 */
	function setSearchParams(params: Partial<INoticeList>) {
		searchParams.value = { ...searchParams.value, ...params };
	}

	/** 重置搜索参数 */
	function resetSearchParams() {
		searchParams.value = { title: "", pageSize: 10, pageNum: 1 };
	}

	return {
		tableData,
		loading,
		total,
		searchParams,
		fetchList,
		saveNotice,
		deleteNotice,
		fetchDetail,
		setSearchParams,
		resetSearchParams,
	};
});
