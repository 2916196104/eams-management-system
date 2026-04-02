const routes = [
	{
		path: "/course/manage",
		name: "CourseManage",
		component: () => import("@/views/course/course-management/index.vue"),
	},
	{
		path: "/course/subject",
		name: "CourseSubject",
		component: () => import("@/views/course/subject-management/index.vue"),
	},
];

export default routes;
