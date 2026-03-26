export interface SystemMenuItem {
	label: string;
	path: string;
	disabled?: boolean;
}

export const systemMenuItems: SystemMenuItem[] = [
	{ label: "内部公告", path: "/system/internal-announcement" },
	{ label: "系统参数", path: "/system/system-parameter" },
	{ label: "角色与权限", path: "/system/role-permission" },
	{ label: "数据字典", path: "/system/data-dictionary" },
	{ label: "通知设置", path: "/system/notification-setting" },
	{ label: "公众号菜单", path: "/system/disabled/mp-menu", disabled: true },
	{ label: "节假日管理", path: "/system/disabled/holiday", disabled: true },
	{ label: "操作日志", path: "/system/disabled/log", disabled: true },
];
