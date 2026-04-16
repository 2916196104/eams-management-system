<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { Apis } from "@/api";
import { useGlobalToast } from "@/composables/useGlobalToast";
import { useRouter, useRoute } from "vue-router";

definePage({
	name: "teacherAddStudent",
	style: {
		navigationBarTitleText: "添加学员",
		titleNView: false,
	},
});

interface StudentOption {
	id: string;
	name: string;
	phone: string;
	gender: string;
	restHour: number;
}

const router = useRouter();
const route = useRoute() as { query?: Record<string, string | string[] | undefined> };
const toast = useGlobalToast();

const searchKeyword = ref("");
const loading = ref(false);
const loadingMore = ref(false);
const submitting = ref(false);
const courseLoadingIds = ref<string[]>([]);
const pageIndex = ref(1);
const pages = ref(0);
const total = ref(0);
const students = ref<StudentOption[]>([]);
const selectedStudentIds = ref<string[]>([]);
const studentCourseMap = ref<Record<string, string[]>>({});

const studentForm = reactive({
	name: "",
	phone: "",
	type: "意向学员",
	gender: "未知",
	birthday: "",
	idCard: "",
	remark: "",
	userName: "",
	kinship: 1,
	stage: 0,
	admitTime: "",
	grade: 1,
	schoolId: 0,
});

const genderOptions = ["未知", "男", "女"];
const typeOptions = ["意向学员", "在学学员"];
const kinshipOptions = [
	{ label: "父亲", value: 1 },
	{ label: "母亲", value: 0 }
];

const gradeOptions = [
	{ label: "一年级", value: 1 },
	{ label: "二年级", value: 2 },
	{ label: "三年级", value: 3 },
	{ label: "四年级", value: 4 },
	{ label: "五年级", value: 5 },
	{ label: "六年级", value: 6 },
	{ label: "初一", value: 7 },
	{ label: "初二", value: 8 },
	{ label: "初三", value: 9 },
	{ label: "高一", value: 10 },
	{ label: "高二", value: 11 },
	{ label: "高三", value: 12 }
];

const isSelectMode = computed(() => readQuery("mode") === "select" || !!readQuery("lesson_id"));
const pageTitle = computed(() => (isSelectMode.value ? "添加学员" : "添加意向学员"));
const lessonId = computed(() => readQuery("lesson_id"));
const courseId = computed(() => readQuery("course_id"));
const hasMore = computed(() => pageIndex.value < pages.value);

