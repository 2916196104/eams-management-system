import { useHttp } from "@/plugins/http";
import type { JsonVO } from "@/apis/type";
import type { PageDTO } from "@/components/mytable/type";
import type { LearningEvaluationQuery, TeachEvaluationVO } from "./type";

const http = useHttp();
const baseUrl = "/j7-interaction/j7-student-teacher";

// ==================== Mock 数据 ====================

const USE_MOCK = true;

/** mock 学评教列表 */
const mockList: TeachEvaluationVO[] = [
	{
		serialNumber: 1,
		studentName: "张三",
		teacherName: "李老师",
		lessonTitle: "Java基础第10讲",
		overallScore: 90,
		atmosphereScore: 95,
		attitudeScore: 92,
		effectScore: 88,
		content: "课堂气氛好，老师讲解清晰",
		addTime: "2026-03-16 15:30:00",
	},
	{
		serialNumber: 2,
		studentName: "李四",
		teacherName: "王老师",
		lessonTitle: "Vue3组件开发",
		overallScore: 85,
		atmosphereScore: 80,
		attitudeScore: 90,
		effectScore: 85,
		content: "老师态度认真，但课堂互动稍少",
		addTime: "2026-03-17 10:00:00",
	},
	{
		serialNumber: 3,
		studentName: "王五",
		teacherName: "李老师",
		lessonTitle: "Spring Boot入门",
		overallScore: 92,
		atmosphereScore: 93,
		attitudeScore: 95,
		effectScore: 88,
		content: "非常满意，收获很大",
		addTime: "2026-03-18 14:20:00",
	},
	{
		serialNumber: 4,
		studentName: "赵六",
		teacherName: "赵老师",
		lessonTitle: "数据库原理",
		overallScore: 78,
		atmosphereScore: 75,
		attitudeScore: 85,
		effectScore: 75,
		content: "内容偏理论，希望增加实操",
		addTime: "2026-03-19 09:15:00",
	},
	{
		serialNumber: 5,
		studentName: "钱七",
		teacherName: "王老师",
		lessonTitle: "TypeScript高级",
		overallScore: 88,
		atmosphereScore: 90,
		attitudeScore: 88,
		effectScore: 86,
		content: "讲解深入浅出，案例丰富",
		addTime: "2026-03-20 16:45:00",
	},
	{
		serialNumber: 6,
		studentName: "孙八",
		teacherName: "李老师",
		lessonTitle: "Redis缓存实践",
		overallScore: 95,
		atmosphereScore: 96,
		attitudeScore: 98,
		effectScore: 91,
		content: "老师非常专业，课堂氛围活跃",
		addTime: "2026-03-21 11:30:00",
	},
	{
		serialNumber: 7,
		studentName: "周九",
		teacherName: "赵老师",
		lessonTitle: "微服务架构设计",
		overallScore: 82,
		atmosphereScore: 78,
		attitudeScore: 88,
		effectScore: 80,
		content: "内容有深度，但节奏偏快",
		addTime: "2026-03-22 13:00:00",
	},
	{
		serialNumber: 8,
		studentName: "吴十",
		teacherName: "王老师",
		lessonTitle: "前端性能优化",
		overallScore: 91,
		atmosphereScore: 88,
		attitudeScore: 94,
		effectScore: 91,
		content: "实用性强，学到了很多优化技巧",
		addTime: "2026-03-23 15:00:00",
	},
	{
		serialNumber: 9,
		studentName: "郑十一",
		teacherName: "李老师",
		lessonTitle: "Java基础第12讲",
		overallScore: 87,
		atmosphereScore: 85,
		attitudeScore: 90,
		effectScore: 86,
		content: "老师耐心负责，答疑及时",
		addTime: "2026-03-24 10:30:00",
	},
	{
		serialNumber: 10,
		studentName: "陈十二",
		teacherName: "赵老师",
		lessonTitle: "Docker容器化",
		overallScore: 83,
		atmosphereScore: 80,
		attitudeScore: 86,
		effectScore: 83,
		content: "实验环节很有帮助",
		addTime: "2026-03-25 14:00:00",
	},
	{
		serialNumber: 11,
		studentName: "林十三",
		teacherName: "王老师",
		lessonTitle: "Vue3组合式API",
		overallScore: 89,
		atmosphereScore: 92,
		attitudeScore: 90,
		effectScore: 85,
		content: "课堂互动多，讲解生动",
		addTime: "2026-03-26 09:00:00",
	},
	{
		serialNumber: 12,
		studentName: "黄十四",
		teacherName: "李老师",
		lessonTitle: "Spring Cloud实战",
		overallScore: 93,
		atmosphereScore: 94,
		attitudeScore: 96,
		effectScore: 89,
		content: "课程设计合理，循序渐进",
		addTime: "2026-03-27 16:00:00",
	},
];

/** 成功响应 */
function ok<T>(data: T): JsonVO<T> {
	return { code: 10000, message: "success", data };
}

// ==================== Mock 实现 ====================

function mockListLearningEvaluation(query: LearningEvaluationQuery): JsonVO<PageDTO<TeachEvaluationVO>> {
	let filtered = [...mockList];

	if (query.lessonTitle) {
		const keyword = query.lessonTitle.toLowerCase();
		filtered = filtered.filter((item) => item.lessonTitle.toLowerCase().includes(keyword));
	}
	if (query.studentId) {
		filtered = filtered.filter((item, idx) => idx + 1 === query.studentId);
	}
	if (query.teacherId) {
		const teacherNames = ["李老师", "王老师", "赵老师"];
		const name = teacherNames[(query.teacherId - 1) % teacherNames.length];
		filtered = filtered.filter((item) => item.teacherName === name);
	}
	if (query.addTimeStart) {
		filtered = filtered.filter((item) => item.addTime >= query.addTimeStart!);
	}
	if (query.addTimeEnd) {
		filtered = filtered.filter((item) => item.addTime <= query.addTimeEnd!);
	}

	const pageIndex = query.pageIndex || 1;
	const pageSize = query.pageSize || 10;
	const start = (pageIndex - 1) * pageSize;
	const rows = filtered.slice(start, start + pageSize);
	return ok({ pageIndex, pageSize, total: filtered.length, rows });
}

// ==================== 导出（自动切换 Mock/真实 API） ====================

/** 获取学评教列表（条件+分页） */
export const listLearningEvaluation = (query: LearningEvaluationQuery) => {
	if (USE_MOCK) return Promise.resolve(mockListLearningEvaluation(query));
	return http.get<PageDTO<TeachEvaluationVO>>(`${baseUrl}/list`, query);
};
