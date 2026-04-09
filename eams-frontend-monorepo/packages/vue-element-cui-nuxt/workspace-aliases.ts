import { resolve } from "node:path";

export function getVueElementCuiAliases() {
	return {
		"@eams-monorepo/vue-element-cui/styles": resolve(__dirname, "../vue-element-cui/src/styles/index.scss"),
		"@eams-monorepo/vue-element-cui": resolve(__dirname, "../vue-element-cui/src/index.ts"),
	};
}
