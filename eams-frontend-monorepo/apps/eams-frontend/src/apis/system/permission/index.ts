import { useHttp } from "@/plugins/http";
import type { QuanXianMiaoShuDuiXiang, RolepermDTO, RolepermOperatorDTO, RolepermStaffDTO } from "./type";

const http = useHttp();
const currBaseUrl = "/j2-sys/roleperm";
const legacyBaseUrl = "/sys/roleperm";
const acceptedBusinessCodes = new Set([0, 200, 10000]);

function appendQuery(path: string, params?: Record<string, unknown>) {
	if (!params) return path;

	const search = new URLSearchParams();
	for (const [key, value] of Object.entries(params)) {
		if (value === undefined || value === null || value === "") continue;
		search.append(key, String(value));
	}

	const query = search.toString();
	return query ? `${path}?${query}` : path;
}

function extractAcceptedResponse<T = unknown>(error: unknown) {
	const responseData = (error as { data?: { code?: unknown; data?: T; message?: string } } | undefined)?.data;
	if (!responseData || !acceptedBusinessCodes.has(Number(responseData.code))) return undefined;
	return responseData;
}

function shouldFallbackToLegacy(error: unknown) {
	const status =
		(error as { status?: number } | undefined)?.status ??
		(error as { response?: { status?: number } } | undefined)?.response?.status;
	if (status === 404) return true;

	const message = (error as { message?: string } | undefined)?.message ?? "";
	return message.includes("404") || message.includes("资源不存在");
}

async function getWithFallback<T = unknown>(path: string, params?: unknown) {
	try {
		return await http.get<T>(`${currBaseUrl}${path}`, params);
	} catch (error) {
		const acceptedResponse = extractAcceptedResponse<T>(error);
		if (acceptedResponse) return acceptedResponse;
		if (!shouldFallbackToLegacy(error)) throw error;
		return http.get<T>(`${legacyBaseUrl}${path}`, params);
	}
}

async function postWithFallback<T = unknown>(path: string, data?: unknown) {
	try {
		return await http.post<T>(`${currBaseUrl}${path}`, data);
	} catch (error) {
		const acceptedResponse = extractAcceptedResponse<T>(error);
		if (acceptedResponse) return acceptedResponse;
		if (!shouldFallbackToLegacy(error)) throw error;
		return http.post<T>(`${legacyBaseUrl}${path}`, data);
	}
}

async function deleteWithFallback<T = unknown>(path: string, data?: unknown) {
	try {
		return await http.delete<T>(`${currBaseUrl}${path}`, data);
	} catch (error) {
		const acceptedResponse = extractAcceptedResponse<T>(error);
		if (acceptedResponse) return acceptedResponse;
		if (!shouldFallbackToLegacy(error)) throw error;
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
	return http.post(`${currBaseUrl}/save/role`, data).catch(() => http.post(`${legacyBaseUrl}/save`, data));
};

/**
 * 删除角色
 */
export const deleteRoleperm = (id: number) => {
	return http
		.delete(appendQuery(`${currBaseUrl}/remove/role`, { roleId: id }))
		.catch(() => http.delete(`${legacyBaseUrl}/delete/role/${id}`));
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
	return http
		.post(
			appendQuery(`${currBaseUrl}/save/staff`, {
				roleId: data.roleId,
				staffId: data.staffId,
				name: data.name,
				mobile: data.mobile,
			}),
			data,
		)
		.catch(() => http.post(`${legacyBaseUrl}/save/staff`, data));
};

/**
 * 从角色移除员工
 */
export const removeRolepermStaff = (staffId: number, roleId: number) => {
	return http
		.delete(appendQuery(`${currBaseUrl}/${staffId}`, { roleId }))
		.catch(() => http.delete(`${legacyBaseUrl}/delete/staff/${staffId}`, { roleId }));
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
