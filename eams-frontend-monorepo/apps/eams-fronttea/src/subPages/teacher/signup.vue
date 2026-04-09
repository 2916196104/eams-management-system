<script setup lang="ts">
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";

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
}

const userStore = useUserStore();
const { customers, scheduleItems } = storeToRefs(userStore);

const showStudentSheet = ref(false);
const showCourseSheet = ref(false);
const submitting = ref(false);
const courseLoading = ref(false);
const selectedStudentId = ref("");
const selectedCourseId = ref("");

const selectedStudent = computed(() => customers.value.find((item) => String(item.id) === selectedStudentId.value) || null);
const courseOptions = computed<SignupCourseOption[]>(() => {
	const map = new Map<string, SignupCourseOption>();
	for (const item of scheduleItems.value) {
		const id = String(item.courseId || item.id || item.courseName);
		if (!id || map.has(id)) continue;
		map.set(id, {
			id,
			name: item.courseName,
			label: item.className ? `${item.courseName} / ${item.className}` : item.courseName,
		});
	}
	return Array.from(map.values());
});
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
		await userStore.loadScheduleByDate(formatDate(new Date()));
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
		await (Apis as any).workbench.post_workbench_enrollment_save({
			data: {
				name: selectedStudent.value.name,
				studentId: selectedStudent.value.id,
				studentName: selectedStudent.value.name,
				courseId: selectedCourse.value.id,
				courseName: selectedCourse.value.name,
			},
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
