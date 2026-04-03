<template>
	<section class="material-page">
		<FilterToolbar
			:collapsible-item-count="5"
			:collapse-threshold="4"
			@search="handleSearch"
			@reset="handleReset"
			@refresh="handleRefresh"
			@print="handlePrint"
			@column-setting="handleColumnSetting"
		>
			<template #left="{ showAll, limit }">
				<div class="filter-toolbar-body">
					<div class="filter-grid">
						<div v-show="showAll || 0 < limit" class="filter-cell">
							<span class="filter-label">物料名称</span>
							<div class="search-input-group">
								<el-input v-model="form.materialLabel" placeholder="请输入" clearable />
							</div>
						</div>

						<div v-show="showAll || 3 < limit" class="filter-cell">
							<span class="filter-label">状态</span>
							<el-select v-model="form.status" placeholder="请选择" clearable style="width: 100%">
								<el-option label="启用" value="启用" />
								<el-option label="禁用" value="禁用" />
							</el-select>
						</div>
					</div>

					<div class="batch-row">
						<el-button type="primary" @click="formDialog?.openDialog()">+ 新增</el-button>
						<el-button @click="handleBatchDelete">删除</el-button>
						<el-button type="success" @click="handleBatchEnable">启用</el-button>
						<el-button type="warning" @click="handleBatchDisable">禁用</el-button>
					</div>
				</div>
			</template>
		</FilterToolbar>

		<section class="table-card">
			<el-table
				v-loading="tableLoading"
				:data="tableRows"
				stripe
				row-key="id"
				@selection-change="handleSelectionChange"
			>
				<el-table-column type="selection" width="48" :selectable="isRowSelectable" />

				<el-table-column
					v-for="(col, idx) in visibleColumns"
					:key="idx"
					:label="col.label"
					:prop="col.prop"
					:width="col.width || undefined"
					:min-width="col.minWidth || undefined"
					show-overflow-tooltip
				>
					<template #default="{ row }" v-if="col.prop === 'status'">
						<el-tag :type="row.status === '启用' ? 'success' : 'info'" effect="light">{{ row.status }}</el-tag>
					</template>
					<template #default="{ row }" v-if="col.prop === 'avatar'">
						<el-avatar :size="36" shape="square">图</el-avatar>
					</template>
				</el-table-column>

				<el-table-column label="操作" width="200" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="handleEdit(row)">编辑</el-button>
						<el-button link type="primary" @click="handleInbound(row)">入库</el-button>
						<el-button link type="primary" @click="handleOutbound(row)">出库</el-button>
					</template>
				</el-table-column>
			</el-table>
		</section>

		<PrintTable ref="printRef" print-title="物料管理列表" :column-list="allColumns" :table-data="tableRows" />

		<ColumnSetting
			v-model="columnSettingVisible"
			:columns="allColumns"
			@change="handleColumnChange"
			@confirm="handleColumnConfirm"
			@reset="handleColumnReset"
		/>
	</section>

	<MyFormDialog ref="formDialog" :="formDialogProps" @confirm="onSubmit">
		<template #itemdefault="{ item }">
			<el-upload
				v-if="item.prop === 'avatar'"
				class="avatar-uploader"
				action="https://jsonplaceholder.typicode.com/posts/"
				:show-file-list="false"
			>
				<el-button class="avatar-uploader-icon" type="primary" icon="IconUpload">上传</el-button>
			</el-upload>
		</template>
	</MyFormDialog>

	<MyFormDialog ref="inboundFormDialog" :="inboundFormDialogProps" @confirm="onInboundSubmit"></MyFormDialog>
	<MyFormDialog ref="outboundFormDialog" :="outboundFormDialogProps" @confirm="onOutboundSubmit"></MyFormDialog>

	<MyFormDialog ref="editFormDialog" :="editFormDialogProps" @confirm="onEditSubmit">
		<template #itemdefault="{ item }">
			<el-upload
				v-if="item.prop === 'avatar'"
				class="avatar-uploader"
				action="https://jsonplaceholder.typicode.com/posts/"
				:show-file-list="false"
			>
				<el-button class="avatar-uploader-icon" type="primary" icon="IconUpload">上传</el-button>
			</el-upload>
		</template>
	</MyFormDialog>
</template>

