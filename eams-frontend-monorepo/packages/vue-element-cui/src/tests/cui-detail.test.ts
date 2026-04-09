import { describe, test, expect } from "vitest";
import { mount } from "@vue/test-utils";
import CuiDetail from "../components/cui-detail/cui-detail.vue";
import type { CuiDetailField } from "../components/cui-detail/types";

describe("CuiDetail", () => {
	const mockData = {
		name: "John Doe",
		email: "john@example.com",
		age: 30,
		phone: "123-456-7890",
		address: "123 Main St",
		status: "active",
	};

	const mockFields: CuiDetailField[] = [
		{
			label: "姓名",
			prop: "name",
		},
		{
			label: "邮箱",
			prop: "email",
		},
		{
			label: "年龄",
			prop: "age",
		},
		{
			label: "电话",
			prop: "phone",
		},
	];

	test("renders component correctly", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
			},
		});

		expect(wrapper.exists()).toBe(true);
		expect(wrapper.find(".cui-detail").exists()).toBe(true);
	});

	test("renders correct number of detail items", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
			},
		});

		const items = wrapper.findAll(".detail-item");
		expect(items.length).toBe(mockFields.length);
	});

	test("displays field labels correctly", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
			},
		});

		const labels = wrapper.findAll(".detail-label");
		expect(labels[0].text()).toBe("姓名:");
		expect(labels[1].text()).toBe("邮箱:");
		expect(labels[2].text()).toBe("年龄:");
		expect(labels[3].text()).toBe("电话:");
	});

	test("displays field values correctly", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
			},
		});

		const values = wrapper.findAll(".detail-value");
		expect(values[0].text()).toBe("John Doe");
		expect(values[1].text()).toBe("john@example.com");
		expect(values[2].text()).toBe("30");
		expect(values[3].text()).toBe("123-456-7890");
	});

	test("applies default labelWidth prop", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
			},
		});

		const label = wrapper.find(".detail-label");
		expect(label.attributes("style")).toContain("width: 140px");
	});

	test("applies custom labelWidth prop", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
				labelWidth: "200px",
			},
		});

		const label = wrapper.find(".detail-label");
		expect(label.attributes("style")).toContain("width: 200px");
	});

	test("applies default columns prop", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
			},
		});

		const grid = wrapper.find(".detail-grid");
		expect(grid.attributes("style")).toContain("grid-template-columns: repeat(2, 1fr)");
	});

	test("applies custom columns prop", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
				columns: 3,
			},
		});

		const grid = wrapper.find(".detail-grid");
		expect(grid.attributes("style")).toContain("grid-template-columns: repeat(3, 1fr)");
	});

	test("renders with custom render function", () => {
		const fieldsWithRender: CuiDetailField[] = [
			{
				label: "姓名",
				prop: "name",
				render: (data) => data.name.toUpperCase(),
			},
			{
				label: "状态",
				prop: "status",
				render: (data) => (data.status === "active" ? "激活" : "未激活"),
			},
		];

		const wrapper = mount(CuiDetail, {
			props: {
				fields: fieldsWithRender,
				data: mockData,
			},
		});

		const values = wrapper.findAll(".detail-value");
		expect(values[0].text()).toBe("JOHN DOE");
		expect(values[1].text()).toBe("激活");
	});

	test("handles empty data object", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: {},
			},
		});

		expect(wrapper.exists()).toBe(true);
		const values = wrapper.findAll(".detail-value");
		expect(values.length).toBe(mockFields.length);
	});

	test("handles empty fields array", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: [],
				data: mockData,
			},
		});

		expect(wrapper.exists()).toBe(true);
		const items = wrapper.findAll(".detail-item");
		expect(items.length).toBe(0);
	});

	test("handles missing data properties", () => {
		const partialData = {
			name: "John Doe",
			email: "john@example.com",
		};

		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: partialData,
			},
		});

		const values = wrapper.findAll(".detail-value");
		expect(values[0].text()).toBe("John Doe");
		expect(values[1].text()).toBe("john@example.com");
		expect(values[2].text()).toBe("");
		expect(values[3].text()).toBe("");
	});

	test("handles undefined data values", () => {
		const dataWithUndefined = {
			name: "John Doe",
			email: undefined,
			age: null,
			phone: "",
		};

		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: dataWithUndefined,
			},
		});

		expect(wrapper.exists()).toBe(true);
		const values = wrapper.findAll(".detail-value");
		expect(values[0].text()).toBe("John Doe");
	});

	test("renders with single column layout", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
				columns: 1,
			},
		});

		const grid = wrapper.find(".detail-grid");
		expect(grid.attributes("style")).toContain("grid-template-columns: repeat(1, 1fr)");
	});

	test("renders with multiple columns layout", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
				columns: 4,
			},
		});

		const grid = wrapper.find(".detail-grid");
		expect(grid.attributes("style")).toContain("grid-template-columns: repeat(4, 1fr)");
	});

	test("handles field with width property", () => {
		const fieldsWithWidth: CuiDetailField[] = [
			{
				label: "姓名",
				prop: "name",
				width: "300px",
			},
		];

		const wrapper = mount(CuiDetail, {
			props: {
				fields: fieldsWithWidth,
				data: mockData,
			},
		});

		expect(wrapper.exists()).toBe(true);
	});

	test("renders complex data types", () => {
		const complexData = {
			name: "John Doe",
			tags: ["tag1", "tag2"],
			metadata: { key: "value" },
			count: 0,
			isActive: false,
		};

		const complexFields: CuiDetailField[] = [
			{ label: "姓名", prop: "name" },
			{ label: "标签", prop: "tags" },
			{ label: "元数据", prop: "metadata" },
			{ label: "计数", prop: "count" },
			{ label: "激活", prop: "isActive" },
		];

		const wrapper = mount(CuiDetail, {
			props: {
				fields: complexFields,
				data: complexData,
			},
		});

		expect(wrapper.exists()).toBe(true);
		const items = wrapper.findAll(".detail-item");
		expect(items.length).toBe(complexFields.length);
	});

	test("applies correct CSS classes", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: mockFields,
				data: mockData,
			},
		});

		expect(wrapper.classes()).toContain("cui-detail");
		expect(wrapper.find(".detail-grid").exists()).toBe(true);
		expect(wrapper.find(".detail-item").exists()).toBe(true);
		expect(wrapper.find(".detail-label").exists()).toBe(true);
		expect(wrapper.find(".detail-value").exists()).toBe(true);
	});

	test("handles render function with error gracefully", () => {
		const fieldsWithErrorRender: CuiDetailField[] = [
			{
				label: "姓名",
				prop: "name",
				render: (data) => {
					if (!data.name) return "无";
					return data.name;
				},
			},
		];

		const wrapper = mount(CuiDetail, {
			props: {
				fields: fieldsWithErrorRender,
				data: {},
			},
		});

		expect(wrapper.exists()).toBe(true);
		const value = wrapper.find(".detail-value");
		expect(value.text()).toBe("无");
	});

	test("renders with special characters in data", () => {
		const specialData = {
			name: '<script>alert("xss")</script>',
			email: "test@example.com & more",
			description: "Line 1\nLine 2\nLine 3",
		};

		const specialFields: CuiDetailField[] = [
			{ label: "姓名", prop: "name" },
			{ label: "邮箱", prop: "email" },
			{ label: "描述", prop: "description" },
		];

		const wrapper = mount(CuiDetail, {
			props: {
				fields: specialFields,
				data: specialData,
			},
		});

		expect(wrapper.exists()).toBe(true);
		const values = wrapper.findAll(".detail-value");
		expect(values.length).toBe(3);
	});
});
