<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { withTeacherBackQuery } from "@/utils/teacherNavigation";

definePage({
	name: "teacherHomeworkList",
	style: {
		navigationBarTitleText: "作业列表",
		titleNView: false,
	},
});

interface HomeworkClassOption {
	id?: number | string;
	name: string;
}

interface HomeworkRecordItem {
	id: string;
	title: string;
	className: string;
	submitCount: number;
	createTime: string;
}

const router = useRouter();
const currentRoute = useRoute();
const userStore = useUserStore();
const { teacherInfo } = storeToRefs(userStore);

const classLoading = ref(false);
const loading = ref(false);
const loadingMore = ref(false);
const pageIndex = ref(1);
const pages = ref(0);
const total = ref(0);
const pageSize = 10;
const selectedClassId = ref("");
const classOptions = ref<HomeworkClassOption[]>([]);
const homeworkList = ref<HomeworkRecordItem[]>([]);

const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeClassOptions(source: unknown) {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source ?? {};
	const rawRows = Array.isArray(payload.rows)
		? payload.rows
		: Array.isArray(payload.list)
			? payload.list
			: Array.isArray(payload)
				? payload
				: [];

	return rawRows.map((item: any, index: number) => {
		return {
			id: item.id ?? item.classId ?? item.class_id,
			name: item.className || item.classname || item.myclass || item.name || `班级${index + 1}`,
		} satisfies HomeworkClassOption;
	});
}

function normalizeHomeworkRows(source: unknown) {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source ?? {};
	const rawRows = Array.isArray(payload.rows)
		? payload.rows
		: Array.isArray(payload.list)
			? payload.list
			: Array.isArray(payload)
				? payload
				: [];

	return rawRows.map((item: any, index: number) => {
		return {
			id: String(item.homework_id ?? item.id ?? `homework-${index}`),
			title: item.title || `作业${index + 1}`,
			className: item.class_name || item.className || "--",
			submitCount: Number(item.submit_count ?? item.submitCount ?? 0),
			createTime: item.create_time || item.createTime || "--",
		} satisfies HomeworkRecordItem;
	});
}

async function ensureTeacherInfo() {
	await userStore.loadCurrentUserInfo();
}

async function loadClassOptions() {
	classLoading.value = true;
	try {
		const response = await (Apis as any).class.get_class_query_myclass({
			params: {
				pageIndex: 1,
				pageSize: 50,
			},
		});

		classOptions.value = normalizeClassOptions(response);
		if (!selectedClassId.value) {
			const firstValid = classOptions.value.find((item) => item.id !== undefined && item.id !== null && item.id !== "");
			selectedClassId.value = firstValid ? String(firstValid.id) : "";
		}
	} catch {
		classOptions.value = [];
		uni.showToast({ title: "班级列表加载失败", icon: "none" });
	} finally {
		classLoading.value = false;
	}
}

