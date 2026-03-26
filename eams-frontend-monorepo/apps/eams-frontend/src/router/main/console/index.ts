const routes = [
	{
		path: "/index",
		name: "index",
		meta: {
			label: "首页",
		},
		component: () => import("@/views/console/index/Index.vue"),
	},
	{
		path: "/curriculum",
		name: "curriculum",
		meta: {
			label: "我的课表",
		},
		component: () => import("@/views/console/curriculum/Curriculum.vue"),
	},
	{
		path: "/client",
		name: "client",
		meta: {
			label: "我的客户",
		},
		component: () => import("@/views/console/client/Client.vue"),
	},
	{
		path: "/signup",
		name: "signup",
		meta: {
			label: "我的报名",
		},
		component: () => import("@/views/console/signup/Signup.vue"),
	},
	{
		path: "/payment",
		name: "payment",
		meta: {
			label: "我的请款",
		},
		component: () => import("@/views/console/payment/Payment.vue"),
	},
	{
		path: "/follow",
		name: "follow",
		meta: {
			label: "我的跟进",
		},
		component: () => import("@/views/console/follow/Follow.vue"),
	},
	{
		path: "/student/online",
		name: "studentOnline",
		meta: {
			label: "在学学员",
		},
		component: () => import("@/views/console/student/OnlineStudents.vue"),
	},
	{
		path: "/student/detail",
		name: "studentDetail",
		meta: {
			label: "学员详情",
		},
		component: () => import("@/views/console/student/StudentDetail.vue"),
	},
	{
		path: "/student/intention",
		name: "studentIntention",
		meta: { label: "意向学员" },
		component: () => import("@/views/console/student/IntentionStudents.vue"),
	},
	{
		path: "/student/graduated",
		name: "studentGraduated",
		meta: { label: "结业学员" },
		component: () => import("@/views/console/student/GraduatedStudents.vue"),
	},
	{
		path: "/student/parent-accounts",
		name: "studentParentAccounts",
		meta: { label: "家长账号" },
		component: () => import("@/views/console/student/ParentAccounts.vue"),
	},
	{
		path: "/student/lesson-progress",
		name: "studentLessonProgress",
		meta: { label: "课时进度" },
		component: () => import("@/views/console/student/StudentModulePlaceholder.vue"),
	},
	{
		path: "/student/lesson-summary",
		name: "studentLessonSummary",
		meta: { label: "课时汇总" },
		component: () => import("@/views/console/student/StudentModulePlaceholder.vue"),
	},
	{
		path: "/student/enrollment-records",
		name: "studentEnrollmentRecords",
		meta: { label: "报名记录" },
		component: () => import("@/views/console/signup/Signup.vue"),
	},
	{
		path: "/student/follow-records",
		name: "studentFollowRecords",
		meta: { label: "跟进记录" },
		component: () => import("@/views/console/follow/Follow.vue"),
	},
];

export default routes;
