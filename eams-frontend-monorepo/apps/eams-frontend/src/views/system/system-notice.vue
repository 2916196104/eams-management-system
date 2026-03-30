<template>
	<div class="system-notice">
		<!-- 搜索区域 -->
		<MySearch :model="searchForm" :items="searchItems" formtitle="公告查询" @do-search="handleSearch">
			<!-- 头部操作按钮 -->
			<template #header>
				<el-button type="primary" :icon="Plus" @click="handleAdd">新增</el-button>
				<el-button type="danger" :icon="Delete" :disabled="selectedRows.length === 0" @click="handleBatchDelete">
					删除
				</el-button>
			</template>
			<!-- 底部工具栏：刷新 / 打印 / 自定义列 -->
			<template #footer>
				<div class="toolbar-right">
					<el-tooltip content="刷新" placement="top">
						<el-button link :icon="Refresh" @click="reload">刷新</el-button>
					</el-tooltip>
					<el-tooltip content="打印" placement="top">
						<el-button link :icon="Printer" @click="handlePrint">打印</el-button>
					</el-tooltip>
					<el-dropdown trigger="click">
						<el-button link>
							<el-icon><Grid /></el-icon>
							自定义列
						</el-button>
						<template #dropdown>
							<el-dropdown-menu>
								<el-dropdown-item v-for="col in allColumns" :key="col.key">
									<el-checkbox
										:model-value="visibleColumns.includes(col.key)"
										@click.stop
										@change="toggleColumn(col.key)"
									>
										{{ col.label }}
									</el-checkbox>
								</el-dropdown-item>
							</el-dropdown-menu>
						</template>
					</el-dropdown>
				</div>
			</template>
		</MySearch>

		<!-- 表格区域 -->
		<F1Table
			:config="tableConfig"
			:data="noticeStore.tableData"
			:loading="noticeStore.loading"
			@page-change="handlePageChange"
			@edit="handleEdit"
			@view="handleView"
			@delete="handleDelete"
			@selection-change="handleSelectionChange"
		>
			<template #title="{ row }">
				<el-text type="primary">{{ row.title }}</el-text>
			</template>
		</F1Table>

		<!-- 新增/编辑对话框 -->
		<el-dialog v-model="dialogVisible" :title="dialogTitle" width="600px" destroy-on-close>
			<el-form ref="formRef" :model="formData" :rules="formRules" label-width="80px">
				<el-form-item label="标题" prop="title">
					<el-input v-model="formData.title" placeholder="请输入标题" />
				</el-form-item>
				<el-form-item label="内容" prop="content">
					<el-input v-model="formData.content" type="textarea" :rows="6" placeholder="请输入内容" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="dialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="submitLoading" @click="handleSubmit">确定</el-button>
			</template>
		</el-dialog>

		<!-- 详情对话框 -->
		<el-dialog v-model="detailDialogVisible" title="公告详情" width="600px" destroy-on-close>
			<div class="notice-detail" v-if="currentDetail">
				<div class="detail-item">
					<span class="detail-label">标题：</span>
					<span>{{ currentDetail.title }}</span>
				</div>
				<div class="detail-item">
					<span class="detail-label">内容：</span>
					<div class="detail-content">{{ currentDetail.content }}</div>
				</div>
				<div class="detail-item" v-if="currentDetail.createTime">
					<span class="detail-label">添加时间：</span>
					<span>{{ currentDetail.createTime }}</span>
				</div>
				<div class="detail-item" v-if="currentDetail.updateTime">
					<span class="detail-label">修改时间：</span>
					<span>{{ currentDetail.updateTime }}</span>
				</div>
			</div>
			<template #footer>
				<el-button @click="detailDialogVisible = false">关闭</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, computed, onMounted } from "vue";
import { ElMessage, ElMessageBox, type FormInstance } from "element-plus";
import { Plus, Delete, Refresh, Printer, Grid } from "@element-plus/icons-vue";
import F1Table from "@/components/f1table/F1Table.vue";
import { TableType } from "@/components/f1table/type";
import type { TableConfig } from "@/components/f1table/type";
import MySearch from "@/components/mysearch/MySearch.vue";
import type { MyFormItemAttr } from "@/components/myform/type";
import { useSystemNoticeStore, type NoticeItem } from "@/stores/systemNotice";

const noticeStore = useSystemNoticeStore();

// ==================== 搜索表单 ====================

const searchForm = reactive({
	title: "",
	pageSize: 10,
	pageNum: 1,
});

const searchItems: MyFormItemAttr[] = [
	{
		prop: "title",
		label: "标题",
		type: "input",
		fprops: {
			placeholder: "请输入标题",
			clearable: true,
		},
	},
];

// ==================== 自定义列 ====================

const STORAGE_KEY = "system-notice-columns";

const allColumns = [
	{ key: "title", label: "标题" },
	{ key: "createTime", label: "添加时间" },
	{ key: "updateTime", label: "修改时间" },
	{ key: "action", label: "操作" },
];

const visibleColumns = ref<string[]>(allColumns.map((col) => col.key));

function loadColumnConfig() {
	const saved = localStorage.getItem(STORAGE_KEY);
	if (saved) {
		try {
			visibleColumns.value = JSON.parse(saved);
		} catch {
			/* ignore */
		}
	}
}

