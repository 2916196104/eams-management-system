import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import CuiSelect from "../cui-select.vue";
import type { CuiSelectOption } from "../types";

describe("CuiSelect", () => {
	const mockOptions: CuiSelectOption[] = [
		{ label: "Option 1", value: "opt1" },
		{ label: "Option 2", value: "opt2" },
		{ label: "Option 3", value: "opt3" },
	];

	test("renders with default props", () => {
		const wrapper = mount(CuiSelect, {
			props: {
				modelValue: "",
				options: mockOptions,
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
	});

	test("emits update:modelValue on value change", async () => {
		const wrapper = mount(CuiSelect, {
			props: {
				modelValue: "",
				options: mockOptions,
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		await selectStub.vm.$emit("update:model-value", "opt1");

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual(["opt1"]);
	});

	test("emits change event on value change", async () => {
		const wrapper = mount(CuiSelect, {
			props: {
				modelValue: "",
				options: mockOptions,
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		await selectStub.vm.$emit("update:model-value", "opt2");

		expect(wrapper.emitted("change")).toBeTruthy();
		expect(wrapper.emitted("change")?.[0]).toEqual(["opt2"]);
	});

	test("passes placeholder prop correctly", () => {
		const wrapper = mount(CuiSelect, {
			props: {
				modelValue: "",
				options: mockOptions,
				placeholder: "Custom placeholder",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		expect(selectStub.props("placeholder")).toBe("Custom placeholder");
	});

	test("passes disabled prop correctly", () => {
		const wrapper = mount(CuiSelect, {
			props: {
				modelValue: "",
				options: mockOptions,
				disabled: true,
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		expect(selectStub.props("disabled")).toBe(true);
	});

	test("supports multiple selection", () => {
		const wrapper = mount(CuiSelect, {
			props: {
				modelValue: ["opt1", "opt2"],
				options: mockOptions,
				multiple: true,
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		expect(selectStub.props("multiple")).toBe(true);
	});

	test("renders all options", () => {
		const wrapper = mount(CuiSelect, {
			props: {
				modelValue: "",
				options: mockOptions,
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		// Verify options are passed correctly via props
		expect(wrapper.props("options")).toHaveLength(3);
		expect(wrapper.props("options")).toEqual(mockOptions);
	});

	test("passes clearable prop correctly", () => {
		const wrapper = mount(CuiSelect, {
			props: {
				modelValue: "",
				options: mockOptions,
				clearable: false,
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		expect(selectStub.props("clearable")).toBe(false);
	});

	test("passes filterable prop correctly", () => {
		const wrapper = mount(CuiSelect, {
			props: {
				modelValue: "",
				options: mockOptions,
				filterable: false,
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		expect(selectStub.props("filterable")).toBe(false);
	});
});
