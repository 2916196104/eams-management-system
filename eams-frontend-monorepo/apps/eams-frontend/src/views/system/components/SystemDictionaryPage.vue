<template>
	<section class="dict-page">
		<section class="panel-card dict-nav">
			<div class="dict-nav__toolbar">
				<div>
					<div class="dict-nav__title">字典类型</div>
					<div class="dict-nav__subtitle">维护左侧字典分类</div>
				</div>
				<el-button type="primary" plain size="small" :icon="Plus" @click="openCategoryDialog()">新增类型</el-button>
			</div>

			<div class="dict-nav__actions">
				<el-button size="small" :disabled="!activeCategory" @click="openCategoryDialog(activeCategory || undefined)">
					编辑
				</el-button>
				<el-button size="small" :disabled="!activeCategory" @click="handleCategoryDelete">删除</el-button>
			</div>

			<div v-if="categories.length === 0" class="dict-nav__empty">暂无字典类型，请先新增。</div>
			<template v-else>
				<div
					v-for="category in categories"
					:key="category.id"
					:class="['dict-nav__item', { 'dict-nav__item--active': category.id === activeCategoryId }]"
					@click="selectCategory(category.id)"
				>
					<div class="dict-nav__content">
						<div class="dict-nav__label">{{ category.label }}</div>
						<div v-if="category.code" class="dict-nav__code">{{ category.code }}</div>
					</div>
					<div class="dict-nav__count">{{ category.itemCount }} {{ config.categoryCountSuffix }}</div>
				</div>
			</template>
		</section>

		<section class="panel-card dict-table">
			<div class="dict-table__toolbar">
				<div class="dict-table__actions">
					<el-button type="primary" :icon="Plus" :disabled="!activeCategoryId" @click="openItemDialog()">
						{{ config.createButtonText }}
					</el-button>
					<el-button :icon="Delete" :disabled="selectedRows.length === 0" @click="handleItemBatchDelete">
						{{ config.deleteButtonText }}
					</el-button>
				</div>
				<div class="dict-table__actions">
					<el-button circle :icon="RefreshRight" @click="loadCategories" />
					<el-button circle :icon="Printer" />
					<el-button circle :icon="Grid" />
				</div>
			</div>

			<el-table :data="items" border @selection-change="handleSelectionChange">
				<el-table-column type="selection" width="55" />
				<el-table-column
					v-for="column in config.columns"
					:key="column.prop"
					:prop="column.prop"
					:label="column.label"
					:min-width="column.minWidth"
					:width="column.width"
				/>
				<el-table-column label="操作" width="120" align="center">
					<template #default="{ row }">
						<el-button link type="primary" @click="openItemDialog(row)">编辑</el-button>
					</template>
				</el-table-column>
			</el-table>

			<div class="dict-table__pagination">
				<el-pagination
					:current-page="pageState.pageIndex"
					:page-size="pageState.pageSize"
					:page-sizes="[10, 20, 30, 50]"
					:total="pageState.total"
					layout="total, sizes, prev, pager, next, jumper"
					@size-change="handlePageSizeChange"
					@current-change="handlePageCurrentChange"
				/>
			</div>
		</section>
	</section>

	<el-dialog
		v-model="categoryDialogVisible"
		:title="categoryDialogForm.id ? '编辑字典类型' : '新增字典类型'"
		width="540px"
	>
		<el-form label-width="96px">
			<el-form-item label="类型名称">
				<el-input v-model="categoryDialogForm.label" maxlength="50" />
			</el-form-item>
			<el-form-item label="字典编码">
				<el-input v-model="categoryDialogForm.code" maxlength="50" />
			</el-form-item>
			<el-form-item label="排序号">
				<el-input v-model="categoryDialogForm.sortNum" />
			</el-form-item>
			<el-form-item label="备注">
				<el-input v-model="categoryDialogForm.remark" type="textarea" :rows="3" maxlength="200" show-word-limit />
			</el-form-item>
		</el-form>
		<template #footer>
			<el-button @click="categoryDialogVisible = false">取消</el-button>
			<el-button type="primary" @click="submitCategoryDialog">保存</el-button>
		</template>
	</el-dialog>

	<el-dialog
		v-model="itemDialogVisible"
		:title="itemDialogForm.id ? config.editDialogTitle : config.createDialogTitle"
		width="540px"
	>
		<el-form label-width="80px">
			<el-form-item v-for="field in config.formFields" :key="field.prop" :label="field.label">
				<el-input v-if="field.type !== 'textarea'" v-model="itemDialogForm[field.prop]" />
				<el-input v-else v-model="itemDialogForm[field.prop]" type="textarea" :rows="field.rows || 3" />
			</el-form-item>
		</el-form>
		<template #footer>
			<el-button @click="itemDialogVisible = false">取消</el-button>
			<el-button type="primary" @click="submitItemDialog">保存</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Delete, Grid, Plus, Printer, RefreshRight } from "@element-plus/icons-vue";
