import type { CuiTableProps, SortChangeEvent, SelectionChangeEvent } from "./types";
declare const __VLS_export: <T = any>(
	__VLS_props: NonNullable<Awaited<typeof __VLS_setup>>["props"],
	__VLS_ctx?: __VLS_PrettifyLocal<Pick<NonNullable<Awaited<typeof __VLS_setup>>, "attrs" | "emit" | "slots">>,
	__VLS_exposed?: NonNullable<Awaited<typeof __VLS_setup>>["expose"],
	__VLS_setup?: Promise<{
		props: import("vue").PublicProps &
			__VLS_PrettifyLocal<
				CuiTableProps<T> & {
					"onSort-change"?: ((event: SortChangeEvent) => any) | undefined;
					"onSelection-change"?: ((selection: SelectionChangeEvent<T>) => any) | undefined;
					"onRow-click"?: ((row: T, column: any, event: Event) => any) | undefined;
					"onCell-click"?: ((row: T, column: any, cell: any, event: Event) => any) | undefined;
				}
			> &
			(typeof globalThis extends {
				__VLS_PROPS_FALLBACK: infer P;
			}
				? P
				: {});
		expose: (exposed: {}) => void;
		attrs: any;
		slots: {
			[x: string]: ((props: { row: any; column: import("./types").CuiTableColumn<T>; $index: any }) => any) | undefined;
		};
		emit: ((evt: "sort-change", event: SortChangeEvent) => void) &
			((evt: "selection-change", selection: SelectionChangeEvent<T>) => void) &
			((evt: "row-click", row: T, column: any, event: Event) => void) &
			((evt: "cell-click", row: T, column: any, cell: any, event: Event) => void);
	}>,
) => import("vue").VNode & {
	__ctx?: Awaited<typeof __VLS_setup>;
};
declare const _default: typeof __VLS_export;
export default _default;
type __VLS_PrettifyLocal<T> = (T extends any
	? {
			[K in keyof T]: T[K];
		}
	: {
			[K in keyof T as K]: T[K];
		}) & {};
//# sourceMappingURL=cui-table.vue.d.ts.map
