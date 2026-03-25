import type { Menu, Oauth2TokenDTO, UserInfo } from "@/apis/login/type";
import { DataUpType, useHttp } from "@/plugins/http";
import { defineStore } from "pinia";

// 前端临时补充的菜单项，用于在正式管理端左侧展示这 5 个页面。
// 图标统一改成 iconify 风格字符串，便于和后端存储格式保持一致。
const tempMenus: Array<Menu> = [
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

// 合并后端菜单与前端临时菜单，尽量复用已有“财务/数据”分组。
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
		// 指示登录后需要加载的初始化数据是否完成
		loaded: false,
		// 保存当前用户
		user: null as UserInfo | null,
		// 菜单数据
		menus: [] as Array<Menu>,
	}),
	getters: {
		// 获取 token
		getToken: (state) => state.token || localStorage.getItem("token"),
		// 是否加载完成
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
			const data = await useHttp().get<Array<Menu>>("/login/get-menus");
			this.menus = mergeMenus(data.data || []);
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
