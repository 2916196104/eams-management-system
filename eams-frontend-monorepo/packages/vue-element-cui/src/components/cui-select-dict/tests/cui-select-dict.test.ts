import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import CuiSelectDict from "../cui-select-dict.vue";

describe("CuiSelectDict", () => {
	test("renders with default props", () => {
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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

	test("loads dictionary options on mount", async () => {
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		await selectStub.vm.$emit("update:model-value", "dict1");

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual(["dict1"]);
	});

	test("emits change event on value change", async () => {
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		await selectStub.vm.$emit("update:model-value", "dict2");

		expect(wrapper.emitted("change")).toBeTruthy();
		expect(wrapper.emitted("change")?.[0]).toEqual(["dict2"]);
	});

	test("passes placeholder prop correctly", () => {
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
				placeholder: "Select dictionary value",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		const selectStub = wrapper.findComponent({ name: "ElSelect" });
		expect(selectStub.props("placeholder")).toBe("Select dictionary value");
	});

	test("passes disabled prop correctly", () => {
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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

	test("renders loaded dictionary options", async () => {
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "TEST_DICT",
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
		expect(wrapper.vm.options.map((o: any) => o.value)).toEqual(["1", "2", "3"]);
	});

	test("handles different dictionary codes", async () => {
		const wrapper = mount(CuiSelectDict, {
			props: {
				modelValue: "",
				dictCode: "ANOTHER_DICT",
			},
			global: {
				stubs: {
					ElSelect: true,
					ElOption: true,
				},
			},
		});

		await wrapper.vm.$nextTick();
		expect(wrapper.props("dictCode")).toBe("ANOTHER_DICT");
	});
});
