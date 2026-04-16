<template>
	<div class="admin-shell">
		<!-- 顶部统一头部：品牌、面包屑、快捷操作和用户下拉 -->
		<header class="admin-shell__header">
			<div class="admin-shell__brand">
				<img class="admin-shell__logo" src="/logo.jpg" :alt="appName" />
				<div class="admin-shell__brand-title">{{ appName }}</div>
				<el-button link class="admin-shell__brand-toggle" @click="secondaryCollapsed = !secondaryCollapsed">
					<el-icon size="20">
						<Fold />
					</el-icon>
				</el-button>
			</div>

			<div class="admin-shell__breadcrumb">
				<el-breadcrumb separator="/">
					<el-breadcrumb-item v-for="item in breadcrumbItems" :key="item">
						<span class="admin-shell__breadcrumb-item">
							<el-icon v-if="item === '首页'">
								<HomeFilled />
							</el-icon>
							<span>{{ item }}</span>
						</span>
					</el-breadcrumb-item>
				</el-breadcrumb>
			</div>

			<div class="admin-shell__actions">
				<el-button text class="admin-shell__action-btn" @click="showDeviceTip">
					<el-icon>
						<Cellphone />
					</el-icon>
				</el-button>
				<el-button text class="admin-shell__action-btn" @click="showFeedbackTip">
					反馈
				</el-button>
				<el-button text class="admin-shell__action-btn" @click="toggleFullscreen">
					<el-icon>
						<FullScreen />
					</el-icon>
				</el-button>

				<el-dropdown trigger="click" @command="handleUserCommand">
					<div class="admin-shell__user">
						<el-avatar :size="32" :src="user?.avatar" />
						<span class="admin-shell__user-name">{{ userName }}</span>
						<el-icon>
							<ArrowDown />
						</el-icon>
					</div>
					<template #dropdown>
						<el-dropdown-menu>
							<el-dropdown-item command="profile">个人资料</el-dropdown-item>
							<el-dropdown-item command="logout">退出登录</el-dropdown-item>
						</el-dropdown-menu>
					</template>
				</el-dropdown>
			</div>
		</header>

		<div class="admin-shell__body">
			<!-- 一级导航：固定展示参考系统的主模块入口 -->
			<aside class="primary-nav">
				<button
					v-for="section in navSections"
					:key="section.id"
					type="button"
					class="primary-nav__item"
					:class="{ 'primary-nav__item--active': section.id === activeSection.id }"
					@click="navigateToSection(section)"
				>
					<el-icon class="primary-nav__icon" size="22">
						<component :is="renderNavIcon(section.icon)" />
					</el-icon>
					<span class="primary-nav__label">{{ section.text }}</span>
				</button>
			</aside>

			<!-- 二级导航：跟随当前一级菜单切换，可折叠但不参与页面滚动 -->
			<aside class="secondary-nav" :class="{ 'secondary-nav--collapsed': secondaryCollapsed }">
				<div class="secondary-nav__header">
					<div class="secondary-nav__title">
						<el-icon size="18">
							<component :is="renderNavIcon(activeSection.icon)" />
						</el-icon>
						<span>{{ activeSection.text }}</span>
					</div>
					<el-icon class="secondary-nav__arrow">
						<ArrowUp />
					</el-icon>
				</div>

				<div class="secondary-nav__list">
					<button
						v-for="child in activeSection.children"
						:key="child.id"
						type="button"
						class="secondary-nav__item"
						:class="{ 'secondary-nav__item--active': child.path === activeNavPath }"
						@click="navigateToChild(child.path)"
					>
						{{ child.text }}
					</button>
				</div>
			</aside>

			<!-- 主内容区：顶部标签页 + 可滚动的页面内容 -->
			<section class="admin-shell__main">
				<div class="admin-shell__tabs">
					<el-tabs
						v-model="activeIndex"
						type="card"
						:before-leave="beforeLeave"
						@tab-click="tabClick"
						@tab-remove="tabClose"
					>
						<el-tab-pane :name="indexPath">
							<template #label>
								<span class="admin-shell__home-tab">
									<el-icon>
										<HomeFilled />
									</el-icon>
									<span>首页</span>
								</span>
							</template>
						</el-tab-pane>

						<el-tab-pane
							v-for="(item, index) in tabs"
							:key="`${item.path}-${index}`"
							:label="item.label"
							:name="item.path"
							closable
						/>

						<el-tab-pane name="tab-operation">
							<template #label>
								<el-dropdown trigger="click">
									<el-button class="admin-shell__tab-action" type="info" link>
										<el-icon size="18">
											<Operation />
										</el-icon>
									</el-button>
									<template #dropdown>
										<el-dropdown-menu>
											<el-dropdown-item :disabled="tabs.length === 0" @click="handleClose(1)">
												关闭所有标签页
											</el-dropdown-item>
											<el-dropdown-item
												:disabled="activeIndex === indexPath || tabstore.getTabIndex(activeIndex) === 0"
												@click="handleClose(2)"
											>
												关闭当前标签页左边
											</el-dropdown-item>
											<el-dropdown-item
												:disabled="tabstore.getTabIndex(activeIndex) === tabs.length - 1"
												@click="handleClose(3)"
											>
												关闭当前标签页右边
											</el-dropdown-item>
										</el-dropdown-menu>
									</template>
								</el-dropdown>
							</template>
						</el-tab-pane>
					</el-tabs>
				</div>

				<div class="admin-shell__content">
					<router-view />
				</div>
			</section>
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, ref } from "vue";
import { ElMessage } from "element-plus";
import type { TabPaneName, TabsPaneContext } from "element-plus";
import { ArrowDown, ArrowUp, Cellphone, Fold, FullScreen, HomeFilled, Operation } from "@element-plus/icons-vue";
import { storeToRefs } from "pinia";
import { useRoute, useRouter } from "vue-router";
import { useRenderIcon } from "@/components/ReIcon";
import {
	ADMIN_NAVIGATION,
	findAdminNavItemByPath,
	findAdminNavSectionByPath,
	getAdminNavSectionEntryPath,
	type AdminNavSection,
} from "@/config/adminNavigation";
import { useTabStore } from "@/stores/tab";
import { useUserStore } from "@/stores/user";

