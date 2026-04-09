<script setup lang="ts">
withDefaults(
	defineProps<{
		title: string;
		extra?: string;
	}>(),
	{
		extra: "",
	},
);
</script>

<template>
	<view class="teacher-section">
		<view class="teacher-section__head">
			<text class="teacher-section__title">{{ title }}</text>
			<text v-if="extra" class="teacher-section__extra">{{ extra }}</text>
		</view>
		<view class="teacher-section__body">
			<slot />
		</view>
	</view>
</template>

<style scoped>
.teacher-section {
	margin-top: 14px;
	overflow: hidden;
	border-radius: 14px;
	background: #fff;
}

.teacher-section__head {
	display: flex;
	align-items: center;
	justify-content: space-between;
	padding: 14px 16px;
	border-bottom: 1px solid #eef1f6;
}

.teacher-section__title {
	font-size: 16px;
	font-weight: 600;
	color: #1f2937;
}

.teacher-section__extra {
	font-size: 14px;
	color: #8d97a7;
}

.teacher-section__body {
	min-height: 120px;
}
</style>
