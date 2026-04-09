<template>
	<el-table
		v-loading="loading"
		:data="data"
		:stripe="stripe"
		:border="border"
		:height="height"
		:max-height="maxHeight"
		v-bind="$attrs"
		@sort-change="handleSortChange"
		@selection-change="handleSelectionChange"
		@row-click="(row, column, event) => $emit('row-click', row, column, event)"
		@cell-click="(row, column, cell, event) => $emit('cell-click', row, column, cell, event)"
	>
		<!-- 选择列 -->
		<el-table-column v-if="showSelection" type="selection" width="55" align="center" />

		<!-- 索引列 -->
		<el-table-column v-if="showIndex" type="index" label="序号" width="60" align="center" />

		<!-- 数据列 -->
		<el-table-column
			v-for="(column, index) in columns"
			:key="index"
			:prop="column.prop"
			:label="column.label"
			:width="column.width"
			:min-width="column.minWidth"
			:sortable="column.sortable"
			:fixed="column.fixed"
			:align="column.align"
			:formatter="column.formatter"
		>
			<template v-if="column.slot" #default="scope">
				<slot :name="column.slot" :row="scope.row" :column="column" :$index="scope.$index" />
			</template>
		</el-table-column>
	</el-table>
</template>

<script setup lang="ts" generic="T = any">
import { ElTable, ElTableColumn } from "element-plus";
import type { CuiTableProps, SortChangeEvent, SelectionChangeEvent } from "./types";

/* 定义 Props */
const props = withDefaults(defineProps<CuiTableProps<T>>(), {
	loading: false,
	showIndex: false,
	showSelection: false,
	stripe: false,
	border: true,
});

/* 定义 Emits */
const emit = defineEmits<{
	"sort-change": [event: SortChangeEvent];
	"selection-change": [selection: SelectionChangeEvent<T>];
	"row-click": [row: T, column: any, event: Event];
	"cell-click": [row: T, column: any, cell: any, event: Event];
}>();

/* 排序变化处理 */
const handleSortChange = ({ prop, order }: { prop: string; order: "ascending" | "descending" | null }) => {
	emit("sort-change", { prop, order });
};

/* 选择变化处理 */
const handleSelectionChange = (selection: T[]) => {
	emit("selection-change", selection);
};

/* 启用属性继承以透传其他 ElTable 的 props 和事件 */
defineOptions({
	inheritAttrs: false,
});
</script>
