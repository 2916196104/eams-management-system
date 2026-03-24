import type { ChartSeriesData } from "@/components/mychart/type";

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
