<script setup lang="ts">
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { Apis } from "@/api";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "teacherSignup",
	style: {
		navigationBarTitleText: "报名",
		titleNView: false,
	},
});

interface SignupCourseOption {
	id: string;
	name: string;
	label: string;
	courseId?: string;
	className?: string;
	date?: string;
	startTime?: string;
	endTime?: string;
	lessonCount?: number;
	coursePrice?: number;
	discountPrice?: number;
	actualPayment?: number;
	expireDate?: string;
	subjectName?: string;
	subjectId?: number;
}

const userStore = useUserStore();
const { customers, scheduleItems } = storeToRefs(userStore);

const showStudentSheet = ref(false);
const showCourseSheet = ref(false);
const showSubjectSheet = ref(false);
const submitting = ref(false);
const courseLoading = ref(false);
const selectedStudentId = ref("");
const selectedCourseId = ref("");

// 科目选项列表
const subjectOptions = [
	{ id: 1, name: "语文" },
	{ id: 2, name: "数学" },
	{ id: 3, name: "英语" },
	{ id: 4, name: "物理" },
	{ id: 5, name: "化学" },
	{ id: 6, name: "生物" },
	{ id: 7, name: "历史" },
	{ id: 8, name: "地理" },
	{ id: 9, name: "政治" },
	{ id: 10, name: "音乐" },
	{ id: 11, name: "美术" },
	{ id: 12, name: "体育" },
];

const registerForm = reactive({
	reportType: 0,
	stuName: "",
	courseName: "",
	subjectName: "",
	subjectId: 0,
	startDate: "",
	expireDate: "",
	courseHour: 0,
	coursePrice: 0,
	discountPrice: 0,
	actualPayment: 0,
	tip: ""
});

const selectedStudent = computed(() => customers.value.find((item) => String(item.id) === selectedStudentId.value) || null);
const courseOptions = ref<SignupCourseOption[]>([]);
const selectedCourse = computed(() => courseOptions.value.find((item) => item.id === selectedCourseId.value) || null);

function formatDate(date: Date) {
	const year = date.getFullYear();
	const month = String(date.getMonth() + 1).padStart(2, "0");
	const day = String(date.getDate()).padStart(2, "0");
	return `${year}-${month}-${day}`;
}

async function ensureCourseOptions() {
	if (courseOptions.value.length) return;
	courseLoading.value = true;
	try {
		// 从课程列表接口获取课程数据
		const response = await (Apis as any).workbench.get_workbench_courseList({
			params: { pageIndex: 1, pageSize: 100 }
		});
		
		if (response?.data?.courses) {
			courseOptions.value = response.data.courses.map((course: any) => ({
				id: String(course.id),
				name: course.courseName,
				label: course.className ? `${course.courseName} / ${course.className}` : course.courseName,
				courseId: String(course.id),
				className: course.className,
				date: course.startDate,
				startTime: course.startTime,
				endTime: course.endTime,
				lessonCount: course.courseHour,
				coursePrice: course.coursePrice,
				discountPrice: course.discountPrice,
				actualPayment: course.actualPayment,
				expireDate: course.expireDate,
				subjectName: course.subjectName,
				subjectId: course.subjectId,
			}));
		}
	} finally {
		courseLoading.value = false;
	}
}

async function ensureCustomers() {
	if (customers.value.length) return;
	await userStore.loadCustomers(1, 50, false);
}

function openStudentSheet() {
	void ensureCustomers();
	showStudentSheet.value = true;
}

async function openCourseSheet() {
	await ensureCourseOptions();
	showCourseSheet.value = true;
}

function selectStudent(id: string) {
	selectedStudentId.value = id;
	showStudentSheet.value = false;
}

