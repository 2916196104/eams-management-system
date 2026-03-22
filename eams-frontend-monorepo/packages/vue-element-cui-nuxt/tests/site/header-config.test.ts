import { readFileSync } from "node:fs";
import { resolve, dirname } from "node:path";
import { fileURLToPath } from "node:url";

import { describe, expect, test } from "vitest";

const __dirname = dirname(fileURLToPath(import.meta.url));

describe("app.config header navigation", () => {
	test("keeps four fixed top-level nav items matching content IA", () => {
		const raw = readFileSync(resolve(__dirname, "../../app.config.ts"), "utf8");

		expect(raw).toContain('title: "快速开始"');
		expect(raw).toContain('to: "/getting-started"');
		expect(raw).toContain('title: "组件"');
		expect(raw).toContain('to: "/components"');
		expect(raw).toContain('title: "规范"');
		expect(raw).toContain('to: "/guidelines"');
		expect(raw).toContain('title: "更新"');
		expect(raw).toContain('to: "/updates"');
	});
});
