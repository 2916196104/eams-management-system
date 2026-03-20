import { defineConfig } from "vite";
import vue from "@vitejs/plugin-vue";
import dts from "vite-plugin-dts";
import { resolve } from "path";

export default defineConfig({
	plugins: [
		vue(),
		dts({
			insertTypesEntry: true,
			copyDtsFiles: true,
			// 与 tsconfig 一致：resolver 从 package.json 读取 name，需纳入 d.ts 生成图
			include: ["src/**/*.ts", "src/**/*.d.ts", "src/**/*.vue", "package.json"],
		}),
	],
	build: {
		lib: {
			entry: {
				index: resolve(__dirname, "src/index.ts"),
				resolver: resolve(__dirname, "src/resolver.ts"),
			},
			name: "VueElementCui",
			formats: ["es", "cjs"],
			fileName: (format, entryName) => `${entryName}.${format === "es" ? "js" : "cjs"}`,
		},
		rollupOptions: {
			external: ["vue", "element-plus", "@element-plus/icons-vue", "xlsx"],
			output: {
				globals: {
					vue: "Vue",
					"element-plus": "ElementPlus",
					"@element-plus/icons-vue": "ElementPlusIconsVue",
					xlsx: "XLSX",
				},
				assetFileNames: (assetInfo) => {
					if (assetInfo.name === "style.css") {
						return "index.css";
					}
					return assetInfo.name ?? "assets/[name][extname]";
				},
			},
		},
		sourcemap: false,
	},
});
