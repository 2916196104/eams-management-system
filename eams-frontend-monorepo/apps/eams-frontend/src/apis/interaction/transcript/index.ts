import { useHttp } from "@/plugins/http";
import type { JsonVO } from "@/apis/type";
import type { PageDTO } from "@/components/mytable/type";
import type {
	GradeListQuery,
	GradeSaveDTO,
	GradeDeleteDTO,
	GradeRecordSaveDTO,
	GradeRecordDeleteDTO,
	GradeVO,
	GradeRecordVO,
	GradeRecordListQuery,
} from "./type";

const http = useHttp();
const baseUrl = "/j7-interaction/j7-grade";

// ==================== Mock 数据 ====================

const USE_MOCK = true;

/** mock 考核项列表 */
let mockGradeList: GradeVO[] = [
	{
		id: 1,
		title: "期中考试",
		info: "2026年第一学期期中考试",
		creator: 101,
		creatorName: "张老师",
		addTime: "2026-03-10 10:00:00",
	},
	{
		id: 2,
		title: "期末考试",
		info: "2026年第一学期期末考试",
		creator: 101,
		creatorName: "张老师",
		addTime: "2026-03-15 14:00:00",
	},
	{
		id: 3,
		title: "课堂测验一",
		info: "Vue3 基础课堂测验",
		creator: 102,
		creatorName: "李老师",
		addTime: "2026-03-18 09:30:00",
	},
	{
		id: 4,
		title: "课堂测验二",
		info: "Spring Boot 基础课堂测验",
		creator: 102,
		creatorName: "李老师",
		addTime: "2026-03-22 16:00:00",
	},
	{
		id: 5,
		title: "平时成绩",
		info: "出勤与课堂表现综合评分",
		creator: 101,
		creatorName: "张老师",
		addTime: "2026-03-25 08:00:00",
	},
];

