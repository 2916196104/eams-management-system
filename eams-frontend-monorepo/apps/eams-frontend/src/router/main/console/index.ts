const routes = [
	{
		path: "/index",
		name: "ConsoleIndex",
		meta: {
			label: "控制台",
		},
		component: () => import("@/views/console/index/Index.vue"),
	},
	{
		path: "/curriculum",
		name: "ConsoleCurriculum",
		meta: {
			label: "我的课表",
		},
		component: () => import("@/views/console/curriculum/Curriculum.vue"),
	},
	{
		path: "/client",
		name: "ConsoleClient",
		meta: {
			label: "我的客户",
		},
		component: () => import("@/views/console/client/Client.vue"),
	},
	{
		path: "/signup",
		name: "ConsoleSignup",
		meta: {
			label: "我的报名",
		},
		component: () => import("@/views/console/signup/Signup.vue"),
	},
	{
		path: "/payment",
		name: "ConsolePayment",
		meta: {
			label: "我的请款",
		},
		component: () => import("@/views/console/payment/Payment.vue"),
	},
	{
		path: "/follow",
		name: "ConsoleFollow",
		meta: {
			label: "我的跟进",
		},
		component: () => import("@/views/console/follow/Follow.vue"),
	},
	{
		path: "/student/online",
		name: "StudentOnline",
		meta: {
			label: "在学学员",
		},
		component: () => import("@/views/console/student/OnlineStudents.vue"),
	},
	{
		path: "/student/detail",
		name: "StudentDetail",
		meta: {
			label: "学员详情",
		},
		component: () => import("@/views/console/student/StudentDetail.vue"),
	},
	{
		path: "/student/intention",
		name: "StudentIntention",
		meta: {
			label: "意向学员",
		},
		component: () => import("@/views/console/student/IntentionStudents.vue"),
	},
	{
		path: "/student/graduated",
		name: "StudentGraduated",
		meta: {
			label: "结业学员",
		},
		component: () => import("@/views/console/student/GraduatedStudents.vue"),
	},
	{
		path: "/student/parent-accounts",
		name: "StudentParentAccounts",
		meta: {
			label: "家长账号",
		},
		component: () => import("@/views/console/student/ParentAccounts.vue"),
	},
	{
		path: "/student/lesson-progress",
		name: "StudentLessonProgress",
		meta: {
			label: "课时进度",
		},
		component: () => import("@/views/console/student/StudentModulePlaceholder.vue"),
	},
	// 下面三个旧地址只做兼容跳转，真正的页面标题、tab 名称和后续维护都统一收口到 student 模块路由里。
	// 这里故意不再重复维护 meta，避免同一页面出现两份 label 来源，后续改名时也漏改一处。
	{
		path: "/student/lesson-summary",
		name: "StudentLessonSummaryLegacy",
		redirect: { name: "classSummary" },
	},
	{
		path: "/student/enrollment-records",
		name: "StudentEnrollmentRecordsLegacy",
		redirect: { name: "signupRecord" },
	},
	{
		path: "/student/follow-records",
		name: "StudentFollowRecordsLegacy",
		redirect: { name: "followRecord" },
	},
];

export default routes;
