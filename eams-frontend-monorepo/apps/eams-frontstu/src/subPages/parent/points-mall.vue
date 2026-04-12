<script setup lang="ts">
import { computed, ref } from "vue";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";

definePage({
	name: "pointsMall",
	style: {
		navigationBarTitleText: "积分兑换",
		titleNView: false,
	},
});

interface GoodsItem {
	id?: number;
	categoryName?: string;
	name?: string;
	credit?: number;
	saleNum?: number;
	viewNum?: number;
	cover?: string;
	content?: string;
	state?: number;
	schoolName?: string;
	storage?: number;
}

// 列表分页状态
const router = useRouter();
const keyword = ref("");
const loading = ref(false);
const loadingMore = ref(false);
const goodsList = ref<Array<GoodsItem>>([]);
const pageIndex = ref(1);
const pages = ref(0);
const total = ref(0);
const pageSize = 10;

// 顶部搜索仅做前端本地筛选
const filteredGoods = computed(() => {
	const value = keyword.value.trim().toLowerCase();
	if (!value) return goodsList.value;

	return goodsList.value.filter((item) =>
		[item.name, item.categoryName, item.schoolName, item.content].some((text) =>
			String(text || "")
				.toLowerCase()
				.includes(value),
		),
	);
});

const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeRows(data: any): Array<GoodsItem> {
	return Array.isArray(data?.rows) ? data.rows : [];
}

function goodsStatusText(item: GoodsItem) {
	if (Number(item.state) !== 1) return "暂不可兑换";
	if (Number(item.storage || 0) <= 0) return "库存不足";
	return "可兑换";
}

function goodsStatusClass(item: GoodsItem) {
	if (Number(item.state) !== 1) return "goods-card__status--disabled";
	if (Number(item.storage || 0) <= 0) return "goods-card__status--warn";
	return "goods-card__status--ready";
}

