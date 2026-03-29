<script setup lang="ts">
withDefaults(
	defineProps<{
		title?: string;
		description?: string;
		compact?: boolean;
	}>(),
	{
		title: "暂无记录",
		description: "",
		compact: false,
	},
);
</script>

<template>
	<view class="teacher-empty" :class="{ 'teacher-empty--compact': compact }">
		<view class="i-carbon:document-unknown text-60px text-#c7ced9" />
		<text class="teacher-empty__title">{{ title }}</text>
		<text v-if="description" class="teacher-empty__desc">{{ description }}</text>
	</view>
</template>

<style scoped>
.teacher-empty {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	padding: 36px 16px;
	color: #c7ced9;
}

.teacher-empty--compact {
	padding: 28px 16px;
}

.teacher-empty__title {
	margin-top: 8px;
	font-size: 16px;
	color: #c7ced9;
}

.teacher-empty__desc {
	margin-top: 6px;
	font-size: 13px;
	color: #d6dbe5;
	text-align: center;
}
</style>
