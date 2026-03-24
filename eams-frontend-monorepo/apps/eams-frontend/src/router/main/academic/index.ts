const routes = [
	{
		path: "/academic/studentLeave",
		name: "studentLeave",
		meta: {
			label: "学员请假",
		},
		component: () => import("@/views/academic/StudentLeave.vue"),
	},
];

export default routes;
