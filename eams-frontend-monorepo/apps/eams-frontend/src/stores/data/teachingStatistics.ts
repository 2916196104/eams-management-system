import { defineStore } from "pinia";
import { ElMessage } from "element-plus";
import { queryTeachClassHour, queryTeachScoreRank, type TeachClassHourResult, type TeachScoreRow } from "@/apis/data/teachingStatistics";

type DateRange = { startDate: string; endDate: string };

const STORAGE_KEY = "teaching-statistics-filters:v1";

function pad2(n: number) {
	return String(n).padStart(2, "0");
}

function formatDate(d: Date) {
	return `${d.getFullYear()}-${pad2(d.getMonth() + 1)}-${pad2(d.getDate())}`;
}

function defaultLast30Days(): DateRange {
	const end = new Date();
	const start = new Date(end);
	start.setDate(start.getDate() - 29);
	return { startDate: formatDate(start), endDate: formatDate(end) };
}

interface TeachingStatisticsState {
	classHourRange: DateRange;
	scoreRange: DateRange;
	classHourData: TeachClassHourResult | null;
	scoreRankData: TeachScoreRow[];
	loading: {
		classHour: boolean;
		scoreRank: boolean;
	};
}

function loadStateFromStorage(): Partial<TeachingStatisticsState> {
	try {
		const raw = localStorage.getItem(STORAGE_KEY);
		if (!raw) return {};
		return JSON.parse(raw);
	} catch {
		return {};
	}
}

function saveStateToStorage(state: Pick<TeachingStatisticsState, "classHourRange" | "scoreRange">) {
	try {
		localStorage.setItem(STORAGE_KEY, JSON.stringify(state));
	} catch {
		// ignore
	}
}

export const useTeachingStatisticsStore = defineStore("teachingStatistics", {
	state: (): TeachingStatisticsState => ({
		classHourRange: defaultLast30Days(),
		scoreRange: defaultLast30Days(),
		classHourData: null,
		scoreRankData: [],
		loading: {
			classHour: false,
			scoreRank: false,
		},
	}),
	actions: {
		initFilters() {
			const partial = loadStateFromStorage();
			if (partial.classHourRange?.startDate && partial.classHourRange?.endDate) this.classHourRange = partial.classHourRange;
			if (partial.scoreRange?.startDate && partial.scoreRange?.endDate) this.scoreRange = partial.scoreRange;
		},
		setClassHourRange(range: DateRange) {
			this.classHourRange = range;
			saveStateToStorage({ classHourRange: this.classHourRange, scoreRange: this.scoreRange });
		},
		setScoreRange(range: DateRange) {
			this.scoreRange = range;
			saveStateToStorage({ classHourRange: this.classHourRange, scoreRange: this.scoreRange });
		},
		async refreshAll() {
			try {
				await Promise.all([this.fetchClassHourData(), this.fetchScoreRankData()]);
			} catch {
				ElMessage.error("加载数据失败");
			}
		},
		async fetchClassHourData() {
			this.loading.classHour = true;
			try {
				this.classHourData = await queryTeachClassHour(this.classHourRange);
			} catch (e) {
				this.classHourData = null;
				throw e;
			} finally {
				this.loading.classHour = false;
			}
		},
		async fetchScoreRankData() {
			this.loading.scoreRank = true;
			try {
				this.scoreRankData = await queryTeachScoreRank(this.scoreRange);
			} catch (e) {
				this.scoreRankData = [];
				throw e;
			} finally {
				this.loading.scoreRank = false;
			}
		},
	},
});
