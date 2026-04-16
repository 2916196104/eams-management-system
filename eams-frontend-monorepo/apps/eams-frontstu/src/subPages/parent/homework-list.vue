<script setup lang="ts">
import { computed, ref } from "vue";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";

definePage({
	name: "homeworkList",
	style: {
		navigationBarTitleText: "作业列表",
		titleNView: false,
	},
});

interface HomeworkItem {
	id?: number;
	title?: string;
	courseName?: string;
	teacherName?: string;
}

const router = useRouter();
const loading = ref(false);
const loadingMore = ref(false);
const pageIndex = ref(1);
const pageSize = 10;
const total = ref(0);
const pages = ref(0);
const homeworkList = ref<Array<HomeworkItem>>([]);

const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeRows(data: any): Array<HomeworkItem> {
	return Array.isArray(data?.rows) ? data.rows : [];
}

async function loadHomework(nextPage = 1, append = false) {
	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await Apis.home.get_c1_homework({
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
		homeworkList.value = append ? [...homeworkList.value, ...rows] : rows;
	} catch {
		if (!append) homeworkList.value = [];
		uni.showToast({ title: "作业列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

function openDetail(item: HomeworkItem) {
	if (!item.id) return;

	router.push({
		path: "/subPages/parent/homework-detail",
		query: {
			id: String(item.id),
		},
	} as any);
}

async function refreshPage() {
	await loadHomework(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadHomework(pageIndex.value + 1, true);
}

onMounted(() => {
	loadHomework();
});

onShow(() => {
	loadHomework(1, false);
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="作业列表" :show-refresh="true" @refresh="refreshPage" />
		<view class="page-content">
			<view v-if="homeworkList.length" class="homework-list">
				<view class="homework-summary">共 {{ total }} 条作业</view>
				<view v-for="item in homeworkList" :key="item.id" class="homework-card" @click="openDetail(item)">
					<view class="homework-card__main">
						<view>
							<view class="homework-card__title">{{ item.title || "未命名作业" }}</view>
							<view class="homework-card__meta">
								<view class="homework-card__meta-item">
									<view class="i-carbon:notebook text-14px text-#94a3b8" />
									<text>{{ item.courseName || "未设置所属课程" }}</text>
								</view>
								<view class="homework-card__meta-item">
									<view class="i-carbon:user-avatar-filled-alt text-14px text-#94a3b8" />
									<text>{{ item.teacherName || "未设置发布教师" }}</text>
								</view>
							</view>
						</view>
						<view class="i-carbon:chevron-right text-16px text-#c3cad5" />
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

.homework-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.homework-summary {
	padding: 0 2px;
	font-size: 13px;
	color: #8b95a7;
}

.homework-card {
	padding: 14px 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.homework-card__main {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.homework-card__title {
	font-size: 16px;
	font-weight: 700;
	line-height: 1.5;
	color: #1f2937;
}

.homework-card__meta {
	margin-top: 12px;
	display: flex;
	flex-direction: column;
	gap: 8px;
}

.homework-card__meta-item {
	display: flex;
	align-items: center;
	gap: 6px;
	font-size: 13px;
	color: #6b7280;
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
