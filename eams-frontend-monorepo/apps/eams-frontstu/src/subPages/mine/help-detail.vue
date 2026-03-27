<script setup lang="ts">
import { computed, ref } from "vue";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";

definePage({
	name: "mineHelpDetail",
	style: {
		navigationBarTitleText: "帮助详情",
		titleNView: false,
	},
});

interface ManualDetail {
	title?: string;
	content?: string;
}

const route = useRoute() as any;
const loading = ref(false);
const detail = ref<ManualDetail | null>(null);

const manualId = computed(() => route.query?.id || "");
const fallbackTitle = computed(() => decodeURIComponent(route.query?.title || ""));

async function loadDetail() {
	if (!manualId.value) {
		detail.value = {
			title: fallbackTitle.value || "帮助详情",
			content: "",
		};
		return;
	}

	loading.value = true;
	try {
		const res: any = await (Apis as any).me.get_me_manual_getDetail({
			params: {
				id: manualId.value,
			},
		});
		detail.value = res?.data || null;
	}
	catch {
		detail.value = null;
		uni.showToast({ title: "说明详情加载失败", icon: "none" });
	}
	finally {
		loading.value = false;
	}
}

async function refreshPage() {
	await loadDetail();
	uni.showToast({ title: "已刷新", icon: "none" });
}

onMounted(() => {
	loadDetail();
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar :title="detail?.title || fallbackTitle || '帮助详情'" :show-refresh="true" @refresh="refreshPage" />
		<view class="page-content">
			<view v-if="detail" class="detail-card">
				<view class="detail-card__title">{{ detail.title || fallbackTitle || "帮助详情" }}</view>
				<rich-text v-if="detail.content" class="detail-card__content" :nodes="detail.content" />
				<view v-else class="detail-card__empty">暂无说明内容</view>
			</view>
			<ParentEmptyState v-else :text="loading ? '加载中...' : '暂无详情'" min-height="180px" />
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

.detail-card {
	padding: 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.detail-card__title {
	font-size: 18px;
	font-weight: 700;
	line-height: 1.6;
	color: #111827;
}

.detail-card__content {
	margin-top: 14px;
	font-size: 15px;
	line-height: 1.8;
	color: #475569;
	word-break: break-word;
}

.detail-card__empty {
	margin-top: 14px;
	font-size: 14px;
	color: #94a3b8;
}
</style>
