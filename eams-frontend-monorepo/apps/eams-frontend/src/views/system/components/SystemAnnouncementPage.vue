<template>
	<SystemSectionLayout>
		<section class="panel-card">
			<div class="toolbar">
				<div class="toolbar__filters">
					<span class="toolbar__label">{{ config.search.label }}</span>
					<el-input v-model="query.title" clearable class="toolbar__input" @keyup.enter="handleSearch" />
					<el-button type="primary" @click="handleSearch">查询</el-button>
				</div>

				<div class="toolbar__actions">
					<el-button type="primary" :icon="Plus" @click="openDialog()">{{ config.createButtonText }}</el-button>
					<el-button :icon="Delete" :disabled="selectedRows.length === 0" @click="handleBatchDelete">
						{{ config.deleteButtonText }}
					</el-button>
					<el-button circle :icon="RefreshRight" @click="loadData" />
					<el-button circle :icon="Printer" />
					<el-button circle :icon="Grid" />
				</div>
			</div>

			<el-table :data="tableData.rows" border style="width: 100%" @selection-change="handleSelectionChange">
				<el-table-column type="selection" width="55" />
				<el-table-column
					v-for="column in config.columns"
					:key="column.prop"
					:prop="column.prop"
					:label="column.label"
					:min-width="column.minWidth"
					:width="column.width"
				/>
				<el-table-column label="操作" width="160" align="center">
					<template #default="{ row }">
						<el-button link type="primary" @click="openDialog(row)">编辑</el-button>
						<el-button link type="danger" @click="handleDelete(row.id)">删除</el-button>
					</template>
				</el-table-column>
			</el-table>

			<div class="footer">
				<el-pagination
					v-model:current-page="tableData.pageIndex"
					v-model:page-size="tableData.pageSize"
					background
					layout="total, sizes, prev, pager, next, jumper"
					:page-sizes="config.pageSizes"
					:total="tableData.total"
					@current-change="loadData"
					@size-change="handleSizeChange"
				/>
			</div>
		</section>

		<el-dialog
			v-model="dialogVisible"
			:title="dialogForm.id ? config.editDialogTitle : config.createDialogTitle"
			width="640px"
		>
			<el-form label-width="80px">
				<el-form-item v-for="field in config.formFields" :key="field.prop" :label="field.label">
					<el-input
						v-if="field.type !== 'textarea'"
						v-model="dialogForm[field.prop]"
						:maxlength="field.maxlength"
						:show-word-limit="field.showWordLimit"
					/>
					<el-input
						v-else
						v-model="dialogForm[field.prop]"
						type="textarea"
						:rows="field.rows || 3"
						:maxlength="field.maxlength"
						:show-word-limit="field.showWordLimit"
					/>
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="dialogVisible = false">取消</el-button>
				<el-button type="primary" @click="submitDialog">保存</el-button>
			</template>
		</el-dialog>
	</SystemSectionLayout>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Delete, Grid, Plus, Printer, RefreshRight } from "@element-plus/icons-vue";
import { createPageDTO, type PageDTO } from "@/apis/type";
import type { InternalAnnouncement } from "@/apis/system/type";
import type { SystemAnnouncementPageConfig } from "../shared";
import SystemSectionLayout from "./SystemSectionLayout.vue";

const props = defineProps<{
	config: SystemAnnouncementPageConfig;
}>();

const query = reactive({
	title: "",
});

const tableData = ref<PageDTO<InternalAnnouncement>>(createPageDTO({ pageSize: 30 }));
const selectedRows = ref<InternalAnnouncement[]>([]);
const dialogVisible = ref(false);
const dialogForm = reactive<Record<string, any>>({
	id: undefined,
	title: "",
	publisher: props.config.defaultPublisher,
	content: "",
});

async function loadData() {
	tableData.value = await props.config.loadPage({
		pageIndex: tableData.value.pageIndex,
		pageSize: tableData.value.pageSize,
		title: query.title,
	});
}

function handleSearch() {
	tableData.value.pageIndex = 1;
	loadData();
}

function handleSizeChange() {
	tableData.value.pageIndex = 1;
	loadData();
}

function handleSelectionChange(rows: InternalAnnouncement[]) {
	selectedRows.value = rows;
}

function resetDialogForm() {
	dialogForm.id = undefined;
	dialogForm.title = "";
	dialogForm.publisher = props.config.defaultPublisher;
	dialogForm.content = "";
}

function openDialog(row?: InternalAnnouncement) {
	resetDialogForm();
	if (row) {
		dialogForm.id = row.id;
		dialogForm.title = row.title;
		dialogForm.publisher = row.publisher || props.config.defaultPublisher;
		dialogForm.content = row.content;
	}
	dialogVisible.value = true;
}

async function submitDialog() {
	if (!String(dialogForm.title || "").trim() || !String(dialogForm.content || "").trim()) {
		ElMessage.warning("请先填写完整的公告标题和内容");
		return;
	}

	await props.config.saveItem({
		id: dialogForm.id,
		title: String(dialogForm.title).trim(),
		content: String(dialogForm.content).trim(),
		publisher: String(dialogForm.publisher || props.config.defaultPublisher).trim() || props.config.defaultPublisher,
	});
	dialogVisible.value = false;
	ElMessage.success(dialogForm.id ? "公告已更新" : "公告已创建");
	await loadData();
}

async function handleDelete(id: number) {
	await ElMessageBox.confirm("确认删除这条公告吗？", "提示", {
		type: "warning",
		confirmButtonText: "删除",
		cancelButtonText: "取消",
	});
	await props.config.deleteItems([id]);
	ElMessage.success("公告已删除");
	await loadData();
}

async function handleBatchDelete() {
	await ElMessageBox.confirm(`确认删除选中的 ${selectedRows.value.length} 条公告吗？`, "提示", {
		type: "warning",
		confirmButtonText: "删除",
		cancelButtonText: "取消",
	});
	await props.config.deleteItems(selectedRows.value.map((item) => item.id));
	selectedRows.value = [];
	ElMessage.success("选中公告已删除");
	await loadData();
}

onMounted(() => {
	loadData();
});
</script>

<style scoped>
.panel-card {
	padding: 18px;
	background: #ffffff;
	border: 1px solid #edf0f5;
	box-shadow: 0 1px 2px rgb(31 45 61 / 4%);
}

.toolbar {
	margin-bottom: 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 16px;
}

.toolbar__filters,
.toolbar__actions {
	display: flex;
	align-items: center;
	gap: 12px;
}

.toolbar__label {
	color: #4b566a;
	font-size: 15px;
}

.toolbar__input {
	width: 200px;
}

.footer {
	margin-top: 18px;
	display: flex;
	justify-content: flex-start;
}
</style>
