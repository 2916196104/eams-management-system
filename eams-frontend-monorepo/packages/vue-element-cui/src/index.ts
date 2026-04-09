// Vue Element CUI - 主入口文件
import type { App, Plugin } from "vue";
import {
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
} from "./components";

// 导出版本号
export const version: string = "1.0.0";

// 导出安装函数
export function install(app: App): void {
	// 注册组件
	app.component("CuiTable", CuiTable);
	app.component("CuiForm", CuiForm);
	app.component("CuiSearch", CuiSearch);
	app.component("CuiDialog", CuiDialog);
	app.component("CuiDialogForm", CuiDialogForm);
	app.component("CuiDetail", CuiDetail);
	app.component("CuiTab", CuiTab);
	app.component("CuiExcel", CuiExcel);
	app.component("CuiSelectBox", CuiSelectBox);
	app.component("CuiSelect", CuiSelect);
	app.component("CuiSelectEnum", CuiSelectEnum);
	app.component("CuiSelectDict", CuiSelectDict);
	app.component("CuiRadioEnum", CuiRadioEnum);
	app.component("CuiRadioDict", CuiRadioDict);
	app.component("CuiCheckboxEnum", CuiCheckboxEnum);
	app.component("CuiAutocomplete", CuiAutocomplete);
	console.log(`@eams-monorepo/vue-element-cui v${version} installed`);
}

// 默认导出
const plugin: Plugin & { version: string } = {
	version: version,
	install: install,
};

export default plugin;

// 组件导出
export * from "./components";
