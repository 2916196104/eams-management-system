const routes = [
	{
		path: "/interaction/homework",
		name: "InteractionHomework",
		meta: {
			label: "课后作业",
		},
		component: () => import("@/views/interaction/Homework.vue"),
	},
	{
		path: "/interaction/teaching-evaluation",
		name: "InteractionTeachingEvaluation",
		meta: {
			label: "教评学",
		},
		component: () => import("@/views/interaction/TeachingEvaluation.vue"),
	},
	{
		path: "/interaction/learning-evaluation",
		name: "InteractionLearningEvaluation",
		meta: {
			label: "学评教",
		},
		component: () => import("@/views/interaction/LearningEvaluation.vue"),
	},
	{
		path: "/interaction/transcript",
		name: "InteractionTranscript",
		meta: {
			label: "成绩单",
		},
		component: () => import("@/views/interaction/Transcript.vue"),
	},
	{
		path: "/interaction/announcement-management",
		name: "InteractionAnnouncementManagement",
		meta: {
			label: "公告管理",
		},
		component: () => import("@/views/interaction/AnnouncementManagement.vue"),
	},
];

export default routes;
