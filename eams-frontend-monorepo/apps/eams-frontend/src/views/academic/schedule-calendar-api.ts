import { getClassOptions } from "@/apis/academic/class";
import { getCourseList } from "@/apis/course";
import { getTeacherList } from "@/apis/academic/schedule-plan";
import { getClassroomList } from "@/apis/academic/classroom";
import type { SelectOption } from "./schedule-calendar";

// 获取班级选项列表
export async function getClassSelectOptions(searchText?: string): Promise<SelectOption[]> {
	try {
		const res = await getClassOptions({
			pageIndex: 1,
			pageSize: 1000,
			className: searchText,
		});
		if (res.data && res.data.records) {
			return res.data.records.map((item) => ({
				value: item.id,
				label: item.name,
			}));
		}
		return [];
	} catch (error) {
		console.error("获取班级列表失败:", error);
		return [];
	}
}

// 获取课程选项列表
export async function getCourseSelectOptions(searchText?: string): Promise<SelectOption[]> {
	try {
		const res = await getCourseList({
			pageIndex: 1,
			pageSize: 1000,
			courseName: searchText,
		});
		if (res.data && res.data.rows) {
			return res.data.rows.map((item) => ({
				value: item.id!,
				label: item.name || "未命名课程",
			}));
		}
		return [];
	} catch (error) {
		console.error("获取课程列表失败:", error);
		return [];
	}
}

// 获取教师选项列表
export async function getTeacherSelectOptions(searchText?: string): Promise<SelectOption[]> {
	try {
		const res = await getTeacherList({
			pageIndex: 1,
			pageSize: 1000,
			teacherName: searchText,
		});
		if (res.data && res.data.records) {
			return res.data.records.map((item: any) => ({
				value: item.id,
				label: item.teacherName || item.name || "未命名教师",
			}));
		}
		return [];
	} catch (error) {
		console.error("获取教师列表失败:", error);
		return [];
	}
}

// 获取教室选项列表
export async function getClassroomSelectOptions(searchText?: string): Promise<SelectOption[]> {
	try {
		const res = await getClassroomList({
			pageIndex: 1,
			pageSize: 1000,
			name: searchText,
		});
		if (res.data && res.data.records) {
			return res.data.records.map((item) => ({
				value: item.id,
				label: item.name,
			}));
		}
		return [];
	} catch (error) {
		console.error("获取教室列表失败:", error);
		return [];
	}
}
