import { createPageDTO, type PageDTO, type PageQuery } from "@/apis/type";
import { useHttp } from "@/plugins/http";
import type {
	CashoutDetail,
	CashoutPage,
	CashoutQuery,
	CashoutRow,
	CashoutVerifyPayload,
	CourseRewardPage,
	CourseRewardQuery,
	CourseRewardRow,
	CourseSalesTotalPoint,
	FundPage,
	FundQuery,
	FundRow,
	MonthlyClassFeePage,
	MonthlyClassFeeQuery,
	MonthlyClassFeeRow,
	SaleTrendPoint,
} from "./type";

type MockFundRow = FundRow & {
	handlerName?: string;
	payerName?: string;
	itemType?: number;
};

type MockCashoutDetail = CashoutDetail & {
	addTime?: string;
};

const mockFundRows: Array<MockFundRow> = [
	{
		id: 1001,
		title: "春季班学费收款",
		amount: 3980,
		studentName: "张小雨",
		operator: 201,
		operatorName: "王晓晴",
		handlerName: "王晓晴",
		payerName: "张妈妈",
		remark: "三月份续费，已线下确认",
		submit_time: "2026-03-03 10:18:00",
		verifyState: 0,
		verifyStateName: "审核中",
		verifyRemark: "等待财务确认到账",
		type: 1,
		itemType: 1,
		typeName: "学费",
	},
	{
		id: 1002,
		title: "机器人教材费",
		amount: 560,
		studentName: "李星辰",
		operator: 202,
		operatorName: "陈晓楠",
		handlerName: "陈晓楠",
		payerName: "李爸爸",
		remark: "含教材包与实验耗材",
		submit_time: "2026-03-05 15:42:00",
		verifyState: 1,
		verifyStateName: "已审核",
		verifyRemark: "已确认到账",
		type: 2,
		itemType: 2,
		typeName: "教材费",
	},
	{
		id: 1003,
		title: "校区亲子活动费",
		amount: 299,
		studentName: "王可心",
		operator: 203,
		operatorName: "赵雪",
		handlerName: "赵雪",
		payerName: "王妈妈",
		remark: "周末活动场地与材料费用",
		submit_time: "2026-03-09 09:20:00",
		verifyState: 2,
		verifyStateName: "已拒绝",
		verifyRemark: "付款截图信息不完整",
		type: 3,
		itemType: 3,
		typeName: "活动费",
	},
	{
		id: 1004,
		title: "乐高创客体验课",
		amount: 199,
		studentName: "周亦安",
		operator: 204,
		operatorName: "孙慧",
		handlerName: "孙慧",
		payerName: "周爸爸",
		remark: "体验课单次收款",
		submit_time: "2026-03-12 19:08:00",
		verifyState: 1,
		verifyStateName: "已审核",
		verifyRemark: "收款完成",
		type: 4,
		itemType: 4,
		typeName: "其他",
	},
	{
		id: 1005,
		title: "美术班补缴学费",
		amount: 1280,
		studentName: "宋嘉禾",
		operator: 205,
		operatorName: "林悦",
		handlerName: "林悦",
		payerName: "宋妈妈",
		remark: "补缴两次课程费用",
		submit_time: "2026-03-18 13:26:00",
		verifyState: 0,
		verifyStateName: "审核中",
		verifyRemark: "待核对银行卡流水",
		type: 1,
		itemType: 1,
		typeName: "学费",
	},
];

const mockMonthlyClassFeeRows: Array<MonthlyClassFeeRow> = [
	{
		teacherName: "王老师",
		month: "2026-01",
		singleClassFee: 180,
		classCount: 16,
		classFeeSubtotal: 2880,
		singleAssistantFee: 60,
		assistantCount: 4,
		assistantFeeSubtotal: 240,
	},
	{
		teacherName: "李老师",
		month: "2026-02",
		singleClassFee: 200,
		classCount: 14,
		classFeeSubtotal: 2800,
		singleAssistantFee: 80,
		assistantCount: 3,
		assistantFeeSubtotal: 240,
	},
	{
		teacherName: "陈老师",
		month: "2026-03",
		singleClassFee: 220,
		classCount: 18,
		classFeeSubtotal: 3960,
		singleAssistantFee: 90,
		assistantCount: 5,
		assistantFeeSubtotal: 450,
	},
	{
		teacherName: "周老师",
		month: "2026-03",
		singleClassFee: 160,
		classCount: 12,
		classFeeSubtotal: 1920,
		singleAssistantFee: 70,
		assistantCount: 2,
		assistantFeeSubtotal: 140,
	},
];

