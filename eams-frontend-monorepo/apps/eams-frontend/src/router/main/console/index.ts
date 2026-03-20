const routes = [
	{
		path: "/index",
		name: "index",
		meta: {
			label: "首页",
		},
		component: () => import("@/views/status/404.vue"),
	},
	{
		path: "/curriculum",
		name: "curriculum",
		meta: {
			label: "我的课表",
		},
		component: () => import("@/views/status/403.vue"),
	},
	{
		path: "/client",
		name: "client",
		meta: {
			label: "我的客户",
		},
		component: () => import("@/views/status/500.vue"),
	},
	{
		path: "/signup",
		name: "signup",
		meta: {
			label: "我的报名",
		},
		component: () => import("@/views/status/403.vue"),
	},
	{
		path: "/payment",
		name: "payment",
		meta: {
			label: "我的请款",
		},
		component: () => import("@/views/status/404.vue"),
	},
	{
		path: "/follow",
		name: "follow",
		meta: {
			label: "我的跟进",
		},
		component: () => import("@/views/status/500.vue"),
	},
];

export default routes;
