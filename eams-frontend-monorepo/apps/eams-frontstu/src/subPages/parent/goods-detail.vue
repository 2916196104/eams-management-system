<script setup lang="ts">
import { computed, reactive, ref } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useGlobalMessage } from "@/composables/useGlobalMessage";
import { useGlobalToast } from "@/composables/useGlobalToast";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "goodsDetail",
	style: {
		navigationBarTitleText: "礼品详情",
		titleNView: false,
	},
});

// 礼品详情结构
interface GoodsDetail {
	deleted?: number;
	id?: number;
	schoolId?: number;
	addTime?: string;
	editTime?: string;
	creator?: number;
	editor?: number;
	materialId?: number;
	categoryId?: number;
	categoryName?: string;
	name?: string;
	credit?: number;
	saleNum?: number;
	viewNum?: number;
	cover?: string;
	content?: string;
	state?: number;
	orgId?: number;
	schoolName?: string;
	storage?: number;
	detailImages?: string;
	specs?: string;
	deliveryInfo?: string;
	limitNum?: number;
	exchangeStartTime?: string | number;
	exchangeEndTime?: string | number;
}

// 兑换规则与提交结果结构
interface ExchangeRule {
	id?: number;
	settingId?: number;
	name?: string;
	code?: string;
	value?: string;
	valueType?: string;
	info?: string;
	sortNum?: number;
}

interface ExchangeResult {
	exchangeId?: number;
	orderNo?: string;
	totalCredit?: number;
	status?: number;
	message?: string;
}

// 页面状态
const route = useRoute() as any;
const router = useRouter();
const userStore = useUserStore();
const globalToast = useGlobalToast();
const globalMessage = useGlobalMessage();
const { currentStudent } = storeToRefs(userStore);

const loading = ref(false);
const submitLoading = ref(false);
const showApplyPopup = ref(false);
const detail = ref<GoodsDetail | null>(null);
const exchangeRule = ref<ExchangeRule | null>(null);
const exchangeResult = ref<ExchangeResult | null>(null);

const form = reactive({
	num: 1,
	remark: "",
});

// 当前礼品与可提交状态
const goodsId = computed(() => Number(route.query?.id || 0));
const studentId = computed(() => Number(currentStudent.value?.id || 0));
const detailImages = computed(() =>
	String(detail.value?.detailImages || "")
		.split(",")
		.map((item) => item.trim())
		.filter(Boolean),
);
const canSubmit = computed(() => {
	return Number(detail.value?.state) === 1 && Number(detail.value?.storage || 0) > 0;
});

function formatTime(value?: string | number) {
	if (!value) return "未设置";
	const date = new Date(value);
	if (Number.isNaN(date.getTime())) return String(value);
	const year = date.getFullYear();
	const month = `${date.getMonth() + 1}`.padStart(2, "0");
	const day = `${date.getDate()}`.padStart(2, "0");
	const hour = `${date.getHours()}`.padStart(2, "0");
	const minute = `${date.getMinutes()}`.padStart(2, "0");
	return `${year}-${month}-${day} ${hour}:${minute}`;
}

function exchangeStateText(state?: number) {
	return Number(state) === 1 ? "可兑换" : "暂不可兑换";
}

function orderStateText(status?: number) {
	switch (Number(status)) {
		case 1:
			return "已提交";
		case 2:
			return "处理中";
		case 3:
			return "已完成";
		default:
			return "待审核";
	}
}

function resetForm() {
	form.num = 1;
	form.remark = "";
}

function openApplyPopup() {
	if (!detail.value?.id) {
		globalToast.error("缺少礼品信息");
		return;
	}
	if (!studentId.value) {
		globalToast.error("缺少学生信息");
		return;
	}
	if (!canSubmit.value) {
		globalToast.warning("当前礼品暂不可兑换");
		return;
	}
	resetForm();
	showApplyPopup.value = true;
}

function closeApplyPopup() {
	if (submitLoading.value) return;
	showApplyPopup.value = false;
}

