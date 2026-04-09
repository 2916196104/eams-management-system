<template>
	<section class="demo-page">
		<EamsNav
			:menus="menus"
			app-name="教务系统导航示例"
			logo-src="/logo.jpg"
			user-text="动态菜单演示"
			:collapse="collapse"
			:default-active="activeIndex"
			:router="false"
			@update:collapse="collapse = $event"
			@select="handleSelect"
		>
			<div class="workspace">
				<section class="hero-card">
					<div>
						<p class="hero-card__eyebrow">当前展示</p>
						<h2 class="hero-card__title">{{ currentTitle }}</h2>
						<p class="hero-card__desc">
							这个页面用来演示 `mynav` 组件的一级菜单、二级菜单和动态修改能力。右侧表单改完后，左边导航会立即更新。
						</p>
					</div>
				</section>

				<section class="panel-grid">
					<el-card shadow="hover" class="panel-card">
						<template #header>
							<div class="panel-card__header">
								<span>菜单编辑</span>
								<el-tag type="success">动态数据</el-tag>
							</div>
						</template>

						<el-form label-width="96px" class="panel-form">
							<el-form-item label="选择菜单">
								<el-select v-model="renameTargetId" placeholder="请选择需要修改的菜单">
									<el-option v-for="option in menuOptions" :key="option.id" :label="option.label" :value="option.id" />
								</el-select>
							</el-form-item>
							<el-form-item label="新名称">
								<el-input v-model="renameText" placeholder="输入新的菜单名称" />
							</el-form-item>
							<el-form-item>
								<el-button type="primary" @click="renameMenu">修改菜单名</el-button>
							</el-form-item>
						</el-form>

						<el-divider />

						<el-form label-width="96px" class="panel-form">
							<el-form-item label="所属一级菜单">
								<el-select v-model="newChildParentId" placeholder="请选择一级菜单">
									<el-option
										v-for="option in topLevelOptions"
										:key="option.id"
										:label="option.label"
										:value="option.id"
									/>
								</el-select>
							</el-form-item>
							<el-form-item label="二级菜单名">
								<el-input v-model="newChildText" placeholder="例如：成绩查询" />
							</el-form-item>
							<el-form-item label="菜单索引">
								<el-input v-model="newChildPath" placeholder="例如：score-query" />
							</el-form-item>
							<el-form-item>
								<el-button type="primary" plain @click="addChildMenu">新增二级菜单</el-button>
								<el-button @click="resetMenus">重置示例数据</el-button>
							</el-form-item>
						</el-form>
					</el-card>

					<el-card shadow="hover" class="panel-card">
						<template #header>
							<div class="panel-card__header">
								<span>菜单数据预览</span>
								<el-tag type="info">实时同步</el-tag>
							</div>
						</template>

						<div class="data-preview">
							<pre>{{ menusJson }}</pre>
						</div>
					</el-card>
				</section>
			</div>
		</EamsNav>
	</section>
</template>

<script setup lang="ts">
import { computed, ref } from "vue";
import EamsNav from "@/components/mynav/EamsNav.vue";
import type { EamsNavMenuItem } from "@/components/mynav/type";

type MenuOption = {
	id: string;
	label: string;
};

/**
 * 这里说明 mynav 的 icon 写法已经发生扩展：
 * 1. 旧写法仍兼容：`IconMenu`、`IconUser`
 * 2. 推荐离线 iconify 写法：`图标集/图标名`，例如 `ep/menu`、`ep/home-filled`
 * 3. 在线 iconify 写法：`图标集:图标名`，例如 `ri:home-4-line`
 *
 * 当前示例统一改成离线 iconify 写法，便于后台项目按需打包并保持稳定。
 *
 * 常见迁移示例：
 * - `IconHomeFilled` -> `ep/home-filled`
 * - `IconUser` -> `ep/user`
 * - `IconTickets` -> `ep/tickets`
 * - `IconMenu` -> `ep/menu`
 *
 * 完整调研文档：
 * https://01s-11comm-doc.ruan-cat.com/docs/reports/2025-11-14-pure-admin-icon-solution-research.md
 *
 * Iconify 官方文档：
 * https://iconify.design/docs/
 */
const createMenus = (): EamsNavMenuItem[] => [
	{
		id: "dashboard",
		text: "工作台",
		path: "dashboard",
		icon: "ep/home-filled",
	},
	{
		id: "student",
		text: "学籍管理",
		icon: "ep/user",
		children: [
			{
				id: "student-status",
				text: "学籍信息",
				path: "student-status",
				icon: "ep/tickets",
			},
			{
				id: "student-change",
				text: "异动管理",
				path: "student-change",
				icon: "ep/tickets",
			},
		],
	},
	{
		id: "course",
		text: "教学管理",
		icon: "ep/setting",
		children: [
			{
				id: "course-plan",
				text: "培养方案",
				path: "course-plan",
				icon: "ep/menu",
			},
			{
				id: "course-table",
				text: "课表安排",
				path: "course-table",
				icon: "ep/menu",
			},
		],
	},
];

