import { readFileSync } from "node:fs";
import { dirname, resolve } from "node:path";
import { fileURLToPath } from "node:url";

import { describe, expect, test } from "vitest";

const __dirname = dirname(fileURLToPath(import.meta.url));

describe("troubleshooting documentation", () => {
	test("uses the current styles entry instead of the legacy dist css path", () => {
		const raw = readFileSync(resolve(__dirname, "../../content/1.getting-started/4.troubleshooting.md"), "utf8");

		expect(raw).toContain("@eams-monorepo/vue-element-cui/styles");
		expect(raw).not.toContain("@eams-monorepo/vue-element-cui/dist/style.css");
	});
});
