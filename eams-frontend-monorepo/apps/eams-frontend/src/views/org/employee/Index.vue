<template>
	<!-- start -->
	<div class="employee-page">
		<el-row :gutter="12">
			<el-col :span="6">
				<OrgTreePanel :data="store.orgTree" :loading="store.loading.org" :selected-id="store.selectedOrgId" @select="handleSelectOrg" />
			</el-col>
			<el-col :span="18">
				<el-card shadow="never">
					<div class="filters-row">
						<div class="filters-left">
							<span class="toolbar-label">搜索:</span>
							<el-input v-model="keywordModel" placeholder="姓名或手机号" clearable class="search-input" @keyup.enter="handleSearch" />
							<span class="toolbar-label">状态:</span>
							<el-select v-model="statusModel" placeholder="请选择" clearable class="status-select" @change="handleSearch">
								<el-option label="在职" value="在职" />
								<el-option label="离职" value="离职" />
							</el-select>
						</div>
						<div class="filters-right">
							<el-tooltip content="搜索" placement="top">
								<el-button circle @click="handleSearch">
									<el-icon><Search /></el-icon>
								</el-button>
							</el-tooltip>
							<el-tooltip content="重置" placement="top">
								<el-button circle @click="handleReset">
									<el-icon><Refresh /></el-icon>
								</el-button>
							</el-tooltip>
							<el-button class="export-btn" plain @click="handleExport">导出</el-button>
						</div>
					</div>

					<div class="actions-row">
						<div class="actions-left">
							<el-button type="primary" plain @click="dialogVisible = true">+ 添加员工</el-button>
							<el-button :disabled="!hasSelection" @click="setRoleDialogVisible = true">设置角色</el-button>
							<el-button :disabled="!hasSelection" @click="handleDelete">删除</el-button>
							<el-button :disabled="!hasSelection" @click="transferOrgDialogVisible = true">+ 转机构</el-button>
							<el-button :disabled="!hasSelection" @click="leaveDialogVisible = true">转为离职</el-button>
							<el-button :disabled="!hasSelection" @click="activeDialogVisible = true">转为在职</el-button>
							<el-button :disabled="!hasSelection" @click="openTransferStudentDialog">转学员</el-button>
						</div>
						<div class="actions-right">
							<el-tooltip content="刷新" placement="top">
								<el-button circle @click="handleRefresh">
									<el-icon><Refresh /></el-icon>
								</el-button>
							</el-tooltip>
							<el-tooltip content="打印" placement="top">
								<el-button circle @click="handlePrint">
									<el-icon><Printer /></el-icon>
								</el-button>
							</el-tooltip>
							<el-tooltip content="自定义列" placement="top">
								<el-button circle @click="openColumnDialog">
									<el-icon><Grid /></el-icon>
								</el-button>
							</el-tooltip>
						</div>
					</div>

					<el-table v-loading="store.loading.list" :data="store.list" border @selection-change="handleSelectionChange">
						<el-table-column type="selection" width="45" />
						<el-table-column v-if="isColumnVisible('name')" prop="name" label="姓名" min-width="120" />
						<el-table-column v-if="isColumnVisible('account')" prop="account" label="电话/登录账户" min-width="140" />
						<el-table-column v-if="isColumnVisible('orgName')" prop="orgName" label="所属机构" min-width="200" />
						<el-table-column v-if="isColumnVisible('gender')" prop="gender" label="性别" min-width="70" />
						<el-table-column v-if="isColumnVisible('position')" prop="position" label="职位" min-width="130" />
						<el-table-column v-if="isColumnVisible('roleName')" prop="roleName" label="权限角色" min-width="120" />
						<el-table-column v-if="isColumnVisible('personType')" prop="personType" label="人员类型" min-width="90" />
						<el-table-column v-if="isColumnVisible('hireDate')" prop="hireDate" label="入职日期" min-width="110" />
						<el-table-column v-if="isColumnVisible('status')" prop="status" label="状态" min-width="80" />
						<el-table-column label="操作" min-width="130" fixed="right">
							<template #default="scope">
								<el-button link type="primary" @click="handleOpenEdit(scope.row)">编辑</el-button>
								<el-button link type="primary" @click="handleOpenResetPwd(scope.row)">改密</el-button>
							</template>
						</el-table-column>
					</el-table>

					<div class="pagination-wrap">
						<el-pagination
							background
							layout="total, sizes, prev, pager, next, jumper"
							:total="store.total"
							:current-page="store.page"
							:page-size="store.pageSize"
							:page-sizes="[10, 20, 50]"
							@current-change="handleChangePage"
							@size-change="handleChangePageSize"
						/>
					</div>
				</el-card>
			</el-col>
		</el-row>

		<EmployeeFormDialog
			v-model="dialogVisible"
			:org-options="orgOptions"
			:default-org-id="store.selectedOrgId"
			:submitting="store.loading.add"
			@submit="handleSubmitAdd"
		/>

		<el-dialog v-model="setRoleDialogVisible" title="设置权限" width="520px">
			<el-form>
				<el-form-item label="选择权限角色" required>
					<el-select v-model="selectedRole" placeholder="请选择" class="full-width">
						<el-option v-for="item in store.roleOptions" :key="item" :label="item" :value="item" />
					</el-select>
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="setRoleDialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="store.loading.batch" @click="handleConfirmSetRole">确定</el-button>
			</template>
		</el-dialog>

		<el-dialog v-model="transferOrgDialogVisible" title="转机构" width="620px">
			<el-form>
				<el-form-item label="选择转入机构" required>
					<el-select v-model="targetOrgId" placeholder="请选择" class="full-width" filterable>
						<el-option v-for="item in orgOptions" :key="item.id" :label="item.label" :value="item.id" />
					</el-select>
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="transferOrgDialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="store.loading.batch" @click="handleConfirmTransferOrg">确定</el-button>
			</template>
		</el-dialog>

		<el-dialog v-model="leaveDialogVisible" title="转为离职" width="520px">
			<el-form>
				<el-form-item label="办理日期" required>
					<el-date-picker v-model="leaveDate" type="date" value-format="YYYY-MM-DD" class="full-width" />
				</el-form-item>
				<el-form-item label="状态">
					<el-select model-value="离职" disabled class="full-width">
						<el-option label="离职" value="离职" />
					</el-select>
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="leaveDialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="store.loading.batch" @click="handleConfirmLeave">提交</el-button>
			</template>
		</el-dialog>

		<el-dialog v-model="activeDialogVisible" title="转为在职" width="520px">
			<el-form>
				<el-form-item label="办理日期" required>
					<el-date-picker v-model="activeDate" type="date" value-format="YYYY-MM-DD" class="full-width" />
				</el-form-item>
				<el-form-item label="状态">
					<el-select model-value="在职" disabled class="full-width">
						<el-option label="在职" value="在职" />
					</el-select>
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="activeDialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="store.loading.batch" @click="handleConfirmActive">提交</el-button>
			</template>
		</el-dialog>

		<TransferStudentDialog
			v-model="transferStudentDialogVisible"
			:selected-employee-name="selectedRows[0]?.name || ''"
			:submitting="store.loading.batch"
			@submit="handleConfirmTransferStudent"
		/>
		<el-dialog v-model="columnDialogVisible" title="自定义显示列：" width="520px" destroy-on-close>
			<div class="column-dialog-body">
				<el-checkbox-group v-model="draftCheckedColumns" class="column-grid">
					<el-checkbox v-for="item in allColumns" :key="item.key" :label="item.key">{{ item.label }}</el-checkbox>
				</el-checkbox-group>
			</div>
			<template #footer>
				<div class="column-footer">
					<el-button @click="handleRestoreColumns">恢复</el-button>
					<el-button type="primary" @click="handleConfirmColumns">确认</el-button>
				</div>
			</template>
		</el-dialog>
		<EmployeeEditDialog
			v-model="editDialogVisible"
			:submitting="store.loading.add"
			:org-options="orgOptions"
			:data="editingEmployee"
			@submit="handleSubmitEdit"
		/>
		<ResetPasswordDialog v-model="resetPwdDialogVisible" :submitting="store.loading.batch" @submit="handleSubmitResetPwd" />
	</div>
	<!-- end -->
