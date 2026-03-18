<script setup lang="ts">
definePage({
	name: "home",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "主页",
		titleNView: false,
	},
});

// 预导入图标
const preloadicons = [
	"i-carbon:settings",
	"i-carbon:application-virtual",
	"i-carbon:assembly",
	"i-carbon:favorite",
	"i-carbon:user",
];

// 获取主题是否是暗色
const { isDark } = useManualTheme();

// 系统通知数据
const textArray = ref([
	"欢迎使用wot design uni",
	"该组件库基于uniapp ->Vue3, ts构建",
	"我们的目标是打造最强uniapp组件库",
	"诚挚邀请大家共同建设",
	"这是一条消息提示信息，这是一条消息提示信息，这是一条消息提示信息，这是一条消息提示信息，这是一条消息提示信息",
]);

// 轮播图数据
const current = ref<number>(0);
const swiperList = ref([
	"https://wot-ui.cn/assets/redpanda.jpg",
	"https://wot-ui.cn/assets/capybara.jpg",
	"https://wot-ui.cn/assets/panda.jpg",
	"https://wot-ui.cn/assets/moon.jpg",
	"https://wot-ui.cn/assets/meng.jpg",
]);

// 功能列表
const { funs } = useUserStore();

// 获取路由实例
const router = useRouter();

// 页面跳转
function navigateTo(name: string) {
	if (!name) return;
	router.push({
		name,
	});
}
</script>

<template>
	<!-- 预导入图标 -->
	<view class="hidden">
		<view v-for="(one, key) in preloadicons" :key="key" :class="one" />
	</view>
	<!-- 主体 -->
	<view class="box-border">
		<!-- 系统通知 -->
		<wd-notice-bar
			:text="textArray"
			:delay="3"
			direction="vertical"
			type="warning"
			custom-class="space"
			:background-color="isDark ? 'var(--wot-dark-background2)' : 'RGB(255,246,200)'"
		>
			<template #prefix>
				<span class="i-carbon:information-filled mr-1 text-20px" />
			</template>
			<template #suffix>
				<div class="text-16px text-#4d80f0">查看</div>
			</template>
		</wd-notice-bar>
		<!-- 轮播图 -->
		<wd-swiper
			v-model:current="current"
			height="200px"
			class="mt-3"
			:list="swiperList"
			autoplay
			:indicator="{ type: 'dots-bar' }"
		/>
		<!-- 功能列表 -->
		<wd-row class="my-4 rounded-2 bg-white p-2 dark:bg-[var(--wot-dark-background2)] dark:text-white">
			<template v-for="one in funs" :key="one.id">
				<wd-col :span="6">
					<view
						class="cursor-pointer select-none rounded-lg p-2 pt-2 text-center transition-all duration-200 ease-out active:scale-95 hover:scale-105 hover:bg-gray-100 dark:hover:bg-gray-800"
						@click="navigateTo(one.router)"
					>
						<view :class="`${one.icon} text-35px transition-transform duration-200`" />
						<text class="mt-2 block text-4 text-gray-500 dark:text-gray-300">
							{{ one.name }}
						</text>
					</view>
				</wd-col>
			</template>
		</wd-row>
	</view>
</template>

<style scoped>
:deep(.space) {
	padding: 15px 8px;
	font-size: 15px;
}
</style>
