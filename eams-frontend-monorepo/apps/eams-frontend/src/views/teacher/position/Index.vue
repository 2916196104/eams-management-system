<template>
	<div class="page">
		<el-card shadow="never" class="main-card">
			<!-- 第一行：搜名称 + 右侧合并「查询 / 重置」 -->
			<div class="toolbar-row toolbar-row-search">
				<div class="toolbar-left">
					<span class="label">搜名称:</span>
					<el-input
						v-model="keyword"
						class="keyword-input"
						placeholder="请输入"
						clearable
						@keyup.enter="handleSearch"
						@clear="handleSearch"
					/>
				</div>
				<div class="toolbar-right">
					<el-button-group class="search-btn-group">
						<el-tooltip content="查询" placement="top">
							<el-button class="search-seg-btn" :icon="Search" @click="handleSearch" />
						</el-tooltip>
						<el-tooltip content="重置" placement="top">
							<el-button class="search-seg-btn" :icon="CircleClose" @click="handleReset" />
						</el-tooltip>
					</el-button-group>
				</div>
			</div>

			<!-- 第二行：左侧新增/删除，右侧刷新/打印/列设置 -->
			<div class="toolbar-row toolbar-row-actions">
				<div class="toolbar-left actions-primary">
					<el-button type="primary" :icon="Plus" @click="openAdd">新增</el-button>
					<el-button :disabled="!selectedIds.length" :icon="Delete" @click="handleBatchDelete">删除</el-button>
				</div>
				<div class="toolbar-right utility-icons">
					<el-tooltip content="刷新" placement="top">
						<el-button text type="primary" class="utility-icon-btn" :icon="RefreshRight" @click="store.refresh" />
					</el-tooltip>
					<el-tooltip content="打印" placement="top">
						<el-button text type="primary" class="utility-icon-btn" :icon="Printer" @click="handlePrint" />
					</el-tooltip>
					<el-tooltip content="自定义列" placement="top">
						<el-button text type="primary" class="utility-icon-btn" :icon="Grid" @click="handleColumnConfig" />
					</el-tooltip>
				</div>
			</div>

			<el-table
				v-loading="store.loading"
				:data="store.list"
				border
				row-key="id"
				@selection-change="handleSelectionChange"
			>
				<el-table-column type="selection" width="46" />
				<el-table-column label="职位名称" prop="name" min-width="240" />
				<el-table-column label="操作" width="180" fixed="right">
					<template #default="{ row }">
						<el-button type="primary" link @click="openEdit(row)">编辑</el-button>
						<el-button type="primary" link @click="openPermission(row)">数据权限</el-button>
					</template>
				</el-table-column>
			</el-table>

			<div class="pager">
				<div class="total">共 {{ store.total }} 条</div>
				<el-pagination
					background
					layout="sizes, prev, pager, next, jumper"
					:page-sizes="[10, 20, 30, 50, 100]"
					:page-size="store.pageSize"
					:current-page="store.pageIndex"
					:total="store.total"
					@size-change="store.setPageSize"
					@current-change="store.setPage"
				/>
			</div>
		</el-card>

		<el-dialog :model-value="editDialogVisible" :title="editForm.id ? '修改职位信息' : '新增职位'" width="720px" destroy-on-close @close="closeEdit">
			<el-form ref="editFormRef" :model="editForm" :rules="editRules" label-width="90px">
				<el-form-item label="职位名称" prop="name" required>
					<el-input v-model="editForm.name" maxlength="30" placeholder="请输入名称" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="closeEdit">取消</el-button>
				<el-button type="primary" :loading="saving" @click="submitEdit">提交</el-button>
			</template>
		</el-dialog>

		<el-dialog :model-value="permDialogVisible" :title="permTitle" width="980px" destroy-on-close @close="closePermission">
			<div class="perm-actions">
				<el-button type="primary" :icon="Plus" @click="openPermAdd">新增</el-button>
				<el-button :disabled="!permSelectedIds.length" :icon="Delete" @click="handlePermBatchDelete">删除</el-button>
			</div>

			<el-table
				v-loading="store.permissionLoading"
				:data="store.permissionList"
				border
				row-key="id"
				@selection-change="handlePermSelectionChange"
			>
				<el-table-column type="selection" width="46" />
				<el-table-column label="数据实体表" prop="entityName" min-width="200" />
				<el-table-column label="数据范围类型" prop="scopeType" min-width="160" />
				<el-table-column label="数据表code" prop="tableCode" min-width="160" />
				<el-table-column label="数据负责人字段" prop="ownerField" min-width="160" />
				<el-table-column label="数据所属组织字段" prop="ownerOrgField" min-width="180" />
				<el-table-column label="操作" width="90" fixed="right">
					<template #default="{ row }">
						<el-button type="primary" link @click="openPermEdit(row)">编辑</el-button>
					</template>
				</el-table-column>
			</el-table>

			<div class="perm-pager">
				<el-pagination
					background
					layout="sizes, prev, pager, next"
					:page-sizes="[10, 20, 30, 50]"
					:page-size="store.permissionPageSize"
					:current-page="store.permissionPageIndex"
					:total="store.permissionTotal"
					@size-change="store.setPermissionPageSize"
					@current-change="store.setPermissionPage"
				/>
			</div>
		</el-dialog>

		<el-dialog :model-value="permEditVisible" title="设置岗位的数据查看权限" width="980px" destroy-on-close @close="closePermEdit">
			<div class="perm-form-desc">
				数据权限是通过对实体表的范围查询来控制的；负责人字段里存放的是员工的ID，该字段名要和数据库里的一致；未定义的实体表默认不参与数据权限控制；范围类型依托组织结构的层级关系。
			</div>
			<el-form ref="permFormRef" :model="permForm" :rules="permRules" label-width="140px" class="perm-form">
				<el-form-item label="数据实体表" prop="entityName" required>
					<el-select v-model="permForm.entityName" filterable class="full" placeholder="请选择">
						<el-option v-for="item in entityOptions" :key="item.value" :label="item.label" :value="item.value" />
					</el-select>
					<div class="minor-hint">带(*)的表示默认不支持设置为“权限范围类型-自己的数据”</div>
				</el-form-item>
				<el-form-item label="数据负责人字段名" prop="ownerField">
					<el-input v-model="permForm.ownerField" placeholder="" />
					<div class="minor-hint">建议留空表示按系统默认，开发人员可以根据表内容定义该字段名</div>
				</el-form-item>
				<el-form-item label="数据所属组织字段名" prop="ownerOrgField">
					<el-input v-model="permForm.ownerOrgField" placeholder="" />
					<div class="minor-hint">建议留空表示按系统默认，开发人员可以根据表内容定义该字段名</div>
				</el-form-item>
				<el-form-item label="权限范围类型" prop="scopeType" required>
					<el-radio-group v-model="permForm.scopeType">
						<el-radio :value="0">全部</el-radio>
						<el-radio :value="1">本集团数据</el-radio>
						<el-radio :value="2">本校数据</el-radio>
						<el-radio :value="3">本部门数据</el-radio>
						<el-radio :value="4">自己的数据</el-radio>
						<el-radio :value="5">自定义</el-radio>
					</el-radio-group>
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="closePermEdit">取消</el-button>
				<el-button type="primary" :loading="permSaving" @click="submitPerm">提交</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox, type FormInstance, type FormRules } from "element-plus";
