/**
 * @filename: lint-staged.config.js
 * @description 用于配置 lint-staged 的配置文件，在 git commit 时自动格式化暂存区内的目标文件。
 * @type {import('lint-staged').Configuration}
 * @see https://github.com/lint-staged/lint-staged/blob/main/README.md#typescript
 */

/**
 * 仅对 Prettier 常见支持的源码、样式、配置和文档文件做预提交格式化，
 * 避免对二进制文件或无关文件触发无意义的扫描。
 */
const prettierExtensions = [
	"js",
	"jsx",
	"ts",
	"tsx",
	"cts",
	"mts",
	"cjs",
	"mjs",
	"vue",
	"json",
	"md",
	"mdx",
	"yml",
	"yaml",
	"css",
	"scss",
	"less",
	"html",
];

/**
 * 使用精确的文件类型匹配，替代 `"*"` 的全量匹配方式，
 * 减少 lint-staged 与 Prettier 在提交前的启动和扫描开销。
 *
 * @see https://github.com/lint-staged/lint-staged/blob/main/README.md#automatically-fix-code-style-with-prettier-for-any-format-prettier-supports
 */
const prettierPattern = `**/*.{${prettierExtensions.join(",")}}`;

export default {
	[prettierPattern]: (files) => {
		/**
		 * 锁文件体积较大、格式稳定，提交前不再交给 Prettier 处理，
		 * 避免它拖慢 pre-commit。
		 */
		const targetFiles = files.filter((file) => file !== "pnpm-lock.yaml");

		if (targetFiles.length === 0) {
			return [];
		}

		/** 返回给 lint-staged 的命令数组。 */
		return [`prettier --experimental-cli --write ${targetFiles.join(" ")}`];
	},
};
