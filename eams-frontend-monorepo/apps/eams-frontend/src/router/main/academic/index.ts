const routes = [
	{
		path: "/academic/schedule",
		name: "schedule",
		meta: {
			label: "课程表",
		},
		component: () => import("@/views/academic/Schedule.vue"),
	},
	{
		path: "/academic/schedule-calendar",
		name: "scheduleCalendar",
		meta: {
			label: "课表日历",
		},
		component: () => import("@/views/academic/ScheduleCalendar.vue"),
	},
	{
		path: "/academic/studentLeave",
		name: "studentLeave",
		meta: {
			label: "学员请假",
		},
		component: () => import("@/views/academic/StudentLeave.vue"),
	},
];

export default routes;