import { CircleClose, Delete, Grid, Plus, Printer, RefreshRight, Search } from "@element-plus/icons-vue";
import { usePositionManageStore } from "@/stores/org/positionManage";
import type { PositionPermissionRow, PositionRow } from "@/apis/org/positionManage";

const store = usePositionManageStore();

const keyword = ref(store.keyword);
const selectedIds = ref<string[]>([]);

const editDialogVisible = ref(false);
const saving = ref(false);
const editFormRef = ref<FormInstance>();
const editForm = reactive<{ id?: string; name: string }>({ id: undefined, name: "" });
const editRules: FormRules = {
	name: [{ required: true, message: "请输入名称", trigger: "blur" }],
};

const permDialogVisible = ref(false);
const permSelectedIds = ref<string[]>([]);
const permTitle = computed(() => "岗位的数据权限列表");

const permEditVisible = ref(false);
const permSaving = ref(false);
const permFormRef = ref<FormInstance>();
const permForm = reactive<{ id?: string; entityName: string; ownerField: string; ownerOrgField: string; scopeType: number }>({
	id: undefined,
	entityName: "",
	ownerField: "",
	ownerOrgField: "",
	scopeType: 0,
});
const permRules: FormRules = {
	entityName: [{ required: true, message: "请选择数据实体表", trigger: "change" }],
	scopeType: [{ required: true, message: "请选择权限范围类型", trigger: "change" }],
};

const entityOptions = [
	{ label: "排课计划表", value: "schedule_plan" },
	{ label: "跟进记录表", value: "follow_record" },
	{ label: "学生表", value: "student" },
	{ label: "上课预约表", value: "lesson_reserve" },
	{ label: "在线购课订单表(*)", value: "online_order" },
	{ label: "学生请假", value: "student_leave" },
	{ label: "购课退款表(*)", value: "refund_order" },
];

onMounted(async () => {
	await store.fetchList();
});

function handleSelectionChange(rows: PositionRow[]) {
	selectedIds.value = rows.map((i) => i.id);
}

async function handleSearch() {
	await store.search(keyword.value);
}

async function handleReset() {
	keyword.value = "";
	await store.search("");
}

function handlePrint() {
	window.print();
}

