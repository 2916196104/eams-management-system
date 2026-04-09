import type { App, Plugin } from "vue";
export declare const version: string;
export declare function install(app: App): void;
declare const plugin: Plugin & {
	version: string;
};
export default plugin;
export * from "./components";
//# sourceMappingURL=index.d.ts.map
