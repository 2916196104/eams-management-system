<script setup lang="ts">
import { computed, ref } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "minePointRecord",
	style: {
		navigationBarTitleText: "积分记录",
		titleNView: false,
	},
});

interface PointRecordItem {
	student_id?: number;
	credit?: number;
	current_credit?: number;
	add_time?: string;
	remark?: string;
}

const userStore = useUserStore();
const { currentStudent } = storeToRefs(userStore);

const loading = ref(false);
const loadingMore = ref(false);
const pageIndex = ref(1);
const pageSize = 10;
const total = ref(0);
const pages = ref(0);
const recordList = ref<Array<PointRecordItem>>([]);

// 当前学生信息
const studentId = computed(() => Number(currentStudent.value?.id || 0));
const studentName = computed(() => currentStudent.value?.name || "");
const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeRows(data: any): Array<PointRecordItem> {
	return Array.isArray(data?.rows) ? data.rows : [];
}

function formatCredit(value?: number) {
	const num = Number(value || 0);
	return num > 0 ? `+${num}` : `${num}`;
}

function creditClass(value?: number) {
	return Number(value || 0) >= 0 ? "point-record__credit--plus" : "point-record__credit--minus";
}

// 拉取积分记录
async function loadRecords(nextPage = 1, append = false) {
	if (!studentId.value) {
		recordList.value = [];
		return;
	}

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await (Apis as any).me.get_me_getMyPoint({
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
		recordList.value = append ? [...recordList.value, ...rows] : rows;
	}
	catch {
		if (!append) recordList.value = [];
		uni.showToast({ title: "积分记录加载失败", icon: "none" });
	}
	finally {
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
		<ParentNavBar title="积分记录" :show-refresh="true" @refresh="refreshPage" />

		<view class="page-content">
			<!-- 积分记录列表 -->
			<view v-if="recordList.length" class="point-record">
				<view class="point-record__summary">
					<text>{{ studentName || "当前学生" }}</text>
					<text>共 {{ total }} 条积分记录</text>
				</view>

				<view v-for="(item, index) in recordList" :key="`${item.add_time || index}-${index}`" class="point-card">
					<view class="point-card__left">
						<view class="point-card__remark">{{ item.remark || "积分变动" }}</view>
						<view class="point-card__time">{{ item.add_time || "暂无时间" }}</view>
					</view>

					<view class="point-card__right">
						<view class="point-card__credit" :class="creditClass(item.credit)">
							{{ formatCredit(item.credit) }}
						</view>
						<view class="point-card__current">当前积分 {{ item.current_credit || 0 }}</view>
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

.point-record {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.point-record__summary {
	padding: 0 2px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	font-size: 13px;
	color: #8b95a7;
}

.point-card {
	padding: 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.point-card__left {
	flex: 1;
	min-width: 0;
}

.point-card__remark {
	font-size: 15px;
	font-weight: 700;
	color: #111827;
}

.point-card__time {
	margin-top: 8px;
	font-size: 12px;
	color: #8b95a7;
}

.point-card__right {
	flex-shrink: 0;
	text-align: right;
}

.point-card__credit {
	font-size: 22px;
	font-weight: 800;
}

.point-record__credit--plus {
	color: #16a34a;
}

.point-record__credit--minus {
	color: #ef4444;
}

.point-card__current {
	margin-top: 8px;
	font-size: 12px;
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
