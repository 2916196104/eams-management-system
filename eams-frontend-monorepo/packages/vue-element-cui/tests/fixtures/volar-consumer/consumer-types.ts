import type { Component } from "vue";
import VueElementCui, {
	install,
	version,
	CuiAutocomplete,
	CuiCheckboxEnum,
	CuiDetail,
	CuiDialog,
	CuiDialogForm,
	CuiExcel,
	CuiForm,
	CuiRadioDict,
	CuiRadioEnum,
	CuiSearch,
	CuiSelect,
	CuiSelectBox,
	CuiSelectDict,
	CuiSelectEnum,
	CuiTab,
	CuiTable,
} from "@eams-monorepo/vue-element-cui";
import {
	VueElementCuiAutoImportResolver,
	VueElementCuiResolver,
	vueElementCuiImports,
	vueElementCuiTypeImports,
} from "@eams-monorepo/vue-element-cui/resolver";
import type {
	CuiAutocompleteProps,
	CuiAutocompleteSuggestion,
	CuiCheckboxEnumProps,
	CuiDetailField,
	CuiDetailProps,
	CuiDialogFormProps,
	CuiDialogProps,
	CuiExcelProps,
	CuiFormField,
	CuiFormProps,
	CuiRadioDictProps,
	CuiRadioEnumProps,
	CuiSearchField,
	CuiSearchProps,
	CuiSelectBoxOption,
	CuiSelectBoxProps,
	CuiSelectDictProps,
	CuiSelectEnumProps,
	CuiSelectOption,
	CuiSelectProps,
	CuiTabItem,
	CuiTabProps,
	CuiTableColumn,
	CuiTableProps,
} from "@eams-monorepo/vue-element-cui";

type Row = {
	id: number;
	name: string;
	status: "enabled" | "disabled";
};

const tableColumns: CuiTableColumn<Row>[] = [
	{ prop: "name", label: "名称" },
	{ prop: "status", label: "状态", sortable: true },
];

const tableProps: CuiTableProps<Row> = {
	data: [{ id: 1, name: "固定资产", status: "enabled" }],
	columns: tableColumns,
	border: true,
};

const formFields: CuiFormField<Row>[] = [{ prop: "name", label: "名称", type: "input" }];

const formProps: CuiFormProps<Row> = {
	modelValue: { id: 1, name: "固定资产", status: "enabled" },
	fields: formFields,
};

const searchFields: CuiSearchField[] = [{ prop: "name", label: "名称", type: "input" }];

const searchProps: CuiSearchProps = {
	modelValue: { id: 1, name: "固定资产", status: "enabled" },
	fields: searchFields,
};

const detailFields: CuiDetailField[] = [{ prop: "name", label: "名称" }];

const detailProps: CuiDetailProps = {
	data: { id: 1, name: "固定资产", status: "enabled" },
	fields: detailFields,
};

const tabProps: CuiTabProps = {
	activeTab: "base",
	tabs: [{ label: "基础信息", name: "base" } satisfies CuiTabItem],
};

const excelProps: CuiExcelProps = {
	modelValue: false,
	uploadUrl: "/api/import",
};

const dialogProps: CuiDialogProps = {
	modelValue: false,
	title: "编辑",
};

const dialogFormProps: CuiDialogFormProps<Row> = {
	visible: true,
	modelValue: { id: 1, name: "固定资产", status: "enabled" },
	fields: formFields,
};

const selectOptions: CuiSelectOption[] = [{ label: "启用", value: "enabled" }];
const selectProps: CuiSelectProps = { modelValue: "enabled", options: selectOptions };
const selectEnumProps: CuiSelectEnumProps = { modelValue: "enabled", enumCode: "asset_status" };
const selectDictProps: CuiSelectDictProps = { modelValue: "enabled", dictCode: "asset_status" };
const radioEnumProps: CuiRadioEnumProps = { modelValue: "enabled", enumCode: "asset_status" };
const radioDictProps: CuiRadioDictProps = { modelValue: "enabled", dictCode: "asset_status" };
const checkboxEnumProps: CuiCheckboxEnumProps = { modelValue: ["enabled"], enumCode: "asset_status" };
const selectBoxProps: CuiSelectBoxProps = {
	modelValue: "1",
	type: "single",
	condition: { keyword: "资产" },
};

const selectBoxOption: CuiSelectBoxOption = { id: 1, label: "资产 A" };

const autocompleteSuggestions: CuiAutocompleteSuggestion[] = [{ value: "固定资产" }];
const autocompleteProps: CuiAutocompleteProps = {
	modelValue: "固定",
	fetchSuggestions: async () => autocompleteSuggestions,
};

const registry: Record<string, Component> = {
	CuiTable,
	CuiForm,
	CuiSearch,
	CuiDialog,
	CuiDialogForm,
	CuiDetail,
	CuiTab,
	CuiExcel,
	CuiSelectBox,
	CuiSelect,
	CuiSelectEnum,
	CuiSelectDict,
	CuiRadioEnum,
	CuiRadioDict,
	CuiCheckboxEnum,
	CuiAutocomplete,
};

const pluginVersion: string = VueElementCui.version;
const componentResolver = VueElementCuiResolver();
const autoImportResolver = VueElementCuiAutoImportResolver();
const importsPreset = vueElementCuiImports;
const typeImportsSource = vueElementCuiTypeImports[0]?.from;
const resolvedComponent = componentResolver("CuiTable");
const resolvedAutoImport = autoImportResolver("version");

void registry;
void install;
void version;
void pluginVersion;
void tableProps;
void formProps;
void searchProps;
void detailProps;
void tabProps;
void excelProps;
void dialogProps;
void dialogFormProps;
void selectProps;
void selectEnumProps;
void selectDictProps;
void radioEnumProps;
void radioDictProps;
void checkboxEnumProps;
void selectBoxProps;
void selectBoxOption;
void autocompleteProps;
void componentResolver;
void autoImportResolver;
void importsPreset;
void typeImportsSource;
void resolvedComponent;
void resolvedAutoImport;