<script setup lang="ts">
import { reactive, ref, computed } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Search } from "@element-plus/icons-vue";
import FilterToolbar from "@/views/material/components/FilterToolbar.vue";
import MyFormDialog from "@/components/mydialog/MyFormDialog.vue";
import type { MyFormItemAttr } from "@/components/myform/type";
import type { SampleFormData } from "@/apis/sample/type";
import type { MyFormDialogProps } from "@/components/mydialog/type";
import type { MyFormInputProps } from "@/components/myform/props/input.ts";
import type { MyFormSelectProps } from "@/components/myform/props/select.ts";
import type { MyFormBaseProps } from "@/components/myform/props/formbase.ts";
import { MaterialInboundAndOutbound } from "@/apis/material/materialManagement";

import ColumnSetting from "../../operation/components/ColumnSetting.vue";
import PrintTable from "../../operation/components/PrintTable.vue";

const formDialog = ref();
const editFormDialog = ref();
const inboundFormDialog = ref();
const outboundFormDialog = ref();

const form = reactive({
	materialId: "" as string,
	materialLabel: "",
	operType: "",
	school: "",
	operator: "",
	operTimeRange: [] as string[],
	status: "",
});

const currentEditRow = ref(null);
const currentMaterialId = ref("");
const selectedRows = ref<any[]>([]);

// ==============================================
// ✅ 正确结构：原始数据永远保存，表格只显示筛选后的结果
// ==============================================
const originalTableRows = ref([
	{
		id: "1",
		name: "水",
		category: "耗材",
		school: "总校",
		stock: 200,
		updatedAt: "2026-03-01 10:00:00",
		status: "启用",
	},
	{
		id: "2",
		name: "鼠标",
		category: "办公",
		school: "总校",
		stock: 45,
		updatedAt: "2026-03-02 11:30:00",
		status: "启用",
	},
]);

const tableRows = ref([...originalTableRows.value]);
const tableLoading = ref(false);

// ==============================================
// 列配置
// ==============================================
const columnSettingVisible = ref(false);
const allColumns = ref([
	{ label: "序号", prop: "index", width: 48, visible: true },
	{ label: "图片", prop: "avatar", width: 72, visible: true },
	{ label: "物料名称", prop: "name", minWidth: 120, visible: true },
	{ label: "分类", prop: "category", width: 100, visible: true },
	{ label: "所属学校", prop: "school", minWidth: 110, visible: true },
	{ label: "库存", prop: "stock", width: 80, visible: true },
	{ label: "最后编辑时间", prop: "updatedAt", minWidth: 165, visible: true },
	{ label: "状态", prop: "status", width: 88, visible: true },
]);

const visibleColumns = computed(() => {
	return allColumns.value.filter((c) => c.visible);
});

const handleColumnSetting = () => {
	columnSettingVisible.value = true;
};

const handleColumnChange = (newColumns: any) => {
	allColumns.value = newColumns;
};

const handleColumnConfirm = (newColumns: any) => {
	allColumns.value = newColumns;
	localStorage.setItem("materialManageColumns", JSON.stringify(newColumns));
};

const handleColumnReset = () => {
	allColumns.value.forEach((c) => (c.visible = true));
};

// ==============================================
// 打印
// ==============================================
const printRef = ref();
const handlePrint = () => {
	printRef.value?.handlePrint();
};

// ==============================================
// 复选框
// ==============================================
const handleSelectionChange = (val: any[]) => {
	selectedRows.value = val;
};

const isRowSelectable = (row: any) => {
	return row.status !== "禁用";
};

// ==============================================
// 批量删除 / 禁用 / 启用
// ==============================================
const handleBatchDelete = async () => {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请选择要删除的数据");
		return;
	}
	await ElMessageBox.confirm("确认删除选中的数据？", "提示", { type: "warning" });
	const ids = selectedRows.value.map((item) => item.id);

	// 删除同时更新原始数据
	originalTableRows.value = originalTableRows.value.filter((item) => !ids.includes(item.id));
	tableRows.value = [...originalTableRows.value];

	ElMessage.success("删除成功");
};

const handleBatchDisable = async () => {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请选择要禁用的数据");
		return;
	}
	await ElMessageBox.confirm("确认禁用选中的数据？", "提示", { type: "warning" });
	selectedRows.value.forEach((item) => {
		item.status = "禁用";
	});
	ElMessage.success("禁用成功");
};

const handleBatchEnable = async () => {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请选择要启用的数据");
		return;
	}
	await ElMessageBox.confirm("确认启用选中的数据？", "提示", { type: "warning" });
	selectedRows.value.forEach((item) => {
		item.status = "启用";
	});
	ElMessage.success("启用成功");
};


