const placeholderView = () => import("@/views/common/MenuPlaceholder.vue");

const routes = [
	{
		path: "/interaction/teacher-review",
		name: "InteractionTeacherReview",
		meta: {
			label: "学评教",
			description: "评价任务、评分结果和汇总分析后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/interaction/message-center",
		name: "InteractionMessageCenter",
		meta: {
			label: "站内消息",
			description: "消息中心、模板通知和已读未读状态后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/org/staff-management",
		name: "OrganizationStaffManagement",
		meta: {
			label: "员工管理",
			description: "员工档案、岗位信息和权限关系后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/org/branch-management",
		name: "OrganizationBranchManagement",
		meta: {
			label: "机构管理",
			description: "机构树、校区配置和组织关系后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/system/param",
		name: "SystemParam",
		meta: {
			label: "系统参数",
		},
		component: () => import("@/views/system/system-param.vue"),
	},
	{
		path: "/system/role-permission",
		name: "SystemRolePermission",
		meta: {
			label: "角色与权限",
			description: "角色、菜单权限和数据权限后续可继续补齐。",
		},
		component: () => import("@/views/system/system-permission.vue"),
	},
];

export default routes;
