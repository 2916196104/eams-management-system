<template>
	<section class="dict-page">
		<section class="panel-card dict-nav">
			<div
				v-for="category in categories"
				:key="category.id"
				:class="['dict-nav__item', { 'dict-nav__item--active': category.id === activeCategoryId }]"
				@click="selectCategory(category.id)"
			>
				<div>{{ category.label }}</div>
				<div class="dict-nav__count">{{ category.itemCount }} {{ config.categoryCountSuffix }}</div>
			</div>
		</section>

		<section class="panel-card dict-table">
			<div class="dict-table__toolbar">
				<div class="dict-table__actions">
					<el-button type="primary" :icon="Plus" @click="openDialog()">{{ config.createButtonText }}</el-button>
					<el-button :icon="Delete" :disabled="selectedRows.length === 0" @click="handleBatchDelete">
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
						<el-button link type="primary" @click="openDialog(row)">编辑</el-button>
					</template>
				</el-table-column>
			</el-table>
		</section>
	</section>

	<el-dialog
		v-model="dialogVisible"
		:title="dialogForm.id ? config.editDialogTitle : config.createDialogTitle"
		width="540px"
	>
		<el-form label-width="80px">
			<el-form-item v-for="field in config.formFields" :key="field.prop" :label="field.label">
				<el-input v-if="field.type !== 'textarea'" v-model="dialogForm[field.prop]" />
				<el-input v-else v-model="dialogForm[field.prop]" type="textarea" :rows="field.rows || 3" />
			</el-form-item>
		</el-form>
		<template #footer>
			<el-button @click="dialogVisible = false">取消</el-button>
			<el-button type="primary" @click="submitDialog">保存</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Delete, Grid, Plus, Printer, RefreshRight } from "@element-plus/icons-vue";
import type { DictionaryCategory, DictionaryItem } from "@/apis/system/type";
import type { SystemDictionaryPageConfig } from "../shared";

const props = defineProps<{
	config: SystemDictionaryPageConfig;
}>();

const categories = ref<DictionaryCategory[]>([]);
const activeCategoryId = ref("");
const items = ref<DictionaryItem[]>([]);
const selectedRows = ref<DictionaryItem[]>([]);
const dialogVisible = ref(false);
const dialogForm = reactive<Record<string, any>>({
	id: undefined,
	name: "",
	info: "",
	sortNum: "",
});

async function loadCategories() {
	const previousCategoryId = activeCategoryId.value;
	categories.value = await props.config.loadCategories();
	activeCategoryId.value =
		previousCategoryId && categories.value.some((item) => item.id === previousCategoryId)
			? previousCategoryId
			: categories.value[0]?.id || "";
	await loadItems();
}

async function loadItems() {
	if (!activeCategoryId.value) {
		items.value = [];
		return;
	}
	items.value = await props.config.loadItems(activeCategoryId.value);
}

async function selectCategory(id: string) {
	activeCategoryId.value = id;
	await loadItems();
}

function handleSelectionChange(rows: DictionaryItem[]) {
	selectedRows.value = rows;
}

function openDialog(row?: DictionaryItem) {
	dialogForm.id = row?.id;
	dialogForm.name = row?.name || "";
	dialogForm.info = row?.info || row?.remark || "";
	dialogForm.sortNum = row?.sortNum ?? "";
	dialogVisible.value = true;
}

async function submitDialog() {
	if (!String(dialogForm.name || "").trim() || !activeCategoryId.value) {
		ElMessage.warning("请填写完整的字典项名称");
		return;
	}

	const sortNumText = String(dialogForm.sortNum ?? "").trim();
	if (sortNumText && Number.isNaN(Number(sortNumText))) {
		ElMessage.warning("排序必须是数字");
		return;
	}

	await props.config.saveItem({
		id: dialogForm.id,
		categoryId: activeCategoryId.value,
		name: String(dialogForm.name).trim(),
		info: String(dialogForm.info || "").trim(),
		sortNum: sortNumText ? Number(sortNumText) : undefined,
	});
	dialogVisible.value = false;
	await loadCategories();
	ElMessage.success(dialogForm.id ? "字典项已更新" : "字典项已新增");
}

async function handleBatchDelete() {
	await ElMessageBox.confirm(`确认删除选中的 ${selectedRows.value.length} 条数据吗？`, "提示", {
		type: "warning",
		confirmButtonText: "删除",
		cancelButtonText: "取消",
	});
	await props.config.deleteItems(selectedRows.value.map((item) => item.id));
	selectedRows.value = [];
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
	padding: 14px 0;
}

.dict-nav__item {
	padding: 14px 22px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	font-size: 17px;
	color: #2f3b53;
	cursor: pointer;
}

.dict-nav__item--active {
	background: #edf4ff;
	color: #4a89f3;
}

.dict-nav__count {
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
}

.dict-table__actions {
	display: flex;
	gap: 12px;
}

@media (max-width: 1280px) {
	.dict-page {
		grid-template-columns: 1fr;
	}
}
</style>
