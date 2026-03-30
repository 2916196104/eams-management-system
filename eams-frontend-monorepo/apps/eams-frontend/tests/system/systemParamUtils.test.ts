import { describe, expect, test } from "vitest";
import { buildOptionMeta, getOptionEditorKind, normalizeSubmitValue } from "../../src/views/system/systemParam.utils";

describe("systemParam utils", () => {
	test("buildOptionMeta 会保留名称前缀并拆分多行说明", () => {
		const meta = buildOptionMeta({
			name: "是否脱敏学生的手机号",
			info: "为保护客户资源，开启后手机号将被脱敏处理。\n仅管理员可查看完整号码",
		});

		expect(meta.displayName).toBe("* 是否脱敏学生的手机号");
		expect(meta.infoLines).toEqual(["为保护客户资源，开启后手机号将被脱敏处理。", "仅管理员可查看完整号码"]);
	});

	test("getOptionEditorKind 能识别开关与文本输入", () => {
		expect(
			getOptionEditorKind({
				code: "mask_mobile",
				name: "是否脱敏学生的手机号",
				info: "开启后手机号脱敏",
				value: 1,
				valueType: "int",
			}),
		).toBe("switch");

		expect(
			getOptionEditorKind({
				code: "parent_default_password",
				name: "家长端初始密码",
				info: "添加学生时的默认登录密码",
				value: "123456",
				valueType: "string",
			}),
		).toBe("input");
	});

	test("normalizeSubmitValue 会按字段类型转换提交值", () => {
		expect(
			normalizeSubmitValue(
				{
					code: "auto_assign_class",
					name: "报名1V1课程时自动生成班级",
					info: "",
					value: 0,
					valueType: "int",
				},
				true,
			),
		).toBe(1);

		expect(
			normalizeSubmitValue(
				{
					code: "refund_hours",
					name: "在线支付后可申请退款的小时数(0表示不限时)",
					info: "",
					value: "0",
					valueType: "number",
				},
				"24",
			),
		).toBe(24);
	});
});
