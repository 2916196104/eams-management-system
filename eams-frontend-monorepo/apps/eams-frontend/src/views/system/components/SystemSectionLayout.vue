<template>
	<section class="system-layout">
		<aside class="system-layout__sidebar">
			<div class="system-layout__module">
				<div class="system-layout__module-name">
					<el-icon class="system-layout__module-icon">
						<Monitor />
					</el-icon>
					<span>系统</span>
				</div>
				<el-icon class="system-layout__module-arrow">
					<ArrowUp />
				</el-icon>
			</div>

			<el-menu :default-active="activePath" class="system-layout__menu" router>
				<el-menu-item v-for="item in systemMenuItems" :key="item.path" :index="item.path" :disabled="item.disabled">
					{{ item.label }}
				</el-menu-item>
			</el-menu>
		</aside>

		<div class="system-layout__content">
			<slot />
		</div>
	</section>
</template>

<script setup lang="ts">
import { computed } from "vue";
import { useRoute } from "vue-router";
import { ArrowUp, Monitor } from "@element-plus/icons-vue";
import { systemMenuItems } from "../menu";

const route = useRoute();

const activePath = computed(() => {
	const matched = systemMenuItems.find((item) => item.path === route.path);
	return matched?.path || "";
});
</script>

<style scoped>
.system-layout {
	display: grid;
	grid-template-columns: 174px minmax(0, 1fr);
	gap: 0;
	min-height: calc(100vh - 92px);
	background: #f3f5f9;
}

.system-layout__sidebar {
	background: #ffffff;
	border-right: 1px solid #e9edf5;
}

.system-layout__module {
	height: 56px;
	padding: 0 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	color: #5f6f8a;
	border-bottom: 1px solid #eef2f7;
}

.system-layout__module-name {
	display: flex;
	align-items: center;
	gap: 10px;
	font-size: 18px;
	font-weight: 500;
	color: #4a89f3;
}

.system-layout__module-icon,
.system-layout__module-arrow {
	font-size: 16px;
}

.system-layout__menu {
	border-right: 0;
	--el-menu-item-height: 48px;
}

.system-layout__menu :deep(.el-menu-item) {
	padding-left: 38px !important;
	font-size: 16px;
	color: #2c3b57;
}

.system-layout__menu :deep(.el-menu-item.is-active) {
	background: #edf4ff;
	color: #4a89f3;
}

.system-layout__menu :deep(.el-menu-item.is-disabled) {
	color: #7a879c;
	opacity: 1;
	cursor: not-allowed;
}

.system-layout__content {
	padding: 16px;
	min-width: 0;
}

@media (max-width: 1200px) {
	.system-layout {
		grid-template-columns: 156px minmax(0, 1fr);
	}

	.system-layout__menu :deep(.el-menu-item) {
		padding-left: 24px !important;
	}
}
</style>
