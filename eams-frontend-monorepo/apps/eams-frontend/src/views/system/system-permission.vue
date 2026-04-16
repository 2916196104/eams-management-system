<template>
	<div class="system-permission">
		<div class="permission-shell">
			<section class="role-panel">
				<div class="panel-title">角色列表</div>
				<div class="toolbar-row">
					<el-button type="primary" class="primary-action" :icon="Plus" @click="handleAddRole">添加角色</el-button>
				</div>

				<div class="role-table" v-loading="permissionStore.rolesLoading">
					<div class="table-header role-grid">
						<div>角色名称</div>
						<div>编码</div>
						<div>操作</div>
					</div>

					<el-scrollbar class="table-scroll">
						<template v-if="permissionStore.roles.length > 0">
							<div
								v-for="role in permissionStore.roles"
								:key="role.id"
								class="table-row role-grid role-row"
								:class="{ active: permissionStore.currentRoleId === role.id }"
								@click="handleSelectRole(role.id)"
							>
								<div class="row-primary">{{ role.name }}</div>
								<div class="row-secondary">{{ role.code }}</div>
								<div class="row-actions">
									<button type="button" class="link-button" @click.stop="handleOpenPermissionDialog(role)">
										管理权限
									</button>
									<button type="button" class="link-button" @click.stop="handleEditRole(role)">编辑</button>
									<button type="button" class="link-button danger" @click.stop="handleDeleteRole(role.id)">删除</button>
								</div>
							</div>
						</template>
						<el-empty v-else description="暂无角色" :image-size="72" />
					</el-scrollbar>
				</div>
			</section>

			<section class="staff-panel">
				<div class="panel-title">设置人员</div>
				<div class="toolbar-row toolbar-row-right">
					<el-button
						type="primary"
						class="primary-action"
						:icon="Plus"
						:disabled="!permissionStore.currentRoleId"
						@click="handleAddStaff"
					>
						给角色配置人员
					</el-button>
					<el-button :icon="Delete" :disabled="!selectedStaffIds.length" @click="handleBatchRemoveStaff">
						从角色移除人员
					</el-button>
				</div>

				<div class="staff-table" v-loading="permissionStore.staffsLoading">
					<div class="table-header staff-grid">
						<div class="checkbox-col">
							<el-checkbox
								:model-value="isAllStaffSelected"
								:indeterminate="isStaffSelectionIndeterminate"
								:disabled="permissionStore.staffs.length === 0"
								@change="handleToggleAllStaff"
							/>
						</div>
						<div>员工姓名</div>
						<div>手机号</div>
					</div>

					<el-scrollbar class="table-scroll">
						<template v-if="permissionStore.currentRoleId && permissionStore.staffs.length > 0">
							<div v-for="staff in permissionStore.staffs" :key="staff.staffId" class="table-row staff-grid">
								<div class="checkbox-col">
									<el-checkbox
										:model-value="selectedStaffIds.includes(staff.staffId)"
										@change="() => handleToggleStaff(staff.staffId)"
									/>
								</div>
								<div class="row-primary">{{ staff.name }}</div>
								<div class="row-secondary">{{ staff.mobile }}</div>
							</div>
						</template>
						<el-empty v-else-if="permissionStore.currentRoleId" description="当前角色暂无人员" :image-size="72" />
						<el-empty v-else description="请先选择左侧角色" :image-size="72" />
					</el-scrollbar>
				</div>
			</section>
		</div>

		<el-dialog v-model="roleDialogVisible" :title="roleDialogTitle" width="420px" destroy-on-close>
			<el-form ref="roleFormRef" :model="roleForm" :rules="roleFormRules" label-width="80px">
				<el-form-item label="角色名称" prop="name">
					<el-input v-model="roleForm.name" placeholder="请输入角色名称" />
				</el-form-item>
				<el-form-item label="角色编码" prop="code">
					<el-input v-model="roleForm.code" placeholder="请输入角色编码" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="roleDialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="submitLoading" @click="handleRoleSubmit">确定</el-button>
			</template>
		</el-dialog>

		<el-dialog v-model="staffDialogVisible" title="给角色配置人员" width="460px" destroy-on-close>
			<el-form ref="staffFormRef" :model="staffForm" :rules="staffFormRules" label-width="80px">
				<el-form-item label="员工" prop="staffId">
					<el-select
						v-model="staffForm.staffId"
						filterable
						remote
						clearable
						reserve-keyword
						loading-text="搜索中"
						no-match-text="没有匹配员工"
						no-data-text="暂无可选员工"
						placeholder="请输入姓名搜索员工"
						style="width: 100%"
						:loading="permissionStore.operatorsLoading"
						:remote-method="handleSearchOperator"
					>
						<el-option
							v-for="operator in availableOperators"
							:key="operator.id"
							:label="formatOperatorLabel(operator)"
							:value="operator.id"
						/>
					</el-select>
				</el-form-item>
				<div v-if="selectedOperator" class="operator-tip">
					<span>已选员工：</span>
					<span>{{ selectedOperator.name }}</span>
					<span v-if="selectedOperator.positionName">/ {{ selectedOperator.positionName }}</span>
				</div>
			</el-form>
			<template #footer>
				<el-button @click="staffDialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="submitLoading" @click="handleStaffSubmit">确定</el-button>
			</template>
		</el-dialog>

		<el-dialog
			v-model="permissionDialogVisible"
			:title="`${permissionRoleName}的权限`"
			width="880px"
			top="4vh"
			class="permission-dialog"
			destroy-on-close
		>
			<div class="permission-dialog-tip">刷新页面后生效</div>
			<el-scrollbar max-height="68vh">
				<div class="permission-groups">
					<section v-for="group in permissionGroupsForDialog" :key="group.groupName" class="permission-group-card">
						<div class="permission-group-title">
							<el-checkbox
								:model-value="isGroupChecked(group.permissionIds)"
								:indeterminate="isGroupIndeterminate(group.permissionIds)"
								@change="(value) => handleToggleGroup(group.permissionIds, value)"
							/>
							<span>{{ group.groupName }}</span>
						</div>
						<el-checkbox-group v-model="editingPermissionIds" class="permission-check-grid">
							<el-checkbox v-for="permission in group.permissions" :key="permission.id" :value="permission.id">
								{{ permission.name }}
							</el-checkbox>
						</el-checkbox-group>
					</section>
				</div>
			</el-scrollbar>
			<template #footer>
				<el-button @click="permissionDialogVisible = false">关闭</el-button>
				<el-button type="primary" :loading="permissionSubmitLoading" @click="handleSavePermissions">保存权限</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref, watch } from "vue";
