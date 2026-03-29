<template>
	<section class="table-container">
		<!-- 表格顶部 -->
		<section class="table-header">
			<h3 v-if="tabtitle">{{ tabtitle }}</h3>
			<h3 v-else></h3>
			<!-- 顶部插槽，用于支持扩展顶部操作栏 -->
			<section class="header-slot">
				<slot name="header" :table="tableRef" :props="props"></slot>
			</section>
		</section>
		<!-- 表格主体 -->
		<el-table
			ref="tableRef"
			:data="tabdata.rows"
			:="reltabattr"
			@row-dblclick="handleRowDblclick"
			@selection-change="handleSelectionChange"
		>
			<!-- 多选列 -->
			<el-table-column v-if="istabmultiple" type="selection" width="55" />
			<!-- 自定义展开行 -->
			<el-table-column v-if="istabexpand" fixed type="expand" width="30">
				<template #default="scope">
					<!-- 声明一个具名插槽，用于支持外部自定义扩展行显示内容 -->
					<slot name="customerexpand" :row="scope.row"></slot>
				</template>
			</el-table-column>
			<!-- 序号列 -->
			<el-table-column
				v-if="istabseq"
				fixed
				type="index"
				label="序号"
				width="60"
				align="center"
				:index="(index: number) => ++index"
			/>
			<!-- 数据列 -->
			<el-table-column v-for="(column, index) in tabdatacolumns" :key="column.prop || index" :="column">
				<template #default="scope">
					<!-- 声明一个具名插槽，用于支持外部自定义单元格显示内容 -->
					<slot name="customercell" :column="column" :prop="column.prop" :index="scope.$index" :row="scope.row">
						<!-- 数据列 -->
						<template v-if="column.prop !== 'operate'">
							{{ scope.row[column.prop] }}
						</template>
						<!-- 操作列 -->
						<template v-else>
							<el-button
								v-for="(btn, index) in taboperbtns"
								:key="btn.text || index"
								:size="btn.attr?.size || tabopercolumnattr?.size"
								:="btn.attr"
								@click="emit('taboper-click', scope.$index, scope.row, btn.evtname)"
							>
								{{ btn.text }}
							</el-button>
						</template>
					</slot>
				</template>
			</el-table-column>
		</el-table>
		<!-- 表格底部 -->
		<section class="table-footer">
			<!-- 底部插槽，用于支持扩展底部操作栏或表格底部标注 -->
			<section class="footer-slot">
				<slot name="footer" :table="tableRef" :props="props"></slot>
			</section>
			<!-- 分页组件 -->
			<el-pagination
				v-if="istabpage"
				layout="sizes, prev, pager, next, total"
				hide-on-single-page
				:size="reltabattr.psize"
				:page-size="tabdata.pageSize"
				:page-sizes="pageSizeOptions"
				:total="tabdata.total"
				:current-page="tabdata.pageIndex"
				@size-change="handlePageSizeChange"
				@current-change="handleCurrentPageChange"
			/>
		</section>
	</section>
</template>

<script setup lang="ts" generic="T extends Object">
import { type PropType, computed, ref } from "vue";
import type { TableInstance } from "element-plus";
import {
	type MyTableAttr,
	type MyTableColumn,
	type MyTableOperationsColumn,
	type MyTableOperationsBtn,
	type PageDTO,
	createMyTableOperationsColumn,
	createPageDTO,
} from "./type";

// el-table的引用
const tableRef = ref<TableInstance>();

