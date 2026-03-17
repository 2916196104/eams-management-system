import { describe, test, expect } from "vitest";
import { version, install } from "../index";

describe("vue-element-cui", () => {
	test("should export version", () => {
		expect(version).toBe("1.0.0");
	});

	test("should export install function", () => {
		expect(typeof install).toBe("function");
	});
});
