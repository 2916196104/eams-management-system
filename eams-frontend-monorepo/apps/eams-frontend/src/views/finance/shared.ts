import type { PageDTO } from "@/apis/type";
import type { MyTableColumn, MyTableOperationsBtn } from "@/components/mytable/type";
import { createMyTableOperationsColumn } from "@/components/mytable/type";
import {
	batchPassCashout,
	batchRejectCashout,
	cancelCashout,
	confirmFunds,
	downloadFunds,
	getCashoutDetail,
	queryCashoutPage,
	queryCourseRewardPage,
	queryFundPage,
	queryMonthlyClassFeePage,
	refuseFunds,
} from "@/apis/finance";

export interface FinanceFilterOption {
	label: string;
	value: string | number;
}

export interface FinanceFilterField {
	prop: string;
	label: string;
	type: "input" | "select" | "date";
	placeholder: string;
	options?: FinanceFilterOption[];
}

export interface FinanceActionButton {
	key: string;
	label: string;
	type?: "primary" | "success" | "warning" | "danger" | "info";
}

export interface FinanceListConfig<T extends Record<string, any>> {
	title: string;
	description?: string;
	filters: FinanceFilterField[];
	initialFilters: Record<string, any>;
	batchActions?: FinanceActionButton[];
	columns: MyTableColumn[];
	rows?: T[];
	operationButtons?: MyTableOperationsBtn[];
	loadPage?: (params: Record<string, any>) => Promise<PageDTO<T> | undefined>;
	batchActionHandler?: (key: string, rows: T[]) => Promise<string>;
	operationHandler?: (evtname: string, row: T) => Promise<string>;
	exportHandler?: (params: Record<string, any>) => Promise<string>;
}

const paymentStatusOptions: FinanceFilterOption[] = [
	{ label: "审核中", value: 0 },
	{ label: "已审核", value: 1 },
	{ label: "已拒绝", value: 2 },
];

const paymentTypeOptions: FinanceFilterOption[] = [
	{ label: "学费", value: 1 },
	{ label: "教材费", value: 2 },
	{ label: "活动费", value: 3 },
	{ label: "其他", value: 4 },
];

const requestStatusOptions: FinanceFilterOption[] = [
	{ label: "待审核", value: 0 },
	{ label: "已通过", value: 1 },
	{ label: "已驳回", value: 2 },
];

const requestTypeOptions: FinanceFilterOption[] = [
	{ label: "广告宣传", value: 1 },
	{ label: "物业费", value: 2 },
	{ label: "办公耗材", value: 3 },
	{ label: "水费", value: 4 },
	{ label: "差旅费", value: 5 },
	{ label: "其他", value: 6 },
];

export const paymentManagementConfig: FinanceListConfig<Record<string, any>> = {
	title: "款项管理",
	filters: [
		{ prop: "title", label: "标题", type: "input", placeholder: "请输入标题" },
		{ prop: "handlerName", label: "经办人", type: "input", placeholder: "请输入经办人" },
		{ prop: "payerName", label: "付款人", type: "input", placeholder: "请输入付款人" },
		{
			prop: "verifyState",
			label: "认款状态",
			type: "select",
			placeholder: "请选择认款状态",
			options: paymentStatusOptions,
		},
		{ prop: "itemType", label: "款项类型", type: "select", placeholder: "请选择款项类型", options: paymentTypeOptions },
	],
	initialFilters: {
		title: "",
		handlerName: "",
		payerName: "",
		verifyState: "",
		itemType: "",
	},
	batchActions: [
		{ key: "confirm", label: "批量认款", type: "primary" },
		{ key: "reject", label: "批量拒绝", type: "danger" },
	],
	columns: [
		{ prop: "typeName", label: "款项类型", "min-width": 140 },
		{ prop: "title", label: "标题", "min-width": 180 },
		{ prop: "amount", label: "金额", width: "120px" },
		{ prop: "studentName", label: "学员", "min-width": 120 },
		{ prop: "operatorName", label: "经办人", "min-width": 120 },
		{ prop: "remark", label: "备注说明", "min-width": 220, "show-overflow-tooltip": true },
		{ prop: "submit_time", label: "提交时间", "min-width": 180 },
		{ prop: "verifyStateName", label: "认款状态", "min-width": 120 },
		{ prop: "verifyRemark", label: "认款信息", "min-width": 220, "show-overflow-tooltip": true },
	],
	loadPage: async (params) =>
		queryFundPage({
			title: params.title,
			handlerName: params.handlerName,
			payerName: params.payerName,
			itemType: params.itemType === "" ? undefined : Number(params.itemType),
			verifyState: params.verifyState === "" ? undefined : Number(params.verifyState),
			pageIndex: params.pageIndex,
			pageSize: params.pageSize,
		}),
	batchActionHandler: async (key, rows) => {
		const ids = rows.map((row) => Number(row.id));
		if (key === "confirm") {
			await confirmFunds(ids);
			return `已批量认款 ${rows.length} 条记录`;
		}
		await refuseFunds(ids);
		return `已批量拒绝 ${rows.length} 条记录`;
	},
	exportHandler: async () => {
		await downloadFunds();
		return "已触发款项管理导出";
	},
};

