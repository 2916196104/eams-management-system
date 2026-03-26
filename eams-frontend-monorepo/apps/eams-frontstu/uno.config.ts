import { presetUni } from "@uni-helper/unocss-preset-uni";

import { defineConfig, presetIcons, transformerDirectives, transformerVariantGroup } from "unocss";

export default defineConfig({
	safelist: [
		"i-carbon:bookmark-filled",
		"i-carbon:user-multiple",
		"i-carbon:notebook",
		"i-carbon:result",
		"i-carbon:edit",
		"i-carbon:star-filled",
		"i-carbon:calendar",
		"i-carbon:gift",
	],
	presets: [
		presetUni({
			attributify: false,
		}),
		presetIcons({
			scale: 1.2,
			warn: true,
			extraProperties: {
				display: "inline-block",
				"vertical-align": "middle",
			},
			// HBuilderX 必须针对要使用的 Collections 做异步导入
			// collections: {
			//   carbon: () => import('@iconify-json/carbon/icons.json').then(i => i.default),
			// },
		}),
	],
	transformers: [transformerDirectives(), transformerVariantGroup()],
});
