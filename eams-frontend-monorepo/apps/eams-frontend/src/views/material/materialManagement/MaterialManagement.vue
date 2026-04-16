<template>
	<section class="material-page">
		<FilterToolbar
			:collapsible-item-count="2"
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
							<el-input v-model="form.materialLabel" placeholder="请输入物料名称" clearable />
						</div>

						<div v-show="showAll || 1 < limit" class="filter-cell">
							<span class="filter-label">状态</span>
							<el-select v-model="form.status" placeholder="请选择" clearable style="width: 100%">
								<el-option label="启用" :value="1" />
								<el-option label="禁用" :value="0" />
							</el-select>
						</div>
					</div>

					<div class="batch-row">
						<el-button type="primary" @click="handleCreate">+ 新增</el-button>
						<el-button @click="handleBatchDelete">删除</el-button>
						<el-button type="success" @click="handleBatchEnable">启用</el-button>
						<el-button type="warning" @click="handleBatchDisable">禁用</el-button>
					</div>
				</div>
			</template>
		</FilterToolbar>

		<section class="table-card">
			<el-table
				ref="tableRef"
				v-loading="tableLoading"
				:data="tableRows"
				stripe
				row-key="id"
				@selection-change="handleSelectionChange"
			>
				<el-table-column type="selection" width="48" />

				<el-table-column
					v-for="(col, idx) in visibleColumns"
					:key="idx"
					:label="col.label"
					:prop="col.prop"
					:width="col.width || undefined"
					:min-width="col.minWidth || undefined"
					show-overflow-tooltip
				>
					<template #default="{ row }">
						<el-tag v-if="col.prop === 'statusText'" :type="row.state ? 'success' : 'info'" effect="light">
							{{ row.statusText }}
						</el-tag>
						<el-avatar v-else-if="col.prop === 'cover'" :size="36" shape="square" :src="row.cover || undefined">
							图
						</el-avatar>
						<span v-else>{{ row[col.prop] || "-" }}</span>
					</template>
				</el-table-column>

				<el-table-column label="操作" width="220" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="handleEdit(row)">编辑</el-button>
						<el-button link type="primary" @click="handleInbound(row)">入库</el-button>
						<el-button link type="primary" @click="handleOutbound(row)">出库</el-button>
					</template>
				</el-table-column>
			</el-table>

			<div class="table-pagination">
				<el-pagination
					v-model:current-page="pagination.pageIndex"
					v-model:page-size="pagination.pageSize"
					background
					layout="total, sizes, prev, pager, next, jumper"
					:page-sizes="[10, 20, 50, 100]"
					:total="pagination.total"
					@size-change="handlePageSizeChange"
					@current-change="handlePageChange"
				/>
			</div>
		</section>

		<PrintTable ref="printRef" print-title="物料管理列表" :column-list="allColumns" :table-data="tableRows" />

		<ColumnSetting
			v-model="columnSettingVisible"
			:columns="allColumns"
			@change="handleColumnChange"
			@confirm="handleColumnConfirm"
			@reset="handleColumnReset"
		/>

		<MyFormDialog ref="saveFormDialog" :="saveFormDialogProps" @confirm="onSaveSubmit" />
		<MyFormDialog ref="inboundFormDialog" :="inboundFormDialogProps" @confirm="onInboundSubmit" />
		<MyFormDialog ref="outboundFormDialog" :="outboundFormDialogProps" @confirm="onOutboundSubmit" />
	</section>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import FilterToolbar from "@/views/material/components/FilterToolbar.vue";
import MyFormDialog from "@/components/mydialog/MyFormDialog.vue";
import type { MyFormItemAttr } from "@/components/myform/type";
import type { MyFormDialogProps } from "@/components/mydialog/type";
import type { MyFormInputProps } from "@/components/myform/props/input.ts";
import type { MyFormSelectProps } from "@/components/myform/props/select.ts";
import {
	deleteMaterials,
	getMaterialDetail,
	getMaterialPage,
	materialInStorage,
	materialOutStorage,
	saveMaterial,
	updateMaterialState,
} from "@/apis/material/materialManagement";
import type {
	MaterialDetail,
	MaterialItem,
	MaterialSaveDTO,
	MaterialStateValue,
} from "@/apis/material/materialManagement/type";

import ColumnSetting from "../../operation/components/ColumnSetting.vue";
import PrintTable from "../../operation/components/PrintTable.vue";

interface MaterialTableRow extends MaterialItem {
	id: number;
	index: number;
	name: string;
	info: string;
	cover: string;
	state: boolean;
	statusText: string;
	categoryText: string;
	schoolText: string;
}

interface MaterialFormData {
	categoryId?: number;
	cover: string;
	id?: number;
	info: string;
	name: string;
	schoolId?: number;
	state: boolean;
}

interface StockFormData {
	amount?: number;
}