function selectCourse(id: string) {
	selectedCourseId.value = id;
	showCourseSheet.value = false;
	
	// 自动填充表单字段
	const course = courseOptions.value.find((item) => item.id === id);
	if (course) {
		registerForm.courseName = course.name;
		registerForm.startDate = course.date || "";
		registerForm.courseHour = course.lessonCount || 0;
		registerForm.coursePrice = course.coursePrice || 0;
		registerForm.discountPrice = course.discountPrice || 0;
		registerForm.actualPayment = course.actualPayment || 0;
		registerForm.expireDate = course.expireDate || "";
		registerForm.subjectName = course.subjectName || "";
		registerForm.subjectId = course.subjectId || 0;
	}
}

function openSubjectSheet() {
	showSubjectSheet.value = true;
}

function selectSubject(id: number) {
	const subject = subjectOptions.find((item) => item.id === id);
	if (subject) {
		registerForm.subjectId = subject.id;
		registerForm.subjectName = subject.name;
	}
	showSubjectSheet.value = false;
}

function onExpireDateChange(e: any) {
	registerForm.expireDate = e.detail.value;
}

async function refreshPage() {
	await Promise.all([ensureCourseOptions(), ensureCustomers()]);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function submitForm() {
	if (!selectedStudent.value) {
		uni.showToast({ title: "请选择学员", icon: "none" });
		return;
	}

	if (!selectedCourse.value) {
		uni.showToast({ title: "请选择课程", icon: "none" });
		return;
	}

	submitting.value = true;
	try {
		// 更新表单数据
		registerForm.stuName = selectedStudent.value.name;
		registerForm.courseName = selectedCourse.value.name;

		await (Apis as any).workbench.post_workbench_register({
			data: registerForm
		});

		uni.showToast({ title: "报名成功", icon: "none" });
		const timer = setTimeout(() => {
			clearTimeout(timer);
			uni.navigateBack();
		}, 500);
	} catch {
		uni.showToast({ title: "报名失败", icon: "none" });
	} finally {
		submitting.value = false;
	}
}

onShow(() => {
	void Promise.all([ensureCourseOptions(), ensureCustomers()]);
});
</script>

<template>
	<view class="teacher-form-page">
		<teacher-nav-bar title="报名" @refresh="refreshPage" />

		<view class="teacher-form-card">
			<view class="teacher-form-row" @click="openStudentSheet">
				<text class="teacher-form-label">选择学员</text>
				<view class="teacher-form-value-wrap">
					<text class="teacher-form-value" :class="{ 'teacher-form-value--selected': selectedStudent }">
						{{ selectedStudent ? selectedStudent.name : "请选择" }}
					</text>
					<view class="i-carbon:chevron-right text-16px text-#98a2b3" />
				</view>
			</view>

			<view class="teacher-form-row" @click="openCourseSheet">
				<text class="teacher-form-label">选择课程</text>
				<view class="teacher-form-value-wrap">
					<text class="teacher-form-value" :class="{ 'teacher-form-value--selected': selectedCourse }">
						{{ selectedCourse ? selectedCourse.label : courseLoading ? "加载中..." : "请选择" }}
					</text>
					<view class="i-carbon:chevron-right text-16px text-#98a2b3" />
				</view>
			</view>

			<view class="teacher-form-row" @click="openSubjectSheet">
				<text class="teacher-form-label">所属科目</text>
				<view class="teacher-form-value-wrap">
					<text class="teacher-form-value" :class="{ 'teacher-form-value--selected': registerForm.subjectName }">
						{{ registerForm.subjectName || "请选择" }}
					</text>
					<view class="i-carbon:chevron-right text-16px text-#98a2b3" />
				</view>
			</view>

			<view class="teacher-form-row">
				<text class="teacher-form-label">结束日期</text>
				<view class="teacher-form-value-wrap">
					<picker mode="date" :value="registerForm.expireDate" @change="onExpireDateChange">
						<view class="teacher-form-value" :class="{ 'teacher-form-value--selected': registerForm.expireDate }">
							{{ registerForm.expireDate || "请选择结束日期" }}
						</view>
					</picker>
					<view class="i-carbon:chevron-right text-16px text-#98a2b3" />
				</view>
			</view>

			<view class="teacher-form-row">
				<text class="teacher-form-label">备注</text>
				<view class="teacher-form-value-wrap">
					<input v-model="registerForm.tip" class="teacher-form-input" type="text" placeholder="请输入备注" />
				</view>
			</view>
		</view>

		<view class="teacher-form-action">
			<wd-button type="primary" block :loading="submitting" @click="submitForm">提交</wd-button>
		</view>

		<wd-action-sheet
			v-model="showStudentSheet"
			title="选择学员"
			:close-on-click-action="false"
			:close-on-click-modal="true"
		>
			<view class="teacher-sheet">
				<view
					v-for="customer in customers"
					:key="customer.id"
					class="teacher-sheet__item"
					@click="selectStudent(String(customer.id))"
				>
					<view>
						<view class="teacher-sheet__title">{{ customer.name }}</view>
						<view class="teacher-sheet__desc">{{ customer.phone }}</view>
					</view>
					<view v-if="selectedStudentId === String(customer.id)" class="i-carbon:checkmark text-18px text-#31c7a5" />
				</view>
				<view v-if="!customers.length" class="teacher-sheet__empty">暂无学员数据</view>
			</view>
		</wd-action-sheet>

		<wd-action-sheet
			v-model="showCourseSheet"
			title="选择课程"
			:close-on-click-action="false"
			:close-on-click-modal="true"
		>
			<view class="teacher-sheet">
				<view
					v-for="course in courseOptions"
					:key="course.id"
					class="teacher-sheet__item"
					@click="selectCourse(course.id)"
				>
					<view class="teacher-sheet__title">{{ course.label }}</view>
					<view v-if="selectedCourseId === course.id" class="i-carbon:checkmark text-18px text-#31c7a5" />
				</view>
				<view v-if="!courseOptions.length" class="teacher-sheet__empty">暂无课程数据</view>
			</view>
		</wd-action-sheet>

		<wd-action-sheet
			v-model="showSubjectSheet"
			title="选择科目"
			:close-on-click-action="false"
			:close-on-click-modal="true"
		>
			<view class="teacher-sheet">
				<view
					v-for="subject in subjectOptions"
					:key="subject.id"
					class="teacher-sheet__item"
					@click="selectSubject(subject.id)"
				>
					<view class="teacher-sheet__title">{{ subject.name }}</view>
					<view v-if="registerForm.subjectId === subject.id" class="i-carbon:checkmark text-18px text-#31c7a5" />
				</view>
			</view>
		</wd-action-sheet>
	</view>
</template>

<style scoped>
.teacher-form-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-form-card {
	margin-top: 10px;
	background: #fff;
}

.teacher-form-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	padding: 18px 16px;
	border-bottom: 1px solid #edf0f5;
}

