/**
 * @type {import('lint-staged').Configuration}
 * @see https://github.com/lint-staged/lint-staged/blob/main/README.md#typescript
 */
export default {
  "*.{js,jsx,ts,tsx,mts,json,css,scss,md,yml,yaml,html,vue}": "prettier --write",
};
