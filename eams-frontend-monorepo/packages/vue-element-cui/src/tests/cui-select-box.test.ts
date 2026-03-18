import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import { ElPopover, ElInput } from "element-plus";
import CuiSelectBox from "../components/cui-select-box/cui-select-box.vue";
import type { CuiSelectBoxOption } from "../components/cui-select-box/types";

describe("CuiSelectBox", () => {
	const mockOptions: CuiSelectBoxOption[] = [
		{ id: 1, label: "选项1" },
		{ id: 2, label: "选项2" },
		{ id: 3, label: "选项3" },
	];

	test("renders component correctly", () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
		expect(wrapper.findComponent(ElPopover).exists()).toBe(true);
		expect(wrapper.findComponent(ElInput).exists()).toBe(true);
	});

	test("renders with default props", () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const input = wrapper.findComponent(ElInput);
		expect(input.props("placeholder")).toBe("请选择");
		expect(input.props("disabled")).toBe(false);
		expect(input.props("readonly")).toBe(true);
	});

	test("applies custom placeholder", () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
				placeholder: "请选择项目",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const input = wrapper.findComponent(ElInput);
		expect(input.props("placeholder")).toBe("请选择项目");
	});

	test("disables input when disabled prop is true", () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
				disabled: true,
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const input = wrapper.findComponent(ElInput);
		expect(input.props("disabled")).toBe(true);
	});

	test("sets popover width based on limit prop", () => {
		const singleWrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
				limit: 1,
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const multiWrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
				limit: 0,
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		expect(singleWrapper.findComponent(ElPopover).props("width")).toBe(400);
		expect(multiWrapper.findComponent(ElPopover).props("width")).toBe(700);
	});

	test("emits update:modelValue when handleSubmit is called with single selection", async () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
				limit: 1,
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const selectedItems = [mockOptions[0]];
		await wrapper.vm.handleSubmit(selectedItems);

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual([1]);
	});

	test("emits update:modelValue when handleSubmit is called with multiple selections", async () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
				limit: 0,
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const selectedItems = [mockOptions[0], mockOptions[1]];
		await wrapper.vm.handleSubmit(selectedItems);

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual(["1,2"]);
	});

	test("emits submit event when handleSubmit is called", async () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
				limit: 1,
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const selectedItems = [mockOptions[0]];
		await wrapper.vm.handleSubmit(selectedItems);

		expect(wrapper.emitted("submit")).toBeTruthy();
		expect(wrapper.emitted("submit")?.[0]).toEqual([1]);
	});

	test("updates display label when handleSubmit is called", async () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const selectedItems = [mockOptions[0], mockOptions[1]];
		await wrapper.vm.handleSubmit(selectedItems);

		expect(wrapper.vm.displayLabel).toBe("选项1, 选项2");
	});

	test("closes popover after handleSubmit is called", async () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		wrapper.vm.showPopover = true;
		await wrapper.vm.$nextTick();

		const selectedItems = [mockOptions[0]];
		await wrapper.vm.handleSubmit(selectedItems);

		expect(wrapper.vm.showPopover).toBe(false);
	});

	test("clears value when handleClear is called", async () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "1",
				type: "test",
				limit: 1,
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		wrapper.vm.displayLabel = "选项1";
		await wrapper.vm.handleClear();

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual([""]);
		expect(wrapper.vm.displayLabel).toBe("");
	});

	test("clears display label when modelValue becomes empty", async () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "1",
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		wrapper.vm.displayLabel = "选项1";
		await wrapper.setProps({ modelValue: "" });

		expect(wrapper.vm.displayLabel).toBe("");
	});

	test("clears display label when modelValue becomes empty array", async () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: ["1", "2"],
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		wrapper.vm.displayLabel = "选项1, 选项2";
		await wrapper.setProps({ modelValue: [] });

		expect(wrapper.vm.displayLabel).toBe("");
	});

	test("passes condition prop correctly", () => {
		const condition = { status: "active", type: "user" };
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
				condition,
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		expect(wrapper.props("condition")).toEqual(condition);
	});

	test("input is readonly", () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const input = wrapper.findComponent(ElInput);
		expect(input.props("readonly")).toBe(true);
	});

	test("input has clearable prop", () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const input = wrapper.findComponent(ElInput);
		expect(input.props("clearable")).toBe(true);
	});

	test("popover placement is bottom", () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const popover = wrapper.findComponent(ElPopover);
		expect(popover.props("placement")).toBe("bottom");
	});

	test("popover trigger is click", () => {
		const wrapper = mount(CuiSelectBox, {
			props: {
				modelValue: "",
				type: "test",
			},
			global: {
				components: {
					ElPopover,
					ElInput,
				},
			},
		});

		const popover = wrapper.findComponent(ElPopover);
		expect(popover.props("trigger")).toBe("click");
	});
});
