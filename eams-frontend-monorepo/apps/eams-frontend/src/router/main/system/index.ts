const routes = [
	{
		path: "/notice",
		name: "system-notice",
		meta: {
			label: "系统公告",
		},
		component: () => import("@/views/system/system-notice.vue"),
	},
];

export default routes;
