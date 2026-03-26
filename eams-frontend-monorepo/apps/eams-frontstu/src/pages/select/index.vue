<script setup lang="ts">
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import ParentSectionCard from "@/components/parent/ParentSectionCard.vue";

definePage({
	name: "select",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "选课",
		titleNView: false,
	},
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="选课" :show-back="false" />
		<view class="page-shell__content">
			<ParentSectionCard title="我的课程" right-text="全部">
				<ParentEmptyState text="未报名课程" min-height="160px" />
			</ParentSectionCard>
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.page-shell__content {
	padding: 14px 12px 20px;
}
</style>
