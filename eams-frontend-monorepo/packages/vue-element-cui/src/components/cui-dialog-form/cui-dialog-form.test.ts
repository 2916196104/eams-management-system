import { describe, test, expect } from "vitest";
import { mount } from "@vue/test-utils";
import { ElDialog, ElButton, ElForm, ElFormItem, ElInput } from "element-plus";
import CuiDialogForm from "./cui-dialog-form.vue";
import CuiDialog from "../cui-dialog/cui-dialog.vue";
import CuiForm from "../cui-form/cui-form.vue";

describe("CuiDialogForm", () => {
	const defaultProps = {
		visible: true,
		modelValue: { name: "", email: "" },
		title: "Test Form Dialog",
		fields: [
			{
				prop: "name",
				label: "Name",
				type: "input" as const,
				placeholder: "Enter name",
			},
			{
				prop: "email",
				label: "Email",
				type: "input" as const,
				placeholder: "Enter email",
			},
		],
	};

	test("renders dialog form", () => {
		const wrapper = mount(CuiDialogForm, {
			props: defaultProps,
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		const dialog = wrapper.findComponent(CuiDialog);
		expect(dialog.exists()).toBe(true);
		expect(dialog.props("modelValue")).toBe(true);
	});

	test("emits update:visible when dialog closes", async () => {
		const wrapper = mount(CuiDialogForm, {
			props: defaultProps,
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		const dialog = wrapper.findComponent(CuiDialog);
		await dialog.vm.$emit("update:modelValue", false);

		expect(wrapper.emitted("update:visible")).toBeTruthy();
		expect(wrapper.emitted("update:visible")?.[0]).toEqual([false]);
	});

	test("emits submit event with form data on confirm", async () => {
		const wrapper = mount(CuiDialogForm, {
			props: defaultProps,
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		// Mock formRef.value.validate
		wrapper.vm.formRef = {
			validate: () => Promise.resolve(true),
		};

		await wrapper.vm.handleConfirm();
		expect(wrapper.emitted("submit")).toBeTruthy();
	});

	test("emits cancel event when cancel button clicked", async () => {
		const wrapper = mount(CuiDialogForm, {
			props: defaultProps,
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		await wrapper.vm.handleCancel();
		expect(wrapper.emitted("cancel")).toBeTruthy();
	});

	test("respects custom button text", () => {
		const wrapper = mount(CuiDialogForm, {
			props: {
				...defaultProps,
				confirmText: "Save",
				cancelText: "Discard",
			},
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		const dialog = wrapper.findComponent(CuiDialog);
		expect(dialog.props("confirmText")).toBe("Save");
		expect(dialog.props("cancelText")).toBe("Discard");
	});

	test("disables form when loading", () => {
		const wrapper = mount(CuiDialogForm, {
			props: {
				...defaultProps,
				loading: true,
			},
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		expect(wrapper.props("loading")).toBe(true);
	});

	test("exposes resetForm method", () => {
		const wrapper = mount(CuiDialogForm, {
			props: defaultProps,
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		expect(wrapper.vm.resetForm).toBeDefined();
		expect(typeof wrapper.vm.resetForm).toBe("function");
	});

	test("exposes setFormData method", () => {
		const wrapper = mount(CuiDialogForm, {
			props: defaultProps,
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		expect(wrapper.vm.setFormData).toBeDefined();
		expect(typeof wrapper.vm.setFormData).toBe("function");
	});

	test("updates form data when modelValue changes", async () => {
		const wrapper = mount(CuiDialogForm, {
			props: defaultProps,
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		const newData = { name: "John", email: "john@example.com" };
		await wrapper.setProps({ modelValue: newData });

		// 验证 props 更新
		expect(wrapper.props("modelValue")).toEqual(newData);
	});

	test("renders form fields from config", () => {
		const wrapper = mount(CuiDialogForm, {
			props: defaultProps,
			global: {
				components: { ElDialog, ElButton, ElForm, ElFormItem, ElInput, CuiDialog, CuiForm },
			},
		});

		expect(wrapper.props("fields")).toEqual(defaultProps.fields);
	});
});
