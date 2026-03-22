const routes = [
	{
		path: "/class-summary",
		name: "classSummary",
		meta: {
			label: "课时汇总",
		},
		component: () => import("@/views/student/ClassSummary.vue"),
	},
	{
		path: "/signup-record",
		name: "signupRecord",
		meta: {
			label: "报名记录",
		},
		component: () => import("@/views/student/SignupRecord.vue"),
	},
	{
		path: "/follow-record",
		name: "followRecord",
		meta: {
			label: "跟进记录",
		},
		component: () => import("@/views/student/FollowRecord.vue"),
	},
];

export default routes;
