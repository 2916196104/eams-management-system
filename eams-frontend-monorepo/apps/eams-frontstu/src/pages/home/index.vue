<script setup lang="ts">
import { computed, ref } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentSectionCard from "@/components/parent/ParentSectionCard.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "home",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "首页",
		titleNView: false,
	},
});

interface AdvertisementItem {
	id?: number | string;
	title?: string;
	content?: string;
	cover?: string;
	addTime?: string;
}

interface ScheduleItem {
	id?: number;
	startTime?: string;
	endTime?: string;
	courseStatusText?: string;
	scheduleType?: number;
	className?: string;
	courseName?: string;
	teacherName?: string;
	classroomName?: string;
	signInStatusText?: string;
	canSignIn?: boolean;
	canLeave?: boolean;
	canReserve?: boolean;
}

interface RegistrationRecordItem {
	id?: number;
	course_id?: number;
	course_name?: string;
	subject_name?: string;
	expire_date?: string;
	count_lesson_total?: number;
	count_lesson_complete?: number;
	count_lesson_remaining?: number;
	verify_state?: string | number;
	expired?: boolean;
}

const router = useRouter();
const userStore = useUserStore();
const { currentStudent, parentHomeActions } = storeToRefs(userStore);

const topNotice = ref<AdvertisementItem | null>(null);
const noticeLoading = ref(false);
const scheduleLoading = ref(false);
const coursesLoading = ref(false);
const todayScheduleList = ref<Array<ScheduleItem>>([]);
const myCourseList = ref<Array<RegistrationRecordItem>>([]);

const studentId = computed(() => Number(currentStudent.value?.id || 0));
const noticeText = computed(() => topNotice.value?.title || "暂无公告提醒");
const bannerStyle = computed(() => {
	if (topNotice.value?.cover) {
		return {
			backgroundImage: `linear-gradient(180deg, rgba(19,35,61,0.12), rgba(19,35,61,0.04)), url(${topNotice.value.cover})`,
		};
	}

	return {};
});
const scheduleRightText = computed(() => (todayScheduleList.value.length ? "全部" : "无课"));

// 公告数据标准化
function normalizeNotice(data: any): AdvertisementItem | null {
	if (!data) return null;
	return {
		id: data.id,
		title: data.title,
		content: data.content,
		cover: data.cover,
		addTime: data.addTime,
	};
}

// 课表数据标准化，仅保留普通课表
function normalizeScheduleList(data: any): Array<ScheduleItem> {
	const rows = Array.isArray(data?.rows) ? data.rows : Array.isArray(data) ? data : [];
	return rows
		.map((item: any) => ({
			id: Number(item?.id || 0) || undefined,
			startTime: item?.startTime,
			endTime: item?.endTime,
			courseStatusText: item?.state,
			scheduleType: item?.bookable ? 2 : 1,
			className: item?.className,
			courseName: item?.courseName,
			teacherName: item?.teacherNames,
			classroomName: item?.classroom,
			signInStatusText: item?.studentSignState,
			canSignIn: Boolean(item?.studentCanSign),
			canLeave: Boolean(item?.studentCanLeave),
			canReserve: Boolean(item?.bookable),
		}))
		.filter((item: ScheduleItem) => item.scheduleType !== 2 && !item.canReserve);
}

