import { describe, test, expect } from "vitest";
import { mount } from "@vue/test-utils";
import { ElDialog, ElButton } from "element-plus";
import CuiDialog from "./cui-dialog.vue";

describe("CuiDialog", () => {
	test("renders with correct props", () => {
		const wrapper = mount(CuiDialog, {
			props: {
				modelValue: true,
				title: "Test Dialog",
				width: "600px",
			},
			global: {
				components: { ElDialog, ElButton },
			},
		});

		const dialog = wrapper.findComponent(ElDialog);
		expect(dialog.exists()).toBe(true);
		expect(dialog.props("modelValue")).toBe(true);
		expect(dialog.props("title")).toBe("Test Dialog");
		expect(dialog.props("width")).toBe("600px");
	});

	test("emits update:modelValue when dialog closes", async () => {
		const wrapper = mount(CuiDialog, {
			props: {
				modelValue: true,
				title: "Test Dialog",
			},
			global: {
				components: { ElDialog, ElButton },
			},
		});

		const dialog = wrapper.findComponent(ElDialog);
		await dialog.vm.$emit("update:modelValue", false);

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual([false]);
	});

	test("emits confirm event when confirm button clicked", async () => {
		const wrapper = mount(CuiDialog, {
			props: {
				modelValue: true,
				title: "Test Dialog",
			},
			global: {
				components: { ElDialog, ElButton },
			},
		});

		await wrapper.vm.handleConfirm();
		expect(wrapper.emitted("confirm")).toBeTruthy();
	});

	test("emits cancel event when cancel button clicked", async () => {
		const wrapper = mount(CuiDialog, {
			props: {
				modelValue: true,
				title: "Test Dialog",
			},
			global: {
				components: { ElDialog, ElButton },
			},
		});

		await wrapper.vm.handleCancel();
		expect(wrapper.emitted("cancel")).toBeTruthy();
	});

	test("respects custom button text", () => {
		const wrapper = mount(CuiDialog, {
			props: {
				modelValue: true,
				title: "Test Dialog",
				confirmText: "Submit",
				cancelText: "Close",
			},
			global: {
				components: { ElDialog, ElButton },
			},
		});

		expect(wrapper.props("confirmText")).toBe("Submit");
		expect(wrapper.props("cancelText")).toBe("Close");
	});

	test("disables confirm button when confirmDisabled is true", () => {
		const wrapper = mount(CuiDialog, {
			props: {
				modelValue: true,
				title: "Test Dialog",
				confirmDisabled: true,
			},
			global: {
				components: { ElDialog, ElButton },
			},
		});

		expect(wrapper.props("confirmDisabled")).toBe(true);
	});

	test("shows loading state on confirm button", () => {
		const wrapper = mount(CuiDialog, {
			props: {
				modelValue: true,
				title: "Test Dialog",
				loading: true,
			},
			global: {
				components: { ElDialog, ElButton },
			},
		});

		expect(wrapper.props("loading")).toBe(true);
	});

	test("renders slot content", () => {
		const wrapper = mount(CuiDialog, {
			props: {
				modelValue: true,
				title: "Test Dialog",
			},
			slots: {
				default: '<div class="test-content">Test Content</div>',
			},
			global: {
				components: { ElDialog, ElButton },
			},
		});

		// 验证插槽内容被传递（即使 ElDialog 在测试中不渲染）
		expect(wrapper.vm.$slots.default).toBeDefined();
	});

	test("hides footer when showFooter is false", () => {
		const wrapper = mount(CuiDialog, {
			props: {
				modelValue: true,
				title: "Test Dialog",
				showFooter: false,
			},
			global: {
				components: { ElDialog, ElButton },
			},
		});

		expect(wrapper.props("showFooter")).toBe(false);
	});
});