const appName = import.meta.env.VITE_APP_TITLE || "宏之博教务系统";
const route = useRoute();
const router = useRouter();

const userStore = useUserStore();
const { user } = storeToRefs(userStore);

const tabstore = useTabStore();
const { tabs, activeIndex, indexPath } = storeToRefs(tabstore);

// 后台主导航按参考系统收口为一份固定配置，所有页面统一复用这套入口定义。
const navSections = ADMIN_NAVIGATION;
const secondaryCollapsed = ref(false);

// 根据当前路由反推激活的一级菜单和二级菜单，保证刷新后导航状态仍然正确。
const activeSection = computed<AdminNavSection>(() => findAdminNavSectionByPath(route.path) || navSections[0]);
const activeNavItem = computed(() => findAdminNavItemByPath(route.path));
const activeNavPath = computed(() => activeNavItem.value?.path || getAdminNavSectionEntryPath(activeSection.value));

// 面包屑文案直接复用导航配置，避免页面标题和菜单文案出现两套来源。
const breadcrumbItems = computed(() => {
	const currentSection = activeSection.value;
	const currentItem = activeNavItem.value;
	if (!currentItem) return ["首页"];
	if (currentSection.id === "home") {
		return currentItem.path === indexPath.value ? ["首页"] : ["首页", currentItem.text];
	}
	return ["首页", currentSection.text, currentItem.text];
});

const userName = computed(() => user.value?.username || "管理员");

function renderNavIcon(icon?: string) {
	return useRenderIcon(icon || "ep/menu");
}

// 点击一级菜单时默认进入该分组的首个可落地页面，保持和参考系统一致的交互习惯。
function navigateToSection(section: AdminNavSection) {
	router.push({ path: getAdminNavSectionEntryPath(section) });
}

function navigateToChild(path: string) {
	router.push({ path });
}

const tabClick = (pane: TabsPaneContext) => {
	if (pane.paneName === "tab-operation") return;
	const path = pane.paneName as string;
	tabstore.setActiveIndex(path);
	router.push({ path });
};

// 关闭当前标签页时，优先激活左侧相邻标签，保持旧后台的使用习惯。
const tabClose = (name: TabPaneName) => {
	if (activeIndex.value === name) {
		const idx = tabstore.getTabIndex(name as string) - 1;
		activeIndex.value = idx >= 0 ? tabs.value[idx].path : indexPath.value;
		router.push({ path: activeIndex.value });
	}
	tabstore.remTab(name as string);
};

const beforeLeave = (activeName: TabPaneName) => activeName !== "tab-operation";

// 标签页右侧操作菜单：1 全关，2 关左侧，3 关右侧。
function handleClose(type: number) {
	switch (type) {
		case 1:
			tabstore.reset();
			router.push({ path: activeIndex.value });
			break;
		case 2:
			tabstore.remBeforeTab(activeIndex.value);
			break;
		case 3:
			tabstore.remAfterTab(activeIndex.value);
			break;
		default:
			break;
	}
}

