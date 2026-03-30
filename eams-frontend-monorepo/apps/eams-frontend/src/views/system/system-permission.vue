<template>
	<div class="system-permission">
		<!-- 主体内容：左右分栏 -->
		<div class="permission-layout">
			<!-- 左侧：角色列表 -->
			<div class="role-panel">
				<div class="panel-header">
					<span>角色列表</span>
					<el-button type="primary" size="small" :icon="Plus" @click="handleAddRole">新增角色</el-button>
				</div>
				<el-scrollbar v-loading="permissionStore.rolesLoading">
					<div class="role-list">
						<div
							v-for="role in permissionStore.roles"
							:key="role.id"
							class="role-card"
							:class="{ active: permissionStore.currentRoleId === role.id }"
							@click="handleSelectRole(role.id)"
						>
							<div class="role-info">
								<div class="role-name">{{ role.name }}</div>
								<div class="role-code">{{ role.code }}</div>
							</div>
							<div class="role-actions">
								<el-button type="primary" link size="small" @click.stop="handleEditRole(role)">编辑</el-button>
								<el-popconfirm title="确定删除该角色？" @confirm="handleDeleteRole(role.id)">
									<template #reference>
										<el-button type="danger" link size="small" @click.stop>删除</el-button>
									</template>
								</el-popconfirm>
							</div>
						</div>
						<el-empty v-if="permissionStore.roles.length === 0" description="暂无角色" :image-size="60" />
					</div>
				</el-scrollbar>
			</div>

			<!-- 右侧：员工管理 + 权限分配 -->
			<div class="right-panel">
				<template v-if="permissionStore.currentRoleId">
					<!-- 员工管理 -->
					<div class="staff-section">
						<div class="section-header">
							<span>{{ currentRoleName }} - 员工管理</span>
							<el-button type="primary" size="small" :icon="Plus" @click="handleAddStaff">添加员工</el-button>
						</div>
						<el-scrollbar v-loading="permissionStore.staffsLoading">
							<div class="staff-list">
								<el-table :data="permissionStore.staffs" border stripe style="width: 100%">
									<el-table-column prop="name" label="姓名" width="120" />
									<el-table-column prop="mobile" label="手机号" min-width="140" />
									<el-table-column label="操作" width="80">
										<template #default="{ row }">
											<el-popconfirm title="确定移除该员工？" @confirm="handleRemoveStaff(row.staffId)">
												<template #reference>
													<el-button type="danger" link size="small">移除</el-button>
												</template>
											</el-popconfirm>
										</template>
									</el-table-column>
								</el-table>
								<el-empty v-if="permissionStore.staffs.length === 0" description="暂无员工" :image-size="60" />
							</div>
						</el-scrollbar>
					</div>

					<!-- 权限分配 -->
					<div class="permission-section">
						<div class="section-header">
							<span>{{ currentRoleName }} - 权限分配</span>
							<el-button type="primary" size="small" @click="handleSavePermissions">保存权限</el-button>
						</div>
						<el-scrollbar v-loading="permissionStore.permissionsLoading">
							<div class="permission-tree">
								<el-tree
									ref="permissionTreeRef"
									:data="treeData"
									show-checkbox
									node-key="id"
									:default-checked-keys="permissionStore.selectedPermissionIds"
									:props="{ label: 'name', children: 'children' }"
								/>
							</div>
						</el-scrollbar>
					</div>
				</template>
				<el-empty v-else description="请先选择一个角色" class="empty-placeholder" />
			</div>
		</div>

		<!-- 新增/编辑角色弹窗 -->
		<el-dialog v-model="roleDialogVisible" :title="roleDialogTitle" width="400px" destroy-on-close>
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

		<!-- 添加员工弹窗 -->
		<el-dialog v-model="staffDialogVisible" title="添加员工" width="400px" destroy-on-close>
			<el-form ref="staffFormRef" :model="staffForm" :rules="staffFormRules" label-width="80px">
				<el-form-item label="员工姓名" prop="name">
					<el-input v-model="staffForm.name" placeholder="请输入员工姓名" />
				</el-form-item>
				<el-form-item label="手机号" prop="mobile">
					<el-input v-model="staffForm.mobile" placeholder="请输入手机号" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="staffDialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="submitLoading" @click="handleStaffSubmit">确定</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, computed, onMounted, nextTick } from "vue";
import { ElMessage, type FormInstance, type TreeInstance } from "element-plus";
import { Plus } from "@element-plus/icons-vue";
import { useSystemPermissionStore, type RoleItem } from "@/stores/systemPermission";

const permissionStore = useSystemPermissionStore();

// ==================== 当前角色 ====================

const currentRoleName = computed(() => {
	const current = permissionStore.roles.find((item) => item.id === permissionStore.currentRoleId);
	return current?.name ?? "未选择";
});

// ==================== 权限树 ====================

const permissionTreeRef = ref<TreeInstance>();

const treeData = computed(() => {
	return permissionStore.permissionGroups.map((group) => ({
		id: `group-${group.groupName}`,
		name: group.groupName,
		children: (group.permissions || []).map((perm) => ({
			id: perm.id,
			name: perm.name,
			code: perm.code,
		})),
	}));
});

