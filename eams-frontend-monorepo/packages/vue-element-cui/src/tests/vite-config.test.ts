import { describe, expect, test } from "vitest";
import viteConfig from "../../vite.config";

describe("vite build config", () => {
	test("returns a stable css asset file name when asset name is missing", () => {
		const output = viteConfig.build?.rollupOptions?.output;

		if (!output || Array.isArray(output) || !output.assetFileNames) {
			throw new Error("vite output.assetFileNames is not configured");
		}

		const assetFileNames = output.assetFileNames;

		if (typeof assetFileNames !== "function") {
			throw new Error("vite output.assetFileNames must be a function");
		}

		expect(assetFileNames({ type: "asset" })).toBe("assets/[name][extname]");
	});
});
