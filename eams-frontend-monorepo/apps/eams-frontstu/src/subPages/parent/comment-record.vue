<script setup lang="ts">
import { computed, ref } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "commentRecord",
	style: {
		navigationBarTitleText: "点评记录",
		titleNView: false,
	},
});

interface ReviewRecordItem {
	id?: number;
	creator_name?: string;
	content?: string;
	score?: number;
	add_time?: string;
	lesson_title?: string;
}

const userStore = useUserStore();
const { currentStudent } = storeToRefs(userStore);

const loading = ref(false);
const loadingMore = ref(false);
const pageIndex = ref(1);
const pageSize = 10;
const total = ref(0);
const pages = ref(0);
const reviews = ref<Array<ReviewRecordItem>>([]);

const studentId = computed(() => Number(currentStudent.value?.id || 0));
const studentName = computed(() => currentStudent.value?.name || "");
const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeRows(data: any): Array<ReviewRecordItem> {
	const rows = Array.isArray(data?.rows) ? data.rows : [];
	return rows.map((item: any) => ({
		id: item?.id,
		creator_name:
			item?.evaluate_teacher_name ??
			item?.evaluateTeacherName ??
			(typeof item?.evaluate_teacher === "number" ? `教师 ${item.evaluate_teacher}` : item?.evaluate_teacher),
		content: item?.evaluation ?? item?.content,
		score: item?.score,
		add_time: item?.evaluate_time ?? item?.add_time,
		lesson_title: item?.lesson_title,
	}));
}

function scoreText(score?: number) {
	if (typeof score !== "number") return "未评分";
	return `${score} 分`;
}

function scoreClass(score?: number) {
	if (typeof score !== "number") return "review-score--empty";
	if (score >= 90) return "review-score--excellent";
	if (score >= 80) return "review-score--good";
	if (score >= 60) return "review-score--pass";
	return "review-score--warn";
}

async function loadReviews(nextPage = 1, append = false) {
	if (!studentId.value) {
		reviews.value = [];
		return;
	}

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await Apis.home.get_c1_review_records_query_reviews({
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
		reviews.value = append ? [...reviews.value, ...rows] : rows;
	} catch {
		if (!append) reviews.value = [];
		uni.showToast({ title: "点评记录加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function refreshPage() {
	await loadReviews(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadReviews(pageIndex.value + 1, true);
}

onMounted(() => {
	loadReviews();
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="点评记录" :show-refresh="true" @refresh="refreshPage" />
		<view class="page-content">
			<view v-if="reviews.length" class="review-list">
				<view class="review-summary">
					<text>{{ studentName || "当前学生" }}</text>
					<text>共 {{ total }} 条点评</text>
				</view>

				<view v-for="item in reviews" :key="item.id" class="review-card">
					<view class="review-card__header">
						<view>
							<view class="review-card__teacher">{{ item.creator_name || "未设置评价人" }}</view>
							<view class="review-card__time">{{ item.add_time || "暂无时间" }}</view>
						</view>
						<view class="review-score" :class="scoreClass(item.score)">
							{{ scoreText(item.score) }}
						</view>
					</view>

					<view class="review-card__content">{{ item.content || "暂无点评内容" }}</view>
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

.review-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.review-summary {
	padding: 0 2px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	font-size: 13px;
	color: #8b95a7;
}

.review-card {
	padding: 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.review-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.review-card__teacher {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.review-card__time {
	margin-top: 6px;
	font-size: 12px;
	color: #94a3b8;
}

.review-score {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 700;
}

.review-score--excellent {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.review-score--good {
	background: rgba(59, 130, 246, 0.12);
	color: #2563eb;
}

.review-score--pass {
	background: rgba(245, 158, 11, 0.12);
	color: #d97706;
}

.review-score--warn {
	background: rgba(239, 68, 68, 0.12);
	color: #dc2626;
}

.review-score--empty {
	background: rgba(148, 163, 184, 0.12);
	color: #64748b;
}

.review-card__content {
	margin-top: 14px;
	padding: 14px;
	border-radius: 14px;
	background: #f8fafc;
	font-size: 14px;
	line-height: 1.8;
	color: #475569;
	white-space: pre-wrap;
	word-break: break-word;
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
