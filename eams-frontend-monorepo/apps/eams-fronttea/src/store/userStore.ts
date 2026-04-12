import { defineStore } from "pinia";

export interface TeacherInfo {
	id: string;
	username: string;
	name: string;
	role: string;
	phone: string;
	organization: string;
	authorities: string[];
}

export interface TeacherQuickAction {
	id: number;
	name: string;
	icon: string;
	route: string;
	routeType: "page" | "tab";
	iconBg: string;
}

export interface TeacherMonthMetric {
	id: number;
	label: string;
	value: number;
}

export interface TeacherScheduleItem {
	id: number | string;
	lessonId?: number | string;
	courseId?: number | string;
	date: string;
	startTime: string;
	endTime: string;
	className: string;
	courseName: string;
	classroom: string;
	lessonCount?: number;
	teacherId?: number | string;
	teacherName?: string;
	classroomId?: number | string;
	isSigned?: boolean;
	isLeave?: boolean;
	isReserved?: boolean;
}

interface TeacherScheduleApiItem {
	id?: number | string;
	lesson_id?: number | string;
	lessonId?: number | string;
	schedule_id?: number | string;
	lesson_date?: string;
	lessonDate?: string;
	schedule_date?: string;
	scheduleDate?: string;
	course_id?: number | string;
	courseId?: number | string;
	date?: string;
	start_time?: string;
	startTime?: string;
	end_time?: string;
	endTime?: string;
	class_name?: string;
	className?: string;
	course_name?: string;
	courseName?: string;
	title?: string;
	teacher_name?: string;
	teacherName?: string;
	classroom_name?: string;
	classroomName?: string;
	classroom?: string;
	lesson_count?: number;
	teacher_id?: number | string;
	classroom_id?: number | string;
	is_signed?: boolean;
	is_leave?: boolean;
	is_reserved?: boolean;
}

interface CurrentUserApiItem {
	id?: number | string;
	ID?: number | string;
	teacherId?: number | string;
	username?: string;
	realName?: string;
	displayName?: string;
	name?: string;
	phone?: string;
	mobile?: string;
	organization?: string;
	organizationName?: string;
	orgName?: string;
	schoolName?: string;
	companyName?: string;
	authorities?: string[];
	permissions?: string[];
	role?: string[];
	roles?: string[];
}

interface TeacherMonthlyDataApiItem {
	id?: number | string;
	class_count?: number;
	classCount?: number;
	checkin_count?: number;
	checkinCount?: number;
	registration_amount?: number;
	registrationAmount?: number;
	new_students?: number;
	newStudents?: number;
}

export interface TeacherCustomer {
	id: string;
	name: string;
	phone: string;
}

interface TeacherCustomerApiItem {
	id?: number | string;
	customerId?: number | string;
	name?: string;
	studentName?: string;
	phone?: string;
	mobile?: string;
}

interface TeacherCustomerPageResult {
	pageIndex: number;
	pages: number;
	total: number;
	rows: TeacherCustomer[];
}

const defaultTeacherInfo: TeacherInfo = {
	id: "",
	username: "",
	name: "教师用户",
	role: "教师",
	phone: "",
	organization: "零壹教务管理系统",
	authorities: [],
};

const quickActions: TeacherQuickAction[] = [
	{ id: 1, name: "课表", icon: "i-carbon:calendar", route: "schedule", routeType: "tab", iconBg: "#2481ff" },
	{ id: 2, name: "报名", icon: "i-carbon:currency", route: "teacherSignup", routeType: "page", iconBg: "#2cc7c3" },
	{ id: 3, name: "班级", icon: "i-carbon:group", route: "class", routeType: "tab", iconBg: "#ff795d" },
	{ id: 4, name: "课程", icon: "i-carbon:catalog", route: "teacherCourseList", routeType: "page", iconBg: "#2aaaf4" },
	{
		id: 5,
		name: "添加学员",
		icon: "i-carbon:user-follow",
		route: "teacherAddStudent",
		routeType: "page",
		iconBg: "#ffbf25",
	},
	{
		id: 6,
		name: "我的客户",
		icon: "i-carbon:user-avatar-filled-alt",
		route: "teacherCustomerList",
		routeType: "page",
		iconBg: "#6f90ff",
	},
	{
		id: 7,
		name: "报名记录",
		icon: "i-carbon:receipt",
		route: "teacherSignupRecord",
		routeType: "page",
		iconBg: "#ca65e3",
	},
	{
		id: 8,
		name: "点名记录",
		icon: "i-carbon:list-checked",
		route: "teacherAttendanceRecord",
		routeType: "page",
		iconBg: "#2cc7c3",
	},
	{ id: 9, name: "作业", icon: "i-carbon:book", route: "teacherHomeworkList", routeType: "page", iconBg: "#2cc7c3" },
	{
		id: 10,
		name: "点评记录",
		icon: "i-carbon:favorite-filled",
		route: "teacherCommentRecord",
		routeType: "page",
		iconBg: "#ff8a5c",
	},
	{ id: 11, name: "排课", icon: "i-carbon:star-filled", route: "teacherScheduling", routeType: "page", iconBg: "#31b4f4" },
	{
		id: 12,
		name: "学生档案",
		icon: "i-carbon:user-profile",
		route: "teacherStudentArchive",
		routeType: "page",
		iconBg: "#ff7b5d",
	},
];