const handleSearch = () => {
	tableLoading.value = true;
	setTimeout(() => {
		// 从完整原始数据过滤
		let filtered = [...originalTableRows.value];

		if (form.materialLabel) {
			filtered = filtered.filter((row) => row.name.includes(form.materialLabel));
		}
		if (form.status) {
			filtered = filtered.filter((row) => row.status === form.status);
		}

		tableRows.value = filtered;
		tableLoading.value = false;
		ElMessage.success("已按条件查询");
	}, 300);
};

// ==============================================
// ✅ 正确重置：恢复全部原始数据
// ==============================================
const handleReset = () => {
	form.materialId = "";
	form.materialLabel = "";
	form.operType = "";
	form.school = "";
	form.operator = "";
	form.operTimeRange = [];
	form.status = "";

	// 恢复全部数据
	tableRows.value = [...originalTableRows.value];
	ElMessage.info("已重置条件");
};

const handleRefresh = () => {
	handleSearch();
};

// ==============================================
// 原有功能完全不动
// ==============================================
const handleEdit = (row: any) => {
	currentEditRow.value = row;
	editFormDialogProps.value.data = {
		name: row.name,
		school: row.school,
		category: row.category,
		changeReason: row.updatedAt ? "原说明" : "",
	};
	editFormDialog.value?.openDialog();
};

const handleInbound = (row: any) => {
	currentMaterialId.value = row.id;
	inboundFormDialog.value?.openDialog();
};

const handleOutbound = (row: any) => {
	currentMaterialId.value = row.id;
	outboundFormDialog.value?.openDialog();
};

const inboundFormDialogProps = ref<MyFormDialogProps<SampleFormData>>({
	data: reactive<SampleFormData>({}),
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "number",
			prop: "amount",
			label: "入库数量",
			fprops: { placeholder: "请输入入库数量", width: "100%" } as MyFormInputProps,
		},
		{
			type: "input",
			prop: "changeReason",
			label: "入库说明",
			fprops: {
				type: "textarea",
				rows: 4,
				placeholder: "请输入物料说明",
				clearable: true,
				width: "100%",
			} as MyFormInputProps,
		},
	]),
	formattr: { disabled: false, "label-width": "80px" },
	title: "物料入库",
	width: "35vw",
	reset: false,
	submitText: "提交",
	cancelText: "取消",
});

const outboundFormDialogProps = ref<MyFormDialogProps<SampleFormData>>({
	data: reactive<SampleFormData>({}),
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "number",
			prop: "amount",
			label: "出库数量",
			fprops: { placeholder: "请输入出库数量", width: "100%" } as MyFormInputProps,
		},
		{
			type: "input",
			prop: "changeReason",
			label: "出库说明",
			fprops: {
				type: "textarea",
				rows: 4,
				placeholder: "请输入物料说明",
				clearable: true,
				width: "100%",
			} as MyFormInputProps,
		},
	]),
	formattr: { disabled: false, "label-width": "80px" },
	title: "物料出库",
	width: "35vw",
	reset: false,
	submitText: "提交",
	cancelText: "取消",
});

const editFormDialogProps = ref<MyFormDialogProps<SampleFormData>>({
	data: reactive<SampleFormData>({}),
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "input",
			prop: "name",
			label: "物料名称",
			required: true,
			fprops: { placeholder: "请输入物料名称", width: "100%" } as MyFormInputProps,
		},
		{
			type: "input",
			prop: "school",
			label: "所属学校",
			required: true,
			fprops: { placeholder: "请输入所属学校", width: "100%" } as MyFormInputProps,
		},
		{
			type: "select",
			prop: "category",
			label: "所属分类",
			required: true,
			fprops: {
				placeholder: "请选择所属分类",
				width: "100%",
				options: [
					{ label: "教材", value: "textbook" },
					{ label: "教具", value: "teachingAids" },
					{ label: "实验器材", value: "labEquipment" },
				],
			} as MyFormSelectProps,
		},
		{
			type: "file",
			prop: "avatar",
			label: "物料图片",
			fprops: { placeholder: "点击上传文件", clearable: true } as MyFormBaseProps,
		},
		{
			type: "input",
			prop: "changeReason",
			label: "物料说明",
			fprops: { type: "textarea", placeholder: "请输入物料说明", rows: 4, width: "100%" } as any,
		},
	]),
	title: "修改物料",
	width: "35vw",
	reset: false,
	submitText: "提交",
	cancelText: "取消",
});

