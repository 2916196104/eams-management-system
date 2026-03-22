<template>
	<section class="reicon-demo">
		<header class="hero">
			<div>
				<p class="eyebrow">Admin Iconify</p>
				<h2>ReIcon 图标方案演示</h2>
				<p class="desc">
					这个页面用于展示后台项目中 iconify 的四种接入方式，并验证它与现有 `IconXxx` 组件别名、`mynav`
					菜单配置和动态渲染 hook 的兼容性。
				</p>
			</div>
			<el-tag type="success">11comm 方案已接入</el-tag>
		</header>

		<section class="grid">
			<el-card shadow="hover">
				<template #header>
					<div class="card-header">
						<span>旧别名兼容</span>
						<el-tag>Legacy</el-tag>
					</div>
				</template>
				<div class="icon-list">
					<div v-for="item in legacyIcons" :key="item.label" class="icon-item">
						<el-icon :size="20">
							<component :is="item.icon" />
						</el-icon>
						<div>
							<div class="item-title">{{ item.label }}</div>
							<div class="item-text">{{ item.description }}</div>
						</div>
					</div>
				</div>
			</el-card>

			<el-card shadow="hover">
				<template #header>
					<div class="card-header">
						<span>离线字符串</span>
						<el-tag type="success">Offline</el-tag>
					</div>
				</template>
				<div class="icon-list">
					<div v-for="item in offlineIcons" :key="item.label" class="icon-item">
						<IconifyIconOffline :icon="item.icon" width="20" height="20" />
						<div>
							<div class="item-title">{{ item.label }}</div>
							<div class="item-text">{{ item.description }}</div>
						</div>
					</div>
				</div>
			</el-card>

			<el-card shadow="hover">
				<template #header>
					<div class="card-header">
						<span>在线字符串</span>
						<el-tag type="warning">Online</el-tag>
					</div>
				</template>
				<div class="icon-list">
					<div v-for="item in onlineIcons" :key="item.label" class="icon-item">
						<IconifyIconOnline :icon="item.icon" width="20" height="20" />
						<div>
							<div class="item-title">{{ item.label }}</div>
							<div class="item-text">{{ item.description }}</div>
						</div>
					</div>
				</div>
			</el-card>

			<el-card shadow="hover">
				<template #header>
					<div class="card-header">
						<span>直接导入组件</span>
						<el-tag type="info">Import</el-tag>
					</div>
				</template>
				<div class="icon-list">
					<div v-for="item in importedIcons" :key="item.label" class="icon-item">
						<component :is="item.icon" width="20" height="20" />
						<div>
							<div class="item-title">{{ item.label }}</div>
							<div class="item-text">{{ item.description }}</div>
						</div>
					</div>
				</div>
			</el-card>
		</section>

		<section class="grid secondary">
			<el-card shadow="hover">
				<template #header>
					<div class="card-header">
						<span>useRenderIcon Hook</span>
						<el-tag type="primary">Hook</el-tag>
					</div>
				</template>
				<div class="icon-list">
					<div v-for="item in hookIcons" :key="item.label" class="icon-item">
						<component :is="item.icon" />
						<div>
							<div class="item-title">{{ item.label }}</div>
							<div class="item-text">{{ item.description }}</div>
						</div>
					</div>
				</div>
			</el-card>

			<el-card shadow="hover">
				<template #header>
					<div class="card-header">
						<span>mynav 菜单接入</span>
						<el-tag type="success">Config Driven</el-tag>
					</div>
				</template>
				<div class="nav-demo">
					<EamsNav
						:menus="navMenus"
						app-name="图标菜单"
						user-text="ReIcon"
						:router="false"
						:show-home="true"
						home-icon="ep/home-filled"
						@select="handleSelect"
					>
						<div class="nav-preview">
							<p class="item-title">当前选中</p>
							<p class="item-text">{{ activeMenu }}</p>
						</div>
					</EamsNav>
				</div>
			</el-card>
		</section>
	</section>
</template>

<script setup lang="ts">
import { ref } from "vue";
import type { Component } from "vue";
import MdiCalendarMonthOutline from "~icons/mdi/calendar-month-outline";
import RiUserStarLine from "~icons/ri/user-star-line";
import EamsNav from "@/components/mynav/EamsNav.vue";
import { IconifyIconOffline, IconifyIconOnline, useRenderIcon } from "@/components/ReIcon";
import type { EamsNavMenuItem } from "@/components/mynav/type";
type StringIconOption = {
	label: string;
	icon: string;
	description?: string;
};

