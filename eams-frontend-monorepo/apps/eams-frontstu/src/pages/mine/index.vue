<script setup lang="ts">
import { computed, ref } from "vue";
import { storeToRefs } from "pinia";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "mine",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "我的",
		titleNView: false,
	},
});

interface MineMenuItem {
	key: string;
	title: string;
	icon: string;
	iconColor: string;
	routeName: string;
}

const userStore = useUserStore();
const router = useRouter();
const { currentStudent } = storeToRefs(userStore);

const userInfo = computed(() => userStore.userInfo);
const remainingLessons = ref(0);
const trialCardCount = ref(0);

const menuList: Array<MineMenuItem> = [
	{ key: "order", title: "选课订单", icon: "i-carbon:shopping-cart", iconColor: "#c87cff", routeName: "mineOrderList" },
	{ key: "signup", title: "报名记录", icon: "i-carbon:favorite-filled", iconColor: "#ff6b5f", routeName: "signupRecord" },
	{ key: "attendance", title: "上课记录", icon: "i-carbon:checkmark-filled", iconColor: "#2aa7ff", routeName: "attendanceRecord" },
	{ key: "parentInfo", title: "家长信息", icon: "i-carbon:user-profile", iconColor: "#6366f1", routeName: "parentInfo" },
	{ key: "studentRelated", title: "学员相关", icon: "i-carbon:user-multiple", iconColor: "#8b5cf6", routeName: "studentRelated" },
	{ key: "manual", title: "使用说明", icon: "i-carbon:document", iconColor: "#ec4899", routeName: "manual" },
];

const pagePathMap = {
	parentInfo: "/pages/parentInfo/index",
	studentRelated: "/pages/studentRelated/index",
	manual: "/pages/manual/index",
} as const;

function navigateTo(name: string) {
	const path = pagePathMap[name as keyof typeof pagePathMap];
	if (path) {
		router.push({ path });
		return;
	}

	router.push({ name });
}

// 顶部统计卡片跳转
function navigateStat(type: "lessons" | "trialCard") {
	switch (type) {
		case "lessons":
			navigateTo("signupRecord");
			break;
		case "trialCard":
			navigateTo("trialCard");
			break;
		default:
			break;
	}
}



// 加载剩余课时汇总
async function loadRemainingLessons(studentId: number) {
	try {
		const res: any = await Apis.home.get_c1_registration_records_query_records({
			params: {
				student_id: studentId,
				exclude_expired: true,
				pageIndex: 1,
				pageSize: 50,
			},
		});
		const rows = Array.isArray(res?.data?.rows) ? res.data.rows : [];
		remainingLessons.value = rows.reduce((sum: number, item: any) => {
			const totalLessons = Number(item?.count_lesson_total || 0);
			const completedLessons = Number(item?.count_lesson_complete || 0);
			return sum + Math.max(totalLessons - completedLessons, 0);
		}, 0);
	}
	catch {
		remainingLessons.value = 0;
	}
}

async function loadTrialCardCount() {
	try {
		const res: any = await (Apis as any).home.get_app_sCenter_course_myTrialList({
			params: {
				userId: String(userInfo.value.id || ""),
			},
		});
		trialCardCount.value = Array.isArray(res?.data) ? res.data.length : 0;
	}
	catch {
		trialCardCount.value = 0;
	}
}

// 统一刷新顶部统计数据
async function loadSummary() {
	const studentId = Number(currentStudent.value?.id || 0);
	if (!studentId) {
		remainingLessons.value = 0;
		trialCardCount.value = 0;
		return;
	}

	// 单独调用每个加载函数，捕获错误以避免触发全局错误提示
	await loadRemainingLessons(studentId).catch(() => {});
	await loadTrialCardCount().catch(() => {});
}

onShow(() => {
	loadSummary();
});
</script>

