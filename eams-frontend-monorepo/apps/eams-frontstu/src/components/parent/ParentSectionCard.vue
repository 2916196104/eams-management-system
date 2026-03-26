<script setup lang="ts">
withDefaults(
	defineProps<{
		title?: string;
		rightText?: string;
	}>(),
	{
		title: "",
		rightText: "",
	},
);

const emit = defineEmits<{
	(e: "right-click"): void;
}>();
</script>

<template>
	<view class="parent-section">
		<view v-if="title || rightText" class="parent-section__header">
			<text class="parent-section__title">{{ title }}</text>
			<text v-if="rightText" class="parent-section__action" @click="emit('right-click')">{{ rightText }}</text>
		</view>
		<view class="parent-section__body">
			<slot />
		</view>
	</view>
</template>

<style scoped>
.parent-section {
	border-radius: 16px;
	background: #fff;
	overflow: hidden;
}

.parent-section__header {
	padding: 14px 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-bottom: 1px solid #f1f3f7;
}

.parent-section__title {
	font-size: 16px;
	font-weight: 600;
	color: #222;
}

.parent-section__action {
	font-size: 14px;
	color: #8e97a6;
}

.parent-section__body {
	padding: 0;
}
</style>
