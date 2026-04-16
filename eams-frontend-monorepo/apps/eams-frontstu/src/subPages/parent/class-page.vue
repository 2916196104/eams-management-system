<script setup lang="ts">
import { computed, ref } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "parentClass",
	style: {
		navigationBarTitleText: "我的班级",
		titleNView: false,
	},
});

interface ClassInfo {
	id?: number;
	class_name?: string;
	teacher_id?: number;
	teacher_name?: string;
	course_id?: number;
	course_name?: string;
	start_date?: string;
	end_date?: string;
	student_count?: number;
	classroom_id?: number;
	classroom_name?: string;
	remark?: string;
}

interface ClassListItem {
	id?: number;
	name?: string;
	course?: string;
	teacher?: string;
	room?: string;
	grade?: string;
	createTime?: string;
	updateTime?: string;
	number?: number;
	courseCount?: number;
	description?: string;
}

interface ClassStudentItem {
	id?: number;
	name?: string;
	gender?: string;
}

const router = useRouter();
const route = useRoute() as any;
const userStore = useUserStore();
const { currentStudent } = storeToRefs(userStore);
const loading = ref(false);
const loadingMore = ref(false);
const classInfo = ref<ClassInfo | null>(null);
const classList = ref<Array<ClassListItem>>([]);
const classStudents = ref<Array<ClassStudentItem>>([]);
const pageIndex = ref(1);
const pageSize = 10;
const pages = ref(0);
const total = ref(0);

const classId = computed(() => {
	const raw = route.query?.class_id || route.query?.classId;
	const value = Number(raw || 0);
	return Number.isFinite(value) && value > 0 ? value : undefined;
});

const courseId = computed(() => {
	const raw = route.query?.course_id || route.query?.courseId;
	const value = Number(raw || 0);
	return Number.isFinite(value) && value > 0 ? value : undefined;
});

const isListMode = computed(() => Boolean(courseId.value) && !classId.value);
const pageTitle = computed(() => (isListMode.value ? "班级列表" : "我的班级"));
const hasMore = computed(() => pageIndex.value < pages.value);
const studentId = computed(() => Number(currentStudent.value?.id || 0));

function normalizeRows(data: any): Array<ClassListItem> {
	const rows = Array.isArray(data?.rows) ? data.rows : [];
	return rows.map((item: any, index: number) => ({
		id: item?.id ?? item?.class_id ?? item?.classId ?? undefined,
		name: item?.class_name ?? item?.className ?? `班级${index + 1}`,
		course: item?.course_name ?? item?.courseName,
		teacher: item?.teacher_name ?? item?.teacherName,
		room: item?.classroom_name ?? item?.classroomName,
		createTime: item?.start_date ?? item?.startDate,
		updateTime: item?.end_date ?? item?.endDate,
		number: item?.student_count ?? item?.studentCount,
		description: item?.remark,
	}));
}

function normalizeStudents(data: any): Array<ClassStudentItem> {
	const rows = Array.isArray(data?.student_list) ? data.student_list : [];
	return rows.map((item: any, index: number) => ({
		id: item?.id ?? item?.student_id ?? item?.studentId ?? index + 1,
		name: item?.name ?? item?.student_name ?? `学员${index + 1}`,
		gender:
			typeof item?.gender === "boolean"
				? item.gender
					? "男"
					: "女"
				: item?.gender,
	}));
}

function studentGenderText(gender?: string) {
	if (!gender) return "未设置";
	if (gender === "男") return "♂";
	if (gender === "女") return "♀";
	return gender;
}

async function loadClassInfo() {
	if (!classId.value) {
		classInfo.value = null;
		return;
	}
	const res: any = await Apis.home.get_home_class_info_query_by_class_id({
		params: {
			class_id: classId.value,
		},
	});
	classInfo.value = res?.data || null;
}

async function loadClassStudents(targetClassId?: number) {
	if (!targetClassId) {
		classStudents.value = [];
		return;
	}

	const res: any = await Apis.home.get_home_class_student_list_query_by_class_id({
		params: {
			class_id: targetClassId,
		},
	});
	classStudents.value = normalizeStudents(res?.data);
}

