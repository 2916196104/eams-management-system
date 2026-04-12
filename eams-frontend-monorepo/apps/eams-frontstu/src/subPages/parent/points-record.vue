<script setup lang="ts">
import { computed, ref, onMounted } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "pointsRecord",
	style: {
		navigationBarTitleText: "积分兑换记录",
		titleNView: false,
	},
});

interface AcceptGoodsItem {
	addTime?: string;
	editTime?: string;
	creator?: number;
	editor?: number;
	deleted?: number;
	id?: number;
	creditMallId?: number;
	studentId?: number;
	schoolId?: number;
	userId?: number;
	num?: number;
	credit?: string;
	verifyState?: number;
	verifyStaff?: number;
	verifyTime?: string;
	verifyRemark?: string;
	creditMallName?: string;
	cover?: string;
	studentName?: string;
	schoolName?: string;
	mobile?: string;
	verifyStaffName?: string;
}

const userStore = useUserStore();
const { currentStudent } = storeToRefs(userStore);

const loading = ref(false);
const loadingMore = ref(false);
const pageIndex = ref(1);
const pageSize = 10;
const total = ref(0);
const pages = ref(0);
const recordList = ref<Array<AcceptGoodsItem>>([]);

// 当前学生与分页状态
const studentId = computed(() => Number(currentStudent.value?.id || 0));
const studentName = computed(() => currentStudent.value?.name || "");
const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeRows(data: any): Array<AcceptGoodsItem> {
	return Array.isArray(data?.rows) ? data.rows : [];
}

function verifyStateText(state?: number) {
	switch (Number(state)) {
		case 1:
			return "审核通过";
		case 2:
			return "已驳回";
		case 0:
		default:
			return "待审核";
	}
}

function verifyStateClass(state?: number) {
	switch (Number(state)) {
		case 1:
			return "record-status--success";
		case 2:
			return "record-status--danger";
		case 0:
		default:
			return "record-status--pending";
	}
}

// 拉取兑换记录
async function loadRecords(nextPage = 1, append = false) {
	if (!studentId.value) {
		recordList.value = [];
		return;
	}

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await (Apis as any).home.get_c1_exchange_query_acceptGoods({
			params: {
				studentId: studentId.value,
				pageIndex: nextPage,
				pageSize,
			},
		});

		const pageData = res?.data || {};
		const rows = normalizeRows(pageData);
		pageIndex.value = Number(pageData.pageIndex || nextPage);
		pages.value = Number(pageData.pages || 0);
		total.value = Number(pageData.total || 0);
		recordList.value = append ? [...recordList.value, ...rows] : rows;
	} catch {
		if (!append) recordList.value = [];
		uni.showToast({ title: "兑换记录加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function refreshPage() {
	await loadRecords(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadRecords(pageIndex.value + 1, true);
}

onMounted(() => {
	loadRecords();
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="积分兑换记录" :show-refresh="true" @refresh="refreshPage" />
		<view class="page-content">
			<!-- 兑换记录列表 -->
			<view v-if="recordList.length" class="record-list">
				<view class="record-summary">
					<text>{{ studentName || "当前学生" }}</text>
					<text>共 {{ total }} 条兑换记录</text>
				</view>

				<view v-for="item in recordList" :key="item.id" class="record-card">
					<image v-if="item.cover" :src="item.cover" class="record-card__cover" mode="aspectFill" />
					<view v-else class="record-card__cover record-card__cover--placeholder">
						<view class="i-carbon:gift text-28px text-#bcc4d1" />
					</view>

					<view class="record-card__body">
						<view class="record-card__header">
							<view class="record-card__title">{{ item.creditMallName || "未命名礼品" }}</view>
							<view class="record-status" :class="verifyStateClass(item.verifyState)">
								{{ verifyStateText(item.verifyState) }}
							</view>
						</view>

						<view class="record-card__meta">
							<text>兑换数量 {{ item.num || 0 }}</text>
							<text>消耗积分 {{ item.credit || 0 }}</text>
						</view>

						<view class="record-card__text">兑换时间：{{ item.addTime || "暂无" }}</view>
						<view class="record-card__text">审核时间：{{ item.verifyTime || "暂无" }}</view>
						<view class="record-card__text">审核人：{{ item.verifyStaffName || "暂无" }}</view>
						<view class="record-card__remark">审核备注：{{ item.verifyRemark || "暂无备注" }}</view>
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

.record-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.record-summary {
	padding: 0 2px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	font-size: 13px;
	color: #8b95a7;
}

.record-card {
	display: flex;
	gap: 12px;
	padding: 14px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.record-card__cover {
	width: 84px;
	height: 84px;
	flex-shrink: 0;
	border-radius: 14px;
	background: #eef2f7;
}

.record-card__cover--placeholder {
	display: flex;
	align-items: center;
	justify-content: center;
}

.record-card__body {
	flex: 1;
	min-width: 0;
}

.record-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 10px;
}

.record-card__title {
	flex: 1;
	font-size: 16px;
	font-weight: 700;
	line-height: 1.5;
	color: #111827;
}

.record-status {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 700;
}

.record-status--pending {
	background: rgba(245, 158, 11, 0.12);
	color: #d97706;
}

.record-status--success {
	background: rgba(34, 197, 94, 0.12);
	color: #16a34a;
}

.record-status--danger {
	background: rgba(239, 68, 68, 0.12);
	color: #dc2626;
}

.record-card__meta {
	margin-top: 8px;
	display: flex;
	flex-wrap: wrap;
	gap: 10px;
	font-size: 12px;
	color: #8b95a7;
}

.record-card__text,
.record-card__remark {
	margin-top: 8px;
	font-size: 13px;
	line-height: 1.6;
	color: #475569;
}

.record-card__remark {
	padding-top: 8px;
	border-top: 1px solid #eef2f7;
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
	color: #27c79f;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}
</style>
