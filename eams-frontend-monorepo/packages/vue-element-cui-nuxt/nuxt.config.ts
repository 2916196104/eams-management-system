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