import { ElMessage, ElMessageBox, type FormInstance } from "element-plus";
import { Delete, Plus } from "@element-plus/icons-vue";
import { useSystemPermissionStore, type OperatorItem, type RoleItem } from "@/stores/systemPermission";

const permissionStore = useSystemPermissionStore();

const selectedStaffIds = ref<number[]>([]);
const permissionDialogVisible = ref(false);
const permissionRoleId = ref<number | null>(null);
const permissionRoleName = ref("管理角色");
const editingPermissionIds = ref<number[]>([]);
const permissionSubmitLoading = ref(false);

const roleDialogVisible = ref(false);
const roleDialogTitle = ref("新增角色");
const submitLoading = ref(false);
const roleFormRef = ref<FormInstance>();
const roleForm = reactive({
	id: 0,
	name: "",
	code: "",
});

const roleFormRules = {
	name: [{ required: true, message: "请输入角色名称", trigger: "blur" }],
	code: [{ required: true, message: "请输入角色编码", trigger: "blur" }],
};

const staffDialogVisible = ref(false);
const staffFormRef = ref<FormInstance>();
const staffForm = reactive<{
	staffId?: number;
}>({
	staffId: undefined,
});

const staffFormRules = {
	staffId: [{ required: true, message: "请选择员工", trigger: "change" }],
};

const permissionGroupsForDialog = computed(() => {
	return permissionStore.permissionGroups.map((group) => ({
		groupName: group.groupName ?? "未分组",
		permissions: (group.permissions ?? []).filter((item) => item.id != null),
		permissionIds: (group.permissions ?? [])
			.map((item) => item.id)
			.filter((id): id is number => typeof id === "number"),
	}));
});

const selectedOperator = computed(() => {
	return permissionStore.operators.find((item) => item.id === staffForm.staffId) ?? null;
});

