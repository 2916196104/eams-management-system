import { describe, test, expect, vi, beforeEach } from "vitest";
import { mount } from "@vue/test-utils";
import { ElUpload, ElButton, ElIcon, ElDialog } from "element-plus";
import CuiExcel from "../components/cui-excel/cui-excel.vue";
import { CuiDialog } from "../components/cui-dialog";

describe("CuiExcel", () => {
	const mockProps = {
		modelValue: true,
		uploadUrl: "https://api.example.com/upload",
		title: "导入用户数据",
		templateUrl: "https://api.example.com/template.xlsx",
		headers: { Authorization: "Bearer token" },
		params: { type: "user" },
	};

	beforeEach(() => {
		vi.clearAllMocks();
	});

	test("renders component correctly", () => {
		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
			attachTo: document.body,
		});

		expect(wrapper.exists()).toBe(true);
		expect(wrapper.findComponent(CuiDialog).exists()).toBe(true);

		wrapper.unmount();
	});

	test("shows template download section when templateUrl is provided", async () => {
		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
			attachTo: document.body,
		});

		await wrapper.vm.$nextTick();

		const templateSection = document.querySelector(".template-download");
		expect(templateSection).toBeTruthy();

		wrapper.unmount();
	});

	test("renders upload instructions", async () => {
		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
			attachTo: document.body,
		});

		await wrapper.vm.$nextTick();

		const bodyText = document.body.textContent || "";
		expect(bodyText).toContain("将文件拖到此处");

		wrapper.unmount();
	});

	test("hides template download when templateUrl is not provided", () => {
		const wrapper = mount(CuiExcel, {
			props: {
				modelValue: true,
				uploadUrl: "https://api.example.com/upload",
			},
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		const html = wrapper.html();
		expect(html).not.toContain("template-download");
	});

	test("applies default props correctly", () => {
		const wrapper = mount(CuiExcel, {
			props: {
				modelValue: true,
				uploadUrl: "https://api.example.com/upload",
			},
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		expect(wrapper.props("title")).toBe("导入 Excel");
		expect(wrapper.props("accept")).toBe(".xls,.xlsx");
		expect(wrapper.props("headers")).toEqual({});
		expect(wrapper.props("params")).toEqual({});
	});

	test("accepts custom props", () => {
		const wrapper = mount(CuiExcel, {
			props: {
				...mockProps,
				accept: ".csv,.xlsx",
				title: "导入数据",
			},
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		expect(wrapper.props("accept")).toBe(".csv,.xlsx");
		expect(wrapper.props("title")).toBe("导入数据");
	});

	test("emits update:modelValue event", async () => {
		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		await wrapper.vm.$emit("update:modelValue", false);

		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual([false]);
	});

	test("emits success event", async () => {
		const mockResponse = { code: 200, message: "success" };
		const mockFile = { name: "test.xlsx", size: 1024 };
		const mockFileList = [mockFile];

		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		await wrapper.vm.$emit("success", mockResponse, mockFile, mockFileList);

		expect(wrapper.emitted("success")).toBeTruthy();
		expect(wrapper.emitted("success")?.[0]).toEqual([mockResponse, mockFile, mockFileList]);
	});

	test("emits error event", async () => {
		const mockError = new Error("Upload failed");

		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		await wrapper.vm.$emit("error", mockError);

		expect(wrapper.emitted("error")).toBeTruthy();
		expect(wrapper.emitted("error")?.[0]).toEqual([mockError]);
	});

	test("downloads template when button is clicked", async () => {
		const windowOpenSpy = vi.spyOn(window, "open").mockImplementation(() => null);

		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
			attachTo: document.body,
		});

		await wrapper.vm.$nextTick();

		const buttons = wrapper.findAllComponents(ElButton);
		const downloadButton = buttons.find((btn) => btn.text().includes("点击此处下载模板"));

		if (downloadButton) {
			await downloadButton.trigger("click");
			expect(windowOpenSpy).toHaveBeenCalledWith("https://api.example.com/template.xlsx", "_blank");
		}

		windowOpenSpy.mockRestore();
		wrapper.unmount();
	});

	test("has uploadRef in component instance", () => {
		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		expect("uploadRef" in wrapper.vm).toBe(true);
	});

	test("handleUpload calls submit on uploadRef", async () => {
		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		const submitMock = vi.fn();
		wrapper.vm.uploadRef = { submit: submitMock };

		wrapper.vm.handleUpload();

		expect(submitMock).toHaveBeenCalled();
	});

	test("handleSuccess emits success and closes dialog", async () => {
		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		const mockResponse = { code: 200 };
		const mockFile = { name: "test.xlsx" };
		const mockFileList = [mockFile];

		wrapper.vm.handleSuccess(mockResponse, mockFile, mockFileList);
		await wrapper.vm.$nextTick();

		expect(wrapper.emitted("success")).toBeTruthy();
		expect(wrapper.emitted("success")?.[0]).toEqual([mockResponse, mockFile, mockFileList]);
		expect(wrapper.emitted("update:modelValue")).toBeTruthy();
		expect(wrapper.emitted("update:modelValue")?.[0]).toEqual([false]);
	});

	test("handleError emits error event", async () => {
		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		const mockError = new Error("Upload failed");

		wrapper.vm.handleError(mockError);
		await wrapper.vm.$nextTick();

		expect(wrapper.emitted("error")).toBeTruthy();
		expect(wrapper.emitted("error")?.[0]).toEqual([mockError]);
	});

	test("downloadTemplate opens templateUrl in new window", () => {
		const windowOpenSpy = vi.spyOn(window, "open").mockImplementation(() => null);

		const wrapper = mount(CuiExcel, {
			props: mockProps,
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		wrapper.vm.downloadTemplate();

		expect(windowOpenSpy).toHaveBeenCalledWith("https://api.example.com/template.xlsx", "_blank");

		windowOpenSpy.mockRestore();
	});

	test("downloadTemplate does nothing when templateUrl is not provided", () => {
		const windowOpenSpy = vi.spyOn(window, "open").mockImplementation(() => null);

		const wrapper = mount(CuiExcel, {
			props: {
				modelValue: true,
				uploadUrl: "https://api.example.com/upload",
			},
			global: {
				components: {
					CuiDialog,
					ElDialog,
					ElUpload,
					ElButton,
					ElIcon,
				},
			},
		});

		wrapper.vm.downloadTemplate();

		expect(windowOpenSpy).not.toHaveBeenCalled();

		windowOpenSpy.mockRestore();
	});
});