interface ColumnItem {
	label: string;
	prop: string;
	width?: number;
	minWidth?: number;
	visible: boolean;
}

type SaveDialogMode = "create" | "edit";

const COLUMN_STORAGE_KEY = "materialManageColumnsV2";

const createDefaultColumns = (): ColumnItem[] => [
	{ label: "序号", prop: "index", width: 60, visible: true },
	{ label: "封面", prop: "cover", width: 80, visible: true },
	{ label: "物料名称", prop: "name", minWidth: 140, visible: true },
	{ label: "分类ID", prop: "categoryText", minWidth: 100, visible: true },
	{ label: "学校ID", prop: "schoolText", minWidth: 100, visible: true },
	{ label: "物料说明", prop: "info", minWidth: 180, visible: true },
	{ label: "状态", prop: "statusText", width: 90, visible: true },
];

const createEmptyMaterialForm = (): MaterialFormData => ({
	categoryId: undefined,
	cover: "",
	id: undefined,
	info: "",
	name: "",
	schoolId: undefined,
	state: true,
});

const tableRef = ref();
const printRef = ref();
const saveFormDialog = ref();
const inboundFormDialog = ref();
const outboundFormDialog = ref();

const form = reactive({
	materialLabel: "",
	status: "" as "" | MaterialStateValue,
});

const pagination = reactive({
	pageIndex: 1,
	pageSize: 10,
	total: 0,
});

const tableLoading = ref(false);
const tableRows = ref<MaterialTableRow[]>([]);
const selectedRows = ref<MaterialTableRow[]>([]);
const currentMaterialId = ref<number | null>(null);
const saveDialogMode = ref<SaveDialogMode>("create");

const columnSettingVisible = ref(false);
const allColumns = ref<ColumnItem[]>(createDefaultColumns());
const visibleColumns = computed(() => allColumns.value.filter((column) => column.visible));

function formatValue(value?: string | number | null) {
	if (value === undefined || value === null || value === "") return "-";
	return String(value);
}

function formatStateText(state?: boolean) {
	return state ? "启用" : "禁用";
}

function normalizeMaterialRows(rows: MaterialItem[]) {
	return rows.map((item, index) => {
		const enabled = item.state === true;

		return {
			...item,
			id: Number(item.id ?? 0),
			index: (pagination.pageIndex - 1) * pagination.pageSize + index + 1,
			name: formatValue(item.name),
			info: formatValue(item.info),
			cover: item.cover ?? "",
			state: enabled,
			statusText: formatStateText(enabled),
			categoryText: formatValue(item.categoryId),
			schoolText: formatValue(item.schoolId),
		};
	});
}

function toMaterialFormData(item?: MaterialDetail): MaterialFormData {
	return {
		categoryId: item?.categoryId,
		cover: item?.cover ?? "",
		id: item?.id,
		info: item?.info ?? "",
		name: item?.name ?? "",
		schoolId: item?.schoolId,
		state: item?.state ?? true,
	};
}

function buildSavePayload(formData: MaterialFormData): MaterialSaveDTO | null {
	const name = formData.name.trim();
	const categoryId = Number(formData.categoryId);
	const schoolId = Number(formData.schoolId);

	if (!name) {
		ElMessage.warning("请输入物料名称");
		return null;
	}
	if (!Number.isFinite(categoryId) || categoryId <= 0) {
		ElMessage.warning("请输入正确的分类ID");
		return null;
	}
	if (!Number.isFinite(schoolId) || schoolId <= 0) {
		ElMessage.warning("请输入正确的学校ID");
		return null;
	}

	return {
		categoryId,
		cover: formData.cover.trim() || undefined,
		id: formData.id,
		info: formData.info.trim() || undefined,
		name,
		schoolId,
		state: Boolean(formData.state),
	};
}

async function confirmAction(message: string) {
	try {
		await ElMessageBox.confirm(message, "提示", { type: "warning" });
		return true;
	} catch {
		return false;
	}
}

function clearTableSelection() {
	selectedRows.value = [];
	tableRef.value?.clearSelection?.();
}

async function loadMaterials(showSuccessMessage = false) {
	tableLoading.value = true;

	try {
		const res = await getMaterialPage({
			pageIndex: pagination.pageIndex,
			pageSize: pagination.pageSize,
		});

		let rows = normalizeMaterialRows(res.data?.rows ?? []);

		// The backend docs for /material/list currently only give stable page params.
		// The page keeps name/state as client-side filters until backend筛选字段明确.
		const keyword = form.materialLabel.trim();
		if (keyword) {
			rows = rows.filter((row) => row.name.includes(keyword));
		}
		if (form.status !== "") {
			rows = rows.filter((row) => row.state === (form.status === 1));
		}

		tableRows.value = rows;
		pagination.total = res.data?.total ?? 0;
		clearTableSelection();

		if (showSuccessMessage) {
			ElMessage.success("查询成功");
		}
	} catch (error) {
		console.error(error);
		ElMessage.error("查询失败");
	} finally {
		tableLoading.value = false;
	}
}

