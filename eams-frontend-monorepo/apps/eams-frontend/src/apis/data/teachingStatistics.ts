import type { ChartSeriesData } from "@/components/mychart/type";
import { useHttp } from "@/plugins/http";

export interface TeachClassHourResult {
	xAxisData: string[];
	seriesData: ChartSeriesData[];
}

export interface TeachScoreRow {
	teacherName: string;
	reviewCount: number;
	compositeScore: number;
	classAtmosphere: number;
	teachingAttitude: number;
	teachingEffect: number;
}

function hashToNumber(str: string) {
	let h = 0;
	for (let i = 0; i < str.length; i++) h = (h * 31 + str.charCodeAt(i)) % 100000;
	return h;
}

const teacherPool = [
	"彭老师",
	"测试",
	"王二麻子",
	"王老师-授课",
	"李老师-助教",
	"杜老师",
	"王助山",
	"duan老师",
	"t001",
	"888",
	"林林源",
	"JSMCygi",
	"test0922",
	"POOKdwfg",
	"张老师",
	"李老师",
	"赵老师",
	"王老师",
	"陈老师",
	"刘老师",
];

export async function queryTeachClassHour(params: { startDate: string; endDate: string }): Promise<TeachClassHourResult> {
	// 文档：GET /app/common/statis/teacherLessonTotal?startDate&endDate
	try {
		const http = useHttp();
		const res = await http.get<unknown>("/app/common/statis/teacherLessonTotal", {
			startDate: params.startDate,
			endDate: params.endDate,
		});
		const raw = res.data;
		if (Array.isArray(raw)) {
			const rows = raw
				.map((item) => {
					if (!item || typeof item !== "object") return null;
					const o = item as Record<string, unknown>;
					const name = String(o.teacherName ?? o.name ?? o.label ?? "");
					const value = Number(o.lessonCount ?? o.count ?? o.value ?? 0);
					if (!name) return null;
					return { name, value: Number.isFinite(value) ? value : 0 };
				})
				.filter((i): i is { name: string; value: number } => Boolean(i))
				.slice(0, 20);

			return {
				xAxisData: rows.map((i) => i.name),
				seriesData: [{ name: "课时统计", data: rows.map((i) => i.value), color: "#40c9c6" }],
			};
		}
	} catch {
		// ignore -> fallback mock
	}

	const seed = hashToNumber(`${params.startDate}-${params.endDate}`);
	const xAxisData = [...teacherPool];
	const data = xAxisData.map((_, i) => Math.max(20, 920 - i * 45 + ((seed + i * 19) % 60)));

	return new Promise((resolve) =>
		setTimeout(
			() =>
				resolve({
					xAxisData,
					seriesData: [{ name: "课时统计", data, color: "#40c9c6" }],
				}),
			420,
		),
	);
}

export async function queryTeachScoreRank(params: { startDate: string; endDate: string }): Promise<TeachScoreRow[]> {
	// 文档：GET /app/common/lesson/teachEvaluate（分页）但文档缺 records 字段结构
	// 这里先做兼容解析，失败则回退 mock，等你后续 Apifox 给到 records 示例再严格对齐字段。
	try {
		const http = useHttp();
		const res = await http.get<unknown>("/app/common/lesson/teachEvaluate", {
			startDate: params.startDate,
			endDate: params.endDate,
			page: 1,
			pageSize: 50,
		});
		const raw = res.data;
		const records = (raw && typeof raw === "object" ? (raw as Record<string, unknown>).records : null) as unknown;
		if (Array.isArray(records)) {
			return records
				.map((item) => {
					if (!item || typeof item !== "object") return null;
					const o = item as Record<string, unknown>;
					const teacherName = String(o.teacherName ?? o.name ?? "");
					if (!teacherName) return null;
					return {
						teacherName,
						reviewCount: Number(o.reviewCount ?? o.count ?? 0),
						compositeScore: Number(o.compositeScore ?? o.score ?? 0),
						classAtmosphere: Number(o.classAtmosphere ?? o.atmosphereScore ?? 0),
						teachingAttitude: Number(o.teachingAttitude ?? o.attitudeScore ?? 0),
						teachingEffect: Number(o.teachingEffect ?? o.effectScore ?? 0),
					} as TeachScoreRow;
				})
				.filter((i): i is TeachScoreRow => Boolean(i));
		}
	} catch {
		// ignore -> fallback mock
	}

	const seed = hashToNumber(`${params.startDate}-${params.endDate}-score`);
	const rows = teacherPool.slice(0, 12).map((teacherName, i) => {
		const base = 5 - ((seed + i * 7) % 3) * 0.5;
		return {
			teacherName,
			reviewCount: 1 + ((seed + i * 3) % 3),
			compositeScore: Number(base.toFixed(1)),
			classAtmosphere: Number((base - ((i + 1) % 2) * 0.5).toFixed(1)),
			teachingAttitude: Number((base - (i % 2) * 0.5).toFixed(1)),
			teachingEffect: Number((base - ((i + 2) % 2) * 0.5).toFixed(1)),
		};
	});

	return new Promise((resolve) => setTimeout(() => resolve(rows), 420));
}