const mockCourseRewardRows: Array<CourseRewardRow> = [
	{
		teacherName: "王老师",
		month: "2026-03",
		studentName: "张小雨",
		courseName: "数学压轴训练营",
		consumptionCount: 6,
		feePerClass: 120,
		feeSubtotal: 720,
	},
	{
		teacherName: "李老师",
		month: "2026-03",
		studentName: "李星辰",
		courseName: "信息学启蒙营",
		consumptionCount: 8,
		feePerClass: 110,
		feeSubtotal: 880,
	},
	{
		teacherName: "陈老师",
		month: "2026-02",
		studentName: "周亦安",
		courseName: "地理提分班",
		consumptionCount: 5,
		feePerClass: 98,
		feeSubtotal: 490,
	},
	{
		teacherName: "周老师",
		month: "2026-01",
		studentName: "宋嘉禾",
		courseName: "创意美术体验课",
		consumptionCount: 4,
		feePerClass: 88,
		feeSubtotal: 352,
	},
];

const mockCashoutRows: Array<CashoutRow> = [
	{
		id: 3001,
		title: "三月广告物料采购",
		type: 1,
		typeName: "广告宣传",
		creator: 101,
		creatorName: "王晓晴",
		payeeName: "星火文化传媒",
		amount: 6800,
		addTime: "2026-03-02 11:00:00",
		account: "6217 8890 0021 8832",
		info: "校区春招宣传海报、易拉宝和短视频剪辑费用",
		verifyState: 0,
		verifyStateName: "待审核",
		verifyRemark: "待主管审批",
	},
	{
		id: 3002,
		title: "二月物业费报销",
		type: 2,
		typeName: "物业费",
		creator: 102,
		creatorName: "陈晓楠",
		payeeName: "鑫源物业",
		amount: 3200,
		addTime: "2026-03-05 09:30:00",
		account: "6222 0900 1138 7721",
		info: "校区二月物业管理及保洁服务费用",
		verifyState: 1,
		verifyStateName: "已通过",
		verifyRemark: "已完成审批并打款",
	},
	{
		id: 3003,
		title: "教具采购",
		type: 3,
		typeName: "办公耗材",
		creator: 103,
		creatorName: "赵雪",
		payeeName: "优学文具",
		amount: 1260,
		addTime: "2026-03-11 16:20:00",
		account: "6214 5021 9920 1176",
		info: "新增课堂教具、白板笔和打印纸",
		verifyState: 2,
		verifyStateName: "已驳回",
		verifyRemark: "发票抬头不符合报销要求",
	},
	{
		id: 3004,
		title: "校区水费",
		type: 4,
		typeName: "水费",
		creator: 104,
		creatorName: "孙慧",
		payeeName: "自来水公司",
		amount: 560,
		addTime: "2026-03-18 08:10:00",
		account: "6230 0099 2233 1178",
		info: "二月份校区水费缴纳",
		verifyState: 1,
		verifyStateName: "已通过",
		verifyRemark: "正常月度支出",
	},
];

