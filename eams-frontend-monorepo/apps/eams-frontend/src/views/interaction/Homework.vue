<template>
	<div class="homework">
		<!-- 搜索行：左搜索框 + 右按钮 -->
		<div class="search-row">
			<div class="search-box">
				<div class="search-item">
					<span class="search-label">搜索标题</span>
					<el-input v-model="searchForm.title" placeholder="请输入标题" clearable />
				</div>
				<div class="search-item">
					<span class="search-label">班级</span>
					<el-input v-model="searchForm.className" placeholder="请输入班级" clearable />
				</div>
				<div class="search-item">
					<span class="search-label">发布者</span>
					<el-input v-model="searchForm.teacherName" placeholder="请输入发布者" clearable />
				</div>
			</div>
			<div class="search-actions">
				<el-button type="primary" :icon="Search" @click="handleSearch">搜索</el-button>
				<el-button :icon="Delete" @click="handleResetSearch">删除</el-button>
			</div>
		</div>

		<!-- 操作行 -->
		<div class="action-row">
			<el-button type="primary" :icon="Plus" @click="handleAdd">布置作业</el-button>
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
			@edit="handleDetail"
			@selection-change="handleSelectionChange"
		>
			<template #title="{ row }">
				<el-text type="primary">{{ row.title }}</el-text>
			</template>
		</F1Table>

		<!-- 新增/编辑作业弹窗 -->
		<el-dialog v-model="formDialogVisible" :title="formDialogTitle" width="500px" destroy-on-close>
			<MyForm
				:model="formData"
				:items="formItems"
				:rules="formRules"
				:showback="false"
				:showreset="false"
				submittext="确定"
				:disableBeforeClose="true"
				@do-submit="handleSubmit"
			/>
		</el-dialog>

		<!-- 作业详情弹窗 -->
		<el-dialog v-model="detailDialogVisible" title="作业详情" width="800px" destroy-on-close>
			<template v-if="homeworkDetail">
				<!-- 作业基本信息 -->
				<el-descriptions :column="3" border>
					<el-descriptions-item label="作业标题" :span="3">{{ homeworkDetail.title }}</el-descriptions-item>
					<el-descriptions-item label="班级">{{ homeworkDetail.className }}</el-descriptions-item>
					<el-descriptions-item label="教师">{{ homeworkDetail.teacherName }}</el-descriptions-item>
					<el-descriptions-item label="已提交">{{ homeworkDetail.completeCount }}</el-descriptions-item>
					<el-descriptions-item label="内容" :span="3">{{ homeworkDetail.content }}</el-descriptions-item>
				</el-descriptions>

				<!-- 提交记录列表 -->
				<div class="records-section">
					<div class="records-title">提交记录</div>
					<el-table :data="recordsData" v-loading="recordsLoading" border stripe>
						<el-table-column type="index" label="序号" width="60" />
						<el-table-column prop="studentName" label="学生姓名" width="100" />
						<el-table-column prop="content" label="提交内容" min-width="150" show-overflow-tooltip />
						<el-table-column prop="addTime" label="提交时间" width="170" />
						<el-table-column prop="score" label="评分" width="80">
							<template #default="{ row }">{{ row.score ?? "-" }}</template>
						</el-table-column>
						<el-table-column prop="comment" label="点评" min-width="120" show-overflow-tooltip>
							<template #default="{ row }">{{ row.comment || "-" }}</template>
						</el-table-column>
						<el-table-column label="操作" width="80" fixed="right">
							<template #default="{ row }">
								<el-button type="primary" link size="small" @click="handleOpenComment(row)">点评</el-button>
							</template>
						</el-table-column>
					</el-table>
					<!-- 提交记录分页 -->
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

		<!-- 点评弹窗 -->
		<el-dialog v-model="commentDialogVisible" title="点评作业" width="450px" destroy-on-close>
			<MyForm
				:model="commentForm"
				:items="commentItems"
				:rules="commentRules"
				:showback="false"
				:showreset="false"
				submittext="确定"
				:disableBeforeClose="true"
				@do-submit="handleCommentSubmit"
			/>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Plus, Delete, Search } from "@element-plus/icons-vue";
