const PACKAGE_NAME = "@eams-monorepo/vue-element-cui";
const STYLE_ENTRY = `${PACKAGE_NAME}/styles`;

type Awaitable<T> = T | PromiseLike<T>;

export type VueElementCuiSideEffects = string | string[] | undefined;

export interface VueElementCuiComponentInfo {
	as?: string;
	name?: string;
	from: string;
	sideEffects?: VueElementCuiSideEffects;
}

export type VueElementCuiComponentResolverResult = string | VueElementCuiComponentInfo | null | undefined | void;

export type VueElementCuiComponentResolver = (name: string) => Awaitable<VueElementCuiComponentResolverResult>;

export interface VueElementCuiImportsMap {
	[moduleName: string]: Array<string | [from: string, alias: string]>;
}

export interface VueElementCuiTypeImport {
	from: string;
	imports: string[];
	type: true;
}

export const vueElementCuiComponentNames = [
	"CuiTable",
	"CuiForm",
	"CuiSearch",
	"CuiDialog",
	"CuiDialogForm",
	"CuiDetail",
	"CuiTab",
	"CuiExcel",
	"CuiSelectBox",
	"CuiSelect",
	"CuiSelectEnum",
	"CuiSelectDict",
	"CuiRadioEnum",
	"CuiRadioDict",
	"CuiCheckboxEnum",
	"CuiAutocomplete",
] as const;

export const vueElementCuiRuntimeExports = ["install", "version", ...vueElementCuiComponentNames] as const;

export const vueElementCuiTypeExportNames = [
	"CuiTableProps",
	"CuiTableColumn",
	"SortChangeEvent",
	"SelectionChangeEvent",
	"CuiFormProps",
	"CuiFormField",
	"CuiFormFieldType",
	"CuiFormSelectOption",
	"CuiFormValidateResult",
	"CuiSearchProps",
	"CuiSearchField",
	"CuiDialogProps",
	"CuiDialogEmits",
	"CuiDialogFormProps",
	"CuiDialogFormEmits",
	"CuiDetailProps",
	"CuiDetailField",
	"CuiTabProps",
	"CuiTabItem",
	"CuiExcelProps",
	"CuiExcelEmits",
	"CuiSelectBoxProps",
	"CuiSelectBoxEmits",
	"CuiSelectBoxOption",
	"CuiSelectProps",
	"CuiSelectEmits",
	"CuiSelectOption",
	"CuiSelectEnumProps",
	"CuiSelectEnumEmits",
	"CuiSelectEnumOption",
	"CuiSelectDictProps",
	"CuiSelectDictEmits",
	"CuiSelectDictOption",
	"CuiRadioEnumProps",
	"CuiRadioEnumEmits",
	"CuiRadioEnumOption",
	"CuiRadioDictProps",
	"CuiRadioDictEmits",
	"CuiRadioDictOption",
	"CuiCheckboxEnumProps",
	"CuiCheckboxEnumEmits",
	"CuiCheckboxEnumOption",
	"CuiAutocompleteProps",
	"CuiAutocompleteEmits",
	"CuiAutocompleteSuggestion",
] as const;

const componentNameSet = new Set<string>(vueElementCuiComponentNames);
const runtimeExportNameSet = new Set<string>(vueElementCuiRuntimeExports);

function createRuntimeImport(name: string): VueElementCuiComponentInfo {
	return componentNameSet.has(name)
		? { name, from: PACKAGE_NAME, sideEffects: STYLE_ENTRY }
		: { name, from: PACKAGE_NAME };
}

export function VueElementCuiResolver(): VueElementCuiComponentResolver {
	return (name) => {
		if (!componentNameSet.has(name)) {
			return undefined;
		}

		return createRuntimeImport(name);
	};
}

export function VueElementCuiAutoImportResolver(): VueElementCuiComponentResolver {
	return (name) => {
		if (name === "VueElementCui") {
			return {
				name: "default",
				as: "VueElementCui",
				from: PACKAGE_NAME,
			};
		}

		if (!runtimeExportNameSet.has(name)) {
			return undefined;
		}

		return createRuntimeImport(name);
	};
}

export const vueElementCuiImports: VueElementCuiImportsMap = {
	[PACKAGE_NAME]: [["default", "VueElementCui"], ...vueElementCuiRuntimeExports],
};

export const vueElementCuiTypeImports: VueElementCuiTypeImport[] = [
	{
		from: PACKAGE_NAME,
		imports: [...vueElementCuiTypeExportNames],
		type: true,
	},
];
