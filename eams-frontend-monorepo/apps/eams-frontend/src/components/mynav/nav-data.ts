import type { EamsNavItem } from "./types";

export const eamsNavItems: EamsNavItem[] = [
	{
		key: "student",
		label: "学员",
		icon: "IconUser",
		children: [
			{ key: "student-lesson-summary", label: "课时汇总", path: "/student/lesson-summary" },
			{ key: "student-graduated", label: "结业", path: "/student/graduated" },
			{ key: "student-intention", label: "意向", path: "/student/intention" },
			{ key: "student-studying", label: "在学", path: "/student/studying" },
			{ key: "student-enrolled", label: "报名", path: "/student/enrolled" },
		],
	},
	{
		key: "edu",
		label: "教务",
		icon: "IconTickets",
		children: [
			{ key: "edu-schedule", label: "排课", path: "/edu/schedule" },
			{ key: "edu-appointment", label: "预约", path: "/edu/appointment" },
			{ key: "edu-class", label: "班级", path: "/edu/class" },
			{ key: "edu-classroom", label: "教室", path: "/edu/classroom" },
			{ key: "edu-grade", label: "年级", path: "/edu/grade" },
			{ key: "edu-timetable", label: "课程表", path: "/edu/timetable" },
			{ key: "edu-leave", label: "学员请假", path: "/edu/leave" },
		],
	},
	{
		key: "course",
		label: "课程",
		icon: "IconMenu",
		children: [
			{ key: "course-manage", label: "课程管理", path: "/course/manage" },
			{ key: "course-subject", label: "科目管理", path: "/course/subject" },
		],
	},
	{
		key: "ops",
		label: "运营",
		icon: "IconOperation",
		children: [{ key: "ops-homework", label: "课后作业", path: "/ops/homework" }],
	},
	{
		key: "material",
		label: "物料",
		icon: "IconUpload",
		children: [{ key: "material-peer-review", label: "交评学", path: "/material/peer-review" }],
	},
	{
		key: "interaction",
		label: "互动",
		icon: "IconMessage",
		children: [{ key: "interaction-teacher-review", label: "学评教", path: "/interaction/teacher-review" }],
	},
	{
		key: "finance",
		label: "财务",
		icon: "IconMoreFilled",
		children: [{ key: "finance-report", label: "成绩单", path: "/finance/report" }],
	},
	{
		key: "data",
		label: "数据",
		icon: "IconSearch",
		path: "/data",
	},
	{
		key: "org",
		label: "组织",
		icon: "IconFinished",
		path: "/org",
	},
	{
		key: "system",
		label: "系统",
		icon: "IconSetting",
		path: "/system",
	},
];
