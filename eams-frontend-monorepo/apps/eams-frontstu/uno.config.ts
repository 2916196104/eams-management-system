import { presetUni } from "@uni-helper/unocss-preset-uni";
import { defineConfig, presetIcons, transformerDirectives, transformerVariantGroup } from "unocss";

export default defineConfig({
	safelist: [
		"i-carbon:bookmark-filled",
		"i-carbon:user-multiple",
		"i-carbon:user-profile",
		"i-carbon:notebook",
		"i-carbon:result",
		"i-carbon:edit",
		"i-carbon:star-filled",
		"i-carbon:calendar",
		"i-carbon:gift",
		"i-carbon:shopping-cart",
		"i-carbon:favorite-filled",
		"i-carbon:checkmark-filled",
		"i-carbon:help-filled",
		"i-carbon:document",
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
			// HBuilderX/uni-app 环境下显式注册已安装的图标集，避免构建时整批 i-carbon:* 解析失败。
			collections: {
				carbon: () => import("@iconify-json/carbon/icons.json").then((i) => i.default),
			},
		}),
	],
	transformers: [transformerDirectives(), transformerVariantGroup()],
});
