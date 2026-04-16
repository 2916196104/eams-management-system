<script setup lang="ts">
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import TeacherSectionCard from "@/components/teacher/TeacherSectionCard.vue";
import { withTeacherBackQuery } from "@/utils/teacherNavigation";

definePage({
	name: "mine",
	layout: "page",
	style: {
		navigationBarTitleText: "教师资料",
		titleNView: false,
	},
});

const router = useRouter();
const currentRoute = useRoute();
const userStore = useUserStore();
const { teacherInfo } = storeToRefs(userStore);

function navigateTo(name: string) {
	router.push({
		name,
		query: withTeacherBackQuery(currentRoute),
	} as any);
}

onShow(() => {
	void userStore.loadCurrentUserInfo();
});
</script>

<template>
	<view class="teacher-profile-page">
		<teacher-nav-bar title="教师资料" :show-refresh="false" />
		<view class="teacher-profile-card">
			<view class="teacher-profile-card__avatar">
				<wd-avatar :text="teacherInfo.name" size="large" bg-color="#1699ff" color="#fff" />
			</view>
			<view class="teacher-profile-card__main">
				<text class="teacher-profile-card__name">{{ teacherInfo.name }}</text>
				<text class="teacher-profile-card__meta">{{ teacherInfo.role }}</text>
				<text class="teacher-profile-card__meta">{{ teacherInfo.phone || "未设置手机号" }}</text>
			</view>
		</view>

		<teacher-section-card title="基础设置">
			<wd-cell-group border custom-class="overflow-hidden rounded-2!">
				<wd-cell title="主题设置" is-link @click="navigateTo('them')" />
				<wd-cell title="关于系统" is-link @click="navigateTo('about')" />
			</wd-cell-group>
		</teacher-section-card>
	</view>
</template>

<style scoped>
.teacher-profile-page {
	min-height: 100vh;
	padding: 0 12px 18px;
	background: #f5f6fa;
}

.teacher-profile-card {
	display: flex;
	align-items: center;
	gap: 14px;
	margin-top: 12px;
	border-radius: 14px;
	background: #fff;
	padding: 18px 16px;
}

.teacher-profile-card__main {
	display: flex;
	flex-direction: column;
	gap: 4px;
}

.teacher-profile-card__name {
	font-size: 18px;
	font-weight: 600;
	color: #111827;
}

.teacher-profile-card__meta {
	font-size: 14px;
	color: #98a2b3;
}
</style>
