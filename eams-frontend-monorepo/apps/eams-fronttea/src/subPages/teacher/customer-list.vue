<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { withTeacherBackQuery } from "@/utils/teacherNavigation";

definePage({
	name: "teacherCustomerList",
	style: {
		navigationBarTitleText: "我的客户",
		titleNView: false,
	},
});

const router = useRouter();
const currentRoute = useRoute();
const userStore = useUserStore();
const { customers } = storeToRefs(userStore);

const loading = ref(false);
const loadingMore = ref(false);
const pageIndex = ref(1);
const pages = ref(0);
const total = ref(0);
const pageSize = 10;

const hasMore = computed(() => pageIndex.value < pages.value);

async function loadCustomers(nextPage = 1, append = false) {
	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const payload = await userStore.loadCustomers(nextPage, pageSize, append);
		pageIndex.value = payload.pageIndex;
		pages.value = payload.pages;
		total.value = payload.total;
	} finally {
		targetLoading.value = false;
	}
}

function openDetail(id: string) {
	router.push({
		name: "teacherCustomerDetail",
		query: withTeacherBackQuery(currentRoute, { id }),
	} as any);
}

async function refreshPage() {
	await loadCustomers(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadCustomers(pageIndex.value + 1, true);
}

onShow(() => {
	void loadCustomers(1, false);
});
</script>

<template>
	<view class="teacher-list-page">
		<teacher-nav-bar title="我的客户" @refresh="refreshPage" />
		<view class="teacher-list-page__content">
			<view v-if="customers.length" class="teacher-list-page__summary">共 {{ total }} 位客户</view>

			<view v-if="customers.length" class="teacher-list-card">
				<view v-for="customer in customers" :key="customer.id" class="teacher-list-item" @click="openDetail(customer.id)">
					<view>
						<text class="teacher-list-item__name">{{ customer.name }}</text>
						<view class="teacher-list-item__phone">{{ customer.phone }}</view>
					</view>
					<view class="i-carbon:chevron-right text-16px text-#98a2b3" />
				</view>
			</view>

			<teacher-empty-state v-else :title="loading ? '加载中...' : '暂无客户数据'" compact />

			<view v-if="hasMore" class="teacher-list-page__more" @click="loadMore">
				{{ loadingMore ? "加载中..." : "加载更多" }}
			</view>
		</view>
	</view>
</template>

<style scoped>
.teacher-list-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-list-page__content {
	padding: 12px;
}

.teacher-list-page__summary {
	margin-bottom: 10px;
	padding: 0 2px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-list-card {
	overflow: hidden;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-list-item {
	display: flex;
	align-items: center;
	justify-content: space-between;
	padding: 16px;
	border-bottom: 1px solid #edf0f5;
}

.teacher-list-item:last-child {
	border-bottom: 0;
}

.teacher-list-item__name {
	font-size: 16px;
	font-weight: 600;
	color: #111827;
}

.teacher-list-item__phone {
	margin-top: 6px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-list-page__more {
	display: flex;
	align-items: center;
	justify-content: center;
	height: 40px;
	margin-top: 12px;
	border-radius: 999px;
	background: #fff;
	font-size: 14px;
	font-weight: 600;
	color: #31c7a5;
}
</style>
