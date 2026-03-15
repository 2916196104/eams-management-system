export default defineNuxtConfig({
	extends: ["shadcn-docs-nuxt"],
	compatibilityDate: "2025-05-13",
	devtools: { enabled: true },

	build: {
		// 警告 不需要配置 "shiki" 因为最简单的 `shadcn-docs-nuxt-starter` 项目本身也没有配置 "shiki"
		transpile: ["ohash"],
	},

	vite: {
		ssr: {
			noExternal: ["debug"],
		},
	},

	i18n: {
		defaultLocale: "zh-cn",
		locales: [
			{
				code: "zh-cn",
				name: "简体中文",
				language: "zh-CN",
			},
		],
	},

	content: {
		highlight: {
			theme: {
				default: "github-light",
				dark: "github-dark",
			},
			preload: ["vue", "typescript", "javascript", "bash"],
		},
	},

	ogImage: {
		enabled: false,
	},

	icon: {
		clientBundle: {
			scan: true,
			sizeLimitKb: 512,
		},
	},
});
