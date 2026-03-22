<template>
	<div class="index">
		<div class="toolbar">
			<el-button type="primary" @click="handleRefresh">刷新数据</el-button>
			<el-button @click="handleGetSelection">获取选中项</el-button>
		</div>
		<F1Table
			:config="tableConfig"
			:data="tableData"
			@page-change="handlePageChange"
			@selection-change="handleSelectionChange"
			@edit="handleEdit"
			@delete="handleDelete"
			@view="handleView"
		>
			<template #status="{ row }">
				<el-tag :type="row.enable === 1 ? 'success' : 'danger'">
					{{ row.enable === 1 ? "启用" : "禁用" }}
				</el-tag>
			</template>
			<template #handler-extra="{ row }">
				<el-button type="warning" link @click="handleCustom(row)">自定义</el-button>
			</template>
		</F1Table>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage } from "element-plus";
import F1Table from "@/components/f1table/F1Table.vue";
import { getMockData } from "@/components/f1table/mock";
import type { TableConfig } from "@/components/f1table/type";
import { TableType } from "@/components/f1table/type";

const tableData = ref<any[]>([]);
const selectionData = ref<any[]>([]);

const tableConfig = reactive<TableConfig>({
	tableProperties: {
		stripe: true,
		border: true,
		height: 400,
	},
	tableList: [
		{
			type: TableType.selection,
			width: "50px",
			label: "选择",
			fixed: true,
		},
		{
			type: TableType.index,
			width: "60px",
			label: "序号",
			fixed: true,
		},
		{
			type: TableType.normal,
			label: "用户名",
			prop: "name",
			width: "120px",
		},
		{
			type: TableType.normal,
			label: "真实名",
			prop: "realname",
			width: "100px",
		},
		{
			type: TableType.normal,
			label: "手机号码",
			prop: "cellphone",
			width: "130px",
		},
		{
			type: TableType.normal,
			label: "角色",
			prop: "role",
			width: "100px",
		},
		{
			type: TableType.normal,
			label: "部门",
			prop: "department",
			width: "100px",
		},
		{
			type: TableType.custom,
			label: "状态",
			prop: "enable",
			width: "80px",
			slotName: "status",
		},
		{
			type: TableType.normal,
			label: "创建时间",
			prop: "createTime",
			width: "180px",
		},
		{
			type: TableType.handler,
			label: "操作",
			width: "180px",
			fixed: "right",
		},
	],
	pagination: {
		enabled: true,
		currentPage: 1,
		pageSize: 10,
		total: 0,
		pageSizes: [5, 10, 20, 50],
	},
	handler: {
		edit: true,
		delete: true,
		view: true,
		editText: "编辑",
		deleteText: "删除",
		viewText: "查看",
	},
	loading: false,
	rowKey: "id",
});

function loadData() {
	tableConfig.loading = true;
	setTimeout(() => {
		const result = getMockData(tableConfig.pagination!.currentPage ?? 1, tableConfig.pagination!.pageSize ?? 10);
		tableData.value = result.list;
		tableConfig.pagination!.total = result.total;
		tableConfig.loading = false;
	}, 300);
}

function handlePageChange(page: number, size: number) {
	console.log("分页变化:", page, size);
	loadData();
}

function handleSelectionChange(selection: any[]) {
	selectionData.value = selection;
	console.log("选中项:", selection);
}

function handleEdit(row: any) {
	ElMessage.info(`编辑: ${row.name}`);
}

function handleDelete(row: any) {
	ElMessage.warning(`删除: ${row.name}`);
}

function handleView(row: any) {
	ElMessage.success(`查看: ${row.name}`);
}

function handleCustom(row: any) {
	ElMessage.info(`自定义操作: ${row.name}`);
}

function handleRefresh() {
	loadData();
	ElMessage.success("刷新成功");
}

function handleGetSelection() {
	if (selectionData.value.length === 0) {
		ElMessage.warning("请先选择数据");
		return;
	}
	ElMessage.success(`已选中 ${selectionData.value.length} 项`);
	console.log("选中数据:", selectionData.value);
}

onMounted(() => {
	loadData();
});
</script>

<style scoped>
.index {
	padding: 20px;
}

.toolbar {
	margin-bottom: 16px;
}
</style>