const menus = ref<EamsNavMenuItem[]>(createMenus());
const collapse = ref(false);
const activeIndex = ref("dashboard");

const renameTargetId = ref("student-status");
const renameText = ref("学生档案");
const newChildParentId = ref("course");
const newChildText = ref("成绩查询");
const newChildPath = ref("score-query");

const currentTitle = computed(() => {
	const current = findMenuByIndex(menus.value, activeIndex.value);
	return current?.text ?? "请选择菜单";
});

const childMenuCount = computed(() => menus.value.reduce((count, item) => count + (item.children?.length ?? 0), 0));

const menuOptions = computed<MenuOption[]>(() => {
	const options: MenuOption[] = [];
	appendMenuOptions(menus.value, options);
	return options;
});

const topLevelOptions = computed<MenuOption[]>(() =>
	menus.value.map((item) => ({
		id: String(item.id),
		label: item.text,
	})),
);

const menusJson = computed(() => JSON.stringify(menus.value, null, 2));

function handleSelect(item?: EamsNavMenuItem) {
	if (!item) return;
	activeIndex.value = item.path || item.href || String(item.id);
}

function renameMenu() {
	const targetId = renameTargetId.value.trim();
	const targetText = renameText.value.trim();
	if (!targetId || !targetText) return;
	updateMenuById(menus.value, targetId, (item) => {
		item.text = targetText;
	});
}

function addChildMenu() {
	const parentId = newChildParentId.value.trim();
	const text = newChildText.value.trim();
	const path = newChildPath.value.trim();
	if (!parentId || !text || !path) return;

	updateMenuById(menus.value, parentId, (item) => {
		if (!item.children) item.children = [];
		/** 新增菜单时也继续写入 iconify 离线格式，避免回退成旧的 `IconMenu` */
		item.children.push({
			id: `${parentId}-${Date.now()}`,
			text,
			path,
			icon: "ep/menu",
		});
	});

	activeIndex.value = path;
	newChildText.value = "";
	newChildPath.value = "";
}

function resetMenus() {
	menus.value = createMenus();
	activeIndex.value = "dashboard";
	renameTargetId.value = "student-status";
	renameText.value = "学生档案";
	newChildParentId.value = "course";
	newChildText.value = "成绩查询";
	newChildPath.value = "score-query";
}

function appendMenuOptions(items: EamsNavMenuItem[], options: MenuOption[], prefix = "") {
	for (const item of items) {
		const label = prefix ? `${prefix} / ${item.text}` : item.text;
		options.push({
			id: String(item.id),
			label,
		});
		if (item.children?.length) {
			appendMenuOptions(item.children, options, item.text);
		}
	}
}

function updateMenuById(items: EamsNavMenuItem[], targetId: string, updater: (item: EamsNavMenuItem) => void): boolean {
	for (const item of items) {
		if (String(item.id) === targetId) {
			updater(item);
			return true;
		}
		if (item.children?.length && updateMenuById(item.children, targetId, updater)) {
			return true;
		}
	}
	return false;
}

function findMenuByIndex(items: EamsNavMenuItem[], index: string): EamsNavMenuItem | undefined {
	for (const item of items) {
		const itemIndex = item.path || item.href || String(item.id);
		if (itemIndex === index) return item;
		if (item.children?.length) {
			const child = findMenuByIndex(item.children, index);
			if (child) return child;
		}
	}
	return undefined;
}
</script>

<style scoped>
.demo-page {
	margin: -10px;
}

.workspace {
	display: flex;
	flex-direction: column;
	gap: 16px;
}

.hero-card {
	padding: 0;
}

.hero-card__eyebrow {
	margin: 0 0 8px;
	font-size: 12px;
	letter-spacing: 0.14em;
	text-transform: uppercase;
	opacity: 0.8;
}

.hero-card__title {
	margin: 0;
	font-size: 28px;
	line-height: 1.2;
	color: #1f2937;
}

.hero-card__desc {
	max-width: 720px;
	margin: 12px 0 0;
	line-height: 1.7;
	color: #4b5563;
}

.panel-grid {
	display: grid;
	grid-template-columns: minmax(320px, 420px) minmax(0, 1fr);
	gap: 16px;
}

.panel-card {
	border-radius: 18px;
}

.panel-card__header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
	font-weight: 600;
}

.panel-form :deep(.el-select),
.panel-form :deep(.el-input) {
	width: 100%;
}

.data-preview {
	min-height: 420px;
	max-height: 520px;
	padding: 16px;
	border-radius: 14px;
	background: #0f172a;
	overflow: auto;
}

.data-preview pre {
	margin: 0;
	color: #dbeafe;
	font-size: 13px;
	line-height: 1.6;
	font-family: Consolas, Monaco, monospace;
}

@media (max-width: 960px) {
	.panel-grid {
		grid-template-columns: 1fr;
	}
}
</style>
