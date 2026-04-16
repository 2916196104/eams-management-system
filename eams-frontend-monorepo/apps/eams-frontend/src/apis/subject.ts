import type { JsonVO } from "@/apis/http";
import { useHttp } from "@/plugins/http";

interface LegacyResponse<T> {
	errCode: number;
	msg: string;
	data?: T;
}

interface SubjectRow {
	id?: number;
	name?: string;
	sortNum?: number;
	info?: string;
}

interface SubjectPageData {
	rows?: SubjectRow[]; // 改成 rows
	total?: number;
	pageIndex?: number;
	pageSize?: number;
	pages?: number;
}

const SUCCESS_CODE = 10000;
const http = useHttp();

function toLegacyResponse<T>(response: JsonVO<T>): LegacyResponse<T> {
	return {
		errCode: response.code === SUCCESS_CODE ? 0 : response.code,
		msg: response.message,
		data: response.data,
	};
}

export async function getSubjectList(params?: Record<string, any>) {
	const newParams = { ...params };
	if (newParams.pageNum) {
		newParams.pageIndex = newParams.pageNum;
		delete newParams.pageNum;
	}

	const response = await http.get<SubjectPageData>("/j9-subject/list", newParams);
	return toLegacyResponse(response);
}

export async function saveSubject(data: Record<string, any>) {
	const response = await http.post("/app/common/subject/save", data);
	return toLegacyResponse(response);
}

export async function deleteSubject(ids: Array<number>) {
	const response = await http.post("/app/common/subject/delete", ids);
	return toLegacyResponse(response);
}
