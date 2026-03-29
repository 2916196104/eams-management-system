<template>
	<div class="transcript">
		<!-- 搜索行 -->
		<div class="search-row">
			<div class="search-box">
				<div class="search-item">
					<span class="search-label">考核项</span>
					<el-input v-model="searchForm.title" placeholder="请输入考核项名称" clearable />
				</div>
				<div class="search-item">
					<span class="search-label">发布者</span>
					<el-input v-model="searchForm.creatorName" placeholder="请输入发布者" clearable />
				</div>
			</div>
			<div class="search-actions">
				<el-button type="primary" :icon="Search" @click="handleSearch">搜索</el-button>
				<el-button :icon="Delete" @click="handleResetSearch">重置</el-button>
			</div>
		</div>

		<!-- 操作行 -->
		<div class="action-row">
			<el-button type="primary" :icon="Plus" @click="handleAdd">新增考核项</el-button>
			<el-button type="danger" :icon="Delete" :disabled="selectedRows.length === 0" @click="handleBatchDelete">
				删除
			</el-button>
		</div>

		<!-- 表格区域 -->
		<F1Table
			:config="tableConfig"
			:data="tableData"
			:loading="loading"
			@page-change="handlePageChange"
			@selection-change="handleSelectionChange"
		>
			<template #title="{ row }">
				<el-text type="primary">{{ row.title }}</el-text>
			</template>
			<template #action="{ row }">
				<el-button type="primary" link size="small" @click="handleEdit(row)">编辑</el-button>
				<el-button type="success" link size="small" @click="handleImport(row)">导入成绩</el-button>
				<el-button type="primary" link size="small" @click="handleDetail(row)">成绩列表</el-button>
			</template>
		</F1Table>

		<!-- 新增/编辑考核项弹窗 -->
		<el-dialog v-model="formDialogVisible" :title="formDialogTitle" width="500px" destroy-on-close>
			<MyForm
				:model="formData"
				:items="formItems"
				:rules="formRules"
				:showback="false"
				:showreset="false"
				submittext="确定"
				:disableBeforeClose="true"
				@do-submit="handleFormSubmit"
			/>
		</el-dialog>

		<!-- 考核项详情弹窗（含成绩记录列表） -->
		<el-dialog v-model="detailDialogVisible" title="成绩记录" width="800px" destroy-on-close>
			<template v-if="currentGrade">
				<!-- 考核项基本信息 -->
				<el-descriptions :column="2" border>
					<el-descriptions-item label="考核项">{{ currentGrade.title }}</el-descriptions-item>
					<el-descriptions-item label="说明">{{ currentGrade.info }}</el-descriptions-item>
				</el-descriptions>

				<!-- 成绩记录列表 -->
				<div class="records-section">
					<div class="records-header">
						<div class="records-title">成绩列表</div>
						<el-button type="primary" size="small" :icon="Plus" @click="handleAddRecord">录入成绩</el-button>
					</div>
					<el-table :data="recordsData" v-loading="recordsLoading" border stripe>
						<el-table-column type="index" label="序号" width="60" />
						<el-table-column prop="studentName" label="学生姓名" width="120" />
						<el-table-column prop="score" label="分数" width="100">
							<template #default="{ row }">
								<span :class="{ 'score-pass': row.score >= 60, 'score-fail': row.score < 60 }">
									{{ row.score }}
								</span>
							</template>
						</el-table-column>
						<el-table-column prop="addTime" label="添加时间" width="170" />
						<el-table-column label="操作" width="100" fixed="right">
							<template #default="{ row }">
								<el-button type="danger" link size="small" @click="handleDeleteRecord(row)">删除</el-button>
							</template>
						</el-table-column>
					</el-table>
					<!-- 成绩记录分页 -->
					<div class="records-pagination">
						<el-pagination
							v-model:current-page="recordsPageIndex"
							v-model:page-size="recordsPageSize"
							:total="recordsTotal"
							:page-sizes="[10, 20, 50]"
							layout="total, sizes, prev, pager, next"
							@size-change="handleRecordsPageChange"
							@current-change="handleRecordsPageChange"
						/>
					</div>
				</div>
			</template>
		</el-dialog>

		<!-- 录入成绩弹窗 -->
		<el-dialog v-model="recordDialogVisible" title="录入成绩" width="450px" destroy-on-close>
			<MyForm
				:model="recordForm"
				:items="recordItems"
				:rules="recordRules"
				:showback="false"
				:showreset="false"
				submittext="确定"
				:disableBeforeClose="true"
				@do-submit="handleRecordSubmit"
			/>
		</el-dialog>

		<!-- 导入成绩弹窗 -->
		<el-dialog v-model="importDialogVisible" title="导入成绩" width="450px" destroy-on-close>
			<el-form label-width="80px">
				<el-form-item label="考核项">
					<el-input :model-value="importGradeTitle" disabled />
				</el-form-item>
				<el-form-item label="Excel">
					<el-upload
						:auto-upload="false"
						:limit="1"
						accept=".xlsx,.xls"
						:on-change="handleFileChange"
					>
						<el-button type="primary">选择文件</el-button>
					</el-upload>
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="importDialogVisible = false">取消</el-button>
				<el-button type="primary" :disabled="!importFile" @click="handleImportSubmit">确认导入</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import type { UploadFile } from "element-plus";
