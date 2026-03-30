import type { Menu, Oauth2TokenDTO, UserInfo } from "@/apis/login/type";
import { mergeStudentMenuBranch } from "@/config/studentMenuMerge";
import { DataUpType, useHttp } from "@/plugins/http";
import { defineStore } from "pinia";

// 前端临时补充的菜单项，用于在正式管理端左侧展示当前已经完成的菜单入口。
// 图标统一使用 iconify 风格字符串，便于和后端后续菜单数据保持一致。
const tempMenus: Array<Menu> = [
	{
		id: "temp-dashboard",
		text: "工作台",
		icon: "ep/home-filled",
		children: [
			{
				id: "temp-dashboard-overview",
				text: "首页概览",
				icon: "ep/monitor",
				href: "/dashboard",
			},
		],
	},
	{
		id: "temp-console",
		text: "控制台",
		icon: "ep/office-building",
		children: [
			{
				id: "temp-console-index",
				text: "首页",
				icon: "ep/house",
				href: "/index",
			},
			{
				id: "temp-console-curriculum",
				text: "我的课表",
				icon: "ep/calendar",
				href: "/curriculum",
			},
			{
				id: "temp-console-client",
				text: "我的客户",
				icon: "ep/user",
				href: "/client",
			},
			{
				id: "temp-console-signup",
				text: "我的报名",
				icon: "ep/tickets",
				href: "/signup",
			},
			{
				id: "temp-console-payment",
				text: "我的请款",
				icon: "ep/money",
				href: "/payment",
			},
			{
				id: "temp-console-follow",
				text: "我的跟进",
				icon: "ep/flag",
				href: "/follow",
			},
		],
	},
	{
		id: "temp-student",
		text: "学员",
		icon: "ep/user",
		children: [
			{
				id: "temp-student-class-summary",
				text: "课时汇总",
				icon: "ep/histogram",
				href: "/student/classSummary",
			},
			{
				id: "temp-student-signup-record",
				text: "报名记录",
				icon: "ep/tickets",
				href: "/student/signupRecord",
			},
			{
				id: "temp-student-follow-record",
				text: "跟进记录",
				icon: "ep/flag",
				href: "/student/followRecord",
			},
		],
	},
	{
		id: "temp-academic",
		text: "教务",
		icon: "ep/calendar",
		children: [
			{
				id: "temp-academic-class",
				text: "班级管理",
				icon: "ep/user-filled",
				href: "/academic/class",
			},
			{
				id: "temp-academic-classroom",
				text: "教室管理",
				icon: "ep/office-building",
				href: "/academic/classroom",
			},
			{
				id: "temp-academic-grade",
				text: "年级管理",
				icon: "ep/medal",
				href: "/academic/grade",
			},
			{
				id: "temp-academic-schedule-plan",
				text: "排课计划",
				icon: "ep/date",
				href: "/academic/schedule-plan",
			},
			{
				id: "temp-academic-appointment",
				text: "预约管理",
				icon: "ep/clock",
				href: "/academic/appointment",
			},
			{
				id: "temp-academic-schedule",
				text: "课程表",
				icon: "ep/calendar",
				href: "/academic/schedule",
			},
			{
				id: "temp-academic-student-leave",
				text: "学员请假",
				icon: "ep/document-checked",
				href: "/academic/studentLeave",
			},
		],
	},
	{
		id: "temp-finance",
		text: "财务",
		icon: "ep/wallet-filled",
		children: [
			{
				id: "temp-finance-payment-management",
				text: "款项管理",
				icon: "ep/credit-card",
				href: "/finance/paymentManagement",
			},
			{
				id: "temp-finance-finance-record",
				text: "月课时费",
				icon: "ep/calendar",
				href: "/finance/financeRecord",
			},
			{
				id: "temp-finance-course-reward",
				text: "消课课酬",
				icon: "ep/coin",
				href: "/finance/courseReward",
			},
			{
				id: "temp-finance-request-management",
				text: "请款管理",
				icon: "ep/document-checked",
				href: "/finance/requestManagement",
			},
		],
	},
	{
		id: "temp-data",
		text: "数据",
		icon: "ep/data-analysis",
		children: [
			{
				id: "temp-data-sale-stats",
				text: "销售统计",
				icon: "ep/trend-charts",
				href: "/statis/saleStatis",
			},
		],
	},
	{
		id: "temp-interaction",
		text: "互动",
		icon: "ep/cherry",
		children: [
			{
				id: "temp-interaction-homework",
				text: "课后作业",
				icon: "ep/notebook",
				href: "/interaction/homework",
			},
			{
				id: "temp-interaction-teaching-evaluation",
				text: "教评学",
				icon: "ep/edit-pen",
				href: "/interaction/teaching-evaluation",
			},
			{
				id: "temp-interaction-learning-evaluation",
				text: "学评教",
				icon: "ep/opportunity",
				href: "/interaction/learning-evaluation",
			},
			{
				id: "temp-interaction-transcript",
				text: "成绩单",
				icon: "ep/trophy",
				href: "/interaction/transcript",
			},
			{
				id: "temp-interaction-announcement-management",
				text: "公告管理",
				icon: "ep/broadcast",
				href: "/interaction/announcement-management",
			},
		],
	},
	{
		id: "temp-system",
		text: "系统",
		icon: "ep/setting",
		children: [
			{
				id: "temp-system-notice",
				text: "系统公告",
				icon: "ep/setting",
				href: "/notice",
			},
		],
	},
];

