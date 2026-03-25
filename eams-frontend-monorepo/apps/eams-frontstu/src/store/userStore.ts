import { defineStore } from "pinia";

export interface ParentStudent {
	id: string;
	name: string;
	gender: "男" | "女";
	avatarText: string;
}

export interface ParentHomeAction {
	id: number;
	name: string;
	icon: string;
	iconColor: string;
	routeName: string;
	redPoint?: number;
}

/**
 * 当前用户信息，包含下面数据：
 * 1. 家长基本信息
 * 2. 家长首页功能列表
 * 3. 当前关联学生列表
 */
export const useUserStore = defineStore("user", {
	state: () => ({
		userInfo: {
			id: "1",
			nickName: "家长用户",
			phone: "13800000001",
			sex: "女",
		} as { id: string; nickName: string; phone: string; sex: string },
		students: [
			{
				id: "1",
				name: "jack",
				gender: "男",
				avatarText: "J",
			},
		] as Array<ParentStudent>,
		currentStudentId: "1",
		parentHomeActions: [
			{ id: 1, name: "试听卡", icon: "i-carbon:bookmark-filled", iconColor: "#ff5b5b", routeName: "trialCard" },
			{ id: 2, name: "班级", icon: "i-carbon:user-multiple", iconColor: "#5b7cff", routeName: "parentClass" },
			{ id: 3, name: "作业", icon: "i-carbon:notebook", iconColor: "#20c3d8", routeName: "homeworkList", redPoint: 0 },
			{ id: 4, name: "成绩", icon: "i-carbon:result", iconColor: "#1c9bf3", routeName: "scoreList", redPoint: 0 },
			{ id: 5, name: "报名记录", icon: "i-carbon:edit", iconColor: "#2fc65a", routeName: "signupRecord" },
			{ id: 6, name: "点评记录", icon: "i-carbon:star-filled", iconColor: "#ff9d00", routeName: "commentRecord", redPoint: 0 },
			{ id: 7, name: "上课记录", icon: "i-carbon:calendar", iconColor: "#3979ff", routeName: "attendanceRecord" },
			{ id: 8, name: "积分兑换", icon: "i-carbon:gift", iconColor: "#b35cff", routeName: "pointsMall" },
		] as Array<ParentHomeAction>,
	}),
	getters: {
		currentStudent: (state) => state.students.find((item) => item.id === state.currentStudentId) || state.students[0],
	},
	actions: {
		setCurrentStudent(id: string) {
			this.currentStudentId = id;
		},
		setHomeRedPoints(payload: { homework_count?: number; grade_count?: number; evaluate_count?: number }) {
			this.parentHomeActions = this.parentHomeActions.map((item) => {
				if (item.routeName === "homeworkList") return { ...item, redPoint: payload.homework_count || 0 };
				if (item.routeName === "scoreList") return { ...item, redPoint: payload.grade_count || 0 };
				if (item.routeName === "commentRecord") return { ...item, redPoint: payload.evaluate_count || 0 };
				return item;
			});
		},
	},
});
