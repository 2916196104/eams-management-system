import { describe, expect, test } from "vitest";
import { mount } from "@vue/test-utils";

import ApiTable from "../../components/content/ApiTable.vue";

describe("ApiTable", () => {
	test("renders heading and slot content", () => {
		const wrapper = mount(ApiTable, {
			props: {
				title: "Props",
				description: "组件属性说明",
			},
			slots: {
				default: "<table><tbody><tr><td>data</td><td>表格数据</td></tr></tbody></table>",
			},
		});

		expect(wrapper.text()).toContain("Props");
		expect(wrapper.text()).toContain("组件属性说明");
		expect(wrapper.find("table").exists()).toBe(true);
		expect(wrapper.text()).toContain("表格数据");
	});
});
