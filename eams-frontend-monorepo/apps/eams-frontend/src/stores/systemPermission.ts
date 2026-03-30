import { defineStore } from "pinia";
import { ref } from "vue";
import {
	getRolepermNameList,
	saveRoleperm,
	deleteRoleperm,
	getRolepermStaffList,
	addRolepermStaff,
	removeRolepermStaff,
	getPermissionList,
	getSelectedPermissionList,
	saveRolePermission,
} from "@/apis/system/permission";
import type {
	RolepermDTO,
	RolepermStaffDTO,
	QuanXianFenZuVo,
	QuanXianMiaoShuDuiXiang,
} from "@/apis/system/permission/type";

/** 角色信息（页面展示用） */
export interface RoleItem {
	id: number;
	code: string;
	name: string;
}

/** 角色员工（页面展示用） */
export interface StaffItem {
	staffId: number;
	roleId: number;
	name: string;
	mobile: string;
}

function unwrapPayload(input: unknown): unknown {
	let current = input;

	while (current && typeof current === "object" && "data" in (current as Record<string, unknown>)) {
		const next = (current as { data?: unknown }).data;
		if (next === undefined || next === current) {
			break;
		}
		current = next;
	}

	return current;
}

function hasServerPayload(input: unknown) {
	return Boolean(
		input &&
		typeof input === "object" &&
		("data" in (input as Record<string, unknown>) || "status" in (input as Record<string, unknown>)),
	);
}

function extractRows<T>(data: unknown): T[] {
	if (Array.isArray(data)) {
		return data;
	}

	if (data && typeof data === "object") {
		const source = data as { rows?: T[]; list?: T[] };
		const rows = source.rows ?? source.list;
		return Array.isArray(rows) ? rows : [];
	}

	return [];
}

function normalizeRoles(rows: RolepermDTO[]): RoleItem[] {
	return rows.map((item) => ({
		id: item.id ?? 0,
		code: item.code ?? "",
		name: item.name ?? "",
	}));
}

function normalizeStaffs(rows: RolepermStaffDTO[], roleId: number): StaffItem[] {
	return rows.map((item) => ({
		staffId: item.staffId ?? 0,
		roleId: item.roleId ?? roleId,
		name: item.name ?? "",
		mobile: item.mobile ?? "",
	}));
}

