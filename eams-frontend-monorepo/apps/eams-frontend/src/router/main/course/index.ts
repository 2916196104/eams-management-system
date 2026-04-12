// router/main/course/index.ts
import type { RouteRecordRaw } from "vue-router";

export default [
	{
		path: "course/list", //  改成了 course/list

		name: "CourseManagement",
		component: () => import("@/views/course/course-management/index.vue"),
		meta: {
			label: "课程管理",
			icon: "course",
		},
	},
	{
		path: "subject/list", // 改成了 subject/list（注意不是 /course/xxx
		name: "SubjectManagement",
		component: () => import("@/views/course/subject-management/index.vue"),
		meta: {
			label: "科目管理",
			icon: "subject",
		},
	},
] as RouteRecordRaw[];