// 深拷贝菜单，避免直接修改后端返回的原始数据。
function cloneMenu(menu: Menu): Menu {
	return {
		...menu,
		children: (menu.children || []).map(cloneMenu),
	};
}

// 合并后端菜单与前端临时菜单，尽量复用已有分组。
function mergeMenus(sourceMenus: Array<Menu> = []) {
	const menus = sourceMenus.map(cloneMenu);

	for (const tempGroup of tempMenus) {
		const currentGroup = menus.find((item) => item.text === tempGroup.text);
		if (!currentGroup) {
			menus.push(cloneMenu(tempGroup));
			continue;
		}

		const currentChildren = currentGroup.children || [];
		for (const tempChild of tempGroup.children || []) {
			const exists = currentChildren.some((item) => item.href === tempChild.href || item.text === tempChild.text);
			if (!exists) currentChildren.push(cloneMenu(tempChild));
		}
		currentGroup.children = currentChildren;
	}

	return menus;
}

export const useUserStore = defineStore("user", {
	state: () => ({
		// 记录 token
		token: null as string | null,
		// 记录 refreshToken
		refreshToken: null as string | null,
		// 保存一个标识信息，指示登录后需要加载的初始化数据是否完成
		loaded: false,
		// 保存当前用户
		user: null as UserInfo | null,
		// 菜单数据
		menus: [] as Array<Menu>,
	}),
	getters: {
		// 获取 token
		getToken: (state) => state.token || localStorage.getItem("token"),
		// 是否已加载
		isLoaded: (state) => state.loaded,
		// 获取当前用户
		getUser: (state) => state.user,
		// 获取菜单
		getMenus: (state) => state.menus,
	},
	actions: {
		// 加载用户
		async loadUser() {
			const data = await useHttp().get<UserInfo>("/login/current-user");
			if (data.data) this.user = data.data;
			if (!this.user?.avatar) {
				this.user = {
					avatar: "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
					...this.user,
				} as UserInfo;
			}
		},
		// 加载菜单
		async loadMenus() {
			try {
				const data = await useHttp().get<Array<Menu>>("/login/get-menus");
				const raw = Array.isArray(data.data) ? data.data : [];

				// 关键约束：这里必须先执行 mergeMenus(raw)，再执行 mergeStudentMenuBranch(...)。
				// mergeMenus(...) 负责恢复前端本地补充菜单，包括原来的 5 个页面和后续补充的菜单入口。
				// 如果直接把 raw 交给 mergeStudentMenuBranch(...)，这些菜单会从左侧栏里消失。
				// 这条注释是留给后续维护者和组员 AI 看的，不要调整这两个步骤的先后顺序。
				this.menus = mergeStudentMenuBranch(mergeMenus(raw));
			} catch {
				// 接口失败时也要保持同样的合并顺序，确保本地补充菜单和 student/follow 兜底入口仍然显示在侧边栏。
				this.menus = mergeStudentMenuBranch(mergeMenus([]));
			}
		},
		// 加载刷新凭证
		loadRefreshToken() {
			if (!this.refreshToken) this.refreshToken = localStorage.getItem("refreshToken");
		},
		// 刷新 token
		async reloadToken() {
			this.loadRefreshToken();
			const data = await useHttp().post<Oauth2TokenDTO>(
				"/login/refresh-token",
				{
					refreshToken: this.refreshToken,
					token: this.token,
				},
				{
					upType: DataUpType.form,
				},
			);
			this.setToken(data.data);
		},
		// 设置是否加载完成
		setLoaded(loaded: boolean) {
			this.loaded = loaded;
		},
		// 设置 token
		setToken(data: any) {
			this.token = data.token;
			this.refreshToken = data.refreshToken;
			if (this.token) localStorage.setItem("token", this.token);
			if (this.refreshToken) localStorage.setItem("refreshToken", this.refreshToken);
		},
		// 重置数据
		resetSaveData() {
			this.loaded = false;
			this.user = null;
			this.token = null;
			this.refreshToken = null;
			localStorage.removeItem("token");
			localStorage.removeItem("refreshToken");
		},
	},
});