function handleColumnConfig() {
	ElMessage.info("自定义列：本页面为固定列展示");
}

function openAdd() {
	editForm.id = undefined;
	editForm.name = "";
	editDialogVisible.value = true;
}

function openEdit(row: PositionRow) {
	editForm.id = row.id;
	editForm.name = row.name;
	editDialogVisible.value = true;
}

function closeEdit() {
	editDialogVisible.value = false;
}

async function submitEdit() {
	try {
		await editFormRef.value?.validate();
		saving.value = true;
		await store.savePosition({ id: editForm.id, name: editForm.name.trim() });
		editDialogVisible.value = false;
	} catch {
		ElMessage.warning("请完善必填项");
	} finally {
		saving.value = false;
	}
}

async function handleBatchDelete() {
	if (!selectedIds.value.length) return;
	try {
		await ElMessageBox.confirm("确定删除所选职位吗？", "删除确认", { type: "warning" });
		await store.batchDelete([...selectedIds.value]);
		selectedIds.value = [];
	} catch {
		// ignore
	}
}

async function openPermission(row: PositionRow) {
	permSelectedIds.value = [];
	permDialogVisible.value = true;
	await store.openPermission(row.id);
}

function closePermission() {
	permDialogVisible.value = false;
	permSelectedIds.value = [];
}

function handlePermSelectionChange(rows: PositionPermissionRow[]) {
	permSelectedIds.value = rows.map((i) => i.id);
}

function openPermAdd() {
	permForm.id = undefined;
	permForm.entityName = "";
	permForm.ownerField = "";
	permForm.ownerOrgField = "";
	permForm.scopeType = 0;
	permEditVisible.value = true;
}

function openPermEdit(row: PositionPermissionRow) {
	permForm.id = row.id;
	permForm.entityName = row.entityName;
	permForm.ownerField = row.ownerField;
	permForm.ownerOrgField = row.ownerOrgField;
	permForm.scopeType = Number(row.scopeType) || 0;
	permEditVisible.value = true;
}

function closePermEdit() {
	permEditVisible.value = false;
}

async function submitPerm() {
	try {
		await permFormRef.value?.validate();
		permSaving.value = true;
		await store.savePermission({
			id: permForm.id,
			entityName: permForm.entityName,
			ownerField: permForm.ownerField,
			ownerOrgField: permForm.ownerOrgField,
			scopeType: permForm.scopeType,
		});
		permEditVisible.value = false;
	} catch {
		ElMessage.warning("请完善必填项");
	} finally {
		permSaving.value = false;
	}
}

async function handlePermBatchDelete() {
	if (!permSelectedIds.value.length) return;
	try {
		await ElMessageBox.confirm("确定删除所选数据权限吗？", "删除确认", { type: "warning" });
		await store.removePermissions([...permSelectedIds.value]);
		permSelectedIds.value = [];
	} catch {
		// ignore
	}
}
</script>

<style scoped>
.page {
	padding: 12px;
}
.main-card {
	border-radius: 6px;
}
.toolbar-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 16px;
}
.toolbar-row-search {
	margin-bottom: 12px;
}
.toolbar-row-actions {
	margin-bottom: 12px;
}
.toolbar-left {
	display: flex;
	align-items: center;
	gap: 10px;
	flex-wrap: wrap;
}
.toolbar-right {
	display: flex;
	align-items: center;
	justify-content: flex-end;
	flex-shrink: 0;
}
.label {
	color: #606266;
	white-space: nowrap;
}
.keyword-input {
	width: 260px;
	max-width: 100%;
}
.search-btn-group {
	border-radius: 4px;
	overflow: hidden;
}
.search-btn-group .search-seg-btn {
	margin: 0;
	padding: 8px 12px;
	border-color: var(--el-border-color);
	color: var(--el-text-color-secondary);
}
.search-btn-group .search-seg-btn:hover {
	color: var(--el-color-primary);
	border-color: var(--el-color-primary-light-5);
}
.actions-primary {
	gap: 10px;
}
.utility-icons {
	gap: 4px;
}
.utility-icon-btn {
	font-size: 18px;
	padding: 8px;
}
.pager {
	display: flex;
	align-items: center;
	justify-content: space-between;
	padding-top: 12px;
}
.total {
	color: #606266;
}
.perm-actions {
	display: flex;
	align-items: center;
	gap: 10px;
	margin-bottom: 12px;
}
.perm-pager {
	display: flex;
	justify-content: flex-end;
	padding-top: 12px;
}
.perm-form-desc {
	color: #606266;
	line-height: 20px;
	margin-bottom: 14px;
}
.perm-form :deep(.el-form-item__content) {
	flex-wrap: wrap;
}
.full {
	width: 520px;
}
.minor-hint {
	width: 100%;
	color: #909399;
	font-size: 12px;
	line-height: 18px;
	margin-top: 4px;
}
</style>