import type { PageDTO } from "@/apis/type";
import type { DictionaryCategory, DictionaryItem } from "@/apis/system/type";
import type { SystemDictionaryPageConfig } from "../shared";

const props = defineProps<{
	config: SystemDictionaryPageConfig;
}>();

const categories = ref<DictionaryCategory[]>([]);
const activeCategoryId = ref("");
const activeCategory = computed(() => categories.value.find((item) => item.id === activeCategoryId.value));
const items = ref<DictionaryItem[]>([]);
const selectedRows = ref<DictionaryItem[]>([]);
const pageState = reactive<PageDTO<DictionaryItem>>({
	pageIndex: 1,
	pageSize: 30,
	total: 0,
	pages: 1,
	rows: [],
});

const categoryDialogVisible = ref(false);
const categoryDialogForm = reactive<Record<string, any>>({
	id: undefined,
	label: "",
	code: "",
	remark: "",
	sortNum: "",
});

const itemDialogVisible = ref(false);
const itemDialogForm = reactive<Record<string, any>>({
	id: undefined,
	name: "",
	info: "",
	sortNum: "",
});

async function loadCategories() {
	const previousCategoryId = activeCategoryId.value;
	categories.value = await props.config.loadCategories();
	const nextCategoryId =
		previousCategoryId && categories.value.some((item) => item.id === previousCategoryId)
			? previousCategoryId
			: categories.value[0]?.id || "";
	if (nextCategoryId !== previousCategoryId) {
		pageState.pageIndex = 1;
	}
	activeCategoryId.value = nextCategoryId;
	await loadItems();
}

async function loadItems(options?: { resetPage?: boolean }) {
	selectedRows.value = [];
	if (options?.resetPage) {
		pageState.pageIndex = 1;
	}
	if (!activeCategoryId.value) {
		items.value = [];
		pageState.total = 0;
		pageState.pages = 1;
		return;
	}

	const page = await props.config.loadItemsPage(activeCategoryId.value, {
		pageIndex: pageState.pageIndex,
		pageSize: pageState.pageSize,
	});
	const totalPages = Math.max(
		1,
		Number(page.pages ?? Math.ceil(Number(page.total || 0) / Number(page.pageSize || pageState.pageSize))),
	);

	if ((page.rows?.length || 0) === 0 && Number(page.total || 0) > 0 && pageState.pageIndex > totalPages) {
		pageState.pageIndex = totalPages;
		await loadItems();
		return;
	}

	pageState.pageIndex = Number(page.pageIndex || pageState.pageIndex);
	pageState.pageSize = Number(page.pageSize || pageState.pageSize);
	pageState.total = Number(page.total || 0);
	pageState.pages = totalPages;
	items.value = page.rows || [];
}

async function selectCategory(id: string) {
	if (id === activeCategoryId.value) return;
	activeCategoryId.value = id;
	await loadItems({ resetPage: true });
}

function handleSelectionChange(rows: DictionaryItem[]) {
	selectedRows.value = rows;
}

async function handlePageSizeChange(size: number) {
	pageState.pageSize = size;
	pageState.pageIndex = 1;
	await loadItems();
}

async function handlePageCurrentChange(pageIndex: number) {
	pageState.pageIndex = pageIndex;
	await loadItems();
}

function openCategoryDialog(row?: DictionaryCategory) {
	categoryDialogForm.id = row?.id;
	categoryDialogForm.label = row?.label || "";
	categoryDialogForm.code = row?.code || "";
	categoryDialogForm.remark = row?.remark || "";
	categoryDialogForm.sortNum = row?.sortNum ?? "";
	categoryDialogVisible.value = true;
}

function openItemDialog(row?: DictionaryItem) {
	itemDialogForm.id = row?.id;
	itemDialogForm.name = row?.name || "";
	itemDialogForm.info = row?.info || row?.remark || "";
	itemDialogForm.sortNum = row?.sortNum ?? "";
	itemDialogVisible.value = true;
}

async function submitCategoryDialog() {
	const label = String(categoryDialogForm.label || "").trim();
	if (!label) {
		ElMessage.warning("请填写字典类型名称");
		return;
	}

	const sortNumText = String(categoryDialogForm.sortNum ?? "").trim();
	if (sortNumText && Number.isNaN(Number(sortNumText))) {
		ElMessage.warning("排序号必须是数字");
		return;
	}

	const isEdit = Boolean(categoryDialogForm.id);
	const code = String(categoryDialogForm.code || "").trim();
	await props.config.saveCategory({
		id: categoryDialogForm.id,
		label,
		code: code || undefined,
		remark: String(categoryDialogForm.remark || "").trim(),
		sortNum: sortNumText ? Number(sortNumText) : undefined,
	});
	categoryDialogVisible.value = false;
	await loadCategories();

	if (!isEdit) {
		const createdCategory = categories.value.find(
			(item) => (code && item.code === code) || (!code && item.label === label),
		);
		if (createdCategory && createdCategory.id !== activeCategoryId.value) {
			activeCategoryId.value = createdCategory.id;
			pageState.pageIndex = 1;
			await loadItems();
		}
	}

	ElMessage.success(isEdit ? "字典类型已更新" : "字典类型已新增");
}

