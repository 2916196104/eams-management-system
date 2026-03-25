<template>
	<div class="teaching-statistics-page">
		<el-alert v-if="store.error" class="error-alert" type="error" :closable="false" :title="store.error" />

		<el-card class="panel-card" shadow="never">
			<template #header>
				<div class="panel-header">
					<div class="panel-title">课时统计</div>
					<CompactDateRange
						:start-date="store.classHourRange.startDate"
						:end-date="store.classHourRange.endDate"
						:disabled="store.loading.classHour"
						@change="handleClassHourRangeChange"
					/>
				</div>
			</template>
			<div class="chart-wrap">
				<el-skeleton v-if="store.loading.classHour" :rows="6" animated />
				<BarChart
					v-else
					:title="'课时统计'"
					:x-axis-data="store.classHourData?.xAxisData ?? []"
					:series-data="store.classHourData?.seriesData ?? []"
					:show-label="true"
				/>
			</div>
		</el-card>

		<el-card class="panel-card" shadow="never">
			<template #header>
				<div class="panel-header">
					<div class="panel-title">学评教得分排名</div>
					<CompactDateRange
						:start-date="store.scoreRange.startDate"
						:end-date="store.scoreRange.endDate"
						:disabled="store.loading.scoreRank"
						@change="handleScoreRangeChange"
					/>
				</div>
			</template>

			<el-table v-loading="store.loading.scoreRank" :data="scoreTableData" border @sort-change="handleSortChange">
				<el-table-column type="index" label="#" width="60" />
				<el-table-column prop="teacherName" label="老师姓名" min-width="140" />
				<el-table-column prop="reviewCount" label="评价次数" min-width="100" sortable="custom" :sort-orders="sortOrders" />
				<el-table-column prop="compositeScore" label="综合评分" min-width="100" sortable="custom" :sort-orders="sortOrders" />
				<el-table-column prop="classAtmosphere" label="课堂气氛" min-width="100" sortable="custom" :sort-orders="sortOrders" />
				<el-table-column prop="teachingAttitude" label="授课态度" min-width="100" sortable="custom" :sort-orders="sortOrders" />
				<el-table-column prop="teachingEffect" label="教学效果" min-width="100" sortable="custom" :sort-orders="sortOrders" />
			</el-table>
		</el-card>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, ref } from "vue";
import { ElMessage } from "element-plus";
import BarChart from "@/components/mychart/BarChart.vue";
import CompactDateRange from "@/components/common/CompactDateRange.vue";
import { useTeachingStatisticsStore } from "@/stores/data/teachingStatistics";
import type { TeachScoreRow } from "@/apis/data/teachingStatistics";

const store = useTeachingStatisticsStore();
const sortOrders = ["ascending", "descending", null] as const;
type SortOrder = "ascending" | "descending" | null;
type SortProp = "reviewCount" | "compositeScore" | "classAtmosphere" | "teachingAttitude" | "teachingEffect";
const sortState = ref<{ prop: SortProp | null; order: SortOrder }>({ prop: null, order: null });

const scoreTableData = computed(() => {
	const source = [...store.scoreRankData];
	if (!sortState.value.prop || !sortState.value.order) return source;

	const prop = sortState.value.prop;
	const factor = sortState.value.order === "ascending" ? 1 : -1;
	return source.sort((a: TeachScoreRow, b: TeachScoreRow) => (a[prop] - b[prop]) * factor);
});

onMounted(async () => {
	store.initFilters();
	await refreshAll();
});

async function refreshAll() {
	try {
		await store.refreshAll();
	} catch (e) {
		const err = e as Error;
		ElMessage.error(err?.message || "查询失败");
	}
}

async function handleClassHourRangeChange(payload: { startDate: string; endDate: string }) {
	store.setClassHourRange(payload);
	try {
		await store.fetchClassHourData();
	} catch (e) {
		const err = e as Error;
		ElMessage.error(err?.message || "更新课时统计失败");
	}
}

async function handleScoreRangeChange(payload: { startDate: string; endDate: string }) {
	store.setScoreRange(payload);
	try {
		await store.fetchScoreRankData();
		sortState.value = { prop: null, order: null };
	} catch (e) {
		const err = e as Error;
		ElMessage.error(err?.message || "更新学评教得分失败");
	}
}

function handleSortChange(payload: { prop?: string; order?: SortOrder | null }) {
	const prop = (payload.prop as SortProp | undefined) ?? null;
	const order = (payload.order ?? null) as SortOrder | null;
	sortState.value = { prop, order };
}
</script>

<style scoped>
.teaching-statistics-page {
	padding: 0 8px 16px;
}

.error-alert {
	margin-bottom: 12px;
}

.panel-card {
	margin-bottom: 12px;
}

.panel-header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.panel-title {
	font-weight: 700;
}

.chart-wrap {
	height: 320px;
}
</style>

