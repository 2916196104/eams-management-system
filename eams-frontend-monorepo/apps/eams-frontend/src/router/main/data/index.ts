const routes = [
	{
		path: "/data",
		name: "DataRoot",
		redirect: { path: "/data/student-statistics" },
	},
	{
		path: "/data/student-statistics",
		name: "StudentStatistics",
		meta: {
			label: "学员统计",
		},
		component: () => import("@/views/data/studentStatistics/Index.vue"),
	},
	{
		path: "/data/teaching-statistics",
		name: "TeachingStatistics",
		meta: {
			label: "授课统计",
		},
		component: () => import("@/views/data/teachingStatistics/Index.vue"),
	},
];

export default routes;

