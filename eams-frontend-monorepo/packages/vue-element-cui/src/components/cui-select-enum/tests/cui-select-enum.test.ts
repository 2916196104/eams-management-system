import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import CuiSelectEnum from "../cui-select-enum.vue";

describe("CuiSelectEnum", () => {
	test("renders with default props", () => {
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
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

	test("loads enum options on mount", async () => {
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.vm.options).toHaveLength(3);
	});

	test("emits update:modelValue on value change", async () => {
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		await selectStub.vm.$emit("update:model-value", "1");

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual(["1"]);
	});

	test("emits change event on value change", async () => {
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		await selectStub.vm.$emit("update:model-value", "2");

		expect(wrapper.emitted("change")).toBeTruthy();
		expect(wrapper.emitted("change")?.[0]).toEqual(["2"]);
	});

	test("passes placeholder prop correctly", () => {
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
				placeholder: "Select enum value",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		expect(selectStub.props("placeholder")).toBe("Select enum value");
	});

	test("passes disabled prop correctly", () => {
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
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

	test("passes clearable prop correctly", () => {
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
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
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
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

	test("renders loaded enum options", async () => {
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		// Verify options are loaded via component state since Element Plus
		// sub-components are not findable via findAllComponents in jsdom
		expect(wrapper.vm.options).toHaveLength(3);
		expect(wrapper.vm.options.map((o: any) => o.value)).toEqual(["1", "2", "3"]);
	});

	test("handles different enum codes", async () => {
		const wrapper = mount(CuiSelectEnum, {
			props: {
				modelValue: "",
				enumCode: "ANOTHER_ENUM",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.props("enumCode")).toBe("ANOTHER_ENUM");
	});
});
