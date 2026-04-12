import { useHttp } from "@/plugins/http";

const http = useHttp();

export interface JsonVo<T> {
	code: number;
	message: string;
	data: T;
}

export interface PageClassListVo {
	records: ClassItem[];
	total: number;
	size: number;
	current: number;
}

export interface ClassItem {
	id: number;
	name: string;
	courseId: number;
	courseName: string;
	classroomId: number;
	classroom: string;
	teacherId: number;
	teacherName: string;
	startDate: string;
	endDate?: string;
	plannedLessonCount: number;
	plannedStudentCount: number;
	studentCount: number;
	overLessonCount: number;
	scheduleLessonCount: number;
	beOver: boolean;
	remark?: string;
}

export interface ClassListParams {
	pageIndex?: number;
	pageSize?: number;
	className?: string;
	courseName?: string;
	teacherName?: string;
	classroomName?: string;
	gradeName?: string;
}

export interface SaveClassParams {
	id?: number;
	name: string;
	courseId: number;
	classroomId: number;
	teacherId: number;
	startDate: string;
	endDate?: string;
	plannedLessonCount: number;
	plannedStudentCount: number;
	remark?: string;
}

// 分页查询班级
export const getClassList = (params: ClassListParams) => {
	const formData = new FormData();
	if (params.pageIndex) formData.append("pageIndex", String(params.pageIndex));
	if (params.pageSize) formData.append("pageSize", String(params.pageSize));
	if (params.className) formData.append("className", params.className);
	if (params.courseName) formData.append("courseName", params.courseName);
	if (params.teacherName) formData.append("teacherName", params.teacherName);

	return http.post<JsonVo<PageClassListVo>>("/j5-class-manager/page", formData, {
		headers: { "Content-Type": "multipart/form-data" },
	});
};

// 获取班级详情
export const getClassDetail = (id: number) => {
	return http.get<JsonVo<ClassItem>>(`/j5-class-manager/class-detail/${id}`);
};

// 保存班级
export const saveClass = (data: SaveClassParams) => {
	return http.post<JsonVo<number>>("/j5-class-manager", data);
};

// 删除班级
export const deleteClass = (ids: number[]) => {
	return http.delete<JsonVo<number[]>>("/j5-class-manager", { data: ids });
};

// 结业班级
export const overClass = (ids: number[]) => {
	return http.put<JsonVo<number[]>>("/j5-class-manager", null, { data: ids });
};

// 获取班级下拉选项
export const getClassOptions = (params?: { pageIndex?: number; pageSize?: number; className?: string }) => {
	return http.get<JsonVo<PageClassListVo>>("/j5-class-manager/class-options", params);
};

// 添加班级学员
export const addClassStudents = (classId: number, studentIds: number[]) => {
	return http.post<JsonVo<number>>("/j5-class-manager/class-student", { classId, studentIds });
};

// 批量调班
export const transferClassStudents = (newClassId: number, studentIds: number[]) => {
	return http.put<JsonVo<number>>("/j5-class-manager/class-student", { newClassId, studentIds });
};

// 删除班级学员
export const deleteClassStudents = (classId: number, studentIds: number[]) => {
	return http.delete<JsonVo<number>>("/j5-class-manager/class-student", { data: { classId, studentIds } });
};

// 分页查询班级学员
export const getClassStudents = (
	classId: number,
	params: { pageIndex?: number; pageSize?: number; studentName?: string },
) => {
	return http.post<JsonVo<PageClassListVo>>(`/j5-class-manager/${classId}/student/page`, params);
};
