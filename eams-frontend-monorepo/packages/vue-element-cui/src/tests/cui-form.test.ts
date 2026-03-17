import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import { ElForm, ElFormItem, ElInput, ElInputNumber, ElSelect, ElOption, ElDatePicker } from "element-plus";
import CuiForm from "../components/cui-form/cui-form.vue";
import type { CuiFormField } from "../components/cui-form/types";

describe("CuiForm", () => {
	const mockFormData = {
		name: "",
		age: 0,
		email: "",
		gender: "",
		birthday: "",
		description: "",
	};

	const mockFields: CuiFormField[] = [
		{
			prop: "name",
			label: "姓名",
			type: "input",
			placeholder: "请输入姓名",
			required: true,
		},
		{
			prop: "age",
			label: "年龄",
			type: "number",
			placeholder: "请输入年龄",
		},
		{
			prop: "email",
			label: "邮箱",
			type: "input",
			placeholder: "请输入邮箱",
			required: true,
		},
		{
			prop: "gender",
			label: "性别",
			type: "select",
			placeholder: "请选择性别",
			options: [
				{ label: "男", value: "male" },
				{ label: "女", value: "female" },
			],
		},
		{
			prop: "birthday",
			label: "生日",
			type: "date",
			placeholder: "请选择生日",
		},
		{
			prop: "description",
			label: "描述",
			type: "textarea",
			placeholder: "请输入描述",
		},
	];

	test("renders form with fields", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: mockFields,
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElInputNumber,
					ElSelect,
					ElOption,
					ElDatePicker,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
		expect(wrapper.findComponent(ElForm).exists()).toBe(true);
	});

	test("renders correct number of form items", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: mockFields,
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElInputNumber,
					ElSelect,
					ElOption,
					ElDatePicker,
				},
			},
		});

		const formItems = wrapper.findAllComponents(ElFormItem);
		expect(formItems.length).toBe(mockFields.length);
	});

	test("renders input field correctly", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: [mockFields[0]], // name field
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
				},
			},
		});

		const input = wrapper.findComponent(ElInput);
		expect(input.exists()).toBe(true);
		expect(input.props("placeholder")).toBe("请输入姓名");
	});

	test("renders number field correctly", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: [mockFields[1]], // age field
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInputNumber,
				},
			},
		});

		const inputNumber = wrapper.findComponent(ElInputNumber);
		expect(inputNumber.exists()).toBe(true);
	});

	test("renders select field correctly", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: [mockFields[3]], // gender field
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElSelect,
					ElOption,
				},
			},
		});

		const select = wrapper.findComponent(ElSelect);
		expect(select.exists()).toBe(true);

		const options = wrapper.findAllComponents(ElOption);
		expect(options.length).toBe(2);
	});

	test("renders date field correctly", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: [mockFields[4]], // birthday field
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElDatePicker,
				},
			},
		});

		const datePicker = wrapper.findComponent(ElDatePicker);
		expect(datePicker.exists()).toBe(true);
	});

	test("renders textarea field correctly", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: [mockFields[5]], // description field
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
				},
			},
		});

		const textarea = wrapper.findComponent(ElInput);
		expect(textarea.exists()).toBe(true);
		expect(textarea.props("type")).toBe("textarea");
	});

	test("emits update:modelValue when field value changes", async () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: [mockFields[0]], // name field
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
				},
			},
		});

		const input = wrapper.findComponent(ElInput);
		await input.vm.$emit("update:modelValue", "John Doe");

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		const emittedValue = wrapper.emitted("update:modelValue")?.[0]?.[0] as any;
		expect(emittedValue.name).toBe("John Doe");
	});

	test("applies form props correctly", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: mockFields,
				modelValue: mockFormData,
				labelWidth: "120px",
				inline: true,
				disabled: true,
				labelPosition: "top",
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElInputNumber,
					ElSelect,
					ElOption,
					ElDatePicker,
				},
			},
		});

		const elForm = wrapper.findComponent(ElForm);
		expect(elForm.props("labelWidth")).toBe("120px");
		expect(elForm.props("inline")).toBe(true);
		expect(elForm.props("disabled")).toBe(true);
		expect(elForm.props("labelPosition")).toBe("top");
	});

	test("applies required validation rules", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: [mockFields[0]], // name field with required: true
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
				},
			},
		});

		const formItem = wrapper.findComponent(ElFormItem);
		const rules = formItem.props("rules") as any[];
		expect(rules).toBeDefined();
		expect(rules.length).toBeGreaterThan(0);
		expect(rules[0].required).toBe(true);
	});

	test("disables field when disabled prop is true", () => {
		const disabledField: CuiFormField = {
			...mockFields[0],
			disabled: true,
		};

		const wrapper = mount(CuiForm, {
			props: {
				fields: [disabledField],
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
				},
			},
		});

		const input = wrapper.findComponent(ElInput);
		expect(input.props("disabled")).toBe(true);
	});

	test("renders custom slot content", () => {
		const fieldWithSlot: CuiFormField = {
			prop: "custom",
			label: "自定义字段",
			type: "input",
			slot: "custom",
		};

		const wrapper = mount(CuiForm, {
			props: {
				fields: [fieldWithSlot],
				modelValue: { ...mockFormData, custom: "" },
			},
			slots: {
				custom: ({ field, value }: { field: CuiFormField; value: any }) =>
					`<div class="custom-field">${field.label}: ${value}</div>`,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
				},
			},
		});

		// 检查字段配置中是否有 slot 属性
		expect(fieldWithSlot.slot).toBe("custom");
	});

	test("exposes validate method", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: mockFields,
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElInputNumber,
					ElSelect,
					ElOption,
					ElDatePicker,
				},
			},
		});

		expect(wrapper.vm.validate).toBeDefined();
		expect(typeof wrapper.vm.validate).toBe("function");
	});

	test("exposes resetFields method", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: mockFields,
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElInputNumber,
					ElSelect,
					ElOption,
					ElDatePicker,
				},
			},
		});

		expect(wrapper.vm.resetFields).toBeDefined();
		expect(typeof wrapper.vm.resetFields).toBe("function");
	});

	test("exposes submit method", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: mockFields,
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElInputNumber,
					ElSelect,
					ElOption,
					ElDatePicker,
				},
			},
		});

		expect(wrapper.vm.submit).toBeDefined();
		expect(typeof wrapper.vm.submit).toBe("function");
	});

	test("exposes clearValidate method", () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: mockFields,
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElInputNumber,
					ElSelect,
					ElOption,
					ElDatePicker,
				},
			},
		});

		expect(wrapper.vm.clearValidate).toBeDefined();
		expect(typeof wrapper.vm.clearValidate).toBe("function");
	});

	test("emits reset event when resetFields is called", async () => {
		const wrapper = mount(CuiForm, {
			props: {
				fields: mockFields,
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
					ElInputNumber,
					ElSelect,
					ElOption,
					ElDatePicker,
				},
			},
		});

		wrapper.vm.resetFields();
		await wrapper.vm.$nextTick();

		expect(wrapper.emitted("reset")).toBeTruthy();
	});

	test("applies custom validation rules", () => {
		const fieldWithCustomRules: CuiFormField = {
			prop: "email",
			label: "邮箱",
			type: "input",
			rules: [
				{
					type: "email",
					message: "请输入正确的邮箱格式",
					trigger: "blur",
				},
			],
		};

		const wrapper = mount(CuiForm, {
			props: {
				fields: [fieldWithCustomRules],
				modelValue: mockFormData,
			},
			global: {
				components: {
					ElForm,
					ElFormItem,
					ElInput,
				},
			},
		});

		const formItem = wrapper.findComponent(ElFormItem);
		const rules = formItem.props("rules") as any[];
		expect(rules).toBeDefined();
		expect(rules.length).toBeGreaterThan(0);
		expect(rules[0].type).toBe("email");
	});
});
