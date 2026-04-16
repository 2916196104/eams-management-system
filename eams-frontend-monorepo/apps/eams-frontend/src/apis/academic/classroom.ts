import { useHttp } from "@/plugins/http";

const http = useHttp();

export interface JsonVo<T> {
	code: number;
	message: string;
	data: T;
}

export interface PageDtoClassroomVo {
	rows: ClassroomItem[];
	total: number;
	size: number;
	current: number;
}

export interface ClassroomItem {
	id: number;
	name: string;
	address: string;
	area: number;
	remark?: string;
	schoolId: number;
}

export interface ClassroomListParams {
	name?: string;
	pageIndex?: number;
	pageSize?: number;
}

export interface SaveClassroomParams {
	id?: number;
	name: string;
	address: string;
	area: number;
	remark?: string;
	schoolId: number;
}

// 获取教室列表（修复点：使用 { params } 包裹）
export const getClassroomList = (params: ClassroomListParams) => {
	return http.get<JsonVo<PageDtoClassroomVo>>("/j4/classroom/list", params);
};

// 获取教室详情（无参数，无需改动）
export const getClassroomDetail = (id: number) => {
	return http.get<JsonVo<ClassroomItem>>(`/j4/classroom/${id}`);
};

// 保存教室（POST 请求参数传递方式通常没问题，但为保险也建议检查）
export const saveClassroom = (data: SaveClassroomParams) => {
	return http.post<JsonVo<number>>("/j4/classroom/save", data);
};

// 删除教室（DELETE 请求需注意 data 字段，当前写法正确）
export const deleteClassroom = (ids: number[]) => {
	return http.delete<JsonVo<number[]>>("/j4/classroom/delete", { data: ids });
};