const routes = [
	{
		path: "/org/employee-manage",
		name: "EmployeeManage",
		meta: {
			label: "员工管理",
		},
		component: () => import("@/views/org/employee/Index.vue"),
	},
	{
		path: "/org/salary-settings",
		name: "SalarySettings",
		meta: {
			label: "薪资设置",
		},
		component: () => import("@/views/org/salary/Index.vue"),
	},
	{
		path: "/org/org-manage",
		name: "OrgManage",
		meta: {
			label: "组织管理",
		},
		component: () => import("@/views/org/orgManage/Index.vue"),
	},
	{
		path: "/un-1",
		name: "UN1",
		meta: {
			label: "系统管理1",
		},
		component: () => import("@/views/status/404.vue"),
	},
	{
		path: "/un-2",
		name: "UN2",
		meta: {
			label: "系统管理2",
		},
		component: () => import("@/views/status/403.vue"),
	},
	{
		path: "/un-3",
		name: "UN3",
		meta: {
			label: "系统管理3",
		},
		component: () => import("@/views/status/500.vue"),
	},
	{
		path: "/un-4",
		name: "UN4",
		meta: {
			label: "系统管理4",
		},
		component: () => import("@/views/status/403.vue"),
	},
	{
		path: "/un-5",
		name: "UN5",
		meta: {
			label: "系统管理5",
		},
		component: () => import("@/views/status/404.vue"),
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
