<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherSectionCard from "@/components/teacher/TeacherSectionCard.vue";
import { withTeacherBackQuery } from "@/utils/teacherNavigation";

definePage({
	name: "home",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "工作台",
		titleNView: false,
	},
});

const router = useRouter();
const currentRoute = useRoute();
const userStore = useUserStore();
const { teacherInfo, quickActions, monthMetrics, getScheduleByDate } = storeToRefs(userStore);
const bannerTitle = computed(() => {
	const organization = teacherInfo.value.organization?.trim();
	if (!organization) return "零壹教务管理系统";
	return organization.replace(/宏之博|洪之博/g, "零壹");
});

const today = computed(() => {
	const now = new Date();
	const year = now.getFullYear();
	const month = String(now.getMonth() + 1).padStart(2, "0");
	const day = String(now.getDate()).padStart(2, "0");
	return `${year}-${month}-${day}`;
});

const todaySchedules = computed(() => getScheduleByDate.value(today.value));
const isTodayScheduleLoading = ref(false);

// 加载工作台首屏数据
async function loadHomeData() {
	isTodayScheduleLoading.value = true;
	try {
		await Promise.allSettled([userStore.loadCurrentUserInfo(), userStore.loadMonthlyMetrics(), userStore.loadScheduleByDate(today.value)]);
	} finally {
		isTodayScheduleLoading.value = false;
	}
}

// 统一处理快捷入口跳转
function navigate(action: (typeof quickActions.value)[number]) {
	if (action.routeType === "tab") {
		router.pushTab({ name: action.route });
		return;
	}

	router.push({
		name: action.route,
		query: withTeacherBackQuery(currentRoute),
	} as any);
}

// 从工作台直接进入课次点名详情
function openAttendanceDetail(lessonId?: number | string, date = today.value) {
	if (!lessonId) return;

	router.push({
		path: "/subPages/teacher/attendance-record",
		query: withTeacherBackQuery(currentRoute, {
			lesson_id: String(lessonId),
			date,
		}),
	} as any);
}

onShow(() => {
	void loadHomeData();
});
</script>

<template>
  <view class="teacher-home">
    <!-- 顶部应用栏 -->
    <view class="teacher-home__topbar">
      <view class="teacher-home__safe" />
      <view class="teacher-home__topbar-inner">
        <text class="teacher-home__topbar-title">
          系统工作台
        </text>
        <view class="teacher-home__manager">
          <view class="i-carbon:user-avatar-filled-alt text-14px text-#4c7cff" />
          <text>{{ teacherInfo.role }}</text>
        </view>
      </view>
    </view>

    <!-- 顶部横幅 -->
    <view class="teacher-home__banner">
      <view>
        <text class="teacher-home__banner-title">
          {{ bannerTitle }}
        </text>
        <text class="teacher-home__banner-subtitle">
          教培行业云化解决方案
        </text>
      </view>
      <view class="teacher-home__banner-visual">
        <view class="i-carbon:cloud text-72px text-white" />
        <view class="teacher-home__banner-rocket i-carbon:rocket text-36px text-#fffbe6" />
      </view>
    </view>

    <!-- 常用功能 -->
    <teacher-section-card title="常用功能">
      <view class="teacher-home__action-grid">
        <view v-for="action in quickActions" :key="action.id" class="teacher-home__action" @click="navigate(action)">
          <view class="teacher-home__action-icon" :style="{ backgroundColor: action.iconBg }">
            <view
              v-if="action.route === 'teacherAddStudent'"
              class="i-carbon:user-follow text-24px text-white"
            />
            <view v-else class="text-24px text-white" :class="[action.icon]" />
          </view>
          <text class="teacher-home__action-name">
            {{ action.name }}
          </text>
        </view>
      </view>
    </teacher-section-card>

    <!-- 今日课表 -->
    <teacher-section-card
      title="今日课表"
      :extra="isTodayScheduleLoading ? '加载中' : todaySchedules.length ? `${todaySchedules.length}节` : '无课'"
    >
      <view v-if="todaySchedules.length" class="teacher-home__schedule-list">
        <view
          v-for="item in todaySchedules"
          :key="item.id"
          class="teacher-home__schedule-item"
          @click="openAttendanceDetail(item.lessonId, today)"
        >
          <text class="teacher-home__schedule-time">
            {{ item.startTime }}-{{ item.endTime }}
          </text>
          <view class="teacher-home__schedule-main">
            <text class="teacher-home__schedule-course">
              {{ item.courseName }}
            </text>
            <text class="teacher-home__schedule-meta">
              {{ item.className }} / {{ item.classroom }}
            </text>
          </view>
        </view>
      </view>
      <teacher-empty-state v-else :title="isTodayScheduleLoading ? '加载中...' : '今日无课'" compact />
    </teacher-section-card>

    <!-- 我的本月数据 -->
    <teacher-section-card title="我的本月数据">
      <view class="teacher-home__metric-grid">
        <view v-for="metric in monthMetrics" :key="metric.id" class="teacher-home__metric">
          <text class="teacher-home__metric-value">
            {{ metric.value }}
          </text>
          <text class="teacher-home__metric-label">
            {{ metric.label }}
          </text>
        </view>
      </view>
    </teacher-section-card>
  </view>
