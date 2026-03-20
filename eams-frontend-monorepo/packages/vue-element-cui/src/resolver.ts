/** 包名与 package.json 的 name 保持单一数据源；Vite 构建会将 JSON 内联进 dist/resolver.* */
import packageJson from "../package.json" with { type: "json" };
import { VUE_ELEMENT_CUI_COMPONENT_NAMES, VUE_ELEMENT_CUI_TYPE_EXPORT_NAMES } from "./components-manifest";

const PACKAGE_NAME: string = packageJson.name;
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

/** 组件名列表，由 components-manifest 驱动，新增组件时只改 manifest */
export const vueElementCuiComponentNames = VUE_ELEMENT_CUI_COMPONENT_NAMES;

/** 运行时导出名（install、version + 所有组件名），供 unplugin-auto-import 等使用 */
export const vueElementCuiRuntimeExports = ["install", "version", ...vueElementCuiComponentNames] as const;

/** 类型导出名列表，由 components-manifest 驱动 */
export const vueElementCuiTypeExportNames = VUE_ELEMENT_CUI_TYPE_EXPORT_NAMES;

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
