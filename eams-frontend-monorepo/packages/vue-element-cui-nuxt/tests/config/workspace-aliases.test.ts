import { describe, expect, test } from "vitest";

import { getVueElementCuiAliases } from "../../workspace-aliases";

describe("getVueElementCuiAliases", () => {
	test("points package imports to local source entries for dev-time resolution", () => {
		const aliases = getVueElementCuiAliases();

		expect(aliases["@eams-monorepo/vue-element-cui"]).toMatch(/packages[\\/]+vue-element-cui[\\/]+src[\\/]+index\.ts$/);
		expect(aliases["@eams-monorepo/vue-element-cui/styles"]).toMatch(
			/packages[\\/]+vue-element-cui[\\/]+src[\\/]+styles[\\/]+index\.scss$/,
		);
	});
});
