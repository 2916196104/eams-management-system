<template>
	<div class="header-row">
		<!-- 应用信息栏 -->
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
		<!-- 导航栏 -->
		<div class="header-nav">示例效果演示页</div>
	</div>
	<div class="content-row">
		<!-- 侧边菜单栏 -->
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
			<template v-for="(menu, index) in menus">
				<el-sub-menu v-if="menu.children" :key="index" :index="menu.id + 'submenu'">
					<template #title>
						<el-icon>
							<icon-menu />
						</el-icon>
						<span>{{ menu.text }}</span>
					</template>
					<el-menu-item-group>
						<el-menu-item v-for="i in menu.children" :key="i.id" :index="i.path">
							<el-icon>
								<icon-menu />
							</el-icon>
							<span>{{ i.text }}</span>
						</el-menu-item>
					</el-menu-item-group>
				</el-sub-menu>
				<el-menu-item v-else :key="index * 100" :index="menu.path">
					<el-icon>
						<icon-menu />
					</el-icon>
					<span>{{ menu.text }}</span>
				</el-menu-item>
			</template>
		</el-menu>
		<!-- 主内容区 -->
		<div class="main">
			<!-- 二级路由 -->
			<router-view />
		</div>
	</div>
</template>

<style>
:root {
	--sample-header-height: 60px;
	--sample-menu-width: 220px;
}
</style>
<style scoped>
.header-row {
	height: var(--sample-header-height);
	background-color: #6c777f;
	display: flex;
	align-items: center;
	justify-content: space-between;

	.header-title {
		width: var(--sample-menu-width);
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
		font-size: 18px;
		color: #f8f8f8;
		flex: 1;
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		gap: 10px;
	}
}

.content-row {
	height: calc(100vh - var(--sample-header-height));
	display: flex;
	flex-direction: row;

	.el-menu {
		border: 0;
		width: var(--sample-menu-width);
		height: 100%;
		overflow: auto;
	}

	.el-menu--collapse {
		width: calc(var(--el-menu-icon-width) + var(--el-menu-base-level-padding) * 2);
	}

	.main {
		flex: 1;
		padding: 10px;
		background-color: #edecec;
		width: calc(100vw - var(--sample-menu-width));
		height: 100%;
		overflow: auto;
	}
}
</style>

<script setup lang="ts">
import { reactive, ref, watch } from "vue";
import { useRoute } from "vue-router";
// 默认激活菜单
const activeIndex = ref("/sample/file");
// 监听路由地址改变
const route = useRoute();
watch(
	() => route.path,
	async (newpath) => {
		activeIndex.value = newpath;
	},
);
// 应用名称
const appName = import.meta.env.VITE_APP_TITLE;
// 菜单是是否折叠
const isCollapse = ref(false);
// 演示菜单数据，添加新的演示在这里不从数据即可 path代表路由地址 text代表提示文本
const menus = reactive([
	{
		id: 1,
		path: "/sample/file",
		text: "文件上传",
	},
	{
		id: 2,
		path: "/sample/excel",
		text: "Excel演示",
	},
	{
		id: 3,
		path: "/sample/print",
		text: "打印演示",
	},
	{
		id: 4,
		path: "/sample/editor",
		text: "富文本框演示",
	},
	{
		id: 5,
		path: "/sample/pdfobject",
		text: "PDF预览演示",
	},
	{
		id: 6,
		path: "/sample/echarts",
		text: "图表演示",
	},
	{
		id: 7,
		path: "/sample/formcreate",
		text: "可视化表单演示",
	},
	{
		id: 8,
		text: "流程图",
		children: [
			{
				id: 801,
				path: "/sample/flow",
				text: "流程设计示例",
			},
			{
				id: 802,
				path: "/sample/flowm",
				text: "流程管理示例",
			},
		],
	},
	{
		id: 9,
		path: "/sample/mytable",
		text: "自定义表格",
	},
	{
		id: 10,
		path: "/sample/myform",
		text: "自定义表单",
	},
	{
		id: 11,
		path: "/sample/mysearch",
		text: "自定义搜索",
	},
	{
		id: 12,
		path: "/sample/mydialog",
		text: "自定义对话框",
	},
	{
		id: 13,
		path: "/sample/mycalendar",
		text: "课程表(预约管理)",
	},
	{
		id: 123,
		path: "/sample/f1table",
		text: "F1自定义表格",
	},
	{
		id: 13,
		path: "/sample/mydetaildialog",
		text: "课时详情对话框",
	},
	{
		id: 13,
		path: "/sample/statistics",
		text: "统计数据(控制台)",
	},
	{
		id: 14,
		path: "/sample/pagination",
		text: "分页",
	},
	{
		id: 15,
		path: "/sample/myselector",
		text: "人员选择器",
	},
	{
		id: 16,
		path: "/sample/mynav",
		text: "导航组件示例",
	},
	{
		id: 17,
		path: "/sample/reicon",
		text: "ReIcon 图标方案",
	},
	{
		id: 15,
		path: "/sample/attendanceManagement",
		text: "弹窗点名管理",
	},

]);
</script>