function handleSelectionChange(rows: MaterialTableRow[]) {
	selectedRows.value = rows;
}

function getSelectedIds() {
	return selectedRows.value.map((row) => Number(row.id)).filter((id) => Number.isFinite(id) && id > 0);
}

const handleColumnSetting = () => {
	columnSettingVisible.value = true;
};

const handleColumnChange = (newColumns: ColumnItem[]) => {
	allColumns.value = newColumns;
};

const handleColumnConfirm = (newColumns: ColumnItem[]) => {
	allColumns.value = newColumns;
	localStorage.setItem(COLUMN_STORAGE_KEY, JSON.stringify(newColumns));
};

const handleColumnReset = () => {
	allColumns.value = createDefaultColumns();
	localStorage.removeItem(COLUMN_STORAGE_KEY);
};

const handlePrint = () => {
	printRef.value?.handlePrint();
};

const materialFormData = reactive<MaterialFormData>(createEmptyMaterialForm());

const saveFormDialogProps = reactive<MyFormDialogProps<MaterialFormData>>({
	data: materialFormData,
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "input",
			prop: "name",
			label: "物料名称",
			rules: [{ required: true, message: "请输入物料名称", trigger: "blur" }],
			fprops: { placeholder: "请输入物料名称", width: "100%" } as MyFormInputProps,
		},
		{
			type: "number",
			prop: "categoryId",
			label: "分类ID",
			rules: [{ required: true, message: "请输入分类ID", trigger: "blur" }],
			fprops: { placeholder: "请输入分类ID", width: "100%" } as MyFormInputProps,
		},
		{
			type: "number",
			prop: "schoolId",
			label: "学校ID",
			rules: [{ required: true, message: "请输入学校ID", trigger: "blur" }],
			fprops: { placeholder: "请输入学校ID", width: "100%" } as MyFormInputProps,
		},
		{
			type: "select",
			prop: "state",
			label: "状态",
			fprops: {
				placeholder: "请选择状态",
				width: "100%",
				options: [
					{ label: "启用", value: true },
					{ label: "禁用", value: false },
				],
			} as MyFormSelectProps,
		},
		{
			type: "input",
			prop: "cover",
			label: "封面图",
			fprops: { placeholder: "请输入封面图URL", width: "100%" } as MyFormInputProps,
		},
		{
			type: "input",
			prop: "info",
			label: "物料说明",
			fprops: { type: "textarea", rows: 4, placeholder: "请输入物料说明", width: "100%" } as MyFormInputProps,
		},
	]),
	formattr: { disabled: false, "label-width": "90px" },
	title: "新增物料",
	width: "35vw",
	reset: false,
	submitText: "提交",
	cancelText: "取消",
});

function openCreateDialog() {
	saveDialogMode.value = "create";
	saveFormDialogProps.title = "新增物料";
	Object.assign(materialFormData, createEmptyMaterialForm());
	saveFormDialog.value?.openDialog(true);
}

const handleCreate = () => {
	openCreateDialog();
};

const handleSearch = async () => {
	pagination.pageIndex = 1;
	await loadMaterials(true);
};

const handleReset = async () => {
	form.materialLabel = "";
	form.status = "";
	pagination.pageIndex = 1;
	await loadMaterials();
	ElMessage.info("已重置筛选条件");
};

const handleRefresh = async () => {
	await loadMaterials();
};

const handlePageSizeChange = async (pageSize: number) => {
	pagination.pageSize = pageSize;
	pagination.pageIndex = 1;
	await loadMaterials();
};

const handlePageChange = async (pageIndex: number) => {
	pagination.pageIndex = pageIndex;
	await loadMaterials();
};

const handleBatchDelete = async () => {
	const ids = getSelectedIds();
	if (!ids.length) {
		ElMessage.warning("请选择要删除的物料");
		return;
	}

	if (!(await confirmAction("确认删除选中的物料吗？"))) {
		return;
	}

	try {
		await deleteMaterials(ids);
		ElMessage.success("删除成功");
		await loadMaterials();
	} catch (error) {
		console.error(error);
		ElMessage.error("删除失败");
	}
};

async function handleBatchToggle(state: MaterialStateValue) {
	const ids = getSelectedIds();
	if (!ids.length) {
		ElMessage.warning(state === 1 ? "请选择要启用的物料" : "请选择要禁用的物料");
		return;
	}

	if (!(await confirmAction(state === 1 ? "确认启用选中的物料吗？" : "确认禁用选中的物料吗？"))) {
		return;
	}

	try {
		await updateMaterialState(ids, state);
		ElMessage.success(state === 1 ? "启用成功" : "禁用成功");
		await loadMaterials();
	} catch (error) {
		console.error(error);
		ElMessage.error(state === 1 ? "启用失败" : "禁用失败");
	}
}

