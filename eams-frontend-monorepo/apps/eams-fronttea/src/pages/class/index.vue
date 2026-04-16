<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { withTeacherBackQuery } from "@/utils/teacherNavigation";
import { Apis } from "@/api";

definePage({
	name: "class",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "我的班级",
		titleNView: false,
	},
});

interface TeacherClassItem {
	id?: number | string;
	classId?: number | string;
	name: string;
	teacher: string;
	course: string;
	number: string;
}

const router = useRouter();
const currentRoute = useRoute();

const loading = ref(false);
const loadingMore = ref(false);
const pageIndex = ref(1);
const pages = ref(0);
const total = ref(0);
const pageSize = 10;
const classList = ref<TeacherClassItem[]>([]);

const hasMore = computed(() => pageIndex.value < pages.value);

function normalizeRows(source: unknown): TeacherClassItem[] {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source ?? {};
	const rawRows = Array.isArray(payload)
		? payload
		: Array.isArray(payload.rows)
			? payload.rows
			: Array.isArray(payload.list)
				? payload.list
				: [];

	return rawRows.map((item: any, index: number) => {
		const classId = item.id ?? item.classId ?? item.class_id;
		return {
			id: classId,
			classId,
			name: item.className || item.classname || item.myclass || item.name || `班级${index + 1}`,
			teacher: item.teacher || item.teacherName || item.homeroom_teacher || "--",
			course: item.course || item.courseName || item.course_name || item.subject || "--",
			number: String(item.number ?? item.studentCount ?? item.num_of_people ?? item.maxStudentCount ?? "--"),
		} satisfies TeacherClassItem;
	});
}

async function loadClassList(nextPage = 1, append = false) {
	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const response = await (Apis as any).class.get_class({
			params: {
				pageIndex: nextPage,
				pageSize,
			},
		});

		const payload = (response as any)?.data?.data ?? (response as any)?.data ?? response ?? {};
		const rows = normalizeRows(response);
		pageIndex.value = Number(payload.pageIndex ?? payload.page_index ?? nextPage);
		pages.value = Number(payload.pages ?? payload.total_page ?? (rows.length ? 1 : 0));
		total.value = Number(payload.total ?? rows.length);
		classList.value = append ? [...classList.value, ...rows] : rows;
	} catch (error) {
		console.error("加载班级列表失败:", error);
		if (!append) classList.value = [];
		uni.showToast({ title: "班级列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

function openClassDetail(item: TeacherClassItem) {
	if (item.classId === undefined || item.classId === null || item.classId === "") {
		uni.showToast({ title: "当前班级缺少ID，无法查看详情", icon: "none" });
		return;
	}

	router.push({
		name: "teacherClassDetail",
		query: withTeacherBackQuery(currentRoute, {
			classId: String(item.classId),
			name: item.name,
			teacher: item.teacher,
			course: item.course,
			number: item.number,
		}),
	} as any);
}

async function refreshPage() {
	await loadClassList(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadClassList(pageIndex.value + 1, true);
}

onShow(() => {
	void loadClassList(1, false);
});
</script>

<template>
  <view class="teacher-class">
    <teacher-nav-bar title="我的班级" @refresh="refreshPage" />
    <view class="teacher-class__content">
      <view v-if="classList.length" class="teacher-class__summary">
        共 {{ total }} 个班级
      </view>

      <view v-if="classList.length" class="teacher-class__list">
        <view v-for="item in classList" :key="`${item.classId ?? item.name}`" class="teacher-class-card" @click="openClassDetail(item)">
          <view class="teacher-class-card__header">
            <text class="teacher-class-card__title">
              {{ item.name }}
            </text>
            <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
          </view>
          <view class="teacher-class-card__meta">
            课程：{{ item.course }}
          </view>
          <view class="teacher-class-card__meta">
            班主任：{{ item.teacher }}
          </view>
          <view class="teacher-class-card__meta">
            人数：{{ item.number }}
          </view>
        </view>
      </view>

      <teacher-empty-state v-else :title="loading ? '加载中...' : '暂无班级信息'" compact />

      <view v-if="hasMore" class="teacher-class__more" @click="loadMore">
        {{ loadingMore ? "加载中..." : "加载更多" }}
      </view>
    </view>
  </view>
</template>

<style scoped>
.teacher-class {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-class__content {
	padding: 12px;
}

.teacher-class__summary {
	margin-bottom: 10px;
	padding: 0 2px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-class__list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.teacher-class-card {
	border-radius: 18px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-class-card__header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.teacher-class-card__title {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.teacher-class-card__meta {
	margin-top: 10px;
	font-size: 13px;
	color: #667085;
}

.teacher-class__more {
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
