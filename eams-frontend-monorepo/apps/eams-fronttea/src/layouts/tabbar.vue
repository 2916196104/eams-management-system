<script lang="ts" setup>
const router = useRouter();
const route = useRoute();

const { activeTabbar, setTabbarItemActive, tabbarList } = useTabbar();

function handleTabbarChange(name: string) {
	setTabbarItemActive(name);
	router.pushTab({ name });
}

onMounted(() => {
	// #ifdef APP
	uni.hideTabBar();
	// #endif
	nextTick(() => {
		if (route.name && route.name !== activeTabbar.value.name) {
			setTabbarItemActive(route.name);
		}
	});
});
</script>

<script lang="ts">
export default {
	options: {
		addGlobalClass: true,
		virtualHost: true,
		styleIsolation: "shared",
	},
};
</script>

<template>
	<slot />
	<view class="teacher-tabbar-gap" />
	<view class="teacher-tabbar">
		<view class="teacher-tabbar__safe" />
		<view class="teacher-tabbar__inner">
			<view
				v-for="item in tabbarList"
				:key="item.name"
				class="teacher-tabbar__item"
				:class="{ 'teacher-tabbar__item--active': activeTabbar.name === item.name }"
				@click="handleTabbarChange(item.name)"
			>
				<view
					class="teacher-tabbar__icon"
					:class="item.icon"
					:style="{ color: activeTabbar.name === item.name ? item.activeColor : '#2d2d2d' }"
				/>
				<text
					class="teacher-tabbar__title"
					:style="{ color: activeTabbar.name === item.name ? item.activeColor : '#2d2d2d' }"
				>
					{{ item.title }}
				</text>
			</view>
		</view>
	</view>
</template>

<style scoped>
.teacher-tabbar-gap {
	height: 74px;
}

.teacher-tabbar {
	position: fixed;
	right: 0;
	bottom: 0;
	left: 0;
	z-index: 100;
	background: #fff;
	border-top: 1px solid #edf0f5;
}

.teacher-tabbar__safe {
	height: env(safe-area-inset-bottom);
	background: #fff;
}

.teacher-tabbar__inner {
	display: flex;
	align-items: center;
	justify-content: space-around;
	height: 64px;
}

.teacher-tabbar__item {
	display: flex;
	flex: 1;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 4px;
}

.teacher-tabbar__icon {
	font-size: 22px;
}

.teacher-tabbar__title {
	font-size: 12px;
	line-height: 1;
}
</style>
