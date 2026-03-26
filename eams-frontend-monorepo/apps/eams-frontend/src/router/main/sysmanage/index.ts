const routes = [
	{
		path: "/un-4",
		name: "UN4",
		meta: {
			label: "数据字典",
		},
		redirect: { name: "SystemDataDictionary" },
	},
	{
		path: "/un-5",
		name: "UN5",
		meta: {
			label: "通知设置",
		},
		redirect: { name: "SystemNotificationSetting" },
	},
	{
		path: "/un-6",
		name: "UN6",
		meta: {
			label: "系统管理6",
		},
		component: () => import("@/views/status/500.vue"),
	},
];

export default routes;