/** mock 成绩记录 */
let mockRecords: GradeRecordVO[] = [
	{
		id: 101,
		gradeId: 1,
		studentId: 201,
		studentName: "赵同学",
		score: 88,
		creator: 101,
		addTime: "2026-03-12 10:00:00",
	},
	{
		id: 102,
		gradeId: 1,
		studentId: 202,
		studentName: "钱同学",
		score: 92,
		creator: 101,
		addTime: "2026-03-12 10:00:00",
	},
	{
		id: 103,
		gradeId: 1,
		studentId: 203,
		studentName: "孙同学",
		score: 75,
		creator: 101,
		addTime: "2026-03-12 10:00:00",
	},
	{
		id: 104,
		gradeId: 1,
		studentId: 204,
		studentName: "李同学",
		score: 95,
		creator: 101,
		addTime: "2026-03-12 10:00:00",
	},
	{
		id: 105,
		gradeId: 1,
		studentId: 205,
		studentName: "周同学",
		score: 60,
		creator: 101,
		addTime: "2026-03-12 10:00:00",
	},
	{
		id: 106,
		gradeId: 1,
		studentId: 206,
		studentName: "吴同学",
		score: 83,
		creator: 101,
		addTime: "2026-03-12 10:00:00",
	},
	{
		id: 201,
		gradeId: 2,
		studentId: 201,
		studentName: "赵同学",
		score: 90,
		creator: 101,
		addTime: "2026-03-20 14:00:00",
	},
	{
		id: 202,
		gradeId: 2,
		studentId: 202,
		studentName: "钱同学",
		score: 85,
		creator: 101,
		addTime: "2026-03-20 14:00:00",
	},
	{
		id: 203,
		gradeId: 2,
		studentId: 203,
		studentName: "孙同学",
		score: 78,
		creator: 101,
		addTime: "2026-03-20 14:00:00",
	},
	{
		id: 204,
		gradeId: 2,
		studentId: 204,
		studentName: "李同学",
		score: 98,
		creator: 101,
		addTime: "2026-03-20 14:00:00",
	},
	{
		id: 205,
		gradeId: 2,
		studentId: 205,
		studentName: "周同学",
		score: 55,
		creator: 101,
		addTime: "2026-03-20 14:00:00",
	},
	{
		id: 206,
		gradeId: 2,
		studentId: 206,
		studentName: "吴同学",
		score: 80,
		creator: 101,
		addTime: "2026-03-20 14:00:00",
	},
	{
		id: 301,
		gradeId: 3,
		studentId: 201,
		studentName: "赵同学",
		score: 92,
		creator: 102,
		addTime: "2026-03-19 10:00:00",
	},
	{
		id: 302,
		gradeId: 3,
		studentId: 202,
		studentName: "钱同学",
		score: 88,
		creator: 102,
		addTime: "2026-03-19 10:00:00",
	},
	{
		id: 303,
		gradeId: 3,
		studentId: 203,
		studentName: "孙同学",
		score: 70,
		creator: 102,
		addTime: "2026-03-19 10:00:00",
	},
	{
		id: 304,
		gradeId: 4,
		studentId: 201,
		studentName: "赵同学",
		score: 86,
		creator: 102,
		addTime: "2026-03-24 16:00:00",
	},
	{
		id: 305,
		gradeId: 4,
		studentId: 202,
		studentName: "钱同学",
		score: 91,
		creator: 102,
		addTime: "2026-03-24 16:00:00",
	},
	{
		id: 401,
		gradeId: 5,
		studentId: 201,
		studentName: "赵同学",
		score: 95,
		creator: 101,
		addTime: "2026-03-26 08:00:00",
	},
	{
		id: 402,
		gradeId: 5,
		studentId: 202,
		studentName: "钱同学",
		score: 90,
		creator: 101,
		addTime: "2026-03-26 08:00:00",
	},
	{
		id: 403,
		gradeId: 5,
		studentId: 203,
		studentName: "孙同学",
		score: 80,
		creator: 101,
		addTime: "2026-03-26 08:00:00",
	},
	{
		id: 404,
		gradeId: 5,
		studentId: 204,
		studentName: "李同学",
		score: 100,
		creator: 101,
		addTime: "2026-03-26 08:00:00",
	},
	{
		id: 405,
		gradeId: 5,
		studentId: 205,
		studentName: "周同学",
		score: 70,
		creator: 101,
		addTime: "2026-03-26 08:00:00",
	},
];

let mockGradeIdCounter = mockGradeList.length + 1;
let mockRecordIdCounter = 500;

/** 成功响应 */
function ok<T>(data: T): JsonVO<T> {
	return { code: 10000, message: "success", data };
}

// ==================== Mock 实现 ====================

function mockGetGradeList(query: GradeListQuery): JsonVO<PageDTO<GradeVO>> {
	let filtered = [...mockGradeList];
	if (query.title) {
		const keyword = query.title.toLowerCase();
		filtered = filtered.filter((g) => g.title.toLowerCase().includes(keyword));
	}
	if (query.creatorName) {
		const keyword = query.creatorName.toLowerCase();
		filtered = filtered.filter((g) => g.creatorName.toLowerCase().includes(keyword));
	}
	const pageIndex = query.pageIndex || 1;
	const pageSize = query.pageSize || 10;
	const start = (pageIndex - 1) * pageSize;
	return ok({ pageIndex, pageSize, total: filtered.length, rows: filtered.slice(start, start + pageSize) });
}

function mockGetGradeRecordList(query: GradeRecordListQuery): JsonVO<PageDTO<GradeRecordVO>> {
	let filtered = [...mockRecords];
	if (query.gradeId) {
		filtered = filtered.filter((r) => r.gradeId === query.gradeId);
	}
	if (query.studentId) {
		filtered = filtered.filter((r) => r.studentId === query.studentId);
	}
	const pageIndex = query.pageIndex || 1;
	const pageSize = query.pageSize || 10;
	const start = (pageIndex - 1) * pageSize;
	return ok({ pageIndex, pageSize, total: filtered.length, rows: filtered.slice(start, start + pageSize) });
}

