// taze.config.ts
import { defineConfig } from "taze";
import { defaultConfig } from "@ruan-cat/taze-config";

export default defineConfig({
	...defaultConfig,
	// 忽略 old\vue-element-cui 项目的依赖升级
	ignorePaths: [...(defaultConfig.ignorePaths || []), "**/old/vue-element-cui/**"],
});
