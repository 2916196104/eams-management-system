<script setup lang="ts">
import { storeToRefs } from "pinia";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "studentList",
	style: {
		navigationBarTitleText: "学生列表",
		titleNView: false,
	},
});

const userStore = useUserStore();
const { students, currentStudent } = storeToRefs(userStore);

function switchStudent(id: string) {
	userStore.setCurrentStudent(id);
	uni.navigateBack();
}

function goBack() {
	uni.navigateBack();
}

function addStudent() {
	uni.showToast({ title: "后续接入添加学生", icon: "none" });
}

function refreshPage() {
	uni.showToast({ title: "已刷新", icon: "none" });
}
</script>

<template>
	<view class="student-page">
		<view class="student-page__hero">
			<view class="student-page__safe" />
			<view class="student-page__nav">
				<view class="student-page__nav-icon" @click="goBack">
					<view class="i-carbon:chevron-left text-18px text-white" />
				</view>
				<view class="student-page__nav-icon" @click="refreshPage">
					<view class="i-carbon:renew text-16px text-white" />
				</view>
			</view>
			<text class="student-page__title">学生列表</text>
			<view class="student-page__wave student-page__wave--one" />
			<view class="student-page__wave student-page__wave--two" />
		</view>

		<view class="student-page__content">
			<view v-for="student in students" :key="student.id" class="student-item">
				<view class="student-item__info">
					<view class="student-item__icon i-carbon:user-avatar-filled-alt text-34px text-#30c7a6" />
					<view class="student-item__name">
						{{ student.name }}<text class="student-item__gender">{{ student.gender === "男" ? "♂" : "♀" }}</text>
					</view>
				</view>
				<view
					class="student-item__switch"
					:class="{ 'student-item__switch--active': currentStudent?.id === student.id }"
					@click="switchStudent(student.id)"
				>
					切换
				</view>
			</view>

			<view class="student-page__add-btn" @click="addStudent">添加学生</view>
		</view>
	</view>
</template>

<style scoped>
.student-page {
	min-height: 100vh;
	background: #f5f7fb;
}

.student-page__hero {
	position: relative;
	height: 176px;
	background: linear-gradient(135deg, #33c8a7 0%, #2bc5a3 100%);
	overflow: hidden;
}

.student-page__safe {
	height: env(safe-area-inset-top);
}

.student-page__nav {
	padding: 12px 14px 0;
	display: flex;
	align-items: center;
	justify-content: space-between;
}

.student-page__nav-icon {
	width: 24px;
	height: 24px;
	display: flex;
	align-items: center;
	justify-content: center;
}

.student-page__title {
	position: absolute;
	left: 18px;
	top: calc(env(safe-area-inset-top) + 46px);
	font-size: 22px;
	font-weight: 700;
	color: #fff;
}

.student-page__wave {
	position: absolute;
	left: -10%;
	right: -10%;
	height: 70px;
	border-radius: 50%;
	background: rgba(255, 255, 255, 0.48);
}

.student-page__wave--one {
	bottom: 34px;
	transform: rotate(-4deg);
}

.student-page__wave--two {
	bottom: 10px;
	background: rgba(255, 255, 255, 0.72);
	transform: rotate(2deg);
}

.student-page__content {
	margin-top: -34px;
	padding: 0 18px 24px;
	position: relative;
	z-index: 1;
}

.student-item {
	padding: 18px 16px;
	margin-bottom: 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.student-item__info {
	display: flex;
	align-items: center;
	gap: 14px;
}

.student-item__name {
	font-size: 18px;
	color: #2b313c;
}

.student-item__gender {
	margin-left: 4px;
	color: #5b7cff;
}

.student-item__switch {
	padding: 8px 12px;
	border-radius: 999px;
	background: #35c9aa;
	font-size: 14px;
	font-weight: 600;
	color: #fff;
}

.student-item__switch--active {
	background: #27b794;
}

.student-page__add-btn {
	height: 44px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	background: #ff9800;
	font-size: 16px;
	font-weight: 700;
	color: #fff;
}
</style>
