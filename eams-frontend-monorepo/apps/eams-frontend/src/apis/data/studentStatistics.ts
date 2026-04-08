import type { FunnelSeriesItem } from "@/components/mychart/FunnelChart.vue";
import type { ChartSeriesData } from "@/components/mychart/type";
import { useHttp } from "@/plugins/http";

export interface ScorePieItem {
	name: string;
	value: number;
	color?: string;
}

export interface LeadTrendResult {
	xAxisData: Array<string>;
	seriesData: ChartSeriesData[];
}

export interface ClassHourRankResult {
	xAxisData: Array<string>;
	seriesData: ChartSeriesData[];
}

export interface StudentAgeCompositionItem {
	age: string;
	count: number;
}

function hashToNumber(str: string): number {
	let h = 0;
	for (const ch of str) h = (h * 31 + ch.charCodeAt(0)) % 100000;
	return h;
}

function mockMonth(month: string): { stage: FunnelSeriesItem[]; score: ScorePieItem[] } {
	const seed = hashToNumber(month);
	return {
		stage: [
			{ name: "目标客户阶段", value: 1800 + (seed % 200), color: "#2bb8c6" },
			{ name: "潜在客户阶段", value: 1200 + (seed % 180), color: "#7a6bd7" },
			{ name: "意向阶段", value: 680 + (seed % 150), color: "#3b9cff" },
			{ name: "认可阶段", value: 420 + (seed % 120), color: "#f2a65a" },
			{ name: "签约阶段", value: 300 + (seed % 100), color: "#e46a74" },
			{ name: "售后阶段", value: 180 + (seed % 80), color: "#8a93b0" },
		],
		score: [
			{ name: "90-100分", value: 90 + (seed % 20), color: "#2bb8c6" },
			{ name: "80-89分", value: 180 + (seed % 30), color: "#7a6bd7" },
			{ name: "70-79分", value: 230 + (seed % 35), color: "#3b9cff" },
			{ name: "60-69分", value: 120 + (seed % 20), color: "#f2a65a" },
			{ name: "60分以下", value: 40 + (seed % 10), color: "#e46a74" },
		],
	};
}

function toDateTimeRange(params: { startDate: string; endDate: string }): { beginTime: string; endTime: string } {
	const beginTime = params.startDate.includes("T") ? params.startDate : `${params.startDate} 00:00:00`;
	const endTime = params.endDate.includes("T") ? params.endDate : `${params.endDate} 23:59:59`;
	return { beginTime, endTime };
}

function unwrapData(raw: unknown): unknown {
	if (!raw || typeof raw !== "object") return raw;
	const data = (raw as { data?: unknown }).data;
	if (data === undefined) return raw;
	return data;
}

export async function queryStudentFunnelByMonth(params: { month: string }): Promise<FunnelSeriesItem[]> {
	void params;
	const http = useHttp();
	const res = await http.get<unknown>("/j3-statis/sales-funnel");
	const raw = unwrapData(res.data);
	if (!Array.isArray(raw)) throw new Error("销售漏斗接口返回格式不正确");

	const mapped = raw
		.map((item) => {
			if (!item || typeof item !== "object") return null;
			const o = item as Record<string, unknown>;
			const name = (o.name ?? o.stageName ?? o.label) as string | undefined;
			const value = Number(o.value ?? o.count ?? o.num ?? 0);
			const code = Number(o.code ?? o.stageCode ?? -1);
			if (!name) return null;
			return { name, value, _code: Number.isFinite(code) ? code : -1 } as FunnelSeriesItem & { _code: number };
		})
		.filter((i): i is FunnelSeriesItem & { _code: number } => Boolean(i));

	const hasCode = mapped.some((i) => i._code >= 0);
	const sorted = hasCode ? [...mapped].sort((a, b) => a._code - b._code) : mapped;
	return sorted.map(({ _code, ...rest }) => rest);
}

export async function queryStudentScorePieByMonth(params: { month: string }): Promise<ScorePieItem[]> {
	const mock = mockMonth(params.month);
	return new Promise((resolve) => setTimeout(() => resolve(mock.score), 450));
}

export async function queryStudentAgeComposition(): Promise<StudentAgeCompositionItem[]> {
	const http = useHttp();
	const res = await http.get<unknown>("/j3-statis/student-age-composition");
	const raw = unwrapData(res.data);
	if (!Array.isArray(raw)) throw new Error("年龄构成接口返回格式不正确");

	return raw
		.map((item) => {
			if (!item || typeof item !== "object") return null;
			const o = item as Record<string, unknown>;
			const age = String(o.age ?? "");
			const count = Number(o.count ?? o.value ?? 0);
			if (!age) return null;
			return { age, count: Number.isFinite(count) ? count : 0 } as StudentAgeCompositionItem;
		})
		.filter((i): i is StudentAgeCompositionItem => Boolean(i));
}

export async function queryLeadTrend(params: { startDate: string; endDate: string }): Promise<LeadTrendResult> {
	const http = useHttp();
	const range = toDateTimeRange(params);
	const res = await http.get<unknown>("/j3-static/newStudentCounts", {
		beginTime: range.beginTime,
		endTime: range.endTime,
	});
	const raw = unwrapData(res.data);
	if (!Array.isArray(raw)) throw new Error("新增学员趋势接口返回格式不正确");

	const rows = raw
		.map((item) => {
			if (!item || typeof item !== "object") return null;
			const o = item as Record<string, unknown>;
			const x = String(o.date ?? o.day ?? o.statDate ?? "");
			const y = Number(o.count ?? o.value ?? o.num ?? 0);
			if (!x) return null;
			return { x, y: Number.isFinite(y) ? y : 0 };
		})
		.filter((item): item is { x: string; y: number } => Boolean(item));

	return {
		xAxisData: rows.map((i) => i.x),
		seriesData: [{ name: "新增线索", data: rows.map((i) => i.y), color: "#e91e63" }],
	};
}

export async function queryClassHourRank(params: { startDate: string; endDate: string; top?: number }): Promise<ClassHourRankResult> {
	const http = useHttp();
	const range = toDateTimeRange(params);
	const res = await http.get<unknown>("/j3-static/studentLessonCounts", {
		beginTime: range.beginTime,
		endTime: range.endTime,
	});
	const raw = unwrapData(res.data);
	if (!Array.isArray(raw)) throw new Error("学员课时排行接口返回格式不正确");

	const rows = raw
		.map((item) => {
			if (!item || typeof item !== "object") return null;
			const o = item as Record<string, unknown>;
			const name = String(o.studentName ?? o.name ?? o.label ?? "");
			const value = Number(o.lessonCount ?? o.count ?? o.value ?? 0);
			if (!name) return null;
			return { name, value: Number.isFinite(value) ? value : 0 };
		})
		.filter((i): i is { name: string; value: number } => Boolean(i));

	const top = params.top ?? 10;
	const sliced = rows.slice(0, top);
	return {
		xAxisData: sliced.map((i) => i.name),
		seriesData: [{ name: "课时数", data: sliced.map((i) => i.value), color: "#40c9c6" }],
	};
}
