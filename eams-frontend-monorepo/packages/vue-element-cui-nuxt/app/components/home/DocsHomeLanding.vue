<template>
	<div class="space-y-10">
		<section
			class="docs-home-shell grid gap-8 px-6 py-8 lg:grid-cols-[minmax(0,1.35fr)_minmax(320px,0.65fr)] lg:px-8 lg:py-10"
		>
			<div class="relative space-y-6">
				<div
					class="inline-flex items-center gap-2 rounded-full border border-sky-200/80 bg-sky-50 px-3 py-1 text-xs font-semibold text-sky-900 dark:border-sky-900 dark:bg-sky-950/40 dark:text-sky-100"
				>
					<span class="h-2 w-2 rounded-full bg-sky-500" />
					Vue Element CUI 组件库文档
				</div>

				<div class="space-y-4">
					<h1 class="max-w-3xl text-4xl font-semibold tracking-tight text-foreground lg:text-5xl">
						从安装、演示到规范，按组件库官网的方式组织文档入口。
					</h1>
					<p class="max-w-2xl text-base leading-7 text-muted-foreground">
						这里不再把文档当成零散的 markdown
						列表。首页优先给出安装、快速开始、组件分类和规范入口，再把常见的表格、表单、选择器和弹层能力用真实组件直接跑起来。
					</p>
				</div>

				<div class="flex flex-wrap gap-3">
					<NuxtLink
						v-for="action in primaryActions"
						:key="action.to"
						:to="action.to"
						class="inline-flex items-center gap-2 rounded-full border border-border bg-background px-4 py-2 text-sm font-medium text-foreground transition hover:bg-accent hover:text-accent-foreground"
					>
						<Icon :name="action.icon" class="h-4 w-4" />
						{{ action.label }}
					</NuxtLink>
				</div>

				<HomeQuickStartLinks :entries="sectionEntries" />
			</div>

			<div
				class="space-y-4 rounded-2xl border border-slate-200/80 bg-slate-950 p-5 text-slate-100 shadow-sm dark:border-slate-800"
			>
				<div class="flex items-center justify-between">
					<p class="text-sm font-semibold text-slate-50">安装命令</p>
					<span class="rounded-full border border-slate-700 px-2 py-1 text-xs text-slate-300">pnpm</span>
				</div>
				<pre
					class="overflow-auto rounded-xl bg-slate-900 p-4 text-sm leading-6 text-sky-100"
				><code>pnpm add @eams-monorepo/vue-element-cui element-plus</code></pre>
				<div class="space-y-3 text-sm text-slate-300">
					<p>推荐先走一遍安装和快速开始，再根据组件类型进入对应栏目。</p>
					<ul class="space-y-2">
						<li v-for="point in installPoints" :key="point" class="flex items-start gap-2">
							<span class="mt-2 h-1.5 w-1.5 rounded-full bg-sky-400" />
							<span>{{ point }}</span>
						</li>
					</ul>
				</div>
			</div>
		</section>

		<section class="space-y-4">
			<div class="flex items-center justify-between gap-3">
				<div>
					<h2 class="text-xl font-semibold text-foreground">组件分类入口</h2>
					<p class="mt-1 text-sm text-muted-foreground">先按类型找入口，再进入对应的体系页看 demo、代码和 API。</p>
				</div>
				<NuxtLink
					to="/components"
					class="text-sm font-medium text-sky-700 transition hover:text-sky-800 dark:text-sky-300 dark:hover:text-sky-200"
				>
					查看全部组件
				</NuxtLink>
			</div>

			<HomeCategoryGrid :categories="componentCategories" />
		</section>
	</div>
</template>

<script setup lang="ts">
import HomeCategoryGrid from "../site/HomeCategoryGrid.vue";
import HomeQuickStartLinks from "../site/HomeQuickStartLinks.vue";

const primaryActions = [
	{ label: "开始安装", to: "/getting-started/installation", icon: "lucide:download" },
	{ label: "查看组件", to: "/components", icon: "lucide:layout-grid" },
	{ label: "阅读规范", to: "/guidelines", icon: "lucide:book-open" },
];

const sectionEntries = [
	{
		title: "快速开始",
		description: "安装、接入、迁移和排障入口集中在同一栏目，不再分散跳转。",
		to: "/getting-started",
		icon: "lucide:rocket",
	},
	{
		title: "组件",
		description: "按数据展示、表单输入、选择器、弹层交互等类型重组页面结构。",
		to: "/components",
		icon: "lucide:component",
	},
	{
		title: "规范",
		description: "把跨组件的设计约定、最佳实践和开发约定独立沉淀。",
		to: "/guidelines",
		icon: "lucide:badge-info",
	},
	{
		title: "更新",
		description: "保留版本变更和迁移提醒，方便团队统一升级节奏。",
		to: "/updates",
		icon: "lucide:history",
	},
];

const installPoints = [
	"接入真实 @eams-monorepo/vue-element-cui 组件和样式。",
	"组件体系页默认提供 live demo 优先的阅读模型。",
	"规范栏目专门收纳共性经验，而不是散回组件页面。",
];

const componentCategories = [
	{
		title: "数据展示",
		description: "聚焦表格和详情展示，先确认字段结构，再考虑扩展渲染。",
		to: "/components/data-display",
		icon: "lucide:table-properties",
		items: "CuiTable / CuiDetail / CuiExcel",
	},
	{
		title: "表单输入",
		description: "覆盖动态表单与录入场景，适合快速搭建新增和编辑页面。",
		to: "/components/form-input",
		icon: "lucide:form-input",
		items: "CuiForm / CuiAutocomplete",
	},
	{
		title: "选择器",
		description: "把 select、enum、dict、autocomplete 等选择类能力集中整理。",
		to: "/components/selectors",
		icon: "lucide:list-filter",
		items: "CuiSelect / 枚举类 / 选择容器",
	},
	{
		title: "反馈与弹层",
		description: "统一说明基础弹层、对话框表单和交互建议。",
		to: "/components/feedback-overlay",
		icon: "lucide:square-stack",
		items: "CuiDialog / CuiDialogForm",
	},
	{
		title: "导航与布局",
		description: "针对搜索和标签页等页面组织能力提供入口和使用建议。",
		to: "/components/navigation-layout",
		icon: "lucide:panels-top-left",
		items: "CuiSearch / CuiTab",
	},
	{
		title: "扩展能力",
		description: "保留业务增强组件入口，便于继续沉淀上传、导入导出等能力。",
		to: "/components/extensions",
		icon: "lucide:puzzle",
		items: "业务增强 / 后续扩展",
	},
];
</script>
