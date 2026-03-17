// Volar 全局组件类型声明
// 用于在 Vue 3 + TypeScript 项目中提供组件类型提示

import type { DefineComponent } from "vue";
import type { CuiTableProps } from "./components/cui-table/types";
import type { CuiFormProps } from "./components/cui-form/types";
import type { CuiSearchProps } from "./components/cui-search/types";
import type { CuiDialogProps } from "./components/cui-dialog/types";
import type { CuiDialogFormProps } from "./components/cui-dialog-form/types";
import type { CuiDetailProps } from "./components/cui-detail/types";
import type { CuiTabProps } from "./components/cui-tab/types";
import type { CuiExcelProps } from "./components/cui-excel/types";
import type { CuiSelectBoxProps } from "./components/cui-select-box/types";
import type { CuiSelectProps } from "./components/cui-select/types";
import type { CuiSelectEnumProps } from "./components/cui-select-enum/types";
import type { CuiSelectDictProps } from "./components/cui-select-dict/types";
import type { CuiRadioEnumProps } from "./components/cui-radio-enum/types";
import type { CuiRadioDictProps } from "./components/cui-radio-dict/types";
import type { CuiCheckboxEnumProps } from "./components/cui-checkbox-enum/types";
import type { CuiAutocompleteProps } from "./components/cui-autocomplete/types";

declare module "@vue/runtime-core" {
	export interface GlobalComponents {
		CuiTable: DefineComponent<CuiTableProps, {}, any>;
		CuiForm: DefineComponent<CuiFormProps, {}, any>;
		CuiSearch: DefineComponent<CuiSearchProps, {}, any>;
		CuiDialog: DefineComponent<CuiDialogProps, {}, any>;
		CuiDialogForm: DefineComponent<CuiDialogFormProps, {}, any>;
		CuiDetail: DefineComponent<CuiDetailProps, {}, any>;
		CuiTab: DefineComponent<CuiTabProps, {}, any>;
		CuiExcel: DefineComponent<CuiExcelProps, {}, any>;
		CuiSelectBox: DefineComponent<CuiSelectBoxProps, {}, any>;
		CuiSelect: DefineComponent<CuiSelectProps, {}, any>;
		CuiSelectEnum: DefineComponent<CuiSelectEnumProps, {}, any>;
		CuiSelectDict: DefineComponent<CuiSelectDictProps, {}, any>;
		CuiRadioEnum: DefineComponent<CuiRadioEnumProps, {}, any>;
		CuiRadioDict: DefineComponent<CuiRadioDictProps, {}, any>;
		CuiCheckboxEnum: DefineComponent<CuiCheckboxEnumProps, {}, any>;
		CuiAutocomplete: DefineComponent<CuiAutocompleteProps, {}, any>;
	}
}

export {};