async function toggleFullscreen() {
	if (!document.fullscreenElement) {
		await document.documentElement.requestFullscreen();
		return;
	}
	await document.exitFullscreen();
}

function showDeviceTip() {
	ElMessage.info("移动端入口后续可在这里补齐。");
}

function showFeedbackTip() {
	ElMessage.info("反馈入口已经预留，后续可接真实表单。");
}

function handleUserCommand(command: string) {
	if (command === "logout") {
		userStore.resetSaveData();
		tabstore.reset();
		router.push({ name: "Login" });
		return;
	}
	ElMessage.info("个人资料页后续可继续补齐。");
}
</script>

<style>
:root {
	/* 统一尺寸变量：后续如果继续微调导航密度，优先改这里。 */
	--admin-header-height: 60px;
	--admin-primary-width: 72px;
	--admin-secondary-width: 168px;
}
</style>

<style scoped>
/* 整个后台壳层锁定在一屏内，避免左侧菜单跟随页面内容一起滚动。 */
.admin-shell {
	height: 100vh;
	min-height: 100vh;
	display: flex;
	flex-direction: column;
	background: #eef2f7;
	color: #1f2a37;
	overflow: hidden;
}

.admin-shell__header {
	height: var(--admin-header-height);
	display: flex;
	align-items: center;
	gap: 20px;
	padding: 0 20px 0 18px;
	background: #ffffff;
	border-bottom: 1px solid #e5eaf3;
	box-sizing: border-box;
	flex-shrink: 0;
}

.admin-shell__brand {
	width: 300px;
	display: flex;
	align-items: center;
	gap: 12px;
	flex-shrink: 0;
}

.admin-shell__logo {
	width: 38px;
	height: 38px;
	border-radius: 10px;
	object-fit: cover;
}

.admin-shell__brand-title {
	font-size: 19px;
	font-weight: 700;
	color: #111827;
	white-space: nowrap;
}

.admin-shell__brand-toggle {
	margin-left: auto;
	color: #1f2937;
}

.admin-shell__breadcrumb {
	flex: 1;
	min-width: 0;
}

.admin-shell__breadcrumb-item {
	display: inline-flex;
	align-items: center;
	gap: 6px;
	color: #64748b;
	font-size: 15px;
}

.admin-shell__actions {
	display: flex;
	align-items: center;
	gap: 10px;
	flex-shrink: 0;
}

.admin-shell__action-btn {
	min-width: 44px;
	height: 40px;
	padding: 0 14px;
	border-radius: 10px;
	border: 1px solid #d6deea;
	color: #475569;
	background: #ffffff;
}

.admin-shell__user {
	display: inline-flex;
	align-items: center;
	gap: 10px;
	padding-left: 8px;
	cursor: pointer;
	color: #334155;
}

.admin-shell__user-name {
	font-size: 15px;
	font-weight: 500;
}

.admin-shell__body {
	display: flex;
	flex: 1;
	min-height: 0;
	overflow: hidden;
}

/* 一级菜单使用固定窄栏，尽量在一屏内容纳完整主模块。 */
.primary-nav {
	width: var(--admin-primary-width);
	padding: 10px 0;
	display: flex;
	flex-direction: column;
	align-items: center;
	gap: 6px;
	background: #11263a;
	box-sizing: border-box;
	flex-shrink: 0;
	overflow: hidden;
}

.primary-nav__item {
	width: 54px;
	min-height: 52px;
	border: 0;
	border-radius: 14px;
	padding: 9px 0 7px;
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 4px;
	background: transparent;
	color: #ffffff;
	cursor: pointer;
	transition: background-color 0.2s ease, transform 0.2s ease;
	flex: 0 0 auto;
}

.primary-nav__item:hover {
	background: rgba(59, 130, 246, 0.18);
}

