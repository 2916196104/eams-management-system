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
		component: () => import("@/views/data/student-statistics/Index.vue"),
	},
	{
		path: "/data/teaching-statistics",
		name: "TeachingStatistics",
		meta: {
			label: "授课统计",
		},
		component: () => import("@/views/data/teaching-statistics/Index.vue"),
	},
];

export default routes;