</template>

<script setup lang="ts">
import { computed, onMounted, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Grid, Printer, Refresh, Search } from "@element-plus/icons-vue";
import OrgTreePanel from "@/components/org/employee/OrgTreePanel.vue";
import EmployeeFormDialog from "@/components/org/employee/EmployeeFormDialog.vue";
import EmployeeEditDialog from "@/components/org/employee/EmployeeEditDialog.vue";
import ResetPasswordDialog from "@/components/org/employee/ResetPasswordDialog.vue";
import TransferStudentDialog from "@/components/org/employee/TransferStudentDialog.vue";
import { useEmployeeManageStore } from "@/stores/org/employeeManage";
import type { EmployeeCreatePayload, EmployeeItem, EmployeeUpdatePayload, OrgNode } from "@/apis/org/employeeManage";

const store = useEmployeeManageStore();
const dialogVisible = ref(false);
const setRoleDialogVisible = ref(false);
const transferOrgDialogVisible = ref(false);
const leaveDialogVisible = ref(false);
const activeDialogVisible = ref(false);
const transferStudentDialogVisible = ref(false);
const editDialogVisible = ref(false);
const resetPwdDialogVisible = ref(false);
const keywordModel = ref("");
const statusModel = ref<"" | "在职" | "离职">("");
const selectedRows = ref<EmployeeItem[]>([]);
const editingEmployee = ref<EmployeeItem | null>(null);
const resettingEmployee = ref<EmployeeItem | null>(null);
const selectedRole = ref("");
const targetOrgId = ref("");
const leaveDate = ref(new Date().toISOString().slice(0, 10));
const activeDate = ref(new Date().toISOString().slice(0, 10));
const hasSelection = computed(() => selectedRows.value.length > 0);
const selectedIds = computed(() => selectedRows.value.map((i) => i.id));
const allColumns = [
	{ key: "name", label: "姓名" },
	{ key: "account", label: "电话/登录账户" },
	{ key: "orgName", label: "所属机构" },
	{ key: "gender", label: "性别" },
	{ key: "position", label: "职位" },
	{ key: "roleName", label: "权限角色" },
	{ key: "personType", label: "人员类型" },
	{ key: "hireDate", label: "入职日期" },
	{ key: "status", label: "状态" },
] as const;
const checkedColumns = ref<string[]>(allColumns.map((i) => i.key));
const columnDialogVisible = ref(false);
const defaultColumnKeys = allColumns.map((i) => i.key);
const draftCheckedColumns = ref<string[]>([...checkedColumns.value]);

