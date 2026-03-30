import { defineStore } from "pinia";
import { ref } from "vue";
import {
	getRolepermPage,
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

const mockRoles: RoleItem[] = [
	{ id: 1, code: "admin", name: "管理员" },
	{ id: 2, code: "teacher", name: "教师" },
	{ id: 3, code: "student", name: "学生" },
	{ id: 4, code: "operator", name: "运营" },
];

const mockStaffs: Record<number, StaffItem[]> = {
	1: [
		{ staffId: 101, roleId: 1, name: "张三", mobile: "13800001111" },
		{ staffId: 102, roleId: 1, name: "李四", mobile: "13800002222" },
	],
	2: [{ staffId: 201, roleId: 2, name: "王老师", mobile: "13800003333" }],
	3: [],
	4: [{ staffId: 401, roleId: 4, name: "赵运营", mobile: "13800004444" }],
};

const mockPermissions: QuanXianFenZuVo[] = [
	{
		groupName: "系统管理",
		permissions: [
			{
				id: 1,
				code: "system:notice",
				name: "内部公告",
				groupName: "系统管理",
				path: "/system/internal-notice",
				enabled: 1,
			},
			{
				id: 2,
				code: "system:dict",
				name: "数据字典",
				groupName: "系统管理",
				path: "/system/data-dictionary",
				enabled: 1,
			},
			{
				id: 3,
				code: "system:param",
				name: "系统参数",
				groupName: "系统管理",
				path: "/system/system-parameter",
				enabled: 1,
			},
			{
				id: 4,
				code: "system:permission",
				name: "角色与权限",
				groupName: "系统管理",
				path: "/system/permission",
				enabled: 1,
			},
		],
		selectedPermissions: [],
	},
	{
		groupName: "教务管理",
		permissions: [
			{ id: 10, code: "edu:course", name: "课程管理", groupName: "教务管理", path: "/edu/course", enabled: 1 },
			{ id: 11, code: "edu:student", name: "学员管理", groupName: "教务管理", path: "/edu/student", enabled: 1 },
		],
		selectedPermissions: [],
	},
];

let localMockRoles = [...mockRoles];
let localMockStaffs = JSON.parse(JSON.stringify(mockStaffs)) as Record<number, StaffItem[]>;
let localMockSelectedPermissions: Record<number, number[]> = {
	1: [1, 2, 3, 4, 10, 11],
	2: [10, 11],
	3: [],
	4: [1, 2],
};

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
			const data = (res as any).data ?? res;
			const rows: RolepermDTO[] = Array.isArray(data) ? data : data.rows || data.list || [];
			roles.value = rows.map((item) => ({
				id: item.id ?? 0,
				code: item.code ?? "",
				name: item.name ?? "",
			}));
		} catch {
			roles.value = [...localMockRoles];
		} finally {
			rolesLoading.value = false;
		}
	}

	/** 获取角色员工列表 */
	async function fetchStaffs(roleId: number) {
		staffsLoading.value = true;
		try {
			const res = await getRolepermStaffList({ roleId, pageIndex: 1, pageSize: 1000 });
			const data = (res as any).data ?? res;
			const rows: RolepermStaffDTO[] = data.rows || data.list || (Array.isArray(data) ? data : []);
			staffs.value = rows.map((item) => ({
				staffId: item.staffId ?? 0,
				roleId: item.roleId ?? roleId,
				name: item.name ?? "",
				mobile: item.mobile ?? "",
			}));
		} catch {
			staffs.value = localMockStaffs[roleId] ? [...localMockStaffs[roleId]] : [];
		} finally {
			staffsLoading.value = false;
		}
	}

	/** 获取权限列表 */
	async function fetchPermissions() {
		permissionsLoading.value = true;
		try {
			const res = await getPermissionList();
			const data = (res as any).data ?? res;
			permissionGroups.value = Array.isArray(data) ? data : data.rows || data.list || [];
		} catch {
			permissionGroups.value = JSON.parse(JSON.stringify(mockPermissions));
		} finally {
			permissionsLoading.value = false;
		}
	}

	/** 获取已选中的权限 */
	async function fetchSelectedPermissions(roleId: number) {
		try {
			const res = await getSelectedPermissionList(roleId);
			const data = (res as any).data ?? res;
			const groups: QuanXianFenZuVo[] = Array.isArray(data) ? data : data.rows || data.list || [];
			const ids: number[] = [];
			for (const group of groups) {
				if (group.selectedPermissions) {
					for (const perm of group.selectedPermissions) {
						if (perm.id != null) ids.push(perm.id);
					}
				}
			}
			selectedPermissionIds.value = ids;
		} catch {
			selectedPermissionIds.value = localMockSelectedPermissions[roleId]
				? [...localMockSelectedPermissions[roleId]]
				: [];
		}
	}

	/** 选中角色 */
	async function selectRole(roleId: number) {
		currentRoleId.value = roleId;
		await Promise.all([fetchStaffs(roleId), fetchSelectedPermissions(roleId)]);
	}

	/** 保存角色 */
	async function saveRole(data: RoleItem) {
		try {
			await saveRoleperm({ id: data.id || undefined, code: data.code, name: data.name });
			await fetchRoles();
			return true;
		} catch {
			if (data.id) {
				const idx = localMockRoles.findIndex((item) => item.id === data.id);
				if (idx !== -1) {
					localMockRoles[idx] = { ...data };
				}
			} else {
				const newId = localMockRoles.length > 0 ? Math.max(...localMockRoles.map((r) => r.id)) + 1 : 1;
				localMockRoles.push({ ...data, id: newId });
			}
			await fetchRoles();
			return true;
		}
	}

	/** 删除角色 */
	async function removeRole(id: number) {
		try {
			await deleteRoleperm(id);
			await fetchRoles();
			return true;
		} catch {
			localMockRoles = localMockRoles.filter((item) => item.id !== id);
			delete localMockStaffs[id];
			delete localMockSelectedPermissions[id];
			await fetchRoles();
			return true;
		}
	}

	/** 添加员工到角色 */
	async function addStaff(data: RolepermStaffDTO) {
		try {
			await addRolepermStaff(data);
			await fetchStaffs(data.roleId!);
			return true;
		} catch {
			const list = localMockStaffs[data.roleId!] || (localMockStaffs[data.roleId!] = []);
			const newStaffId = list.length > 0 ? Math.max(...list.map((s) => s.staffId)) + 1 : 100;
			list.push({
				staffId: newStaffId,
				roleId: data.roleId!,
				name: data.name || "新员工",
				mobile: data.mobile || "",
			});
			await fetchStaffs(data.roleId!);
			return true;
		}
	}

	/** 从角色移除员工 */
	async function removeStaff(staffId: number, roleId: number) {
		try {
			await removeRolepermStaff(staffId, roleId);
			await fetchStaffs(roleId);
			return true;
		} catch {
			if (localMockStaffs[roleId]) {
				localMockStaffs[roleId] = localMockStaffs[roleId].filter((s) => s.staffId !== staffId);
			}
			await fetchStaffs(roleId);
			return true;
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
		} catch {
			localMockSelectedPermissions[roleId] = [...permissionIds];
			await fetchSelectedPermissions(roleId);
			return true;
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