async function loadClassList(nextPage = 1, append = false) {
	if (!studentId.value) {
		classList.value = [];
		return;
	}

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;
	try {
		const res: any = await (Apis as any).home.get_home_class_page_query_by_student_id({
			params: {
				student_id: studentId.value,
				pageIndex: nextPage,
				pageSize,
			},
		});

		const pageData = res?.data || {};
		const rows = normalizeRows(pageData);
		pageIndex.value = Number(pageData.pageIndex || nextPage);
		pages.value = Number(pageData.pages || 0);
		total.value = Number(pageData.total || 0);
		classList.value = append ? [...classList.value, ...rows] : rows;
	} catch {
		if (!append) classList.value = [];
		uni.showToast({ title: "班级列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function loadPageData() {
	loading.value = true;
	try {
		if (isListMode.value) {
			classInfo.value = null;
			classStudents.value = [];
			await loadClassList(1, false);
			return;
		}

		classList.value = [];
		await loadClassInfo();
		await loadClassStudents(classId.value);
	} catch {
		classInfo.value = null;
		classStudents.value = [];
		uni.showToast({ title: "班级信息加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

async function refreshPage() {
	await loadPageData();
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!isListMode.value || !hasMore.value || loadingMore.value) return;
	await loadClassList(pageIndex.value + 1, true);
}

function openClassDetail(item: ClassListItem) {
	if (!item.id) return;
	router.push({
		path: "/subPages/parent/class-page",
		query: {
			class_id: String(item.id),
		},
	} as any);
}

onMounted(() => {
	loadPageData();
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar :title="pageTitle" :show-refresh="true" @refresh="refreshPage" />
		<view class="page-content">
			<view v-if="isListMode && classList.length" class="class-list-wrap">
				<view class="class-list-summary">共 {{ total }} 个班级</view>
				<view v-for="item in classList" :key="item.id" class="class-list-card" @click="openClassDetail(item)">
					<view class="class-list-card__header">
						<view>
							<view class="class-list-card__title">{{ item.name || "未命名班级" }}</view>
							<view class="class-list-card__sub">{{ item.course || "未设置课程" }}</view>
						</view>
						<view class="i-carbon:chevron-right text-16px text-#c3cad5" />
					</view>

					<view class="class-list-card__grid">
						<view class="class-list-card__item">
							<text>班主任</text>
							<text>{{ item.teacher || "未设置" }}</text>
						</view>
						<view class="class-list-card__item">
							<text>教室</text>
							<text>{{ item.room || "未设置" }}</text>
						</view>
						<view class="class-list-card__item">
							<text>计划开课</text>
							<text>{{ item.createTime || "未设置" }}</text>
						</view>
						<view class="class-list-card__item">
							<text>计划结业</text>
							<text>{{ item.updateTime || "未设置" }}</text>
						</view>
					</view>
				</view>

				<view v-if="hasMore" class="load-more" @click="loadMore">
					{{ loadingMore ? "加载中..." : "加载更多" }}
				</view>
			</view>

			<view v-else-if="!isListMode && classInfo" class="class-card">
				<view class="class-card__hero">
					<view class="class-card__title">{{ classInfo.class_name }}</view>
					<view class="class-card__course">{{ classInfo.course_name }}</view>
				</view>

				<view class="class-card__grid">
					<view class="class-card__item">
						<text class="class-card__label">授课老师</text>
						<text class="class-card__value">{{ classInfo.teacher_name || "未设置" }}</text>
					</view>
					<view class="class-card__item">
						<text class="class-card__label">学生人数</text>
						<text class="class-card__value">{{ classInfo.student_count ?? 0 }} 人</text>
					</view>
					<view class="class-card__item">
						<text class="class-card__label">上课日期</text>
						<text class="class-card__value">{{ classInfo.start_date || "未设置" }}</text>
					</view>
					<view class="class-card__item">
						<text class="class-card__label">结业日期</text>
						<text class="class-card__value">{{ classInfo.end_date || "未设置" }}</text>
					</view>
					<view class="class-card__item">
						<text class="class-card__label">教室名称</text>
						<text class="class-card__value">{{ classInfo.classroom_name || "未设置" }}</text>
					</view>
					<view class="class-card__item">
						<text class="class-card__label">班级 ID</text>
						<text class="class-card__value">{{ classId || "未设置" }}</text>
					</view>
				</view>

				<view class="class-card__remark">
					<view class="class-card__remark-title">排课备注</view>
					<view class="class-card__remark-content">{{ classInfo.remark || "暂无备注" }}</view>
				</view>

				<view class="class-card__students">
					<view class="class-card__students-title">班级学员</view>
					<view v-if="classStudents.length" class="class-card__students-list">
						<view v-for="student in classStudents" :key="student.id" class="class-card__student-item">
							<view class="class-card__student-avatar">{{ student.name?.slice(0, 1) || "学" }}</view>
							<view class="class-card__student-info">
								<view class="class-card__student-name">{{ student.name || "未命名学员" }}</view>
								<view class="class-card__student-gender">{{ studentGenderText(student.gender) }}</view>
							</view>
						</view>
					</view>
					<view v-else class="class-card__students-empty">暂无班级学员</view>
				</view>
			</view>

			<ParentEmptyState
				v-else
				:text="loading ? '加载中...' : isListMode ? '暂无班级列表' : '暂无班级信息'"
				min-height="180px"
			/>
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.page-content {
	padding: 12px;
}

.class-list-wrap {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.class-list-summary {
	padding: 0 2px;
	font-size: 13px;
	color: #8b95a7;
}

.class-list-card {
	padding: 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.class-list-card__header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.class-list-card__title {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.class-list-card__sub {
	margin-top: 6px;
	font-size: 13px;
	color: #6b7280;
}

.class-list-card__grid {
	margin-top: 14px;
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 10px 12px;
}

.class-list-card__item {
	padding: 10px 12px;
	display: flex;
	flex-direction: column;
	gap: 4px;
	border-radius: 12px;
	background: #f8fafc;
	font-size: 12px;
	color: #94a3b8;
}

.class-list-card__item text:last-child {
	font-size: 14px;
	font-weight: 600;
	color: #334155;
}

.class-card {
	border-radius: 18px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
	overflow: hidden;
}

.class-card__hero {
	padding: 20px 18px 18px;
	background: linear-gradient(135deg, #5b7cff 0%, #31c7a5 100%);
}

.class-card__title {
	font-size: 22px;
	font-weight: 700;
	color: #fff;
}

.class-card__course {
	margin-top: 8px;
	font-size: 14px;
	color: rgba(255, 255, 255, 0.9);
}

.class-card__grid {
	padding: 16px;
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 12px;
}

.class-card__item {
	padding: 12px;
	display: flex;
	flex-direction: column;
	gap: 6px;
	border-radius: 14px;
	background: #f8fafc;
}

.class-card__label {
	font-size: 12px;
	color: #94a3b8;
}

.class-card__value {
	font-size: 14px;
	font-weight: 600;
	line-height: 1.6;
	color: #334155;
}

.class-card__remark {
	padding: 0 16px 18px;
}

.class-card__remark-title,
.class-card__students-title {
	font-size: 14px;
	font-weight: 700;
	color: #111827;
}

.class-card__remark-content {
	margin-top: 10px;
	padding: 14px;
	border-radius: 14px;
	background: #f8fafc;
	font-size: 14px;
	line-height: 1.8;
	color: #475569;
	white-space: pre-wrap;
	word-break: break-word;
}

.class-card__students {
	padding: 0 16px 18px;
}

.class-card__students-list {
	margin-top: 10px;
	display: flex;
	flex-direction: column;
	gap: 10px;
}

.class-card__student-item {
	padding: 12px 14px;
	display: flex;
	align-items: center;
	gap: 12px;
	border-radius: 14px;
	background: #f8fafc;
}

.class-card__student-avatar {
	width: 36px;
	height: 36px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 50%;
	background: rgba(49, 199, 165, 0.14);
	font-size: 16px;
	font-weight: 700;
	color: #1ca386;
}

.class-card__student-info {
	display: flex;
	align-items: center;
	gap: 8px;
}

.class-card__student-name {
	font-size: 14px;
	font-weight: 600;
	color: #334155;
}

.class-card__student-gender {
	font-size: 13px;
	color: #64748b;
}

.class-card__students-empty {
	margin-top: 10px;
	padding: 14px;
	border-radius: 14px;
	background: #f8fafc;
	font-size: 13px;
	color: #94a3b8;
}

.load-more {
	height: 40px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	background: #fff;
	font-size: 14px;
	font-weight: 600;
	color: #31c7a5;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}
</style>