const availableOperators = computed(() => {
	const assignedIds = new Set(permissionStore.staffs.map((item) => item.staffId));
	return permissionStore.operators.filter((item) => item.id === staffForm.staffId || !assignedIds.has(item.id));
});

const isAllStaffSelected = computed(() => {
	return permissionStore.staffs.length > 0 && selectedStaffIds.value.length === permissionStore.staffs.length;
});

const isStaffSelectionIndeterminate = computed(() => {
	return selectedStaffIds.value.length > 0 && selectedStaffIds.value.length < permissionStore.staffs.length;
});

watch(
	() => permissionStore.staffs,
	() => {
		selectedStaffIds.value = [];
	},
	{ deep: true },
);

watch(
	() => permissionStore.selectedPermissionIds,
	(value) => {
		editingPermissionIds.value = [...value];
	},
	{ immediate: true },
);

function formatOperatorLabel(operator: OperatorItem) {
	return operator.positionName ? `${operator.name} / ${operator.positionName}` : operator.name;
}

function handleAddRole() {
	roleDialogTitle.value = "新增角色";
	roleForm.id = 0;
	roleForm.name = "";
	roleForm.code = "";
	roleDialogVisible.value = true;
}

function handleEditRole(role: RoleItem) {
	roleDialogTitle.value = "编辑角色";
	roleForm.id = role.id;
	roleForm.name = role.name;
	roleForm.code = role.code;
	roleDialogVisible.value = true;
}

async function handleRoleSubmit() {
	await roleFormRef.value?.validate();
	submitLoading.value = true;
	const success = await permissionStore.saveRole({
		id: roleForm.id,
		name: roleForm.name,
		code: roleForm.code,
	});
	submitLoading.value = false;

	if (!success) {
		ElMessage.error("角色保存失败，请检查接口配置");
		return;
	}

	roleDialogVisible.value = false;
	ElMessage.success(roleForm.id === 0 ? "新增成功" : "修改成功");
	await ensureCurrentRole(roleForm.id || permissionStore.currentRoleId);
}

async function handleDeleteRole(roleId: number) {
	await ElMessageBox.confirm("确定删除该角色吗？", "删除角色", { type: "warning" });
	const success = await permissionStore.removeRole(roleId);
	if (!success) {
		ElMessage.error("删除失败，请检查接口配置");
		return;
	}

	ElMessage.success("删除成功");
	if (permissionStore.currentRoleId === roleId) {
		await ensureCurrentRole();
	}
}

async function handleSelectRole(roleId: number) {
	const success = await permissionStore.selectRole(roleId);
	if (!success) {
		ElMessage.error("角色关联数据加载失败，请检查接口配置");
	}
}

async function handleAddStaff() {
	if (!permissionStore.currentRoleId) return;

	staffForm.staffId = undefined;
	staffDialogVisible.value = true;

	const success = await permissionStore.fetchOperators();
	if (!success) {
		ElMessage.error("员工列表加载失败，请检查接口配置");
	}
}

function handleSearchOperator(keyword: string) {
	void permissionStore.fetchOperators(keyword.trim());
}

async function handleStaffSubmit() {
	await staffFormRef.value?.validate();
	if (!permissionStore.currentRoleId || staffForm.staffId == null) return;

	submitLoading.value = true;
	const success = await permissionStore.addStaff({
		roleId: permissionStore.currentRoleId,
		staffId: staffForm.staffId,
	});
	submitLoading.value = false;

	if (!success) {
		ElMessage.error("配置人员失败，请检查接口配置");
		return;
	}

	staffDialogVisible.value = false;
	staffForm.staffId = undefined;
	ElMessage.success("添加成功");
}

function handleToggleStaff(staffId: number) {
	if (selectedStaffIds.value.includes(staffId)) {
		selectedStaffIds.value = selectedStaffIds.value.filter((id) => id !== staffId);
		return;
	}

	selectedStaffIds.value = [...selectedStaffIds.value, staffId];
}

function handleToggleAllStaff(value: string | number | boolean) {
	selectedStaffIds.value = value ? permissionStore.staffs.map((item) => item.staffId) : [];
}

