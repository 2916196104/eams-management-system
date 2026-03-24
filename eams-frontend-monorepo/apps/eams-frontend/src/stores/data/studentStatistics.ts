import { defineStore } from "pinia";
import { queryClassHourRank, queryLeadTrend, queryStudentFunnelByMonth, queryStudentScorePieByMonth } from "@/apis/data/studentStatistics";
import type { FunnelSeriesItem } from "@/components/mychart/FunnelChart.vue";
import type { ClassHourRankResult, LeadTrendResult, ScorePieItem } from "@/apis/data/studentStatistics";

type DateRange = { startDate: string; endDate: string };

const STORAGE_KEY = "student-statistics-filters:v1";

function pad2(n: number) {
	return String(n).padStart(2, "0");
}

function formatDate(d: Date) {
	return `${d.getFullYear()}-${pad2(d.getMonth() + 1)}-${pad2(d.getDate())}`;
}

function defaultLast7Days(): DateRange {
	const end = new Date();
	const start = new Date(end);
	start.setDate(start.getDate() - 6);
	return { startDate: formatDate(start), endDate: formatDate(end) };
}

function defaultMonthStr(): string {
	const d = new Date();
	return `${d.getFullYear()}-${pad2(d.getMonth() + 1)}`;
}

interface StudentStatisticsState {
	month: string;
	leadRange: DateRange;
	rankRange: DateRange;

	funnelStages: FunnelSeriesItem[];
	scorePieData: ScorePieItem[];
	leadTrend: LeadTrendResult | null;
	classHourRank: ClassHourRankResult | null;

	loading: {
		funnel: boolean;
		age: boolean;
		leadTrend: boolean;
		classHourRank: boolean;
	};
	error: string | null;
}

function loadStateFromStorage(): Partial<StudentStatisticsState> {
	try {
		const raw = localStorage.getItem(STORAGE_KEY);
		if (!raw) return {};
		return JSON.parse(raw);
	} catch {
		return {};
	}
}

function saveStateToStorage(state: Pick<StudentStatisticsState, "month" | "leadRange" | "rankRange">) {
	try {
		localStorage.setItem(STORAGE_KEY, JSON.stringify(state));
	} catch {
		// 忽略 localStorage 写入异常
	}
}

export const useStudentStatisticsStore = defineStore("studentStatistics", {
	state: (): StudentStatisticsState => ({
		month: defaultMonthStr(),
		leadRange: defaultLast7Days(),
		rankRange: defaultLast7Days(),

		funnelStages: [],
		scorePieData: [],
		leadTrend: null,
		classHourRank: null,

		loading: {
			funnel: false,
			age: false,
			leadTrend: false,
			classHourRank: false,
		},
		error: null,
	}),
	actions: {
		initFilters() {
			const partial = loadStateFromStorage();
			if (partial.month) this.month = partial.month;
			if (partial.leadRange?.startDate && partial.leadRange?.endDate) this.leadRange = partial.leadRange;
			if (partial.rankRange?.startDate && partial.rankRange?.endDate) this.rankRange = partial.rankRange;
		},
		setMonth(month: string) {
			this.month = month;
			saveStateToStorage({ month: this.month, leadRange: this.leadRange, rankRange: this.rankRange });
		},
		setLeadRange(range: DateRange) {
			this.leadRange = range;
			saveStateToStorage({ month: this.month, leadRange: this.leadRange, rankRange: this.rankRange });
		},
		setRankRange(range: DateRange) {
			this.rankRange = range;
			saveStateToStorage({ month: this.month, leadRange: this.leadRange, rankRange: this.rankRange });
		},
		async refreshAll() {
			this.error = null;
			await Promise.all([this.fetchFunnelStages(), this.fetchScorePieData(), this.fetchLeadTrend(), this.fetchClassHourRank()]);
		},
		async fetchFunnelStages() {
			this.loading.funnel = true;
			try {
				const data = await queryStudentFunnelByMonth({ month: this.month });
				this.funnelStages = data;
			} catch (e: any) {
				this.error = e?.message || "获取漏斗图数据失败";
			} finally {
				this.loading.funnel = false;
			}
		},
		async fetchScorePieData() {
			this.loading.age = true;
			try {
				const data = await queryStudentScorePieByMonth({ month: this.month });
				this.scorePieData = data;
			} catch (e: any) {
				this.error = e?.message || "获取成绩构成数据失败";
			} finally {
				this.loading.age = false;
			}
		},
		async fetchLeadTrend() {
			this.loading.leadTrend = true;
			try {
				const data = await queryLeadTrend({ startDate: this.leadRange.startDate, endDate: this.leadRange.endDate });
				this.leadTrend = data;
			} catch (e: any) {
				this.error = e?.message || "获取走势数据失败";
			} finally {
				this.loading.leadTrend = false;
			}
		},
		async fetchClassHourRank() {
			this.loading.classHourRank = true;
			try {
				const data = await queryClassHourRank({ startDate: this.rankRange.startDate, endDate: this.rankRange.endDate, top: 20 });
				this.classHourRank = data;
			} catch (e: any) {
				this.error = e?.message || "获取课时排行数据失败";
			} finally {
				this.loading.classHourRank = false;
			}
		},
	},
});

