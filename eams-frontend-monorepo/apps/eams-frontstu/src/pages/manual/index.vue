<script setup lang="ts">
import { computed, onMounted, ref } from "vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";

definePage({
	name: "manual",
	style: {
		navigationBarTitleText: "使用说明",
		titleNView: false,
	},
});

interface ManualItem {
	id?: string | number;
	title: string;
	summary?: string;
	createTime?: string;
	content?: string;
}

const manualList = ref<ManualItem[]>([]);
const selectedManual = ref<ManualItem | null>(null);
const isLoading = ref(false);
const showDetail = ref(false);

const latestManualTime = computed(() => {
	return manualList.value.find((item) => item.createTime)?.createTime || "实时更新";
});

const selectedManualNodes = computed(() => {
	const rawText = String(selectedManual.value?.content || selectedManual.value?.summary || "").trim();
	if (!rawText) return "";

	if (/<[a-z][\s\S]*>/i.test(rawText)) {
		return rawText;
	}

	return rawText
		.replace(/&/g, "&amp;")
		.replace(/</g, "&lt;")
		.replace(/>/g, "&gt;")
		.replace(/\n/g, "<br/>");
});

function normalizeManualItem(item: any): ManualItem {
	return {
		id: item?.id ?? item?.manualId ?? "",
		title: item?.title ?? item?.name ?? "未命名说明",
		summary: item?.summary ?? item?.description ?? "",
		createTime: item?.createTime ?? item?.date ?? "",
		content: item?.content ?? "",
	};
}

function normalizeManualList(data: any): ManualItem[] {
	const rows = Array.isArray(data?.rows) ? data.rows : Array.isArray(data) ? data : [];
	return rows.map(normalizeManualItem);
}

async function loadManualList() {
	isLoading.value = true;
	try {
		const res: any = await Apis.me.get_me_manual_getList({
			params: {
				pageIndex: 1,
				pageSize: 20,
			},
		});
		manualList.value = normalizeManualList(res?.data);
	}
	catch (error) {
		manualList.value = [];
		console.error("获取使用说明列表失败:", error);
		uni.showToast({
			title: "加载失败，请稍后重试",
			icon: "none",
		});
	}
	finally {
		isLoading.value = false;
	}
}

async function loadManualDetail(id: string | number) {
	isLoading.value = true;
	try {
		const res: any = await Apis.me.get_me_manual_getDetail({
			params: { id },
		});
		selectedManual.value = normalizeManualItem(res?.data);
		showDetail.value = true;
	}
	catch (error) {
		console.error("获取使用说明详情失败:", error);
		uni.showToast({
			title: "详情加载失败",
			icon: "none",
		});
	}
	finally {
		isLoading.value = false;
	}
}

async function openManual(manual: ManualItem) {
	if (!manual.id) {
		selectedManual.value = manual;
		showDetail.value = true;
		return;
	}

	await loadManualDetail(manual.id);
}

onMounted(() => {
	loadManualList();
});
</script>