const mockCashoutDetails: Record<number, MockCashoutDetail> = {
	3001: {
		id: 3001,
		title: "三月广告物料采购",
		type: 1,
		typeName: "广告宣传",
		creator: 101,
		creatorName: "王晓晴",
		payeeName: "星火文化传媒",
		amount: 6800,
		account: "6217 8890 0021 8832",
		info: "校区春招宣传海报、易拉宝和短视频剪辑费用",
		verifyState: 0,
		verifyStateName: "待审核",
		verifyRemark: "待主管审批",
		verifyStaff: 0,
		verifyTime: "",
		applyTime: "2026-03-02 11:00:00",
		attachFile: "",
		orgId: 1,
		addTime: "2026-03-02 11:00:00",
	},
	3002: {
		id: 3002,
		title: "二月物业费报销",
		type: 2,
		typeName: "物业费",
		creator: 102,
		creatorName: "陈晓楠",
		payeeName: "鑫源物业",
		amount: 3200,
		account: "6222 0900 1138 7721",
		info: "校区二月物业管理及保洁服务费用",
		verifyState: 1,
		verifyStateName: "已通过",
		verifyRemark: "已完成审批并打款",
		verifyStaff: 9001,
		verifyTime: "2026-03-06 10:00:00",
		applyTime: "2026-03-05 09:30:00",
		attachFile: "",
		orgId: 1,
		addTime: "2026-03-05 09:30:00",
	},
	3003: {
		id: 3003,
		title: "教具采购",
		type: 3,
		typeName: "办公耗材",
		creator: 103,
		creatorName: "赵雪",
		payeeName: "优学文具",
		amount: 1260,
		account: "6214 5021 9920 1176",
		info: "新增课堂教具、白板笔和打印纸",
		verifyState: 2,
		verifyStateName: "已驳回",
		verifyRemark: "发票抬头不符合报销要求",
		verifyStaff: 9002,
		verifyTime: "2026-03-12 09:10:00",
		applyTime: "2026-03-11 16:20:00",
		attachFile: "",
		orgId: 1,
		addTime: "2026-03-11 16:20:00",
	},
	3004: {
		id: 3004,
		title: "校区水费",
		type: 4,
		typeName: "水费",
		creator: 104,
		creatorName: "孙慧",
		payeeName: "自来水公司",
		amount: 560,
		account: "6230 0099 2233 1178",
		info: "二月份校区水费缴纳",
		verifyState: 1,
		verifyStateName: "已通过",
		verifyRemark: "正常月度支出",
		verifyStaff: 9001,
		verifyTime: "2026-03-18 15:10:00",
		applyTime: "2026-03-18 08:10:00",
		attachFile: "",
		orgId: 1,
		addTime: "2026-03-18 08:10:00",
	},
};

const mockSaleTrendData: Array<SaleTrendPoint> = [
	{ dates: "2026-03-01", totalCount: 2, totalAmount: 4800, countLessonTotal: 24 },
	{ dates: "2026-03-05", totalCount: 3, totalAmount: 7200, countLessonTotal: 36 },
	{ dates: "2026-03-10", totalCount: 4, totalAmount: 8600, countLessonTotal: 42 },
	{ dates: "2026-03-15", totalCount: 5, totalAmount: 9300, countLessonTotal: 46 },
	{ dates: "2026-03-20", totalCount: 4, totalAmount: 8100, countLessonTotal: 40 },
	{ dates: "2026-03-25", totalCount: 6, totalAmount: 11800, countLessonTotal: 58 },
	{ dates: "2026-03-30", totalCount: 7, totalAmount: 13500, countLessonTotal: 66 },
];

const mockCourseSalesTotalData: Array<CourseSalesTotalPoint> = [
	{ courseId: 1, courseName: "数学压轴训练营", totalCount: 18, totalAmount: 16182, countLessonTotal: 216 },
	{ courseId: 2, courseName: "信息学启蒙营", totalCount: 14, totalAmount: 11186, countLessonTotal: 224 },
	{ courseId: 3, courseName: "地理提分班", totalCount: 12, totalAmount: 8388, countLessonTotal: 144 },
	{ courseId: 4, courseName: "政治时政冲刺班", totalCount: 10, totalAmount: 5990, countLessonTotal: 100 },
	{ courseId: 5, courseName: "创意美术体验课", totalCount: 9, totalAmount: 3591, countLessonTotal: 54 },
];

export async function queryCourseRewardPage(params: CourseRewardQuery) {
	const http = useHttp();
	try {
		const res = await http.get<CourseRewardPage>("/j6-finance/ccf/queryPage", params);
		if (res.data?.rows?.length) {
			return {
				...res.data,
				rows: ensureCourseRewardRowIds(res.data.rows),
			};
		}
	} catch {
		// 本地测试时回退到 mock 数据
	}
	return createMockPage(
		ensureCourseRewardRowIds(mockCourseRewardRows.filter((item) => filterByKeyword(item.teacherName, params.name))),
		params,
	);
}

export async function queryMonthlyClassFeePage(params: MonthlyClassFeeQuery) {
	const http = useHttp();
	try {
		const res = await http.get<MonthlyClassFeePage>("/j6-finance/mcf/queryPage", params);
		if (res.data?.rows?.length) {
			return {
				...res.data,
				rows: ensureMonthlyClassFeeRowIds(res.data.rows),
			};
		}
	} catch {
		// 本地测试时回退到 mock 数据
	}
	return createMockPage(
		ensureMonthlyClassFeeRowIds(
			mockMonthlyClassFeeRows.filter((item) => filterByKeyword(item.teacherName, params.name)),
		),
		params,
	);
}