const monthMetrics: TeacherMonthMetric[] = [
	{ id: 1, label: "本月课次", value: 0 },
	{ id: 2, label: "本月点名人次", value: 0 },
	{ id: 3, label: "本月报名", value: 0 },
	{ id: 4, label: "本月点评", value: 0 },
];

function normalizeCurrentUserPayload(source: unknown, currentValue: TeacherInfo) {
	const payload = ((source as any)?.data?.data ?? (source as any)?.data ?? source ?? {}) as CurrentUserApiItem;
	const authorities = Array.isArray(payload.role)
		? payload.role.filter(Boolean)
		: Array.isArray(payload.roles)
			? payload.roles.filter(Boolean)
			: Array.isArray(payload.authorities)
				? payload.authorities.filter(Boolean)
				: Array.isArray(payload.permissions)
					? payload.permissions.filter(Boolean)
					: currentValue.authorities;

	const username = payload.username || currentValue.username;
	const name = payload.realName || payload.displayName || payload.name || username || currentValue.name;
	const role = authorities[0] || currentValue.role || "教师";
	const id = String(payload.teacherId ?? payload.ID ?? payload.id ?? currentValue.id ?? "");
	const phone = payload.mobile || payload.phone || currentValue.phone;
	const organization =
		payload.organization ||
		payload.organizationName ||
		payload.orgName ||
		payload.schoolName ||
		payload.companyName ||
		currentValue.organization;

	return {
		...currentValue,
		id,
		username,
		name,
		role,
		phone,
		organization,
		authorities,
	};
}

function normalizeMonthMetrics(source: unknown, currentValue: TeacherMonthMetric[]) {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source ?? [];
	const rawRows = Array.isArray(payload)
		? payload
		: Array.isArray(payload.rows)
			? payload.rows
			: Array.isArray(payload.list)
				? payload.list
				: [];

	const total = rawRows.reduce(
		(
			result: { classCount: number; checkinCount: number; registrationAmount: number; newStudents: number },
			item: TeacherMonthlyDataApiItem,
		) => {
			result.classCount += Number(item.class_count ?? item.classCount ?? 0);
			result.checkinCount += Number(item.checkin_count ?? item.checkinCount ?? 0);
			result.registrationAmount += Number(item.registration_amount ?? item.registrationAmount ?? 0);
			result.newStudents += Number(item.new_students ?? item.newStudents ?? 0);
			return result;
		},
		{ classCount: 0, checkinCount: 0, registrationAmount: 0, newStudents: 0 },
	);

	return currentValue.map((item) => {
		if (item.id === 1) return { ...item, value: total.classCount };
		if (item.id === 2) return { ...item, value: total.checkinCount };
		if (item.id === 3) return { ...item, value: total.registrationAmount };
		if (item.id === 4) return { ...item, label: "本月新增学员", value: total.newStudents };
		return item;
	});
}

function normalizeDateValue(value: unknown, fallbackDate: string) {
	if (typeof value !== "string" || !value.trim()) return fallbackDate;

	const trimmed = value.trim();
	const matched = trimmed.match(/\d{4}[-/]\d{1,2}[-/]\d{1,2}/);
	if (!matched) return trimmed;

	return matched[0]
		.split(/[/-]/)
		.map((part, index) => (index === 0 ? part : part.padStart(2, "0")))
		.join("-");
}

function extractScheduleRows(payload: any): unknown[] {
	if (Array.isArray(payload)) return payload;
	if (!payload || typeof payload !== "object") return [];

	// 优先从 payload.data.lessons 中提取课程列表（符合 API 文档结构）
	if (payload.data && Array.isArray(payload.data.lessons)) {
		return payload.data.lessons;
	}

	const directCandidates = [
		payload.data,
		payload.rows,
		payload.list,
		payload.records,
		payload.items,
		payload.result,
		payload.courseList,
		payload.course_list,
		payload.scheduleList,
		payload.schedule_list,
	];

	for (const candidate of directCandidates) {
		if (Array.isArray(candidate)) return candidate;
	}

	for (const value of Object.values(payload)) {
		if (Array.isArray(value)) return value;
	}

	return [];
}

