export default defineAppConfig({
	shadcnDocs: {
		site: {
			name: "Vue Element CUI",
			description: "企业级 Vue 3 组件库，基于 Element Plus 封装，提供更简洁的 API 和常用功能的快速配置。",
		},
		theme: {
			customizable: true,
			color: "stone",
			radius: 0.5,
		},
		header: {
			title: "Vue Element CUI",
			showTitle: true,
			darkModeToggle: true,
			logo: {
				light: "/logo.svg",
				dark: "/logo-dark.svg",
			},
			nav: [
				{
					title: "快速开始",
					to: "/getting-started",
				},
				{
					title: "组件",
					to: "/components",
				},
				{
					title: "规范",
					to: "/guidelines",
				},
				{
					title: "更新",
					to: "/updates",
				},
			],
			links: [
				{
					icon: "lucide:github",
					to: "https://github.com/eams/vue-element-cui",
					target: "_blank",
				},
			],
		},
		aside: {
			useLevel: true,
			collapse: false,
			levelStyle: "aside",
			collapseLevel: 1,
			folderStyle: "default",
		},
		main: {
			breadCrumb: true,
			showTitle: true,
		},
		footer: {
			credits: "Vue Element CUI 文档站，聚焦企业级组件接入、规范和演示。",
			links: [
				{
					icon: "lucide:github",
					to: "https://github.com/eams/vue-element-cui",
					target: "_blank",
				},
			],
		},
		toc: {
			enable: true,
			title: "本页目录",
			links: [
				{
					title: "GitHub",
					icon: "lucide:star",
					to: "https://github.com/eams/vue-element-cui",
					target: "_blank",
				},
				{
					title: "提交 Issue",
					icon: "lucide:circle-dot",
					to: "https://github.com/eams/vue-element-cui/issues",
					target: "_blank",
				},
			],
		},
		search: {
			enable: true,
			inAside: false,
		},
	},
});
