import { describe, test, expect } from "vitest";
import { mount } from "@vue/test-utils";
import CuiDetail from "./cui-detail.vue";

describe("CuiDetail", () => {
	const defaultProps = {
		fields: [
			{ label: "Name", prop: "name" },
			{ label: "Email", prop: "email" },
			{ label: "Age", prop: "age" },
		],
		data: {
			name: "John Doe",
			email: "john@example.com",
			age: 30,
		},
	};

	test("renders detail items", () => {
		const wrapper = mount(CuiDetail, {
			props: defaultProps,
		});

		expect(wrapper.find(".cui-detail").exists()).toBe(true);
		expect(wrapper.findAll(".detail-item")).toHaveLength(3);
	});

	test("displays field labels and values", () => {
		const wrapper = mount(CuiDetail, {
			props: defaultProps,
		});

		const items = wrapper.findAll(".detail-item");
		expect(items[0].text()).toContain("Name:");
		expect(items[0].text()).toContain("John Doe");
	});

	test("respects custom label width", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				...defaultProps,
				labelWidth: "200px",
			},
		});

		const label = wrapper.find(".detail-label");
		expect(label.attributes("style")).toContain("width: 200px");
	});

	test("respects custom columns", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				...defaultProps,
				columns: 3,
			},
		});

		const grid = wrapper.find(".detail-grid");
		expect(grid.attributes("style")).toContain("grid-template-columns: repeat(3, 1fr)");
	});

	test("renders custom render function", () => {
		const wrapper = mount(CuiDetail, {
			props: {
				fields: [
					{
						label: "Name",
						prop: "name",
						render: (row: any) => `${row.name.toUpperCase()}`,
					},
				],
				data: { name: "john" },
			},
		});

		expect(wrapper.text()).toContain("JOHN");
	});
});
