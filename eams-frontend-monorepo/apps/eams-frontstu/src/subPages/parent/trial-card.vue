<script setup lang="ts">
import { computed, ref } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useGlobalMessage } from "@/composables/useGlobalMessage";
import { useGlobalToast } from "@/composables/useGlobalToast";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "trialCard",
	style: {
		navigationBarTitleText: "试听卡",
		titleNView: false,
	},
});

type TrialCardTab = "unclaimed" | "claimed";

interface TrialCardItem {
	id?: number;
	courseId?: number;
	courseName?: string;
	title?: string;
	quantity?: number;
	remainingQuantity?: number;
	lessonCount?: number;
	expireDays?: number;
	endDate?: string;
	state?: number;
	addTime?: string;
}

interface TrialCardRule {
	content?: string;
	description?: string;
}

const userStore = useUserStore();
const globalMessage = useGlobalMessage();
const globalToast = useGlobalToast();
const { currentStudent, userInfo } = storeToRefs(userStore);

const activeTab = ref<TrialCardTab>("unclaimed");
const loading = ref(false);
const receivingId = ref<number | null>(null);
const cards = ref<Array<TrialCardItem>>([]);
const claimedCardIds = ref<number[]>([]);
const claimedCards = ref<Array<TrialCardItem>>([]);
const rule = ref<TrialCardRule | null>(null);

const title = computed(() => (activeTab.value === "unclaimed" ? "领取试听卡" : "我的试听卡"));
const emptyText = computed(() => (activeTab.value === "unclaimed" ? "暂无试听卡" : "暂无已领取试听卡"));
const currentUserId = computed(() => Number(userInfo.value?.id || 0));
const ruleSummary = computed(() => rule.value?.description || "领取试听卡后可以免费体验课程");

const availableCards = computed(() =>
	cards.value.filter((item) => item.state !== 0 && !claimedCardIds.value.includes(item.id || -1)),
);

const displayedCards = computed(() => {
	if (activeTab.value === "claimed") return claimedCards.value;
	return availableCards.value;
});

function cardStatusText(item: TrialCardItem) {
	if (item.state === 0) return "已停用";
	if ((item.remainingQuantity || 0) <= 0) return "已领完";
	return "可领取";
}

function cardStatusClass(item: TrialCardItem) {
	if (item.state === 0) return "trial-card__badge--disabled";
	if ((item.remainingQuantity || 0) <= 0) return "trial-card__badge--empty";
	return "trial-card__badge--active";
}

async function loadTrialCards() {
	const res: any = await Apis.home.get_c1_home_card_list();
	cards.value = Array.isArray(res?.data) ? res.data : [];
}

async function loadMyTrialCards() {
	if (!currentUserId.value) {
		claimedCards.value = [];
		return;
	}

	const res: any = await (Apis as any).home.get_app_sCenter_course_myTrialList({
		params: {
			userId: String(currentUserId.value || 0),
		},
	});
	claimedCards.value = Array.isArray(res?.data) ? res.data : [];
}

async function loadTrialCardRule() {
	const res: any = await Apis.home.get_c1_home_card_rule();
	rule.value = res?.data || null;
}