async function loadHomework(nextPage = 1, append = false) {
	if (!selectedClassId.value) {
		homeworkList.value = [];
		return;
	}

	if (!teacherInfo.value.id) {
		await ensureTeacherInfo();
	}

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const response = await (Apis as any).homework.get_homework_record_list({
			params: {
				homeworkId: selectedClassId.value,
				status: undefined,
			},
		});

		const payload = (response as any)?.data?.data ?? (response as any)?.data ?? response ?? {};
		const rows = normalizeHomeworkRows(response);
		pageIndex.value = Number(payload.pageIndex ?? payload.page ?? nextPage);
		pages.value = Number(payload.pages ?? payload.total_page ?? (rows.length ? 1 : 0));
		total.value = Number(payload.total ?? rows.length);
		homeworkList.value = append ? [...homeworkList.value, ...rows] : rows;
	} catch {
		if (!append) homeworkList.value = [];
		uni.showToast({ title: "作业列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

function selectClass(id?: string | number) {
	if (id === undefined || id === null || id === "") {
		uni.showToast({ title: "当前班级缺少 ID，无法查询作业", icon: "none" });
		return;
	}

	selectedClassId.value = String(id);
	void loadHomework(1, false);
}

function goPublishPage() {
	router.push({
		name: "teacherHomeworkPublish",
		query: withTeacherBackQuery(currentRoute),
	} as any);
}

function openDetail(item: HomeworkRecordItem) {
	router.push({
		name: "teacherHomeworkDetail",
		query: withTeacherBackQuery(currentRoute, {
			homework_id: item.id,
			title: item.title,
		}),
	} as any);
}

async function refreshPage() {
	await Promise.all([ensureTeacherInfo(), loadClassOptions()]);
	if (selectedClassId.value) {
		await loadHomework(1, false);
	}
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadHomework(pageIndex.value + 1, true);
}

onShow(() => {
	void refreshPage();
});
</script>

<template>
  <view class="teacher-homework-page">
    <teacher-nav-bar title="作业列表" @refresh="refreshPage" />

    <view class="teacher-homework-page__content">
      <view class="teacher-homework-page__classes">
        <view
          v-for="item in classOptions"
          :key="`${item.id ?? item.name}`"
          class="teacher-homework-page__class-chip"
          :class="{ 'teacher-homework-page__class-chip--active': selectedClassId === String(item.id) }"
          @click="selectClass(item.id)"
        >
          {{ item.name }}
        </view>
      </view>

      <view v-if="classOptions.length && !selectedClassId" class="teacher-homework-page__tip">
        班级接口暂未返回可用 ID，当前无法查询作业数据。
      </view>

      <view v-if="homeworkList.length" class="teacher-homework-page__summary">
        共 {{ total }} 条作业
      </view>

      <view v-if="homeworkList.length" class="teacher-homework-page__list">
        <view v-for="item in homeworkList" :key="item.id" class="teacher-homework-card" @click="openDetail(item)">
          <view class="teacher-homework-card__header">
            <view class="teacher-homework-card__title">
              {{ item.title }}
            </view>
            <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
          </view>
          <view class="teacher-homework-card__meta">
            班级：{{ item.className }}
          </view>
          <view class="teacher-homework-card__meta">
            提交人数：{{ item.submitCount }}
          </view>
          <view class="teacher-homework-card__meta">
            创建时间：{{ item.createTime }}
          </view>
        </view>
      </view>

      <teacher-empty-state
        v-else
        :title="classLoading || loading ? '加载中...' : classOptions.length ? '暂无作业记录' : '暂无班级信息'"
        compact
      />

      <view v-if="hasMore" class="teacher-homework-page__more" @click="loadMore">
        {{ loadingMore ? "加载中..." : "加载更多" }}
      </view>
    </view>

    <view class="teacher-homework-page__action">
      <wd-button type="primary" block @click="goPublishPage">
        布置新作业
      </wd-button>
    </view>
  </view>
</template>

<style scoped>
.teacher-homework-page {
	min-height: 100vh;
	padding-bottom: calc(env(safe-area-inset-bottom) + 86px);
	background: #f5f6fa;
}

.teacher-homework-page__content {
	padding: 12px;
}

.teacher-homework-page__classes {
	display: flex;
	flex-wrap: wrap;
	gap: 8px;
}

.teacher-homework-page__class-chip {
	border-radius: 999px;
	background: #fff;
	padding: 8px 12px;
	font-size: 13px;
	color: #667085;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-homework-page__class-chip--active {
	background: #31c7a5;
	color: #fff;
}

.teacher-homework-page__tip {
	margin-top: 12px;
	border-radius: 14px;
	background: #fff7ed;
	padding: 12px 14px;
	font-size: 13px;
	line-height: 1.7;
	color: #f97316;
}

.teacher-homework-page__summary {
	margin-top: 14px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-homework-page__list {
	margin-top: 12px;
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.teacher-homework-card {
	border-radius: 18px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-homework-card__header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.teacher-homework-card__title {
	flex: 1;
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.teacher-homework-card__meta {
	margin-top: 10px;
	font-size: 13px;
	color: #667085;
}

.teacher-homework-page__more {
	margin: 16px auto 0;
	width: fit-content;
	font-size: 13px;
	color: #31c7a5;
}

.teacher-homework-page__action {
	position: fixed;
	right: 12px;
	bottom: calc(env(safe-area-inset-bottom) + 18px);
	left: 12px;
}
</style>
