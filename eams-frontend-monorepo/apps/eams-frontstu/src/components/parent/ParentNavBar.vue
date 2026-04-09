<script setup lang="ts">
import router from "@/router";
const props = withDefaults(
	defineProps<{
		title?: string;
		showBack?: boolean;
		showRefresh?: boolean;
		rightText?: string;
		rightTextColor?: string;
	}>(),
	{
		title: "",
		showBack: true,
		showRefresh: false,
		rightText: "",
		rightTextColor: "#31c7a5",
	},
);

const emit = defineEmits<{
	(e: "refresh"): void;
	(e: "right-click"): void;
}>();

function handleBack() {
	const pages = getCurrentPages();
	if (pages.length > 1) {
		uni.navigateBack({
			fail() {
				router.pushTab({ name: "home" });
			},
		});
		return;
	}

	router.pushTab({ name: "home" });
}

function handleRightClick() {
	if (props.rightText) {
		emit("right-click");
		return;
	}

	if (props.showRefresh) emit("refresh");
}
</script>

<template>
	<view class="parent-nav">
		<view class="parent-nav__safe" />
		<view class="parent-nav__row">
			<view class="parent-nav__side parent-nav__side--left">
				<view v-if="showBack" class="parent-nav__icon-btn" @click="handleBack">
					<view class="i-carbon:chevron-left text-18px text-#222" />
				</view>
			</view>
			<view class="parent-nav__title">{{ title }}</view>
			<view class="parent-nav__side parent-nav__side--right">
				<view
					v-if="rightText || showRefresh"
					class="parent-nav__action"
					:style="{ color: rightTextColor }"
					@click="handleRightClick"
				>
					<text v-if="rightText">{{ rightText }}</text>
					<view v-else class="i-carbon:renew text-16px text-#222" />
				</view>
			</view>
		</view>
	</view>
</template>

<style scoped>
.parent-nav {
	background: #fff;
}

.parent-nav__safe {
	height: env(safe-area-inset-top);
}

.parent-nav__row {
	height: 44px;
	padding: 0 12px;
	display: flex;
	align-items: center;
	border-bottom: 1px solid #f0f2f5;
}

.parent-nav__side {
	width: 56px;
	display: flex;
	align-items: center;
}

.parent-nav__side--left {
	justify-content: flex-start;
}

.parent-nav__side--right {
	justify-content: flex-end;
}

.parent-nav__title {
	flex: 1;
	text-align: center;
	font-size: 18px;
	font-weight: 600;
	color: #111827;
}

.parent-nav__icon-btn,
.parent-nav__action {
	min-width: 24px;
	min-height: 24px;
	display: flex;
	align-items: center;
	justify-content: center;
}

.parent-nav__action {
	font-size: 14px;
	font-weight: 500;
}
</style>
