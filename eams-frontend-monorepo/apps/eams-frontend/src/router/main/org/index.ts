const routes = [
	{
		path: "/org",
		name: "OrgRoot",
		redirect: { path: "/org/employee-manage" },
	},
	{
		path: "/teacher/position",
		name: "TeacherPositionManage",
		meta: {
			label: "职位管理",
		},
		component: () => import("@/views/teacher/position/Index.vue"),
	},
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
			label: "机构管理",
		},
		component: () => import("@/views/org/org-manage/Index.vue"),
	},
];

export default routes;

