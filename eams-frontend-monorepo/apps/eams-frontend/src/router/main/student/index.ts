const routes = [
	{
		path: "/student/classSummary",
		name: "classSummary",
		meta: {
			label: "课时汇总",
		},
		component: () => import("@/views/student/ClassSummary.vue"),
	},
	{
		path: "/student/signupRecord",
		name: "signupRecord",
		meta: {
			label: "报名记录",
		},
		component: () => import("@/views/student/SignupRecord.vue"),
	},
	{
		path: "/student/followRecord",
		name: "followRecord",
		meta: {
			label: "跟进记录",
		},
		component: () => import("@/views/student/FollowRecord.vue"),
	},
];

export default routes;
