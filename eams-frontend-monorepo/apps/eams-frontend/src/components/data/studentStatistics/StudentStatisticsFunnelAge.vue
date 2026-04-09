<template>
	<el-card class="panel-card" shadow="never">
		<div class="panel-body">
			<el-row :gutter="16">
				<el-col :span="12">
					<div class="chart-wrap">
						<el-skeleton v-if="loadingFunnel" :rows="6" animated />
						<FunnelChart v-else :title="'销售漏斗模型'" :series-data="funnelStages" :show-label="true" />
					</div>
				</el-col>
				<el-col :span="12">
					<div class="chart-wrap">
						<el-skeleton v-if="loadingAge" :rows="6" animated />
						<PieChart
							v-else
							:title="'在学学员年龄构成'"
							:series-data="pieSeriesData"
							:radius="'68%'"
							:rose-type="false"
							:show-label="false"
						/>
					</div>
				</el-col>
			</el-row>
		</div>
	</el-card>
</template>

<script setup lang="ts">
import { computed } from "vue";
import FunnelChart from "@/components/mychart/FunnelChart.vue";
import PieChart from "@/components/mychart/PieChart.vue";
import type { FunnelSeriesItem } from "@/components/mychart/FunnelChart.vue";
import type { ScorePieItem } from "@/apis/data/studentStatistics";

const props = defineProps<{
	funnelStages: FunnelSeriesItem[];
	scorePieData: ScorePieItem[];
	loadingFunnel: boolean;
	loadingAge: boolean;
}>();

const pieSeriesData = computed(() =>
	props.scorePieData.map((i) => ({
		name: i.name,
		value: i.value,
		color: i.color,
	})),
);
</script>

<style scoped>
.panel-card {
	width: 100%;
}

.panel-body {
	padding-top: 8px;
}

.chart-wrap {
	height: 360px;
}
</style>