type ComponentIconOption = {
	label: string;
	icon: Component;
	description?: string;
};

type RenderedIconOption = {
	label: string;
	icon: Component;
	description?: string;
};

const legacyIcons: StringIconOption[] = [
	{ label: "IconMenu", icon: "IconMenu", description: "沿用现有全局组件别名" },
	{ label: "IconSearch", icon: "IconSearch", description: "旧页面无须立刻迁移" },
];

const offlineIcons: StringIconOption[] = [
	{ label: "ep/menu", icon: "ep/menu", description: "离线字符串，推荐用于后台常用图标" },
	{ label: "ep/setting", icon: "ep/setting", description: "通过 unplugin-icons 按需打包" },
];

const onlineIcons: StringIconOption[] = [
	{ label: "ri:home-4-line", icon: "ri:home-4-line", description: "在线模式，适合长尾图标" },
	{
		label: "mdi:shield-check-outline",
		icon: "mdi:shield-check-outline",
		description: "需要网络时可直接走 iconify CDN",
	},
];

const importedIcons: ComponentIconOption[] = [
	{ label: "mdi/calendar-month-outline", icon: MdiCalendarMonthOutline, description: "直接导入组件使用" },
	{ label: "ri/user-star-line", icon: RiUserStarLine, description: "类型安全，适合在脚本中传递" },
];

const hookIcons: RenderedIconOption[] = [
	{
		label: "离线 hook",
		icon: useRenderIcon("ep/menu", { width: "20px", height: "20px" }),
		description: "字符串会自动分流到离线组件",
	},
	{
		label: "在线 hook",
		icon: useRenderIcon("ri:home-4-line", { width: "20px", height: "20px" }),
		description: "带冒号且未命中离线表时走在线组件",
	},
	{
		label: "组件 hook",
		icon: useRenderIcon(MdiCalendarMonthOutline, { width: "20px", height: "20px" }),
		description: "直接导入的组件也能复用同一个 hook",
	},
];

const activeMenu = ref("overview");
const navMenus: EamsNavMenuItem[] = [
	{
		id: "overview",
		text: "总览",
		path: "overview",
		icon: "ep/home-filled",
	},
	{
		id: "system",
		text: "系统管理",
		icon: "ep/setting",
		children: [
			{
				id: "users",
				text: "用户管理",
				path: "users",
				icon: "IconUser",
			},
			{
				id: "roles",
				text: "角色权限",
				path: "roles",
				icon: "ri:shield-user-line",
			},
		],
	},
];

function handleSelect(item?: EamsNavMenuItem) {
	activeMenu.value = item?.text ?? "overview";
}
</script>

<style scoped lang="scss">
.reicon-demo {
	display: flex;
	flex-direction: column;
	gap: 16px;
}

.hero {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 16px;
	padding: 24px;
	border-radius: 20px;
	background: linear-gradient(135deg, #f8fafc 0%, #dbeafe 100%);
}

.eyebrow {
	margin: 0 0 8px;
	font-size: 12px;
	letter-spacing: 0.12em;
	text-transform: uppercase;
	color: #2563eb;
}

.hero h2 {
	margin: 0;
	font-size: 28px;
	color: #111827;
}

.desc {
	max-width: 760px;
	margin: 12px 0 0;
	line-height: 1.7;
	color: #475569;
}

.grid {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 16px;
}

.secondary {
	align-items: start;
}

.card-header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
	font-weight: 600;
}

.icon-list {
	display: flex;
	flex-direction: column;
	gap: 14px;
}

.icon-item {
	display: flex;
	align-items: center;
	gap: 14px;
	padding: 14px 16px;
	border-radius: 14px;
	background: #f8fafc;
}

.item-title {
	margin: 0;
	font-weight: 600;
	color: #111827;
}

.item-text {
	margin: 4px 0 0;
	color: #64748b;
	line-height: 1.6;
}

.nav-demo {
	overflow: hidden;
	border-radius: 18px;
	border: 1px solid #e2e8f0;
}

.nav-preview {
	min-height: 280px;
	padding: 24px;
	background: linear-gradient(180deg, #f8fafc 0%, #eef2ff 100%);
}

@media (max-width: 960px) {
	.hero {
		flex-direction: column;
	}

	.grid {
		grid-template-columns: 1fr;
	}
}
</style>
