export interface AdminNavChild {
	id: string;
	text: string;
	path: string;
	matchPaths?: string[];
}

export interface AdminNavSection {
	id: string;
	text: string;
	icon: string;
	path?: string;
	children: AdminNavChild[];
}

export const ADMIN_NAVIGATION: AdminNavSection[] = [
	{
		id: "home",
		text: "首页",
		icon: "ep/home-filled",
		path: "/dashboard",
		children: [
			{
				id: "home-dashboard",
				text: "控制台",
				path: "/dashboard",
				matchPaths: ["/index"],
			},
			{
				id: "home-curriculum",
				text: "我的课表",
				path: "/curriculum",
			},
			{
				id: "home-client",
				text: "我的客户",
				path: "/client",
			},
			{
				id: "home-signup",
				text: "我的报名",
				path: "/signup",
			},
			{
				id: "home-payment",
				text: "我的请款",
				path: "/payment",
			},
			{
				id: "home-follow",
				text: "我的跟进",
				path: "/follow",
			},
		],
	},
	{
		id: "student",
		text: "学员",
		icon: "ep/user",
		children: [
			{
				id: "student-online",
				text: "在学学员",
				path: "/student/online",
				matchPaths: ["/student/detail"],
			},
			{
				id: "student-intention",
				text: "意向学员",
				path: "/student/intention",
			},
			{
				id: "student-graduated",
				text: "结业学员",
				path: "/student/graduated",
			},
			{
				id: "student-parent",
				text: "家长账号",
				path: "/student/parent-accounts",
			},
			{
				id: "student-summary",
				text: "课时汇总",
				path: "/student/classSummary",
				matchPaths: ["/student/lesson-summary"],
			},
			{
				id: "student-signup-record",
				text: "报名记录",
				path: "/student/signupRecord",
				matchPaths: ["/student/enrollment-records"],
			},
			{
				id: "student-follow-record",
				text: "跟进记录",
				path: "/student/followRecord",
				matchPaths: ["/student/follow-records"],
			},
		],
	},
	{
		id: "academic",
		text: "教务",
		icon: "ep/calendar",
		children: [
			{
				id: "academic-schedule",
				text: "课程表",
				path: "/academic/schedule",
			},
			{
				id: "academic-leave",
				text: "学员请假",
				path: "/academic/studentLeave",
			},
			{
				id: "academic-schedule-plan",
				text: "排课计划",
				path: "/academic/schedule-plan",
			},
			{
				id: "academic-appointment",
				text: "预约管理",
				path: "/academic/appointment",
			},
			{
				id: "academic-class",
				text: "班级管理",
				path: "/academic/class",
			},
			{
				id: "academic-classroom",
				text: "教室管理",
				path: "/academic/classroom",
			},
			{
				id: "academic-grade",
				text: "年级管理",
				path: "/academic/grade",
			},
		],
	},
	{
		id: "course",
		text: "课程",
		icon: "ri/book-open-line",
		children: [
			{
				id: "course-manage",
				text: "课程管理",
				path: "/home/course/list",
			},
			{
				id: "course-subject",
				text: "科目管理",
				path: "/home/subject/list",
			},
		],
	},
	{
		id: "operations",
		text: "运营",
		icon: "ri/shopping-bag-3-line",
		children: [
			{
				id: "operations-order",
				text: "订单管理",
				path: "/ops/order-management",
			},
			{
				id: "operations-refund",
				text: "订单退款",
				path: "/ops/refund-management",
			},
			{
				id: "operations-evaluation",
				text: "订单评价",
				path: "/ops/evaluation-management",
			},
			{
				id: "operations-trialCardManagement",
				text: "体验卡管理",
				path: "/ops/trialCardManagement",
			},
			{
				id: "operations-PointsGift",
				text: "积分礼品",
				path: "/ops/pointsGift",
			},
			{
				id: "operations-PointsRedemption",
				text: "积分兑换",
				path: "/ops/pointsRedemption",
			},
			{
				id: "operations-pointsRecord",
				text: "积分记录",
				path: "/ops/pointsRecord",
			},
		],
	},
	{
		id: "material",
		text: "物料",
		icon: "ri/apps-2-line",
		children: [
			{
				id: "material-manage",
				text: "物料管理",
				path: "/material/manage",
			},
			{
				id: "material-inventory",
				text: "库存记录",
				path: "/material/inventory",
			},
		],
	},
	{
		id: "interaction",
		text: "互动",
		icon: "ri/mail-line",
		children: [
			{
				id: "interaction-homework",
				text: "课后作业",
				path: "/interaction/homework",
			},
			{
				id: "interaction-teaching-evaluation",
				text: "教评学",
				path: "/interaction/teaching-evaluation",
			},
			{
				id: "interaction-learning-evaluation",
				text: "学评教",
				path: "/interaction/learning-evaluation",
			},
			{
				id: "interaction-transcript",
				text: "成绩单",
				path: "/interaction/transcript",
			},
			{
				id: "interaction-announcement-management",
				text: "公告管理",
				path: "/interaction/announcement-management",
			},
		],
	},
	{
		id: "finance",
		text: "财务",
		icon: "ri/wallet-3-line",
		children: [
			{
				id: "finance-payment-management",
				text: "款项管理",
				path: "/finance/paymentManagement",
				matchPaths: ["/finance/payment-management"],
			},
			{
				id: "finance-record",
				text: "月课时费",
				path: "/finance/financeRecord",
				matchPaths: ["/finance/monthly-class-fee"],
			},
			{
				id: "finance-course-reward",
				text: "消课课酬",
				path: "/finance/courseReward",
				matchPaths: ["/finance/course-reward"],
			},
			{
				id: "finance-request-management",
				text: "请款管理",
				path: "/finance/requestManagement",
				matchPaths: ["/finance/request-management"],
			},
		],
	},
	{
		id: "data",
		text: "数据",
		icon: "ri/database-2-line",
		children: [
			{
				id: "data-sale-stats",
				text: "销售统计",
				path: "/statis/saleStatis",
				matchPaths: ["/statis/sale-stats"],
			},
			{
				id: "data-student-statistics",
				text: "学员统计",
				path: "/data/student-statistics",
			},
			{
				id: "data-teaching-statistics",
				text: "授课统计",
				path: "/data/teaching-statistics",
			},
		],
	},
	{
		id: "organization",
		text: "组织",
		icon: "ri/building-2-line",
		children: [
			{
				id: "organization-staff",
				text: "员工管理",
				path: "/org/employee-manage",
				matchPaths: ["/org/staff-management"],
			},
			{
				id: "organization-org",
				text: "机构管理",
				path: "/org/org-manage",
				matchPaths: ["/org/branch-management"],
			},
			{
				id: "organization-position",
				text: "职位管理",
				path: "/teacher/position",
			},
		],
	},
	{
		id: "system",
		text: "系统",
		icon: "ri/computer-line",
		children: [
			{
				id: "system-notice",
				text: "内部公告",
				path: "/system/internal-notice",
				matchPaths: ["/notice"],
			},
			{
				id: "system-parameter",
				text: "系统参数",
				path: "/system/system-parameter",
			},
			{
				id: "system-role",
				text: "角色与权限",
				path: "/system/role-permission",
			},
			{
				id: "system-data-dictionary",
				text: "数据字典",
				path: "/system/data-dictionary",
				matchPaths: ["/un-4"],
			},
			{
				id: "system-notification-setting",
				text: "通知设置",
				path: "/system/notification-setting",
				matchPaths: ["/un-5"],
			},
			{
				id: "system-holiday-manage",
				text: "节假日管理",
				path: "/system/holiday-manage",
			},
			{
				id: "system-operation-log",
				text: "操作日志",
				path: "/system/operation-log",
			},
		],
	},
];

export function navItemMatchesPath(item: AdminNavChild, path: string) {
	return item.path === path || item.matchPaths?.includes(path) === true;
}

export function findAdminNavSectionByPath(path: string) {
	return ADMIN_NAVIGATION.find(
		(section) => section.path === path || section.children.some((child) => navItemMatchesPath(child, path)),
	);
}

export function findAdminNavItemByPath(path: string) {
	for (const section of ADMIN_NAVIGATION) {
		const child = section.children.find((entry) => navItemMatchesPath(entry, path));
		if (child) return child;
	}
	return undefined;
}

export function getAdminNavSectionEntryPath(section: AdminNavSection) {
	return section.path || section.children[0]?.path || "/dashboard";
}
