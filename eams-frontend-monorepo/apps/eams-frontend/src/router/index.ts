import { createRouter, createWebHistory } from "vue-router";
import { ElMessage } from "element-plus";
import { useUserStore } from "../stores/user";
import { useTabStore } from "@/stores/tab";
import type { RouteRecordRawArray } from "@/types/Route";

const routes = [];
routes.push(
	{
		path: "/:pathMatch(.*)*",
		name: "NotFound",
		component: () => import("../views/status/404.vue"),
	},
	{
		path: "/forbidden",
		name: "Forbidden",
		component: () => import("../views/status/403.vue"),
	},
	{
		path: "/error",
		name: "Error",
		component: () => import("../views/status/500.vue"),
	},
	{
  path: '/test-editable-form',
  name: 'EditableFormTest',
  component: () => import('../views/test/EditableFormTest.vue'),
  meta: {
    title: '可修改表单测试'
  }
}
);

// 读取login模块路由
const loginRouter = import.meta.glob<RouteRecordRawArray>("./login/index.ts", { eager: true });
for (const path in loginRouter) {
	routes.push(...loginRouter[path].default);
}

// 读取main模块路由
const mainRouter = import.meta.glob<RouteRecordRawArray>("./main/index.ts", { eager: true });
for (const path in mainRouter) {
	routes.push(...mainRouter[path].default);
}

// 读取示例演示模块路由
if (import.meta.env.DEV) {
	const sampleRouter = import.meta.glob<RouteRecordRawArray>("./sample/index.ts", { eager: true });
	for (const path in sampleRouter) {
		routes.push(...sampleRouter[path].default);
	}
}

// 定义一个路由对象
const router = createRouter({
	history: createWebHistory(import.meta.env.BASE_URL),
	routes,
});

// 全局前置守卫（Vue Router 4：用 return 替代 next()，避免弃用警告）
router.beforeEach(async (to) => {
	// 判断是否是白名单页面
	if (to.name === "Login" || to.name === "NotFound" || to.name === "Forbidden" || to.name === "Error") {
		return true;
	}

	// 放行示例模块访问
	if (import.meta.env.DEV && to.path.includes("sample")) {
		return true;
	}

	const store = useUserStore();
	const token = store.getToken;
	if (token) {
		if (!store.isLoaded) {
			await store.loadUser();
			await store.loadMenus();
			store.setLoaded(true);
		}

		const tabstore = useTabStore();
		if (to.path === tabstore.indexPath) {
			tabstore.setActiveIndex(to.path);
		} else if (to.meta.label) {
			const idx = tabstore.getTabIndex(to.path);
			if (idx !== -1) {
				tabstore.setActiveIndex(to.path);
			} else {
				tabstore.addTab({
					label: to.meta.label as string,
					path: to.path,
				});
				tabstore.setActiveIndex(to.path);
			}
		}

		return true;
	}

	ElMessage.warning("在未登录时，禁止访问其他页面！");
	return { name: "Login" };
});

export default router;