export const monthlyClassFeeConfig: FinanceListConfig<Record<string, any>> = {
	title: "月课时费",
	description: "按授课次数统计已结课的课时费，支持导出。",
	filters: [
		{ prop: "name", label: "姓名", type: "input", placeholder: "请输入老师姓名" },
		{ prop: "startDate", label: "开始日期", type: "date", placeholder: "请选择开始日期" },
		{ prop: "endDate", label: "结束日期", type: "date", placeholder: "请选择结束日期" },
	],
	initialFilters: {
		name: "",
		startDate: "",
		endDate: "",
	},
	columns: [
		{ prop: "teacherName", label: "姓名", "min-width": 120 },
		{ prop: "month", label: "月份", "min-width": 100 },
		{ prop: "singleClassFee", label: "单节上课费", "min-width": 130 },
		{ prop: "classCount", label: "上课课次数", "min-width": 120 },
		{ prop: "classFeeSubtotal", label: "上课费小计", "min-width": 140 },
		{ prop: "singleAssistantFee", label: "单节助教费", "min-width": 130 },
		{ prop: "assistantCount", label: "助教课次数", "min-width": 120 },
		{ prop: "assistantFeeSubtotal", label: "助教费小计", "min-width": 140 },
	],
	loadPage: async (params) =>
		queryMonthlyClassFeePage({
			name: params.name,
			startTime: params.startDate,
			endTime: params.endDate,
			pageIndex: params.pageIndex,
			pageSize: params.pageSize,
		}),
};

export const courseRewardConfig: FinanceListConfig<Record<string, any>> = {
	title: "消课课酬",
	description: "按消课次数统计老师的课酬，支持导出。",
	filters: [
		{ prop: "name", label: "姓名", type: "input", placeholder: "请输入老师姓名" },
		{ prop: "startDate", label: "开始日期", type: "date", placeholder: "请选择开始日期" },
		{ prop: "endDate", label: "结束日期", type: "date", placeholder: "请选择结束日期" },
	],
	initialFilters: {
		name: "",
		startDate: "",
		endDate: "",
	},
	columns: [
		{ prop: "teacherName", label: "老师名", "min-width": 120 },
		{ prop: "month", label: "月份", "min-width": 100 },
		{ prop: "studentName", label: "学生名", "min-width": 120 },
		{ prop: "courseName", label: "课程名", "min-width": 160 },
		{ prop: "consumptionCount", label: "消课数", "min-width": 100 },
		{ prop: "feePerClass", label: "单节课酬", "min-width": 120 },
		{ prop: "feeSubtotal", label: "消课课酬小计", "min-width": 150 },
	],
	loadPage: async (params) =>
		queryCourseRewardPage({
			name: params.name,
			startTime: params.startDate,
			endTime: params.endDate,
			pageIndex: params.pageIndex,
			pageSize: params.pageSize,
		}),
};