import F1Table from "@/components/f1table/F1Table.vue";
import { TableType } from "@/components/f1table/type";
import type { TableConfig } from "@/components/f1table/type";
import MyForm from "@/components/myform/MyForm.vue";
import type { MyFormItemAttr, MyFormInputProps, MyFormInputNumberProps } from "@/components/myform/type";
import {
	listHomework,
	getHomeworkInfo,
	listHomeworkRecords,
	saveHomework,
	deleteHomework,
	updateComment,
} from "@/apis/interaction/homework";
import type {
	HomeworkVO,
	HomeworkRecordVO,
	HomeworkSaveDTO,
	HomeworkCommentDTO,
} from "@/apis/interaction/homework/type";

// ==================== 列表相关 ====================

const searchForm = reactive({
	title: "",
	className: "",
	teacherName: "",
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
		{ type: TableType.normal, prop: "title", label: "标题", minWidth: "200px" },
		{ type: TableType.normal, prop: "className", label: "班级", width: "120px" },
		{ type: TableType.normal, prop: "teacherName", label: "教师", width: "100px" },
		{ type: TableType.normal, prop: "completeCount", label: "已提交", width: "80px" },
		{ type: TableType.normal, prop: "addTime", label: "发布时间", width: "170px" },
		{ type: TableType.handler as any, label: "操作", width: "120px", editText: "详情" },
	],
	pagination: {
		enabled: true,
		currentPage: 1,
		pageSize: 10,
		total: 0,
	},
	handler: {
		edit: true,
		view: false,
		delete: false,
		editText: "详情",
	},
});

const tableData = ref<HomeworkVO[]>([]);
const loading = ref(false);
const selectedRows = ref<HomeworkVO[]>([]);

