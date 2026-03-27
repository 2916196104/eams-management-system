<script setup lang="ts">
import { ref } from "vue";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";

definePage({
	name: "mineHelp",
	style: {
		navigationBarTitleText: "帮助",
		titleNView: false,
	},
});

interface ManualItem {
	id?: string | number;
	title: string;
}

const loading = ref(false);
const manualList = ref<Array<ManualItem>>([]);

function normalizeRows(data: any): Array<ManualItem> {
	return Array.isArray(data?.rows) ? data.rows : [];
}

async function loadManualList() {
	loading.value = true;
	try {
		const res: any = await (Apis as any).me.get_me_manual_getList({
			params: {
				pageIndex: 1,
				pageSize: 20,
			},
		});
		manualList.value = normalizeRows(res?.data);
	}
	catch {
		manualList.value = [];
		uni.showToast({ title: "使用说明加载失败", icon: "none" });
	}
	finally {
		loading.value = false;
	}
}

function openDetail(item: ManualItem) {
	uni.navigateTo({
		url: `/subPages/mine/help-detail?id=${item.id ?? ""}&title=${encodeURIComponent(item.title || "")}`,
	});
}

async function refreshPage() {
	await loadManualList();
	uni.showToast({ title: "已刷新", icon: "none" });
}

onMounted(() => {
	loadManualList();
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="帮助" :show-refresh="true" @refresh="refreshPage" />
		<view class="page-content">
			<view v-if="manualList.length" class="manual-list">
				<view v-for="item in manualList" :key="`${item.id}-${item.title}`" class="manual-item" @click="openDetail(item)">
					<text class="manual-item__title">{{ item.title }}</text>
					<view class="i-carbon:chevron-right text-16px text-#b4bcc9" />
				</view>
			</view>
			<ParentEmptyState v-else :text="loading ? '加载中...' : '暂无说明'" min-height="180px" :card="false" />
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.page-content {
	padding: 0;
}

.manual-list {
	background: #fff;
}

.manual-item {
	padding: 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-bottom: 1px solid #eef2f7;
}

.manual-item:last-child {
	border-bottom: none;
}

.manual-item__title {
	font-size: 15px;
	color: #1f2937;
}
</style>
