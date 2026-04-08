import { ref, computed } from "vue";
import { defineStore } from "pinia";
import {
	getStatisticsApi,
	getScheduleCalendarApi,
	getCourseDetailApi,
	deleteCoursesApi,
	putCourseStatusApi,
	getTeacherListApi,
	getClassroomListApi,
	getNoticeListApi,
	getMonthlyTrendApi,
	getCourseTop5Api,
	postMyClientApi,
	postMyEnrollmentApi,
	postPaymentApi,
	getPaymentDetailApi,
} from "@/apis/console";
import { useUserStore } from "@/stores/user";
const userStore = useUserStore();

export const useStatisticsStore = defineStore("statistics", () => {
	// ===== state =====
	const statistics = ref({});

	// ===== getters =====
	const totalStudents = computed(() => statistics.value.totalStudents || 0);
	const totalTeachers = computed(() => statistics.value.totalTeachers || 0);
	const totalLessons = computed(() => statistics.value.totalLessons || 0);
	const monthEnrollmentAmount = computed(() => statistics.value.monthEnrollmentAmount || 0);

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
		totalLessons,
		monthEnrollmentAmount,
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
export const useCourseDetailStore = defineStore("courseDetail", () => {
	const courseDetail = ref(null); // 课程详情数据
	const loading = ref(false); // 加载状态
	const error = ref(null); // 错误信息

	// 根据课程ID获取课程详情
	const fetchCourseDetail = async (id) => {
		loading.value = true;
		error.value = null;
		try {
			const res = await getCourseDetailApi(id);
			courseDetail.value = res.data || res; // 根据接口返回调整
		} catch (err) {
			console.error("获取课程详情失败:", err);
			error.value = err.message || "请求失败";
		} finally {
			loading.value = false;
		}
	};
	// 删除课程
	const deleteCourses = async (ids) => {
		try {
			await deleteCoursesApi(ids);
		} catch (err) {
			console.error("删除课程失败:", err);
		}
	};

	// 停止/恢复课程
	const toggleCourseStatus = async (courseIds, isResume) => {
		try {
			await putCourseStatusApi(courseIds, isResume);
		} catch (err) {
			console.error("停止/恢复课程失败:", err);
		}
	};

	return {
		courseDetail,
		loading,
		error,
		fetchCourseDetail,
		deleteCourses,
		toggleCourseStatus,
	};
});
export const useBasicDataStore = defineStore("basicData", () => {
	/* 教师列表 */
	const teacherList = ref([]);
	const teacherLoading = ref(false);

	/* 教室列表 */
	const classroomList = ref([]);
	const classroomLoading = ref(false);

	/* 获取教师列表 */
	const fetchTeacherList = async (params = {}) => {
		try {
			teacherLoading.value = true;
			const res = await getTeacherListApi(params);
			teacherList.value = res.data || [];
		} finally {
			teacherLoading.value = false;
		}
	};

	/* 获取教室列表 */
	const fetchClassroomList = async (params = {}) => {
		try {
			classroomLoading.value = true;
			const res = await getClassroomListApi(params);
			classroomList.value = res.data || [];
		} finally {
			classroomLoading.value = false;
		}
	};

	return {
		teacherList,
		classroomList,
		teacherLoading,
		classroomLoading,
		fetchTeacherList,
		fetchClassroomList,
	};
});
export const useNoticeStore = defineStore("notice", () => {
	/* 公告列表 */
	const noticeList = ref([]);

	/* 分页 */
	const total = ref(0);
	const loading = ref(false);

	/* 查询公告 */
	const fetchNoticeList = async (params = { pageIndex: 1, pageSize: 10 }) => {
		loading.value = true;
		try {
			const res = await getNoticeListApi(params);

			noticeList.value = res.data.rows || [];
			total.value = res.data.total || 0;
		} finally {
			loading.value = false;
		}
	};

	return {
		noticeList,
		total,
		loading,
		fetchNoticeList,
	};
});
export const useEchartsStore = defineStore("echarts", () => {
	/* ===== 本月报名走势 ===== */
	const monthlyTrend = ref([]);
	const trendLoading = ref(false);

	// 给图表用的数据
	const trendXAxis = ref([]);
	const trendSeries = ref([]);

	const fetchMonthlyTrend = async (params = {}) => {
		trendLoading.value = true;
		try {
			const res = await getMonthlyTrendApi(params);
			const list = res.data || [];

			monthlyTrend.value = list;

			// ===== 转换为 echarts 数据 =====
			trendXAxis.value = list.map((item) => formatDate(item.date));

			trendSeries.value = [
				{
					name: "报名人数",
					data: list.map((item) => item.totalCount || 0),
					color: "#5470c6",
				},
			];
		} finally {
			trendLoading.value = false;
		}
	};

	/* ===== 课程报名 Top5 ===== */
	const barXAxis = ref([]);
	const barSeries = ref([]);
	const top5Loading = ref(false);

	const fetchCourseTop5 = async (params = {}) => {
		top5Loading.value = true;
		try {
			const res = await getCourseTop5Api(params);
			const list = res.data || [];

			barXAxis.value = list.map((item) => item.courseName || "");
			barSeries.value = [
				{
					name: "报名人数",
					data: list.map((item) => item.totalCount || 0),
					color: "#5470c6",
				},
			];
		} finally {
			top5Loading.value = false;
		}
	};

	return {
		monthlyTrend,
		trendXAxis,
		trendSeries,
		trendLoading,
		fetchMonthlyTrend,

		barXAxis,
		barSeries,
		top5Loading,
		fetchCourseTop5,
	};
});
export const useClientStore = defineStore("client", () => {
	// 表格数据
	const tableData = ref([]);
	const total = ref(0);
	const loading = ref(false);

	// 查询条件
	const query = ref({
		name: "",
		pageNum: 1,
		pageSize: 10,
	});

	// 获取列表
	const fetchList = async (query) => {
		loading.value = true;
		try {
			const res = await postMyClientApi(query);
			tableData.value = res.data.list || [];
			total.value = res.data.total || 0;
		} catch (err) {
			console.error(err);
		} finally {
			loading.value = false;
		}
	};

	return {
		tableData,
		total,
		loading,
		query,
		fetchList,
	};
});
export const useEnrollmentStore = defineStore("enrollment", () => {
	// 表格数据
	const tableData = ref([]);
	const total = ref(0);
	const loading = ref(false);

	// 查询条件
	const query = ref({
		name: "",
		pageIndex: 1,
		pageSize: 10,
	});

	// 获取列表
	const fetchList = async (query) => {
		loading.value = true;
		try {
			const res = await postMyEnrollmentApi(query);
			tableData.value = res.data.rows || [];
			total.value = res.data.total || 0;
		} catch (err) {
			console.error(err);
		} finally {
			loading.value = false;
		}
	};

	return {
		tableData,
		total,
		loading,
		query,
		fetchList,
	};
});
export const usePaymentStore = defineStore("payment", () => {
	// 表格数据
	const tableData = ref([]);
	const total = ref(0);
	const loading = ref(false);
	const detail = ref({});
	// 查询条件
	const query = ref({
		name: "",
		pageNum: 1,
		pageSize: 10,
	});

	// 获取列表
	const fetchList = async (query) => {
		loading.value = true;
		try {
			const res = await postPaymentApi(query);
			tableData.value = res.data.rows || [];
			total.value = res.data.total || 0;
		} catch (err) {
			console.error(err);
		} finally {
			loading.value = false;
		}
	};
	// 获取请款详情
	const fetchDetail = async (id) => {
		try {
			const res = await getPaymentDetailApi(id);
			detail.value = res.data || {};
			return detail.value;
		} catch (err) {
			console.error("获取请款详情失败", err);
			detail.value = {};
			return {};
		}
	};
	return {
		tableData,
		total,
		loading,
		query,
		fetchList,
		fetchDetail,
	};
});
/* 日期格式化 */
function formatDate(date) {
	if (!date) return "";
	const d = new Date(date);
	const m = String(d.getMonth() + 1).padStart(2, "0");
	const day = String(d.getDate()).padStart(2, "0");
	return `${m}-${day}`;
}