onMounted(async () => {
	await store.initPage();
	keywordModel.value = store.keyword;
	statusModel.value = store.status;
});

const orgOptions = computed(() => {
	const result: Array<{ id: string; label: string }> = [];
	const walk = (nodes: OrgNode[], depth: number) => {
		nodes.forEach((node) => {
			result.push({
				id: node.id,
				label: `${depth > 0 ? `${"  ".repeat(depth)}- ` : ""}${node.name}`,
			});
			if (node.children?.length) walk(node.children, depth + 1);
		});
	};
	walk(store.orgTree, 0);
	return result;
});

async function handleSelectOrg(orgId: string) {
	try {
		await store.setOrgAndQuery(orgId);
	} catch {
		ElMessage.error("加载数据失败");
	}
}

async function handleSearch() {
	try {
		await store.setQueryAndSearch({ keyword: keywordModel.value, status: statusModel.value });
	} catch {
		ElMessage.error("加载数据失败");
	}
}

async function handleReset() {
	keywordModel.value = "";
	statusModel.value = "";
	try {
		await store.setQueryAndSearch({ keyword: "", status: "" });
	} catch {
		ElMessage.error("加载数据失败");
	}
}

async function handleChangePage(page: number) {
	try {
		await store.setPage(page);
	} catch {
		ElMessage.error("加载数据失败");
	}
}

async function handleChangePageSize(size: number) {
	try {
		await store.setPageSize(size);
	} catch {
		ElMessage.error("加载数据失败");
	}
}

async function handleSubmitAdd(payload: EmployeeCreatePayload) {
	try {
		await store.addEmployee(payload);
		dialogVisible.value = false;
		ElMessage.success("员工添加成功");
	} catch (e: any) {
		ElMessage.error(e?.message || "员工添加失败");
	}
}

function handleSelectionChange(rows: EmployeeItem[]) {
	selectedRows.value = rows;
}

async function handleConfirmSetRole() {
	if (!selectedRole.value) return ElMessage.warning("请选择权限角色");
	await store.batchSetRole(selectedIds.value, selectedRole.value);
	setRoleDialogVisible.value = false;
	ElMessage.success("设置角色成功");
}

function isColumnVisible(key: string) {
	return checkedColumns.value.includes(key);
}

function openColumnDialog() {
	draftCheckedColumns.value = [...checkedColumns.value];
	columnDialogVisible.value = true;
}

function handleRestoreColumns() {
	draftCheckedColumns.value = [...defaultColumnKeys];
}

function handleConfirmColumns() {
	checkedColumns.value = [...draftCheckedColumns.value];
	columnDialogVisible.value = false;
}

async function handleRefresh() {
	try {
		await store.fetchEmployeeList();
		ElMessage.success("已刷新");
	} catch {
		ElMessage.error("加载数据失败");
	}
}

function handlePrint() {
	window.print();
}

