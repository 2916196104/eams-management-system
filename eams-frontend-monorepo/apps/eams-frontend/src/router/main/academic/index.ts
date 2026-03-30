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
    path: "/academic/studentLeave",
    name: "studentLeave",
    meta: {
      label: "学员请假",
    },
    component: () => import("@/views/academic/StudentLeave.vue"),
  },
  {
    path: '/academic/schedule-plan',
    name: 'schedule-plan',
    component: () => import('@/views/academic/schedule-plan/index.vue'),
    meta: { title: '排课计划', label: '排课计划' },
  },
  {
    path: '/academic/appointment',
    name: 'appointment',
    component: () => import('@/views/academic/appointment/index.vue'),
    meta: { title: '预约管理', label: '预约管理' },
  },
  {
    path: '/academic/class',
    name: 'class',
    component: () => import('@/views/academic/class/index.vue'),
    meta: { title: '班级管理', label: '班级管理' },
  },
  {
    path: '/academic/classroom',
    name: 'classroom',
    component: () => import('@/views/academic/classroom/index.vue'),
    meta: { title: '教室管理', label: '教室管理' },
  },
  {
    path: '/academic/grade',
    name: 'grade',
    component: () => import('@/views/academic/grade/index.vue'),
    meta: { title: '年级管理', label: '年级管理' },
  },
	{
		path: "/academic/schedule-calendar",
		name: "scheduleCalendar",
		meta: {
			label: "课表日历",
		},
		component: () => import("@/views/academic/ScheduleCalendar.vue"),
	},
];

export default routes;
