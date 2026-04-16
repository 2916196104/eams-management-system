<template>
	<section class="role-page">
		<section class="panel-card role-list">
			<div class="role-list__header">
				<div class="role-list__title">{{ config.titles.list }}</div>
				<el-button type="primary" :icon="Plus" @click="openRoleDialog()">{{ config.titles.addRole }}</el-button>
			</div>

			<el-table
				:data="roles"
				border
				highlight-current-row
				row-key="id"
				:current-row-key="selectedRole?.id"
				@current-change="handleRoleChange"
			>
				<el-table-column prop="name" label="角色名称" min-width="180" />
				<el-table-column prop="code" label="角色编码" min-width="180" />
				<el-table-column label="操作" width="220" align="center">
					<template #default="{ row }">
						<el-button link type="primary" @click="handleRoleChange(row)">管理权限</el-button>
						<el-button link type="primary" @click="openRoleDialog(row)">编辑</el-button>
						<el-button link type="danger" @click="removeRole(row.id)">删除</el-button>
					</template>
				</el-table-column>
			</el-table>
		</section>

		<section class="panel-card role-detail">
			<div v-if="selectedRole" class="role-detail__inner">
				<div class="role-detail__section-header">
					<div class="role-detail__title">{{ config.titles.memberSection }}</div>
					<el-button size="small" type="primary" @click="openMemberDialog">{{ config.titles.addMember }}</el-button>
				</div>
				<div class="role-detail__name">{{ selectedRole.name }}</div>
				<div v-if="selectedRole.members.length" class="role-detail__members">
					<el-tag
						v-for="member in selectedRole.members"
						:key="member.staffId"
						class="role-detail__tag"
						closable
						@close="removeMember(member.staffId)"
					>
						{{ member.name }}
					</el-tag>
				</div>
				<div v-else class="role-detail__member-empty">{{ config.titles.memberEmpty }}</div>

				<div class="role-detail__subtitle">{{ config.titles.permissionSection }}</div>
				<el-tree
					ref="treeRef"
					node-key="id"
					show-checkbox
					default-expand-all
					:data="permissionTree"
					:props="{ label: 'label', children: 'children' }"
					@check="handlePermissionChange"
				/>
			</div>
			<div v-else class="role-detail__empty">{{ config.titles.empty }}</div>
		</section>

		<el-dialog
			v-model="roleDialogVisible"
			:title="roleForm.id ? config.titles.editDialog : config.titles.createDialog"
			width="520px"
		>
			<el-form label-width="96px">
				<el-form-item v-for="field in config.formFields" :key="field.prop" :label="field.label">
					<el-input v-if="field.type !== 'textarea'" v-model="roleForm[field.prop]" />
					<el-input v-else v-model="roleForm[field.prop]" type="textarea" :rows="field.rows || 3" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="roleDialogVisible = false">取消</el-button>
				<el-button type="primary" @click="submitRole">保存</el-button>
			</template>
		</el-dialog>

		<el-dialog v-model="memberDialogVisible" :title="config.titles.addMember" width="420px">
			<el-form label-width="96px">
				<el-form-item label="员工ID">
					<el-input v-model="memberForm.staffId" placeholder="请输入员工ID" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="memberDialogVisible = false">取消</el-button>
				<el-button type="primary" @click="submitMember">保存</el-button>
			</template>
		</el-dialog>
	</section>
</template>

<script setup lang="ts">
import { computed, nextTick, onMounted, reactive, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Plus } from "@element-plus/icons-vue";
import type { PermissionDTO, PermissionNode, RoleRecord } from "@/apis/system/type";
import type { SystemRolePermissionPageConfig } from "../shared";

type TreeRef = {
	setCheckedKeys: (keys: string[]) => void;
	getCheckedKeys: (leafOnly?: boolean) => Array<string | number>;
};

const props = defineProps<{
	config: SystemRolePermissionPageConfig;
}>();

const roles = ref<RoleRecord[]>([]);
const permissionTree = ref<PermissionNode[]>([]);
const permissionMap = ref<Record<string, PermissionDTO>>({});
const selectedRoleId = ref("");
const treeRef = ref<TreeRef | null>(null);
const roleDialogVisible = ref(false);
const memberDialogVisible = ref(false);
const roleForm = reactive<Record<string, string | undefined>>({
	id: undefined,
	name: "",
	code: "",
});
const memberForm = reactive({
	staffId: "",
});

const selectedRole = computed(() => roles.value.find((item) => item.id === selectedRoleId.value));

async function loadRoles(preferredRoleId?: string) {
	roles.value = await props.config.loadRoles();
	const nextRoleId =
		preferredRoleId && roles.value.some((item) => item.id === preferredRoleId)
			? preferredRoleId
			: roles.value[0]?.id || "";
	selectedRoleId.value = nextRoleId;
	await Promise.all([loadPermissionTree(nextRoleId), loadRoleMembers(nextRoleId)]);
}

