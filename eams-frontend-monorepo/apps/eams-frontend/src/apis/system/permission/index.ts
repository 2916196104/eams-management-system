import { useHttp } from "@/plugins/http";
import type { QuanXianMiaoShuDuiXiang, RolepermDTO, RolepermOperatorDTO, RolepermStaffDTO } from "./type";

const http = useHttp();
const currBaseUrl = "/j2-sys/roleperm";
const legacyBaseUrl = "/sys/roleperm";

async function getWithFallback<T = unknown>(path: string, params?: unknown) {
	try {
		return await http.get<T>(`${currBaseUrl}${path}`, params);
	} catch {
		return http.get<T>(`${legacyBaseUrl}${path}`, params);
	}
}

async function postWithFallback<T = unknown>(path: string, data?: unknown) {
	try {
		return await http.post<T>(`${currBaseUrl}${path}`, data);
	} catch {
		return http.post<T>(`${legacyBaseUrl}${path}`, data);
	}
}

async function deleteWithFallback<T = unknown>(path: string, data?: unknown) {
	try {
		return await http.delete<T>(`${currBaseUrl}${path}`, data);
	} catch {
		return http.delete<T>(`${legacyBaseUrl}${path}`, data);
	}
}

/**
 * 获取角色分页列表
 */
export const getRolepermPage = (params?: { id?: number; pageIndex?: number; pageSize?: number }) => {
	return getWithFallback("/page", params);
};

/**
 * 获取角色名称列表
 */
export const getRolepermNameList = (params?: { id?: number; pageIndex?: number; pageSize?: number }) => {
	return getWithFallback<RolepermDTO[]>("/nameList", params);
};

/**
 * 保存角色（新增/编辑）
 */
export const saveRoleperm = (data: RolepermDTO) => {
	return postWithFallback("/save", data);
};

/**
 * 删除角色
 */
export const deleteRoleperm = (id: number) => {
	return deleteWithFallback(`/delete/role/${id}`);
};

/**
 * 获取角色员工列表
 */
export const getRolepermStaffList = (params: { roleId: number; pageIndex?: number; pageSize?: number }) => {
	return getWithFallback("/list/staff", params);
};

/**
 * 获取当前员工列表（姓名+职称）
 */
export const getRolepermOperators = (params?: { name?: string; pageIndex?: number; pageSize?: number }) => {
	return getWithFallback<RolepermOperatorDTO[]>("/operators", params);
};

/**
 * 给角色添加员工
 */
export const addRolepermStaff = (data: RolepermStaffDTO) => {
	return postWithFallback("/save/staff", data);
};

/**
 * 从角色移除员工
 */
export const removeRolepermStaff = (staffId: number, roleId: number) => {
	return deleteWithFallback(`/delete/staff/${staffId}`, { roleId });
};

/**
 * 获取可分配的权限列表
 */
export const getPermissionList = () => {
	return getWithFallback("/query/list/permission");
};

/**
 * 获取已分配的权限列表
 */
export const getSelectedPermissionList = (roleId: number) => {
	return getWithFallback(`/query/list/select/${roleId}`);
};

/**
 * 保存角色权限分配
 */
export const saveRolePermission = (roleId: number, data: QuanXianMiaoShuDuiXiang[]) => {
	return postWithFallback(`/modify/${roleId}`, data);
};