// 我的课程列表数据标准化
function normalizeCourseRows(data: any): Array<RegistrationRecordItem> {
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

// 获取顶部公告
function loadTopNotice() {
	noticeLoading.value = true;
	(Apis as any).sCenter
		.get_app_sCenter_advertisement()
		.then((res: any) => {
			topNotice.value = normalizeNotice(res?.data);
		})
		.catch(() => {
			topNotice.value = null;
		})
		.finally(() => {
			noticeLoading.value = false;
		});
}

// 获取首页红点提醒
function loadRedPoints() {
	if (!studentId.value) {
		userStore.setHomeRedPoints({});
		return;
	}
	(Apis as any).sCenter
		.get_app_sCenter_student_redpoint({
			params: {
				student_id: studentId.value,
			},
		})
		.then((res: any) => {
			userStore.setHomeRedPoints(res?.data || {});
		})
		.catch(() => {
			userStore.setHomeRedPoints({});
		});
}

// 首页“今日课表”复用课表接口
async function loadTodaySchedule() {
	scheduleLoading.value = true;
	try {
		const today = new Date();
		const queryDate = `${today.getFullYear()}-${`${today.getMonth() + 1}`.padStart(2, "0")}-${`${today.getDate()}`.padStart(2, "0")}`;
		const res: any = await (Apis as any).schedule.get_schedule_query({
			params: {
				date: queryDate,
				pageIndex: 1,
				pageSize: 20,
			},
		});
		todayScheduleList.value = normalizeScheduleList(res?.data).slice(0, 3);
	}
	catch {
		todayScheduleList.value = [];
	}
	finally {
		scheduleLoading.value = false;
	}
}

// 首页“我的课程”复用报名记录接口
async function loadMyCourses() {
	if (!studentId.value) {
		myCourseList.value = [];
		return;
	}

	coursesLoading.value = true;
	try {
		const res: any = await Apis.home.get_c1_registration_records_query_records({
			params: {
				student_id: studentId.value,
				exclude_expired: true,
				pageIndex: 1,
				pageSize: 3,
			},
		});
		myCourseList.value = normalizeCourseRows(res?.data).slice(0, 3);
	}
	catch {
		myCourseList.value = [];
	}
	finally {
		coursesLoading.value = false;
	}
}

// 页面跳转
function navigateTo(name: string) {
	if (!name) return;
	router.push({ name });
}

// 打开课表 tab
function openScheduleTab() {
	router.pushTab({ name: "schedule" });
}

// 打开我的课程列表
function openMyCourses() {
	router.push({ name: "signupRecord" });
}

// 打开公告列表
function openNoticeList() {
	router.push({ name: "noticeList" });
}

// 进入课程关联页面
function openCourse(item: RegistrationRecordItem) {
	if (!item.course_id) {
		openMyCourses();
		return;
	}

	router.push({
		path: "/subPages/parent/class-page",
		query: {
			course_id: String(item.course_id),
		},
	} as any);
}

// 首页统一加载逻辑
function loadHomeData() {
	loadTopNotice();
	loadRedPoints();
	loadTodaySchedule();
	loadMyCourses();
}

watch(studentId, () => {
	loadTodaySchedule();
	loadMyCourses();
	loadRedPoints();
});

onShow(() => {
	loadHomeData();
});
</script>

<template>
	<view class="parent-home">
		<view class="parent-home__content">
			<!-- 公告通知 -->
			<view class="parent-home__notice">
				<wd-notice-bar
					:text="[noticeText]"
					prefix="sound"
					:delay="3"
					:scrollable="true"
					custom-class="parent-home__notice-inner"
				>
					<template #suffix>
						<text class="parent-home__notice-more" @click="openNoticeList">更多</text>
					</template>
				</wd-notice-bar>
			</view>

			<!-- 顶部公告卡片 -->
			<view class="parent-home__banner" :style="bannerStyle" @click="openNoticeList">
				<view class="parent-home__banner-mask">
					<text class="parent-home__banner-tag">{{ noticeLoading ? "加载中" : "公告提醒" }}</text>
					<text class="parent-home__banner-title">{{ topNotice?.title || "暂无公告内容" }}</text>
					<text class="parent-home__banner-desc">{{ topNotice?.content || "点击查看全部公告" }}</text>
				</view>
			</view>

			<!-- 家长首页功能九宫格 -->
			<view class="parent-home__grid">
				<view
					v-for="item in parentHomeActions"
					:key="item.id"
					class="parent-home__grid-item"
					@click="navigateTo(item.routeName)"
				>
					<view v-if="item.redPoint" class="parent-home__redpoint">
						{{ item.redPoint > 99 ? "99+" : item.redPoint }}
					</view>
					<view class="parent-home__grid-icon" :style="{ color: item.iconColor }">
						<view :class="`${item.icon} text-30px`" />
					</view>
					<text class="parent-home__grid-text">{{ item.name }}</text>
				</view>
			</view>

			<!-- 当前学生信息卡片 -->
			<view class="student-card" @click="navigateTo('studentList')">
				<view class="student-card__left">
					<view class="student-card__avatar">{{ currentStudent?.avatarText }}</view>
					<view class="student-card__name">
						{{ currentStudent?.name }}
						<text class="student-card__gender">{{ currentStudent?.gender === "男" ? "♂" : "♀" }}</text>
					</view>
				</view>
				<view class="student-card__action">
					切换
					<view class="i-carbon:chevron-right text-16px" />
				</view>
			</view>

			<!-- 今日课表 -->
			<ParentSectionCard title="今日课表" :right-text="scheduleRightText" @right-click="openScheduleTab">
				<view v-if="todayScheduleList.length" class="home-list">
					<view v-for="item in todayScheduleList" :key="item.id" class="home-list__item" @click="openScheduleTab">
						<view class="home-list__main">
							<view class="home-list__title">{{ item.courseName || item.className || "未命名课程" }}</view>
							<view class="home-list__sub">{{ item.teacherName || "未安排老师" }} · {{ item.classroomName || "待定教室" }}</view>
						</view>
						<view class="home-list__side">
							<view class="home-list__time">{{ item.startTime }}-{{ item.endTime }}</view>
							<view class="home-list__tag">{{ item.courseStatusText || item.signInStatusText || "待上课" }}</view>
						</view>
					</view>
				</view>
				<ParentEmptyState v-else :text="scheduleLoading ? '加载中...' : '今日无课'" min-height="136px" />
			</ParentSectionCard>

			<!-- 我的课程 -->
			<ParentSectionCard title="我的课程" right-text="全部" @right-click="openMyCourses">
				<view v-if="myCourseList.length" class="home-list">
					<view v-for="item in myCourseList" :key="item.id" class="home-list__item" @click="openCourse(item)">
						<view class="home-list__main">
							<view class="home-list__title">{{ item.course_name || "未命名课程" }}</view>
							<view class="home-list__sub">{{ item.subject_name || "未设置科目" }}</view>
						</view>
						<view class="home-list__side">
							<view class="home-list__time">{{ item.count_lesson_remaining ?? 0 }}/{{ item.count_lesson_total ?? 0 }} 课次</view>
							<view class="home-list__tag" :class="{ 'home-list__tag--expired': item.expired }">
								{{ item.expired ? "已过期" : item.verify_state || "学习中" }}
							</view>
						</view>
					</view>
				</view>
				<ParentEmptyState v-else :text="coursesLoading ? '加载中...' : '未报名课程'" min-height="136px" />
			</ParentSectionCard>
		</view>
	</view>
</template>

<style scoped>
.parent-home {
	min-height: 100vh;
	background: #f5f7fb;
}

.parent-home__content {
	padding: 14px 12px 20px;
	display: flex;
	flex-direction: column;
	gap: 14px;
}

.parent-home__notice :deep(.parent-home__notice-inner) {
	padding: 12px 8px;
	border-radius: 14px;
	background: #fff7e8;
}

.parent-home__notice-more {
	font-size: 14px;
	font-weight: 600;
	color: #31c7a5;
}

.parent-home__banner {
	height: 168px;
	border-radius: 16px;
	background:
		radial-gradient(circle at 20% 20%, rgba(56, 199, 171, 0.18), transparent 30%),
		radial-gradient(circle at 80% 30%, rgba(91, 124, 255, 0.15), transparent 28%),
		linear-gradient(180deg, #ffffff 0%, #fbfcff 100%);
	background-size: cover;
	background-position: center;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
	overflow: hidden;
}

.parent-home__banner-mask {
	height: 100%;
	padding: 18px 18px 16px;
	display: flex;
	flex-direction: column;
	justify-content: flex-end;
	background: linear-gradient(180deg, rgba(255, 255, 255, 0.2), rgba(20, 30, 50, 0.08));
}

.parent-home__banner-tag {
	width: fit-content;
	padding: 4px 10px;
	margin-bottom: 10px;
	border-radius: 999px;
	background: rgba(49, 199, 165, 0.14);
	font-size: 12px;
	font-weight: 600;
	color: #1d9f83;
}

.parent-home__banner-title {
	font-size: 20px;
	font-weight: 700;
	color: #1f2937;
}

.parent-home__banner-desc {
	margin-top: 8px;
	font-size: 13px;
	line-height: 1.6;
	color: #566074;
	display: -webkit-box;
	overflow: hidden;
	-webkit-line-clamp: 2;
	-webkit-box-orient: vertical;
}

.parent-home__grid {
	display: grid;
	grid-template-columns: repeat(4, 1fr);
	background: #fff;
	border-radius: 16px;
	overflow: hidden;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.parent-home__grid-item {
	position: relative;
	padding: 14px 6px 12px;
	display: flex;
	flex-direction: column;
	align-items: center;
	gap: 8px;
	border-right: 1px solid #eff2f7;
	border-bottom: 1px solid #eff2f7;
}

.parent-home__grid-item:nth-child(4n) {
	border-right: none;
}

.parent-home__grid-item:nth-last-child(-n + 4) {
	border-bottom: none;
}

.parent-home__redpoint {
	position: absolute;
	top: 8px;
	right: 10px;
	min-width: 18px;
	height: 18px;
	padding: 0 5px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	background: #ff4d4f;
	font-size: 11px;
	font-weight: 700;
	line-height: 1;
	color: #fff;
}

.parent-home__grid-icon {
	width: 36px;
	height: 36px;
	display: flex;
	align-items: center;
	justify-content: center;
}

.parent-home__grid-text {
	font-size: 13px;
	color: #4b5563;
}

.student-card {
	padding: 14px 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-radius: 16px;
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	color: #fff;
}

.student-card__left {
	display: flex;
	align-items: center;
	gap: 12px;
}

.student-card__avatar {
	width: 40px;
	height: 40px;
	border-radius: 50%;
	background: rgba(255, 255, 255, 0.9);
	color: #31c7a5;
	font-size: 18px;
	font-weight: 700;
	display: flex;
	align-items: center;
	justify-content: center;
}

.student-card__name {
	font-size: 17px;
	font-weight: 600;
}

.student-card__gender {
	margin-left: 4px;
	font-size: 16px;
	color: #8ad8ff;
}

.student-card__action {
	display: flex;
	align-items: center;
	gap: 4px;
	font-size: 14px;
	font-weight: 500;
}

.home-list {
	padding: 8px 0;
}

.home-list__item {
	padding: 12px 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
	border-bottom: 1px solid #f1f3f7;
}

.home-list__item:last-child {
	border-bottom: none;
}

.home-list__main {
	flex: 1;
	min-width: 0;
}

.home-list__title {
	font-size: 15px;
	font-weight: 600;
	color: #1f2937;
}

.home-list__sub {
	margin-top: 6px;
	font-size: 12px;
	color: #8b95a7;
}

.home-list__side {
	display: flex;
	flex-direction: column;
	align-items: flex-end;
	gap: 6px;
}

.home-list__time {
	font-size: 12px;
	color: #4b5563;
}

.home-list__tag {
	padding: 4px 8px;
	border-radius: 999px;
	background: rgba(49, 199, 165, 0.12);
	font-size: 12px;
	color: #1ca386;
}

.home-list__tag--expired {
	background: rgba(255, 109, 109, 0.12);
	color: #ff6b6b;
}
</style>