const handleBatchEnable = async () => {
	await handleBatchToggle(1);
};

const handleBatchDisable = async () => {
	await handleBatchToggle(0);
};

const inboundFormData = reactive<StockFormData>({
	amount: undefined,
});

const inboundFormDialogProps = reactive<MyFormDialogProps<StockFormData>>({
	data: inboundFormData,
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "number",
			prop: "amount",
			label: "入库数量",
			fprops: { placeholder: "请输入入库数量", width: "100%" } as MyFormInputProps,
		},
	]),
	formattr: { disabled: false, "label-width": "80px" },
	title: "物料入库",
	width: "35vw",
	reset: false,
	submitText: "提交",
	cancelText: "取消",
});

const outboundFormData = reactive<StockFormData>({
	amount: undefined,
});

const outboundFormDialogProps = reactive<MyFormDialogProps<StockFormData>>({
	data: outboundFormData,
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "number",
			prop: "amount",
			label: "出库数量",
			fprops: { placeholder: "请输入出库数量", width: "100%" } as MyFormInputProps,
		},
	]),
	formattr: { disabled: false, "label-width": "80px" },
	title: "物料出库",
	width: "35vw",
	reset: false,
	submitText: "提交",
	cancelText: "取消",
});

const handleEdit = async (row: MaterialTableRow) => {
	if (!row.id) {
		ElMessage.warning("当前物料缺少 ID");
		return;
	}

	try {
		const res = await getMaterialDetail(row.id);
		saveDialogMode.value = "edit";
		saveFormDialogProps.title = "编辑物料";
		Object.assign(materialFormData, toMaterialFormData(res.data));
		saveFormDialog.value?.openDialog(true);
	} catch (error) {
		console.error(error);
		ElMessage.error("获取物料详情失败");
	}
};

const handleInbound = (row: MaterialTableRow) => {
	if (!row.id) {
		ElMessage.warning("当前物料缺少 ID");
		return;
	}

	currentMaterialId.value = row.id;
	inboundFormData.amount = undefined;
	inboundFormDialog.value?.openDialog(true);
};

const handleOutbound = (row: MaterialTableRow) => {
	if (!row.id) {
		ElMessage.warning("当前物料缺少 ID");
		return;
	}

	currentMaterialId.value = row.id;
	outboundFormData.amount = undefined;
	outboundFormDialog.value?.openDialog(true);
};

const onSaveSubmit = async (formData: MaterialFormData) => {
	const payload = buildSavePayload(formData);
	if (!payload) {
		return;
	}

	try {
		await saveMaterial(payload);
		ElMessage.success(saveDialogMode.value === "create" ? "新增成功" : "保存成功");
		saveFormDialog.value?.closeDialog?.();
		await loadMaterials();
	} catch (error) {
		console.error(error);
		ElMessage.error(saveDialogMode.value === "create" ? "新增失败" : "保存失败");
	}
};

const onInboundSubmit = async (formData: StockFormData) => {
	if (!currentMaterialId.value) {
		ElMessage.warning("未选择物料");
		return;
	}

	const amount = Number(formData.amount);
	if (!Number.isFinite(amount) || amount <= 0) {
		ElMessage.warning("请输入正确的入库数量");
		return;
	}

	try {
		await materialInStorage([currentMaterialId.value], amount);
		ElMessage.success("入库成功");
		inboundFormDialog.value?.closeDialog?.();
		await loadMaterials();
	} catch (error) {
		console.error(error);
		ElMessage.error("入库失败");
	}
};

const onOutboundSubmit = async (formData: StockFormData) => {
	if (!currentMaterialId.value) {
		ElMessage.warning("未选择物料");
		return;
	}

	const amount = Number(formData.amount);
	if (!Number.isFinite(amount) || amount <= 0) {
		ElMessage.warning("请输入正确的出库数量");
		return;
	}

	try {
		await materialOutStorage([currentMaterialId.value], amount);
		ElMessage.success("出库成功");
		outboundFormDialog.value?.closeDialog?.();
		await loadMaterials();
	} catch (error) {
		console.error(error);
		ElMessage.error("出库失败");
	}
};

onMounted(async () => {
	const cache = localStorage.getItem(COLUMN_STORAGE_KEY);
	if (cache) {
		try {
			const parsed = JSON.parse(cache);
			if (Array.isArray(parsed)) {
				allColumns.value = parsed;
			}
		} catch (error) {
			console.warn("Failed to restore material column settings:", error);
		}
	}

	await loadMaterials();
});
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

.table-pagination {
	display: flex;
	justify-content: flex-end;
	margin-top: 16px;
}
</style>
