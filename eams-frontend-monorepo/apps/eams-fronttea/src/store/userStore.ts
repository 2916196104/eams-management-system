import { defineStore } from "pinia";

/**
 * 当前用户装，包括下面数据：
 *  用户基本信息
 *  用户功能列表
 */
export const useUserStore = defineStore("user", {
	state: () => {
		return {
			userInfo: {
				id: "1",
				nickName: "王林",
				phone: "13800000001",
				sex: "男",
			} as { id: string; nickName: string; phone: string; sex: string },
			funs: [
				{ id: 1, name: "功能1", icon: "i-carbon:settings", router: "" },
				{ id: 2, name: "功能2", icon: "i-carbon:application-virtual", router: "" },
				{ id: 3, name: "功能3", icon: "i-carbon:assembly", router: "" },
				{ id: 4, name: "功能4", icon: "i-carbon:favorite", router: "" },
				{ id: 5, name: "功能5", icon: "i-carbon:settings", router: "" },
				{ id: 6, name: "功能6", icon: "i-carbon:application-virtual", router: "" },
				{ id: 7, name: "功能7", icon: "i-carbon:assembly", router: "" },
				{ id: 8, name: "功能8", icon: "i-carbon:favorite", router: "" },
				{ id: 9, name: "关 于", icon: "i-carbon:user", router: "about" },
			] as Array<{ id: number; name: string; icon: string; router: string }>,
		};
	},
});