async function handleBatchRemoveStaff() {
	if (!permissionStore.currentRoleId || selectedStaffIds.value.length === 0) return;

	await ElMessageBox.confirm("确定从当前角色移除选中的人员吗？", "移除人员", { type: "warning" });

	const results = await Promise.all(
		selectedStaffIds.value.map((staffId) => permissionStore.removeStaff(staffId, permissionStore.currentRoleId!)),
	);
	const success = results.every(Boolean);

	if (!success) {
		ElMessage.error("部分人员移除失败，请检查接口配置");
		return;
	}

	selectedStaffIds.value = [];
	ElMessage.success("移除成功");
	await permissionStore.fetchStaffs(permissionStore.currentRoleId);
}

async function handleOpenPermissionDialog(role: RoleItem) {
	permissionRoleId.value = role.id;
	permissionRoleName.value = role.name;
	permissionDialogVisible.value = true;

	if (permissionStore.currentRoleId !== role.id) {
		await handleSelectRole(role.id);
	} else {
		const success = await permissionStore.fetchSelectedPermissions(role.id);
		if (!success) {
			ElMessage.error("权限数据加载失败，请检查接口配置");
		}
	}
}

function isGroupChecked(ids: number[]) {
	return ids.length > 0 && ids.every((id) => editingPermissionIds.value.includes(id));
}

function isGroupIndeterminate(ids: number[]) {
	const checkedCount = ids.filter((id) => editingPermissionIds.value.includes(id)).length;
	return checkedCount > 0 && checkedCount < ids.length;
}

function handleToggleGroup(ids: number[], value: string | number | boolean) {
	if (value) {
		editingPermissionIds.value = Array.from(new Set([...editingPermissionIds.value, ...ids]));
		return;
	}

	editingPermissionIds.value = editingPermissionIds.value.filter((id) => !ids.includes(id));
}

async function handleSavePermissions() {
	if (!permissionRoleId.value) return;

	permissionSubmitLoading.value = true;
	const success = await permissionStore.savePermissions(permissionRoleId.value, editingPermissionIds.value);
	permissionSubmitLoading.value = false;

	if (!success) {
		ElMessage.error("权限保存失败，请检查接口配置");
		return;
	}

	permissionDialogVisible.value = false;
	ElMessage.success("权限保存成功");
	await permissionStore.fetchSelectedPermissions(permissionRoleId.value);
}

async function ensureCurrentRole(preferredRoleId?: number | null) {
	const preferred = preferredRoleId ?? permissionStore.currentRoleId;
	const matchedRole = permissionStore.roles.find((item) => item.id === preferred);
	const fallbackRole = matchedRole ?? permissionStore.roles[0];

	if (!fallbackRole) {
		permissionStore.currentRoleId = null;
		permissionStore.staffs = [];
		permissionStore.permissionGroups = [];
		permissionStore.selectedPermissionIds = [];
		return true;
	}

	return permissionStore.selectRole(fallbackRole.id);
}

onMounted(async () => {
	const rolesOk = await permissionStore.fetchRoles();
	const roleDataOk = permissionStore.roles.length === 0 || (await ensureCurrentRole());

	if (!rolesOk) {
		ElMessage.error("角色列表加载失败，请检查接口配置");
	}

	if (!roleDataOk) {
		ElMessage.error("权限列表加载失败，请检查接口配置");
	}
});
</script>

<style scoped lang="scss">
.system-permission {
	height: 100%;
	padding: 8px 12px 12px;
	box-sizing: border-box;
	background: #f3f5f8;
}

.permission-shell {
	display: grid;
	grid-template-columns: minmax(560px, 1fr) minmax(620px, 1fr);
	gap: 18px;
	height: 100%;
}

.role-panel,
.staff-panel {
	display: flex;
	flex-direction: column;
	min-width: 0;
	padding: 28px 18px 16px;
	background: #fff;
	border: 1px solid #dfe6ee;
	overflow: hidden;
}

