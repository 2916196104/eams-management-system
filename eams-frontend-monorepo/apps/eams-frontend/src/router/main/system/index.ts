const routes = [
	{
		path: "/system",
		redirect: { name: "SystemDataDictionary" },
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
