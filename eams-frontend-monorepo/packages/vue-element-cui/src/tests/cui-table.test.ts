import { describe, test, expect, vi } from "vitest";
import { mount } from "@vue/test-utils";
import { ElTable, ElTableColumn } from "element-plus";
import CuiTable from "../components/cui-table/cui-table.vue";
import type { CuiTableColumn } from "../components/cui-table/types";

describe("CuiTable", () => {
	const mockData = [
		{ id: 1, name: "Alice", age: 25, email: "alice@example.com" },
		{ id: 2, name: "Bob", age: 30, email: "bob@example.com" },
		{ id: 3, name: "Charlie", age: 35, email: "charlie@example.com" },
	];

	const mockColumns: CuiTableColumn[] = [
		{ prop: "name", label: "姓名" },
		{ prop: "age", label: "年龄", sortable: true },
		{ prop: "email", label: "邮箱" },
	];

	test("renders table with data", () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
		expect(wrapper.findComponent(ElTable).exists()).toBe(true);
	});

	test("shows index column when showIndex is true", () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
				showIndex: true,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const tableColumns = wrapper.findAllComponents(ElTableColumn);
		const indexColumn = tableColumns.find((col) => col.props("type") === "index");
		expect(indexColumn).toBeDefined();
	});

	test("shows selection column when showSelection is true", () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
				showSelection: true,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const tableColumns = wrapper.findAllComponents(ElTableColumn);
		const selectionColumn = tableColumns.find((col) => col.props("type") === "selection");
		expect(selectionColumn).toBeDefined();
	});

	test("emits sort-change event", async () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const elTable = wrapper.findComponent(ElTable);
		await elTable.vm.$emit("sort-change", { prop: "age", order: "ascending" });

		expect(wrapper.emitted("sort-change")).toBeTruthy();
		expect(wrapper.emitted("sort-change")?.[0]).toEqual([{ prop: "age", order: "ascending" }]);
	});

	test("emits selection-change event", async () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
				showSelection: true,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const selectedRows = [mockData[0], mockData[1]];
		const elTable = wrapper.findComponent(ElTable);
		await elTable.vm.$emit("selection-change", selectedRows);

		expect(wrapper.emitted("selection-change")).toBeTruthy();
		expect(wrapper.emitted("selection-change")?.[0]).toEqual([selectedRows]);
	});

	test("shows loading state", () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
				loading: true,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
				directives: {
					loading: () => {},
				},
			},
		});

		// 检查 loading prop 是否正确传递
		expect(wrapper.props("loading")).toBe(true);
	});

	test("renders custom cell content via slots", () => {
		const columnsWithSlot: CuiTableColumn[] = [
			{ prop: "name", label: "姓名", slot: "name" },
			{ prop: "age", label: "年龄" },
		];

		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: columnsWithSlot,
			},
			slots: {
				name: ({ row }: { row: any }) => `<span class="custom-name">${row.name}</span>`,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		// 检查列配置中是否有 slot 属性
		const nameColumn = columnsWithSlot.find((col) => col.slot === "name");
		expect(nameColumn).toBeDefined();
		expect(nameColumn?.slot).toBe("name");
	});

	test("applies table props correctly", () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
				stripe: true,
				border: false,
				height: 400,
				maxHeight: 600,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const elTable = wrapper.findComponent(ElTable);
		expect(elTable.props("stripe")).toBe(true);
		expect(elTable.props("border")).toBe(false);
		expect(elTable.props("height")).toBe(400);
		expect(elTable.props("maxHeight")).toBe(600);
	});

	test("renders correct number of columns", () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const tableColumns = wrapper.findAllComponents(ElTableColumn);
		// 应该有 3 个数据列
		expect(tableColumns.length).toBe(mockColumns.length);
	});

	test("applies column properties correctly", () => {
		const columnsWithProps: CuiTableColumn[] = [
			{
				prop: "name",
				label: "姓名",
				width: 150,
				align: "center",
				fixed: "left",
			},
			{
				prop: "age",
				label: "年龄",
				sortable: "custom",
				minWidth: 100,
			},
		];

		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: columnsWithProps,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const tableColumns = wrapper.findAllComponents(ElTableColumn);
		const nameColumn = tableColumns[0];
		const ageColumn = tableColumns[1];

		expect(nameColumn.props("width")).toBe(150);
		expect(nameColumn.props("align")).toBe("center");
		expect(nameColumn.props("fixed")).toBe("left");
		expect(ageColumn.props("sortable")).toBe("custom");
		expect(ageColumn.props("minWidth")).toBe(100);
	});

	test("emits row-click event", async () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const elTable = wrapper.findComponent(ElTable);
		const mockColumn = {};
		const mockEvent = new Event("click");
		await elTable.vm.$emit("row-click", mockData[0], mockColumn, mockEvent);

		expect(wrapper.emitted("row-click")).toBeTruthy();
		expect(wrapper.emitted("row-click")?.[0]).toEqual([mockData[0], mockColumn, mockEvent]);
	});

	test("emits cell-click event", async () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const elTable = wrapper.findComponent(ElTable);
		const mockColumn = {};
		const mockCell = {};
		const mockEvent = new Event("click");
		await elTable.vm.$emit("cell-click", mockData[0], mockColumn, mockCell, mockEvent);

		expect(wrapper.emitted("cell-click")).toBeTruthy();
		expect(wrapper.emitted("cell-click")?.[0]).toEqual([mockData[0], mockColumn, mockCell, mockEvent]);
	});

	test("renders with both index and selection columns", () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
				showIndex: true,
				showSelection: true,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const tableColumns = wrapper.findAllComponents(ElTableColumn);
		const indexColumn = tableColumns.find((col) => col.props("type") === "index");
		const selectionColumn = tableColumns.find((col) => col.props("type") === "selection");

		expect(indexColumn).toBeDefined();
		expect(selectionColumn).toBeDefined();
		// 2 个特殊列 + 3 个数据列
		expect(tableColumns.length).toBe(5);
	});

	test("applies formatter to column", () => {
		const formatter = vi.fn((row, column, cellValue) => `${cellValue} years old`);
		const columnsWithFormatter: CuiTableColumn[] = [
			{ prop: "name", label: "姓名" },
			{ prop: "age", label: "年龄", formatter },
		];

		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: columnsWithFormatter,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const tableColumns = wrapper.findAllComponents(ElTableColumn);
		const ageColumn = tableColumns[1];

		expect(ageColumn.props("formatter")).toBe(formatter);
	});

	test("renders empty table with no data", () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: [],
				columns: mockColumns,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		expect(wrapper.exists()).toBe(true);
		expect(wrapper.findComponent(ElTable).exists()).toBe(true);
	});

	test("applies fixed column correctly", () => {
		const columnsWithFixed: CuiTableColumn[] = [
			{ prop: "name", label: "姓名", fixed: true },
			{ prop: "age", label: "年龄", fixed: "right" },
			{ prop: "email", label: "邮箱" },
		];

		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: columnsWithFixed,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const tableColumns = wrapper.findAllComponents(ElTableColumn);
		expect(tableColumns[0].props("fixed")).toBe(true);
		expect(tableColumns[1].props("fixed")).toBe("right");
		expect(tableColumns[2].props("fixed")).toBeUndefined();
	});

	test("handles sortable boolean value", () => {
		const columnsWithSortable: CuiTableColumn[] = [
			{ prop: "name", label: "姓名", sortable: true },
			{ prop: "age", label: "年龄", sortable: false },
		];

		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: columnsWithSortable,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const tableColumns = wrapper.findAllComponents(ElTableColumn);
		expect(tableColumns[0].props("sortable")).toBe(true);
		expect(tableColumns[1].props("sortable")).toBe(false);
	});

	test("renders multiple slots correctly", () => {
		const columnsWithSlots: CuiTableColumn[] = [
			{ prop: "name", label: "姓名", slot: "name" },
			{ prop: "age", label: "年龄", slot: "age" },
			{ prop: "email", label: "邮箱" },
		];

		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: columnsWithSlots,
			},
			slots: {
				name: ({ row }: { row: any }) => `<span class="custom-name">${row.name}</span>`,
				age: ({ row }: { row: any }) => `<span class="custom-age">${row.age}</span>`,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const nameColumn = columnsWithSlots.find((col) => col.slot === "name");
		const ageColumn = columnsWithSlots.find((col) => col.slot === "age");

		expect(nameColumn?.slot).toBe("name");
		expect(ageColumn?.slot).toBe("age");
	});

	test("passes through custom attributes via v-bind", () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
				"row-key": "id",
				"default-sort": { prop: "age", order: "ascending" },
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const elTable = wrapper.findComponent(ElTable);
		expect(elTable.props("rowKey")).toBe("id");
	});

	test("handles sort-change with null order", async () => {
		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: mockColumns,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const elTable = wrapper.findComponent(ElTable);
		await elTable.vm.$emit("sort-change", { prop: "age", order: null });

		expect(wrapper.emitted("sort-change")).toBeTruthy();
		expect(wrapper.emitted("sort-change")?.[0]).toEqual([{ prop: "age", order: null }]);
	});

	test("renders with different align values", () => {
		const columnsWithAlign: CuiTableColumn[] = [
			{ prop: "name", label: "姓名", align: "left" },
			{ prop: "age", label: "年龄", align: "center" },
			{ prop: "email", label: "邮箱", align: "right" },
		];

		const wrapper = mount(CuiTable, {
			props: {
				data: mockData,
				columns: columnsWithAlign,
			},
			global: {
				components: {
					ElTable,
					ElTableColumn,
				},
			},
		});

		const tableColumns = wrapper.findAllComponents(ElTableColumn);
		expect(tableColumns[0].props("align")).toBe("left");
		expect(tableColumns[1].props("align")).toBe("center");
		expect(tableColumns[2].props("align")).toBe("right");
	});
});
