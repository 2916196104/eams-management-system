import { useHttp } from "@/plugins/http";
import type { JsonVO } from "@/apis/type";
import type { PageDTO } from "@/components/mytable/type";
import type { NoticeListQuery, NoticeSaveDTO, NoticeVO } from "./type";

const http = useHttp();
const baseUrl = "/j7-interaction/j7-notice";

// ==================== Mock 数据 ====================

const USE_MOCK = true;

/** mock 公告列表 */
let mockNoticeList: NoticeVO[] = [
	{
		id: "1",
		image: "",
		title: "新版系统上线公告",
		type: "公告",
		content: "新版系统将于3月25日正式上线，届时请各部门做好相关准备工作。",
		articleCode: "GG20260325001",
		publisher: "管理员",
		status: 1,
		addTime: "2026-03-25 09:00:00",
	},
	{
		id: "2",
		image: "",
		title: "期中考试安排通知",
		type: "通知",
		content: "期中考试将于4月10日至4月15日进行，请各位同学做好复习准备。",
		articleCode: "TZ20260322002",
		publisher: "教务处",
		status: 1,
		addTime: "2026-03-22 14:00:00",
	},
	{
		id: "3",
		image: "",
		title: "实验室维护通知",
		type: "紧急",
		content: "3月20日至3月22日将对3号实验室进行网络设备升级维护，期间暂停使用。",
		articleCode: "JJ20260320003",
		publisher: "信息中心",
		status: 1,
		addTime: "2026-03-20 10:30:00",
	},
	{
		id: "4",
		image: "",
		title: "端午节放假通知",
		type: "通知",
		content: "端午节放假安排：5月31日至6月2日放假三天，6月3日正常上课。",
		articleCode: "TZ20260318004",
		publisher: "校办",
		status: 1,
		addTime: "2026-03-18 16:00:00",
	},
	{
		id: "5",
		image: "",
		title: "旧版系统停用公告",
		type: "公告",
		content: "旧版教务系统将于3月31日正式停用，请尽快迁移数据至新版系统。",
		articleCode: "GG20260315005",
		publisher: "管理员",
		status: 0,
		addTime: "2026-03-15 11:00:00",
	},
	{
		id: "6",
		image: "",
		title: "校园网升级通知",
		type: "紧急",
		content: "3月12日晚22:00至次日6:00进行校园网核心设备升级，届时网络可能中断。",
		articleCode: "JJ20260312006",
		publisher: "信息中心",
		status: 1,
		addTime: "2026-03-12 08:00:00",
	},
	{
		id: "7",
		image: "",
		title: "教师培训报名通知",
		type: "通知",
		content: "本学期教师信息化教学能力培训现已开放报名，截止日期3月15日。",
		articleCode: "TZ20260310007",
		publisher: "人事处",
		status: 0,
		addTime: "2026-03-10 09:30:00",
	},
	{
		id: "8",
		image: "",
		title: "期末考试安排公告",
		type: "公告",
		content: "期末考试定于6月20日至6月30日进行，具体考试科目及时间另行通知。",
		articleCode: "GG20260308008",
		publisher: "教务处",
		status: 1,
		addTime: "2026-03-08 15:00:00",
	},
];

let mockIdCounter = 9;

/** 成功响应 */
function ok<T>(data: T): JsonVO<T> {
	return { code: 10000, message: "success", data };
}

// ==================== Mock 实现 ====================

function mockListNotice(query: NoticeListQuery): JsonVO<PageDTO<NoticeVO>> {
	let filtered = [...mockNoticeList];
	if (query.title) {
		const keyword = query.title.toLowerCase();
		filtered = filtered.filter((n) => n.title.toLowerCase().includes(keyword));
	}
	if (query.type) {
		filtered = filtered.filter((n) => n.type === query.type);
	}
	if (query.publisher) {
		const keyword = query.publisher.toLowerCase();
		filtered = filtered.filter((n) => n.publisher.toLowerCase().includes(keyword));
	}
	const pageIndex = query.pageIndex || 1;
	const pageSize = query.pageSize || 10;
	const start = (pageIndex - 1) * pageSize;
	const rows = filtered.slice(start, start + pageSize);
	return ok({ pageIndex, pageSize, total: filtered.length, rows });
}

function mockGetNotice(id: string): JsonVO<PageDTO<NoticeVO>> {
	const item = mockNoticeList.find((n) => n.id === id);
	if (!item) return { code: 9999, message: "公告不存在" };
	return ok({ pageIndex: 1, pageSize: 10, total: 1, rows: [{ ...item }] });
}

function mockSaveNotice(data: NoticeSaveDTO): JsonVO<string> {
	if (data.id) {
		const idx = mockNoticeList.findIndex((n) => n.id === data.id);
		if (idx !== -1) {
			mockNoticeList[idx] = {
				...mockNoticeList[idx],
				title: data.title,
				type: data.type ?? mockNoticeList[idx].type,
				articleCode: data.articleCode ?? mockNoticeList[idx].articleCode,
				image: data.image ?? mockNoticeList[idx].image,
				content: data.content ?? mockNoticeList[idx].content,
			};
			return ok(data.id);
		}
	}
	const newId = String(mockIdCounter++);
	const newItem: NoticeVO = {
		id: newId,
		image: data.image || "",
		title: data.title,
		type: data.type ?? "公告",
		content: data.content,
		articleCode: data.articleCode || `GG${Date.now()}`,
		publisher: "当前用户",
		status: 1,
		addTime: new Date().toLocaleString("zh-CN", { hour12: false }).replace(/\//g, "-"),
	};
	mockNoticeList.unshift(newItem);
	return ok(newId);
}

function mockModifyNotice(id: string, status: number): JsonVO<string> {
	const item = mockNoticeList.find((n) => n.id === id);
	if (!item) return { code: 9999, message: "公告不存在" };
	item.status = status;
	return ok("操作成功");
}

function mockRemoveNotice(id: string): JsonVO<string> {
	mockNoticeList = mockNoticeList.filter((n) => n.id !== id);
	return ok("删除成功");
}

// ==================== 导出（自动切换 Mock/真实 API） ====================

/** 获取公告列表（条件+分页） */
export const listNotice = (query: NoticeListQuery) => {
	if (USE_MOCK) return Promise.resolve(mockListNotice(query));
	return http.get<PageDTO<NoticeVO>>(`${baseUrl}/query/list/select`, query);
};

/** 获取公告详情 */
export const getNoticeDetail = (id: string) => {
	if (USE_MOCK) return Promise.resolve(mockGetNotice(id));
	return http.get<PageDTO<NoticeVO>>(`${baseUrl}/query/get/select/${id}`);
};

/** 保存公告（新增/修改） */
export const saveNotice = (data: NoticeSaveDTO) => {
	if (USE_MOCK) return Promise.resolve(mockSaveNotice(data));
	return http.post<string>(`${baseUrl}/add/save/insert`, data);
};

/** 启用/停用公告 */
export const modifyNotice = (id: string, status: number) => {
	if (USE_MOCK) return Promise.resolve(mockModifyNotice(id, status));
	return http.put<string>(`${baseUrl}/modifyNotice`, null, { params: { id, status } });
};

/** 删除公告 */
export const removeNotice = (id: string) => {
	if (USE_MOCK) return Promise.resolve(mockRemoveNotice(id));
	return http.delete<string>(`${baseUrl}/removeNotice`, id);
};
