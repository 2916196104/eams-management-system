<template>
	<section class="f1nav-demo">
		<EamsNav :menus="menus" :show-home="false" :router="false" @select="handleSelect" />
		<div class="f1nav-demo__main">
			<div class="f1nav-demo__card">
				<div class="f1nav-demo__title">f1nav（mynav 组件）示例</div>
				<div class="f1nav-demo__desc">当前路由：{{ route.path }}</div>
			</div>
			<div class="f1nav-demo__card f1nav-demo__content">
				<router-view />
			</div>
		</div>
	</section>
</template>

<script setup lang="ts">
import { computed } from "vue";
import { useRoute, useRouter } from "vue-router";
import EamsNav from "@/components/mynav/EamsNav.vue";
import { eamsNavItems } from "@/components/mynav/nav-data";
import type { EamsNavMenuItem } from "@/components/mynav/type";

const router = useRouter();
const route = useRoute();
const prefix = "/sample/f1nav";

const menus = computed<EamsNavMenuItem[]>(() =>
	eamsNavItems.map((group) => ({
		id: group.key,
		text: group.label,
		icon: group.icon,
		path: group.path ? `${prefix}${group.path}` : undefined,
		children: (group.children ?? []).map((child) => ({
			id: child.key,
			text: child.label,
			path: `${prefix}${child.path}`,
		})),
	})),
);

function handleSelect(item?: EamsNavMenuItem) {
	const targetPath = item?.path || item?.href;
	if (targetPath) router.push(targetPath);
}
</script>

<style scoped>
.f1nav-demo {
	display: flex;
	width: 100%;
	min-height: 100%;
	background: #edecec;
	border-radius: 6px;
	overflow: hidden;
}

.f1nav-demo__main {
	flex: 1;
	padding: 12px;
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.f1nav-demo__card {
	background: #ffffff;
	border-radius: 6px;
	padding: 14px 16px;
}

.f1nav-demo__title {
	font-size: 18px;
	font-weight: 600;
	margin-bottom: 8px;
}

.f1nav-demo__desc {
	color: #666;
}

.f1nav-demo__content {
	min-height: 320px;
	padding: 16px;
}
</style>
