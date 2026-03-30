import type { ChartSeriesData } from "@/components/mychart/type";
import { useHttp } from "@/plugins/http";

export interface TeachClassHourResult {
	xAxisData: string[];
	seriesData: ChartSeriesData[];
}

interface TeachClassHourRow {
	teacherName: string;
	totalHours: number;
}

export interface TeachScoreRow {
	teacherName: string;
	reviewCount: number;
	compositeScore: number;
	classAtmosphere: number;
	teachingAttitude: number;
	teachingEffect: number;
}

export async function queryTeachClassHour(params: { startDate: string; endDate: string }): Promise<TeachClassHourResult> {
	// Apifox（当前开发）：GET /3/data/class-hour-stats?startDate&endDate
	const http = useHttp();
	const res = await http.get<unknown>("/3/data/class-hour-stats", {
		startDate: params.startDate,
		endDate: params.endDate,
	});

	const raw = res.data;
	// 兼容：可能是数组，也可能是分页对象（rows）
	const rowsRaw: unknown[] = Array.isArray(raw)
		? raw
		: (raw && typeof raw === "object" && Array.isArray((raw as Record<string, unknown>).rows)
				? ((raw as Record<string, unknown>).rows as unknown[])
				: []);

	if (raw === null || raw === undefined) throw new Error("课时统计接口返回为空");

	const rows: TeachClassHourRow[] = rowsRaw
		.map((item) => {
			if (!item || typeof item !== "object") return null;
			const o = item as Record<string, unknown>;
			const teacherName = String(o.teacherName ?? o.name ?? o.label ?? "");
			const totalHours = Number(o.totalHours ?? o.lessonCount ?? o.count ?? o.value ?? 0);
			if (!teacherName) return null;
			return { teacherName, totalHours: Number.isFinite(totalHours) ? totalHours : 0 } as TeachClassHourRow;
		})
		.filter((i): i is TeachClassHourRow => Boolean(i));

	if (!rows.length) {
		return { xAxisData: [], seriesData: [{ name: "课时统计", data: [], color: "#40c9c6" }] };
	}

	return {
		xAxisData: rows.map((i) => i.teacherName),
		seriesData: [{ name: "课时统计", data: rows.map((i) => i.totalHours), color: "#40c9c6" }],
	};
}

export async function queryTeachScoreRank(params: { startDate: string; endDate: string }): Promise<TeachScoreRow[]> {
	// Apifox（当前开发）：GET /3/data
	// 该接口返回 PageDTO：{ pageIndex,pageSize,pages,rows,total }
	const http = useHttp();
	const res = await http.get<unknown>("/3/data", {
		startDate: params.startDate,
		endDate: params.endDate,
		// 后端返回前端只展示第一页；表格仍支持前端三态排序
		pageIndex: 1,
		pageSize: 50,
		sortBy: "evaluationCount",
		sortOrder: "desc",
	});

	const raw = res.data;
	const rowsRaw: unknown[] =
		raw && typeof raw === "object" && Array.isArray((raw as Record<string, unknown>).rows)
			? ((raw as Record<string, unknown>).rows as unknown[])
			: [];

	if (raw === null || raw === undefined) throw new Error("学评教得分排名接口返回为空");

	const rows: TeachScoreRow[] = rowsRaw
		.map((item) => {
			if (!item || typeof item !== "object") return null;
			const o = item as Record<string, unknown>;
			const teacherName = String(o.teacherName ?? o.name ?? "");
			const reviewCount = Number(o.evaluationCount ?? o.reviewCount ?? o.count ?? 0);
			const compositeScore = Number(o.comprehensiveScore ?? o.compositeScore ?? o.score ?? 0);
			const classAtmosphere = Number(o.classroomAtmosphere ?? o.classAtmosphere ?? o.atmosphereScore ?? 0);
			const teachingAttitude = Number(o.teachingAttitude ?? 0);
			const teachingEffect = Number(o.teachingEffect ?? 0);
			if (!teacherName) return null;
			return {
				teacherName,
				reviewCount: Number.isFinite(reviewCount) ? reviewCount : 0,
				compositeScore: Number.isFinite(compositeScore) ? compositeScore : 0,
				classAtmosphere: Number.isFinite(classAtmosphere) ? classAtmosphere : 0,
				teachingAttitude: Number.isFinite(teachingAttitude) ? teachingAttitude : 0,
				teachingEffect: Number.isFinite(teachingEffect) ? teachingEffect : 0,
			} as TeachScoreRow;
		})
		.filter((i): i is TeachScoreRow => Boolean(i));

	if (!rows.length) return [];
	return rows;
}
