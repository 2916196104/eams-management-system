const routes = [
	{
		path: "/notice",
		name: "system-notice",
		meta: {
			label: "内部公告",
		},
		component: () => import("@/views/system/system-notice.vue"),
	},
	{
		path: "/system/parameter",
		name: "system-parameter",
		meta: {
			label: "系统参数",
		},
		component: () => import("@/views/system/system-parameter.vue"),
	},
	{
		path: "/system/permission",
		name: "role-permission",
		meta: {
			label: "角色与权限",
		},
		component: () => import("@/views/system/role-permission.vue"),
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
	{
		path: "/system/holiday-manage",
		name: "SystemHolidayManage",
		meta: {
			label: "节假日管理",
		},
		component: () => import("@/views/system/HolidayManage.vue"),
	},
	{
		path: "/system/operation-log",
		name: "SystemOperationLog",
		meta: {
			label: "操作日志",
		},
		component: () => import("@/views/system/OperationLog.vue"),
	},
];

export default routes;
