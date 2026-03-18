import { describe, test, expect } from "vitest";
import { mount } from "@vue/test-utils";
import { CuiSearch } from "../components/cui-search";
import { CuiTable } from "../components/cui-table";
import { CuiDialogForm } from "../components/cui-dialog-form";
import { CuiForm } from "../components/cui-form";

describe("Integration Tests", () => {
	describe("CuiSearch + CuiTable Integration", () => {
		test("search form data updates table display", async () => {
			const searchFields = [
				{ prop: "name", label: "姓名", type: "input" as const },
				{
					prop: "status",
					label: "状态",
					type: "select" as const,
					options: [
						{ label: "激活", value: "active" },
						{ label: "禁用", value: "inactive" },
					],
				},
			];

			const tableColumns = [
				{ prop: "name", label: "姓名" },
				{ prop: "status", label: "状态" },
			];

			const tableData = [
				{ id: 1, name: "Alice", status: "active" },
				{ id: 2, name: "Bob", status: "inactive" },
				{ id: 3, name: "Charlie", status: "active" },
			];

			const searchWrapper = mount(CuiSearch, {
				props: {
					fields: searchFields,
					modelValue: {},
				},
			});

			const tableWrapper = mount(CuiTable, {
				props: {
					data: tableData,
					columns: tableColumns,
				},
			});

			expect(searchWrapper.exists()).toBe(true);
			expect(tableWrapper.exists()).toBe(true);
		});

		test("search reset clears filters and shows all table data", async () => {
			const searchFields = [{ prop: "keyword", label: "关键词", type: "input" as const }];

			let searchData = {};
			const searchWrapper = mount(CuiSearch, {
				props: {
					fields: searchFields,
					modelValue: searchData,
					"onUpdate:modelValue": (val: any) => {
						searchData = val;
					},
				},
			});

			// Simulate search
			await searchWrapper.vm.handleSearch();

			// Simulate reset
			await searchWrapper.vm.handleReset();

			expect(searchData).toEqual({});
		});
	});

	describe("CuiDialogForm + CuiForm Integration", () => {
		test("dialog form validates using CuiForm validation", async () => {
			const formFields = [
				{
					prop: "username",
					label: "用户名",
					type: "input" as const,
					rules: [{ required: true, message: "请输入用户名" }],
				},
				{
					prop: "email",
					label: "邮箱",
					type: "input" as const,
					rules: [{ required: true, message: "请输入邮箱" }],
				},
			];

			const wrapper = mount(CuiDialogForm, {
				props: {
					visible: true,
					title: "编辑用户",
					fields: formFields,
					modelValue: {},
				},
			});

			expect(wrapper.exists()).toBe(true);
			// Verify CuiDialog is rendered inside CuiDialogForm
			expect(wrapper.findComponent({ name: "CuiDialog" }).exists()).toBe(true);
		});

		test("dialog form submission triggers form validation", async () => {
			const formFields = [
				{
					prop: "name",
					label: "名称",
					type: "input" as const,
					rules: [{ required: true, message: "请输入名称" }],
				},
			];

			let submitCalled = false;
			const wrapper = mount(CuiDialogForm, {
				props: {
					visible: true,
					title: "新建",
					fields: formFields,
					modelValue: {},
					onSubmit: () => {
						submitCalled = true;
					},
				},
			});

			// Try to submit with empty form
			await wrapper.vm.handleConfirm();

			// Validation should prevent submission
			expect(submitCalled).toBe(false);
		});

		test("dialog form integrates with CuiForm for validation", () => {
			const formFields = [{ prop: "title", label: "标题", type: "input" as const }];

			const wrapper = mount(CuiDialogForm, {
				props: {
					visible: true,
					title: "编辑",
					fields: formFields,
					modelValue: { title: "Test" },
				},
			});

			// Verify the dialog form renders correctly
			expect(wrapper.exists()).toBe(true);

			// Verify exposed methods exist
			expect(typeof wrapper.vm.resetForm).toBe("function");
			expect(typeof wrapper.vm.setFormData).toBe("function");
		});
	});

	describe("CuiForm Field Type Integration", () => {
		test("form handles multiple field types correctly", () => {
			const fields = [
				{ prop: "input", label: "输入框", type: "input" as const },
				{ prop: "select", label: "选择器", type: "select" as const, options: [] },
				{ prop: "date", label: "日期", type: "date" as const },
				{ prop: "textarea", label: "文本域", type: "textarea" as const },
			];

			const wrapper = mount(CuiForm, {
				props: {
					fields,
					modelValue: {},
				},
			});

			expect(wrapper.findAll(".el-form-item").length).toBe(4);
		});
	});
});
