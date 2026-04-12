import { useHttp } from "@/plugins/http";
import type { JsonVO } from "@/apis/type";
import type { PageDTO } from "@/components/mytable/type";
import type {
	HomeworkListQuery,
	HomeworkSaveDTO,
	HomeworkDeleteDTO,
	HomeworkCommentDTO,
	HomeworkVO,
	HomeworkRecordVO,
	HomeworkRecordsQuery,
} from "./type";

const http = useHttp();
const baseUrl = "/j7-interaction/j7-homework";

// ==================== Mock 数据 ====================

const USE_MOCK = true;

/** mock 作业列表 */
let mockHomeworkList: HomeworkVO[] = [
	{
		id: 1,
		title: "Spring Boot 基础练习",
		content: "完成 Spring Boot 入门教程中的所有练习题，包括依赖注入、自动装配和 RESTful API 开发",
		classId: 1,
		className: "Java 高级班",
		teacherName: "张老师",
		creator: 101,
		completeCount: 15,
		completed: false,
		addTime: "2026-03-15 10:00:00",
	},
	{
		id: 2,
		title: "Vue3 组件开发实战",
		content: "使用 Vue3 Composition API 开发一个用户管理组件，包含增删改查功能",
		classId: 1,
		className: "Java 高级班",
		teacherName: "张老师",
		creator: 101,
		completeCount: 28,
		completed: true,
		addTime: "2026-03-18 14:30:00",
	},
	{
		id: 3,
		title: "数据库设计作业",
		content: "为在线图书商城设计数据库 ER 图，并编写建表 SQL 语句",
		classId: 2,
		className: "软件工程班",
		teacherName: "李老师",
		creator: 102,
		completeCount: 22,
		completed: true,
		addTime: "2026-03-20 09:00:00",
	},
	{
		id: 4,
		title: "Redis 缓存实践",
		content: "使用 Redis 实现用户登录 Token 管理和热点数据缓存，编写单元测试",
		classId: 2,
		className: "软件工程班",
		teacherName: "李老师",
		creator: 102,
		completeCount: 8,
		completed: false,
		addTime: "2026-03-22 16:00:00",
	},
	{
		id: 5,
		title: "前端性能优化报告",
		content: "选择一个实际项目，分析其前端性能瓶颈并给出优化方案，提交优化报告",
		classId: 3,
		className: "全栈开发班",
		teacherName: "王老师",
		creator: 103,
		completeCount: 30,
		completed: true,
		addTime: "2026-03-10 11:00:00",
	},
	{
		id: 6,
		title: "微服务架构设计",
		content: "将单体电商应用拆分为微服务架构，绘制服务调用关系图，定义 API 网关路由规则",
		classId: 3,
		className: "全栈开发班",
		teacherName: "王老师",
		creator: 103,
		completeCount: 5,
		completed: false,
		addTime: "2026-03-25 08:30:00",
	},
];

/** mock 提交记录 */
const mockRecordsMap: Record<number, HomeworkRecordVO[]> = {
	1: [
		{
			id: 101,
			homeworkId: 1,
			studentId: 201,
			studentName: "赵同学",
			content: "已完成所有依赖注入练习",
			score: 95,
			comment: "完成得很好",
			commentTeacherName: "张老师",
			commentTime: "2026-03-16 10:00:00",
			addTime: "2026-03-15 20:30:00",
		},
		{
			id: 102,
			homeworkId: 1,
			studentId: 202,
			studentName: "钱同学",
			content: "自动装配部分有些疑惑",
			score: 80,
			comment: "建议再复习一下注解",
			commentTeacherName: "张老师",
			commentTime: "2026-03-16 11:00:00",
			addTime: "2026-03-15 21:00:00",
		},
		{
			id: 103,
			homeworkId: 1,
			studentId: 203,
			studentName: "孙同学",
			content: "RESTful API 已完成",
			score: null,
			comment: null,
			commentTeacherName: null,
			commentTime: null,
			addTime: "2026-03-16 09:00:00",
		},
		{
			id: 104,
			homeworkId: 1,
			studentId: 204,
			studentName: "李同学",
			content: "全部完成，附带了单元测试",
			score: 100,
			comment: "非常优秀",
			commentTeacherName: "张老师",
			commentTime: "2026-03-16 14:00:00",
			addTime: "2026-03-15 22:00:00",
		},
		{
			id: 105,
			homeworkId: 1,
			studentId: 205,
			studentName: "周同学",
			content: "完成了一半",
			score: null,
			comment: null,
			commentTeacherName: null,
			commentTime: null,
			addTime: "2026-03-16 18:00:00",
		},
	],
	2: [
		{
			id: 201,
			homeworkId: 2,
			studentId: 201,
			studentName: "赵同学",
			content: "用户管理组件已完成",
			score: 90,
			comment: "代码结构清晰",
			commentTeacherName: "张老师",
			commentTime: "2026-03-19 10:00:00",
			addTime: "2026-03-18 22:00:00",
		},
		{
			id: 202,
			homeworkId: 2,
			studentId: 202,
			studentName: "钱同学",
			content: "增删改查功能全部实现",
			score: 88,
			comment: "建议补充表单验证",
			commentTeacherName: "张老师",
			commentTime: "2026-03-19 11:00:00",
			addTime: "2026-03-18 23:00:00",
		},
	],
	3: [
		{
			id: 301,
			homeworkId: 3,
			studentId: 301,
			studentName: "吴同学",
			content: "ER 图和建表 SQL 都已完成",
			score: 92,
			comment: "表结构设计合理",
			commentTeacherName: "李老师",
			commentTime: "2026-03-21 09:00:00",
			addTime: "2026-03-20 20:00:00",
		},
		{
			id: 302,
			homeworkId: 3,
			studentId: 302,
			studentName: "郑同学",
			content: "设计完成，但缺少索引优化",
			score: 78,
			comment: "可以再优化索引设计",
			commentTeacherName: "李老师",
			commentTime: "2026-03-21 10:00:00",
			addTime: "2026-03-20 21:00:00",
		},
	],
};