export const useSystemPermissionStore = defineStore("systemPermission", () => {
	/** 角色列表 */
	const roles = ref<RoleItem[]>([]);
	/** 当前选中的角色 ID */
	const currentRoleId = ref<number | null>(null);
	/** 当前角色的员工列表 */
	const staffs = ref<StaffItem[]>([]);
	/** 可分配的权限分组 */
	const permissionGroups = ref<QuanXianFenZuVo[]>([]);
	/** 当前角色已选中的权限 ID 列表 */
	const selectedPermissionIds = ref<number[]>([]);
	/** 角色加载状态 */
	const rolesLoading = ref(false);
	/** 员工加载状态 */
	const staffsLoading = ref(false);
	/** 权限加载状态 */
	const permissionsLoading = ref(false);

	/** 获取角色列表 */
	async function fetchRoles() {
		rolesLoading.value = true;
		try {
			const res = await getRolepermNameList();
			roles.value = normalizeRoles(extractRows<RolepermDTO>(unwrapPayload(res)));
			return true;
		} catch (error) {
			const rows = extractRows<RolepermDTO>(unwrapPayload(error));
			if (rows.length > 0 || hasServerPayload(error)) {
				roles.value = normalizeRoles(rows);
				return true;
			}

			roles.value = [];
			currentRoleId.value = null;
			staffs.value = [];
			selectedPermissionIds.value = [];
			return false;
		} finally {
			rolesLoading.value = false;
		}
	}

	/** 获取角色员工列表 */
	async function fetchStaffs(roleId: number) {
		staffsLoading.value = true;
		try {
			const res = await getRolepermStaffList({ roleId, pageIndex: 1, pageSize: 1000 });
			staffs.value = normalizeStaffs(extractRows<RolepermStaffDTO>(unwrapPayload(res)), roleId);
			return true;
		} catch (error) {
			const rows = extractRows<RolepermStaffDTO>(unwrapPayload(error));
			if (rows.length > 0 || hasServerPayload(error)) {
				staffs.value = normalizeStaffs(rows, roleId);
				return true;
			}

			staffs.value = [];
			return false;
		} finally {
			staffsLoading.value = false;
		}
	}

	/** 获取权限列表 */
	async function fetchPermissions() {
		permissionsLoading.value = true;
		try {
			const res = await getPermissionList();
			permissionGroups.value = extractRows<QuanXianFenZuVo>(unwrapPayload(res));
			return true;
		} catch (error) {
			const rows = extractRows<QuanXianFenZuVo>(unwrapPayload(error));
			permissionGroups.value = rows;
			return rows.length > 0 || hasServerPayload(error);
		} finally {
			permissionsLoading.value = false;
		}
	}

	/** 获取已选中的权限 */
	async function fetchSelectedPermissions(roleId: number) {
		try {
			const res = await getSelectedPermissionList(roleId);
			const groups = extractRows<QuanXianFenZuVo>(unwrapPayload(res));
			const ids: number[] = [];
			for (const group of groups) {
				if (group.selectedPermissions) {
					for (const perm of group.selectedPermissions) {
						if (perm.id != null) ids.push(perm.id);
					}
				}
			}
			selectedPermissionIds.value = ids;
			return true;
		} catch (error) {
			const groups = extractRows<QuanXianFenZuVo>(unwrapPayload(error));
			const ids: number[] = [];
			for (const group of groups) {
				if (group.selectedPermissions) {
					for (const perm of group.selectedPermissions) {
						if (perm.id != null) ids.push(perm.id);
					}
				}
			}
			selectedPermissionIds.value = ids;
			return groups.length > 0 || hasServerPayload(error);
		}
	}

	/** 选中角色 */
	async function selectRole(roleId: number) {
		currentRoleId.value = roleId;
		const [staffsOk, permsOk] = await Promise.all([fetchStaffs(roleId), fetchSelectedPermissions(roleId)]);
		return staffsOk && permsOk;
	}

	/** 保存角色 */
	async function saveRole(data: RoleItem) {
		try {
			await saveRoleperm({ id: data.id || undefined, code: data.code, name: data.name });
			await fetchRoles();
			return true;
		} catch (error) {
			if (!hasServerPayload(error)) {
				return false;
			}

			return fetchRoles();
		}
	}

	/** 删除角色 */
	async function removeRole(id: number) {
		try {
			await deleteRoleperm(id);
			await fetchRoles();
			return true;
		} catch (error) {
			if (!hasServerPayload(error)) {
				return false;
			}

			return fetchRoles();
		}
	}

	/** 添加员工到角色 */
	async function addStaff(data: RolepermStaffDTO) {
		try {
			await addRolepermStaff(data);
			await fetchStaffs(data.roleId!);
			return true;
		} catch (error) {
			if (!hasServerPayload(error)) {
				return false;
			}

			return fetchStaffs(data.roleId!);
		}
	}

	/** 从角色移除员工 */
	async function removeStaff(staffId: number, roleId: number) {
		try {
			await removeRolepermStaff(staffId, roleId);
			await fetchStaffs(roleId);
			return true;
		} catch (error) {
			if (!hasServerPayload(error)) {
				return false;
			}

			return fetchStaffs(roleId);
		}
	}

	/** 保存角色权限分配 */
	async function savePermissions(roleId: number, permissionIds: number[]) {
		try {
			const allPerms: QuanXianMiaoShuDuiXiang[] = [];
			for (const group of permissionGroups.value) {
				if (group.permissions) {
					allPerms.push(...group.permissions);
				}
			}
			const selectedPerms = allPerms.filter((p) => permissionIds.includes(p.id!));
			await saveRolePermission(roleId, selectedPerms);
			await fetchSelectedPermissions(roleId);
			return true;
		} catch (error) {
			if (!hasServerPayload(error)) {
				return false;
			}

			return fetchSelectedPermissions(roleId);
		}
	}

	return {
		roles,
		currentRoleId,
		staffs,
		permissionGroups,
		selectedPermissionIds,
		rolesLoading,
		staffsLoading,
		permissionsLoading,
		fetchRoles,
		fetchStaffs,
		fetchPermissions,
		fetchSelectedPermissions,
		selectRole,
		saveRole,
		removeRole,
		addStaff,
		removeStaff,
		savePermissions,
	};
});