async function loadPageData() {
	loading.value = true;
	try {
		await Promise.all([loadTrialCards(), loadMyTrialCards(), loadTrialCardRule()]);
	} catch {
		cards.value = [];
		claimedCards.value = [];
		rule.value = null;
		uni.showToast({ title: "试听卡加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

async function refreshPage() {
	await loadPageData();
	uni.showToast({ title: "已刷新", icon: "none" });
}

function updateClaimedState(item: TrialCardItem) {
	if (!item.id) return;
	if (!claimedCardIds.value.includes(item.id)) {
		claimedCardIds.value = [...claimedCardIds.value, item.id];
	}
	if (!claimedCards.value.some((card) => card.id === item.id)) {
		claimedCards.value = [item, ...claimedCards.value];
	}
	cards.value = cards.value.map((card) => {
		if (card.id !== item.id) return card;
		return {
			...card,
			remainingQuantity: Math.max((card.remainingQuantity || 1) - 1, 0),
		};
	});
}

function confirmClaim(item: TrialCardItem) {
	if (item.state === 0 || (item.remainingQuantity || 0) <= 0) return;
	if (!currentUserId.value || !currentStudent.value?.id) {
		globalToast.error("缺少用户或学生信息");
		return;
	}

	globalMessage.confirm({
		title: "领取试听卡",
		msg: `确认领取“${item.title || "试听卡"}”吗？`,
		success: async (res) => {
			if (res.action !== "confirm") return;
			await claimCard(item);
		},
	});
}

async function claimCard(item: TrialCardItem) {
	if (!item.id) return;

	receivingId.value = item.id;
	try {
		const res: any = await (Apis as any).home.put_c1_card_put({
			pathParams: {
				trialId: item.id,
			},
			data: {
				trialId: item.id,
				userId: currentUserId.value,
				studentId: Number(currentStudent.value?.id || 0),
				schoolId: 0,
				counselor: 0,
				courseId: Number(item.courseId || 0),
				lessonCount: Number(item.lessonCount || 0),
				endDate: item.endDate || "",
				addTime: new Date().toISOString(),
				studentCourseId: 0,
			},
		});

		updateClaimedState(item);
		activeTab.value = "claimed";
		await loadMyTrialCards();
		globalToast.success(res?.message || "领取成功");
	} catch {
		globalToast.error("领取试听卡失败");
	} finally {
		receivingId.value = null;
	}
}

onMounted(() => {
	loadPageData();
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar :title="title" :show-refresh="true" @refresh="refreshPage" />
		<view class="page-content">
			<view class="tab-bar">
				<view
					class="tab-bar__item"
					:class="{ 'tab-bar__item--active': activeTab === 'unclaimed' }"
					@click="activeTab = 'unclaimed'"
				>
					未领取
				</view>
				<view
					class="tab-bar__item"
					:class="{ 'tab-bar__item--active': activeTab === 'claimed' }"
					@click="activeTab = 'claimed'"
				>
					已领取
				</view>
			</view>

			<text class="page-tip">{{ ruleSummary }}</text>

			<view v-if="displayedCards.length" class="trial-card-list">
				<view v-for="item in displayedCards" :key="item.id" class="trial-card">
					<view class="trial-card__header">
						<view>
							<view class="trial-card__title">{{ item.title || "未命名试听卡" }}</view>
							<view class="trial-card__course">{{ item.courseName || "未设置课程" }}</view>
						</view>
						<view class="trial-card__badge" :class="cardStatusClass(item)">{{ cardStatusText(item) }}</view>
					</view>

					<view class="trial-card__meta">
						<view class="trial-card__meta-item">
							<text>课时数</text>
							<text>{{ item.lessonCount ?? 0 }} 节</text>
						</view>
						<view class="trial-card__meta-item">
							<text>剩余数量</text>
							<text>{{ item.remainingQuantity ?? 0 }} / {{ item.quantity ?? 0 }}</text>
						</view>
						<view class="trial-card__meta-item">
							<text>有效期</text>
							<text>领取后 {{ item.expireDays ?? 0 }} 天</text>
						</view>
						<view class="trial-card__meta-item">
							<text>截止日期</text>
							<text>{{ item.endDate || "未设置" }}</text>
						</view>
					</view>

					<view
						v-if="activeTab === 'unclaimed'"
						class="trial-card__action"
						:class="{
							'trial-card__action--disabled':
								item.state === 0 || (item.remainingQuantity || 0) <= 0 || receivingId === item.id,
						}"
						@click="confirmClaim(item)"
					>
						{{
							receivingId === item.id
								? "领取中..."
								: (item.remainingQuantity || 0) > 0 && item.state !== 0
									? "立即领取"
									: "暂不可领取"
						}}
					</view>

					<view v-else class="trial-card__claimed-tip">已领取，可前往课程中心查看使用情况</view>
				</view>
			</view>

			<ParentEmptyState v-else :text="loading ? '加载中...' : emptyText" min-height="180px" />

			<view v-if="rule?.content" class="trial-rule">
				<view class="trial-rule__title">试听卡使用规则</view>
				<view class="trial-rule__content">{{ rule.content }}</view>
			</view>
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.page-content {
	padding: 8px 12px 20px;
}

.tab-bar {
	padding: 4px;
	display: flex;
	border-radius: 10px;
	background: #f1f3f7;
}

.tab-bar__item {
	flex: 1;
	height: 34px;
	display: flex;
	align-items: center;
	justify-content: center;
	font-size: 15px;
	color: #6b7280;
	border-radius: 8px;
}

.tab-bar__item--active {
	background: #fff;
	color: #111827;
	font-weight: 600;
}

.page-tip {
	margin: 10px 0 12px;
	display: block;
	text-align: center;
	font-size: 12px;
	color: #94a3b8;
}

.trial-card-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.trial-card {
	padding: 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.trial-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.trial-card__title {
	font-size: 17px;
	font-weight: 700;
	color: #111827;
}

.trial-card__course {
	margin-top: 6px;
	font-size: 13px;
	color: #6b7280;
}

.trial-card__badge {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 600;
}

.trial-card__badge--active {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.trial-card__badge--empty {
	background: rgba(255, 152, 0, 0.12);
	color: #d98a00;
}

.trial-card__badge--disabled {
	background: rgba(148, 163, 184, 0.12);
	color: #64748b;
}

.trial-card__meta {
	margin-top: 14px;
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 10px 12px;
}

.trial-card__meta-item {
	padding: 10px 12px;
	display: flex;
	flex-direction: column;
	gap: 4px;
	border-radius: 12px;
	background: #f8fafc;
	font-size: 12px;
	color: #94a3b8;
}

.trial-card__meta-item text:last-child {
	font-size: 14px;
	font-weight: 600;
	color: #334155;
}

.trial-card__action {
	margin-top: 14px;
	height: 40px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	font-size: 14px;
	font-weight: 700;
	color: #fff;
}

.trial-card__action--disabled {
	background: #e5e7eb;
	color: #94a3b8;
}

.trial-card__claimed-tip {
	margin-top: 14px;
	padding-top: 12px;
	border-top: 1px solid #eef2f7;
	font-size: 13px;
	color: #64748b;
}

.trial-rule {
	margin-top: 14px;
	padding: 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.trial-rule__title {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.trial-rule__content {
	margin-top: 10px;
	font-size: 14px;
	line-height: 1.8;
	color: #475569;
	white-space: pre-wrap;
	word-break: break-word;
}
</style>
