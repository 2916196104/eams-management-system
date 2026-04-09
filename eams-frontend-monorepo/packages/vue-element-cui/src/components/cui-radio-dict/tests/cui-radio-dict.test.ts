import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import CuiRadioDict from "../cui-radio-dict.vue";

describe("CuiRadioDict", () => {
	test("renders with default props", () => {
		const wrapper = mount(CuiRadioDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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

	test("loads dictionary options on mount", async () => {
		const wrapper = mount(CuiRadioDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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
		const wrapper = mount(CuiRadioDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		const radioGroupStub = wrapper.findComponent({ name: "ElRadioGroup" });
		await radioGroupStub.vm.$emit("update:model-value", "dict1");

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual(["dict1"]);
	});

	test("emits change event on value change", async () => {
		const wrapper = mount(CuiRadioDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		const radioGroupStub = wrapper.findComponent({ name: "ElRadioGroup" });
		await radioGroupStub.vm.$emit("update:model-value", "dict2");

		expect(wrapper.emitted("change")).toBeTruthy();
		expect(wrapper.emitted("change")?.[0]).toEqual(["dict2"]);
	});

	test("passes disabled prop correctly", () => {
		const wrapper = mount(CuiRadioDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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

	test("renders loaded dictionary options", async () => {
		const wrapper = mount(CuiRadioDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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
		const wrapper = mount(CuiRadioDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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

	test("handles different dictionary codes", async () => {
		const wrapper = mount(CuiRadioDict, {
			props: {
				modelValue: "",
				dictCode: "ANOTHER_DICT",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.props("dictCode")).toBe("ANOTHER_DICT");
	});

	test("reflects modelValue prop", () => {
		const wrapper = mount(CuiRadioDict, {
			props: {
				modelValue: "dict2",
				dictCode: "TEST_DICT",
			},
			global: {
				stubs: {
					ElRadioGroup: true,
					ElRadio: true,
				},
			},
		});

		const radioGroupStub = wrapper.findComponent({ name: "ElRadioGroup" });
		expect(radioGroupStub.props("modelValue")).toBe("dict2");
	});
});