.primary-nav__item--active {
	background: linear-gradient(180deg, #3b82f6 0%, #2563eb 100%);
	box-shadow: 0 10px 18px rgba(37, 99, 235, 0.3);
}

.primary-nav__icon {
	color: inherit;
}

.primary-nav__label {
	font-size: 12px;
	font-weight: 600;
	line-height: 1.1;
}

.secondary-nav {
	width: var(--admin-secondary-width);
	background: #ffffff;
	border-right: 1px solid #e5eaf3;
	display: flex;
	flex-direction: column;
	transition: width 0.2s ease, padding 0.2s ease, border-color 0.2s ease;
	overflow: hidden;
	flex-shrink: 0;
	min-height: 0;
}

.secondary-nav--collapsed {
	width: 0;
	border-right-color: transparent;
}

.secondary-nav__header {
	height: 52px;
	padding: 0 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-bottom: 1px solid #edf2f7;
	flex-shrink: 0;
}

.secondary-nav__title {
	display: inline-flex;
	align-items: center;
	gap: 9px;
	color: #2b4f88;
	font-size: 17px;
	font-weight: 600;
	white-space: nowrap;
}

.secondary-nav__arrow {
	color: #94a3b8;
}

.secondary-nav__list {
	padding: 10px 10px 14px;
	display: flex;
	flex-direction: column;
	gap: 4px;
	overflow: hidden;
}

.secondary-nav__item {
	border: 0;
	border-radius: 10px;
	padding: 12px 16px;
	text-align: left;
	background: transparent;
	color: #1f2937;
	font-size: 15px;
	line-height: 1.45;
	cursor: pointer;
	transition: background-color 0.2s ease, color 0.2s ease;
}

.secondary-nav__item:hover {
	background: #eef4ff;
	color: #2563eb;
}

.secondary-nav__item--active {
	background: #edf4ff;
	color: #2f6cf6;
	font-weight: 600;
}

/* 主区域只允许内容区滚动，标签栏和左右导航保持固定。 */
.admin-shell__main {
	flex: 1;
	min-width: 0;
	display: flex;
	flex-direction: column;
	min-height: 0;
	overflow: hidden;
}

.admin-shell__tabs {
	background: #ffffff;
	border-bottom: 1px solid #e5eaf3;
	padding: 0 10px;
	flex-shrink: 0;
}

.admin-shell__tabs :deep(.el-tabs__header) {
	margin: 0;
}

.admin-shell__tabs :deep(.el-tabs__nav-wrap::after) {
	display: none;
}

.admin-shell__tabs :deep(.el-tabs__item) {
	height: 42px;
	border-bottom: 0;
}

.admin-shell__tabs :deep(.el-tabs__item.is-active) {
	background: #409eff;
	color: #ffffff;
	border-radius: 8px 8px 0 0;
}

.admin-shell__tabs :deep(.el-tabs__item .is-icon-close) {
	color: inherit;
}

.admin-shell__home-tab {
	display: inline-flex;
	align-items: center;
	gap: 6px;
}

.admin-shell__tab-action {
	padding: 0 8px;
}

.admin-shell__content {
	flex: 1;
	min-height: 0;
	overflow: auto;
	padding: 12px;
	box-sizing: border-box;
	overscroll-behavior: contain;
}

/* 小高度屏幕继续压缩导航和标签尺寸，尽量保证菜单一屏内可见。 */
@media (max-height: 820px) {
	:root {
		--admin-header-height: 56px;
	}

	.admin-shell__header {
		padding: 0 16px 0 14px;
	}

	.admin-shell__brand {
		width: 276px;
		gap: 10px;
	}

	.admin-shell__logo {
		width: 34px;
		height: 34px;
	}

	.admin-shell__brand-title {
		font-size: 17px;
	}

	.primary-nav {
		padding: 8px 0;
		gap: 4px;
	}

	.primary-nav__item {
		width: 50px;
		min-height: 48px;
		padding: 8px 0 6px;
		gap: 3px;
		border-radius: 12px;
	}

	.primary-nav__label {
		font-size: 11px;
	}

	.secondary-nav__header {
		height: 46px;
	}

	.secondary-nav__title {
		font-size: 16px;
	}

	.secondary-nav__item {
		padding: 10px 14px;
		font-size: 14px;
	}

	.admin-shell__tabs :deep(.el-tabs__item) {
		height: 38px;
	}

	.admin-shell__content {
		padding: 10px;
	}
}

@media (max-height: 700px) {
	:root {
		--admin-header-height: 52px;
	}

	.primary-nav {
		padding: 6px 0;
		gap: 3px;
	}

	.primary-nav__item {
		width: 46px;
		min-height: 44px;
		padding: 7px 0 5px;
		gap: 2px;
		border-radius: 10px;
	}

	.primary-nav__label {
		font-size: 10px;
	}

	.secondary-nav {
		width: 156px;
	}

	.secondary-nav__header {
		height: 42px;
		padding: 0 13px;
	}

	.secondary-nav__title {
		font-size: 15px;
	}

	.secondary-nav__list {
		padding: 8px 8px 10px;
	}

	.secondary-nav__item {
		padding: 9px 12px;
		font-size: 13px;
	}

	.admin-shell__tabs :deep(.el-tabs__item) {
		height: 36px;
		padding: 0 12px;
	}
}
</style>
