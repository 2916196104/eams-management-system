import { mount } from "@vue/test-utils";
import { h } from "vue";
import { describe, expect, test } from "vitest";
import {
	IconifyIconOffline,
	IconifyIconOnline,
	pickIconRenderer,
	resolveOfflineIcon,
	useRenderIcon,
} from "@/components/ReIcon";

describe("ReIcon", () => {
	test("resolveOfflineIcon supports legacy aliases and offline names", () => {
		expect(resolveOfflineIcon("IconMenu")).toBeTruthy();
		expect(resolveOfflineIcon("ep/menu")).toBeTruthy();
		expect(resolveOfflineIcon("ep:menu")).toBeTruthy();
	});

	test("pickIconRenderer routes icon names to the expected renderer", () => {
		expect(pickIconRenderer("IconMenu")).toBe(IconifyIconOffline);
		expect(pickIconRenderer("ep/menu")).toBe(IconifyIconOffline);
		expect(pickIconRenderer("ri:home-line")).toBe(IconifyIconOnline);
	});

	test("useRenderIcon renders offline icon components", () => {
		const RenderedIcon = useRenderIcon("ep/menu", { width: "18px", height: "18px" });
		const wrapper = mount({
			render() {
				return h(RenderedIcon);
			},
		});

		expect(wrapper.html()).toContain("<svg");
		expect(wrapper.html()).toContain('width="18px"');
	});
});
