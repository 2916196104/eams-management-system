<template>
	<div class="announcement-management">
		<!-- 搜索行 -->
		<div class="search-row">
			<div class="search-box">
				<div class="search-item">
					<span class="search-label">公告标题</span>
					<el-input v-model="searchForm.title" placeholder="请输入标题" clearable />
				</div>
				<div class="search-item">
					<span class="search-label">公告类型</span>
					<el-select v-model="searchForm.type" placeholder="请选择类型" clearable>
						<el-option v-for="item in typeOptions" :key="item" :label="item" :value="item" />
					</el-select>
				</div>
				<div class="search-item">
					<span class="search-label">发布人</span>
					<el-input v-model="searchForm.publisher" placeholder="请输入发布人" clearable />
				</div>
			</div>
			<div class="search-actions">
				<el-button type="primary" :icon="Search" @click="handleSearch">搜索</el-button>
				<el-button :icon="Delete" @click="handleResetSearch">删除</el-button>
			</div>
		</div>

		<!-- 操作行 -->
		<div class="action-row">
			<el-button type="primary" :icon="Plus" @click="handleAdd">新增</el-button>
			<el-button type="danger" :icon="Delete" :disabled="selectedRows.length === 0" @click="handleBatchDelete">
				删除
			</el-button>
			<el-button type="success" :disabled="selectedRows.length === 0" @click="handleBatchStatus(1)">
				启用
			</el-button>
			<el-button type="warning" :disabled="selectedRows.length === 0" @click="handleBatchStatus(0)">
				停用
			</el-button>
			<el-button :disabled="selectedRows.length === 0" @click="handleSendMessage">
				发系统消息
			</el-button>
		</div>

		<!-- 表格区域 -->
		<F1Table
			:config="tableConfig"
			:data="tableData"
			:loading="loading"
			@page-change="handlePageChange"
			@edit="handleEdit"
			@selection-change="handleSelectionChange"
		>
			<template #image="{ row }">
				<el-image
					v-if="row.image"
					:src="row.image"
					:preview-src-list="[row.image]"
					fit="cover"
					class="notice-image"
				/>
				<span v-else class="no-image">暂无图片</span>
			</template>
			<template #title="{ row }">
				<el-text type="primary">{{ row.title }}</el-text>
			</template>
			<template #status="{ row }">
				<el-tag :type="row.status === 1 ? 'success' : 'info'">{{ row.status === 1 ? "启用" : "停用" }}</el-tag>
			</template>
		</F1Table>

		<!-- 新增/编辑公告弹窗 -->
		<el-dialog v-model="formDialogVisible" :title="formDialogTitle" width="600px" destroy-on-close>
			<el-form ref="formRef" :model="formData" :rules="formRules" label-width="100px">
				<el-form-item label="公告标题" prop="title">
					<el-input v-model="formData.title" placeholder="请输入公告标题" clearable />
				</el-form-item>
				<el-form-item label="类型" prop="type">
					<el-select v-model="formData.type" placeholder="请选择类型" style="width: 100%">
						<el-option v-for="item in typeOptions" :key="item" :label="item" :value="item" />
					</el-select>
				</el-form-item>
				<el-form-item label="文章编码" prop="articleCode">
					<el-input v-model="formData.articleCode" placeholder="用于文章引用，非必填" clearable />
				</el-form-item>
				<el-form-item label="图片" prop="image">
					<el-upload
						class="notice-uploader"
						action="#"
						:auto-upload="false"
						:show-file-list="false"
						accept="image/*"
						:on-change="handleImageChange"
					>
						<el-image v-if="formData.image" :src="formData.image" fit="cover" class="notice-uploader-preview" />
						<el-icon v-else class="notice-uploader-icon"><Plus /></el-icon>
					</el-upload>
					<div v-if="formData.image" class="image-clear">
						<el-button type="danger" link size="small" @click="formData.image = ''">移除图片</el-button>
					</div>
				</el-form-item>
				<el-form-item label="公告内容" prop="content">
					<el-input
						v-model="formData.content"
						type="textarea"
						:rows="5"
						placeholder="请输入公告内容"
					/>
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="formDialogVisible = false">取消</el-button>
				<el-button type="primary" @click="handleSubmit">确定</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import type { FormInstance, UploadFile } from "element-plus";
import { Plus, Delete, Search } from "@element-plus/icons-vue";
import F1Table from "@/components/f1table/F1Table.vue";
import { TableType } from "@/components/f1table/type";
import type { TableConfig } from "@/components/f1table/type";
import { listNotice, saveNotice, modifyNotice, removeNotice } from "@/apis/interaction/notice";
import type { NoticeVO, NoticeSaveDTO } from "@/apis/interaction/notice/type";

// ==================== 公告类型选项 ====================

const typeOptions = ["通知", "公告", "紧急"];

// ==================== 列表相关 ====================

const searchForm = reactive({
	title: "",
	type: "",
	publisher: "",
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
		{ type: TableType.normal, prop: "image", label: "图片", width: "80px" },
		{ type: TableType.normal, prop: "title", label: "公告标题", minWidth: "200px" },
		{ type: TableType.normal, prop: "type", label: "类型", width: "80px" },
		{ type: TableType.normal, prop: "articleCode", label: "文章编码", width: "140px" },
		{ type: TableType.normal, prop: "status", label: "状态", width: "80px" },
		{ type: TableType.normal, prop: "publisher", label: "发布者", width: "100px" },
		{ type: TableType.normal, prop: "addTime", label: "发布时间", width: "170px" },
		{ type: TableType.handler as any, label: "操作", width: "80px", editText: "编辑" },
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
		editText: "编辑",
	},
});

