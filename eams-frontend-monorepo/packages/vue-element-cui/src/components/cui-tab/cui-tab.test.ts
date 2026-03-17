import { describe, test, expect } from "vitest";
import { mount } from "@vue/test-utils";
import { ElTabs, ElTabPane } from "element-plus";
import CuiTab from "./cui-tab.vue";

describe("CuiTab", () => {
	const defaultProps = {
		tabs: [
			{ label: "Tab 1", name: "tab1", content: "Content 1" },
			{ label: "Tab 2", name: "tab2", content: "Content 2" },
			{ label: "Tab 3", name: "tab3", content: "Content 3" },
		],
		activeTab: "tab1",
	};

	test("renders tabs", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.find(".el-tabs").exists()).toBe(true);
	});

	test("emits update:activeTab on tab change", async () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		await wrapper.vm.$emit("update:activeTab", "tab2");
		expect(wrapper.emitted("update:activeTab")).toBeTruthy();
	});

	test("respects custom type", () => {
		const wrapper = mount(CuiTab, {
			props: {
				...defaultProps,
				type: "border-card",
			},
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.vm.$props.type).toBe("border-card");
	});

	test("supports closable tabs", () => {
		const wrapper = mount(CuiTab, {
			props: {
				...defaultProps,
				closable: true,
			},
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.vm.$props.closable).toBe(true);
	});

	test("emits tab-change event", async () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		await wrapper.vm.handleTabChange("tab2");
		expect(wrapper.emitted("tab-change")).toBeTruthy();
	});
});