export async function queryCashoutPage(params: CashoutQuery) {
	const http = useHttp();
	try {
		const res = await http.get<CashoutPage>("/j6-finance/cashout/list", params);
		if (res.data?.rows?.length) return res.data;
	} catch {
		// 本地测试时回退到 mock 数据
	}

	const rows = mockCashoutRows.filter((item) => {
		if (!filterByKeyword(item.title, params.title)) return false;
		if (!filterByKeyword(item.payeeName, params.payeeName)) return false;
		if (params.creator !== undefined && Number(item.creator) !== Number(params.creator)) return false;
		if (params.type !== undefined && Number(item.type) !== Number(params.type)) return false;
		if (params.verifyState !== undefined && Number(item.verifyState) !== Number(params.verifyState)) return false;
		return true;
	});

	return createMockPage(rows, params);
}

export async function queryFundPage(params: FundQuery) {
	const http = useHttp();
	try {
		const res = await http.get<FundPage>("/j6-finance/fund/list", params);
		const rows =
			res.data?.rows?.map((item) => ({
				...item,
				typeName: item.typeName || mapFundTypeName(item.type),
				operatorName: item.operatorName || `经办人${item.operator}`,
				verifyStateName: item.verifyStateName || mapFundVerifyState(item.verifyState),
			})) || [];

		const normalizedRows = rows.map((item) => ({
			...item,
			operatorName:
				item.operatorName && !item.operatorName.includes("{item.operator}")
					? item.operatorName
					: `经办人#${item.operator}`,
		}));
		const page = createPageDTO({
			...res.data,
			rows: normalizedRows,
		});

		if (page.rows?.length) return page;
	} catch {
		// 本地测试时回退到 mock 数据
	}

	const rows = mockFundRows.filter((item) => {
		if (!filterByKeyword(item.title, params.title)) return false;
		if (!filterByKeyword(item.handlerName || item.operatorName, params.handlerName)) return false;
		if (!filterByKeyword(item.payerName, params.payerName)) return false;
		if (params.itemType !== undefined && Number(item.itemType) !== Number(params.itemType)) return false;
		if (params.verifyState !== undefined && Number(item.verifyState) !== Number(params.verifyState)) return false;
		return true;
	});

	return createMockPage(rows, params);
}

export async function getCashoutDetail(id: number) {
	const http = useHttp();
	try {
		const res = await http.get<CashoutDetail>(`/j6/finance/cashout/detail/${id}`);
		if (res.data) return res.data;
	} catch {
		// 本地测试时回退到 mock 数据
	}
	return mockCashoutDetails[id] || mockCashoutDetails[3001];
}

export async function batchPassCashout(payload: CashoutVerifyPayload) {
	const http = useHttp();
	try {
		return await http.post("/j6-finance/cashout/batchPass", payload);
	} catch {
		return Promise.resolve({ data: payload.ids } as any);
	}
}

export async function batchRejectCashout(payload: CashoutVerifyPayload) {
	const http = useHttp();
	try {
		return await http.post("/j6-finance/cashout/batchReject", payload);
	} catch {
		return Promise.resolve({ data: payload.ids } as any);
	}
}

export async function cancelCashout(id: number) {
	const http = useHttp();
	try {
		return await http.put<number>(`/j6/finance/cashout/cancel/${id}`);
	} catch {
		return Promise.resolve({ data: id } as any);
	}
}

export async function confirmFunds(ids: number[]) {
	const http = useHttp();
	try {
		return await http.put<number[]>("/j6-finance/fund/confirm", ids);
	} catch {
		return Promise.resolve({ data: ids } as any);
	}
}

export async function refuseFunds(ids: number[]) {
	const http = useHttp();
	try {
		return await http.put<number[]>("/j6-finance/fund/refuse", ids);
	} catch {
		return Promise.resolve({ data: ids } as any);
	}
}

export async function downloadFunds() {
	const http = useHttp();
	try {
		return await http.getFile("/j6-finance/fund/download");
	} catch {
		return Promise.resolve(undefined);
	}
}

function toDateOnly(v?: string): string | undefined {
	if (!v) return undefined;
	if (v.includes("T")) return v.split("T")[0];
	if (v.includes(" ")) return v.split(" ")[0];
	return v;
}