const tableData = ref<NoticeVO[]>([]);
const loading = ref(false);
const selectedRows = ref<NoticeVO[]>([]);

async function loadData() {
	loading.value = true;
	try {
		const res = await listNotice(searchForm);
		if (res.code === 10000 && res.data) {
			tableData.value = res.data.rows || [];
			tableConfig.value.pagination!.total = res.data.total;
		}
	} catch (error) {
		console.error("获取公告列表失败:", error);
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
	searchForm.type = "";
	searchForm.publisher = "";
	handleSearch();
}

function handlePageChange(page: number, size: number) {
	searchForm.pageIndex = page;
	searchForm.pageSize = size;
	loadData();
}

function handleSelectionChange(selection: NoticeVO[]) {
	selectedRows.value = selection;
}

// ==================== 新增/编辑公告 ====================

const formDialogVisible = ref(false);
const formDialogTitle = ref("新增公告");
const formRef = ref<FormInstance>();
const formData = reactive<NoticeSaveDTO>({
	id: undefined,
	title: "",
	type: "",
	articleCode: "",
	image: "",
	content: "",
});

const formRules = {
	title: [{ required: true, message: "请输入公告标题", trigger: "change" }],
};

function handleAdd() {
	formDialogTitle.value = "新增公告";
	formData.id = undefined;
	formData.title = "";
	formData.type = "";
	formData.articleCode = "";
	formData.image = "";
	formData.content = "";
	formDialogVisible.value = true;
}

function handleEdit(row: NoticeVO) {
	formDialogTitle.value = "编辑公告";
	formData.id = row.id;
	formData.title = row.title;
	formData.type = row.type;
	formData.articleCode = row.articleCode || "";
	formData.image = row.image || "";
	formData.content = row.content || "";
	formDialogVisible.value = true;
}

/** 图片选择：读取为 base64 预览 */
function handleImageChange(uploadFile: UploadFile) {
	const file = uploadFile.raw;
	if (!file) return;
	const reader = new FileReader();
	reader.onload = (e) => {
		formData.image = e.target?.result as string;
	};
	reader.readAsDataURL(file);
}

async function handleSubmit() {
	const valid = await formRef.value?.validate().catch(() => false);
	if (!valid) return;
	try {
		const res = await saveNotice(formData);
		if (res.code === 10000) {
			ElMessage.success(formData.id ? "修改成功" : "新增成功");
			formDialogVisible.value = false;
			loadData();
		} else {
			ElMessage.error(res.message || "操作失败");
		}
	} catch (error) {
		console.error("保存公告失败:", error);
	}
}

// ==================== 删除公告 ====================

function handleBatchDelete() {
	if (selectedRows.value.length === 0) return;
	ElMessageBox.confirm(`确定要删除选中的 ${selectedRows.value.length} 条公告吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(async () => {
			try {
				for (const row of selectedRows.value) {
					await removeNotice(row.id);
				}
				ElMessage.success("删除成功");
				loadData();
			} catch (error) {
				console.error("删除公告失败:", error);
			}
		})
		.catch(() => {});
}

// ==================== 批量启用/停用 ====================

function handleBatchStatus(status: number) {
	if (selectedRows.value.length === 0) return;
	const statusText = status === 1 ? "启用" : "停用";
	ElMessageBox.confirm(`确定要${statusText}选中的 ${selectedRows.value.length} 条公告吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(async () => {
			try {
				for (const row of selectedRows.value) {
					await modifyNotice(row.id, status);
				}
				ElMessage.success(`${statusText}成功`);
				loadData();
			} catch (error) {
				console.error(`${statusText}公告失败:`, error);
			}
		})
		.catch(() => {});
}

// ==================== 发系统消息 ====================

function handleSendMessage() {
	if (selectedRows.value.length === 0) return;
	ElMessageBox.confirm(`确定要向选中的 ${selectedRows.value.length} 条公告发送系统消息吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "info",
	})
		.then(() => {
			// TODO: 对接发送系统消息接口
			ElMessage.success("系统消息已发送");
		})
		.catch(() => {});
}

// ==================== 初始化 ====================

onMounted(() => {
	loadData();
});
</script>

<style scoped lang="scss">
.announcement-management {
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

	.el-select {
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

.notice-image {
	width: 50px;
	height: 50px;
	border-radius: 4px;
}

.no-image {
	font-size: 12px;
	color: #c0c4cc;
}

/* 图片上传 */
.notice-uploader {
	:deep(.el-upload) {
		border: 1px dashed var(--el-border-color);
		border-radius: 6px;
		cursor: pointer;
		position: relative;
		overflow: hidden;
		transition: var(--el-transition-duration);
		&:hover {
			border-color: var(--el-color-primary);
		}
	}
}

.notice-uploader-icon {
	font-size: 28px;
	color: #8c939d;
	width: 120px;
	height: 120px;
	display: flex;
	align-items: center;
	justify-content: center;
}

.notice-uploader-preview {
	width: 120px;
	height: 120px;
	display: block;
}

.image-clear {
	margin-top: 4px;
}
</style>
