<template>
	<div class="f1-table">
		<el-table
			:data="tableData"
			v-bind="config.tableProperties"
			:row-key="config.rowKey || 'id'"
			v-loading="config.loading"
			style="width: 100%"
			@selection-change="handleSelectionChange"
		>
			<template v-for="(item, index) in config.tableList" :key="item.prop ?? item.type + index">
				<template v-if="item.type === 'index'">
					<el-table-column align="center" v-bind="item" />
				</template>
				<template v-else-if="item.type === 'selection'">
					<el-table-column align="center" v-bind="item" />
				</template>
				<template v-else-if="item.type === 'custom'">
					<el-table-column align="center" v-bind="item">
						<template #default="scope">
							<slot :name="item.slotName" v-bind="scope"></slot>
						</template>
					</el-table-column>
				</template>
				<template v-else-if="item.type === 'handler'">
					<el-table-column align="center" v-bind="item">
						<template #default="scope">
							<div class="handler-btns">
								<el-button v-if="config.handler?.view" type="primary" link @click="handleView(scope.row)">
									{{ config.handler?.viewText || "查看" }}
								</el-button>
								<el-button v-if="config.handler?.edit" type="primary" link @click="handleEdit(scope.row)">
									{{ config.handler?.editText || "编辑" }}
								</el-button>
								<el-button v-if="config.handler?.delete" type="danger" link @click="handleDelete(scope.row)">
									{{ config.handler?.deleteText || "删除" }}
								</el-button>
								<slot name="handler-extra" v-bind="scope"></slot>
							</div>
						</template>
					</el-table-column>
				</template>
				<template v-else>
					<el-table-column align="center" v-bind="item" />
				</template>
			</template>
		</el-table>
		<div v-if="config.pagination?.enabled" class="pagination">
			<el-pagination
				v-model:current-page="currentPage"
				v-model:page-size="pageSize"
				:page-sizes="config.pagination.pageSizes || [10, 20, 50, 100]"
				size="small"
				:layout="config.pagination.layout || 'total, sizes, prev, pager, next, jumper'"
				:total="config.pagination.total"
				@current-change="handlePageChange"
				@size-change="handleSizeChange"
			/>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref, computed, watch } from "vue";
import type { TableConfig } from "./type";

interface Props {
	config: TableConfig;
	data?: any[];
}

const props = withDefaults(defineProps<Props>(), {
	config: () => ({
		tableProperties: {
			stripe: true,
			border: true,
		},
		tableList: [],
		pagination: {
			enabled: true,
			currentPage: 1,
			pageSize: 10,
			total: 0,
		},
		loading: false,
	}),
	data: () => [],
});

const emit = defineEmits<{
	(e: "page-change", page: number, size: number): void;
	(e: "selection-change", selection: any[]): void;
	(e: "edit", row: any): void;
	(e: "delete", row: any): void;
	(e: "view", row: any): void;
}>();

const currentPage = ref(props.config.pagination?.currentPage || 1);
const pageSize = ref(props.config.pagination?.pageSize || 10);

const tableData = computed(() => {
	return props.data;
});

watch(
	() => props.config.pagination?.currentPage,
	(val) => {
		if (val) currentPage.value = val;
	},
);

function handlePageChange(page: number) {
	currentPage.value = page;
	props.config.pagination?.onPageChange?.(page, pageSize.value);
	emit("page-change", page, pageSize.value);
}

function handleSizeChange(size: number) {
	pageSize.value = size;
	currentPage.value = 1;
	props.config.pagination?.onPageChange?.(1, size);
	emit("page-change", 1, size);
}

function handleSelectionChange(selection: any[]) {
	props.config.onSelectionChange?.(selection);
	emit("selection-change", selection);
}

function handleEdit(row: any) {
	props.config.handler?.onEdit?.(row);
	emit("edit", row);
}

function handleDelete(row: any) {
	props.config.handler?.onDelete?.(row);
	emit("delete", row);
}

function handleView(row: any) {
	props.config.handler?.onView?.(row);
	emit("view", row);
}

defineExpose({
	currentPage,
	pageSize,
});
</script>

<style scoped>
.f1-table {
	width: 100%;
}

.pagination {
	display: flex;
	justify-content: flex-end;
	margin-top: 16px;
	background: #fff;
	padding: 12px 0;
}

.handler-btns {
	display: flex;
	gap: 8px;
	justify-content: center;
}
</style>