export const requestManagementConfig: FinanceListConfig<Record<string, any>> = {
	title: "请款管理",
	filters: [
		{ prop: "title", label: "请款项目", type: "input", placeholder: "请输入请款项目" },
		{ prop: "type", label: "请款类型", type: "select", placeholder: "请选择请款类型", options: requestTypeOptions },
		{ prop: "creator", label: "申请人ID", type: "input", placeholder: "请输入申请人ID" },
		{ prop: "payeeName", label: "收款人", type: "input", placeholder: "请输入收款人" },
		{
			prop: "verifyState",
			label: "审核状态",
			type: "select",
			placeholder: "请选择审核状态",
			options: requestStatusOptions,
		},
		{ prop: "startDate", label: "开始日期", type: "date", placeholder: "请选择开始日期" },
		{ prop: "endDate", label: "结束日期", type: "date", placeholder: "请选择结束日期" },
	],
	initialFilters: {
		title: "",
		type: "",
		creator: "",
		payeeName: "",
		verifyState: "",
		startDate: "",
		endDate: "",
	},
	batchActions: [
		{ key: "approve", label: "批量通过", type: "primary" },
		{ key: "return", label: "批量驳回", type: "danger" },
	],
	columns: [
		createMyTableOperationsColumn({ label: "操作", "min-width": 180, align: "center" }),
		{ prop: "title", label: "请款项目", "min-width": 180 },
		{ prop: "typeName", label: "款项类型", "min-width": 120 },
		{ prop: "creatorName", label: "申请人", "min-width": 120 },
		{ prop: "payeeName", label: "收款人", "min-width": 120 },
		{ prop: "amount", label: "请款金额", "min-width": 120 },
		{ prop: "addTime", label: "申请时间", "min-width": 180 },
		{ prop: "account", label: "收款账号", "min-width": 180 },
		{ prop: "info", label: "请款说明", "min-width": 220, "show-overflow-tooltip": true },
		{ prop: "verifyStateName", label: "审核状态", "min-width": 120 },
		{ prop: "verifyRemark", label: "审核信息", "min-width": 220, "show-overflow-tooltip": true },
	],
	operationButtons: [
		{ evtname: "detail", text: "详情", attr: { type: "primary", link: true } },
		{ evtname: "approve", text: "通过", attr: { type: "success", link: true } },
		{ evtname: "reject", text: "驳回", attr: { type: "danger", link: true } },
		{ evtname: "cancel", text: "作废", attr: { type: "info", link: true } },
	],
	loadPage: async (params) =>
		queryCashoutPage({
			title: params.title,
			type: params.type === "" ? undefined : Number(params.type),
			creator: params.creator ? Number(params.creator) : undefined,
			payeeName: params.payeeName,
			verifyState: params.verifyState === "" ? undefined : Number(params.verifyState),
			startDate: params.startDate,
			endDate: params.endDate,
			pageIndex: params.pageIndex,
			pageSize: params.pageSize,
		}),
	batchActionHandler: async (key, rows) => {
		const ids = rows.map((row) => Number(row.id));
		if (key === "approve") {
			await batchPassCashout({ ids, verifyState: 1 });
			return `已批量通过 ${rows.length} 条请款`;
		}
		await batchRejectCashout({
			ids,
			verifyState: 2,
			verifyRemark: "前端默认驳回，请补充审核备注",
		});
		return `已批量驳回 ${rows.length} 条请款`;
	},
	operationHandler: async (evtname, row) => {
		const id = Number(row.id);
		if (evtname === "detail") {
			const detail = await getCashoutDetail(id);
			if (!detail) return "未查询到请款详情";
			return [
				`项目：${detail.title}`,
				`类型：${detail.typeName}`,
				`申请人：${detail.creatorName}`,
				`收款人：${detail.payeeName}`,
				`金额：${detail.amount}`,
				`状态：${detail.verifyStateName}`,
				`备注：${detail.verifyRemark || "无"}`,
			].join("\n");
		}
		if (evtname === "approve") {
			await batchPassCashout({ ids: [id], verifyState: 1 });
			return `已通过请款：${row.title}`;
		}
		if (evtname === "reject") {
			await batchRejectCashout({
				ids: [id],
				verifyState: 2,
				verifyRemark: "前端默认驳回，请补充审核备注",
			});
			return `已驳回请款：${row.title}`;
		}
		await cancelCashout(id);
		return `已作废请款：${row.title}`;
	},
};