.teacher-form-label {
	font-size: 15px;
	color: #111827;
}

.teacher-form-value-wrap {
	display: flex;
	align-items: center;
	gap: 8px;
	min-width: 0;
}

.teacher-form-value {
	max-width: 180px;
	font-size: 15px;
	color: #98a2b3;
	text-align: right;
	overflow: hidden;
	text-overflow: ellipsis;
	white-space: nowrap;
}

.teacher-form-value--selected {
	color: #344054;
}

.teacher-form-input {
	flex: 1;
	min-width: 0;
	font-size: 15px;
	color: #344054;
	text-align: right;
	padding: 0;
}

.teacher-form-action {
	position: fixed;
	right: 12px;
	bottom: calc(env(safe-area-inset-bottom) + 18px);
	left: 12px;
}

.teacher-sheet {
	padding: 0 16px calc(env(safe-area-inset-bottom) + 12px);
}

.teacher-sheet__item {
	display: flex;
	align-items: center;
	justify-content: space-between;
	padding: 14px 0;
	border-bottom: 1px solid #edf0f5;
}

.teacher-sheet__title {
	font-size: 15px;
	color: #111827;
}

.teacher-sheet__desc {
	margin-top: 4px;
	font-size: 12px;
	color: #98a2b3;
}

.teacher-sheet__empty {
	padding: 18px 0;
	text-align: center;
	font-size: 13px;
	color: #98a2b3;
}
</style>
