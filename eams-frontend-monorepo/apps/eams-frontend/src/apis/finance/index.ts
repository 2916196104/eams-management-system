import { createPageDTO } from "@/apis/type";
import { useHttp } from "@/plugins/http";
import type {
	CashoutDetail,
	CashoutPage,
	CashoutQuery,
	CashoutVerifyPayload,
	CourseRewardPage,
	CourseRewardQuery,
	CourseSalesTotalPoint,
	FundPage,
	FundQuery,
	MonthlyClassFeePage,
	MonthlyClassFeeQuery,
	SaleTrendPoint,
} from "./type";

export async function queryCourseRewardPage(params: CourseRewardQuery) {
	const http = useHttp();
	const res = await http.get<CourseRewardPage>("/j6/ccf/queryPage", params);
	return res.data;
}

export async function queryMonthlyClassFeePage(params: MonthlyClassFeeQuery) {
	const http = useHttp();
	const res = await http.get<MonthlyClassFeePage>("/j6/mcf/queryPage", params);
	return res.data;
}

export async function queryCashoutPage(params: CashoutQuery) {
	const http = useHttp();
	const res = await http.get<CashoutPage>("/j6/finance/cashout/list", params);
	return res.data;
}

export async function queryFundPage(params: FundQuery) {
	const http = useHttp();
	const res = await http.get<FundPage>("/j6/finance/fund", params);
	const rows =
		res.data?.rows?.map((item) => ({
			...item,
			typeName: item.typeName || mapFundTypeName(item.type),
			operatorName: item.operatorName || `经办人#${item.operator}`,
			verifyStateName: item.verifyStateName || mapFundVerifyState(item.verifyState),
		})) || [];
	return createPageDTO({
		...res.data,
		rows,
	});
}

export async function getCashoutDetail(id: number) {
	const http = useHttp();
	const res = await http.get<CashoutDetail>(`/j6/finance/cashout/detail/${id}`);
	return res.data;
}

export async function batchPassCashout(payload: CashoutVerifyPayload) {
	const http = useHttp();
	return http.post("/j6/finance/cashout/batchPass", payload);
}

export async function batchRejectCashout(payload: CashoutVerifyPayload) {
	const http = useHttp();
	return http.post("/j6/finance/cashout/batchReject", payload);
}

export async function cancelCashout(id: number) {
	const http = useHttp();
	return http.put<number>(`/j6/finance/cashout/cancel/${id}`);
}

export async function confirmFunds(ids: number[]) {
	const http = useHttp();
	return http.put<number[]>("/j6/finance/fund/confirm", ids);
}

export async function refuseFunds(ids: number[]) {
	const http = useHttp();
	return http.put<number[]>("/j6/finance/fund/refuse", ids);
}

export async function downloadFunds() {
	const http = useHttp();
	return http.getFile("/j6/finance/fund/download");
}

export async function querySaleTrend(params: { startDate?: string; endDate?: string }) {
	const http = useHttp();
	const res = await http.get<SaleTrendPoint[]>("/common/statis/courseSaleByDay", params);
	return res.data || [];
}

export async function queryCourseSalesTotal(params: { startDate?: string; endDate?: string }) {
	const http = useHttp();
	const res = await http.get<CourseSalesTotalPoint[]>("/common/statis/courseSalesTotal", params);
	return res.data || [];
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
