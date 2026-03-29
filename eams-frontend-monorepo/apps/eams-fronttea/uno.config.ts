import { presetUni } from "@uni-helper/unocss-preset-uni";
import { defineConfig, presetIcons, transformerDirectives, transformerVariantGroup } from "unocss";

export default defineConfig({
	safelist: [
		"i-carbon:home",
		"i-carbon:calendar",
		"i-carbon:group",
		"i-carbon:currency",
		"i-carbon:catalog",
		"i-carbon:user-multiple",
		"i-carbon:user-multiple-add",
		"i-carbon:user-follow",
		"i-carbon:user-avatar-filled-alt",
		"i-carbon:receipt",
		"i-carbon:list-checked",
		"i-carbon:book",
		"i-carbon:favorite-filled",
		"i-carbon:star-filled",
		"i-carbon:user-profile",
		"i-carbon:rocket",
		"i-carbon:cloud",
		"i-carbon:chevron-right",
		"i-carbon:arrow-left",
		"i-carbon:renew",
		"i-carbon:search",
		"i-carbon:add",
		"i-carbon:document-unknown",
		"i-carbon:chevron-up",
		"i-carbon:calendar-heat-map",
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
			// HBuilderX 如需按需图标集合，可在这里补 collections。
			// collections: {
			//   carbon: () => import("@iconify-json/carbon/icons.json").then((i) => i.default),
			// },
		}),
	],
	transformers: [transformerDirectives(), transformerVariantGroup()],
});