function mockSaveGrade(data: GradeSaveDTO): JsonVO<boolean> {
	if (data.id) {
		const idx = mockGradeList.findIndex((g) => g.id === data.id);
		if (idx !== -1) {
			mockGradeList[idx] = { ...mockGradeList[idx], title: data.title, info: data.info };
			return ok(true);
		}
	}
	const newId = mockGradeIdCounter++;
	mockGradeList.unshift({
		id: newId,
		title: data.title,
		info: data.info,
		creator: 1,
		creatorName: "当前教师",
		addTime: new Date().toLocaleString("zh-CN", { hour12: false }).replace(/\//g, "-"),
	});
	return ok(true);
}

function mockDeleteGrade(data: GradeDeleteDTO): JsonVO<boolean> {
	mockGradeList = mockGradeList.filter((g) => !data.ids.includes(g.id));
	mockRecords = mockRecords.filter((r) => !data.ids.includes(r.gradeId));
	return ok(true);
}

function mockSaveRecord(data: GradeRecordSaveDTO): JsonVO<boolean> {
	if (data.id) {
		const idx = mockRecords.findIndex((r) => r.id === data.id);
		if (idx !== -1) {
			mockRecords[idx] = { ...mockRecords[idx], studentId: data.studentId, score: data.score };
			return ok(true);
		}
	}
	const newId = mockRecordIdCounter++;
	const names = ["赵同学", "钱同学", "孙同学", "李同学", "周同学", "吴同学", "郑同学", "王同学"];
	mockRecords.push({
		id: newId,
		gradeId: data.gradeId,
		studentId: data.studentId,
		studentName: names.find((_, i) => i + 1 === data.studentId) || `学生${data.studentId}`,
		score: data.score,
		creator: 1,
		addTime: new Date().toLocaleString("zh-CN", { hour12: false }).replace(/\//g, "-"),
	});
	return ok(true);
}

function mockDeleteRecord(data: GradeRecordDeleteDTO): JsonVO<boolean> {
	if (data.id) {
		mockRecords = mockRecords.filter((r) => r.id !== data.id);
	}
	return ok(true);
}

// ==================== 导出（自动切换 Mock/真实 API） ====================

/** 获取考核项列表（条件+分页） */
export const getGradeList = (query: GradeListQuery) => {
	if (USE_MOCK) return Promise.resolve(mockGetGradeList(query));
	return http.get<PageDTO<GradeVO>>(`${baseUrl}/get-grade-list`, query);
};

/** 获取成绩记录列表（条件+分页） */
export const getGradeRecordList = (query: GradeRecordListQuery) => {
	if (USE_MOCK) return Promise.resolve(mockGetGradeRecordList(query));
	return http.get<PageDTO<GradeRecordVO>>(`${baseUrl}/list`, query);
};

/** 保存考核项（新增/修改） */
export const saveGrade = (data: GradeSaveDTO) => {
	if (USE_MOCK) return Promise.resolve(mockSaveGrade(data));
	return http.post<boolean>(`${baseUrl}/save-grade-list`, null, { params: data });
};

/** 删除考核项（批量） */
export const deleteGrade = (data: GradeDeleteDTO) => {
	if (USE_MOCK) return Promise.resolve(mockDeleteGrade(data));
	return http.delete<boolean>(`${baseUrl}/delete-grade-list`, null, { params: { ids: data.ids } });
};

/** 保存成绩记录（新增/修改） */
export const saveRecord = (data: GradeRecordSaveDTO) => {
	if (USE_MOCK) return Promise.resolve(mockSaveRecord(data));
	return http.post<boolean>(`${baseUrl}/saveRecord`, data);
};

/** 删除成绩记录 */
export const deleteRecord = (data: GradeRecordDeleteDTO) => {
	if (USE_MOCK) return Promise.resolve(mockDeleteRecord(data));
	return http.delete<boolean>(`${baseUrl}/delete`, data);
};

/** 导入成绩（Excel） */
export const importGrade = (gradeId: number, file: File) => {
	if (USE_MOCK) {
		return Promise.resolve(ok(true));
	}
	return http.postWithFile<boolean>(`${baseUrl}/import`, { file, gradeId });
};
