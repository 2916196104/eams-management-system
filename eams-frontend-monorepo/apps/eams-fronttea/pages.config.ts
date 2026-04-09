import { defineUniPages } from "@uni-helper/vite-plugin-uni-pages";

export default defineUniPages({
	pages: [],
	globalStyle: {
		navigationBarBackgroundColor: "@navBgColor",
		navigationBarTextStyle: "@navTxtStyle",
		navigationBarTitleText: "教师端",
		backgroundColor: "@bgColor",
		backgroundTextStyle: "@bgTxtStyle",
		backgroundColorTop: "@bgColorTop",
		backgroundColorBottom: "@bgColorBottom",
		enablePullDownRefresh: false,
		onReachBottomDistance: 50,
		animationType: "pop-in",
		animationDuration: 300,
	},
	tabBar: {
		custom: true,
		// #ifdef MP-ALIPAY
		customize: true,
		overlay: true,
		// #endif
		height: "0",
		color: "@tabColor",
		selectedColor: "@tabSelectedColor",
		backgroundColor: "@tabBgColor",
		borderStyle: "@tabBorderStyle",
		list: [
			{
				pagePath: "pages/home/index",
			},
			{
				pagePath: "pages/schedule/index",
			},
			{
				pagePath: "pages/class/index",
			},
		],
	},
});
