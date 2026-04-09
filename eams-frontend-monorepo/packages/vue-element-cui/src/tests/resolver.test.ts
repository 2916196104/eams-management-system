import { describe, expect, test } from "vitest";
import {
	VueElementCuiAutoImportResolver,
	VueElementCuiResolver,
	vueElementCuiComponentNames,
	vueElementCuiImports,
	vueElementCuiRuntimeExports,
	vueElementCuiTypeExportNames,
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

	test("returns undefined for empty string", () => {
		const resolver = VueElementCuiResolver();
		expect(resolver("")).toBeUndefined();
	});

	test("returns undefined for non-Cui names", () => {
		const resolver = VueElementCuiResolver();
		expect(resolver("CuiTableX")).toBeUndefined();
		expect(resolver("cui-table")).toBeUndefined();
		expect(resolver("VueElementCui")).toBeUndefined();
	});

	test("resolves all manifest components with sideEffects", () => {
		const resolver = VueElementCuiResolver();
		for (const name of vueElementCuiComponentNames) {
			const result = resolver(name);
			expect(result).toBeDefined();
			expect(result).toHaveProperty("from", "@eams-monorepo/vue-element-cui");
			expect(result).toHaveProperty("sideEffects", "@eams-monorepo/vue-element-cui/styles");
		}
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

	test("returns undefined for unknown runtime names", () => {
		const resolver = VueElementCuiAutoImportResolver();
		expect(resolver("unknown")).toBeUndefined();
		expect(resolver("ElButton")).toBeUndefined();
		expect(resolver("")).toBeUndefined();
	});

	test("VueElementCui has no sideEffects in auto-import result", () => {
		const resolver = VueElementCuiAutoImportResolver();
		const result = resolver("VueElementCui");
		expect(result).toEqual({
			name: "default",
			as: "VueElementCui",
			from: "@eams-monorepo/vue-element-cui",
		});
		expect(result).not.toHaveProperty("sideEffects");
	});

	test("install and version have no sideEffects in auto-import result", () => {
		const resolver = VueElementCuiAutoImportResolver();
		expect(resolver("install")).toEqual({
			name: "install",
			from: "@eams-monorepo/vue-element-cui",
		});
		expect(resolver("version")).toEqual({
			name: "version",
			from: "@eams-monorepo/vue-element-cui",
		});
	});
});

describe("resolver manifest consistency (Volar / type support)", () => {
	test("vueElementCuiTypeImports contains exactly manifest type names", () => {
		const typeEntry = vueElementCuiTypeImports.find((e) => e.from === "@eams-monorepo/vue-element-cui" && e.type);
		expect(typeEntry).toBeDefined();
		expect(typeEntry!.imports).toEqual([...vueElementCuiTypeExportNames]);
	});

	test("vueElementCuiImports runtime list matches vueElementCuiRuntimeExports", () => {
		const runtimeList = vueElementCuiImports["@eams-monorepo/vue-element-cui"];
		expect(runtimeList).toContainEqual(["default", "VueElementCui"]);
		expect(runtimeList).toEqual(expect.arrayContaining([...vueElementCuiRuntimeExports]));
		// [["default", "VueElementCui"], ...vueElementCuiRuntimeExports]
		expect(runtimeList!.length).toBe(1 + vueElementCuiRuntimeExports.length);
	});

	test("vueElementCuiComponentNames is non-empty and all resolve", () => {
		expect(vueElementCuiComponentNames.length).toBeGreaterThan(0);
		const resolver = VueElementCuiResolver();
		for (const name of vueElementCuiComponentNames) {
			const result = resolver(name);
			expect(result, `resolve("${name}")`).toBeDefined();
			expect(result).toHaveProperty("sideEffects", "@eams-monorepo/vue-element-cui/styles");
		}
	});
});
