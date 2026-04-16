import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import CuiAutocomplete from "../cui-autocomplete.vue";

describe("CuiAutocomplete", () => {
	const mockSuggestions = [
		{ value: "apple", label: "Apple" },
		{ value: "banana", label: "Banana" },
		{ value: "cherry", label: "Cherry" },
	];

	test("renders with default props", () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: mockSuggestions,
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
	});

	test("emits update:modelValue on input change", async () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: mockSuggestions,
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		const autocompleteStub = wrapper.findComponent({ name: "ElAutocomplete" });
		await autocompleteStub.vm.$emit("update:model-value", "app");

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual(["app"]);
	});

	test("emits select event when suggestion is selected", async () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: mockSuggestions,
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		const autocompleteStub = wrapper.findComponent({ name: "ElAutocomplete" });
		const selectedItem = { value: "apple", label: "Apple" };
		await autocompleteStub.vm.$emit("select", selectedItem);

		expect(wrapper.emitted("select")).toBeTruthy();
		expect(wrapper.emitted("select")?.[0]).toEqual([selectedItem]);
	});

	test("passes placeholder prop correctly", () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: mockSuggestions,
				placeholder: "Type to search",
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		const autocompleteStub = wrapper.findComponent({ name: "ElAutocomplete" });
		expect(autocompleteStub.props("placeholder")).toBe("Type to search");
	});

	test("passes disabled prop correctly", () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: mockSuggestions,
				disabled: true,
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		const autocompleteStub = wrapper.findComponent({ name: "ElAutocomplete" });
		expect(autocompleteStub.props("disabled")).toBe(true);
	});

	test("passes clearable prop correctly", () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: mockSuggestions,
				clearable: false,
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		const autocompleteStub = wrapper.findComponent({ name: "ElAutocomplete" });
		expect(autocompleteStub.props("clearable")).toBe(false);
	});

	test("filters suggestions based on query", async () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: mockSuggestions,
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		const vm = wrapper.vm as any;
		const callback = vi.fn();
		vm.fetchSuggestions("app", callback);

		expect(callback).toHaveBeenCalledWith([{ value: "apple", label: "Apple" }]);
	});

	test("filters suggestions case-insensitively", async () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: mockSuggestions,
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		const vm = wrapper.vm as any;
		const callback = vi.fn();
		vm.fetchSuggestions("CHERRY", callback);

		expect(callback).toHaveBeenCalledWith([{ value: "cherry", label: "Cherry" }]);
	});

	test("returns all suggestions for empty query", async () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: mockSuggestions,
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		const vm = wrapper.vm as any;
		const callback = vi.fn();
		vm.fetchSuggestions("", callback);

		expect(callback).toHaveBeenCalledWith(mockSuggestions);
	});

	test("reflects modelValue prop", () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "apple",
				suggestions: mockSuggestions,
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		const autocompleteStub = wrapper.findComponent({ name: "ElAutocomplete" });
		expect(autocompleteStub.props("modelValue")).toBe("apple");
	});

	test("handles empty suggestions array", () => {
		const wrapper = mount(CuiAutocomplete, {
			props: {
				modelValue: "",
				suggestions: [],
			},
			global: {
				stubs: {
					ElAutocomplete: true,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
	});
});
