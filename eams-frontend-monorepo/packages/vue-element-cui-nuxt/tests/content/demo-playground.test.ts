import { describe, expect, test } from "vitest";
import { mount } from "@vue/test-utils";

import DemoCodePanel from "../../components/content/DemoCodePanel.vue";
import DemoPlayground from "../../components/content/DemoPlayground.vue";

describe("DemoPlayground", () => {
	test("renders title, description, preview, and code area", () => {
		const wrapper = mount(DemoPlayground, {
			props: {
				title: "基础示例",
				description: "用于验证预览优先的布局。",
			},
			slots: {
				preview: '<div data-testid="demo-preview">preview</div>',
				code: "<pre><code>const answer = 42;</code></pre>",
			},
			global: {
				components: {
					DemoCodePanel,
				},
				stubs: {
					ClientOnly: {
						template: "<div><slot /></div>",
					},
				},
			},
		});

		expect(wrapper.text()).toContain("基础示例");
		expect(wrapper.text()).toContain("用于验证预览优先的布局。");
		expect(wrapper.find("[data-testid='demo-preview']").exists()).toBe(true);
		expect(wrapper.find("code").text()).toContain("const answer = 42;");
	});

	test("toggles the code panel", async () => {
		const wrapper = mount(DemoPlayground, {
			slots: {
				preview: "<div>preview</div>",
				code: "<pre><code>collapsed</code></pre>",
			},
			global: {
				components: {
					DemoCodePanel,
				},
				stubs: {
					ClientOnly: {
						template: "<div><slot /></div>",
					},
				},
			},
		});

		expect(wrapper.text()).toContain("收起代码");
		expect(wrapper.find("[data-testid='code-panel']").isVisible()).toBe(true);

		await wrapper.get("button").trigger("click");

		expect(wrapper.text()).toContain("展开代码");
		expect(wrapper.find(".cui-demo-code").attributes("hidden")).toBeDefined();
	});
});