async function handleExport() {
	try {
		await store.exportEmployeeList();
		ElMessage.success("已发起导出请求");
	} catch (e: any) {
		ElMessage.error(e?.message || "导出失败");
	}
}

async function handleDelete() {
	try {
		await ElMessageBox.confirm("该操作会永久删除，请谨慎操作！", "操作提示", { type: "warning", confirmButtonText: "确认", cancelButtonText: "取消" });
		await store.batchDelete(selectedIds.value);
		ElMessage.success("删除成功");
	} catch {
		// cancel
	}
}

async function handleConfirmTransferOrg() {
	if (!targetOrgId.value) return ElMessage.warning("请选择转入机构");
	await store.batchTransferOrg(selectedIds.value, targetOrgId.value);
	transferOrgDialogVisible.value = false;
	ElMessage.success("转机构成功");
}

async function handleConfirmLeave() {
	if (!leaveDate.value) return ElMessage.warning("请选择办理日期");
	await store.batchChangeStatus(selectedIds.value, "离职");
	leaveDialogVisible.value = false;
	ElMessage.success("已转为离职");
}

async function handleConfirmActive() {
	if (!activeDate.value) return ElMessage.warning("请选择办理日期");
	await store.batchChangeStatus(selectedIds.value, "在职");
	activeDialogVisible.value = false;
	ElMessage.success("已转为在职");
}

async function openTransferStudentDialog() {
	if (selectedRows.value.length !== 1) return ElMessage.warning("请先选择一位员工");
	transferStudentDialogVisible.value = true;
}

async function handleConfirmTransferStudent() {
	if (selectedRows.value.length !== 1) return ElMessage.warning("请先选择一位员工");
	const id = selectedRows.value[0].id;
	await store.batchTransferStudent([id], id);
	transferStudentDialogVisible.value = false;
	ElMessage.success("转学员成功");
}

function handleOpenEdit(row: EmployeeItem) {
	editingEmployee.value = row;
	editDialogVisible.value = true;
}

async function handleSubmitEdit(payload: EmployeeUpdatePayload) {
	await store.editEmployee(payload);
	editDialogVisible.value = false;
	ElMessage.success("员工信息已更新");
}

function handleOpenResetPwd(row: EmployeeItem) {
	resettingEmployee.value = row;
	resetPwdDialogVisible.value = true;
}

async function handleSubmitResetPwd(newPassword: string) {
	if (!resettingEmployee.value) return;
	await store.changePassword(resettingEmployee.value.id, newPassword);
	resetPwdDialogVisible.value = false;
	ElMessage.success("密码已重置");
}
</script>

<style scoped>
.employee-page {
	padding: 0 8px 12px;
}

.toolbar {
	display: flex;
	justify-content: space-between;
	margin-bottom: 12px;
}

.toolbar-actions {
	margin-top: 2px;
}

.toolbar-left {
	display: flex;
	align-items: center;
	gap: 8px;
}

.toolbar-label {
	color: #606266;
	font-size: 14px;
}

.filters-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	margin-bottom: 10px;
	gap: 12px;
}

.filters-left {
	display: flex;
	align-items: center;
	gap: 10px;
	flex-wrap: wrap;
}

.filters-right {
	display: flex;
	align-items: center;
	gap: 12px;
}

.right-icons {
	display: flex;
	align-items: center;
	gap: 8px;
}

.export-btn {
	padding: 0 10px;
}

.actions-row {
	margin-bottom: 12px;
	display: flex;
	justify-content: space-between;
	align-items: center;
	gap: 12px;
}

.actions-left {
	display: flex;
	align-items: center;
	gap: 8px;
}

.actions-right {
	display: flex;
	align-items: center;
	gap: 8px;
}

.toolbar-right {
	display: flex;
	align-items: center;
	gap: 8px;
}

.search-input {
	width: 220px;
}

.status-select {
	width: 140px;
}

.pagination-wrap {
	display: flex;
	justify-content: flex-end;
	margin-top: 12px;
}

.full-width {
	width: 100%;
}

.column-dialog-body {
	padding: 2px 0 4px;
}

.column-grid {
	display: grid;
	grid-template-columns: repeat(3, 1fr);
	gap: 10px 18px;
	padding: 6px 8px;
}

.column-grid :deep(.el-checkbox__label) {
	white-space: nowrap;
}

.column-footer {
	display: flex;
	justify-content: flex-end;
	gap: 16px;
	width: 100%;
}

.student-pick-toolbar {
	display: flex;
	align-items: center;
	gap: 8px;
	margin: 4px 0 10px;
}

.student-search-input {
	width: 220px;
}
</style>

