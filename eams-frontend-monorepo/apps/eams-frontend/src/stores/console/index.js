import { ref, computed } from "vue";
import { defineStore } from "pinia";
import { getStatisticsApi, getScheduleCalendarApi } from "@/apis/console";
import { useUserStore } from "@/stores/user";
const userStore = useUserStore();

export const useStatisticsStore = defineStore("statistics", () => {
	// ===== state =====
	const statistics = ref({});

	// ===== getters =====
	const totalStudents = computed(() => statistics.value.totalStudents || 0);
	const totalTeachers = computed(() => statistics.value.totalTeachers || 0);
	const totalCourses = computed(() => statistics.value.totalCourses || 0);
	const monthEnrollments = computed(() => statistics.value.monthEnrollments || 0);

	// ===== actions =====
	const fetchStatistics = async () => {
		try {
			const res = await getStatisticsApi();
			statistics.value = res?.data || {};
		} catch (e) {
			console.error("获取统计数据失败", e);
		}
	};

	return {
		statistics,
		totalStudents,
		totalTeachers,
		totalCourses,
		monthEnrollments,
		fetchStatistics,
	};
});
export const useScheduleStore = defineStore("schedule", () => {
	/* =========================
	   state
	========================= */
	// 我的课表
	const myLessonList = ref([]);
	// 全部课表
	const allLessonList = ref([]);
	// 当前查询参数
	const query = ref({
		userId: 0,
		className: "",
		classroomName: "",
		courseName: "",
		subjectName: "",
		teacherName: "",
		startDate: "",
		endDate: "",
		pageIndex: 1,
		pageSize: 100,
		period: "month",
		viewType: 1, // 1月 2周 3日
	});

	// 加载状态
	const loading = ref(false);
	/* =========================
	   actions
	========================= */
	// 获取我的课表
	const fetchMySchedule = async () => {
		loading.value = true;
		try {
			const res = await getScheduleCalendarApi({
				...query.value,
				userId: userStore.user.id,
			});
			myLessonList.value = res?.data || [];
		} finally {
			loading.value = false;
		}
	};
	// 获取全部课表
	const fetchAllSchedule = async () => {
		loading.value = true;
		try {
			const res = await getScheduleCalendarApi({
				...query.value,
			});
			allLessonList.value = res?.data || [];
		} finally {
			loading.value = false;
		}
	};
	// 更新查询参数
	const updateQuery = (params) => {
		query.value = {
			...query.value,
			...params,
		};
	};
	/* =========================
	   数据处理（非常重要）
	========================= */
	// 根据日期分组
	const buildEventMap = (list) => {
		const map = new Map();
		list.forEach((item) => {
			const date = item.Date;
			if (!map.has(date)) {
				map.set(date, []);
			}
			map.get(date).push(item);
		});
		return map;
	};
	// 我的课表 Map
	const myEventMap = computed(() => buildEventMap(myLessonList.value));
	// 全部课表 Map
	const allEventMap = computed(() => buildEventMap(allLessonList.value));
	/* =========================
	   工具函数
	========================= */
	const parseTimeToHour = (time) => {
		if (!time) return 0;
		return Number(time.split(":")[0]);
	};
	function formatDate(date) {
		const y = date.getFullYear();
		const m = String(date.getMonth() + 1).padStart(2, "0");
		const d = String(date.getDate()).padStart(2, "0");
		return `${y}-${m}-${d}`;
	}
	/* =========================
	   对外提供的方法
	========================= */
	const getMonthEvents = (date, type = "my") => {
		const d = formatDate(date);
		const map = type === "my" ? myEventMap.value : allEventMap.value;
		return map.get(d) || [];
	};
	const getWeekEvents = (date, hour, type = "my") => {
		const d = formatDate(date);
		const map = type === "my" ? myEventMap.value : allEventMap.value;
		const list = map.get(d) || [];
		return list.filter((item) => parseTimeToHour(item.startTime) === hour);
	};
	const getDayEvents = (date, hour, type = "my") => {
		const d = formatDate(date);
		const map = type === "my" ? myEventMap.value : allEventMap.value;
		const list = map.get(d) || [];
		return list.filter((item) => parseTimeToHour(item.startTime) === hour);
	};
	return {
		// state
		myLessonList,
		allLessonList,
		query,
		loading,
		// actions
		fetchMySchedule,
		fetchAllSchedule,
		updateQuery,
		// events
		getMonthEvents,
		getWeekEvents,
		getDayEvents,
	};
});
