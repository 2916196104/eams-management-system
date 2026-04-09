import { describe, test, expect } from "vitest";
import { mount } from "@vue/test-utils";
import { ElForm, ElFormItem, ElInput, ElSelect, ElOption, ElDatePicker, ElButton, ElIcon } from "element-plus";
import CuiSearch from "../components/cui-search/cui-search.vue";
import type { CuiSearchField } from "../components/cui-search/types";

describe("CuiSearch", () => {
	const mockFields: CuiSearchField[] = [
		{ prop: "name", label: "姓名", type: "input", placeholder: "请输入姓名" },
		{
			prop: "status",
			label: "状态",
			type: "select",
			options: [
				{ label: "启用", value: 1 },
				{ label: "禁用", value: 0 },
			],
		},
		{ prop: "createDate", label: "创建日期", type: "date" },
		{ prop: "dateRange", label: "日期范围", type: "daterange" },
	];

	const mockFieldsWithAdvanced: CuiSearchField[] = [
		{ prop: "name", label: "姓名", type: "input" },
		{ prop: "email", label: "邮箱", type: "input", advanced: true },
		{ prop: "phone", label: "电话", type: "input", advanced: true },
	];

	test("renders search form with fields", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFields,
				modelValue: {},
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
		expect(wrapper.findComponent(ElForm).exists()).toBe(true);
	});

	test("renders correct number of form items", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFields,
				modelValue: {},
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const formItems = wrapper.findAllComponents(ElFormItem);
		// 4 个字段 + 1 个操作按钮区域
		expect(formItems.length).toBe(5);
	});

	test("renders input field correctly", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: [{ prop: "name", label: "姓名", type: "input", placeholder: "请输入姓名" }],
				modelValue: {},
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const input = wrapper.findComponent(ElInput);
		expect(input.exists()).toBe(true);
		expect(input.props("placeholder")).toBe("请输入姓名");
	});

	test("renders select field correctly", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: [
					{
						prop: "status",
						label: "状态",
						type: "select",
						options: [
							{ label: "启用", value: 1 },
							{ label: "禁用", value: 0 },
						],
					},
				],
				modelValue: {},
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const select = wrapper.findComponent(ElSelect);
		expect(select.exists()).toBe(true);
		const options = wrapper.findAllComponents(ElOption);
		expect(options.length).toBe(2);
	});

	test("renders date picker correctly", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: [{ prop: "createDate", label: "创建日期", type: "date" }],
				modelValue: {},
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const datePicker = wrapper.findComponent(ElDatePicker);
		expect(datePicker.exists()).toBe(true);
		expect(datePicker.props("type")).toBe("date");
	});

	test("renders date range picker correctly", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: [{ prop: "dateRange", label: "日期范围", type: "daterange" }],
				modelValue: {},
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const datePicker = wrapper.findComponent(ElDatePicker);
		expect(datePicker.exists()).toBe(true);
		expect(datePicker.props("type")).toBe("daterange");
	});

	test("emits search event when search button clicked", async () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFields,
				modelValue: { name: "Alice" },
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const buttons = wrapper.findAllComponents(ElButton);
		const searchButton = buttons[0];
		await searchButton.trigger("click");

		expect(wrapper.emitted("search")).toBeTruthy();
		expect(wrapper.emitted("search")?.[0]).toEqual([{ name: "Alice" }]);
	});

	test("emits reset event when reset button clicked", async () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFields,
				modelValue: { name: "Alice" },
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const buttons = wrapper.findAllComponents(ElButton);
		const resetButton = buttons[1];
		await resetButton.trigger("click");

		expect(wrapper.emitted("reset")).toBeTruthy();
		expect(wrapper.emitted("reset")?.[0]).toEqual([{}]);
	});

	test("clears form data when reset button clicked", async () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFields,
				modelValue: { name: "Alice", status: 1 },
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const buttons = wrapper.findAllComponents(ElButton);
		const resetButton = buttons[1];
		await resetButton.trigger("click");

		// 检查 formData 是否被清空
		expect(wrapper.vm.formData).toEqual({});
	});

	test("separates basic and advanced fields", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFieldsWithAdvanced,
				modelValue: {},
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		// 基础字段应该有 1 个
		expect(wrapper.vm.basicFields.length).toBe(1);
		// 高级字段应该有 2 个
		expect(wrapper.vm.advancedFields.length).toBe(2);
	});

	test("shows advanced fields toggle button when has advanced fields", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFieldsWithAdvanced,
				modelValue: {},
				collapsible: true,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const buttons = wrapper.findAllComponents(ElButton);
		// 搜索、重置、展开/收起按钮
		expect(buttons.length).toBe(3);
	});

	test("toggles advanced fields visibility", async () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFieldsWithAdvanced,
				modelValue: {},
				collapsible: true,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		// 初始状态应该是收起的
		expect(wrapper.vm.advancedVisible).toBe(false);

		// 点击展开按钮
		const buttons = wrapper.findAllComponents(ElButton);
		const toggleButton = buttons[2];
		await toggleButton.trigger("click");

		// 应该展开
		expect(wrapper.vm.advancedVisible).toBe(true);

		// 再次点击
		await toggleButton.trigger("click");

		// 应该收起
		expect(wrapper.vm.advancedVisible).toBe(false);
	});

	test("does not show toggle button when collapsible is false", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFieldsWithAdvanced,
				modelValue: {},
				collapsible: false,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const buttons = wrapper.findAllComponents(ElButton);
		// 只有搜索和重置按钮
		expect(buttons.length).toBe(2);
	});

	test("emits update:modelValue when form data changes", async () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFields,
				modelValue: {},
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		// 修改 formData
		wrapper.vm.formData = { name: "Bob" };
		await wrapper.vm.$nextTick();

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
	});

	test("applies inline prop to form", () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFields,
				modelValue: {},
				inline: true,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		const form = wrapper.findComponent(ElForm);
		expect(form.props("inline")).toBe(true);
	});

	test("updates formData when modelValue prop changes", async () => {
		const wrapper = mount(CuiSearch, {
			props: {
				fields: mockFields,
				modelValue: { name: "Alice" },
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElSelect,
					ElOption,
					ElDatePicker,
					ElButton,
					ElIcon,
				},
			},
		});

		expect(wrapper.vm.formData).toEqual({ name: "Alice" });

		// 更新 modelValue
		await wrapper.setProps({ modelValue: { name: "Bob" } });

		expect(wrapper.vm.formData).toEqual({ name: "Bob" });
	});
});