// 兑换申请表单校验
function validateForm() {
	const maxStorage = Number(detail.value?.storage || 0);
	const limitNum = Number(detail.value?.limitNum || 0);

	if (!form.num || form.num < 1) {
		globalToast.warning("兑换数量至少为 1");
		return false;
	}
	if (maxStorage && form.num > maxStorage) {
		globalToast.warning("兑换数量不能超过库存");
		return false;
	}
	if (limitNum && form.num > limitNum) {
		globalToast.warning("兑换数量不能超过限兑数量");
		return false;
	}
	return true;
}

// 提交兑换申请
async function submitExchange() {
	if (!detail.value?.id || !validateForm()) return;

	globalMessage.confirm({
		title: "提交兑换申请",
		msg: `确认兑换 ${form.num} 件“${detail.value.name || "当前礼品"}”吗？`,
		success: async (res) => {
			if (res.action !== "confirm") return;

			submitLoading.value = true;
			try {
				const response: any = await Apis.home.post_c1_exchange_submit({
					data: {
						goodsId: detail.value?.id,
						num: form.num,
						studentId: studentId.value,
						remark: form.remark.trim(),
					},
				});

				exchangeResult.value = response?.data || null;
				showApplyPopup.value = false;
				globalToast.success(response?.data?.message || response?.message || "兑换申请已提交");
			} catch {
				globalToast.error("兑换申请提交失败");
			} finally {
				submitLoading.value = false;
			}
		},
	});
}

function openRecordPage() {
	router.push({ name: "pointsRecord" });
}

