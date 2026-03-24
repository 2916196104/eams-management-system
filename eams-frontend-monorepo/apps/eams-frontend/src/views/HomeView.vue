<template>
	<div class="header-row">
		<div class="header-title">
			<img v-show="!isCollapse" class="app-icon" src="/logo.jpg" :title="appName" />
			<el-text v-show="!isCollapse" class="app-name">{{ appName }}</el-text>
			<el-button
				v-show="isCollapse"
				link
				class="collapse-btn"
				icon="IconExpand"
				@click="isCollapse = !isCollapse"
			></el-button>
			<el-button
				v-show="!isCollapse"
				link
				class="collapse-btn"
				icon="IconFold"
				@click="isCollapse = !isCollapse"
			></el-button>
		</div>
		<div class="header-nav">
			<el-avatar :size="30" :src="user?.avatar" />
			{{ userInfo }}
		</div>
	</div>
	<div class="content-row">
		<el-menu
			:collapse="isCollapse"
			:default-active="activeIndex"
			active-text-color="#409EFF"
			text-color="#fff"
			background-color="#545c64"
			unique-opened
			:collapse-transition="false"
			router
		>
			<el-menu-item :index="indexPath">
				<el-icon>
					<IconHomeFilled />
				</el-icon>
				<span>首页</span>
			</el-menu-item>
			<el-sub-menu v-for="item in menus" :key="item.id" :index="`${item.id}submenu`">
				<template #title>
					<el-icon>
						<component :is="renderMenuIcon(item.icon)" />
					</el-icon>
					<span>{{ item.text }}</span>
				</template>
				<el-menu-item-group>
					<el-menu-item v-for="child in item.children" :key="child.id" :index="child.href">
						<el-icon>
							<component :is="renderMenuIcon(child.icon)" />
						</el-icon>
						{{ child.text }}
					</el-menu-item>
				</el-menu-item-group>
			</el-sub-menu>
		</el-menu>
		<div class="main">
			<el-tabs
				v-model="activeIndex"
				type="border-card"
				:before-leave="beforeLeave"
				@tab-click="tabClick"
				@tab-remove="tabClose"
			>
				<el-tab-pane :name="indexPath" style="height: 0">
					<template #label>
						<el-icon>
							<IconHomeFilled />
						</el-icon>
						<span style="padding-left: 5px">首页</span>
					</template>
				</el-tab-pane>
				<el-tab-pane
					v-for="(item, index) in tabs"
					:key="`${index}tab`"
					:label="item.label"
					:name="item.path"
					closable
					style="height: 0"
				/>
				<el-tab-pane style="height: 0" name="tab-operation">
					<template #label>
						<el-dropdown trigger="click">
							<el-button class="operation-icon" type="info" link>
								<el-icon size="22">
									<IconOperation />
								</el-icon>
							</el-button>
							<template #dropdown>
								<el-dropdown-menu>
									<el-dropdown-item :disabled="tabs.length === 0" icon="IconCloseBlod" @click="handleClose(1)">
										关闭所有标签页
									</el-dropdown-item>
									<el-dropdown-item
										:disabled="activeIndex === indexPath || tabstore.getTabIndex(activeIndex) === 0"
										icon="IconCloseBlod"
										@click="handleClose(2)"
									>
										关闭当前标签页左边
									</el-dropdown-item>
									<el-dropdown-item
										:disabled="tabstore.getTabIndex(activeIndex) === tabs.length - 1"
										icon="IconCloseBlod"
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
			<router-view />
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { useRouter } from "vue-router";
import { storeToRefs } from "pinia";
import type { TabPaneName, TabsPaneContext } from "element-plus";
import { useRenderIcon } from "@/components/ReIcon";
import { useUserStore } from "@/stores/user";
import { useTabStore } from "@/stores/tab";

const appName = import.meta.env.VITE_APP_TITLE;
const ustore = useUserStore();
const { user, menus } = storeToRefs(ustore);
const userInfo = ref(`欢迎用户：${user.value === null ? "游客" : user.value.username}`);
const isCollapse = ref(false);
const router = useRouter();
const tabstore = useTabStore();
const { tabs, activeIndex, indexPath } = storeToRefs(tabstore);

function renderMenuIcon(icon?: string) {
	return useRenderIcon(icon || "ep/menu");
}

const tabClick = (pane: TabsPaneContext) => {
	if (pane.paneName === "tab-operation") return;
	tabstore.setActiveIndex(pane.paneName as string);
	router.push({ path: activeIndex.value });
};

const tabClose = (name: TabPaneName) => {
	if (activeIndex.value === name) {
		const idx = tabstore.getTabIndex(name as string) - 1;
		if (idx >= 0) activeIndex.value = tabs.value[idx].path;
		else activeIndex.value = indexPath.value;
		router.push({ path: activeIndex.value });
	}
	tabstore.remTab(name as string);
};

const beforeLeave = (activeName: TabPaneName) => {
	if (activeName === "tab-operation") return false;
	return true;
};

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
</script>

<style>
:root {
	--home-header-height: 60px;
	--home-menu-width: 220px;
}
.main .el-tabs {
	.el-tabs__header {
		padding: 0;
		margin-bottom: 0;
	}
	.el-tabs__content {
		padding-top: 0;
		padding-bottom: 0;
	}
	#tab-tab-operation {
		padding: 0;
	}
}
</style>

<style scoped>
.header-row {
	height: var(--home-header-height);
	background-color: #6c777f;
	display: flex;
	align-items: center;
	justify-content: space-between;

	.header-title {
		width: var(--home-menu-width);
		padding-left: 15px;
		display: flex;
		align-items: center;
		justify-content: space-between;

		.app-icon {
			width: 30px;
			border-radius: 5px;
		}

		.app-name {
			color: white;
			font-size: 16px;
		}

		.collapse-btn {
			color: white;
			font-size: 24px;
		}
	}

	.header-nav {
		display: flex;
		justify-content: flex-end;
		align-items: center;
		gap: 10px;
		padding-right: 15px;
		color: #f8f8f8;
		text-align: right;
	}
}

.content-row {
	height: calc(100vh - var(--home-header-height));
	display: flex;
	flex-direction: row;

	.el-menu {
		border: 0;
		width: var(--home-menu-width);
		height: 100%;
		overflow: auto;
	}

	.el-menu--collapse {
		width: calc(var(--el-menu-icon-width) + var(--el-menu-base-level-padding) * 2);
	}

	.main {
		flex: 1;
		background-color: #edecec;
		width: calc(100vw - var(--home-menu-width));
		height: 100%;
		overflow: auto;

		.operation-icon {
			padding: calc(var(--el-tabs-header-height) / 2 - 12px) 20px;
		}
	}
}
</style>
