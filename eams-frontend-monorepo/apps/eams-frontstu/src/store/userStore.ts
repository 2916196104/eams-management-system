import { defineStore } from "pinia";

export interface ParentUserInfo {
	id: string;
	nickName: string;
	phone: string;
	sex: string;
	regDate?: string;
}

export interface ParentStudent {
	id: string;
	name: string;
	gender: "男" | "女";
	avatarText: string;
	relation?: string;
	grade?: string;
	idCard?: string;
	birthday?: string;
}

export interface ParentHomeAction {
	id: number;
	name: string;
	icon: string;
	iconColor: string;
	routeName: string;
	redPoint?: number;
}

function getAvatarText(name: string) {
	return (name || "学").trim().charAt(0).toUpperCase() || "学";
}

/**
 * 当前用户信息，包含下面几类数据：
 * 1. 家长基础信息
 * 2. 家长首页功能列表
 * 3. 当前关联学生列表
 */
export const useUserStore = defineStore("user", {
	state: () => ({
		userInfo: {
			id: "1",
			nickName: "tom",
			phone: "18202025732",
			sex: "女",
			regDate: "2026-03-08",
		} as ParentUserInfo,
		students: [
			{
				id: "1",
				name: "jack",
				gender: "男",
				avatarText: "J",
				relation: "妈妈",
				grade: "2027级",
				idCard: "",
				birthday: "2026-03-27",
			},
		] as Array<ParentStudent>,
		currentStudentId: "1",
		parentHomeActions: [
			{ id: 1, name: "试听卡", icon: "i-carbon:bookmark-filled", iconColor: "#ff5b5b", routeName: "trialCard" },
			{ id: 2, name: "班级", icon: "i-carbon:user-multiple", iconColor: "#5b7cff", routeName: "parentClass" },
			{ id: 3, name: "作业", icon: "i-carbon:notebook", iconColor: "#20c3d8", routeName: "homeworkList", redPoint: 0 },
			{ id: 4, name: "成绩", icon: "i-carbon:result", iconColor: "#1c9bf3", routeName: "scoreList", redPoint: 0 },
			{ id: 5, name: "报名记录", icon: "i-carbon:edit", iconColor: "#2fc65a", routeName: "signupRecord" },
			{
				id: 6,
				name: "点评记录",
				icon: "i-carbon:star-filled",
				iconColor: "#ff9d00",
				routeName: "commentRecord",
				redPoint: 0,
			},
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
		setStudents(list: Array<ParentStudent>) {
			this.students = list;
			if (!list.length) {
				this.currentStudentId = "";
				return;
			}
			if (!list.some((item) => item.id === this.currentStudentId)) {
				this.currentStudentId = list[0].id;
			}
		},
		updateUserInfo(payload: Partial<ParentUserInfo>) {
			this.userInfo = {
				...this.userInfo,
				...payload,
			};
		},
		upsertStudent(payload: Partial<ParentStudent> & { id?: string }) {
			const targetId = payload.id || `${Date.now()}`;
			const index = this.students.findIndex((item) => item.id === targetId);
			const nextStudent: ParentStudent = {
				id: targetId,
				name: payload.name?.trim() || "未命名学生",
				gender: payload.gender === "女" ? "女" : "男",
				avatarText: payload.avatarText || getAvatarText(payload.name || "未"),
				relation: payload.relation || "妈妈",
				grade: payload.grade || "",
				idCard: payload.idCard || "",
				birthday: payload.birthday || "",
			};

			if (index >= 0) {
				this.students.splice(index, 1, {
					...this.students[index],
					...nextStudent,
				});
				return targetId;
			}

			this.students.push(nextStudent);
			if (!this.currentStudentId) this.currentStudentId = targetId;
			return targetId;
		},
		removeStudent(id: string) {
			this.students = this.students.filter((item) => item.id !== id);
			if (this.currentStudentId === id) {
				this.currentStudentId = this.students[0]?.id || "";
			}
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
