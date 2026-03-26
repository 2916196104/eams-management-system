const routes = [
	{
		path: "/system",
		redirect: { name: "SystemInternalAnnouncement" },
	},
	{
		path: "/system/internal-announcement",
		name: "SystemInternalAnnouncement",
		meta: {
			label: "内部公告",
		},
		component: () => import("@/views/system/InternalAnnouncement.vue"),
	},
	{
		path: "/system/system-parameter",
		name: "SystemParameter",
		meta: {
			label: "系统参数",
		},
		component: () => import("@/views/system/SystemParameter.vue"),
	},
	{
		path: "/system/role-permission",
		name: "SystemRolePermission",
		meta: {
			label: "角色与权限",
		},
		component: () => import("@/views/system/RolePermission.vue"),
	},
	{
		path: "/system/data-dictionary",
		name: "SystemDataDictionary",
		meta: {
			label: "数据字典",
		},
		component: () => import("@/views/system/DataDictionary.vue"),
	},
	{
		path: "/system/notification-setting",
		name: "SystemNotificationSetting",
		meta: {
			label: "通知设置",
		},
		component: () => import("@/views/system/NotificationSetting.vue"),
	},
];

export default routes;
