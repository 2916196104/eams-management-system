import { describe, test, expectTypeOf } from "vitest";
import type {
	CuiTableProps,
	CuiTableColumn,
	SortChangeEvent,
	SelectionChangeEvent,
	CuiFormProps,
	CuiFormField,
	CuiFormFieldType,
	CuiFormSelectOption,
	CuiFormValidateResult,
	CuiSearchProps,
	CuiSearchField,
	CuiDialogProps,
	CuiDialogEmits,
	CuiDialogFormProps,
	CuiDialogFormEmits,
	CuiDetailProps,
	CuiDetailField,
	CuiTabProps,
	CuiTabItem,
	CuiExcelProps,
	CuiExcelEmits,
	CuiSelectBoxProps,
	CuiSelectBoxEmits,
	CuiSelectBoxOption,
	CuiSelectProps,
	CuiSelectEmits,
	CuiSelectOption,
	CuiSelectEnumProps,
	CuiSelectEnumEmits,
	CuiSelectDictProps,
	CuiSelectDictEmits,
	CuiRadioEnumProps,
	CuiRadioEnumEmits,
	CuiRadioDictProps,
	CuiRadioDictEmits,
	CuiCheckboxEnumProps,
	CuiCheckboxEnumEmits,
	CuiAutocompleteProps,
	CuiAutocompleteEmits,
	CuiAutocompleteSuggestion,
} from "../components";

