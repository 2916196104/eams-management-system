<script setup lang="ts">
import { ref } from "vue";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";

definePage({
	name: "noticeList",
	style: {
		navigationBarTitleText: "公告提醒",
		titleNView: false,
	},
});

interface AdvertisementItem {
	id?: number | string;
	title?: string;
	content?: string;
	cover?: string;
	addTime?: string;
}

const loading = ref(false);
const notices = ref<Array<AdvertisementItem>>([]);

function normalizeRows(data: any) {
	return Array.isArray(data?.rows) ? data.rows : [];
}

function loadNotices() {
	loading.value = true;
	Apis.sCenter
		.get_app_sCenter_advertisementList({
			params: {
				pageIndex: 1,
				pageSize: 10,
			},
		})
		.then((res: any) => {
			notices.value = normalizeRows(res?.data);
		})
		.catch(() => {
			notices.value = [];
			uni.showToast({ title: "公告加载失败", icon: "none" });
		})
		.finally(() => {
			loading.value = false;
		});
}

function refreshPage() {
	loadNotices();
}

onMounted(() => {
	loadNotices();
});
</script>

<template>
	<view class="notice-page">
		<ParentNavBar title="公告提醒" :show-refresh="true" @refresh="refreshPage" />
		<view class="notice-page__content">
			<view v-if="notices.length" class="notice-list">
				<view v-for="item in notices" :key="item.id" class="notice-card">
					<image v-if="item.cover" class="notice-card__cover" :src="item.cover" mode="aspectFill" />
					<view class="notice-card__body">
						<text class="notice-card__title">{{ item.title }}</text>
						<text v-if="item.addTime" class="notice-card__time">{{ item.addTime }}</text>
						<text class="notice-card__content">{{ item.content || "暂无公告内容" }}</text>
					</view>
				</view>
			</view>
			<ParentEmptyState v-else :text="loading ? '加载中...' : '暂无公告'" min-height="180px" />
		</view>
	</view>
</template>

<style scoped>
.notice-page {
	min-height: 100vh;
	background: #f5f7fb;
}

.notice-page__content {
	padding: 12px;
}

.notice-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.notice-card {
	border-radius: 16px;
	background: #fff;
	overflow: hidden;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.notice-card__cover {
	width: 100%;
	height: 148px;
	background: #eef2f7;
}

.notice-card__body {
	padding: 14px 16px 16px;
	display: flex;
	flex-direction: column;
	gap: 8px;
}

.notice-card__title {
	font-size: 17px;
	font-weight: 600;
	color: #111827;
}

.notice-card__time {
	font-size: 12px;
	color: #9ca3af;
}

.notice-card__content {
	font-size: 14px;
	line-height: 1.7;
	color: #4b5563;
}
</style>