let mockIdCounter = mockHomeworkList.length + 1;

/** 成功响应 */
function ok<T>(data: T): JsonVO<T> {
	return { code: 10000, message: "success", data };
}

// ==================== Mock 实现 ====================

function mockListHomework(query: HomeworkListQuery): JsonVO<PageDTO<HomeworkVO>> {
	let filtered = [...mockHomeworkList];
	if (query.title) {
		const keyword = query.title.toLowerCase();
		filtered = filtered.filter((h) => h.title.toLowerCase().includes(keyword));
	}
	if (query.className) {
		const keyword = query.className.toLowerCase();
		filtered = filtered.filter((h) => h.className.toLowerCase().includes(keyword));
	}
	if (query.teacherName) {
		const keyword = query.teacherName.toLowerCase();
		filtered = filtered.filter((h) => h.teacherName.toLowerCase().includes(keyword));
	}
	if (query.classId) {
		filtered = filtered.filter((h) => h.classId === query.classId);
	}
	const pageIndex = query.pageIndex || 1;
	const pageSize = query.pageSize || 10;
	const start = (pageIndex - 1) * pageSize;
	const rows = filtered.slice(start, start + pageSize);
	return ok({ pageIndex, pageSize, total: filtered.length, rows });
}

function mockGetHomeworkInfo(id: number): JsonVO<HomeworkVO> {
	const item = mockHomeworkList.find((h) => h.id === id);
	if (!item) return { code: 9999, message: "作业不存在" };
	return ok({ ...item, recordList: mockRecordsMap[id] || [] });
}

function mockListRecords(query: HomeworkRecordsQuery): JsonVO<PageDTO<HomeworkRecordVO>> {
	const records = mockRecordsMap[query.homeworkId] || [];
	const pageIndex = query.pageIndex || 1;
	const pageSize = query.pageSize || 10;
	const start = (pageIndex - 1) * pageSize;
	return ok({ pageIndex, pageSize, total: records.length, rows: records.slice(start, start + pageSize) });
}

function mockSaveHomework(data: HomeworkSaveDTO): JsonVO<number> {
	if (data.id) {
		const idx = mockHomeworkList.findIndex((h) => h.id === data.id);
		if (idx !== -1) {
			mockHomeworkList[idx] = {
				...mockHomeworkList[idx],
				title: data.title,
				content: data.content,
				classId: data.classId,
			};
			return ok(data.id);
		}
	}
	const newId = mockIdCounter++;
	const newItem: HomeworkVO = {
		id: newId,
		title: data.title,
		content: data.content,
		classId: data.classId,
		className: `班级${data.classId}`,
		teacherName: "当前教师",
		creator: 1,
		completeCount: 0,
		completed: false,
		addTime: new Date().toLocaleString("zh-CN", { hour12: false }).replace(/\//g, "-"),
	};
	mockHomeworkList.unshift(newItem);
	return ok(newId);
}

function mockDeleteHomework(data: HomeworkDeleteDTO): JsonVO<boolean> {
	if (data.id) {
		mockHomeworkList = mockHomeworkList.filter((h) => h.id !== data.id);
		delete mockRecordsMap[data.id!];
	}
	return ok(true);
}

function mockUpdateComment(data: HomeworkCommentDTO): JsonVO<boolean> {
	if (!data.id) return { code: 9999, message: "缺少记录ID" };
	for (const records of Object.values(mockRecordsMap)) {
		const record = records.find((r) => r.id === data.id);
		if (record) {
			record.comment = data.name || "";
			record.commentTeacherName = "当前教师";
			record.commentTime = new Date().toLocaleString("zh-CN", { hour12: false }).replace(/\//g, "-");
			return ok(true);
		}
	}
	return { code: 9999, message: "提交记录不存在" };
}

// ==================== 导出（自动切换 Mock/真实 API） ====================

/** 获取作业列表（条件+分页） */
export const listHomework = (query: HomeworkListQuery) => {
	if (USE_MOCK) return Promise.resolve(mockListHomework(query));
	return http.get<PageDTO<HomeworkVO>>(`${baseUrl}/list`, query);
};

/** 获取作业详情（含提交记录列表） */
export const getHomeworkInfo = (id: number) => {
	if (USE_MOCK) return Promise.resolve(mockGetHomeworkInfo(id));
	return http.get<HomeworkVO>(`${baseUrl}/info/${id}`);
};

/** 获取作业提交列表 */
export const listHomeworkRecords = (query: HomeworkRecordsQuery) => {
	if (USE_MOCK) return Promise.resolve(mockListRecords(query));
	return http.get<PageDTO<HomeworkRecordVO>>(`${baseUrl}/recordsList`, query);
};

/** 保存/提交作业 */
export const saveHomework = (data: HomeworkSaveDTO) => {
	if (USE_MOCK) return Promise.resolve(mockSaveHomework(data));
	return http.post<number>(`${baseUrl}/save`, data);
};

/** 点评作业 */
export const updateComment = (data: HomeworkCommentDTO) => {
	if (USE_MOCK) return Promise.resolve(mockUpdateComment(data));
	return http.post<boolean>(`${baseUrl}/comment`, data);
};

/** 删除作业 */
export const deleteHomework = (data: HomeworkDeleteDTO) => {
	if (USE_MOCK) return Promise.resolve(mockDeleteHomework(data));
	return http.delete<boolean>(`${baseUrl}/delete`, data);
};