</template>

<style scoped>
.teacher-home {
	min-height: 100vh;
	padding: 0 12px 18px;
	background: #f5f6fa;
}

.teacher-home__topbar {
	margin: 0 -12px;
	background: #fff;
}

.teacher-home__safe {
	height: env(safe-area-inset-top);
}

.teacher-home__topbar-inner {
	position: relative;
	display: flex;
	align-items: center;
	justify-content: center;
	height: 42px;
	padding: 0 16px;
}

.teacher-home__topbar-title {
	font-size: 18px;
	font-weight: 600;
	color: #101828;
}

.teacher-home__manager {
	position: absolute;
	right: 16px;
	display: flex;
	align-items: center;
	gap: 4px;
	font-size: 13px;
	color: #4c7cff;
}

.teacher-home__banner {
	display: flex;
	align-items: center;
	justify-content: space-between;
	margin-left: -12px;
	margin-right: -12px;
	padding: 22px 20px 18px;
	background: linear-gradient(135deg, #1699ff 0%, #0f8aef 60%, #0fc4ff 100%);
}

.teacher-home__banner-title {
	display: block;
	font-size: 34px;
	font-weight: 700;
	color: #fff;
	line-height: 1.25;
}

.teacher-home__banner-subtitle {
	display: block;
	margin-top: 8px;
	font-size: 18px;
	color: rgba(255, 255, 255, 0.92);
}

.teacher-home__banner-visual {
	position: relative;
	display: flex;
	align-items: center;
	justify-content: center;
	width: 108px;
	height: 88px;
}

.teacher-home__banner-rocket {
	position: absolute;
	right: 8px;
	bottom: 4px;
	transform: rotate(15deg);
}

.teacher-home__action-grid {
	display: grid;
	grid-template-columns: repeat(4, minmax(0, 1fr));
	gap: 18px 8px;
	padding: 18px 10px;
}

.teacher-home__action {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 10px;
}

.teacher-home__action-icon {
	display: flex;
	align-items: center;
	justify-content: center;
	width: 48px;
	height: 48px;
	border-radius: 50%;
}

.teacher-home__action-name {
	font-size: 14px;
	color: #344054;
}

.teacher-home__schedule-list {
	padding: 12px 14px 16px;
}

.teacher-home__schedule-item {
	display: flex;
	align-items: flex-start;
	gap: 12px;
	padding: 12px 0;
	border-bottom: 1px solid #eef1f6;
}

.teacher-home__schedule-item:last-child {
	border-bottom: 0;
}

.teacher-home__schedule-time {
	flex-shrink: 0;
	font-size: 14px;
	font-weight: 600;
	color: #1f2937;
}

.teacher-home__schedule-main {
	display: flex;
	flex-direction: column;
	gap: 4px;
}

.teacher-home__schedule-course {
	font-size: 15px;
	font-weight: 600;
	color: #1f2937;
}

.teacher-home__schedule-meta {
	font-size: 13px;
	color: #98a2b3;
}

.teacher-home__metric-grid {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	border-top: 1px solid #eef1f6;
	border-left: 1px solid #eef1f6;
}

.teacher-home__metric {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 8px;
	min-height: 92px;
	border-right: 1px solid #eef1f6;
	border-bottom: 1px solid #eef1f6;
}

.teacher-home__metric-value {
	font-size: 24px;
	font-weight: 600;
	color: #101828;
}

.teacher-home__metric-label {
	font-size: 13px;
	color: #98a2b3;
}
</style>
