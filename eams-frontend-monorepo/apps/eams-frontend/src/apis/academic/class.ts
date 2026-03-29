import { useHttp } from "@/plugins/http";

const http = useHttp();

// 通用响应类型
export interface JsonVo<T> {
  code: number;
  message: string;
  data: T;
}

// 班级列表响应
export interface PageClassListVo {
  records: ClassItem[];
  total: number;
  size: number;
  current: number;
}

// 班级数据类型
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

// 班级列表查询参数
export interface ClassListParams {
  pageIndex?: number;
  pageSize?: number;
  className?: string;
  courseName?: string;
  teacherName?: string;
  classroomName?: string;
  gradeName?: string;
}

// 保存班级参数
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

// 获取班级列表 (POST form-data)
export const getClassList = (params: ClassListParams) => {
  const formData = new FormData();
  if (params.pageIndex) formData.append('pageIndex', String(params.pageIndex));
  if (params.pageSize) formData.append('pageSize', String(params.pageSize));
  if (params.className) formData.append('className', params.className);
  if (params.courseName) formData.append('courseName', params.courseName);
  if (params.teacherName) formData.append('teacherName', params.teacherName);
  if (params.classroomName) formData.append('classroomName', params.classroomName);
  if (params.gradeName) formData.append('gradeName', params.gradeName);

  return http.post<JsonVo<PageClassListVo>>('/j5/class-manager/page', formData, {
    headers: { 'Content-Type': 'multipart/form-data' }
  });
};

// 获取班级详情
export const getClassDetail = (id: number) => {
  return http.get<JsonVo<ClassItem>>(`/j5/class-manager/class-detail/${id}`);
};

// 保存班级
export const saveClass = (data: SaveClassParams) => {
  return http.post<JsonVo<number>>('/j5/class-manager', data);
};

// 删除班级
export const deleteClass = (ids: number[]) => {
  return http.delete<JsonVo<number[]>>('/j5/class-manager', { params: { ids } });
};

// 结业班级
export const overClass = (ids: number[]) => {
  return http.put<JsonVo<number[]>>('/j5/class-manager', null, { params: { ids } });
};

// 获取班级下拉选项
export const getClassOptions = (params?: { pageIndex?: number; pageSize?: number; className?: string }) => {
  return http.get<JsonVo<PageClassListVo>>('/j5/class-manager/class-options', { params });
};