<template>
	<view class="manual-page">
		<view class="manual-page__bg" />
		<ParentNavBar title="使用说明" :show-refresh="true" @refresh="loadManualList" />

		<view class="manual-page__content">
			<view class="manual-hero">
				<view class="manual-hero__badge">学习助手</view>
				<view class="manual-hero__title">操作说明与常见指引</view>
				<view class="manual-hero__desc">常用功能、操作步骤和注意事项都整理在这里，点开就能查看完整内容。</view>
				<view class="manual-hero__stats">
					<view class="manual-hero__stat">
						<view class="manual-hero__value">{{ manualList.length }}</view>
						<view class="manual-hero__label">当前说明</view>
					</view>
					<view class="manual-hero__stat manual-hero__stat--right">
						<view class="manual-hero__value manual-hero__value--small">{{ latestManualTime }}</view>
						<view class="manual-hero__label">最近更新</view>
					</view>
				</view>
			</view>

			<view class="manual-section">
				<view class="manual-section__header">
					<view>
						<view class="manual-section__title">说明列表</view>
						<view class="manual-section__subtitle">点击任意卡片即可展开完整说明</view>
					</view>
				</view>

				<view v-if="isLoading && !manualList.length" class="state-card">
					<view class="state-card__icon">
						<view class="i-carbon:renew state-card__icon--spin text-24px text-#1aa784" />
					</view>
					<view class="state-card__title">正在加载说明内容</view>
					<view class="state-card__desc">请稍候，列表马上就好。</view>
				</view>

				<view v-else-if="manualList.length" class="manual-list">
					<view
						v-for="(manual, index) in manualList"
						:key="manual.id || manual.title"
						class="manual-card"
						@click="openManual(manual)"
					>
						<view class="manual-card__index">{{ index + 1 }}</view>
						<view class="manual-card__body">
							<view class="manual-card__title-row">
								<view class="manual-card__title">{{ manual.title }}</view>
								<view class="i-carbon:chevron-right text-18px text-#b6c0ca" />
							</view>
							<view class="manual-card__summary">{{ manual.summary || "点击查看完整说明内容" }}</view>
							<view class="manual-card__meta">
								<view class="manual-card__time">{{ manual.createTime || "暂无时间" }}</view>
								<view class="manual-card__tag">查看详情</view>
							</view>
						</view>
					</view>
				</view>

				<view v-else class="state-card state-card--empty">
					<view class="state-card__icon">
						<view class="i-carbon:document text-26px text-#1aa784" />
					</view>
					<view class="state-card__title">暂时还没有使用说明</view>
					<view class="state-card__desc">后续新增说明后，这里会第一时间展示。</view>
				</view>
			</view>
		</view>

		<uni-popup v-model:visible="showDetail" mode="bottom">
			<view class="detail-sheet">
				<view class="detail-sheet__handle" />
				<view class="detail-sheet__top">
					<view class="detail-sheet__copy">
						<view class="detail-sheet__eyebrow">使用说明</view>
						<view class="detail-sheet__title">{{ selectedManual?.title || "说明详情" }}</view>
						<view class="detail-sheet__time">{{ selectedManual?.createTime || "刚刚更新" }}</view>
					</view>
					<view class="detail-sheet__close" @click="showDetail = false">
						<view class="i-carbon:close text-18px text-#4b5563" />
					</view>
				</view>
				<scroll-view scroll-y class="detail-sheet__scroll">
					<rich-text v-if="selectedManualNodes" :nodes="selectedManualNodes" class="detail-sheet__rich" />
					<view v-else class="detail-sheet__empty">暂无详细说明内容</view>
				</scroll-view>
			</view>
		</uni-popup>
	</view>
</template>

<style scoped>
.manual-page {
	position: relative;
	min-height: 100vh;
	background: #f4f7fb;
	overflow: hidden;
}