describe("CuiTable 类型测试", () => {
	test("CuiTableProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiTableProps>().toHaveProperty("data");
		expectTypeOf<CuiTableProps>().toHaveProperty("columns");
		expectTypeOf<CuiTableProps["data"]>().toEqualTypeOf<any[]>();
		expectTypeOf<CuiTableProps["loading"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiTableProps["showIndex"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiTableProps["showSelection"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiTableProps["stripe"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiTableProps["border"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiTableColumn 泛型应正确约束 formatter", () => {
		type UserColumn = CuiTableColumn<{ name: string; age: number }>;
		expectTypeOf<UserColumn>().toHaveProperty("prop");
		expectTypeOf<UserColumn>().toHaveProperty("label");
		expectTypeOf<UserColumn["sortable"]>().toEqualTypeOf<boolean | "custom" | undefined>();
		expectTypeOf<UserColumn["fixed"]>().toEqualTypeOf<boolean | "left" | "right" | undefined>();
	});

	test("CuiTableProps 泛型应正确传递到 columns", () => {
		type UserTableProps = CuiTableProps<{ name: string }>;
		expectTypeOf<UserTableProps["data"]>().toEqualTypeOf<{ name: string }[]>();
		expectTypeOf<UserTableProps["columns"]>().toEqualTypeOf<CuiTableColumn<{ name: string }>[]>();
	});

	test("SortChangeEvent 应包含正确的属性", () => {
		expectTypeOf<SortChangeEvent>().toHaveProperty("prop");
		expectTypeOf<SortChangeEvent>().toHaveProperty("order");
		expectTypeOf<SortChangeEvent["prop"]>().toEqualTypeOf<string>();
	});

	test("SelectionChangeEvent 应为泛型数组", () => {
		expectTypeOf<SelectionChangeEvent<{ id: number }>>().toEqualTypeOf<{ id: number }[]>();
	});
});

describe("CuiForm 类型测试", () => {
	test("CuiFormProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiFormProps>().toHaveProperty("fields");
		expectTypeOf<CuiFormProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiFormProps["labelWidth"]>().toEqualTypeOf<string | number | undefined>();
		expectTypeOf<CuiFormProps["inline"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiFormProps["disabled"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiFormField 泛型应约束 prop 为对象的 key", () => {
		type UserField = CuiFormField<{ name: string; age: number }>;
		expectTypeOf<UserField["prop"]>().toEqualTypeOf<"name" | "age">();
	});

	test("CuiFormFieldType 应为联合类型", () => {
		expectTypeOf<CuiFormFieldType>().toEqualTypeOf<"input" | "select" | "date" | "textarea" | "number">();
	});

	test("CuiFormSelectOption 应包含 label 和 value", () => {
		expectTypeOf<CuiFormSelectOption>().toHaveProperty("label");
		expectTypeOf<CuiFormSelectOption>().toHaveProperty("value");
		expectTypeOf<CuiFormSelectOption["disabled"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiFormValidateResult 应包含验证结果", () => {
		expectTypeOf<CuiFormValidateResult>().toHaveProperty("valid");
		expectTypeOf<CuiFormValidateResult["valid"]>().toEqualTypeOf<boolean>();
	});
});

describe("CuiSearch 类型测试", () => {
	test("CuiSearchProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiSearchProps>().toHaveProperty("fields");
		expectTypeOf<CuiSearchProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiSearchProps["inline"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiSearchProps["collapsible"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiSearchField 应包含正确的字段类型", () => {
		expectTypeOf<CuiSearchField>().toHaveProperty("prop");
		expectTypeOf<CuiSearchField>().toHaveProperty("label");
		expectTypeOf<CuiSearchField>().toHaveProperty("type");
		expectTypeOf<CuiSearchField["advanced"]>().toEqualTypeOf<boolean | undefined>();
	});
});

describe("CuiDialog 类型测试", () => {
	test("CuiDialogProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiDialogProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiDialogProps["modelValue"]>().toEqualTypeOf<boolean>();
		expectTypeOf<CuiDialogProps["title"]>().toEqualTypeOf<string | undefined>();
		expectTypeOf<CuiDialogProps["width"]>().toEqualTypeOf<string | number | undefined>();
		expectTypeOf<CuiDialogProps["showClose"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiDialogProps["showFooter"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiDialogProps["loading"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiDialogEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiDialogEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiDialogEmits>().toHaveProperty("confirm");
		expectTypeOf<CuiDialogEmits>().toHaveProperty("cancel");
		expectTypeOf<CuiDialogEmits>().toHaveProperty("open");
		expectTypeOf<CuiDialogEmits>().toHaveProperty("close");
	});
});

describe("CuiDialogForm 类型测试", () => {
	test("CuiDialogFormProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiDialogFormProps>().toHaveProperty("visible");
		expectTypeOf<CuiDialogFormProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiDialogFormProps>().toHaveProperty("fields");
		expectTypeOf<CuiDialogFormProps["title"]>().toEqualTypeOf<string | undefined>();
		expectTypeOf<CuiDialogFormProps["width"]>().toEqualTypeOf<string | number | undefined>();
	});

	test("CuiDialogFormProps 泛型应正确传递", () => {
		type UserDialogForm = CuiDialogFormProps<{ name: string }>;
		expectTypeOf<UserDialogForm["modelValue"]>().toEqualTypeOf<{ name: string }>();
	});

	test("CuiDialogFormEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiDialogFormEmits>().toHaveProperty("update:visible");
		expectTypeOf<CuiDialogFormEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiDialogFormEmits>().toHaveProperty("submit");
		expectTypeOf<CuiDialogFormEmits>().toHaveProperty("cancel");
	});
});

describe("CuiDetail 类型测试", () => {
	test("CuiDetailProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiDetailProps>().toHaveProperty("fields");
		expectTypeOf<CuiDetailProps>().toHaveProperty("data");
		expectTypeOf<CuiDetailProps["labelWidth"]>().toEqualTypeOf<string | undefined>();
		expectTypeOf<CuiDetailProps["columns"]>().toEqualTypeOf<number | undefined>();
	});

	test("CuiDetailField 应包含正确的属性", () => {
		expectTypeOf<CuiDetailField>().toHaveProperty("label");
		expectTypeOf<CuiDetailField>().toHaveProperty("prop");
		expectTypeOf<CuiDetailField["width"]>().toEqualTypeOf<string | undefined>();
	});
});

describe("CuiTab 类型测试", () => {
	test("CuiTabProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiTabProps>().toHaveProperty("tabs");
		expectTypeOf<CuiTabProps>().toHaveProperty("activeTab");
		expectTypeOf<CuiTabProps["activeTab"]>().toEqualTypeOf<string>();
		expectTypeOf<CuiTabProps["closable"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiTabProps["addable"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiTabItem 应包含正确的属性", () => {
		expectTypeOf<CuiTabItem>().toHaveProperty("label");
		expectTypeOf<CuiTabItem>().toHaveProperty("name");
		expectTypeOf<CuiTabItem["disabled"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiTabItem["closable"]>().toEqualTypeOf<boolean | undefined>();
	});
});

describe("CuiExcel 类型测试", () => {
	test("CuiExcelProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiExcelProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiExcelProps>().toHaveProperty("uploadUrl");
		expectTypeOf<CuiExcelProps["modelValue"]>().toEqualTypeOf<boolean>();
		expectTypeOf<CuiExcelProps["uploadUrl"]>().toEqualTypeOf<string>();
		expectTypeOf<CuiExcelProps["templateUrl"]>().toEqualTypeOf<string | undefined>();
	});

	test("CuiExcelEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiExcelEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiExcelEmits>().toHaveProperty("success");
		expectTypeOf<CuiExcelEmits>().toHaveProperty("error");
	});
});

describe("CuiSelectBox 类型测试", () => {
	test("CuiSelectBoxProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiSelectBoxProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiSelectBoxProps>().toHaveProperty("type");
		expectTypeOf<CuiSelectBoxProps["modelValue"]>().toEqualTypeOf<string | string[]>();
		expectTypeOf<CuiSelectBoxProps["type"]>().toEqualTypeOf<string>();
		expectTypeOf<CuiSelectBoxProps["limit"]>().toEqualTypeOf<number | undefined>();
		expectTypeOf<CuiSelectBoxProps["disabled"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiSelectBoxOption 应包含 id 和 label", () => {
		expectTypeOf<CuiSelectBoxOption>().toHaveProperty("id");
		expectTypeOf<CuiSelectBoxOption>().toHaveProperty("label");
		expectTypeOf<CuiSelectBoxOption["id"]>().toEqualTypeOf<string | number>();
	});

	test("CuiSelectBoxEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiSelectBoxEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiSelectBoxEmits>().toHaveProperty("submit");
	});
});

describe("CuiSelect 类型测试", () => {
	test("CuiSelectProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiSelectProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiSelectProps["placeholder"]>().toEqualTypeOf<string | undefined>();
		expectTypeOf<CuiSelectProps["disabled"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiSelectProps["clearable"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiSelectProps["filterable"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiSelectProps["remote"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiSelectProps["loading"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiSelectOption 应包含 label 和 value", () => {
		expectTypeOf<CuiSelectOption>().toHaveProperty("label");
		expectTypeOf<CuiSelectOption>().toHaveProperty("value");
		expectTypeOf<CuiSelectOption["disabled"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiSelectEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiSelectEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiSelectEmits>().toHaveProperty("change");
	});
});

describe("CuiSelectEnum 类型测试", () => {
	test("CuiSelectEnumProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiSelectEnumProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiSelectEnumProps>().toHaveProperty("enumCode");
		expectTypeOf<CuiSelectEnumProps["enumCode"]>().toEqualTypeOf<string>();
		expectTypeOf<CuiSelectEnumProps["placeholder"]>().toEqualTypeOf<string | undefined>();
		expectTypeOf<CuiSelectEnumProps["clearable"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiSelectEnumProps["filterable"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiSelectEnumEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiSelectEnumEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiSelectEnumEmits>().toHaveProperty("change");
	});
});

describe("CuiSelectDict 类型测试", () => {
	test("CuiSelectDictProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiSelectDictProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiSelectDictProps>().toHaveProperty("dictCode");
		expectTypeOf<CuiSelectDictProps["dictCode"]>().toEqualTypeOf<string>();
		expectTypeOf<CuiSelectDictProps["placeholder"]>().toEqualTypeOf<string | undefined>();
		expectTypeOf<CuiSelectDictProps["clearable"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiSelectDictProps["filterable"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiSelectDictEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiSelectDictEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiSelectDictEmits>().toHaveProperty("change");
	});
});

describe("CuiRadioEnum 类型测试", () => {
	test("CuiRadioEnumProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiRadioEnumProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiRadioEnumProps>().toHaveProperty("enumCode");
		expectTypeOf<CuiRadioEnumProps["enumCode"]>().toEqualTypeOf<string>();
		expectTypeOf<CuiRadioEnumProps["disabled"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiRadioEnumEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiRadioEnumEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiRadioEnumEmits>().toHaveProperty("change");
	});
});

describe("CuiRadioDict 类型测试", () => {
	test("CuiRadioDictProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiRadioDictProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiRadioDictProps>().toHaveProperty("dictCode");
		expectTypeOf<CuiRadioDictProps["dictCode"]>().toEqualTypeOf<string>();
		expectTypeOf<CuiRadioDictProps["disabled"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiRadioDictEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiRadioDictEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiRadioDictEmits>().toHaveProperty("change");
	});
});

describe("CuiCheckboxEnum 类型测试", () => {
	test("CuiCheckboxEnumProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiCheckboxEnumProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiCheckboxEnumProps>().toHaveProperty("enumCode");
		expectTypeOf<CuiCheckboxEnumProps["enumCode"]>().toEqualTypeOf<string>();
		expectTypeOf<CuiCheckboxEnumProps["disabled"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiCheckboxEnumProps["modelValue"]>().toEqualTypeOf<any[]>();
	});

	test("CuiCheckboxEnumEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiCheckboxEnumEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiCheckboxEnumEmits>().toHaveProperty("change");
	});
});

describe("CuiAutocomplete 类型测试", () => {
	test("CuiAutocompleteProps 应包含正确的属性类型", () => {
		expectTypeOf<CuiAutocompleteProps>().toHaveProperty("modelValue");
		expectTypeOf<CuiAutocompleteProps["modelValue"]>().toEqualTypeOf<string>();
		expectTypeOf<CuiAutocompleteProps["placeholder"]>().toEqualTypeOf<string | undefined>();
		expectTypeOf<CuiAutocompleteProps["disabled"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiAutocompleteProps["clearable"]>().toEqualTypeOf<boolean | undefined>();
		expectTypeOf<CuiAutocompleteProps["debounce"]>().toEqualTypeOf<number | undefined>();
		expectTypeOf<CuiAutocompleteProps["triggerOnFocus"]>().toEqualTypeOf<boolean | undefined>();
	});

	test("CuiAutocompleteEmits 应包含正确的事件类型", () => {
		expectTypeOf<CuiAutocompleteEmits>().toHaveProperty("update:modelValue");
		expectTypeOf<CuiAutocompleteEmits>().toHaveProperty("select");
	});

	test("CuiAutocompleteSuggestion 应包含 value 属性", () => {
		expectTypeOf<CuiAutocompleteSuggestion>().toHaveProperty("value");
		expectTypeOf<CuiAutocompleteSuggestion["value"]>().toEqualTypeOf<string>();
	});
});