function normalizeCustomerPagePayload(source: unknown): TeacherCustomerPageResult {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source ?? {};
	const rawRows = Array.isArray(payload)
		? payload
		: Array.isArray(payload.rows)
			? payload.rows
			: Array.isArray(payload.list)
				? payload.list
				: Array.isArray(payload.records)
					? payload.records
					: [];

	const rows = rawRows.map((item: TeacherCustomerApiItem, index: number) => {
		return {
			id: String(item.id ?? item.customerId ?? `customer-${index}`),
			name: item.name || item.studentName || `客户${index + 1}`,
			phone: item.phone || item.mobile || "--",
		} satisfies TeacherCustomer;
	});

	return {
		pageIndex: Number(payload.pageIndex ?? payload.page_index ?? 1),
		pages: Number(payload.pages ?? payload.total_page ?? (rows.length ? 1 : 0)),
		total: Number(payload.total ?? rows.length),
		rows,
	};
}

function normalizeSchedulePayload(payload: unknown, fallbackDate: string): TeacherScheduleItem[] {
	const rawList = extractScheduleRows(payload);

	return rawList.map((item: unknown, index: number) => {
		const record = item as TeacherScheduleApiItem;
		const date = normalizeDateValue(
			record.date || record.lesson_date || record.lessonDate || record.schedule_date || record.scheduleDate,
			fallbackDate,
		);
		const startTime = record.start_time || record.startTime || "--:--";
		const endTime = record.end_time || record.endTime || "--:--";
		const className = record.class_name || record.className || `班级${index + 1}`;
		const courseName = record.course_name || record.courseName || record.title || "未命名课程";
		const classroom =
			record.classroom_name ||
			record.classroomName ||
			record.classroom ||
			(record.classroom_id ? `教室${record.classroom_id}` : "待分配教室");
		const lessonId = record.lesson_id || record.lessonId || record.id || record.schedule_id;
		const courseId = record.course_id || record.courseId;

		return {
			id: record.id || record.schedule_id || record.course_id || `${date}-${startTime}-${endTime}-${index}`,
			lessonId,
			courseId,
			date,
			startTime,
			endTime,
			className,
			courseName,
			classroom,
			lessonCount: record.lesson_count,
			teacherId: record.teacher_id,
			teacherName: record.teacher_name || record.teacherName,
			classroomId: record.classroom_id,
			isSigned: record.is_signed,
			isLeave: record.is_leave,
			isReserved: record.is_reserved,
		};
	});
}

export const useUserStore = defineStore("user", {
	state: () => {
		return {
			teacherInfo: { ...defaultTeacherInfo },
			quickActions,
			monthMetrics: monthMetrics.map((item) => ({ ...item })),
			scheduleItems: [] as TeacherScheduleItem[],
			customers: [] as TeacherCustomer[],
		};
	},
	getters: {
		getScheduleByDate: (state) => {
			return (date: string) => state.scheduleItems.filter((item) => item.date === date);
		},
	},
	actions: {
		setScheduleItems(date: string, items: TeacherScheduleItem[]) {
			this.scheduleItems = [...this.scheduleItems.filter((item) => item.date !== date), ...items];
		},
		setCustomers(rows: TeacherCustomer[]) {
			this.customers = rows;
		},
		setMonthMetrics(metrics: TeacherMonthMetric[]) {
			this.monthMetrics = metrics;
		},
		async loadCurrentUserInfo() {
			try {
				const response = await (Apis as any).login.get_login_current_user();
				this.teacherInfo = normalizeCurrentUserPayload(response, this.teacherInfo);
			} catch {
				// 当前用户信息失败时保留本地兜底数据，避免工作台直接空白。
			}

			return this.teacherInfo;
		},
		async loadMonthlyMetrics() {
			try {
				const response = await (Apis as any).workbench.get_workbench_monthly_data();
				this.monthMetrics = normalizeMonthMetrics(response, this.monthMetrics);
			} catch {
				this.monthMetrics = monthMetrics.map((item) => ({ ...item }));
			}

			return this.monthMetrics;
		},
		async loadCustomers(pageIndex = 1, pageSize = 20, append = false) {
			try {
				const response = await (Apis as any).workbench.get_workbench_MyCustomers_List({
					params: {
						pageIndex,
						pageSize,
					},
				});

				const payload = normalizeCustomerPagePayload(response);
				if (append) {
					const merged = new Map<string, TeacherCustomer>();
					for (const item of this.customers) merged.set(item.id, item);
					for (const item of payload.rows) merged.set(item.id, item);
					this.customers = Array.from(merged.values());
				} else {
					this.customers = payload.rows;
				}

				return payload;
			} catch {
				if (!append) this.customers = [];
				return {
					pageIndex,
					pages: 0,
					total: 0,
					rows: [] as TeacherCustomer[],
				};
			}
		},
		async loadScheduleByDate(date: string) {
			try {
				const response = await (Apis as any).course.get_course_get_common_datetime({
					params: { date },
				});

				const items = normalizeSchedulePayload(response, date);
				this.setScheduleItems(date, items);
				return items;
			} catch {
				this.setScheduleItems(date, []);
				return [];
			}
		},
	},
});
