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
	rows?: CoursePageRow[];
	total?: number;
	pageIndex?: number;
	pageSize?: number;
	pages?: number;
}

const SUCCESS_CODE = 10000;
const http = useHttp();

function toLegacyResponse<T>(response: JsonVO<T>): LegacyResponse<T> {
	// code 10000 表示成功
    const isSuccess = response.code === 10000 || response.code === SUCCESS_CODE;
    return {
        errCode: isSuccess ? 0 : response.code,
        msg: response.message,
        data: response.data,
    };
}

// 获取课程列表
export async function getCourseList(params?: Record<string, any>) {
    const newParams = { ...params };
    if (newParams.pageNum) {
        newParams.pageIndex = newParams.pageNum;
        delete newParams.pageNum;
    }
    const response = await http.get<CoursePageData>("/j9-course/list", newParams);
    return toLegacyResponse(response);
}

// 获取课程详情
export async function getCourseInfo(id: number) {
     const response = await http.get(`/j9-course/detail/${id}`);
    console.log('原始响应：', response);  // 查看原始数据
    return {
        errCode: response.code === 10000 ? 0 : response.code,
        msg: response.message,
        data: response.data
    };
}

// 保存课程
export async function saveCourse(data: Record<string, any>) {
     console.log('保存课程数据：', data);  // 添加日志
    const response = await http.post("/j9-course/save", data);
    console.log('保存响应：', response);  // 添加日志
    return toLegacyResponse(response);
}




// 获取已关联课程列表
export async function getLinkedCourses(courseId: number) {
    const response = await http.get("/j9-course/link", {
        params: {
            courseId,
            pageIndex: 1,
            pageSize: 100
        }
    });
    return toLegacyResponse(response);
}

// 添加关联
export async function linkCourse(courseId: number, linkedCourseIds: number[]) {
    const url = `/j9-course/link?courseId=${courseId}&linkedCourseIds=${linkedCourseIds.join(',')}`;
    const response = await http.post(url, null);
    return toLegacyResponse(response);
}

// 删除关联
export async function unlinkCourse(courseId: number, linkedCourseIds: number[]) {
    const url = `/j9-course/link?courseId=${courseId}&linkedCourseIds=${linkedCourseIds.join(',')}`;
    const response = await http.delete(url);
    return toLegacyResponse(response);
}

// 获取章节列表
export async function getCourseSectionList(params?: Record<string, any>) {
    const response = await http.get("/j9-course/chapter/query-chapters", { courseId });
    return toLegacyResponse(response);
}

// 添加章节
export async function addCourseSection(data: Record<string, any>) {
    const response = await http.post("/j9-course/chapter/add-chapter", data);
    return toLegacyResponse(response);
}

// 删除章节
export async function removeCourseSection(id: number) {
    const response = await http.delete("/j9-course/chapter/remove-chapter", { data: { id } });
    return toLegacyResponse(response);
}
