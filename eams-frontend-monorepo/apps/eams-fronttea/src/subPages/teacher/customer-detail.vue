<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import TeacherSectionCard from "@/components/teacher/TeacherSectionCard.vue";
import { Apis } from "@/api";

definePage({
	name: "teacherCustomerDetail",
	style: {
		navigationBarTitleText: "客户详情",
		titleNView: false,
	},
});

interface CustomerDetailInfo {
	id: string;
	name: string;
	phone: string;
	sex: string;
	age: string;
	birthday: string;
	customerType: string;
	note: string;
}

interface CustomerLessonItem {
	id: string;
	name: string;
	progress: string;
	deadline: string;
	restTimes: string;
}

const route = useRoute() as { query?: Record<string, string | string[] | undefined> };

const loading = ref(false);
const lessonLoading = ref(false);
const detail = ref<CustomerDetailInfo | null>(null);
const lessons = ref<CustomerLessonItem[]>([]);

function readQuery(key: string) {
	const value = route.query?.[key];
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

const customerId = computed(() => readQuery("id"));

function normalizeDetail(source: unknown): CustomerDetailInfo | null {
	const payload = (source as any)?.data ?? source;
	if (!payload || Array.isArray(payload)) return null;

	return {
		id: String(payload.id ?? customerId.value),
		name: payload.myCustomerName || "--",
		phone: payload.phoneNumber || "--",
		sex: payload.sex || "--",
		age: payload.age !== undefined ? String(payload.age) : "--",
		birthday: payload.birth || "--",
		customerType: payload.type || "--",
		note: payload.notes || "--",
	};
}

function normalizeLessons(source: unknown) {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source ?? {};
	const rawRows = Array.isArray(payload?.list)
		? payload.list
		: Array.isArray(payload)
			? payload
			: Array.isArray(payload?.rows)
				? payload.rows
				: [];

	return rawRows.map((item: any, index: number) => {
		return {
			id: String(item.id ?? `lesson-${index}`),
			name: item.name || "--",
			progress: item.progress || "--",
			deadline: item.deadline || "--",
			restTimes: String(item.restTimes ?? item.remainingTimes ?? item.resttimes ?? "--"),
		} satisfies CustomerLessonItem;
	});
}

async function loadDetail() {
	if (!customerId.value) return;

	loading.value = true;
	try {
		const response = await (Apis as any).workbench.get_workbench_MyCustomers_get_cus_details({
			params: { id: customerId.value },
		});
		detail.value = normalizeDetail(response);
	} catch {
		detail.value = null;
		uni.showToast({ title: "客户详情加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

async function loadLessons() {
	if (!customerId.value) return;

	lessonLoading.value = true;
	try {
		const response = await (Apis as any).customer.get_customer_lesson({
			params: { id: customerId.value },
		});
		lessons.value = normalizeLessons(response);
	} catch {
		lessons.value = [];
		uni.showToast({ title: "客户课程加载失败", icon: "none" });
	} finally {
		lessonLoading.value = false;
	}
}

async function refreshPage() {
	await Promise.all([loadDetail(), loadLessons()]);
	uni.showToast({ title: "已刷新", icon: "none" });
}

onShow(() => {
	void refreshPage();
});
</script>

<template>
	<view class="teacher-customer-detail-page">
		<teacher-nav-bar title="客户详情" @refresh="refreshPage" />

		<view class="teacher-customer-detail-page__content">
			<view v-if="detail" class="teacher-customer-card">
				<view class="teacher-customer-card__title">{{ detail.name }}</view>
				<view class="teacher-customer-card__meta">{{ detail.phone }}</view>

				<view class="teacher-customer-card__grid">
					<view class="teacher-customer-card__field">
						<text class="teacher-customer-card__label">性别</text>
						<text class="teacher-customer-card__value">{{ detail.sex }}</text>
					</view>
					<view class="teacher-customer-card__field">
						<text class="teacher-customer-card__label">年龄</text>
						<text class="teacher-customer-card__value">{{ detail.age }}</text>
					</view>
					<view class="teacher-customer-card__field">
						<text class="teacher-customer-card__label">生日</text>
						<text class="teacher-customer-card__value">{{ detail.birthday }}</text>
					</view>
					<view class="teacher-customer-card__field">
						<text class="teacher-customer-card__label">客户类型</text>
						<text class="teacher-customer-card__value">{{ detail.customerType }}</text>
					</view>
				</view>

				<view class="teacher-customer-card__remark">
					<text class="teacher-customer-card__label">备注</text>
					<text class="teacher-customer-card__remark-text">{{ detail.note }}</text>
				</view>
			</view>

			<teacher-empty-state v-else :title="loading ? '加载中...' : '暂无客户详情'" compact />

			<teacher-section-card title="课程列表" :extra="lessons.length ? `${lessons.length} 门` : ''">
				<view v-if="lessons.length" class="teacher-customer-lessons">
					<view v-for="item in lessons" :key="item.id" class="teacher-customer-lesson">
						<view class="teacher-customer-lesson__title">{{ item.name }}</view>
						<view class="teacher-customer-lesson__meta">学习进度：{{ item.progress }}</view>
						<view class="teacher-customer-lesson__meta">有效期：{{ item.deadline }}</view>
						<view class="teacher-customer-lesson__meta">剩余次数：{{ item.restTimes }}</view>
					</view>
				</view>
				<teacher-empty-state v-else :title="lessonLoading ? '加载中...' : '暂无课程记录'" compact />
			</teacher-section-card>
		</view>
	</view>
</template>

<style scoped>
.teacher-customer-detail-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-customer-detail-page__content {
	padding: 12px;
}

.teacher-customer-card {
	border-radius: 18px;
	background: #fff;
	padding: 18px 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-customer-card__title {
	font-size: 20px;
	font-weight: 700;
	color: #111827;
}

.teacher-customer-card__meta {
	margin-top: 8px;
	font-size: 14px;
	color: #667085;
}

.teacher-customer-card__grid {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 12px;
	margin-top: 16px;
}

.teacher-customer-card__field {
	display: flex;
	flex-direction: column;
	gap: 6px;
	border-radius: 14px;
	background: #f8fafc;
	padding: 12px;
}

.teacher-customer-card__label {
	font-size: 12px;
	color: #98a2b3;
}

.teacher-customer-card__value {
	font-size: 14px;
	font-weight: 600;
	color: #344054;
}

.teacher-customer-card__remark {
	display: flex;
	flex-direction: column;
	gap: 8px;
	margin-top: 14px;
	border-radius: 14px;
	background: #f8fafc;
	padding: 12px;
}

.teacher-customer-card__remark-text {
	font-size: 14px;
	line-height: 1.7;
	color: #475467;
	word-break: break-word;
}

.teacher-customer-lessons {
	padding: 12px 14px 16px;
}

.teacher-customer-lesson {
	padding: 14px 0;
	border-bottom: 1px solid #edf0f5;
}

.teacher-customer-lesson:last-child {
	border-bottom: 0;
}

.teacher-customer-lesson__title {
	font-size: 15px;
	font-weight: 600;
	color: #111827;
}

.teacher-customer-lesson__meta {
	margin-top: 8px;
	font-size: 13px;
	color: #667085;
}
</style>
