import { ref, computed } from "vue";
import { defineStore } from "pinia";
import type { StatisticsDTO } from "@/apis/console/type";
import { getStatistics } from "@/apis/console";

export const useStatisticsStore = defineStore("statistics", () => {
	// ===== state =====
	const statistics = ref<StatisticsDTO>({});

	// ===== getters =====
	const totalStudents = computed(() => statistics.value.totalStudents || 0);
	const totalTeachers = computed(() => statistics.value.totalTeachers || 0);
	const totalCourses = computed(() => statistics.value.totalCourses || 0);
	const monthEnrollments = computed(() => statistics.value.monthEnrollments || 0);

	// ===== actions =====
	const fetchStatistics = async () => {
		try {
			const res = await getStatistics();
			if (res.data) {
				statistics.value = res.data;
			}
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
