import { useHttp } from "@/plugins/http";
import type { RolepermDTO, QuanXianMiaoShuDuiXiang, RolepermStaffDTO } from "./type";

const http = useHttp();
const currBaseUrl = "/sys/roleperm";

/**
 * 获取角色分页列表
 */
export const getRolepermPage = (params?: { id?: number; pageIndex?: number; pageSize?: number }) => {
	return http.get(`${currBaseUrl}/page`, params);
};

/**
 * 获取角色名称列表
 */
export const getRolepermNameList = () => {
	return http.get(`${currBaseUrl}/nameList`);
};

/**
 * 保存角色（新增/编辑）
 */
export const saveRoleperm = (data: RolepermDTO) => {
	return http.post(`${currBaseUrl}/save`, data);
};

/**
 * 删除角色
 */
export const deleteRoleperm = (id: number) => {
	return http.delete(`${currBaseUrl}/delete/role/${id}`);
};

/**
 * 获取角色员工列表
 */
export const getRolepermStaffList = (params: { roleId: number; pageIndex?: number; pageSize?: number }) => {
	return http.get(`${currBaseUrl}/list/staff`, params);
};

/**
 * 给角色添加员工
 */
export const addRolepermStaff = (data: RolepermStaffDTO) => {
	return http.post(`${currBaseUrl}/save/staff`, data);
};

/**
 * 从角色移除员工
 */
export const removeRolepermStaff = (staffId: number, roleId: number) => {
	return http.delete(`${currBaseUrl}/delete/staff/${staffId}`, { roleId });
};

/**
 * 获取可分配的权限列表
 */
export const getPermissionList = () => {
	return http.get(`${currBaseUrl}/query/list/permission`);
};

/**
 * 获取已分配的权限列表
 */
export const getSelectedPermissionList = (roleId: number) => {
	return http.get(`${currBaseUrl}/query/list/select/${roleId}`);
};

/**
 * 保存角色权限分配
 */
export const saveRolePermission = (roleId: number, data: QuanXianMiaoShuDuiXiang[]) => {
	return http.post(`${currBaseUrl}/modify/${roleId}`, data);
};