const onInboundSubmit = async (formData: any) => {
	if (!currentMaterialId.value) {
		ElMessage.warning("未选择物料");
		return;
	}
	if (!formData.amount || formData.amount <= 0) {
		ElMessage.warning("请输入正确的入库数量");
		return;
	}
	if (!formData.changeReason?.trim()) {
		ElMessage.warning("请输入入库说明");
		return;
	}

	try {
		await MaterialInboundAndOutbound({
			materialId: Number(currentMaterialId.value),
			amount: formData.amount,
			changeType: 1,
			reason: formData.changeReason.trim(),
		});
		ElMessage.success("入库成功");
		inboundFormDialog.value?.closeDialog?.();
	} catch (err) {
		console.error(err);
		ElMessage.error("入库失败");
	}
};

const onOutboundSubmit = async (formData: any) => {
	if (!currentMaterialId.value) {
		ElMessage.warning("未选择物料");
		return;
	}
	if (!formData.amount || formData.amount <= 0) {
		ElMessage.warning("请输入正确的出库数量");
		return;
	}
	if (!formData.changeReason?.trim()) {
		ElMessage.warning("请输入出库说明");
		return;
	}

	try {
		await MaterialInboundAndOutbound({
			materialId: Number(currentMaterialId.value),
			amount: formData.amount,
			changeType: 2,
			reason: formData.changeReason.trim(),
		});
		ElMessage.success("出库成功");
		outboundFormDialog.value?.closeDialog?.();
	} catch (err) {
		console.error(err);
		ElMessage.error("出库失败");
	}
};

const formDialogProps = reactive<MyFormDialogProps<SampleFormData>>({
	data: reactive<SampleFormData>({}),
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "input",
			prop: "name",
			label: "物料名称",
			rules: [{ required: true, message: "请输入物料名称" }],
			fprops: { placeholder: "请输入物料名称", clearable: true } as MyFormInputProps,
		},
		{
			type: "input",
			prop: "school",
			label: "所属学校",
			rules: [{ required: true, message: "请输入所属学校" }],
			fprops: { placeholder: "请输入所属学校", clearable: true } as MyFormInputProps,
		},
		{
			type: "select",
			prop: "category",
			label: "所属分类",
			fprops: {
				placeholder: "请选择所属分类",
				options: [
					{ label: "教材", value: "教材" },
					{ label: "设备", value: "设备" },
				],
			} as MyFormSelectProps,
		},
		{
			type: "file",
			prop: "avatar",
			label: "物料图片",
			fprops: { placeholder: "点击上传文件", clearable: true } as MyFormBaseProps,
		},
		{
			type: "input",
			prop: "changeReason",
			label: "物料说明",
			fprops: {
				type: "textarea",
				rows: 4,
				placeholder: "请输入物料说明",
				clearable: true,
				width: "100%",
			} as MyFormInputProps,
		},
	]),
	formattr: { disabled: false, "label-width": "80px" },
	title: "新增物料",
	width: "35vw",
	reset: false,
	submitText: "提交",
	cancelText: "取消",
});

const onSubmit = () => {
	ElMessage.success("提交成功");
};

const onEditSubmit = async (formData: any) => {
	if (!currentEditRow.value) return;
	Object.assign(currentEditRow.value, {
		name: formData.name,
		school: formData.school,
		category: formData.category,
		changeReason: formData.changeReason,
		updatedAt: new Date().toLocaleString(),
	});
	ElMessage.success("修改成功");
	editFormDialog.value?.closeDialog();
};

const cache = localStorage.getItem("materialManageColumns");
if (cache) allColumns.value = JSON.parse(cache);
</script>

<style scoped>
.material-page {
	padding: 16px;
}

.filter-toolbar-body {
	display: flex;
	flex-wrap: wrap;
	align-items: flex-start;
	gap: 12px 16px;
	width: 100%;
}

.filter-grid {
	flex: 1;
	min-width: 240px;
}

.search-input-group {
	display: flex;
	align-items: center;
	gap: 8px;
}

.batch-row {
	display: flex;
	flex-wrap: wrap;
	align-items: center;
	gap: 8px;
	flex-shrink: 0;
	padding-top: 4px;
}

.table-card {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
}
</style>
