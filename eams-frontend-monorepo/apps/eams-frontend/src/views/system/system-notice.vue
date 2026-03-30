<template>
	<div class="system-notice">
		<div class="notice-panel">
			<div class="notice-search-row">
				<span class="search-label">搜索项:</span>
				<el-input v-model="searchForm.title" class="search-input" clearable @keyup.enter="handleSearch" />
				<div class="search-tools">
					<el-button circle :icon="Search" @click="handleSearch" />
					<el-button circle :icon="CircleClose" @click="handleResetSearch" />
				</div>
			</div>

			<div class="notice-toolbar-row">
				<div class="toolbar-actions">
					<el-button type="primary" class="primary-action" :icon="Plus" @click="handleAdd">新增</el-button>
					<el-button :icon="Delete" :disabled="selectedRows.length === 0" @click="handleBatchDelete">删除</el-button>
					<el-button :icon="Message" :disabled="selectedRows.length === 0" @click="handleSendNotice">
						发内部消息
					</el-button>
				</div>
				<div class="toolbar-icons">
					<button type="button" class="icon-button" @click="reload">
						<el-icon><RefreshRight /></el-icon>
					</button>
					<button type="button" class="icon-button" @click="handlePrint">
						<el-icon><Printer /></el-icon>
					</button>
					<el-popover placement="bottom-end" :width="180" trigger="click">
						<template #reference>
							<button type="button" class="icon-button">
								<el-icon><Grid /></el-icon>
							</button>
						</template>
						<div class="column-picker">
							<el-checkbox
								v-for="column in allColumns"
								:key="column.key"
								:model-value="visibleColumns.includes(column.key)"
								@change="toggleColumn(column.key)"
							>
								{{ column.label }}
							</el-checkbox>
						</div>
					</el-popover>
				</div>
			</div>

			<div class="notice-table-wrap" v-loading="noticeStore.loading">
				<el-table :data="noticeStore.tableData" @selection-change="handleSelectionChange">
					<el-table-column type="selection" width="52" />
					<el-table-column v-if="visibleColumns.includes('title')" label="标题" min-width="320">
						<template #default="{ row }">
							<button type="button" class="title-button" @click="handleView(row)">{{ row.title }}</button>
						</template>
					</el-table-column>
					<el-table-column
						v-if="visibleColumns.includes('createTime')"
						prop="createTime"
						label="添加时间"
						width="220"
					/>
					<el-table-column
						v-if="visibleColumns.includes('updateTime')"
						prop="updateTime"
						label="修改时间"
						width="220"
					/>
					<el-table-column v-if="visibleColumns.includes('action')" label="操作" width="120" fixed="right">
						<template #default="{ row }">
							<button type="button" class="link-button" @click="handleEdit(row)">编辑</button>
						</template>
					</el-table-column>
				</el-table>
			</div>

			<div class="notice-pagination-row">
				<div class="pagination-left">共 {{ noticeStore.total }} 条</div>
				<el-pagination
					v-model:current-page="searchForm.pageNum"
					v-model:page-size="searchForm.pageSize"
					background
					layout="sizes, prev, pager, next, jumper"
					:page-sizes="[20, 50, 100]"
					:total="noticeStore.total"
					@size-change="handlePageSizeChange"
					@current-change="handlePageChange"
				/>
			</div>
		</div>

		<el-dialog v-model="dialogVisible" :title="dialogTitle" width="640px" destroy-on-close>
			<el-form ref="formRef" :model="formData" :rules="formRules" label-width="80px">
				<el-form-item label="标题" prop="title">
					<el-input v-model="formData.title" placeholder="请输入标题" />
				</el-form-item>
				<el-form-item label="内容" prop="content">
					<el-input v-model="formData.content" type="textarea" :rows="8" placeholder="请输入内容" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="dialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="submitLoading" @click="handleSubmit">确定</el-button>
			</template>
		</el-dialog>

		<el-dialog v-model="detailDialogVisible" title="公告详情" width="640px" destroy-on-close>
			<div v-if="currentDetail" class="notice-detail">
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
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref } from "vue";
import { CircleClose, Delete, Grid, Message, Plus, Printer, RefreshRight, Search } from "@element-plus/icons-vue";
import { ElMessage, ElMessageBox, type FormInstance } from "element-plus";
import { useSystemNoticeStore, type NoticeItem } from "@/stores/systemNotice";

const noticeStore = useSystemNoticeStore();

const STORAGE_KEY = "system-notice-columns";
const allColumns = [
	{ key: "title", label: "标题" },
	{ key: "createTime", label: "添加时间" },
	{ key: "updateTime", label: "修改时间" },
	{ key: "action", label: "操作" },
];
const visibleColumns = ref<string[]>(allColumns.map((item) => item.key));

const searchForm = reactive({
	title: "",
	pageSize: 20,
	pageNum: 1,
});

const selectedRows = ref<NoticeItem[]>([]);
const dialogVisible = ref(false);
const detailDialogVisible = ref(false);
const dialogTitle = ref("新增公告");
const submitLoading = ref(false);
const formRef = ref<FormInstance>();
const currentDetail = ref<NoticeItem | null>(null);
const formData = reactive({
	id: 0,
	title: "",
	content: "",
});

const formRules = {
	title: [{ required: true, message: "请输入标题", trigger: "blur" }],
	content: [{ required: true, message: "请输入内容", trigger: "blur" }],
};

