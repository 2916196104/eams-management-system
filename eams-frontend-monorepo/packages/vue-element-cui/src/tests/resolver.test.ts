import { describe, expect, test } from "vitest";
import {
	VueElementCuiAutoImportResolver,
	VueElementCuiResolver,
	vueElementCuiImports,
	vueElementCuiTypeImports,
} from "../resolver";

describe("vue-element-cui resolver", () => {
	test("resolves Cui components for unplugin-vue-components", async () => {
		const resolver = VueElementCuiResolver();
		const result = await resolver("CuiTable");

		expect(result).toEqual({
			name: "CuiTable",
			from: "@eams-monorepo/vue-element-cui",
			sideEffects: "@eams-monorepo/vue-element-cui/styles",
		});
	});

	test("ignores unknown components", async () => {
		const resolver = VueElementCuiResolver();

		expect(resolver("ElButton")).toBeUndefined();
	});
});

describe("vue-element-cui auto import resolver", () => {
	test("resolves runtime exports for unplugin-auto-import", async () => {
		const resolver = VueElementCuiAutoImportResolver();

		expect(resolver("version")).toEqual({
			name: "version",
			from: "@eams-monorepo/vue-element-cui",
		});
		expect(resolver("VueElementCui")).toEqual({
			name: "default",
			as: "VueElementCui",
			from: "@eams-monorepo/vue-element-cui",
		});
		expect(resolver("CuiDialog")).toEqual({
			name: "CuiDialog",
			from: "@eams-monorepo/vue-element-cui",
			sideEffects: "@eams-monorepo/vue-element-cui/styles",
		});
	});

	test("exports a preset that covers runtime names and type names", () => {
		expect(vueElementCuiImports["@eams-monorepo/vue-element-cui"]).toContain("install");
		expect(vueElementCuiImports["@eams-monorepo/vue-element-cui"]).toContain("version");
		expect(vueElementCuiImports["@eams-monorepo/vue-element-cui"]).toContain("CuiTable");
		expect(vueElementCuiImports["@eams-monorepo/vue-element-cui"]).toContainEqual(["default", "VueElementCui"]);

		expect(vueElementCuiTypeImports).toEqual(
			expect.arrayContaining([
				expect.objectContaining({
					from: "@eams-monorepo/vue-element-cui",
					type: true,
					imports: expect.arrayContaining(["CuiTableProps", "CuiTableColumn", "CuiSelectOption"]),
				}),
			]),
		);
	});
});
