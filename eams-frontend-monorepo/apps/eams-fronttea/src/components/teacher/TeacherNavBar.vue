<script setup lang="ts">
import { hasTeacherNavigationHistory, navigateToTeacherBackTarget } from "@/utils/teacherNavigation";

const props = withDefaults(
	defineProps<{
		title: string;
		showBack?: boolean;
		showRefresh?: boolean;
	}>(),
	{
		showBack: true,
		showRefresh: true,
	},
);

const emit = defineEmits<{
	(event: "refresh"): void;
}>();

const router = useRouter();
const route = useRoute() as { query?: Record<string, string | string[] | undefined> };

function handleBack() {
	if (hasTeacherNavigationHistory()) {
		uni.navigateBack({
			fail: () => {
				if (!navigateToTeacherBackTarget(router, route.query)) {
					router.pushTab({ name: "home" });
				}
			},
		});
		return;
	}

	if (!navigateToTeacherBackTarget(router, route.query)) {
		router.pushTab({ name: "home" });
	}
}

function handleRefresh() {
	emit("refresh");
}
</script>

<template>
	<view class="teacher-nav">
		<view class="teacher-nav__safe" />
		<view class="teacher-nav__bar">
			<view class="teacher-nav__side">
				<view v-if="props.showBack" class="teacher-nav__icon" @click="handleBack">
					<view class="i-carbon:arrow-left text-20px text-#101828" />
				</view>
			</view>
			<text class="teacher-nav__title">{{ props.title }}</text>
			<view class="teacher-nav__side teacher-nav__side--right">
				<view v-if="props.showRefresh" class="teacher-nav__icon" @click="handleRefresh">
					<view class="i-carbon:renew text-18px text-#101828" />
				</view>
			</view>
		</view>
	</view>
</template>

<style scoped>
.teacher-nav {
	background: #fff;
}

.teacher-nav__safe {
	height: env(safe-area-inset-top);
}

.teacher-nav__bar {
	display: flex;
	align-items: center;
	justify-content: space-between;
	height: 44px;
	padding: 0 12px;
	border-bottom: 1px solid #edf0f5;
}

.teacher-nav__side {
	display: flex;
	align-items: center;
	width: 32px;
}

.teacher-nav__side--right {
	justify-content: flex-end;
}

.teacher-nav__icon {
	display: flex;
	align-items: center;
	justify-content: center;
	width: 28px;
	height: 28px;
	border-radius: 50%;
}

.teacher-nav__title {
	font-size: 18px;
	font-weight: 600;
	color: #101828;
}
</style>