import { Plus, Delete, Search } from "@element-plus/icons-vue";
import F1Table from "@/components/f1table/F1Table.vue";
import { TableType } from "@/components/f1table/type";
import type { TableConfig } from "@/components/f1table/type";
import MyForm from "@/components/myform/MyForm.vue";
import type { MyFormItemAttr, MyFormInputProps, MyFormInputNumberProps } from "@/components/myform/type";
import {
	getGradeList,
	getGradeRecordList,
	saveGrade,
	deleteGrade,
	saveRecord,
	deleteRecord,
	importGrade,
} from "@/apis/interaction/transcript";
import type { GradeVO, GradeRecordVO, GradeSaveDTO, GradeRecordSaveDTO } from "@/apis/interaction/transcript/type";

// ==================== 列表相关 ====================

const searchForm = reactive({
	title: "",
	creatorName: "",
	pageIndex: 1,
	pageSize: 10,
});

const tableConfig = ref<TableConfig>({
	tableProperties: {
		stripe: true,
		border: true,
	},
	tableList: [
		{ type: TableType.selection, width: "50px", label: "选择", fixed: true },
		{ type: TableType.index, width: "60px", label: "序号", fixed: true },
		{ type: TableType.normal, prop: "title", label: "考核项", minWidth: "200px" },
		{ type: TableType.normal, prop: "info", label: "说明", minWidth: "250px" },
		{ type: TableType.normal, prop: "creatorName", label: "发布者", width: "100px" },
		{ type: TableType.normal, prop: "addTime", label: "添加时间", width: "170px" },
		{ type: TableType.custom, label: "操作", width: "220px", slotName: "action" },
	],
	pagination: {
		enabled: true,
		currentPage: 1,
		pageSize: 10,
		total: 0,
	},
});

const tableData = ref<GradeVO[]>([]);
const loading = ref(false);
const selectedRows = ref<GradeVO[]>([]);

async function loadData() {
	loading.value = true;
	try {
		const res = await getGradeList(searchForm);
		if (res.code === 10000 && res.data) {
			tableData.value = res.data.rows || [];
			tableConfig.value.pagination!.total = res.data.total;
		}
	} catch (error) {
		console.error("获取考核项列表失败:", error);
	} finally {
		loading.value = false;
	}
}

function handleSearch() {
	searchForm.pageIndex = 1;
	loadData();
}

function handleResetSearch() {
	searchForm.title = "";
	searchForm.creatorName = "";
	handleSearch();
}

