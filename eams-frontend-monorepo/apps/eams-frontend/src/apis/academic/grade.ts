import { useHttp } from "@/plugins/http";

const http = useHttp();

export interface JsonVo<T> {
	code: number;
	message: string;
	data: T;
}

export interface PageDtoNianJiBiao {
	records: GradeItem[];
	total: number;
	size: number;
	current: number;
}

export interface GradeItem {
	id: number;
	name: string;
	year?: number;
	sortNum?: number;
	remark?: string;
}

export interface GradeListParams {
	name?: string;
	pageIndex?: number;
	pageSize?: number;
	year?: number;
}

export interface SaveGradeParams {
	id?: number;
	name: string;
	year?: number;
	sortNum?: number;
	remark?: string;
}

// 获取年级列表
export const getGradeList = (params: GradeListParams) => {
	return http.get<JsonVo<PageDtoNianJiBiao>>("/j6-eas/class_grade/list", params);
};

// 获取年级详情
export const getGradeDetail = (id: number) => {
	return http.get<JsonVo<GradeItem>>(`/j6-eas/class_grade/${id}`);
};

// 获取年级名称列表（下拉用）
export const getGradeNameList = () => {
	return http.get<JsonVo<Array<{ id: number; name: string }>>>("/j6-eas/class_grade/name");
};

// 保存年级
export const saveGrade = (data: SaveGradeParams) => {
	return http.post<JsonVo<number>>("/j6-eas/class_grade/save", data);
};

// 删除年级
export const deleteGrade = (ids: number[]) => {
	return http.delete<JsonVo<number[]>>("/j6-eas/class_grade/delete", { data: ids });
};

// 升级年级
export const upgradeGrade = (ids: number[]) => {
	return http.post<JsonVo<number[]>>("/j6-eas/class_grade/upgrade", ids);
};
