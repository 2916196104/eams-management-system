<script setup lang="ts">
import { ref } from "vue";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";

definePage({
	name: "mineOrderList",
	style: {
		navigationBarTitleText: "选课订单",
		titleNView: false,
	},
});

const tabs = ["全部", "待付款", "已完成", "待评价"];
const activeTab = ref("全部");
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="选课订单" />
		<view class="tab-bar">
			<view
				v-for="tab in tabs"
				:key="tab"
				class="tab-bar__item"
				:class="{ 'tab-bar__item--active': activeTab === tab }"
				@click="activeTab = tab"
			>
				{{ tab }}
			</view>
		</view>
		<view class="page-content">
			<ParentEmptyState text="您还没有相关的订单" :card="false" min-height="220px" />
			<view class="empty-action">在线购课</view>
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.tab-bar {
	display: grid;
	grid-template-columns: repeat(4, minmax(0, 1fr));
	background: #fff;
}

.tab-bar__item {
	height: 42px;
	display: flex;
	align-items: center;
	justify-content: center;
	font-size: 15px;
	color: #1f2937;
	position: relative;
}

.tab-bar__item--active {
	color: #ff9800;
	font-weight: 700;
}

.tab-bar__item--active::after {
	content: "";
	position: absolute;
	left: 50%;
	bottom: 0;
	width: 22px;
	height: 2px;
	border-radius: 999px;
	background: #ff9800;
	transform: translateX(-50%);
}

.page-content {
	padding-top: 24px;
	display: flex;
	flex-direction: column;
	align-items: center;
}

.empty-action {
	margin-top: -48px;
	width: 108px;
	height: 40px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	background: #ff8c3a;
	font-size: 15px;
	color: #fff;
}
</style>
