import { describe, expect, test } from "vitest";

import { useLocalePath } from "../../composables/useLocalePath";
import { useSwitchLocalePath } from "../../composables/useSwitchLocalePath";

describe("no-i18n compatibility", () => {
	test("locale path helper returns original path", () => {
		const localePath = useLocalePath();

		expect(localePath("/components")).toBe("/components");
	});

	test("switch locale helper keeps current route shape callable", () => {
		expect(typeof useSwitchLocalePath()).toBe("function");
	});
});