function handlePageChange(page: number, size: number) {
	searchForm.pageIndex = page;
	searchForm.pageSize = size;
	loadData();
}

function handleSelectionChange(selection: GradeVO[]) {
	selectedRows.value = selection;
}

// ==================== 新增/编辑考核项 ====================

const formDialogVisible = ref(false);
const formDialogTitle = ref("新增考核项");
const formData = reactive<GradeSaveDTO>({
	id: undefined,
	title: "",
	info: "",
});

const formItems: MyFormItemAttr[] = [
	{
		prop: "title",
		label: "考核项",
		type: "input",
		required: true,
		fprops: { placeholder: "请输入考核项名称", clearable: true } as MyFormInputProps,
	},
	{
		prop: "info",
		label: "说明",
		type: "input",
		required: true,
		fprops: { placeholder: "请输入考核项说明", type: "textarea" } as MyFormInputProps,
	},
];

const formRules = {
	title: [{ required: true, message: "请输入考核项名称", trigger: "change" }],
	info: [{ required: true, message: "请输入考核项说明", trigger: "change" }],
};

function handleAdd() {
	formDialogTitle.value = "新增考核项";
	formData.id = undefined;
	formData.title = "";
	formData.info = "";
	formDialogVisible.value = true;
}

function handleEdit(row: GradeVO) {
	formDialogTitle.value = "编辑考核项";
	formData.id = row.id;
	formData.title = row.title;
	formData.info = row.info;
	formDialogVisible.value = true;
}

async function handleFormSubmit(data: GradeSaveDTO) {
	try {
		const res = await saveGrade(data);
		if (res.code === 10000) {
			ElMessage.success(data.id ? "修改成功" : "新增成功");
			formDialogVisible.value = false;
			loadData();
		} else {
			ElMessage.error(res.message || "操作失败");
		}
	} catch (error) {
		console.error("保存考核项失败:", error);
	}
}

// ==================== 删除考核项 ====================

