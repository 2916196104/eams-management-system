import type { PageDTO, PageQuery } from "@/apis/type";

export interface CourseRewardQuery extends PageQuery {
	name?: string;
	startTime?: string;
	endTime?: string;
}

export interface MonthlyClassFeeQuery extends PageQuery {
	name?: string;
	startTime?: string;
	endTime?: string;
}

export interface MonthlyClassFeeRow {
	assistantCount: number;
	assistantFeeSubtotal: number;
	classCount: number;
	classFeeSubtotal: number;
	id?: number | string;
	month: string;
	singleAssistantFee: number;
	singleClassFee: number;
	teacherName: string;
}

export interface CourseRewardRow {
	consumptionCount: number;
	courseName: string;
	feePerClass: number;
	feeSubtotal: number;
	id?: number | string;
	month: string;
	studentName: string;
	teacherName: string;
}

export interface CashoutQuery extends PageQuery {
	creator?: number;
	endDate?: string;
	payeeName?: string;
	startDate?: string;
	title?: string;
	type?: number;
	verifyState?: number;
}

export interface CashoutRow {
	account: string;
	addTime: string;
	amount: number;
	creator: number;
	creatorName: string;
	id: number;
	info: string;
	payeeName: string;
	title: string;
	type: number;
	typeName: string;
	verifyRemark: string;
	verifyState: number;
	verifyStateName: string;
}

export interface CashoutDetail {
	account: string;
	amount: number;
	applyTime: string;
	attachFile: string;
	creator: number;
	creatorName: string;
	id: number;
	info: string;
	orgId: number;
	payeeName: string;
	title: string;
	type: number;
	typeName: string;
	verifyRemark: string;
	verifyStaff: number;
	verifyState: number;
	verifyStateName: string;
	verifyTime: string;
}

export interface CashoutVerifyPayload {
	ids: number[];
	verifyRemark?: string;
	verifyState: number;
}

export interface FundQuery extends PageQuery {
	handlerName?: string;
	itemType?: number;
	payerName?: string;
	title?: string;
	verifyState?: number;
}

export interface FundRow {
	amount: number;
	id: number;
	operator: number;
	operatorName?: string;
	remark?: string;
	studentName: string;
	submit_time?: string;
	title: string;
	type?: number;
	typeName?: string;
	verifyRemark?: string;
	verifyState: number;
	verifyStateName?: string;
}

export interface SaleTrendPoint {
	countLessonTotal: number;
	dates: string;
	totalAmount: number;
	totalCount: number;
}

export interface CourseSalesTotalPoint {
	countLessonTotal: number;
	courseId: number;
	courseName: string;
	totalAmount: number;
	totalCount: number;
}

export type CourseRewardPage = PageDTO<CourseRewardRow>;
export type MonthlyClassFeePage = PageDTO<MonthlyClassFeeRow>;
export type CashoutPage = PageDTO<CashoutRow>;
export type FundPage = PageDTO<FundRow>;
