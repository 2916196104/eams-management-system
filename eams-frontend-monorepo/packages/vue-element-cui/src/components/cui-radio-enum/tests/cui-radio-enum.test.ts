import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import CuiRadioEnum from "../cui-radio-enum.vue";

describe("CuiRadioEnum", () => {
	test("renders with default props", () => {
		const wrapper = mount(CuiRadioEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
	});

	test("loads enum options on mount", async () => {
		const wrapper = mount(CuiRadioEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.vm.options).toHaveLength(3);
	});

	test("emits update:modelValue on value change", async () => {
		const wrapper = mount(CuiRadioEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		const radioGroupStub = wrapper.findComponent({ name: "ElRadioGroup" });
		await radioGroupStub.vm.$emit("update:model-value", "1");

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual(["1"]);
	});

	test("emits change event on value change", async () => {
		const wrapper = mount(CuiRadioEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		const radioGroupStub = wrapper.findComponent({ name: "ElRadioGroup" });
		await radioGroupStub.vm.$emit("update:model-value", "2");

		expect(wrapper.emitted("change")).toBeTruthy();
		expect(wrapper.emitted("change")?.[0]).toEqual(["2"]);
	});

	test("passes disabled prop correctly", () => {
		const wrapper = mount(CuiRadioEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
				disabled: true,
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		const radioGroupStub = wrapper.findComponent({ name: "ElRadioGroup" });
		expect(radioGroupStub.props("disabled")).toBe(true);
	});

	test("renders loaded enum options", async () => {
		const wrapper = mount(CuiRadioEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.vm.options).toHaveLength(3);
		expect(wrapper.vm.options.map((o: any) => o.value)).toEqual(["1", "2", "3"]);
	});

	test("displays correct labels for options", async () => {
		const wrapper = mount(CuiRadioEnum, {
			props: {
				modelValue: "",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.vm.options[0].label).toBe("选项 1");
		expect(wrapper.vm.options[1].label).toBe("选项 2");
		expect(wrapper.vm.options[2].label).toBe("选项 3");
	});

	test("handles different enum codes", async () => {
		const wrapper = mount(CuiRadioEnum, {
			props: {
				modelValue: "",
				enumCode: "ANOTHER_ENUM",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.props("enumCode")).toBe("ANOTHER_ENUM");
	});

	test("reflects modelValue prop", () => {
		const wrapper = mount(CuiRadioEnum, {
			props: {
				modelValue: "2",
				enumCode: "TEST_ENUM",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		const radioGroupStub = wrapper.findComponent({ name: "ElRadioGroup" });
		expect(radioGroupStub.props("modelValue")).toBe("2");
	});
});
