<script setup lang="ts">
withDefaults(
	defineProps<{
		text?: string;
		subText?: string;
		card?: boolean;
		minHeight?: string;
	}>(),
	{
		text: "暂无记录",
		subText: "",
		card: true,
		minHeight: "160px",
	},
);
</script>

<template>
	<view class="parent-empty" :class="{ 'parent-empty--card': card }" :style="{ minHeight }">
		<view class="parent-empty__icon i-carbon:document text-56px" />
		<text class="parent-empty__text">{{ text }}</text>
		<text v-if="subText" class="parent-empty__subtext">{{ subText }}</text>
	</view>
</template>

<style scoped>
.parent-empty {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	color: #c5ccd8;
}

.parent-empty--card {
	border-radius: 16px;
	background: #fff;
}

.parent-empty__text {
	margin-top: 8px;
	font-size: 16px;
	color: #bcc4d1;
}

.parent-empty__subtext {
	margin-top: 6px;
	font-size: 12px;
	color: #d1d7e2;
}
</style>
