<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { withTeacherBackQuery } from "@/utils/teacherNavigation";
import { Apis } from "@/api";

definePage({
	name: "teacherSignupRecord",
	style: {
		navigationBarTitleText: "报名记录",
		titleNView: false,
	},
});

interface SignupRecordItem {
	id: string;
	title: string;
	subtitle: string;
	meta: string;
}

const loading = ref(false);
const loadingMore = ref(false);
const pageIndex = ref(1);
const pages = ref(0);
const total = ref(0);
const records = ref<SignupRecordItem[]>([]);
const pageSize = 10;
const router = useRouter();
const currentRoute = useRoute();

const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeRecordRows(data: any): SignupRecordItem[] {
	if (typeof data === "string") {
		return data
			.split(/\r?\n/)
			.map((item) => item.trim())
			.filter(Boolean)
			.map((item, index) => ({
				id: `text-${index}`,
				title: item,
				subtitle: "报名记录",
				meta: "",
			}));
	}

	const rows = Array.isArray(data)
		? data
		: Array.isArray(data?.rows)
			? data.rows
			: Array.isArray(data?.list)
				? data.list
				: Array.isArray(data?.records)
					? data.records
					: [];

	return rows.map((item: any, index: number) => {
		const title = item.courseName || item.course_name || item.title || item.name || `报名记录${index + 1}`;
		const studentName = item.studentName || item.student_name || item.name || "";
		const mobile = item.mobile || item.phone || "";
		const addTime = item.addTime || item.add_time || item.createTime || "";
		const state = item.state || item.status || item.verifyState || "";

		return {
			id: String(item.id ?? item.recordId ?? item.orderNo ?? `${title}-${index}`),
			title,
			subtitle: [studentName, mobile].filter(Boolean).join(" / ") || "报名学员信息",
			meta: addTime || state || "",
		} satisfies SignupRecordItem;
	});
}

function parseRecordPayload(source: any) {
	const payload = source?.data?.data ?? source?.data ?? source;
	const rows = normalizeRecordRows(payload);

	return {
		pageIndex: Number(payload?.pageIndex ?? payload?.page_index ?? 1),
		pages: Number(payload?.pages ?? payload?.total_page ?? (rows.length ? 1 : 0)),
		total: Number(payload?.total ?? rows.length),
		rows,
	};
}

async function loadRecords(nextPage = 1, append = false) {
	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await (Apis as any).workbench.get_workbench_RegisterRecordList({
			params: {
				pageIndex: nextPage,
				pageSize,
			},
		});

		const payload = parseRecordPayload(res);
		pageIndex.value = payload.pageIndex;
		pages.value = payload.pages;
		total.value = payload.total;
		records.value = append ? [...records.value, ...payload.rows] : payload.rows;
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

function openDetail(item: SignupRecordItem) {
	router.push({
		name: "teacherSignupRecordDetail",
		query: withTeacherBackQuery(currentRoute, {
			id: item.id,
			title: item.title,
			subtitle: item.subtitle,
			meta: item.meta,
			pageIndex: "1",
			pageSize: String(pageSize),
		}),
	} as any);
}

onShow(() => {
	void loadRecords(1, false);
});
</script>

<template>
	<view class="teacher-record-page">
		<teacher-nav-bar title="报名记录" @refresh="refreshPage" />

		<view class="teacher-record-page__content">
			<view v-if="records.length" class="teacher-record-page__summary">共 {{ total }} 条记录</view>

			<view v-if="records.length" class="teacher-record-list">
				<view v-for="item in records" :key="item.id" class="teacher-record-item" @click="openDetail(item)">
					<view class="teacher-record-item__title">{{ item.title }}</view>
					<view v-if="item.subtitle" class="teacher-record-item__subtitle">{{ item.subtitle }}</view>
					<view v-if="item.meta" class="teacher-record-item__meta">{{ item.meta }}</view>
				</view>
			</view>

			<teacher-empty-state v-else :title="loading ? '加载中...' : '暂无报名信息'" compact />

			<view v-if="hasMore" class="teacher-record-page__more" @click="loadMore">
				{{ loadingMore ? "加载中..." : "加载更多" }}
			</view>
		</view>
	</view>
</template>

<style scoped>
.teacher-record-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-record-page__content {
	padding: 12px;
}

.teacher-record-page__summary {
	margin-bottom: 10px;
	padding: 0 2px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-record-list {
	display: flex;
	flex-direction: column;
	gap: 10px;
}

.teacher-record-item {
	border-radius: 16px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-record-item__title {
	font-size: 16px;
	font-weight: 600;
	color: #111827;
}

.teacher-record-item__subtitle {
	margin-top: 8px;
	font-size: 14px;
	color: #667085;
}

.teacher-record-item__meta {
	margin-top: 8px;
	font-size: 12px;
	color: #98a2b3;
}

.teacher-record-page__more {
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