.panel-title {
	margin-bottom: 26px;
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.toolbar-row {
	display: flex;
	align-items: center;
	gap: 12px;
	margin-bottom: 14px;
}

.toolbar-row-right {
	justify-content: flex-start;
}

.primary-action {
	padding: 10px 18px;
	border-radius: 4px;
}

.role-table,
.staff-table {
	display: flex;
	flex: 1;
	flex-direction: column;
	min-height: 0;
}

.table-header,
.table-row {
	display: grid;
	align-items: center;
	min-height: 42px;
	border-bottom: 1px solid #dbe5ef;
}

.table-header {
	font-size: 14px;
	font-weight: 600;
	color: #7b8794;
}

.role-grid {
	grid-template-columns: minmax(220px, 1.3fr) minmax(180px, 1fr) minmax(240px, 1.2fr);
	column-gap: 12px;
	padding: 0 8px;
}

.staff-grid {
	grid-template-columns: 52px minmax(160px, 1fr) minmax(180px, 1fr);
	column-gap: 12px;
	padding: 0 8px;
}

.table-scroll {
	flex: 1;
	min-height: 0;
}

.role-row {
	cursor: pointer;
	transition: background-color 0.2s ease;

	&:hover {
		background: #f7fbff;
	}

	&.active {
		background: #eaf3ff;
	}
}

.row-primary,
.row-secondary {
	font-size: 15px;
	line-height: 1.45;
	color: #111827;
	word-break: break-all;
}

.row-actions {
	display: flex;
	flex-wrap: wrap;
	gap: 14px;
}

.link-button {
	padding: 0;
	border: 0;
	background: transparent;
	font-size: 15px;
	line-height: 1.4;
	color: #409eff;
	cursor: pointer;

	&.danger {
		color: #f56c6c;
	}
}

.checkbox-col {
	display: flex;
	justify-content: center;
}

.operator-tip {
	margin-top: -4px;
	padding: 0 4px 4px;
	font-size: 13px;
	line-height: 1.6;
	color: #6b7280;
}

.permission-dialog-tip {
	margin-bottom: 12px;
	padding: 12px 18px;
	border: 1px solid #edf2f7;
	border-radius: 6px;
	background: #f7f9fc;
	font-size: 15px;
	color: #98a2b3;
}

.permission-groups {
	display: flex;
	flex-direction: column;
	gap: 12px;
	padding-right: 10px;
}

.permission-group-card {
	padding: 14px 12px 16px;
	border: 1px solid #d8e1ea;
	border-radius: 6px;
	background: #fff;
	box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.9);
}

.permission-group-title {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-bottom: 12px;
	font-size: 15px;
	font-weight: 600;
	color: #4b5563;
}

.permission-check-grid {
	display: grid;
	grid-template-columns: repeat(5, minmax(0, 1fr));
	gap: 10px 12px;

	:deep(.el-checkbox) {
		margin-right: 0;
		min-width: 0;
	}

	:deep(.el-checkbox__label) {
		padding-left: 8px;
		font-size: 15px;
		line-height: 1.3;
		color: #2f86f6;
		white-space: nowrap;
		overflow: hidden;
		text-overflow: ellipsis;
	}

	:deep(.is-checked .el-checkbox__label) {
		color: #2f86f6;
	}

	:deep(.el-checkbox__inner) {
		border-radius: 2px;
	}
}

:deep(.permission-dialog) {
	border-radius: 8px;
	overflow: hidden;
}

:deep(.permission-dialog .el-dialog__header) {
	margin-right: 0;
	padding: 12px 18px;
	background: #dcecff;
	border-bottom: 1px solid #d2e2f3;
}

:deep(.permission-dialog .el-dialog__title) {
	font-size: 18px;
	font-weight: 500;
	color: #374151;
}

:deep(.permission-dialog .el-dialog__headerbtn) {
	top: 14px;
	right: 18px;
}

:deep(.permission-dialog .el-dialog__body) {
	padding: 16px 18px 12px;
	background: #fff;
}

:deep(.permission-dialog .el-dialog__footer) {
	padding: 12px 18px 16px;
	border-top: 1px solid #edf2f7;
	background: #fff;
}

@media (max-width: 1360px) {
	.permission-shell {
		grid-template-columns: 1fr;
		height: auto;
	}

	.role-panel,
	.staff-panel {
		min-height: 420px;
	}
}

@media (max-width: 960px) {
	.system-permission {
		padding: 8px;
	}

	.role-grid,
	.staff-grid,
	.permission-check-grid {
		grid-template-columns: 1fr;
	}

	.table-header {
		display: none;
	}

	.table-row {
		padding: 12px 8px;
	}

	.row-actions {
		padding-top: 4px;
	}
}
</style>