// 组件属性定义
const props = defineProps({
	/** 表格标题, 默认无标题 */
	tabtitle: String,
	/** 是否显示自定义展开行，默认不显示 */
	istabexpand: {
		type: Boolean,
		default: false,
	},
	/** 是否显示序号列，默认不显示 */
	istabseq: {
		type: Boolean,
		default: false,
	},
	/** 是否开启多选，默认不开启 */
	istabmultiple: {
		type: Boolean,
		default: false,
	},
	/** 是否开启分页，默认开启 */
	istabpage: {
		type: Boolean,
		default: true,
	},
	/** 表格属性 */
	tabattr: Object as PropType<MyTableAttr>,
	/** 表格列数据 */
	tabdatacolumns: Array as PropType<MyTableColumn[]>,
	/** 表格数据 */
	tabdata: {
		type: Object as PropType<PageDTO<T>>,
		default: () => createPageDTO(),
	},
	/** 表操作列按钮数据 */
	taboperbtns: {
		type: Array as PropType<MyTableOperationsBtn[]>,
		default: () => [],
	},
});

/**
 * 合并表格默认属性与传入属性
 */
const reltabattr = computed<MyTableAttr>(() => {
	// 默认属性
	const defaultAttrs: MyTableAttr = {
		psize: "default",
		border: false,
		stripe: true,
		"highlight-current-row": true,
	};
	return {
		...defaultAttrs,
		...props.tabattr,
	};
});

/**
 * 合并操作列默认属性与传入属性
 */
const tabopercolumnattr = computed<MyTableOperationsColumn>(() => {
	const defaultCol = createMyTableOperationsColumn();
	if (props.tabdatacolumns) {
		const col = props.tabdatacolumns.find((column) => column.prop === "operate");
		if (col) {
			return { ...defaultCol, ...col };
		}
	}
	return defaultCol;
});

/**
 * 分页器每页条数选项。
 * 当外部传入了更小的 pageSize 时，也一并展示出来，保证分页器和业务页默认值一致。
 */
const pageSizeOptions = computed(() => {
	const defaultOptions = [10, 20, 50];
	const currentPageSize = props.tabdata?.pageSize;
	if (!currentPageSize || defaultOptions.includes(currentPageSize)) return defaultOptions;
	return [currentPageSize, ...defaultOptions];
});

/**
 * 声明emit事件
 */
const emit = defineEmits<{
	/** 分页事件 */
	(event: "page-change", data: PageDTO<T>): void;
	/** 选中行事件 */
	(event: "selection-change", data: Array<T>): void;
	/** 行双击事件 */
	(event: "row-dbclick", data: T): void;
	/** 操作栏点击事件 */
	(event: "taboper-click", index: number, row: T, evtname: string): void;
}>();

/**
 * 多选框选中行发生改变时候触发
 * @param rows 当前选择的行
 */
function handleSelectionChange(rows: T[]) {
	emit("selection-change", rows);
}

/**
 * 双击行触发事件
 * @param row 当前双击的行
 */
function handleRowDblclick(row: T) {
	emit("row-dbclick", row);
}

/**
 * 每页数据条数发生改变时候触发
 * @param val 每页数据条数
 */
const handlePageSizeChange = (val: number) => {
	emit("page-change", createPageDTO({ pageSize: val, pageIndex: 1 }));
};
/**
 * 页码发生改变时候触发
 * @param val 当前页码
 */
const handleCurrentPageChange = (val: number) => {
	emit("page-change", createPageDTO({ pageSize: props.tabdata.pageSize, pageIndex: val }));
};
</script>
<style scoped>
.table-container {
	width: 100%;
	background-color: white;
	border-radius: 5px;
	box-sizing: border-box;
	padding: 10px;
}
.table-header {
	margin: 0.8% 0.5%;
	display: flex;
	flex-direction: row;
	justify-content: space-between;
	align-items: center;
	.header-slot {
		display: flex;
		justify-content: flex-end;
		gap: 10px;
		align-items: center;
	}
}
.table-footer {
	margin: 1% 0.5%;
	display: flex;
	flex-direction: row;
	justify-content: space-between;
	align-items: flex-start;
	.footer-slot {
		display: flex;
		justify-content: flex-start;
		align-items: center;
		gap: 10px;
	}
}
</style>