async function loadData() {
	loading.value = true;
	try {
		const res = await listHomework(searchForm);
		if (res.code === 10000 && res.data) {
			tableData.value = res.data.rows || [];
			tableConfig.value.pagination!.total = res.data.total;
		}
	} catch (error) {
		console.error("获取作业列表失败:", error);
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
	searchForm.className = "";
	searchForm.teacherName = "";
	handleSearch();
}

function handlePageChange(page: number, size: number) {
	searchForm.pageIndex = page;
	searchForm.pageSize = size;
	loadData();
}

function handleSelectionChange(selection: HomeworkVO[]) {
	selectedRows.value = selection;
}

// ==================== 新增/编辑作业 ====================

const formDialogVisible = ref(false);
const formDialogTitle = ref("新增作业");
const formData = reactive<HomeworkSaveDTO>({
	id: undefined,
	title: "",
	content: "",
	classId: undefined as unknown as number,
});

const formItems: MyFormItemAttr[] = [
	{
		prop: "title",
		label: "标题",
		type: "input",
		required: true,
		fprops: { placeholder: "请输入作业标题", clearable: true } as MyFormInputProps,
	},
	{
		prop: "content",
		label: "内容",
		type: "input",
		required: true,
		fprops: { placeholder: "请输入作业内容", type: "textarea" } as MyFormInputProps,
	},
	{
		prop: "classId",
		label: "班级",
		type: "number",
		required: true,
		fprops: { placeholder: "请输入班级ID", min: 1, width: "100%" } as MyFormInputNumberProps,
	},
];

const formRules = {
	title: [{ required: true, message: "请输入作业标题", trigger: "change" }],
	content: [{ required: true, message: "请输入作业内容", trigger: "change" }],
	classId: [{ required: true, message: "请输入班级ID", trigger: "change" }],
};

function handleAdd() {
	formDialogTitle.value = "新增作业";
	formData.id = undefined;
	formData.title = "";
	formData.content = "";
	formData.classId = undefined as unknown as number;
	formDialogVisible.value = true;
}

async function handleSubmit(data: HomeworkSaveDTO) {
	try {
		const res = await saveHomework(data);
		if (res.code === 10000) {
			ElMessage.success(data.id ? "修改成功" : "新增成功");
			formDialogVisible.value = false;
			loadData();
		} else {
			ElMessage.error(res.message || "操作失败");
		}
	} catch (error) {
		console.error("保存作业失败:", error);
	}
}

// ==================== 删除作业 ====================

function handleBatchDelete() {
	if (selectedRows.value.length === 0) return;
	ElMessageBox.confirm(`确定要删除选中的 ${selectedRows.value.length} 条作业吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(async () => {
			try {
				// 逐条删除（API 文档中删除接口未明确支持批量）
				for (const row of selectedRows.value) {
					await deleteHomework({ id: row.id, name: row.title });
				}
				ElMessage.success("删除成功");
				loadData();
			} catch (error) {
				console.error("删除作业失败:", error);
			}
		})
		.catch(() => {});
}

// ==================== 作业详情（含提交记录） ====================

const detailDialogVisible = ref(false);
const homeworkDetail = ref<HomeworkVO | null>(null);
const recordsData = ref<HomeworkRecordVO[]>([]);
const recordsLoading = ref(false);
const recordsPageIndex = ref(1);
const recordsPageSize = ref(10);
const recordsTotal = ref(0);
const currentHomeworkId = ref<number>(0);

async function handleDetail(row: HomeworkVO) {
	currentHomeworkId.value = row.id;
	detailDialogVisible.value = true;
	recordsPageIndex.value = 1;
	await loadHomeworkDetail(row.id);
	await loadRecords();
}

async function loadHomeworkDetail(id: number) {
	recordsLoading.value = true;
	try {
		const res = await getHomeworkInfo(id);
		if (res.code === 10000 && res.data) {
			homeworkDetail.value = res.data;
		}
	} catch (error) {
		console.error("获取作业详情失败:", error);
	} finally {
		recordsLoading.value = false;
	}
}

async function loadRecords() {
	recordsLoading.value = true;
	try {
		const res = await listHomeworkRecords({
			homeworkId: currentHomeworkId.value,
			pageIndex: recordsPageIndex.value,
			pageSize: recordsPageSize.value,
		});
		if (res.code === 10000 && res.data) {
			recordsData.value = res.data.rows || [];
			recordsTotal.value = res.data.total;
		}
	} catch (error) {
		console.error("获取提交记录失败:", error);
	} finally {
		recordsLoading.value = false;
	}
}

function handleRecordsPageChange() {
	loadRecords();
}

// ==================== 点评作业 ====================

const commentDialogVisible = ref(false);
const currentRecordId = ref<number>(0);
const commentForm = reactive({
	studentName: "",
	score: undefined as number | undefined,
	comment: "",
});

const commentItems: MyFormItemAttr[] = [
	{
		prop: "studentName",
		label: "学生",
		type: "input",
		fprops: { placeholder: "学生姓名", disabled: true } as MyFormInputProps,
	},
	{
		prop: "score",
		label: "评分",
		type: "number",
		required: true,
		fprops: { placeholder: "请输入评分", min: 0, max: 100, width: "100%" } as MyFormInputNumberProps,
	},
	{
		prop: "comment",
		label: "点评",
		type: "input",
		required: true,
		fprops: { placeholder: "请输入点评内容", type: "textarea" } as MyFormInputProps,
	},
];

const commentRules = {
	score: [{ required: true, message: "请输入评分", trigger: "change" }],
	comment: [{ required: true, message: "请输入点评内容", trigger: "change" }],
};

function handleOpenComment(row: HomeworkRecordVO) {
	currentRecordId.value = row.id;
	commentForm.studentName = row.studentName;
	commentForm.score = row.score ?? undefined;
	commentForm.comment = row.comment || "";
	commentDialogVisible.value = true;
}

async function handleCommentSubmit(data: typeof commentForm) {
	try {
		const dto: HomeworkCommentDTO = {
			id: currentRecordId.value,
			name: data.comment,
		};
		const res = await updateComment(dto);
		if (res.code === 10000) {
			ElMessage.success("点评成功");
			commentDialogVisible.value = false;
			loadRecords();
		} else {
			ElMessage.error(res.message || "点评失败");
		}
	} catch (error) {
		console.error("点评失败:", error);
	}
}

// ==================== 初始化 ====================

onMounted(() => {
	loadData();
});
</script>

<style scoped lang="scss">
.homework {
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

.records-title {
	font-size: 16px;
	font-weight: 600;
	margin-bottom: 12px;
	color: #303133;
}

.records-pagination {
	display: flex;
	justify-content: flex-end;
	margin-top: 12px;
}
</style>
