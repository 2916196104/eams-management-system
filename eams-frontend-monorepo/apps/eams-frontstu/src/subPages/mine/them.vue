<script lang="ts" setup>
definePage({
	name: "them",
	layout: "page",
	style: {
		navigationBarTitleText: "主题设置",
	},
});

const {
	theme,
	toggleTheme,
	currentThemeColor,
	showThemeColorSheet,
	themeColorOptions,
	openThemeColorPicker,
	closeThemeColorPicker,
	selectThemeColor,
	setFollowSystem,
} = useManualTheme();

const isDark = computed({
	get() {
		return theme.value === "dark";
	},
	set() {
		toggleTheme();
	},
});
// 处理主题色选择
function handleThemeColorSelect(option: any) {
	selectThemeColor(option);
}
</script>

<template>
	<!-- 基础设置 -->
	<title-block title="主题设置" transparent>
		<wd-cell-group border custom-class="rounded-2! overflow-hidden">
			<wd-cell title="暗黑模式">
				<wd-switch v-model="isDark" size="18px" />
			</wd-cell>
			<wd-cell title="跟随系统">
				<wd-button size="small" @click="setFollowSystem">跟随系统</wd-button>
			</wd-cell>
			<wd-cell title="选择主题色" is-link @click="openThemeColorPicker">
				<view class="flex items-center justify-end gap-2">
					<view class="h-4 w-4 rounded-full" :style="{ backgroundColor: currentThemeColor.primary }" />
					<text>{{ currentThemeColor.name }}</text>
				</view>
			</wd-cell>
		</wd-cell-group>
	</title-block>

	<!-- 主题色选择 ActionSheet -->
	<wd-action-sheet
		v-model="showThemeColorSheet"
		title="选择主题色"
		:close-on-click-action="true"
		@cancel="closeThemeColorPicker"
	>
		<view class="px-4 pb-4">
			<view
				v-for="option in themeColorOptions"
				:key="option.value"
				class="flex items-center justify-between border-b border-gray-100 py-3 last:border-b-0 dark:border-gray-700"
				@click="handleThemeColorSelect(option)"
			>
				<view class="flex items-center gap-3">
					<view
						class="h-6 w-6 border-2 border-gray-200 rounded-full dark:border-gray-600"
						:style="{ backgroundColor: option.primary }"
					/>
					<text class="text-4 text-gray-800 dark:text-gray-200">
						{{ option.name }}
					</text>
				</view>
				<wd-icon v-if="currentThemeColor.value === option.value" name="check" :color="option.primary" size="20px" />
			</view>
		</view>
		<wd-gap :height="50" />
	</wd-action-sheet>
</template>

<style scoped></style>
