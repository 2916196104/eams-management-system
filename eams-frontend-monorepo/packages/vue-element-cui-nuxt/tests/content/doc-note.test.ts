import { describe, expect, test } from "vitest";
import { mount } from "@vue/test-utils";

import DocNote from "../../components/content/DocNote.vue";

describe("DocNote", () => {
	test("renders warning tone and note copy", () => {
		const wrapper = mount(DocNote, {
			props: {
				title: "迁移提示",
				tone: "warning",
			},
			slots: {
				default: "旧路径不会继续保留。",
			},
		});

		expect(wrapper.text()).toContain("迁移提示");
		expect(wrapper.text()).toContain("旧路径不会继续保留。");
		expect(wrapper.attributes("data-tone")).toBe("warning");
	});
});
