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

function unwrapData(raw: unknown): unknown {
	if (!raw || typeof raw !== "object") return raw;
	const data = (raw as { data?: unknown }).data;
	if (data === undefined) return raw;
	return data;
}

export async function queryTeachClassHour(params: { startDate: string; endDate: string }): Promise<TeachClassHourResult> {
	const http = useHttp();
	const res = await http.get<unknown>("/j3-statis/class-hour-stats", {
		startDate: params.startDate,
		endDate: params.endDate,
		pageIndex: 1,
		pageSize: 10,
	});

	const raw = unwrapData(res.data);
	const rowsRaw: unknown[] = Array.isArray(raw)
		? raw
		: raw && typeof raw === "object" && Array.isArray((raw as Record<string, unknown>).rows)
			? ((raw as Record<string, unknown>).rows as unknown[])
			: [];

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

	return {
		xAxisData: rows.map((i) => i.teacherName),
		seriesData: [{ name: "课时统计", data: rows.map((i) => i.totalHours), color: "#40c9c6" }],
	};
}

export async function queryTeachScoreRank(params: { startDate: string; endDate: string }): Promise<TeachScoreRow[]> {
	const http = useHttp();
	const res = await http.get<unknown>("/j3-statis/teachevaluation", {
		startDate: params.startDate,
		endDate: params.endDate,
		pageIndex: 1,
		pageSize: 10,
		sortBy: "evaluationCount",
		sortOrder: "desc",
	});

	const raw = unwrapData(res.data);
	const rowsRaw: unknown[] =
		raw && typeof raw === "object" && Array.isArray((raw as Record<string, unknown>).rows)
			? ((raw as Record<string, unknown>).rows as unknown[])
			: [];

	if (raw === null || raw === undefined) throw new Error("学评教得分排行接口返回为空");

	return rowsRaw
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
}
