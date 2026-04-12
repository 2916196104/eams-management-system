/*
 * @Author: weisheng
 * @Date: 2025-06-23 22:23:05
 * @LastEditTime: 2026-03-25
 * @LastEditors: Codex
 * @Description:
 * @FilePath: /wot-starter/pages.config.ts
 * 记得注释
 */
import { defineUniPages } from "@uni-helper/vite-plugin-uni-pages";

export default defineUniPages({
	pages: [],
	globalStyle: {
		// 导航栏配置
		navigationBarBackgroundColor: "@navBgColor",
		navigationBarTextStyle: "@navTxtStyle",
		navigationBarTitleText: "Wot Starter",

		// 页面背景配置
		backgroundColor: "@bgColor",
		backgroundTextStyle: "@bgTxtStyle",
		backgroundColorTop: "@bgColorTop",
		backgroundColorBottom: "@bgColorBottom",

		// 下拉刷新配置
		enablePullDownRefresh: false,
		onReachBottomDistance: 50,

		// 动画配置
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
					pagePath: "pages/mine/index",
				},
			],
		},
});
