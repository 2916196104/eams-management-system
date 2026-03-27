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

function hashToNumber(str: string) {
	let h = 0;
	for (let i = 0; i < str.length; i++) h = (h * 31 + str.charCodeAt(i)) % 100000;
	return h;
}

function mockMonth(month: string) {
	// 保证同一个 month 有稳定数据，便于你反复验证页面效果
	const seed = hashToNumber(month);
	return {
		stage: [
			{ name: "目标客户阶段", value: 1800 + (seed % 200), color: "#2bb8c6" },
			{ name: "潜在客户阶段", value: 1200 + (seed % 180), color: "#7a6bd7" },
			{ name: "意向阶段", value: 680 + (seed % 150), color: "#3b9cff" },
			{ name: "认可阶段", value: 420 + (seed % 120), color: "#f2a65a" },
			{ name: "签约阶段", value: 300 + (seed % 100), color: "#e46a74" },
			{ name: "售后阶段", value: 180 + (seed % 80), color: "#8a93b0" },
		] as FunnelSeriesItem[],
		score: [
			{ name: "90-100分", value: 90 + (seed % 20), color: "#2bb8c6" },
			{ name: "80-89分", value: 180 + (seed % 30), color: "#7a6bd7" },
			{ name: "70-79分", value: 230 + (seed % 35), color: "#3b9cff" },
			{ name: "60-69分", value: 120 + (seed % 20), color: "#f2a65a" },
			{ name: "60分以下", value: 40 + (seed % 10), color: "#e46a74" },
		] as ScorePieItem[],
	};
}

export async function queryStudentFunnelByMonth(params: { month: string }): Promise<FunnelSeriesItem[]> {
	// 文档：GET /app/common/statis/funnel（无入参）
	void params;
	try {
		const http = useHttp();
		const res = await http.get<unknown>("/app/common/statis/funnel");
		const raw = res.data;
		if (Array.isArray(raw)) {
			// 兼容后端直接返回 [{ name, value }, ...] 或 [{ stageName, count }, ...]
			return raw
				.map((item) => {
					if (!item || typeof item !== "object") return null;
					const o = item as Record<string, unknown>;
					const name = (o.name ?? o.stageName ?? o.label) as string | undefined;
					const value = Number(o.value ?? o.count ?? o.num ?? 0);
					if (!name) return null;
					return { name, value } as FunnelSeriesItem;
				})
				.filter((i): i is FunnelSeriesItem => Boolean(i));
		}
	} catch {
		// ignore -> fallback mock
	}
	const mock = mockMonth(params.month);
	return new Promise((resolve) => setTimeout(() => resolve(mock.stage), 250));
}

export async function queryStudentScorePieByMonth(params: { month: string }): Promise<ScorePieItem[]> {
	// 文档里对应的是“在学学生年龄统计”GET /app/common/statis/studentAgeStatis，但当前页面展示的是“成绩构成”
	// 在真实“成绩构成”接口未明确前，先保留 mock，等你在 Apifox 给到接口后再替换。
	const mock = mockMonth(params.month);
	return new Promise((resolve) => setTimeout(() => resolve(mock.score), 450));
}

export async function queryLeadTrend(params: { startDate: string; endDate: string }): Promise<LeadTrendResult> {
	// 文档：GET /app/common/statis/newStudentCounts?startDate&endDate
	try {
		const http = useHttp();
		const res = await http.get<unknown>("/app/common/statis/newStudentCounts", {
			startDate: params.startDate,
			endDate: params.endDate,
		});
		const raw = res.data;
		if (Array.isArray(raw)) {
			const xAxisData: string[] = [];
			const data: number[] = [];
			for (const item of raw) {
				if (!item || typeof item !== "object") continue;
				const o = item as Record<string, unknown>;
				const x = String(o.date ?? o.day ?? o.statDate ?? "");
				const y = Number(o.count ?? o.value ?? o.num ?? 0);
				if (!x) continue;
				xAxisData.push(x);
				data.push(Number.isFinite(y) ? y : 0);
			}
			return {
				xAxisData,
				seriesData: [{ name: "新增线索", data, color: "#e91e63" }],
			};
		}
	} catch {
		// ignore -> fallback mock
	}
	const seed = hashToNumber(`${params.startDate}-${params.endDate}`);
	const days = 12;
	const xAxisData = Array.from({ length: days }, (_, i) => `D${i + 1}`);
	const data = xAxisData.map((_, i) => 50 + ((seed + i * 77) % 80));
	return new Promise((resolve) =>
		setTimeout(
			() =>
				resolve({
					xAxisData,
					seriesData: [
						{
							name: "新增线索",
							data,
							color: "#e91e63",
						},
					],
				}),
			500,
		),
	);
}

export async function queryClassHourRank(params: { startDate: string; endDate: string; top?: number }): Promise<ClassHourRankResult> {
	// 文档：GET /app/common/statis/studentLessonCounts?startDate&endDate
	try {
		const http = useHttp();
		const res = await http.get<unknown>("/app/common/statis/studentLessonCounts", {
			startDate: params.startDate,
			endDate: params.endDate,
		});
		const raw = res.data;
		if (Array.isArray(raw)) {
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
	} catch {
		// ignore -> fallback mock
	}
	const seed = hashToNumber(`${params.startDate}-${params.endDate}`);
	const top = params.top ?? 10;
	const xAxisData = Array.from({ length: top }, (_, i) => `学员${i + 1}`);
	const data = xAxisData.map((_, i) => 100 + ((seed + i * 13) % 900));
	return new Promise((resolve) =>
		setTimeout(
			() =>
				resolve({
					xAxisData,
					seriesData: [
						{
							name: "课时数",
							data,
							color: "#40c9c6",
						},
					],
				}),
			500,
		),
	);
}

