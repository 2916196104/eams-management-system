/**
 * 每次修改该文件后 务必执行一次 `npx simple-git-hooks` 命令
 * 否则这些钩子不会生效
 */
export default {
  "commit-msg": "npx --no-install commitlint --edit ${1}",
  "pre-commit": "npx lint-staged",
};