function loadColumnConfig() {
	const saved = localStorage.getItem(STORAGE_KEY);
	if (!saved) return;

	try {
		visibleColumns.value = JSON.parse(saved);
	} catch {
		visibleColumns.value = allColumns.map((item) => item.key);
	}
}

function saveColumnConfig() {
	localStorage.setItem(STORAGE_KEY, JSON.stringify(visibleColumns.value));
}

function toggleColumn(key: string) {
	if (visibleColumns.value.includes(key)) {
		visibleColumns.value = visibleColumns.value.filter((item) => item !== key);
	} else {
		visibleColumns.value = [...visibleColumns.value, key];
	}

	saveColumnConfig();
}

async function reload() {
	noticeStore.setSearchParams({
		title: searchForm.title,
		pageSize: searchForm.pageSize,
		pageNum: searchForm.pageNum,
	});
	const success = await noticeStore.fetchList();
	if (!success) {
		ElMessage.error("内部公告加载失败，请检查接口配置");
	}
}

function handleSearch() {
	searchForm.pageNum = 1;
	void reload();
}

function handleResetSearch() {
	searchForm.title = "";
	searchForm.pageNum = 1;
	void reload();
}

function handlePageChange(page: number) {
	searchForm.pageNum = page;
	void reload();
}

function handlePageSizeChange(size: number) {
	searchForm.pageSize = size;
	searchForm.pageNum = 1;
	void reload();
}

function handleSelectionChange(rows: NoticeItem[]) {
	selectedRows.value = rows;
}

function handleAdd() {
	dialogTitle.value = "新增公告";
	formData.id = 0;
	formData.title = "";
	formData.content = "";
	dialogVisible.value = true;
}

async function handleEdit(row: NoticeItem) {
	const detail = await noticeStore.fetchDetail(row.id);
	const source = detail ?? row;
	dialogTitle.value = "编辑公告";
	formData.id = source.id;
	formData.title = source.title;
	formData.content = source.content;
	dialogVisible.value = true;
}

async function handleView(row: NoticeItem) {
	currentDetail.value = await noticeStore.fetchDetail(row.id);
	if (!currentDetail.value) {
		ElMessage.error("公告详情加载失败，请检查接口配置");
		return;
	}
	detailDialogVisible.value = true;
}

async function handleBatchDelete() {
	if (selectedRows.value.length === 0) return;

	await ElMessageBox.confirm(`确定要删除选中的 ${selectedRows.value.length} 条公告吗？`, "提示", { type: "warning" });
	const success = await noticeStore.deleteNotice(selectedRows.value.map((item) => item.id));
	if (!success) {
		ElMessage.error("公告删除失败，请检查接口配置");
		return;
	}

	selectedRows.value = [];
	ElMessage.success("删除成功");
}

function handleSendNotice() {
	ElMessage.success(`已选择 ${selectedRows.value.length} 条公告，后续可接入内部消息接口`);
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

	if (!success) {
		ElMessage.error("公告保存失败，请检查接口配置");
		return;
	}

	dialogVisible.value = false;
	ElMessage.success(formData.id === 0 ? "新增成功" : "修改成功");
}

onMounted(() => {
	loadColumnConfig();
	void reload();
});
</script>

<style scoped lang="scss">
.system-notice {
	height: 100%;
	padding: 8px 12px 12px;
	box-sizing: border-box;
	background: #f3f5f8;
}

.notice-panel {
	display: flex;
	flex-direction: column;
	gap: 16px;
	height: 100%;
	padding: 18px 12px 10px;
	background: #fff;
	border: 1px solid #dfe6ee;
}

.notice-search-row {
	display: flex;
	align-items: center;
	gap: 12px;
}

.search-label {
	font-size: 15px;
	color: #4b5563;
}

.search-input {
	width: 164px;
}

.search-tools {
	margin-left: auto;
	display: flex;
	gap: 10px;
}

.notice-toolbar-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 16px;
}

.toolbar-actions,
.toolbar-icons {
	display: flex;
	align-items: center;
	gap: 12px;
}

.primary-action {
	padding: 10px 20px;
}

.icon-button {
	display: inline-flex;
	align-items: center;
	justify-content: center;
	width: 32px;
	height: 32px;
	border: 0;
	background: transparent;
	color: #409eff;
	cursor: pointer;
	font-size: 18px;
}

.column-picker {
	display: flex;
	flex-direction: column;
	gap: 8px;
}

.notice-table-wrap {
	flex: 1;
	min-height: 0;
}

.link-button {
	padding: 0;
	border: 0;
	background: transparent;
	color: #409eff;
	cursor: pointer;
	font-size: 14px;
}

.title-button {
	padding: 0;
	border: 0;
	background: transparent;
	color: #111827;
	cursor: pointer;
	font-size: 15px;
	text-align: left;
}

.notice-pagination-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 16px;
}

.pagination-left {
	font-size: 15px;
	color: #475467;
}

.notice-detail {
	padding: 10px 4px;
	line-height: 1.8;
}

.detail-item {
	display: flex;
	margin-bottom: 12px;
}

.detail-label {
	width: 80px;
	flex-shrink: 0;
	color: #909399;
}

.detail-content {
	white-space: pre-wrap;
	line-height: 1.6;
}

@media (max-width: 900px) {
	.notice-search-row,
	.notice-toolbar-row,
	.notice-pagination-row {
		flex-direction: column;
		align-items: stretch;
	}

	.search-tools,
	.toolbar-icons {
		margin-left: 0;
		justify-content: flex-end;
	}
}
</style>