<template>
	<view class="mine-page">
		<view class="mine-page__content">
			<!-- 顶部用户信息卡片 -->
			<view class="mine-hero">
				<view class="mine-hero__top">
					<view class="mine-hero__user">
						<view class="mine-hero__avatar">
							<view class="i-carbon:user-avatar-filled-alt text-36px text-white" />
						</view>
						<view>
							<view class="mine-hero__name">{{ userInfo.nickName }}</view>
							<view class="mine-hero__phone">{{ userInfo.phone }}</view>
						</view>
					</view>
					<view class="mine-hero__action" @click="navigateTo('mineProfile')">
						资料
						<view class="i-carbon:chevron-right text-16px" />
					</view>
				</view>

				<view class="mine-hero__student" @click="navigateTo('studentList')">
					<text>当前登录学生：{{ currentStudent?.name || "未选择" }}</text>
					<view class="i-carbon:list text-18px text-#4b5563" />
				</view>

				<view class="mine-stats">
					<view class="mine-stats__item" @click="navigateStat('lessons')">
						<view class="mine-stats__value">{{ remainingLessons }}</view>
						<view class="mine-stats__label">剩余课时</view>
					</view>
					<view class="mine-stats__item" @click="navigateStat('trialCard')">
						<view class="mine-stats__value">{{ trialCardCount }}</view>
						<view class="mine-stats__label">试听卡</view>
					</view>
				</view>
			</view>

			<!-- 功能菜单 -->
			<view class="mine-menu">
				<view v-for="item in menuList" :key="item.key" class="mine-menu__item" @click="navigateTo(item.routeName)">
					<view class="mine-menu__left">
						<view :class="`${item.icon} text-18px`" :style="{ color: item.iconColor }" />
						<text class="mine-menu__title">{{ item.title }}</text>
					</view>
					<view class="i-carbon:chevron-right text-16px text-#b4bcc9" />
				</view>
			</view>
		</view>
	</view>
</template>

<style scoped>
.mine-page {
	min-height: 100vh;
	background: #f5f7fb;
}

.mine-page__content {
	padding: 8px 0 20px;
}

.mine-hero {
	overflow: hidden;
	background: #fff;
}

.mine-hero__top {
	padding: 14px 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	color: #fff;
}

.mine-hero__user {
	display: flex;
	align-items: center;
	gap: 12px;
}

.mine-hero__avatar {
	width: 48px;
	height: 48px;
	border-radius: 50%;
	background: rgba(255, 255, 255, 0.28);
	display: flex;
	align-items: center;
	justify-content: center;
}

.mine-hero__name {
	font-size: 18px;
	font-weight: 700;
}

.mine-hero__phone {
	margin-top: 6px;
	font-size: 13px;
	color: rgba(255, 255, 255, 0.92);
}

.mine-hero__action {
	display: flex;
	align-items: center;
	gap: 4px;
	font-size: 15px;
	font-weight: 600;
}

.mine-hero__student {
	padding: 12px 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	background: rgba(49, 199, 165, 0.42);
	font-size: 15px;
	color: #1f2937;
}

.mine-stats {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	background: #fff;
}

.mine-stats__item {
	padding: 16px 8px 14px;
	position: relative;
	text-align: center;
}

.mine-stats__item + .mine-stats__item {
	border-left: 1px solid #eef2f7;
}

.mine-stats__value {
	font-size: 28px;
	font-weight: 700;
	color: #1f2937;
}

.mine-stats__label {
	margin-top: 8px;
	font-size: 13px;
	color: #6b7280;
}

.mine-menu {
	margin-top: 10px;
	background: #fff;
}

.mine-menu__item {
	padding: 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-bottom: 1px solid #eef2f7;
}

.mine-menu__item:last-child {
	border-bottom: none;
}

.mine-menu__left {
	display: flex;
	align-items: center;
	gap: 10px;
}

.mine-menu__title {
	font-size: 15px;
	color: #374151;
}
</style>
