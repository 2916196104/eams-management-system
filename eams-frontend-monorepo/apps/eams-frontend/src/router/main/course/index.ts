// router/main/course/index.ts
import type { RouteRecordRaw } from "vue-router";

export default [
	{
		path: "/course/list",
		name: "CourseManagement",
		component: () => import("@/views/course/course-management/index.vue"),
		meta: {
			label: "课程管理",
			icon: "course",
		},
	},
	{
		path: "/subject/list",
		name: "SubjectManagement",
		component: () => import("@/views/course/subject-management/index.vue"),
		meta: {
			label: "科目管理",
			icon: "subject",
		},
	},
] as RouteRecordRaw[];