// 加载礼品详情与兑换规则
async function loadDetail() {
	if (!goodsId.value) {
		detail.value = null;
		exchangeRule.value = null;
		return;
	}

	loading.value = true;
	try {
		const [detailRes, ruleRes]: any = await Promise.all([
			(Apis as any).home.get_c1_exchange_goods_detail_id({
				params: {
					id: goodsId.value,
				},
			}),
			Apis.home.get_c1_exchange_query_rule({
				params: {
					id: goodsId.value,
				},
			}),
		]);

		detail.value = detailRes?.data || null;
		exchangeRule.value = ruleRes?.data || null;
	} catch {
		detail.value = null;
		exchangeRule.value = null;
		uni.showToast({ title: "礼品详情加载失败", icon: "none" });
	} finally {
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
	<view class="detail-page">
		<ParentNavBar title="礼品详情" :show-refresh="true" @refresh="refreshPage" />
		<view class="detail-page__content">
			<!-- 礼品详情主体 -->
			<view v-if="detail" class="detail-card">
				<image v-if="detail.cover" :src="detail.cover" class="detail-card__cover" mode="aspectFill" />
				<view v-else class="detail-card__cover detail-card__cover--placeholder">
					<view class="i-carbon:gift text-42px text-#bcc4d1" />
				</view>

				<view class="detail-card__section">
					<view class="detail-card__title-row">
						<view class="detail-card__title">{{ detail.name || "未命名礼品" }}</view>
						<view class="detail-card__credit">{{ detail.credit || 0 }} 积分</view>
					</view>
					<view class="detail-card__meta">
						<text>{{ detail.categoryName || "未分类" }}</text>
						<text v-if="detail.schoolName">{{ detail.schoolName }}</text>
						<text>{{ exchangeStateText(detail.state) }}</text>
					</view>
				</view>

				<view class="detail-card__grid">
					<view class="detail-card__metric">
						<text class="detail-card__metric-label">库存</text>
						<text class="detail-card__metric-value">{{ detail.storage || 0 }}</text>
					</view>
					<view class="detail-card__metric">
						<text class="detail-card__metric-label">已兑换</text>
						<text class="detail-card__metric-value">{{ detail.saleNum || 0 }}</text>
					</view>
					<view class="detail-card__metric">
						<text class="detail-card__metric-label">浏览数</text>
						<text class="detail-card__metric-value">{{ detail.viewNum || 0 }}</text>
					</view>
					<view class="detail-card__metric">
						<text class="detail-card__metric-label">限兑数量</text>
						<text class="detail-card__metric-value">{{ detail.limitNum || 0 }}</text>
					</view>
				</view>

				<view class="detail-card__section">
					<view class="detail-card__label">礼品介绍</view>
					<rich-text v-if="detail.content" class="detail-card__rich" :nodes="detail.content" />
					<view v-else class="detail-card__text">暂无礼品介绍</view>
				</view>

				<view class="detail-card__section">
					<view class="detail-card__label">规格参数</view>
					<view class="detail-card__text">{{ detail.specs || "暂无规格参数" }}</view>
				</view>

				<view class="detail-card__section">
					<view class="detail-card__label">发货信息</view>
					<view class="detail-card__text">{{ detail.deliveryInfo || "暂无发货信息" }}</view>
				</view>

				<view class="detail-card__section">
					<view class="detail-card__label">兑换时间</view>
					<view class="detail-card__text">
						{{ formatTime(detail.exchangeStartTime) }} 至 {{ formatTime(detail.exchangeEndTime) }}
					</view>
				</view>

				<view class="detail-card__section">
					<view class="detail-card__label">{{ exchangeRule?.name || "兑换规则" }}</view>
					<view class="detail-card__text">
						{{ exchangeRule?.value || exchangeRule?.info || "暂无兑换规则" }}
					</view>
					<view
						v-if="exchangeRule?.info && exchangeRule?.value && exchangeRule.info !== exchangeRule.value"
						class="detail-card__subtext"
					>
						{{ exchangeRule.info }}
					</view>
				</view>

				<view v-if="exchangeResult" class="detail-card__section detail-card__result">
					<view class="detail-card__label">最近一次申请</view>
					<view class="detail-card__text">订单号：{{ exchangeResult.orderNo || "暂无" }}</view>
					<view class="detail-card__text">消耗积分：{{ exchangeResult.totalCredit || 0 }}</view>
					<view class="detail-card__text">状态：{{ orderStateText(exchangeResult.status) }}</view>
					<view class="detail-card__subtext">{{ exchangeResult.message || "兑换申请已提交" }}</view>
					<view class="detail-card__record-btn" @click="openRecordPage">查看兑换记录</view>
				</view>

				<view v-if="detailImages.length" class="detail-card__section">
					<view class="detail-card__label">详情图片</view>
					<view class="detail-card__images">
						<image
							v-for="(src, index) in detailImages"
							:key="`${src}-${index}`"
							:src="src"
							class="detail-card__detail-image"
							mode="widthFix"
						/>
					</view>
				</view>
			</view>

			<ParentEmptyState v-else :text="loading ? '加载中...' : '暂无详情'" min-height="180px" />
		</view>

		<!-- 底部兑换操作栏 -->
		<view v-if="detail" class="detail-page__footer">
			<view
				class="detail-page__submit-btn"
				:class="{ 'detail-page__submit-btn--disabled': !canSubmit }"
				@click="openApplyPopup"
			>
				{{ canSubmit ? "提交兑换申请" : "当前不可兑换" }}
			</view>
		</view>

		<!-- 兑换申请弹层 -->
		<view v-if="showApplyPopup" class="apply-popup">
			<view class="apply-popup__mask" @click="closeApplyPopup" />
			<view class="apply-popup__panel">
				<view class="apply-popup__title">填写兑换信息</view>

				<view class="apply-popup__field">
					<text class="apply-popup__label">兑换数量</text>
					<input v-model.number="form.num" class="apply-popup__input" type="number" placeholder="请输入兑换数量" />
				</view>

				<view class="apply-popup__field">
					<text class="apply-popup__label">备注</text>
					<textarea v-model="form.remark" class="apply-popup__textarea" placeholder="选填备注信息" />
				</view>

				<view class="apply-popup__actions">
					<view class="apply-popup__cancel" @click="closeApplyPopup">取消</view>
					<view class="apply-popup__confirm" @click="submitExchange">
						{{ submitLoading ? "提交中..." : "确认提交" }}
					</view>
				</view>
			</view>
		</view>
	</view>
</template>

<style scoped>
.detail-page {
	min-height: 100vh;
	background: #f5f7fb;
}

.detail-page__content {
	padding: 12px 12px 92px;
}

.detail-card {
	padding: 16px;
	border-radius: 18px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
	display: flex;
	flex-direction: column;
	gap: 16px;
}

.detail-card__cover {
	width: 100%;
	height: 220px;
	border-radius: 16px;
	background: #eef2f7;
}

.detail-card__cover--placeholder {
	display: flex;
	align-items: center;
	justify-content: center;
}

.detail-card__section {
	display: flex;
	flex-direction: column;
	gap: 8px;
}

.detail-card__title-row {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.detail-card__title {
	flex: 1;
	font-size: 20px;
	font-weight: 700;
	line-height: 1.5;
	color: #111827;
}

.detail-card__credit {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	background: rgba(39, 199, 159, 0.12);
	font-size: 13px;
	font-weight: 700;
	color: #12b48f;
}

.detail-card__meta {
	display: flex;
	flex-wrap: wrap;
	gap: 8px;
	font-size: 12px;
	color: #8b95a7;
}

.detail-card__grid {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 12px;
}

.detail-card__metric {
	padding: 12px;
	border-radius: 14px;
	background: #f8fafc;
	display: flex;
	flex-direction: column;
	gap: 6px;
}

.detail-card__metric-label {
	font-size: 12px;
	color: #8b95a7;
}

.detail-card__metric-value {
	font-size: 18px;
	font-weight: 700;
	color: #1f2937;
}

.detail-card__label {
	font-size: 13px;
	font-weight: 600;
	color: #94a3b8;
}

.detail-card__text,
.detail-card__rich {
	font-size: 15px;
	line-height: 1.8;
	color: #334155;
	word-break: break-all;
}

.detail-card__subtext {
	font-size: 13px;
	line-height: 1.7;
	color: #64748b;
}

.detail-card__result {
	padding: 14px;
	border-radius: 14px;
	background: linear-gradient(135deg, rgba(49, 199, 165, 0.08) 0%, rgba(39, 199, 159, 0.03) 100%);
}

.detail-card__record-btn {
	margin-top: 6px;
	align-self: flex-start;
	padding: 8px 14px;
	border-radius: 999px;
	background: rgba(39, 199, 159, 0.12);
	font-size: 13px;
	font-weight: 700;
	color: #12b48f;
}

.detail-card__images {
	display: flex;
	flex-direction: column;
	gap: 10px;
}

.detail-card__detail-image {
	width: 100%;
	border-radius: 14px;
	background: #eef2f7;
}

.detail-page__footer {
	position: fixed;
	left: 0;
	right: 0;
	bottom: 0;
	padding: 12px 16px calc(12px + env(safe-area-inset-bottom));
	background: rgba(245, 247, 251, 0.96);
}

.detail-page__submit-btn {
	height: 46px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	font-size: 16px;
	font-weight: 700;
	color: #fff;
	box-shadow: 0 10px 20px rgba(49, 199, 165, 0.22);
}

.detail-page__submit-btn--disabled {
	background: #cbd5e1;
	box-shadow: none;
}

.apply-popup {
	position: fixed;
	inset: 0;
	z-index: 30;
}

.apply-popup__mask {
	position: absolute;
	inset: 0;
	background: rgba(15, 23, 42, 0.32);
}

.apply-popup__panel {
	position: absolute;
	left: 0;
	right: 0;
	bottom: 0;
	padding: 20px 16px calc(20px + env(safe-area-inset-bottom));
	border-radius: 24px 24px 0 0;
	background: #fff;
	display: flex;
	flex-direction: column;
	gap: 14px;
}

.apply-popup__title {
	text-align: center;
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.apply-popup__field {
	display: flex;
	flex-direction: column;
	gap: 8px;
}

.apply-popup__label {
	font-size: 13px;
	font-weight: 600;
	color: #64748b;
}

.apply-popup__input,
.apply-popup__textarea {
	width: 100%;
	padding: 12px 14px;
	border-radius: 14px;
	background: #f8fafc;
	font-size: 14px;
	color: #111827;
	box-sizing: border-box;
}

.apply-popup__textarea {
	min-height: 84px;
}

.apply-popup__actions {
	margin-top: 4px;
	display: grid;
	grid-template-columns: 112px 1fr;
	gap: 12px;
}

.apply-popup__cancel,
.apply-popup__confirm {
	height: 44px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	font-size: 15px;
	font-weight: 700;
}

.apply-popup__cancel {
	background: #f1f5f9;
	color: #64748b;
}

.apply-popup__confirm {
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	color: #fff;
}
</style>
