import { defineStore } from "pinia";
import { ref } from "vue";
import {
	addRolepermStaff,
	deleteRoleperm,
	getRolepermNameList,
	getRolepermOperators,
	getRolepermStaffList,
	getSelectedPermissionList,
	removeRolepermStaff,
	saveRolePermission,
	saveRoleperm,
} from "@/apis/system/permission";
import type {
	QuanXianFenZuVo,
	QuanXianMiaoShuDuiXiang,
	RolepermDTO,
	RolepermOperatorDTO,
	RolepermStaffDTO,
} from "@/apis/system/permission/type";

export interface RoleItem {
	id: number;
	code: string;
	name: string;
}

export interface StaffItem {
	staffId: number;
	roleId: number;
	name: string;
	mobile: string;
}

export interface OperatorItem {
	id: number;
	name: string;
	positionName: string;
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
		const source = data as { rows?: T[]; list?: T[]; groupList?: T[] };
		const rows = source.rows ?? source.list ?? source.groupList;
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

function normalizeOperators(rows: RolepermOperatorDTO[]): OperatorItem[] {
	return rows.map((item) => ({
		id: item.id ?? 0,
		name: item.name ?? "",
		positionName: item.positionName ?? "",
	}));
}

function extractPermissionState(input: unknown) {
	const groups = extractRows<QuanXianFenZuVo>(unwrapPayload(input));
	const ids: number[] = [];

	for (const group of groups) {
		for (const perm of group.selectedPermissions ?? []) {
			if (perm.id != null) ids.push(perm.id);
		}
	}

	return {
		groups,
		ids: Array.from(new Set(ids)),
	};
}

export const useSystemPermissionStore = defineStore("systemPermission", () => {
	const roles = ref<RoleItem[]>([]);
	const currentRoleId = ref<number | null>(null);
	const staffs = ref<StaffItem[]>([]);
	const operators = ref<OperatorItem[]>([]);
	const permissionGroups = ref<QuanXianFenZuVo[]>([]);
	const selectedPermissionIds = ref<number[]>([]);

	const rolesLoading = ref(false);
	const staffsLoading = ref(false);
	const operatorsLoading = ref(false);
	const permissionsLoading = ref(false);

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
			permissionGroups.value = [];
			selectedPermissionIds.value = [];
			return false;
		} finally {
			rolesLoading.value = false;
		}
	}

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

	async function fetchOperators(name = "") {
		operatorsLoading.value = true;
		try {
			const res = await getRolepermOperators({ name: name || undefined, pageIndex: 1, pageSize: 50 });
			operators.value = normalizeOperators(extractRows<RolepermOperatorDTO>(unwrapPayload(res)));
			return true;
		} catch (error) {
			const rows = extractRows<RolepermOperatorDTO>(unwrapPayload(error));
			if (rows.length > 0 || hasServerPayload(error)) {
				operators.value = normalizeOperators(rows);
				return true;
			}

			operators.value = [];
			return false;
		} finally {
			operatorsLoading.value = false;
		}
	}

	async function fetchSelectedPermissions(roleId: number) {
		permissionsLoading.value = true;
		try {
			const state = extractPermissionState(await getSelectedPermissionList(roleId));
			permissionGroups.value = state.groups;
			selectedPermissionIds.value = state.ids;
			return true;
		} catch (error) {
			const state = extractPermissionState(error);
			permissionGroups.value = state.groups;
			selectedPermissionIds.value = state.ids;
			return state.groups.length > 0 || hasServerPayload(error);
		} finally {
			permissionsLoading.value = false;
		}
	}

	async function selectRole(roleId: number) {
		currentRoleId.value = roleId;
		const [staffsOk, permsOk] = await Promise.all([fetchStaffs(roleId), fetchSelectedPermissions(roleId)]);
		return staffsOk && permsOk;
	}

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

	async function savePermissions(roleId: number, permissionIds: number[]) {
		try {
			const allPerms: QuanXianMiaoShuDuiXiang[] = [];
			for (const group of permissionGroups.value) {
				if (group.permissions) {
					allPerms.push(...group.permissions);
				}
			}

			const selectedPerms = allPerms.filter((item) => item.id != null && permissionIds.includes(item.id));
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
		operators,
		permissionGroups,
		selectedPermissionIds,
		rolesLoading,
		staffsLoading,
		operatorsLoading,
		permissionsLoading,
		fetchRoles,
		fetchStaffs,
		fetchOperators,
		fetchSelectedPermissions,
		selectRole,
		saveRole,
		removeRole,
		addStaff,
		removeStaff,
		savePermissions,
	};
});