function saveColumnConfig() {
	localStorage.setItem(STORAGE_KEY, JSON.stringify(visibleColumns.value));
}

function toggleColumn(key: string) {
	const idx = visibleColumns.value.indexOf(key);
	if (idx === -1) {
		visibleColumns.value.push(key);
	} else {
		visibleColumns.value.splice(idx, 1);
	}
	saveColumnConfig();
}

// ==================== 表格配置 ====================

const tableConfig = computed<TableConfig>(() => {
	const columns: TableConfig["tableList"] = [{ type: TableType.selection, width: "55px", label: "选择" }];

	if (visibleColumns.value.includes("title")) {
		columns.push({ type: TableType.custom, prop: "title", label: "标题", minWidth: "200px", slotName: "title" });
	}
	if (visibleColumns.value.includes("createTime")) {
		columns.push({ type: TableType.normal, prop: "createTime", label: "添加时间", width: "180px" });
	}
	if (visibleColumns.value.includes("updateTime")) {
		columns.push({ type: TableType.normal, prop: "updateTime", label: "修改时间", width: "180px" });
	}
	if (visibleColumns.value.includes("action")) {
		columns.push({ type: TableType.handler as any, label: "操作", width: "200px" });
	}

	return {
		tableProperties: {
			stripe: true,
			border: true,
		},
		tableList: columns,
		pagination: {
			enabled: true,
			currentPage: searchForm.pageNum,
			pageSize: searchForm.pageSize,
			total: noticeStore.total,
		},
		handler: {
			edit: true,
			view: true,
			delete: true,
			editText: "编辑",
			viewText: "详情",
			deleteText: "删除",
		},
	};
});

const selectedRows = ref<NoticeItem[]>([]);

// ==================== 弹窗状态 ====================

const dialogVisible = ref(false);
const dialogTitle = ref("新增公告");
const submitLoading = ref(false);
const formRef = ref<FormInstance>();
const formData = reactive({
	id: 0,
	title: "",
	content: "",
});

const detailDialogVisible = ref(false);
const currentDetail = ref<NoticeItem | null>(null);

const formRules = {
	title: [{ required: true, message: "请输入标题", trigger: "blur" }],
	content: [{ required: true, message: "请输入内容", trigger: "blur" }],
};

// ==================== 生命周期 ====================

onMounted(() => {
	loadColumnConfig();
	reload();
});

// ==================== 数据操作 ====================

async function reload() {
	noticeStore.setSearchParams({
		title: searchForm.title,
		pageSize: searchForm.pageSize,
		pageNum: searchForm.pageNum,
	});
	await noticeStore.fetchList();
}

function handleSearch() {
	searchForm.pageNum = 1;
	reload();
}

function handlePageChange(page: number, size: number) {
	searchForm.pageNum = page;
	searchForm.pageSize = size;
	reload();
}

function handleSelectionChange(selection: NoticeItem[]) {
	selectedRows.value = selection;
}

// ==================== 增删改查 ====================

function handleAdd() {
	dialogTitle.value = "新增公告";
	formData.id = 0;
	formData.title = "";
	formData.content = "";
	dialogVisible.value = true;
}

function handleEdit(row: NoticeItem) {
	dialogTitle.value = "编辑公告";
	formData.id = row.id;
	formData.title = row.title;
	formData.content = row.content;
	dialogVisible.value = true;
}

function handleView(row: NoticeItem) {
	currentDetail.value = row;
	detailDialogVisible.value = true;
}

async function handleDelete(row: NoticeItem) {
	try {
		await ElMessageBox.confirm("确定要删除该公告吗？", "提示", {
			confirmButtonText: "确定",
			cancelButtonText: "取消",
			type: "warning",
		});
		const success = await noticeStore.deleteNotice([row.id]);
		if (success) {
			ElMessage.success("删除成功");
		}
	} catch {
		/* 用户取消 */
	}
}

function handleBatchDelete() {
	if (selectedRows.value.length === 0) return;
	ElMessageBox.confirm(`确定要删除选中的 ${selectedRows.value.length} 条公告吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(async () => {
			const ids = selectedRows.value.map((item) => item.id);
			const success = await noticeStore.deleteNotice(ids);
			if (success) {
				ElMessage.success("删除成功");
				selectedRows.value = [];
			}
		})
		.catch(() => {});
}

function handlePrint() {
	window.print();
}

async function handleSubmit() {
	await formRef.value?.validate();
	submitLoading.value = true;
	const success = await noticeStore.saveNotice({
		id: formData.id,
		title: formData.title,
		content: formData.content,
	});
	submitLoading.value = false;
	if (success) {
		ElMessage.success(formData.id === 0 ? "新增成功" : "修改成功");
		dialogVisible.value = false;
	}
}
</script>

<style scoped lang="scss">
.system-notice {
	padding: 16px;
}

.toolbar-right {
	display: flex;
	gap: 8px;
	align-items: center;
}

.notice-detail {
	padding: 16px;
	line-height: 1.8;

	.detail-item {
		display: flex;
		margin-bottom: 12px;
	}

	.detail-label {
		flex-shrink: 0;
		width: 80px;
		color: #909399;
	}

	.detail-content {
		white-space: pre-wrap;
		line-height: 1.6;
	}
}

@media print {
	.system-notice {
		padding: 0;
	}
}
</style>