function toDateTimeWithSpace(v?: string, endOfDay?: boolean): string | undefined {
	if (!v) return undefined;
	if (v.includes(" ")) return v;
	if (v.includes("T")) return v.replace("T", " ");
	return endOfDay ? `${v} 23:59:59` : `${v} 00:00:00`;
}

function toDateTimeWithT(v?: string, endOfDay?: boolean): string | undefined {
	if (!v) return undefined;
	if (v.includes("T")) return v;
	if (v.includes(" ")) return v.replace(" ", "T");
	return endOfDay ? `${v}T23:59:59` : `${v}T00:00:00`;
}

function buildDateQueryVariants(params: {
	startDate?: string;
	endDate?: string;
}): Array<{ startDate?: string; endDate?: string }> {
	return [
		{
			startDate: toDateOnly(params.startDate),
			endDate: toDateOnly(params.endDate),
		},
		{
			startDate: toDateTimeWithSpace(params.startDate, false),
			endDate: toDateTimeWithSpace(params.endDate, true),
		},
		{
			startDate: toDateTimeWithT(params.startDate, false),
			endDate: toDateTimeWithT(params.endDate, true),
		},
	];
}

function unwrapJsonData<T>(payload: unknown): Array<T> {
	if (Array.isArray(payload)) return payload as Array<T>;
	if (!payload || typeof payload !== "object") return [];
	const data = (payload as { data?: unknown }).data;
	return Array.isArray(data) ? (data as Array<T>) : [];
}

export async function querySaleTrend(params: { startDate?: string; endDate?: string }) {
	const http = useHttp();
	const queries = buildDateQueryVariants(params);
	for (const query of queries) {
		try {
			const res = await http.get<unknown>("/j3-statis/courseSaleByDay", query);
			return unwrapJsonData<SaleTrendPoint>(res.data);
		} catch {}
	}
	return filterTrendByRange(mockSaleTrendData, params.startDate, params.endDate);
}

export async function queryCourseSalesTotal(params: { startDate?: string; endDate?: string }) {
	const http = useHttp();
	// try {
	// 	const res = await http.get<CourseSalesTotalPoint[]>("/j3-statis/courseSalesTotal", params);
	// 	if (res.data?.length) return res.data;
	// } catch {
	// 	// 本地测试时回退到 mock 数据
	// }
	const queries = buildDateQueryVariants(params);
	for (const query of queries) {
		try {
			const res = await http.get<unknown>("/j3-statis/courseSalesTotal", query);
			return unwrapJsonData<CourseSalesTotalPoint>(res.data);
		} catch {}
	}
	return mockCourseSalesTotalData;
}

function createMockPage<T>(rows: Array<T>, params: PageQuery): PageDTO<T> {
	const pageIndex = Number(params.pageIndex || 1);
	const pageSize = Number(params.pageSize || 10);
	const total = rows.length;
	const pages = Math.max(1, Math.ceil(total / pageSize));

	return {
		pageIndex,
		pageSize,
		total,
		pages,
		rows: rows.slice((pageIndex - 1) * pageSize, pageIndex * pageSize),
	};
}

function ensureMonthlyClassFeeRowIds(rows: Array<MonthlyClassFeeRow>) {
	return rows.map((item, index) => ({
		...item,
		id: item.id ?? `mcf-${item.teacherName}-${item.month}-${item.classCount}-${item.assistantCount}-${index}`,
	}));
}

function ensureCourseRewardRowIds(rows: Array<CourseRewardRow>) {
	return rows.map((item, index) => ({
		...item,
		id:
			item.id ??
			`ccf-${item.teacherName}-${item.studentName}-${item.courseName}-${item.month}-${item.consumptionCount}-${index}`,
	}));
}

function filterByKeyword(value: string | number | undefined, keyword?: string) {
	if (!keyword) return true;
	return String(value ?? "").includes(String(keyword).trim());
}

function filterTrendByRange(data: Array<SaleTrendPoint>, startDate?: string, endDate?: string) {
	return data.filter((item) => {
		if (startDate && item.dates < startDate) return false;
		if (endDate && item.dates > endDate) return false;
		return true;
	});
}

function mapFundTypeName(type?: number) {
	const map: Record<number, string> = {
		1: "学费",
		2: "教材费",
		3: "活动费",
		4: "其他",
	};
	return type ? map[type] || `类型${type}` : "-";
}

function mapFundVerifyState(state: number) {
	const map: Record<number, string> = {
		0: "审核中",
		1: "已审核",
		2: "已拒绝",
	};
	return map[state] || "-";
}
