import { useHttp } from "@/plugins/http";
import type { JsonVO } from "@/apis/type";
import type { PageDTO } from "@/components/mytable/type";
import type { CourseCommentListQuery, CourseCommentVO } from "./type";

const http = useHttp();
const baseUrl = "/j7-interaction/j7-teacher-student";

// ==================== Mock 数据 ====================

const USE_MOCK = true;

/** mock 教师点评列表 */
const mockCourseCommentList: CourseCommentVO[] = [
	{
		serialNumber: 1,
		studentName: "张三",
		courseTitle: "Java基础第1讲",
		score: 95,
		content: "课堂表现优秀，作业完成及时",
		creatorName: "李老师",
		addTime: "2026-03-14 10:00:00",
	},
	{
		serialNumber: 2,
		studentName: "李四",
		courseTitle: "Java基础第2讲",
		score: 88,
		content: "回答问题积极，但作业有些粗心",
		creatorName: "李老师",
		addTime: "2026-03-15 14:30:00",
	},
	{
		serialNumber: 3,
		studentName: "王五",
		courseTitle: "Java基础第3讲",
		score: 76,
		content: "基础薄弱，需要加强练习",
		creatorName: "李老师",
		addTime: "2026-03-16 09:00:00",
	},
	{
		serialNumber: 4,
		studentName: "赵六",
		courseTitle: "Java基础第4讲",
		score: 92,
		content: "代码能力突出，团队协作好",
		creatorName: "王老师",
		addTime: "2026-03-17 11:00:00",
	},
	{
		serialNumber: 5,
		studentName: "孙七",
		courseTitle: "Java基础第5讲",
		score: 85,
		content: "学习态度认真，进度跟上",
		creatorName: "王老师",
		addTime: "2026-03-18 16:00:00",
	},
	{
		serialNumber: 6,
		studentName: "周八",
		courseTitle: "Java基础第1讲",
		score: 90,
		content: "课堂互动积极，逻辑清晰",
		creatorName: "李老师",
		addTime: "2026-03-19 08:30:00",
	},
	{
		serialNumber: 7,
		studentName: "吴九",
		courseTitle: "Java基础第6讲",
		score: 78,
		content: "出勤率一般，需提高主动性",
		creatorName: "王老师",
		addTime: "2026-03-20 10:00:00",
	},
	{
		serialNumber: 8,
		studentName: "郑十",
		courseTitle: "Java基础第2讲",
		score: 96,
		content: "表现非常优异，代码规范",
		creatorName: "李老师",
		addTime: "2026-03-21 13:00:00",
	},
];

/** 成功响应 */
function ok<T>(data: T): JsonVO<T> {
	return { code: 10000, message: "success", data };
}

/** mock 获取教师点评列表 */
function mockListCourseComment(query: CourseCommentListQuery): JsonVO<PageDTO<CourseCommentVO>> {
	let filtered = [...mockCourseCommentList];

	if (query.content) {
		const keyword = query.content.toLowerCase();
		filtered = filtered.filter((item) => item.content.toLowerCase().includes(keyword));
	}
	if (query.courseTitle) {
		const keyword = query.courseTitle.toLowerCase();
		filtered = filtered.filter((item) => item.courseTitle.toLowerCase().includes(keyword));
	}
	if (query.creatorName) {
		const keyword = query.creatorName.toLowerCase();
		filtered = filtered.filter((item) => item.creatorName.toLowerCase().includes(keyword));
	}
	if (query.studentName) {
		const keyword = query.studentName.toLowerCase();
		filtered = filtered.filter((item) => item.studentName.toLowerCase().includes(keyword));
	}
	if (query.studentId) {
		// mock 中无 studentId 字段，按序号模拟
		filtered = filtered.filter((item) => item.serialNumber === query.studentId);
	}
	if (query.creator) {
		filtered = filtered.filter((item) => item.creatorName.includes(`${query.creator}`));
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

/** 获取教师点评列表（条件+分页） */
export const listCourseComment = (query: CourseCommentListQuery) => {
	if (USE_MOCK) return Promise.resolve(mockListCourseComment(query));
	return http.get<PageDTO<CourseCommentVO>>(`${baseUrl}/list`, query);
};
