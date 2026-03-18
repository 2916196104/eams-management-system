import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import CuiCheckboxEnum from "../cui-checkbox-enum.vue";

describe("CuiCheckboxEnum", () => {
	test("renders with default props", () => {
		const wrapper = mount(CuiCheckboxEnum, {
			props: {
				modelValue: [],
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElCheckboxGroup: true,
					ElCheckbox: true,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
	});

	test("loads enum options on mount", async () => {
		const wrapper = mount(CuiCheckboxEnum, {
			props: {
				modelValue: [],
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElCheckboxGroup: true,
					ElCheckbox: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.vm.options).toHaveLength(3);
	});

	test("emits update:modelValue on value change", async () => {
		const wrapper = mount(CuiCheckboxEnum, {
			props: {
				modelValue: [],
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElCheckboxGroup: true,
					ElCheckbox: true,
				},
			},
		});

		const checkboxGroupStub = wrapper.findComponent({ name: "ElCheckboxGroup" });
		await checkboxGroupStub.vm.$emit("update:model-value", ["1", "2"]);

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual([["1", "2"]]);
	});

	test("emits change event on value change", async () => {
		const wrapper = mount(CuiCheckboxEnum, {
			props: {
				modelValue: [],
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElCheckboxGroup: true,
					ElCheckbox: true,
				},
			},
		});

		const checkboxGroupStub = wrapper.findComponent({ name: "ElCheckboxGroup" });
		await checkboxGroupStub.vm.$emit("update:model-value", ["1"]);

		expect(wrapper.emitted("change")).toBeTruthy();
		expect(wrapper.emitted("change")?.[0]).toEqual([["1"]]);
	});

	test("passes disabled prop correctly", () => {
		const wrapper = mount(CuiCheckboxEnum, {
			props: {
				modelValue: [],
				enumCode: "TEST_ENUM",
				disabled: true,
			},
			global: {
				stubs: {
					ElCheckboxGroup: true,
					ElCheckbox: true,
				},
			},
		});

		const checkboxGroupStub = wrapper.findComponent({ name: "ElCheckboxGroup" });
		expect(checkboxGroupStub.props("disabled")).toBe(true);
	});

	test("renders loaded enum options", async () => {
		const wrapper = mount(CuiCheckboxEnum, {
			props: {
				modelValue: [],
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElCheckboxGroup: true,
					ElCheckbox: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.vm.options).toHaveLength(3);
		expect(wrapper.vm.options.map((o: any) => o.value)).toEqual(["1", "2", "3"]);
	});

	test("displays correct labels for options", async () => {
		const wrapper = mount(CuiCheckboxEnum, {
			props: {
				modelValue: [],
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElCheckboxGroup: true,
					ElCheckbox: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.vm.options[0].label).toBe("选项 1");
		expect(wrapper.vm.options[1].label).toBe("选项 2");
		expect(wrapper.vm.options[2].label).toBe("选项 3");
	});

	test("handles different enum codes", async () => {
		const wrapper = mount(CuiCheckboxEnum, {
			props: {
				modelValue: [],
				enumCode: "ANOTHER_ENUM",
			},
			global: {
				stubs: {
					ElCheckboxGroup: true,
					ElCheckbox: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.props("enumCode")).toBe("ANOTHER_ENUM");
	});

	test("reflects modelValue prop with multiple selections", () => {
		const wrapper = mount(CuiCheckboxEnum, {
			props: {
				modelValue: ["1", "3"],
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElCheckboxGroup: true,
					ElCheckbox: true,
				},
			},
		});

		const checkboxGroupStub = wrapper.findComponent({ name: "ElCheckboxGroup" });
		expect(checkboxGroupStub.props("modelValue")).toEqual(["1", "3"]);
	});
});
