<script setup lang="ts">
import { computed, ref, watch } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "signupRecord",
	style: {
		navigationBarTitleText: "报名记录",
		titleNView: false,
	},
});

interface RegistrationRecordItem {
	id?: number;
	student_id?: number;
	student_name?: string;
	course_id?: number;
	course_name?: string;
	subject_name?: string;
	add_time?: string;
	expire_date?: string;
	amount?: number;
	paid_amount?: number;
	count_lesson_total?: number;
	count_lesson_complete?: number;
	count_lesson_remaining?: number;
	lesson_type?: string | number;
	verify_state?: string | number;
	expired?: boolean;
}

const userStore = useUserStore();
const { currentStudent } = storeToRefs(userStore);
const router = useRouter();

const loading = ref(false);
const loadingMore = ref(false);
const excludeExpired = ref(false);
const pageIndex = ref(1);
const pageSize = 10;
const total = ref(0);
const pages = ref(0);
const records = ref<Array<RegistrationRecordItem>>([]);

const studentId = computed(() => Number(currentStudent.value?.id || 0));
const studentName = computed(() => currentStudent.value?.name || "");
const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeRows(data: any): Array<RegistrationRecordItem> {
	const rows = Array.isArray(data?.rows) ? data.rows : [];
	return rows.map((item: any) => {
		const totalLessons = Number(item?.count_lesson_total || 0);
		const completedLessons = Number(item?.count_lesson_complete || 0);
		return {
			...item,
			count_lesson_total: totalLessons,
			count_lesson_complete: completedLessons,
			count_lesson_remaining: Math.max(totalLessons - completedLessons, 0),
		};
	});
}

function formatAmount(value?: number) {
	return typeof value === "number" ? `¥${value.toFixed(2)}` : "¥0.00";
}

function expiryText(item: RegistrationRecordItem) {
	if (item.expired) return "已过期";
	return item.expire_date || "长期有效";
}

function expiryClass(item: RegistrationRecordItem) {
	return item.expired ? "record-tag--expired" : "record-tag--active";
}

async function loadRecords(nextPage = 1, append = false) {
	if (!studentId.value) {
		records.value = [];
		return;
	}

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await Apis.home.get_c1_registration_records_query_records({
			params: {
				student_id: studentId.value,
				exclude_expired: excludeExpired.value,
				pageIndex: nextPage,
				pageSize,
			},
		});

		const pageData = res?.data || {};
		const rows = normalizeRows(pageData);
		pageIndex.value = Number(pageData.pageIndex || nextPage);
		pages.value = Number(pageData.pages || 0);
		total.value = Number(pageData.total || 0);
		records.value = append ? [...records.value, ...rows] : rows;
	} catch {
		if (!append) records.value = [];
		uni.showToast({ title: "报名记录加载失败", icon: "none" });
	} finally {
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

function toggleExpiredFilter() {
	excludeExpired.value = !excludeExpired.value;
}

function openClassList(item: RegistrationRecordItem) {
	if (!item.course_id) return;
	router.push({
		path: "/subPages/parent/class-page",
		query: {
			course_id: String(item.course_id),
		},
	} as any);
}

watch(
	studentId,
	() => {
		loadRecords(1, false);
	},
	{ immediate: true },
);

watch(excludeExpired, () => {
	loadRecords(1, false);
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="报名记录" :show-refresh="true" @refresh="refreshPage" />
		<view class="page-content">
			<view class="record-toolbar">
				<view class="record-toolbar__summary">
					<text>{{ studentName || "当前学生" }}</text>
					<text>共 {{ total }} 条报名记录</text>
				</view>
				<view
					class="record-toolbar__filter"
					:class="{ 'record-toolbar__filter--active': excludeExpired }"
					@click="toggleExpiredFilter"
				>
					{{ excludeExpired ? "已排除过期课程" : "显示全部课程" }}
				</view>
			</view>

			<view v-if="records.length" class="record-list">
				<view v-for="item in records" :key="item.id" class="record-card" @click="openClassList(item)">
					<view class="record-card__header">
						<view>
							<view class="record-card__course">{{ item.course_name || "未命名课程" }}</view>
							<view class="record-card__subject">{{ item.subject_name || "未设置科目" }}</view>
						</view>
						<view class="record-card__header-right">
							<view class="record-tag" :class="expiryClass(item)">
								{{ expiryText(item) }}
							</view>
							<view class="i-carbon:chevron-right text-16px text-#c3cad5" />
						</view>
					</view>

					<view class="record-card__meta">
						<view class="record-card__meta-item">
							<text>报名时间</text>
							<text>{{ item.add_time || "暂无时间" }}</text>
						</view>
						<view class="record-card__meta-item">
							<text>课程金额</text>
							<text>{{ formatAmount(item.amount) }}</text>
						</view>
						<view class="record-card__meta-item">
							<text>实付金额</text>
							<text>{{ formatAmount(item.paid_amount) }}</text>
						</view>
						<view class="record-card__meta-item">
							<text>剩余课次</text>
							<text>{{ item.count_lesson_remaining ?? 0 }} / {{ item.count_lesson_total ?? 0 }}</text>
						</view>
					</view>

					<view class="record-card__footer">
						<text>{{ item.lesson_type || "未设置报名类型" }}</text>
						<text>{{ item.verify_state || "未设置审核状态" }}</text>
					</view>
				</view>

				<view v-if="hasMore" class="load-more" @click="loadMore">
					{{ loadingMore ? "加载中..." : "加载更多" }}
				</view>
			</view>

			<ParentEmptyState v-else :text="loading ? '加载中...' : '无报名课程'" min-height="180px" :card="false" />
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

.record-toolbar {
	display: flex;
	flex-direction: column;
	gap: 10px;
	margin-bottom: 12px;
}

.record-toolbar__summary {
	display: flex;
	align-items: center;
	justify-content: space-between;
	font-size: 13px;
	color: #8b95a7;
}

.record-toolbar__filter {
	width: fit-content;
	padding: 6px 12px;
	border-radius: 999px;
	background: #fff;
	font-size: 13px;
	font-weight: 600;
	color: #64748b;
	box-shadow: 0 4px 12px rgba(64, 86, 122, 0.04);
}

.record-toolbar__filter--active {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.record-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.record-card {
	padding: 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.record-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.record-card__header-right {
	display: flex;
	align-items: center;
	gap: 8px;
}

.record-card__course {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.record-card__subject {
	margin-top: 6px;
	font-size: 13px;
	color: #6b7280;
}

.record-tag {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 600;
}

.record-tag--active {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.record-tag--expired {
	background: rgba(239, 68, 68, 0.12);
	color: #dc2626;
}

.record-card__meta {
	margin-top: 14px;
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 10px 12px;
}

.record-card__meta-item {
	padding: 10px 12px;
	display: flex;
	flex-direction: column;
	gap: 4px;
	border-radius: 12px;
	background: #f8fafc;
	font-size: 12px;
	color: #94a3b8;
}

.record-card__meta-item text:last-child {
	font-size: 14px;
	font-weight: 600;
	color: #334155;
}

.record-card__footer {
	margin-top: 14px;
	padding-top: 12px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-top: 1px solid #eef2f7;
	font-size: 13px;
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
	color: #31c7a5;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}
</style>