.manual-page__bg {
	position: absolute;
	top: 0;
	left: 0;
	right: 0;
	height: 260px;
	background: linear-gradient(180deg, #ddfff6 0%, rgba(221, 255, 246, 0) 100%);
}

.manual-page__content {
	position: relative;
	padding: 16px 16px 28px;
}

.manual-hero {
	padding: 22px 20px;
	border-radius: 28px;
	color: #fff;
	background: linear-gradient(135deg, #23c9a0 0%, #47baff 100%);
	box-shadow: 0 18px 42px rgba(35, 201, 160, 0.24);
}

.manual-hero__badge {
	display: inline-flex;
	align-items: center;
	padding: 6px 12px;
	border-radius: 999px;
	background: rgba(255, 255, 255, 0.18);
	font-size: 12px;
	font-weight: 600;
	letter-spacing: 0.5px;
}

.manual-hero__title {
	margin-top: 14px;
	font-size: 26px;
	font-weight: 700;
	line-height: 1.25;
}

.manual-hero__desc {
	margin-top: 10px;
	font-size: 14px;
	line-height: 1.7;
	color: rgba(255, 255, 255, 0.88);
}

.manual-hero__stats {
	display: flex;
	margin-top: 20px;
	padding-top: 18px;
	border-top: 1px solid rgba(255, 255, 255, 0.2);
}

.manual-hero__stat {
	flex: 1;
}

.manual-hero__stat--right {
	padding-left: 18px;
	margin-left: 18px;
	border-left: 1px solid rgba(255, 255, 255, 0.2);
}

.manual-hero__value {
	font-size: 28px;
	font-weight: 700;
	line-height: 1.2;
}

.manual-hero__value--small {
	font-size: 16px;
	word-break: break-all;
}

.manual-hero__label {
	margin-top: 8px;
	font-size: 13px;
	color: rgba(255, 255, 255, 0.84);
}

.manual-section {
	margin-top: 16px;
	padding: 18px 16px;
	border-radius: 24px;
	background: #fff;
	box-shadow: 0 12px 30px rgba(15, 23, 42, 0.06);
}

.manual-section__header {
	margin-bottom: 6px;
}

.manual-section__title {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.manual-section__subtitle {
	margin-top: 6px;
	font-size: 13px;
	color: #6b7280;
}

.manual-card {
	display: flex;
	padding: 16px 0;
	border-bottom: 1px solid #eef2f7;
}

.manual-card:last-child {
	border-bottom: none;
	padding-bottom: 4px;
}

.manual-card__index {
	width: 38px;
	height: 38px;
	flex-shrink: 0;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 14px;
	background: #effbf7;
	color: #15916f;
	font-size: 15px;
	font-weight: 700;
}

.manual-card__body {
	flex: 1;
	margin-left: 12px;
	min-width: 0;
}

.manual-card__title-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
}

.manual-card__title {
	flex: 1;
	min-width: 0;
	font-size: 16px;
	font-weight: 700;
	color: #111827;
	line-height: 1.5;
}

.manual-card__summary {
	margin-top: 8px;
	font-size: 14px;
	line-height: 1.7;
	color: #6b7280;
	overflow: hidden;
	display: -webkit-box;
	-webkit-line-clamp: 2;
	-webkit-box-orient: vertical;
}

.manual-card__meta {
	display: flex;
	align-items: center;
	justify-content: space-between;
	margin-top: 12px;
}

.manual-card__time {
	font-size: 12px;
	color: #94a3b8;
}

.manual-card__tag {
	padding: 5px 10px;
	border-radius: 999px;
	background: #f2fbf8;
	font-size: 12px;
	color: #15916f;
}

.state-card {
	margin-top: 14px;
	padding: 40px 20px;
	border: 1px dashed #dbe4ee;
	border-radius: 22px;
	background: #fbfcff;
	text-align: center;
}

.state-card--empty {
	margin-top: 18px;
}

.state-card__icon {
	width: 52px;
	height: 52px;
	margin: 0 auto 14px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 20px;
	background: #effbf7;
}

.state-card__icon--spin {
	animation: manual-spin 1.1s linear infinite;
}

.state-card__title {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.state-card__desc {
	margin-top: 8px;
	font-size: 13px;
	line-height: 1.6;
	color: #6b7280;
}

.detail-sheet {
	background: #fff;
	border-radius: 28px 28px 0 0;
	padding: 12px 18px 20px;
}

.detail-sheet__handle {
	width: 52px;
	height: 4px;
	margin: 0 auto 14px;
	border-radius: 999px;
	background: #d1d5db;
}

.detail-sheet__top {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
}

.detail-sheet__copy {
	flex: 1;
	min-width: 0;
}

.detail-sheet__eyebrow {
	font-size: 12px;
	font-weight: 600;
	color: #15916f;
}

.detail-sheet__title {
	margin-top: 8px;
	font-size: 20px;
	font-weight: 700;
	line-height: 1.4;
	color: #111827;
}

.detail-sheet__time {
	margin-top: 8px;
	font-size: 12px;
	color: #94a3b8;
}

.detail-sheet__close {
	width: 36px;
	height: 36px;
	margin-left: 12px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 18px;
	background: #f3f4f6;
}

.detail-sheet__scroll {
	max-height: 62vh;
	margin-top: 18px;
}

.detail-sheet__rich {
	font-size: 15px;
	line-height: 1.85;
	color: #334155;
	word-break: break-word;
}

.detail-sheet__empty {
	padding: 28px 12px;
	text-align: center;
	font-size: 14px;
	color: #6b7280;
}

@keyframes manual-spin {
	from {
		transform: rotate(0deg);
	}

	to {
		transform: rotate(360deg);
	}
}
</style>