// ==================== 角色弹窗 ====================

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

// ==================== 员工弹窗 ====================

const staffDialogVisible = ref(false);
const staffFormRef = ref<FormInstance>();
const staffForm = reactive({
	name: "",
	mobile: "",
});

const staffFormRules = {
	name: [{ required: true, message: "请输入员工姓名", trigger: "blur" }],
	mobile: [
		{ required: true, message: "请输入手机号", trigger: "blur" },
		{ pattern: /^1\d{10}$/, message: "请输入正确的手机号", trigger: "blur" },
	],
};

// ==================== 角色操作 ====================

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
	if (success) {
		ElMessage.success(roleForm.id === 0 ? "新增成功" : "修改成功");
		roleDialogVisible.value = false;
	}
}

async function handleDeleteRole(id: number) {
	const success = await permissionStore.removeRole(id);
	if (success) {
		ElMessage.success("删除成功");
	}
}

function handleSelectRole(roleId: number) {
	permissionStore.selectRole(roleId);
}

// ==================== 员工操作 ====================

function handleAddStaff() {
	staffForm.name = "";
	staffForm.mobile = "";
	staffDialogVisible.value = true;
}

async function handleStaffSubmit() {
	await staffFormRef.value?.validate();
	if (!permissionStore.currentRoleId) return;
	submitLoading.value = true;
	const success = await permissionStore.addStaff({
		roleId: permissionStore.currentRoleId,
		name: staffForm.name,
		mobile: staffForm.mobile,
	});
	submitLoading.value = false;
	if (success) {
		ElMessage.success("添加成功");
		staffDialogVisible.value = false;
	}
}

async function handleRemoveStaff(staffId: number) {
	if (!permissionStore.currentRoleId) return;
	const success = await permissionStore.removeStaff(staffId, permissionStore.currentRoleId);
	if (success) {
		ElMessage.success("移除成功");
	}
}

// ==================== 权限操作 ====================

async function handleSavePermissions() {
	if (!permissionStore.currentRoleId) return;
	const checkedKeys = permissionTreeRef.value?.getCheckedKeys() || [];
	const halfCheckedKeys = permissionTreeRef.value?.getHalfCheckedKeys() || [];
	const allKeys = [...(checkedKeys as number[]), ...(halfCheckedKeys as number[])].filter(
		(key) => typeof key === "number",
	);
	const success = await permissionStore.savePermissions(permissionStore.currentRoleId, allKeys);
	if (success) {
		ElMessage.success("权限保存成功");
	}
}

// ==================== 生命周期 ====================

onMounted(async () => {
	await permissionStore.fetchRoles();
	await permissionStore.fetchPermissions();
});
</script>

<style scoped lang="scss">
.system-permission {
	padding: 16px;
	height: 100%;
	display: flex;
	flex-direction: column;
}

.permission-layout {
	flex: 1;
	display: flex;
	gap: 16px;
	min-height: 0;
}

.role-panel {
	width: 260px;
	flex-shrink: 0;
	display: flex;
	flex-direction: column;
	border: 1px solid var(--el-border-color-light);
	border-radius: 8px;
	overflow: hidden;
}

.panel-header {
	padding: 12px 16px;
	font-weight: 600;
	font-size: 15px;
	border-bottom: 1px solid var(--el-border-color-light);
	background-color: var(--el-fill-color-light);
	display: flex;
	justify-content: space-between;
	align-items: center;
}

.role-list {
	padding: 8px;
}

.role-card {
	padding: 12px;
	border-radius: 6px;
	cursor: pointer;
	transition: all 0.2s;
	margin-bottom: 4px;
	display: flex;
	justify-content: space-between;
	align-items: center;

	&:hover {
		background-color: var(--el-fill-color-light);
	}

	&.active {
		background-color: var(--el-color-primary-light-9);
		border-left: 3px solid var(--el-color-primary);
	}

	.role-info {
		flex: 1;
		min-width: 0;
	}

	.role-name {
		font-weight: 500;
		font-size: 14px;
		margin-bottom: 4px;
	}

	.role-code {
		font-size: 12px;
		color: var(--el-text-color-secondary);
		font-family: monospace;
	}

	.role-actions {
		display: flex;
		gap: 4px;
		flex-shrink: 0;
	}
}

.right-panel {
	flex: 1;
	min-width: 0;
	display: flex;
	flex-direction: column;
	gap: 16px;
}

.staff-section,
.permission-section {
	flex: 1;
	min-height: 0;
	display: flex;
	flex-direction: column;
	border: 1px solid var(--el-border-color-light);
	border-radius: 8px;
	overflow: hidden;
}

.section-header {
	padding: 12px 16px;
	font-weight: 600;
	font-size: 15px;
	border-bottom: 1px solid var(--el-border-color-light);
	background-color: var(--el-fill-color-light);
	display: flex;
	justify-content: space-between;
	align-items: center;
}

.staff-list,
.permission-tree {
	padding: 16px;
	flex: 1;
}

.empty-placeholder {
	flex: 1;
	display: flex;
	align-items: center;
	justify-content: center;
}
</style>
