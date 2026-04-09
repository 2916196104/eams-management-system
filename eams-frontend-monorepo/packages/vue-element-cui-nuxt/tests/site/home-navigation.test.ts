import { describe, expect, test } from "vitest";
import { mount, RouterLinkStub } from "@vue/test-utils";

import DocsHomeLanding from "../../app/components/home/DocsHomeLanding.vue";
import HomeCategoryGrid from "../../app/components/site/HomeCategoryGrid.vue";
import HomeQuickStartLinks from "../../app/components/site/HomeQuickStartLinks.vue";

describe("DocsHomeLanding", () => {
	test("surfaces quick-start, guidelines, and category entry links", () => {
		const wrapper = mount(DocsHomeLanding, {
			global: {
				components: {
					HomeCategoryGrid,
					HomeQuickStartLinks,
				},
				stubs: {
					NuxtLink: RouterLinkStub,
					Icon: true,
				},
			},
		});

		const links = wrapper.findAllComponents(RouterLinkStub).map((item) => item.props("to"));

		expect(links).toContain("/getting-started/installation");
		expect(links).toContain("/components");
		expect(links).toContain("/guidelines");
		expect(links).toContain("/components/data-display");
		expect(links).toContain("/components/selectors");
		expect(links).toContain("/components/feedback-overlay");
	});
});
