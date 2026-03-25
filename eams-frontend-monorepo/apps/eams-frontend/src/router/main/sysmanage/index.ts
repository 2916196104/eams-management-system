const routes = [
	{
		path: "/un-1",
		name: "UN1",
		meta: {
			label: "内部公告",
		},
		redirect: { name: "SystemInternalAnnouncement" },
	},
	{
		path: "/un-2",
		name: "UN2",
		meta: {
			label: "系统参数",
		},
		redirect: { name: "SystemParameter" },
	},
	{
		path: "/un-3",
		name: "UN3",
		meta: {
			label: "角色与权限",
		},
		redirect: { name: "SystemRolePermission" },
	},
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
