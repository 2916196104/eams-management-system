import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import { ElTabs, ElTabPane } from "element-plus";
import CuiTab from "../components/cui-tab/cui-tab.vue";
import type { CuiTabItem } from "../components/cui-tab/types";

describe("CuiTab", () => {
	const mockTabs: CuiTabItem[] = [
		{ label: "Tab 1", name: "tab1", content: "Content 1" },
		{ label: "Tab 2", name: "tab2", content: "Content 2" },
		{ label: "Tab 3", name: "tab3", content: "Content 3", disabled: true },
		{ label: "Tab 4", name: "tab4", content: "Content 4", closable: true },
	];

	const defaultProps = {
		tabs: mockTabs,
		activeTab: "tab1",
	};

	test("renders component correctly", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
		expect(wrapper.findComponent(ElTabs).exists()).toBe(true);
	});

	test("renders correct number of tabs", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const tabPanes = wrapper.findAllComponents(ElTabPane);
		expect(tabPanes.length).toBe(mockTabs.length);
	});

	test("validates tabs prop correctly", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.props("tabs")).toEqual(mockTabs);
		expect(wrapper.props("tabs").length).toBe(4);
	});

	test("validates activeTab prop correctly", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.props("activeTab")).toBe("tab1");
		const elTabs = wrapper.findComponent(ElTabs);
		expect(elTabs.props("modelValue")).toBe("tab1");
	});

	test("renders tab labels correctly", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const tabPanes = wrapper.findAllComponents(ElTabPane);
		tabPanes.forEach((pane, index) => {
			expect(pane.props("label")).toBe(mockTabs[index].label);
			expect(pane.props("name")).toBe(mockTabs[index].name);
		});
	});

	test("renders tab content correctly", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const tabPanes = wrapper.findAllComponents(ElTabPane);
		expect(tabPanes[0].text()).toContain("Content 1");
		expect(tabPanes[1].text()).toContain("Content 2");
	});

	test("emits update:activeTab event on tab change", async () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const elTabs = wrapper.findComponent(ElTabs);
		await elTabs.vm.$emit("update:model-value", "tab2");

		expect(wrapper.emitted("update:activeTab")).toBeTruthy();
		expect(wrapper.emitted("update:activeTab")?.[0]).toEqual(["tab2"]);
	});

	test("emits tab-change event when tab changes", async () => {
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
		expect(wrapper.emitted("tab-change")?.[0]).toEqual(["tab2"]);
	});

	test("supports different tab types", () => {
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

		const elTabs = wrapper.findComponent(ElTabs);
		expect(elTabs.props("type")).toBe("border-card");
	});

	test("defaults to card type", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const elTabs = wrapper.findComponent(ElTabs);
		expect(elTabs.props("type")).toBe("card");
	});

	test("supports closable tabs globally", () => {
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

		const elTabs = wrapper.findComponent(ElTabs);
		expect(elTabs.props("closable")).toBe(true);
	});

	test("supports individual tab closable property", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const tabPanes = wrapper.findAllComponents(ElTabPane);
		expect(tabPanes[3].props("closable")).toBe(true);
	});

	test("emits remove event when tab is closed", async () => {
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

		const elTabs = wrapper.findComponent(ElTabs);
		await elTabs.vm.$emit("tab-remove", "tab2");

		expect(wrapper.emitted("remove")).toBeTruthy();
		expect(wrapper.emitted("remove")?.[0]).toEqual(["tab2"]);
	});

	test("supports addable tabs", () => {
		const wrapper = mount(CuiTab, {
			props: {
				...defaultProps,
				addable: true,
			},
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const elTabs = wrapper.findComponent(ElTabs);
		expect(elTabs.props("addable")).toBe(true);
	});

	test("emits add event when adding new tab", async () => {
		const wrapper = mount(CuiTab, {
			props: {
				...defaultProps,
				addable: true,
			},
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const elTabs = wrapper.findComponent(ElTabs);
		await elTabs.vm.$emit("tab-add");

		expect(wrapper.emitted("add")).toBeTruthy();
	});

	test("supports editable type configuration", () => {
		const wrapper = mount(CuiTab, {
			props: {
				...defaultProps,
				editableType: "both",
			},
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.props("editableType")).toBe("both");
	});

	test("defaults editable type to add", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.props("editableType")).toBe("add");
	});

	test("respects disabled tab property", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const tabPanes = wrapper.findAllComponents(ElTabPane);
		expect(tabPanes[2].props("disabled")).toBe(true);
	});

	test("renders custom content via slots", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			slots: {
				"tab-tab1": '<div class="custom-content">Custom Tab 1</div>',
			},
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.html()).toContain("custom-content");
		expect(wrapper.html()).toContain("Custom Tab 1");
	});

	test("renders scoped slot with tab data", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			slots: {
				"tab-tab1": ({ tab }: { tab: CuiTabItem }) => `<div class="scoped-content">${tab.label}</div>`,
			},
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		expect(wrapper.html()).toContain("scoped-content");
		expect(wrapper.html()).toContain("Tab 1");
	});

	test("handles empty tabs array", () => {
		const wrapper = mount(CuiTab, {
			props: {
				tabs: [],
				activeTab: "",
			},
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const tabPanes = wrapper.findAllComponents(ElTabPane);
		expect(tabPanes.length).toBe(0);
	});

	test("handles tab switching correctly", async () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const elTabs = wrapper.findComponent(ElTabs);

		await elTabs.vm.$emit("update:model-value", "tab2");
		expect(wrapper.emitted("update:activeTab")?.[0]).toEqual(["tab2"]);

		await elTabs.vm.$emit("tab-change", "tab2");
		await wrapper.vm.handleTabChange("tab2");
		expect(wrapper.emitted("tab-change")?.[0]).toEqual(["tab2"]);
	});

	test("maintains tab order", () => {
		const wrapper = mount(CuiTab, {
			props: defaultProps,
			global: {
				components: {
					ElTabs,
					ElTabPane,
				},
			},
		});

		const tabPanes = wrapper.findAllComponents(ElTabPane);
		tabPanes.forEach((pane, index) => {
			expect(pane.props("name")).toBe(mockTabs[index].name);
		});
	});
});
