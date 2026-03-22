import { createRequire } from "node:module";

import { getVueElementCuiAliases } from "./workspace-aliases";

const require = createRequire(import.meta.url);
const dayjsEsmEntry = require.resolve("dayjs/esm/index.js");
const mermaidEsmEntry = require.resolve("mermaid/dist/mermaid.esm.mjs");
const debugShimEntry = require.resolve("./shims/debug.ts");

export default defineNuxtConfig({
	extends: ["shadcn-docs-nuxt"],
	compatibilityDate: "2025-05-13",
	devtools: { enabled: true },
	alias: getVueElementCuiAliases(),
	experimental: {
		appManifest: false,
	},

	build: {
		// 警告 不需要配置 "shiki" 因为最简单的 `shadcn-docs-nuxt-starter` 项目本身也没有配置 "shiki"
		transpile: ["ohash"],
	},

	vite: {
		optimizeDeps: {
			include: ["debug", "dayjs", "@braintree/sanitize-url", "mermaid"],
			esbuildOptions: {
				target: "esnext",
			},
		},
		resolve: {
			alias: [
				{
					find: /^dayjs$/,
					replacement: dayjsEsmEntry,
				},
				{
					find: /^mermaid$/,
					replacement: mermaidEsmEntry,
				},
				{
					find: /^debug$/,
					replacement: debugShimEntry,
				},
			],
			dedupe: ["dayjs"],
		},
		ssr: {
			noExternal: ["debug"],
		},
	},

	content: {
		highlight: {
			theme: {
				default: "github-light",
				dark: "houston",
			},
			preload: ["vue", "typescript", "javascript", "bash"],
		},
	},

	i18n: {
		defaultLocale: "zh-CN",
		locales: [
			{
				code: "zh-CN",
				name: "简体中文",
			},
		],
	},

	ogImage: {
		enabled: false,
	},

	icon: {
		/** 默认会扫描本地安装的全部 iconify 集合（可达上百个），Nitro 打包阶段极易 OOM；站点仅使用 lucide */
		serverBundle: {
			collections: ["lucide"],
		},
		clientBundle: {
			scan: true,
			sizeLimitKb: 512,
		},
	},

	/**
	 * `node-server` 产物不依赖构建期全站静态化。预渲染会再拉起一套 nitro-prerender 进程并加载完整 SSR 包，
	 * 在默认堆（及 8G 上限）下易 OOM。清空待渲染路由并关闭 crawl，使 `nuxt build` 只产出 SSR 服务包。
	 * 若需要纯静态托管，可改用 `nuxi generate` 或在有足够内存的环境执行带预渲染的构建。
	 */
	nitro: {
		externals: {
			/**
			 * Windows + pnpm workspace 下 nodeFileTrace 在当前文档站产物上会长期占用高 CPU/内存，
			 * 先关闭 trace，避免 `nuxt build` 卡在 `Building Nuxt Nitro server` 阶段。
			 */
			trace: false,
		},
		prerender: {
			crawlLinks: false,
		},
		hooks: {
			"prerender:routes"(routes: Set<string>) {
				routes.clear();
			},
		},
	},
});
