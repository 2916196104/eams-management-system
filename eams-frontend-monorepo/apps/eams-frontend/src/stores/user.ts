import { defineStore } from "pinia";
import type { Menu, Oauth2TokenDTO, UserInfo } from "@/apis/login/type";
import { DataUpType, useHttp } from "@/plugins/http";

export const useUserStore = defineStore("user", {
	state: () => ({
		// 记录token
		token: null as string | null,
		// 记录refreshToken
		refreshToken: null as string | null,
		// 保存一个标识信息，指示登陆后需要加载的初始化数据是否完成
		loaded: false,
		// 保存当前用户
		user: null as UserInfo | null,
		// 菜单数据
		menus: [] as Array<Menu>,
	}),
	getters: {
		// 获取token
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
			// 发送获取当前用户信息请求
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
			// 发送获取菜单请求
			const data = await useHttp().get<Array<Menu>>("/login/get-menus");
			if (data.data) this.menus = data.data;
		},
		// 加载刷新凭证
		loadRefreshToken() {
			if (!this.refreshToken) this.refreshToken = localStorage.getItem("refreshToken");
		},
		// 刷新token
		async reloadToken() {
			// 先加载刷新凭证
			this.loadRefreshToken();
			// 发送刷新凭证请求
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
			//设置Token相关属性
			this.setToken(data.data);
		},
		// 设置是否加载完成
		setLoaded(loaded: boolean) {
			this.loaded = loaded;
		},
		// 设置token
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
