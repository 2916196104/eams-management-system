import * as prettierPluginOxc from "@prettier/plugin-oxc";
import prettierPluginLintMd from "prettier-plugin-lint-md";

// @ts-check
/** @type {import("prettier").Config} */
const config = {
	plugins: ["prettier-plugin-lint-md"],

	/** @see https://github.com/prettier/prettier/tree/main/packages/plugin-oxc */
	overrides: [
		{
			files: ["**/*.{js,mjs,cjs,jsx}"],
			parser: "oxc",
			plugins: [prettierPluginOxc],
		},
		{
			files: ["**/*.{ts,mts,cts,tsx}"],
			parser: "oxc-ts",
			plugins: [prettierPluginOxc],
		},
		{
			// MDC (Markdown Components) 文档使用 ::component\n--- 紧贴语法，
			// prettier 格式化会在 ::component 和 --- 之间插入空行，
			// 导致 YAML frontmatter 无法被解析，图标等 props 丢失。
			// 因此对 nuxt content 目录的 .md 文件完全禁用格式化。
			files: ["packages/vue-element-cui-nuxt/content/**/*.md"],
			options: {
				requirePragma: true,
			},
		},
	],

	singleQuote: false,
	printWidth: 120,
	semi: true,
	jsxSingleQuote: true,
	useTabs: true,
	tabWidth: 2,
	endOfLine: "auto",
	trailingComma: "all",
	bracketSpacing: true,
	arrowParens: "always",
	htmlWhitespaceSensitivity: "ignore",
	vueIndentScriptAndStyle: false,
	"space-around-alphabet": true,
	"space-around-number": true,
	"no-empty-code-lang": false,
	"no-empty-code": false,
};

export default config;
