import type { JsonVO } from "@/apis/http";
import { useHttp } from "@/plugins/http";

interface LegacyResponse<T> {
	errCode: number;
	msg: string;
	data?: T;
}

interface CoursePageRow {
	id?: number;
	name?: string;
	subjectId?: number;
	subjectName?: string;
	lessonType?: string;
	unitPrice?: number;
	price?: number;
	lessonCount?: number;
	unitName?: string;
	linkCount?: number;
	forSale?: boolean;
	storage?: number;
	saleCount?: number;
	saleAmount?: number;
	closeDate?: string;
	state?: string;
}

interface CoursePageData {
	rows?: CoursePageRow[]; // 注意：API返回的是 rows，不是 records
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

export async function getCourseList(params?: Record<string, any>) {
	const newParams = { ...params };
	if (newParams.pageNum) {
		newParams.pageIndex = newParams.pageNum;
		delete newParams.pageNum;
	}

	const response = await http.get<CoursePageData>("/j9-course/list", newParams);
	return toLegacyResponse(response);
}

export async function getCourseInfo(id: number) {
	const response = await http.get<Record<string, any>>("/app/common/course/info", { id });
	return toLegacyResponse(response);
}

export async function saveCourse(data: Record<string, any>) {
	const response = await http.post("/app/common/course/save", data);
	return toLegacyResponse(response);
}

export async function deleteCourse(ids: Array<number>) {
	const response = await http.post("/app/common/course/delete", ids);
	return toLegacyResponse(response);
}

export async function openCourse(ids: Array<number>) {
	const response = await http.post("/app/common/course/open", ids);
	return toLegacyResponse(response);
}

export async function closeCourse(ids: Array<number>) {
	const response = await http.post("/app/common/course/close", ids);
	return toLegacyResponse(response);
}

export async function linkCourse(id: number, linkId: number) {
	const response = await http.get("/app/common/course/link", { id, linkId });
	return toLegacyResponse(response);
}

export async function unlinkCourse(id: number, linkId: number) {
	const response = await http.get("/app/common/course/unlink", { id, linkId });
	return toLegacyResponse(response);
}

export async function getCourseSectionList(params?: Record<string, any>) {
	const response = await http.get<Record<string, any>>("/app/common/course/courseSectionList", params);
	return toLegacyResponse(response);
}

export async function saveCourseSection(data: Record<string, any>) {
	const response = await http.post("/app/common/course/saveCourseSection", data);
	return toLegacyResponse(response);
}
