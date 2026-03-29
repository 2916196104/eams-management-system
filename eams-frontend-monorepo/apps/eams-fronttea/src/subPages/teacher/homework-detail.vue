<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";

definePage({
	name: "teacherHomeworkDetail",
	style: {
		navigationBarTitleText: "作业详情",
		titleNView: false,
	},
});

interface HomeworkDetailInfo {
	id: string;
	title: string;
	className: string;
	content: string;
}

const route = useRoute() as { query?: Record<string, string | string[] | undefined> };
const userStore = useUserStore();

const loading = ref(false);
const detail = ref<HomeworkDetailInfo | null>(null);

function readQuery(key: string) {
	const value = route.query?.[key];
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

const homeworkId = computed(() => readQuery("homework_id"));

function normalizeDetail(source: unknown): HomeworkDetailInfo | null {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source;
	if (!payload || Array.isArray(payload)) return null;

	return {
		id: String(payload.homework_id ?? payload.id ?? homeworkId.value),
		title: payload.title || readQuery("title") || "--",
		className: payload.class_name || payload.className || "--",
		content: payload.content || "--",
	};
}

async function loadDetail() {
	if (!homeworkId.value) return;

	loading.value = true;
	try {
		await userStore.loadCurrentUserInfo();
		const response = await (Apis as any).homework.get_homework_detail({
			params: {
				homework_id: homeworkId.value,
				admin_id: userStore.teacherInfo.id,
			},
		});
		detail.value = normalizeDetail(response);
	} catch {
		detail.value = null;
		uni.showToast({ title: "作业详情加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

async function refreshPage() {
	await loadDetail();
	uni.showToast({ title: "已刷新", icon: "none" });
}

onShow(() => {
	void loadDetail();
});
</script>

<template>
	<view class="teacher-homework-detail-page">
		<teacher-nav-bar title="作业详情" @refresh="refreshPage" />

		<view class="teacher-homework-detail-page__content">
			<view v-if="detail" class="teacher-homework-detail-card">
				<view class="teacher-homework-detail-card__title">{{ detail.title }}</view>
				<view class="teacher-homework-detail-card__meta">班级：{{ detail.className }}</view>
				<view class="teacher-homework-detail-card__content">{{ detail.content }}</view>
			</view>

			<teacher-empty-state v-else :title="loading ? '加载中...' : '暂无作业详情'" compact />
		</view>
	</view>
</template>

<style scoped>
.teacher-homework-detail-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-homework-detail-page__content {
	padding: 12px;
}

.teacher-homework-detail-card {
	border-radius: 18px;
	background: #fff;
	padding: 18px 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-homework-detail-card__title {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.teacher-homework-detail-card__meta {
	margin-top: 10px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-homework-detail-card__content {
	margin-top: 16px;
	border-radius: 14px;
	background: #f8fafc;
	padding: 14px;
	font-size: 14px;
	line-height: 1.8;
	color: #475467;
	white-space: pre-wrap;
	word-break: break-word;
}
</style>
