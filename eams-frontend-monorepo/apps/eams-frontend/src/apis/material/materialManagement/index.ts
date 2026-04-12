import { useHttp } from "@/plugins/http";
import type { PageDTO } from "@/components/mytable/type";
import type {
	MaterialDetail,
	MaterialItem,
	MaterialPageQuery,
	MaterialRecordItem,
	MaterialRecordQuery,
	MaterialSaveDTO,
	MaterialStateValue,
} from "./type";
const http = useHttp();

function appendQuery(path: string, params?: Record<string, number | undefined>) {
	if (!params) return path;

	const search = new URLSearchParams();
	for (const [key, value] of Object.entries(params)) {
		if (value === undefined) continue;
		search.append(key, String(value));
	}

	const query = search.toString();
	return query ? `${path}?${query}` : path;
}

export const getMaterialList = (params: MaterialRecordQuery) => {
	return http.get<PageDTO<MaterialRecordItem>>("/material-record", params);
};

export const getMaterialPage = (params: MaterialPageQuery) => {
	return http.get<PageDTO<MaterialItem>>("/material/list", params);
};

export const getMaterialDetail = (id: number) => {
	return http.get<MaterialDetail>(`/material/detail/${id}`);
};

export const saveMaterial = (data: MaterialSaveDTO) => {
	return http.post<number>("/material/save", data);
};

export const materialInStorage = (ids: number[], amount?: number) => {
	return http.post<number[]>(appendQuery("/material-record/InStorage", { amount }), ids);
};

export const materialOutStorage = (ids: number[], amount?: number) => {
	return http.post<number[]>(appendQuery("/material-record/OutStorage", { amount }), ids);
};

export const deleteMaterials = (ids: number[]) => {
	return http.delete<string>("/material", ids);
};

export const updateMaterialState = (ids: number[], state: MaterialStateValue) => {
	return http.put<string>(appendQuery("/material/enable-disable", { state }), ids);
};