// 拉取礼品列表
async function loadGoods(nextPage = 1, append = false) {
	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await Apis.home.get_c1_exchange_query_allGoods({
			params: {
				pageIndex: nextPage,
				pageSize,
			},
		});

		const pageData = res?.data || {};
		const rows = normalizeRows(pageData);
		pageIndex.value = Number(pageData.pageIndex || nextPage);
		pages.value = Number(pageData.pages || 0);
		total.value = Number(pageData.total || 0);
		goodsList.value = append ? [...goodsList.value, ...rows] : rows;
	} catch {
		if (!append) goodsList.value = [];
		uni.showToast({ title: "礼品列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadGoods(pageIndex.value + 1, true);
}

// 页面跳转
function openRecord() {
	router.push({ name: "pointsRecord" });
}

function openGoodsDetail(id?: number) {
	if (!id) return;
	router.push({
		name: "goodsDetail",
		query: { id: String(id) },
	});
}

function goBack() {
	uni.switchTab({ url: "/pages/home/index" });
}

onMounted(() => {
	loadGoods();
});
</script>

<template>
	<view class="points-page">
		<view class="points-page__safe" />
		<!-- 顶部搜索与记录入口 -->
		<view class="points-page__toolbar">
			<view class="points-page__back" @click="goBack">
				<view class="i-carbon:arrow-left text-18px text-#374151" />
			</view>
			<view class="points-page__search">
				<view class="i-carbon:search text-16px text-#9aa3b2" />
				<input v-model="keyword" class="points-page__input" placeholder="搜索礼品" />
			</view>
			<text class="points-page__record" @click="openRecord">兑换记录</text>
		</view>
		<view class="points-page__body">
			<!-- 礼品列表概览 -->
			<view v-if="goodsList.length" class="points-page__summary">
				<text>共 {{ total }} 件礼品</text>
				<text v-if="keyword.trim()">搜索结果 {{ filteredGoods.length }} 件</text>
			</view>

			<!-- 礼品卡片列表 -->
			<view v-if="filteredGoods.length" class="goods-list">
				<view v-for="item in filteredGoods" :key="item.id" class="goods-card" @click="openGoodsDetail(item.id)">
					<image v-if="item.cover" :src="item.cover" class="goods-card__cover" mode="aspectFill" />
					<view v-else class="goods-card__cover goods-card__cover--placeholder">
						<view class="i-carbon:gift text-34px text-#bcc4d1" />
					</view>

					<view class="goods-card__body">
						<view class="goods-card__header">
							<view class="goods-card__name">{{ item.name || "未命名礼品" }}</view>
							<view class="goods-card__credit">{{ item.credit || 0 }} 积分</view>
						</view>

						<view class="goods-card__meta">
							<text>{{ item.categoryName || "未分类" }}</text>
							<text v-if="item.schoolName">{{ item.schoolName }}</text>
						</view>

						<view class="goods-card__desc">{{ item.content || "暂无礼品介绍" }}</view>

						<view class="goods-card__footer">
							<view class="goods-card__stats">
								<text>库存 {{ item.storage || 0 }}</text>
								<text>已兑 {{ item.saleNum || 0 }}</text>
								<text>浏览 {{ item.viewNum || 0 }}</text>
							</view>
							<view class="goods-card__status" :class="goodsStatusClass(item)">
								{{ goodsStatusText(item) }}
							</view>
						</view>
					</view>
				</view>

				<view v-if="hasMore" class="load-more" @click="loadMore">
					{{ loadingMore ? "加载中..." : "加载更多" }}
				</view>
			</view>

			<ParentEmptyState
				v-else
				:text="loading ? '加载中...' : keyword.trim() ? '没有匹配的礼品' : '暂无礼品'"
				min-height="180px"
			/>
		</view>
	</view>
</template>

<style scoped>
.points-page {
	min-height: 100vh;
	background: #f5f7fb;
}

.points-page__safe {
	height: env(safe-area-inset-top);
	background: #fff;
}

.points-page__toolbar {
	padding: 10px 12px;
	display: flex;
	align-items: center;
	gap: 10px;
	background: #fff;
}

.points-page__back {
	width: 36px;
	height: 36px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 50%;
	background: #f1f3f7;
}

.points-page__search {
	flex: 1;
	height: 38px;
	padding: 0 14px;
	display: flex;
	align-items: center;
	gap: 8px;
	border-radius: 999px;
	background: #f1f3f7;
}

.points-page__input {
	flex: 1;
	font-size: 14px;
	color: #374151;
}

.points-page__record {
	font-size: 14px;
	font-weight: 600;
	color: #27c79f;
}

.points-page__body {
	padding: 12px;
}

.points-page__summary {
	margin-bottom: 12px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	font-size: 13px;
	color: #8b95a7;
}

.goods-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.goods-card {
	display: flex;
	gap: 12px;
	padding: 14px;
	border-radius: 18px;
	background: #fff;
	box-shadow: 0 8px 24px rgba(50, 75, 122, 0.08);
}

.goods-card__cover {
	width: 92px;
	height: 92px;
	flex-shrink: 0;
	border-radius: 14px;
	background: #eef2f7;
}

.goods-card__cover--placeholder {
	display: flex;
	align-items: center;
	justify-content: center;
}

.goods-card__body {
	flex: 1;
	min-width: 0;
}

.goods-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.goods-card__name {
	flex: 1;
	min-width: 0;
	font-size: 16px;
	font-weight: 700;
	line-height: 1.4;
	color: #111827;
}

.goods-card__credit {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	background: rgba(39, 199, 159, 0.12);
	font-size: 12px;
	font-weight: 700;
	color: #12b48f;
}

.goods-card__meta {
	margin-top: 8px;
	display: flex;
	flex-wrap: wrap;
	gap: 8px;
	font-size: 12px;
	color: #8b95a7;
}

.goods-card__desc {
	margin-top: 10px;
	font-size: 13px;
	line-height: 1.6;
	color: #4b5563;
	display: -webkit-box;
	overflow: hidden;
	-webkit-line-clamp: 2;
	-webkit-box-orient: vertical;
}

.goods-card__footer {
	margin-top: 12px;
	padding-top: 12px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
	border-top: 1px solid #eef2f7;
}

.goods-card__stats {
	display: flex;
	flex-wrap: wrap;
	gap: 10px;
	font-size: 12px;
	color: #94a3b8;
}

.goods-card__status {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 700;
}

.goods-card__status--ready {
	background: rgba(34, 197, 94, 0.12);
	color: #16a34a;
}

.goods-card__status--warn {
	background: rgba(245, 158, 11, 0.12);
	color: #d97706;
}

.goods-card__status--disabled {
	background: rgba(148, 163, 184, 0.12);
	color: #64748b;
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
