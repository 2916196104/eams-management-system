<template>
	<div class="eams-nav" :style="styleVars">
		<div class="eams-nav__header">
			<div class="eams-nav__brand">
				<img v-if="logoSrc" class="eams-nav__logo" :src="logoSrc" :alt="appName" />
				<el-text v-show="!isCollapse" class="eams-nav__title">
					{{ appName }}
				</el-text>
				<el-button
					link
					class="eams-nav__collapse-btn"
					:icon="isCollapse ? 'IconExpand' : 'IconFold'"
					@click="toggleCollapse"
				/>
			</div>
			<div class="eams-nav__header-extra">
				<slot name="header-extra">
					{{ userText }}
				</slot>
			</div>
		</div>

		<div class="eams-nav__body">
			<el-menu
				:collapse="isCollapse"
				:default-active="activeIndex"
				:router="router"
				:unique-opened="uniqueOpened"
				:collapse-transition="collapseTransition"
				:background-color="backgroundColor"
				:text-color="textColor"
				:active-text-color="activeTextColor"
				class="eams-nav__menu"
				@select="handleSelect"
			>
				<el-menu-item v-if="showHome" :index="homePath">
					<el-icon>
						<component :is="homeIconComponent" />
					</el-icon>
					<span>{{ homeText }}</span>
				</el-menu-item>

				<template v-for="item in normalizedMenus" :key="item.id">
					<el-sub-menu v-if="item.children && item.children.length > 0" :index="getSubMenuIndex(item)">
						<template #title>
							<el-icon>
								<component :is="item.icon" />
							</el-icon>
							<span>{{ item.text }}</span>
						</template>

						<el-menu-item
							v-for="child in item.children"
							:key="child.id"
							:index="child.index"
							:disabled="child.disabled"
						>
							<el-icon>
								<component :is="child.icon" />
							</el-icon>
							<span>{{ child.text }}</span>
						</el-menu-item>
					</el-sub-menu>

					<el-menu-item v-else :index="item.index" :disabled="item.disabled">
						<el-icon>
							<component :is="item.icon" />
						</el-icon>
						<span>{{ item.text }}</span>
					</el-menu-item>
				</template>
			</el-menu>

			<div class="eams-nav__content">
				<slot />
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, ref, watch } from "vue";
import type { Component } from "vue";
import { useRoute } from "vue-router";
import { useRenderIcon } from "@/components/ReIcon";
import type { EamsNavMenuItem, EamsNavProps } from "./type";

defineOptions({
	name: "EamsNav",
});

interface NormalizedMenuItem extends EamsNavMenuItem {
	icon: Component;
	index: string;
	children?: Array<NormalizedMenuItem>;
}

const props = withDefaults(defineProps<EamsNavProps>(), {
	appName: "教务系统",
	logoSrc: "",
	userText: "",
	collapse: false,
	defaultActive: "",
	menuWidth: "220px",
	headerHeight: "60px",
	showHome: false,
	homeText: "首页",
	homePath: "/",
	homeIcon: "IconHomeFilled",
	defaultIcon: "IconMenu",
	backgroundColor: "#545c64",
	textColor: "#ffffff",
	activeTextColor: "#409eff",
	uniqueOpened: true,
	router: true,
	collapseTransition: false,
});

const emit = defineEmits<{
	(e: "update:collapse", value: boolean): void;
	(e: "select", item: EamsNavMenuItem | undefined): void;
}>();

const route = useRoute();
const isCollapse = ref(props.collapse);
const activeIndex = ref("");
const homeIconComponent = computed(() => useRenderIcon(props.homeIcon));

const normalizedMenus = computed<NormalizedMenuItem[]>(() => props.menus.map((item) => normalizeMenuItem(item)));

const flatMenuMap = computed(() => {
	const menuMap = new Map<string, EamsNavMenuItem>();

	const walk = (menus: NormalizedMenuItem[]) => {
		for (const item of menus) {
			menuMap.set(item.index, item);
			if (item.children?.length) {
				walk(item.children);
			}
		}
	};

	walk(normalizedMenus.value);
	return menuMap;
});

const styleVars = computed(() => ({
	"--eams-nav-header-height": props.headerHeight,
	"--eams-nav-menu-width": props.menuWidth,
}));

watch(
	() => props.collapse,
	(value) => {
		isCollapse.value = value;
	},
);

watch(
	[() => props.defaultActive, () => route.path, normalizedMenus],
	() => {
		if (props.defaultActive) {
			activeIndex.value = props.defaultActive;
			return;
		}

		if (props.router && flatMenuMap.value.has(route.path)) {
			activeIndex.value = route.path;
			return;
		}

		if (props.showHome && route.path === props.homePath) {
			activeIndex.value = props.homePath;
			return;
		}

		const firstMenu = normalizedMenus.value[0];
		activeIndex.value = firstMenu?.children?.[0]?.index ?? firstMenu?.index ?? props.homePath;
	},
	{ immediate: true, deep: true },
);

function normalizeMenuItem(item: EamsNavMenuItem): NormalizedMenuItem {
	return {
		...item,
		icon: useRenderIcon(item.icon || props.defaultIcon),
		index: getMenuIndex(item),
		children: item.children?.map((child) => normalizeMenuItem(child)),
	};
}

function getMenuIndex(item: EamsNavMenuItem): string {
	return item.path || item.href || String(item.id);
}

function getSubMenuIndex(item: NormalizedMenuItem): string {
	return `submenu-${item.id}`;
}

function toggleCollapse() {
	isCollapse.value = !isCollapse.value;
	emit("update:collapse", isCollapse.value);
}

function handleSelect(index: string) {
	emit("select", flatMenuMap.value.get(index));
	activeIndex.value = index;
}
</script>

<style scoped>
.eams-nav {
	min-height: 100vh;
	background: #edf1f5;
}

.eams-nav__header {
	height: var(--eams-nav-header-height);
	display: flex;
	align-items: center;
	justify-content: space-between;
	background: #6c777f;
	color: #ffffff;
}

.eams-nav__brand {
	width: var(--eams-nav-menu-width);
	padding: 0 16px;
	display: flex;
	align-items: center;
	gap: 10px;
	box-sizing: border-box;
}

.eams-nav__logo {
	width: 30px;
	height: 30px;
	border-radius: 6px;
	object-fit: cover;
	flex-shrink: 0;
}

.eams-nav__title {
	flex: 1;
	color: #ffffff;
	font-size: 16px;
	overflow: hidden;
	text-overflow: ellipsis;
	white-space: nowrap;
}

.eams-nav__collapse-btn {
	color: #ffffff;
	font-size: 20px;
}

.eams-nav__header-extra {
	padding: 0 16px;
	display: flex;
	align-items: center;
	justify-content: flex-end;
	flex: 1;
	min-width: 0;
}

.eams-nav__body {
	display: flex;
	min-height: calc(100vh - var(--eams-nav-header-height));
}

.eams-nav__menu {
	width: var(--eams-nav-menu-width);
	border-right: 0;
	flex-shrink: 0;
}

.eams-nav__menu:not(.el-menu--collapse) {
	min-height: calc(100vh - var(--eams-nav-header-height));
}

.eams-nav__content {
	flex: 1;
	min-width: 0;
	padding: 16px;
	box-sizing: border-box;
	overflow: auto;
}
</style>