async function loadPermissionTree(roleId = selectedRoleId.value) {
	if (!roleId) {
		permissionTree.value = [];
		permissionMap.value = {};
		await syncTreeChecked([]);
		return;
	}

	const data = await props.config.loadPermissionTree(roleId);
	permissionTree.value = data.tree;
	permissionMap.value = data.permissionMap;
	if (selectedRole.value) selectedRole.value.permissionIds = [...data.checkedKeys];
	await syncTreeChecked(data.checkedKeys);
}

async function loadRoleMembers(roleId = selectedRoleId.value) {
	if (!roleId || !selectedRole.value) return;
	const members = await props.config.loadRoleMembers(roleId);
	selectedRole.value.members = members;
	selectedRole.value.memberCount = members.length;
}

async function syncTreeChecked(keys: string[]) {
	await nextTick();
	treeRef.value?.setCheckedKeys(keys);
}

async function handleRoleChange(row?: RoleRecord) {
	selectedRoleId.value = row?.id || "";
	await Promise.all([loadPermissionTree(selectedRoleId.value), loadRoleMembers(selectedRoleId.value)]);
}

function openRoleDialog(row?: RoleRecord) {
	roleForm.id = row?.id;
	roleForm.name = row?.name || "";
	roleForm.code = row?.code || "";
	roleDialogVisible.value = true;
}

function openMemberDialog() {
	memberForm.staffId = "";
	memberDialogVisible.value = true;
}

async function submitRole() {
	const name = String(roleForm.name || "").trim();
	const code = String(roleForm.code || "").trim();
	if (!name || !code) {
		ElMessage.warning("请填写角色名称和角色编码");
		return;
	}

	const isEdit = Boolean(roleForm.id);
	const saved = await props.config.saveRole({
		id: roleForm.id,
		name,
		code,
	});

	roleDialogVisible.value = false;
	await loadRoles(saved.id);
	ElMessage.success(isEdit ? "角色已更新" : "角色已创建");
}

async function submitMember() {
	const roleId = selectedRole.value?.id;
	const staffId = String(memberForm.staffId || "").trim();
	if (!roleId) return;
	if (!staffId) {
		ElMessage.warning("请输入员工ID");
		return;
	}
	if (!/^\d+$/.test(staffId)) {
		ElMessage.warning("员工ID必须是数字");
		return;
	}

	await props.config.addRoleMember(roleId, staffId);
	memberDialogVisible.value = false;
	await loadRoleMembers(roleId);
	ElMessage.success("员工已加入角色");
}

async function removeRole(id: string) {
	await ElMessageBox.confirm("确认删除该角色吗？", "提示", {
		type: "warning",
		confirmButtonText: "删除",
		cancelButtonText: "取消",
	});
	const nextPreferredId = selectedRoleId.value === id ? undefined : selectedRoleId.value;
	await props.config.deleteRole(id);
	await loadRoles(nextPreferredId);
	ElMessage.success("角色已删除");
}

async function removeMember(staffId: number) {
	if (!selectedRole.value) return;
	await props.config.removeRoleMember(selectedRole.value.id, String(staffId));
	await loadRoleMembers(selectedRole.value.id);
	ElMessage.success("员工已移出角色");
}

async function handlePermissionChange() {
	if (!selectedRole.value) return;
	const checkedKeys = (treeRef.value?.getCheckedKeys(false) || [])
		.map((item) => String(item))
		.filter((key) => Boolean(permissionMap.value[key]));
	const permissions = checkedKeys.map((key) => permissionMap.value[key]).filter(Boolean);

	selectedRole.value.permissionIds = checkedKeys;
	await props.config.updateRolePermissions(selectedRole.value.id, permissions);
	ElMessage.success("权限已更新");
}

onMounted(() => {
	loadRoles();
});
</script>

<style scoped>
.role-page {
	margin: 16px;
	display: grid;
	grid-template-columns: minmax(520px, 1.05fr) minmax(360px, 1fr);
	gap: 16px;
}

.panel-card {
	padding: 18px;
	background: #ffffff;
	border: 1px solid #edf0f5;
	box-shadow: 0 1px 2px rgb(31 45 61 / 4%);
}

.role-list__header,
.role-detail__section-header {
	margin-bottom: 16px;
	display: flex;
	align-items: center;
	justify-content: space-between;
}

.role-list__title,
.role-detail__title,
.role-detail__subtitle {
	font-size: 16px;
	font-weight: 700;
	color: #2f3c55;
}

.role-detail__inner {
	min-height: 520px;
}

.role-detail__name {
	margin: 18px 0 14px;
	font-size: 34px;
	font-weight: 700;
	color: #1f2d3d;
}

.role-detail__members {
	display: flex;
	flex-wrap: wrap;
	gap: 10px;
	margin-bottom: 24px;
}

.role-detail__tag {
	margin-right: 0;
}

.role-detail__member-empty {
	margin-bottom: 24px;
	color: #7d8aa5;
}

.role-detail__subtitle {
	margin-bottom: 12px;
}

.role-detail__empty {
	min-height: 520px;
	display: flex;
	align-items: center;
	justify-content: center;
	font-size: 18px;
	color: #7d8aa5;
}
</style>
