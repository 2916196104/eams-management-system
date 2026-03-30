<script setup lang="ts">
import { computed, ref } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "scoreList",
	style: {
		navigationBarTitleText: "成绩单",
		titleNView: false,
	},
});

interface ScoreItem {
	id?: number;
	grade_id?: number;
	grade_title?: string;
	student_id?: number;
	student_name?: string;
	score?: number;
	add_time?: string;
}

const userStore = useUserStore();
const { currentStudent } = storeToRefs(userStore);

const loading = ref(false);
const loadingMore = ref(false);
const pageIndex = ref(1);
const pageSize = 10;
const total = ref(0);
const pages = ref(0);
const scoreList = ref<Array<ScoreItem>>([]);

const studentId = computed(() => Number(currentStudent.value?.id || 0));
const studentName = computed(() => currentStudent.value?.name || "");
const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeRows(data: any): Array<ScoreItem> {
	return Array.isArray(data?.rows) ? data.rows : [];
}

function scoreLevel(score?: number) {
	if (typeof score !== "number") return "未评分";
	if (score >= 90) return "优秀";
	if (score >= 80) return "良好";
	if (score >= 60) return "及格";
	return "待提升";
}

function scoreClass(score?: number) {
	if (typeof score !== "number") return "score-badge--empty";
	if (score >= 90) return "score-badge--excellent";
	if (score >= 80) return "score-badge--good";
	if (score >= 60) return "score-badge--pass";
	return "score-badge--warn";
}

async function loadScores(nextPage = 1, append = false) {
	if (!studentId.value) {
		scoreList.value = [];
		return;
	}

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await Apis.home.get_c1_home_score_query_score_list({
			params: {
				student_id: studentId.value,
				pageIndex: nextPage,
				pageSize,
			},
		});

		const pageData = res?.data || {};
		const rows = normalizeRows(pageData);
		pageIndex.value = Number(pageData.pageIndex || nextPage);
		pages.value = Number(pageData.pages || 0);
		total.value = Number(pageData.total || 0);
		scoreList.value = append ? [...scoreList.value, ...rows] : rows;
	} catch {
		if (!append) scoreList.value = [];
		uni.showToast({ title: "成绩列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function refreshPage() {
	await loadScores(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadScores(pageIndex.value + 1, true);
}

onMounted(() => {
	loadScores();
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="成绩单" :show-refresh="true" @refresh="refreshPage" />
		<view class="page-content">
			<view v-if="scoreList.length" class="score-list">
				<view class="score-summary">
					<text>{{ studentName || "当前学生" }}</text>
					<text>共 {{ total }} 条成绩记录</text>
				</view>

				<view v-for="item in scoreList" :key="item.id" class="score-card">
					<view class="score-card__header">
						<view>
							<view class="score-card__title">{{ item.grade_title || "未命名考核项" }}</view>
							<view class="score-card__student">{{ item.student_name || studentName || "未命名学生" }}</view>
						</view>
						<view class="score-badge" :class="scoreClass(item.score)">
							{{ typeof item.score === "number" ? `${item.score} 分` : "未评分" }}
						</view>
					</view>

					<view class="score-card__footer">
						<text class="score-card__time">{{ item.add_time || "暂无时间" }}</text>
						<text class="score-card__level">{{ scoreLevel(item.score) }}</text>
					</view>
				</view>

				<view v-if="hasMore" class="load-more" @click="loadMore">
					{{ loadingMore ? "加载中..." : "加载更多" }}
				</view>
			</view>

			<ParentEmptyState v-else :text="loading ? '加载中...' : '暂无记录'" min-height="180px" />
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.page-content {
	padding: 12px;
}

.score-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.score-summary {
	padding: 0 2px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	font-size: 13px;
	color: #8b95a7;
}

.score-card {
	padding: 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.score-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.score-card__title {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.score-card__student {
	margin-top: 6px;
	font-size: 13px;
	color: #6b7280;
}

.score-badge {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 700;
}

.score-badge--excellent {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.score-badge--good {
	background: rgba(59, 130, 246, 0.12);
	color: #2563eb;
}

.score-badge--pass {
	background: rgba(245, 158, 11, 0.12);
	color: #d97706;
}

.score-badge--warn {
	background: rgba(239, 68, 68, 0.12);
	color: #dc2626;
}

.score-badge--empty {
	background: rgba(148, 163, 184, 0.12);
	color: #64748b;
}

.score-card__footer {
	margin-top: 14px;
	padding-top: 12px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-top: 1px solid #eef2f7;
}

.score-card__time {
	font-size: 12px;
	color: #94a3b8;
}

.score-card__level {
	font-size: 13px;
	font-weight: 600;
	color: #475569;
}

.load-more {
	height: 40px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	background: #fff;
	font-size: 14px;
	font-weight: 600;
	color: #31c7a5;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}
</style>