async function submitItemDialog() {
	if (!String(itemDialogForm.name || "").trim() || !activeCategoryId.value) {
		ElMessage.warning("请填写完整的字典项名称");
		return;
	}

	const sortNumText = String(itemDialogForm.sortNum ?? "").trim();
	if (sortNumText && Number.isNaN(Number(sortNumText))) {
		ElMessage.warning("排序号必须是数字");
		return;
	}

	const isEdit = Boolean(itemDialogForm.id);
	await props.config.saveItem({
		id: itemDialogForm.id,
		categoryId: activeCategoryId.value,
		name: String(itemDialogForm.name).trim(),
		info: String(itemDialogForm.info || "").trim(),
		sortNum: sortNumText ? Number(sortNumText) : undefined,
	});
	itemDialogVisible.value = false;
	if (!isEdit) {
		pageState.pageIndex = 1;
	}
	await loadCategories();
	ElMessage.success(isEdit ? "字典项已更新" : "字典项已新增");
}

async function handleCategoryDelete() {
	if (!activeCategory.value) return;

	await ElMessageBox.confirm(`确认删除字典类型“${activeCategory.value.label}”吗？`, "提示", {
		type: "warning",
		confirmButtonText: "删除",
		cancelButtonText: "取消",
	});
	await props.config.deleteCategories([activeCategory.value.id]);
	await loadCategories();
	ElMessage.success("字典类型已删除");
}

async function handleItemBatchDelete() {
	const removedCount = selectedRows.value.length;
	await ElMessageBox.confirm(`确认删除选中的 ${removedCount} 条数据吗？`, "提示", {
		type: "warning",
		confirmButtonText: "删除",
		cancelButtonText: "取消",
	});
	await props.config.deleteItems(selectedRows.value.map((item) => item.id));
	selectedRows.value = [];
	if (removedCount > 0 && items.value.length === removedCount && pageState.pageIndex > 1) {
		pageState.pageIndex -= 1;
	}
	await loadCategories();
	ElMessage.success("字典项已删除");
}

onMounted(() => {
	loadCategories();
});
</script>

<style scoped>
.dict-page {
	display: grid;
	grid-template-columns: 360px minmax(0, 1fr);
	gap: 16px;
	padding: 16px;
}

.panel-card {
	background: #ffffff;
	border: 1px solid #edf0f5;
	box-shadow: 0 1px 2px rgb(31 45 61 / 4%);
}

.dict-nav {
	padding: 16px 0 12px;
}

.dict-nav__toolbar {
	padding: 0 18px 12px;
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
	border-bottom: 1px solid #edf0f5;
}

.dict-nav__title {
	font-size: 16px;
	font-weight: 600;
	color: #2f3b53;
}

.dict-nav__subtitle {
	margin-top: 4px;
	font-size: 12px;
	color: #9aa5b5;
}

.dict-nav__actions {
	padding: 12px 18px 6px;
	display: flex;
	gap: 8px;
}

.dict-nav__empty {
	padding: 32px 22px;
	font-size: 14px;
	line-height: 1.6;
	color: #9aa5b5;
	text-align: center;
}

.dict-nav__item {
	padding: 14px 22px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
	font-size: 17px;
	color: #2f3b53;
	cursor: pointer;
	transition:
		background-color 0.2s ease,
		color 0.2s ease;
}

.dict-nav__item + .dict-nav__item {
	border-top: 1px solid #f4f6fa;
}

.dict-nav__item--active {
	background: #edf4ff;
	color: #4a89f3;
}

.dict-nav__content {
	min-width: 0;
}

.dict-nav__label {
	font-size: 16px;
	font-weight: 500;
}

.dict-nav__code {
	margin-top: 4px;
	font-size: 12px;
	color: #9aa5b5;
	word-break: break-all;
}

.dict-nav__count {
	flex-shrink: 0;
	font-size: 12px;
	color: #9aa5b5;
}

.dict-table {
	padding: 18px;
}

.dict-table__toolbar {
	margin-bottom: 14px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
	flex-wrap: wrap;
}

.dict-table__actions {
	display: flex;
	gap: 12px;
	flex-wrap: wrap;
}

.dict-table__pagination {
	margin-top: 16px;
	display: flex;
	justify-content: flex-end;
}

@media (max-width: 1280px) {
	.dict-page {
		grid-template-columns: 1fr;
	}
}

@media (max-width: 768px) {
	.dict-nav__toolbar,
	.dict-table__toolbar {
		flex-direction: column;
		align-items: stretch;
	}

	.dict-nav__actions,
	.dict-table__actions {
		flex-wrap: wrap;
	}

	.dict-table__pagination {
		justify-content: flex-start;
	}
}
</style>