function readQuery(key: string) {
	const value = route.query?.[key];
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

function normalizeStudentsPayload(source: any) {
	const payload = source?.data?.data ?? source?.data ?? source ?? {};
	const rows = Array.isArray(payload.rows)
		? payload.rows
		: Array.isArray(payload.list)
			? payload.list
			: Array.isArray(payload.records)
				? payload.records
				: [];

	return {
		pageIndex: Number(payload.pageIndex ?? payload.page_index ?? 1),
		pages: Number(payload.pages ?? payload.total_page ?? 0),
		total: Number(payload.total ?? rows.length),
		rows: rows.map((item: any) => {
			return {
				id: String(item.id ?? ""),
				name: item.name ?? "未命名学员",
				phone: item.phone ?? "--",
				gender: item.gender ?? "",
				restHour: Number(item.rest_hour ?? item.restHour ?? 0),
			} satisfies StudentOption;
		}),
	};
}

function genderText(value: string) {
	if (value === "1" || value === "男") return "男";
	if (value === "2" || value === "女") return "女";
	return "未知";
}

function hasStudentCourses(id: string) {
	return Object.prototype.hasOwnProperty.call(studentCourseMap.value, id);
}

function isCourseLoading(id: string) {
	return courseLoadingIds.value.includes(id);
}

function studentTypeValue(type: string) {
	return type === "在学学员" ? 2147483641 : 2147483640;
}

function studentGenderValue(gender: string) {
	if (gender === "男") return 1;
	if (gender === "女") return 0;
	return 3;
}

async function loadStudentCourses(id: string) {
	if (!id || hasStudentCourses(id) || isCourseLoading(id)) return;

	courseLoadingIds.value = [...courseLoadingIds.value, id];
	try {
		const res: any = await (Apis as any).course.get_course_record_name_stu_course_list({
			params: {
				id,
			},
		});

		const payload = res?.data?.data ?? res?.data ?? [];
		studentCourseMap.value = {
			...studentCourseMap.value,
			[id]: Array.isArray(payload) ? payload.filter((item) => typeof item === "string" && item) : [],
		};
	} catch {
		studentCourseMap.value = {
			...studentCourseMap.value,
			[id]: [],
		};
		uni.showToast({ title: "学员课程加载失败", icon: "none" });
	} finally {
		courseLoadingIds.value = courseLoadingIds.value.filter((item) => item !== id);
	}
}

async function loadStudents(nextPage = 1, append = false) {
	if (!isSelectMode.value) return;

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await (Apis as any).course.get_course_record_name_stu_list({
			params: {
				keyword: searchKeyword.value || undefined,
				pageIndex: nextPage,
				pageSize: 10,
			},
		});

		const payload = normalizeStudentsPayload(res);
		pageIndex.value = payload.pageIndex;
		pages.value = payload.pages;
		total.value = payload.total;
		students.value = append ? [...students.value, ...payload.rows] : payload.rows;
	} catch {
		if (!append) students.value = [];
		uni.showToast({ title: "学员列表加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function refreshStudents() {
	await loadStudents(1, false);
	if (isSelectMode.value) {
		uni.showToast({ title: "已刷新", icon: "none" });
	}
}

async function loadMoreStudents() {
	if (!hasMore.value || loadingMore.value) return;
	await loadStudents(pageIndex.value + 1, true);
}

function toggleStudent(id: string) {
	const set = new Set(selectedStudentIds.value);
	if (set.has(id)) {
		set.delete(id);
	} else {
		set.add(id);
		void loadStudentCourses(id);
	}
	selectedStudentIds.value = Array.from(set);
}

async function submitSelection() {
	if (!selectedStudentIds.value.length) {
		uni.showToast({ title: "请先选择学员", icon: "none" });
		return;
	}

	if (!courseId.value) {
		uni.showToast({ title: "缺少课程ID，无法提交", icon: "none" });
		return;
	}

	submitting.value = true;
	try {
		await (Apis as any).course.post_course_record_name_stu_add_to_cs({
			data: {
				course_id: courseId.value,
				studentIds: selectedStudentIds.value,
			},
		});

		uni.showToast({ title: "添加学员成功", icon: "none" });
		const timer = setTimeout(() => {
			clearTimeout(timer);
			router.back();
		}, 500);
	} catch {
		uni.showToast({ title: "添加学员失败", icon: "none" });
	} finally {
		submitting.value = false;
	}
}

async function submitForm() {
	if (!studentForm.name.trim()) {
		toast.show("请输入学员姓名");
		return;
	}

	if (!studentForm.phone.trim()) {
		toast.show("请输入手机号");
		return;
	}

	

	submitting.value = true;
	try {
		const response = await (Apis as any).workbench.post_workbench_add_student_info({
			data: {
					name: studentForm.name.trim(),
					phonenumber: studentForm.phone.trim(),
					stage: Number(studentForm.stage) || 0,
					gender: studentGenderValue(studentForm.gender),
					birthday: studentForm.birthday.trim() || undefined,
					idcard: studentForm.idCard.trim() || undefined,
					remark: studentForm.remark.trim() || undefined,
					username: studentForm.userName.trim() || undefined,
					kinship: Number(studentForm.kinship) || 2147483640,
					admitTime: studentForm.admitTime.trim() || new Date().toISOString(),
					grade: Number(studentForm.grade) || studentTypeValue(studentForm.type),
					schoolId: Number(studentForm.schoolId) || 0,
				},
		});

		console.log("添加学员响应:", response);
		uni.showToast({ title: "添加学员成功", icon: "none" });
		const timer = setTimeout(() => {
			clearTimeout(timer);
			router.back();
		}, 500);
	} catch (error) {
		console.error("添加学员失败:", error);
		uni.showToast({ title: "添加学员失败", icon: "none" });
	} finally {
		submitting.value = false;
	}
}

onShow(() => {
	if (isSelectMode.value) {
		void loadStudents(1, false);
	}
});
</script>

<template>
	<view class="teacher-add-page">
		<teacher-nav-bar :title="pageTitle" :show-refresh="isSelectMode" @refresh="refreshStudents" />

		<template v-if="isSelectMode">
			<view class="teacher-select-panel">
				<view class="teacher-select-panel__tip">当前课次 ID：{{ lessonId || "--" }}</view>
				<view class="teacher-select-panel__tip">当前课程 ID：{{ courseId || "--" }}</view>
				<view class="teacher-select-search">
					<input
						v-model="searchKeyword"
						class="teacher-select-search__input"
						type="text"
						placeholder="搜索学员姓名或手机号"
						confirm-type="search"
						@confirm="refreshStudents"
					/>
					<view class="teacher-select-search__button" @click="refreshStudents">搜索</view>
				</view>
			</view>

			<view v-if="students.length" class="teacher-select-list">
				<view
					v-for="item in students"
					:key="item.id"
					class="teacher-select-item"
					:class="{ 'teacher-select-item--active': selectedStudentIds.includes(item.id) }"
					@click="toggleStudent(item.id)"
				>
					<view class="teacher-select-item__main">
						<view>
							<view class="teacher-select-item__name">{{ item.name }}</view>
							<view class="teacher-select-item__meta">{{ item.phone }} / {{ genderText(item.gender) }}</view>
						</view>
						<view class="teacher-select-item__rest">剩余课时 {{ item.restHour }}</view>
					</view>

					<view v-if="selectedStudentIds.includes(item.id)" class="teacher-select-item__courses">
						<text class="teacher-select-item__courses-title">学员课程</text>
						<view v-if="isCourseLoading(item.id)" class="teacher-select-item__courses-loading">课程加载中...</view>
						<view v-else-if="studentCourseMap[item.id]?.length" class="teacher-select-item__course-tags">
							<view v-for="course in studentCourseMap[item.id]" :key="course" class="teacher-select-item__course-tag">
								{{ course }}
							</view>
						</view>
						<view v-else class="teacher-select-item__courses-empty">暂无课程信息</view>
					</view>
				</view>
			</view>

			<teacher-empty-state v-else :title="loading ? '加载中...' : '暂无学员记录'" compact />

			<view v-if="hasMore" class="teacher-select-more" @click="loadMoreStudents">
				{{ loadingMore ? "加载中..." : "加载更多学员" }}
			</view>

			<view class="teacher-add-action">
				<wd-button type="primary" block :loading="submitting" @click="submitSelection">确认添加</wd-button>
			</view>
		</template>

		<template v-else>
			<view class="teacher-add-card">
				<view class="teacher-add-row">
					<text class="teacher-add-label">学员姓名</text>
					<input v-model="studentForm.name" class="teacher-add-input" type="text" placeholder="必填" />
				</view>
				<view class="teacher-add-row">
					<text class="teacher-add-label">手机号码</text>
					<input v-model="studentForm.phone" class="teacher-add-input" type="number" placeholder="用于登录学生端的账号" />
				</view>
				<view class="teacher-add-row teacher-add-row--block">
					<text class="teacher-add-label">学生类型</text>
					<view class="teacher-add-options">
						<view
							v-for="option in typeOptions"
							:key="option"
							class="teacher-add-radio"
							:class="{ 'teacher-add-radio--active': studentForm.type === option }"
							@click="studentForm.type = option"
						>
							{{ option }}
						</view>
					</view>
				</view>
				<view class="teacher-add-row teacher-add-row--block">
					<text class="teacher-add-label">选择性别</text>
					<view class="teacher-add-options">
						<view
							v-for="option in genderOptions"
							:key="option"
							class="teacher-add-radio"
							:class="{ 'teacher-add-radio--active': studentForm.gender === option }"
							@click="studentForm.gender = option"
						>
							{{ option }}
						</view>
					</view>
				</view>
				<view class="teacher-add-row">
					<text class="teacher-add-label">出生年月</text>
					<input v-model="studentForm.birthday" class="teacher-add-input" type="text" placeholder="YY-MM-DD" />
				</view>
				<view class="teacher-add-row">
					<text class="teacher-add-label">身份证号</text>
					<input v-model="studentForm.idCard" class="teacher-add-input" type="text" placeholder="请输入内容" />
				</view>
				<view class="teacher-add-row">
					<text class="teacher-add-label">家长姓名</text>
					<input v-model="studentForm.userName" class="teacher-add-input" type="text" placeholder="请输入内容" />
				</view>
				<view class="teacher-add-row teacher-add-row--block">
					<text class="teacher-add-label">亲属关系</text>
					<view class="teacher-add-options">
						<view
							v-for="option in kinshipOptions"
							:key="option.value"
							class="teacher-add-radio"
							:class="{ 'teacher-add-radio--active': studentForm.kinship === option.value }"
							@click="studentForm.kinship = option.value"
						>
							{{ option.label }}
						</view>
					</view>
				</view>

				<view class="teacher-add-row">
					<text class="teacher-add-label">入学时间</text>
					<input v-model="studentForm.admitTime" class="teacher-add-input" type="text" placeholder="YY-MM-DD" />
				</view>
				<view class="teacher-add-row teacher-add-row--block">
					<text class="teacher-add-label">年级</text>
					<view class="teacher-add-options">
						<view
							v-for="option in gradeOptions"
							:key="option.value"
							class="teacher-add-radio"
							:class="{ 'teacher-add-radio--active': studentForm.grade === option.value }"
							@click="studentForm.grade = option.value"
						>
							{{ option.label }}
						</view>
					</view>
				</view>

				<view class="teacher-add-row teacher-add-row--block">
					<text class="teacher-add-label">备注信息</text>
					<textarea v-model="studentForm.remark" class="teacher-add-textarea" placeholder="请输入内容" />
				</view>
			</view>

			<view class="teacher-add-action">
				<wd-button type="primary" block :loading="submitting" @click="submitForm">提交</wd-button>
			</view>
		</template>
	</view>
</template>

<style scoped>
.teacher-add-page {
	min-height: 100vh;
	padding-bottom: calc(env(safe-area-inset-bottom) + 96px);
	background: #f5f6fa;
}

.teacher-select-panel {
	margin-top: 10px;
	padding: 14px 16px;
	background: #fff;
}

.teacher-select-panel__tip {
	margin-top: 4px;
	font-size: 13px;
	color: #667085;
}

.teacher-select-search {
	display: flex;
	align-items: center;
	gap: 10px;
	margin-top: 14px;
}

.teacher-select-search__input {
	flex: 1;
	height: 40px;
	border-radius: 999px;
	background: #f5f7fb;
	padding: 0 14px;
	font-size: 14px;
	color: #344054;
}

.teacher-select-search__button {
	flex-shrink: 0;
	border-radius: 999px;
	background: #31c7a5;
	padding: 10px 16px;
	font-size: 13px;
	font-weight: 600;
	color: #fff;
}

.teacher-select-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
	padding: 12px;
}

.teacher-select-item {
	border-radius: 16px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.05);
}

.teacher-select-item--active {
	outline: 2px solid rgba(49, 199, 165, 0.22);
}

.teacher-select-item__main {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.teacher-select-item__name {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.teacher-select-item__meta {
	margin-top: 6px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-select-item__rest {
	flex-shrink: 0;
	border-radius: 999px;
	background: rgba(49, 199, 165, 0.1);
	padding: 6px 10px;
	font-size: 12px;
	color: #1ca386;
}

.teacher-select-item__courses {
	margin-top: 14px;
	border-top: 1px solid #eef1f6;
	padding-top: 14px;
}

.teacher-select-item__courses-title {
	display: block;
	margin-bottom: 10px;
	font-size: 13px;
	font-weight: 600;
	color: #344054;
}

.teacher-select-item__courses-loading,
.teacher-select-item__courses-empty {
	font-size: 13px;
	color: #98a2b3;
}

.teacher-select-item__course-tags {
	display: flex;
	flex-wrap: wrap;
	gap: 8px;
}

.teacher-select-item__course-tag {
	border-radius: 999px;
	background: #f5f7fb;
	padding: 6px 10px;
	font-size: 12px;
	color: #475467;
}

.teacher-select-more {
	margin: 0 12px;
	height: 40px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	background: #fff;
	font-size: 14px;
	font-weight: 600;
	color: #31c7a5;
}

.teacher-add-card {
	margin-top: 10px;
	background: #fff;
}

.teacher-add-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 14px;
	padding: 16px;
	border-bottom: 1px solid #edf0f5;
}

.teacher-add-row--block {
	align-items: flex-start;
	flex-direction: column;
}

.teacher-add-label {
	font-size: 15px;
	color: #111827;
}

.teacher-add-input {
	flex: 1;
	min-width: 0;
	text-align: right;
	font-size: 15px;
	color: #344054;
}

.teacher-add-options {
	display: flex;
	flex-wrap: wrap;
	gap: 10px;
}

.teacher-add-radio {
	border-radius: 999px;
	border: 1px solid #d9e0ec;
	padding: 7px 14px;
	font-size: 13px;
	color: #667085;
}

.teacher-add-radio--active {
	border-color: #31c7a5;
	background: rgba(49, 199, 165, 0.1);
	color: #1ca386;
}

.teacher-add-textarea {
	width: 100%;
	min-height: 96px;
	box-sizing: border-box;
	border-radius: 14px;
	background: #f8fafc;
	padding: 12px 14px;
	font-size: 14px;
	color: #344054;
}

.teacher-add-action {
	position: fixed;
	right: 12px;
	bottom: calc(env(safe-area-inset-bottom) + 18px);
	left: 12px;
}
</style>
