import type { ParamOption } from "@/stores/systemParam";

type OptionLike = Pick<ParamOption, "code" | "name" | "info" | "value" | "valueType">;

export function buildOptionMeta(option: Pick<ParamOption, "name" | "info">) {
	return {
		displayName: `* ${option.name}`,
		infoLines: String(option.info ?? "")
			.split(/\r?\n/)
			.map((line) => line.trim())
			.filter(Boolean),
	};
}

export function getOptionEditorKind(option: OptionLike) {
	const valueType = option.valueType?.toLowerCase?.() ?? "";
	const code = option.code?.toLowerCase?.() ?? "";
	const name = option.name ?? "";
	const info = option.info ?? "";
	const primitiveValue = String(option.value ?? "").toLowerCase();

	if (["bool", "boolean", "switch", "checkbox"].includes(valueType)) {
		return "switch" as const;
	}

	const looksBinaryValue = ["0", "1", "true", "false"].includes(primitiveValue);
	const looksLikeToggleField =
		/^(是否|开启|启用|允许|自动)/.test(name) ||
		/(开启|启用|自动|switch|enable|status|mask|anonymous)/i.test(`${code} ${info}`);

	return looksBinaryValue && looksLikeToggleField ? ("switch" as const) : ("input" as const);
}

export function normalizeSubmitValue(option: OptionLike, rawValue: string | boolean) {
	if (getOptionEditorKind(option) === "switch") {
		if (option.valueType?.toLowerCase?.() === "boolean" || typeof option.value === "boolean") {
			return Boolean(rawValue);
		}

		return rawValue ? 1 : 0;
	}

	if (
		["int", "integer", "long", "number", "float", "double", "decimal"].includes(option.valueType?.toLowerCase?.() ?? "")
	) {
		if (rawValue === "") {
			return "";
		}

		const parsedValue = Number(rawValue);
		return Number.isNaN(parsedValue) ? String(rawValue) : parsedValue;
	}

	return String(rawValue);
}