function handleBatchDelete() {
	if (selectedRows.value.length === 0) return;
	ElMessageBox.confirm(`确定要删除选中的 ${selectedRows.value.length} 条考核项吗？关联的成绩记录也会被删除。`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(async () => {
			try {
				const ids = selectedRows.value.map((row) => row.id);
				const res = await deleteGrade({ ids });
				if (res.code === 10000) {
					ElMessage.success("删除成功");
					loadData();
				} else {
					ElMessage.error(res.message || "删除失败");
				}
			} catch (error) {
				console.error("删除考核项失败:", error);
			}
		})
		.catch(() => {});
}

// ==================== 考核项详情（含成绩记录） ====================

const detailDialogVisible = ref(false);
const currentGrade = ref<GradeVO | null>(null);
const recordsData = ref<GradeRecordVO[]>([]);
const recordsLoading = ref(false);
const recordsPageIndex = ref(1);
const recordsPageSize = ref(10);
const recordsTotal = ref(0);

async function handleDetail(row: GradeVO) {
	currentGrade.value = row;
	detailDialogVisible.value = true;
	recordsPageIndex.value = 1;
	await loadRecords();
}

async function loadRecords() {
	if (!currentGrade.value) return;
	recordsLoading.value = true;
	try {
		const res = await getGradeRecordList({
			gradeId: currentGrade.value.id,
			pageIndex: recordsPageIndex.value,
			pageSize: recordsPageSize.value,
		});
		if (res.code === 10000 && res.data) {
			recordsData.value = res.data.rows || [];
			recordsTotal.value = res.data.total;
		}
	} catch (error) {
		console.error("获取成绩记录失败:", error);
	} finally {
		recordsLoading.value = false;
	}
}

function handleRecordsPageChange() {
	loadRecords();
}

// ==================== 录入成绩 ====================

const recordDialogVisible = ref(false);
const recordForm = reactive({
	studentId: undefined as unknown as number,
	score: undefined as number | undefined,
});

const recordItems: MyFormItemAttr[] = [
	{
		prop: "studentId",
		label: "学生ID",
		type: "number",
		required: true,
		fprops: { placeholder: "请输入学生ID", min: 1, width: "100%" } as MyFormInputNumberProps,
	},
	{
		prop: "score",
		label: "分数",
		type: "number",
		required: true,
		fprops: { placeholder: "请输入分数", min: 0, max: 100, width: "100%" } as MyFormInputNumberProps,
	},
];

const recordRules = {
	studentId: [{ required: true, message: "请输入学生ID", trigger: "change" }],
	score: [{ required: true, message: "请输入分数", trigger: "change" }],
};

function handleAddRecord() {
	recordForm.studentId = undefined as unknown as number;
	recordForm.score = undefined;
	recordDialogVisible.value = true;
}

async function handleRecordSubmit(data: typeof recordForm) {
	if (!currentGrade.value) return;
	try {
		const dto: GradeRecordSaveDTO = {
			gradeId: currentGrade.value.id,
			studentId: data.studentId,
			score: data.score!,
		};
		const res = await saveRecord(dto);
		if (res.code === 10000) {
			ElMessage.success("录入成功");
			recordDialogVisible.value = false;
			loadRecords();
		} else {
			ElMessage.error(res.message || "录入失败");
		}
	} catch (error) {
		console.error("录入成绩失败:", error);
	}
}

// ==================== 删除成绩记录 ====================

function handleDeleteRecord(row: GradeRecordVO) {
	ElMessageBox.confirm(`确定要删除 ${row.studentName} 的成绩吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(async () => {
			try {
				const res = await deleteRecord({ id: row.id });
				if (res.code === 10000) {
					ElMessage.success("删除成功");
					loadRecords();
				} else {
					ElMessage.error(res.message || "删除失败");
				}
			} catch (error) {
				console.error("删除成绩记录失败:", error);
			}
		})
		.catch(() => {});
}

// ==================== 导入成绩 ====================

const importDialogVisible = ref(false);
const importGradeId = ref<number>(0);
const importGradeTitle = ref("");
const importFile = ref<File | null>(null);

function handleImport(row: GradeVO) {
	importGradeId.value = row.id;
	importGradeTitle.value = row.title;
	importFile.value = null;
	importDialogVisible.value = true;
}

function handleFileChange(file: UploadFile) {
	importFile.value = file.raw || null;
}

async function handleImportSubmit() {
	if (!importFile.value) return;
	try {
		const res = await importGrade(importGradeId.value, importFile.value);
		if (res.code === 10000) {
			ElMessage.success("导入成功");
			importDialogVisible.value = false;
			loadData();
		} else {
			ElMessage.error(res.message || "导入失败");
		}
	} catch (error) {
		console.error("导入成绩失败:", error);
	}
}

// ==================== 初始化 ====================

onMounted(() => {
	loadData();
});
</script>

<style scoped lang="scss">
.transcript {
	padding: 16px;
}

.search-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	margin-bottom: 12px;
}

.search-box {
	display: flex;
	align-items: center;
	gap: 16px;
	flex: 1;
	padding: 12px 16px;
	background: #fff;
	border: 1px solid #e4e7ed;
	border-radius: 4px;
}

.search-item {
	display: flex;
	align-items: center;
	gap: 8px;

	.search-label {
		font-size: 14px;
		color: #606266;
		white-space: nowrap;
	}

	.el-input {
		width: 180px;
	}
}

.search-actions {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-left: 16px;
}

.action-row {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-bottom: 12px;
}

.records-section {
	margin-top: 20px;
}

.records-header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	margin-bottom: 12px;
}

.records-title {
	font-size: 16px;
	font-weight: 600;
	color: #303133;
}

.records-pagination {
	display: flex;
	justify-content: flex-end;
	margin-top: 12px;
}

.score-pass {
	color: #67c23a;
	font-weight: 600;
}

.score-fail {
	color: #f56c6c;
	font-weight: 600;
}
</style>
