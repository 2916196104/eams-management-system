import js from "@eslint/js";

export default [
  js.configs.recommended,
  {
    ignores: ["**/dist/**", "**/node_modules/**", "**/.turbo/**"],
  },
  {
    files: ["**/*.{js,mjs,cjs,ts,tsx,vue}"],
    rules: {
      "no-unused-vars": "warn",
      "no-console": "warn",
    },
  },
];
