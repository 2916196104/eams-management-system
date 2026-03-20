/**
 * @filename: simple-git-hooks.mjs
 * @description 配置 simple-git-hooks 的 git 钩子。
 *
 * 每次修改该文件后 务必执行一次 `npx simple-git-hooks` 命令
 * 否则这些钩子不会生效
 *
 * ## 为什么钩子命令需要 `cd eams-frontend-monorepo`？
 *
 * 本项目的目录结构如下：
 *
 * ```
 * 01s-2603-13eams/          ← Git 仓库根目录（.git 在这里）
 * └── eams-frontend-monorepo/  ← pnpm monorepo 工作区（package.json、node_modules 在这里）
 * ```
 *
 * Git 执行钩子时，CWD 会被设为仓库根目录（01s-2603-13eams/），
 * 但 lint-staged、commitlint 等工具安装在 monorepo 的 node_modules 中。
 * 因此每条钩子命令都需要先 `cd eams-frontend-monorepo` 切入 monorepo 目录，
 * 让 npx 能正确找到依赖和配置文件。
 *
 * 同时需要配合 `git config core.hooksPath eams-frontend-monorepo/.git/hooks` 使用，
 * 因为 simple-git-hooks 会将钩子写入 eams-frontend-monorepo/.git/hooks/（而非仓库根的 .git/hooks/）。
 */
export default {
	/**
	 * 提交信息校验钩子。
	 * 先用 ROOT 记录仓库根目录的绝对路径，cd 到 monorepo 后再用 "$ROOT/$1" 拼出提交信息文件的完整路径。
	 * （$1 是 Git 传入的提交信息文件相对路径，如 .git/COMMIT_EDITMSG，cd 后会失效，所以需要拼绝对路径。）
	 *
	 * @see https://juejin.cn/post/7381372081915166739#heading-8
	 * @see https://fabric.modyqyw.top/zh-Hans/guide/git/commitlint.html#%E6%95%B4%E5%90%88-simple-git-hooks
	 */
	"commit-msg": 'ROOT=$(pwd) && cd eams-frontend-monorepo && pnpm exec commitlint --edit "$ROOT/$1"',

	/** 提交前格式化钩子。cd 到 monorepo 后执行 lint-staged，对暂存区文件运行 Prettier 格式化。 */
	"pre-commit": "cd eams-frontend-monorepo && pnpm exec lint-staged",
};
