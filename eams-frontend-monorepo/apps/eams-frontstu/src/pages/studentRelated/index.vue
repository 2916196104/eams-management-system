<script setup lang="ts">
import { computed, onMounted, ref } from "vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "studentRelated",
	style: {
		navigationBarTitleText: "学员相关",
		titleNView: false,
	},
});

interface StudentItem {
	id: string | number;
	name: string;
	grade?: string;
}

interface StudentDetailPayload {
	id?: string | number;
	name?: string;
	grade?: string;
}

interface GradeOption {
	label: string;
	value: string;
}

type PickerChangeEvent = {
	detail?: {
		value?: number | string;
	};
};

const userStore = useUserStore();
const studentList = ref<StudentItem[]>([]);
const gradeOptions = ref<GradeOption[]>([]);
const myPoint = ref(0);
const isLoading = ref(false);
const showAddModal = ref(false);
const currentStudentId = ref(String(userStore.currentStudent?.id || ""));
const addForm = ref({
	name: "",
	grade: "",
});

const gradeLabels = computed(() => gradeOptions.value.map((item) => item.label));
const selectedGradeIndex = computed(() => {
	const index = gradeOptions.value.findIndex((item) => item.label === addForm.value.grade);
	return index >= 0 ? index : 0;
});
const studentCount = computed(() => studentList.value.length);
const currentStudent = computed(() => {
	return studentList.value.find((item) => String(item.id) === currentStudentId.value) || studentList.value[0] || null;
});
const currentStudentAvatar = computed(() => getStudentAvatarText(currentStudent.value?.name || "学员"));

function getStudentAvatarText(name: string) {
	return (name || "学").trim().charAt(0).toUpperCase() || "学";
}

function syncStoreStudents(list: StudentItem[]) {
	userStore.setStudents(
		list.map((item) => ({
			id: String(item.id),
			name: item.name,
			gender: "男",
			avatarText: getStudentAvatarText(item.name),
			grade: item.grade || "",
		})),
	);
}

function normalizeStudentList(data: any): StudentItem[] {
	const rows = Array.isArray(data?.rows) ? data.rows : Array.isArray(data) ? data : [];

	return rows.map((item: any, index: number) => ({
		id: item?.id ?? item?.studentId ?? index + 1,
		name: item?.name ?? item?.studentName ?? `学生${index + 1}`,
		grade: item?.grade ?? item?.gradeName ?? "",
	}));
}

function normalizeStudentDetail(raw: any): StudentDetailPayload | null {
	if (!raw) return null;

	let detail = raw;
	if (typeof raw === "string") {
		try {
			detail = JSON.parse(raw);
		}
		catch {
			return {
				id: raw,
			};
		}
	}

	if (typeof detail !== "object" || Array.isArray(detail)) return null;

	return {
		id: detail?.id ?? detail?.studentId ?? detail?.student_id ?? "",
		name: detail?.name ?? detail?.studentName ?? detail?.nickName ?? "",
		grade: detail?.grade ?? detail?.gradeName ?? detail?.grade_level ?? "",
	};
}

function normalizeGradeOptions(data: any): GradeOption[] {
	const rows = Array.isArray(data?.rows) ? data.rows : Array.isArray(data) ? data : [];

	return rows
		.map((item: any) => {
			if (typeof item === "string") {
				return {
					label: item,
					value: item,
				};
			}

			const label = item?.name ?? item?.label ?? item?.grade ?? item?.value ?? "";
			const value = item?.value ?? item?.id ?? label;

			if (!label) return null;
			return {
				label: String(label),
				value: String(value),
			};
		})
		.filter(Boolean) as GradeOption[];
}

function applyCurrentStudentDetail(detail?: StudentDetailPayload | null) {
	if (!detail) return;

	const targetId = String(detail.id || currentStudentId.value || "");
	if (targetId) {
		currentStudentId.value = targetId;
		userStore.setCurrentStudent(targetId);
	}

	const targetName = detail.name?.trim() || "";
	const targetGrade = detail.grade?.trim() || "";
	const hasTarget = studentList.value.some((item) => String(item.id) === targetId);

	if (!hasTarget && (targetId || targetName)) {
		studentList.value.unshift({
			id: targetId || `${Date.now()}`,
			name: targetName || "当前学员",
			grade: targetGrade,
		});
	}
	else if (targetId) {
		studentList.value = studentList.value.map((item) => {
			if (String(item.id) !== targetId) return item;

			return {
				...item,
				name: targetName || item.name,
				grade: targetGrade || item.grade,
			};
		});
	}

	syncStoreStudents(studentList.value);
}

async function loadCurrentStudentDetail(studentId?: string | number) {
	const targetId = String(studentId ?? currentStudentId.value ?? userStore.currentStudent?.id ?? "");
	if (!targetId) return;

	try {
		const res: any = await Apis.me.get_me_currentStudentQueryOne({
			params: {
				id: targetId,
			},
		});
		applyCurrentStudentDetail(normalizeStudentDetail(res?.data));
	}
	catch (error) {
		console.error("获取当前学员详情失败:", error);
	}
}

async function loadStudentList() {
	isLoading.value = true;
	try {
		const res: any = await Apis.me.get_me_getStudentList({
			params: {
				pageIndex: 1,
				pageSize: 50,
			},
		});
		studentList.value = normalizeStudentList(res?.data);
		syncStoreStudents(studentList.value);

		const hasCurrentStudent = studentList.value.some((item) => String(item.id) === currentStudentId.value);
		if (!hasCurrentStudent) {
			currentStudentId.value = studentList.value.length ? String(studentList.value[0].id) : "";
			if (currentStudentId.value) {
				userStore.setCurrentStudent(currentStudentId.value);
			}
		}
	}
	catch (error) {
		console.error("获取学员列表失败:", error);
		uni.showToast({
			title: "学员列表加载失败",
			icon: "none",
		});
	}
	finally {
		isLoading.value = false;
	}
}

async function loadOptionalGrades() {
	try {
		const res: any = await Apis.me.get_me_getOptionalGrade({
			params: {
				pageIndex: 1,
				pageSize: 50,
			},
		});
		gradeOptions.value = normalizeGradeOptions(res?.data);
	}
	catch (error) {
		console.error("获取可选年级失败:", error);
		gradeOptions.value = [];
	}
}

async function loadMyPoint() {
	try {
		const res: any = await Apis.me.get_me_getMyPoint({});
		const nextPoint = Number(res?.data?.point ?? res?.data ?? 0);
		myPoint.value = Number.isFinite(nextPoint) ? nextPoint : 0;
	}
	catch (error) {
		console.error("获取积分失败:", error);
		myPoint.value = 0;
	}
}

function closeAddModal() {
	showAddModal.value = false;
	addForm.value = {
		name: "",
		grade: "",
	};
}

function handleGradeChange(event: PickerChangeEvent) {
	const nextIndex = Number(event?.detail?.value ?? 0);
	const nextOption = gradeOptions.value[nextIndex];
	if (!nextOption) return;
	addForm.value.grade = nextOption.label;
}

async function addStudent() {
	if (!addForm.value.name.trim() || !addForm.value.grade.trim()) {
		uni.showToast({
			title: "请填写完整信息",
			icon: "none",
		});
		return;
	}

	isLoading.value = true;
	try {
		const res: any = await Apis.me.post_me_addStudent({
			data: {
				name: addForm.value.name.trim(),
				grade: addForm.value.grade.trim(),
			},
		});

		if (res?.code === 10000) {
			uni.showToast({
				title: "添加成功",
				icon: "success",
			});
			closeAddModal();
			await loadStudentList();
			await loadCurrentStudentDetail();
		}
	}
	catch (error) {
		console.error("添加学员失败:", error);
		uni.showToast({
			title: "添加失败，请重试",
			icon: "none",
		});
	}
	finally {
		isLoading.value = false;
	}
}

async function removeStudent(studentId: string | number) {
	const modalResult = await uni.showModal({
		title: "确认移除",
		content: "确定要移除该学员吗？",
	});

	if (!modalResult.confirm) return;

	isLoading.value = true;
	try {
		const numericId = Number(studentId);
		const result: any = await Apis.me.get_me_removeStudent({
			params: {
				id: numericId,
				studentId: numericId,
			},
		});

		if (result?.code === 10000) {
			uni.showToast({
				title: "移除成功",
				icon: "success",
			});
			await loadStudentList();
			await loadCurrentStudentDetail();
		}
	}
	catch (error) {
		console.error("移除学员失败:", error);
		uni.showToast({
			title: "移除失败，请重试",
			icon: "none",
		});
	}
	finally {
		isLoading.value = false;
	}
}

async function switchStudent(studentId: string | number) {
	isLoading.value = true;
	try {
		const numericId = Number(studentId);
		const res: any = await Apis.me.get_me_switchStudent({
			params: {
				id: numericId,
				studentId: numericId,
			},
		});

		if (res?.code === 10000) {
			currentStudentId.value = String(studentId);
			userStore.setCurrentStudent(String(studentId));
			uni.showToast({
				title: "切换成功",
				icon: "success",
			});
			await loadStudentList();
			await loadCurrentStudentDetail(studentId);
		}
	}
	catch (error) {
		console.error("切换学员失败:", error);
		uni.showToast({
			title: "切换失败，请重试",
			icon: "none",
		});
	}
	finally {
		isLoading.value = false;
	}
}

onMounted(async () => {
	await loadStudentList();
	await Promise.all([loadCurrentStudentDetail(), loadOptionalGrades(), loadMyPoint()]);
});
</script>

<template>
	<view class="student-related-page">
		<view class="student-related-page__bg" />
		<ParentNavBar title="学员相关" right-text="新增" @right-click="showAddModal = true" />

		<view class="student-related-page__content">
			<view class="student-hero">
				<view class="student-hero__top">
					<view class="student-hero__avatar">{{ currentStudentAvatar }}</view>
					<view class="student-hero__copy">
						<view class="student-hero__eyebrow">当前学员</view>
						<view class="student-hero__name">{{ currentStudent?.name || "未关联学员" }}</view>
						<view class="student-hero__grade">{{ currentStudent?.grade || "可在下方新增或切换学员" }}</view>
					</view>
					<view class="student-hero__point">
						<view class="student-hero__point-value">{{ myPoint }}</view>
						<view class="student-hero__point-label">我的积分</view>
					</view>
				</view>

				<view class="student-hero__stats">
					<view class="student-hero__stat">
						<view class="student-hero__stat-value">{{ studentCount }}</view>
						<view class="student-hero__stat-label">已关联学员</view>
					</view>
					<view class="student-hero__stat student-hero__stat--right">
						<view class="student-hero__stat-value">{{ gradeOptions.length }}</view>
						<view class="student-hero__stat-label">可选年级</view>
					</view>
				</view>

				<view class="student-hero__tip">当前学员信息会优先通过当前学员查询接口同步，列表、新增、切换继续使用学员相关接口。</view>
			</view>

			<view class="section-card">
				<view class="section-card__header">
					<view class="section-card__title">学员列表</view>
					<view class="section-card__subtitle">管理当前关联的学员账号，支持切换和移除</view>
				</view>

				<view v-if="isLoading && !studentList.length" class="state-card">
					<view class="state-card__icon">
						<view class="i-carbon:renew state-card__icon--spin text-24px text-#1aa784" />
					</view>
					<view class="state-card__title">正在同步学员数据</view>
					<view class="state-card__desc">稍等一下，马上就能管理学员信息。</view>
				</view>

				<view v-else-if="studentList.length">
					<view
						v-for="student in studentList"
						:key="student.id"
						:class="['student-card', currentStudentId === String(student.id) ? 'student-card--current' : '']"
					>
						<view class="student-card__main">
							<view class="student-card__avatar">{{ getStudentAvatarText(student.name) }}</view>
							<view class="student-card__content">
								<view class="student-card__title-row">
									<view class="student-card__name">{{ student.name }}</view>
									<view v-if="currentStudentId === String(student.id)" class="student-card__badge">当前学员</view>
								</view>
								<view class="student-card__meta">{{ student.grade || "暂未设置年级" }}</view>
							</view>
						</view>

						<view class="student-card__actions">
							<button
								class="ghost-btn ghost-btn--tint"
								:disabled="isLoading || currentStudentId === String(student.id)"
								@click="switchStudent(student.id)"
							>
								{{ currentStudentId === String(student.id) ? "当前使用中" : "切换到该学员" }}
							</button>
							<button
								class="ghost-btn ghost-btn--danger"
								:disabled="isLoading || currentStudentId === String(student.id)"
								@click="removeStudent(student.id)"
							>
								移除
							</button>
						</view>
					</view>
				</view>

				<view v-else class="state-card state-card--empty">
					<view class="state-card__icon">
						<view class="i-carbon:user-multiple text-26px text-#1aa784" />
					</view>
					<view class="state-card__title">还没有关联学员</view>
					<view class="state-card__desc">点击右上角新增，或者现在添加第一位学员。</view>
					<button class="primary-btn" @click="showAddModal = true">添加第一位学员</button>
				</view>
			</view>
		</view>

		<uni-popup v-model:visible="showAddModal" mode="center">
			<view class="student-modal">
				<view class="student-modal__badge">新增学员</view>
				<view class="student-modal__title">完善学员信息</view>
				<view class="student-modal__desc">保存后即可在首页、记录页中切换查看该学员的学习数据。</view>

				<view class="form-field">
					<view class="form-field__label">学员姓名</view>
					<view class="form-field__shell">
						<input v-model="addForm.name" class="form-field__input" placeholder="请输入学员姓名" />
					</view>
				</view>

				<view class="form-field">
					<view class="form-field__label">年级</view>
					<picker
						v-if="gradeOptions.length"
						mode="selector"
						:range="gradeLabels"
						:value="selectedGradeIndex"
						class="form-field__picker"
						@change="handleGradeChange"
					>
						<view class="picker-shell">
							<text :class="addForm.grade ? 'picker-shell__text' : 'picker-shell__text picker-shell__text--placeholder'">
								{{ addForm.grade || "请选择年级" }}
							</text>
							<view class="i-carbon:chevron-right text-18px text-#94a3b8" />
						</view>
					</picker>
					<view v-else class="form-field__shell">
						<input v-model="addForm.grade" class="form-field__input" placeholder="请输入年级" />
					</view>
				</view>

				<view class="modal-actions">
					<button class="ghost-btn" @click="closeAddModal">取消</button>
					<button class="primary-btn" :disabled="isLoading" @click="addStudent">确认添加</button>
				</view>
			</view>
		</uni-popup>
	</view>
</template>

<style scoped>
.student-related-page {
	position: relative;
	min-height: 100vh;
	background: #f4f7fb;
	overflow: hidden;
}

.student-related-page__bg {
	position: absolute;
	top: 0;
	left: 0;
	right: 0;
	height: 260px;
	background: linear-gradient(180deg, #ddfff6 0%, rgba(221, 255, 246, 0) 100%);
}

.student-related-page__content {
	position: relative;
	padding: 16px 16px 28px;
}

.student-hero {
	padding: 22px 20px;
	border-radius: 28px;
	color: #fff;
	background: linear-gradient(135deg, #20c59c 0%, #38b6ff 100%);
	box-shadow: 0 18px 42px rgba(32, 197, 156, 0.24);
}

.student-hero__top {
	display: flex;
	align-items: center;
}

.student-hero__avatar {
	width: 62px;
	height: 62px;
	flex-shrink: 0;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 22px;
	background: rgba(255, 255, 255, 0.22);
	font-size: 28px;
	font-weight: 700;
}

.student-hero__copy {
	flex: 1;
	margin-left: 14px;
	min-width: 0;
}

.student-hero__eyebrow {
	font-size: 12px;
	font-weight: 600;
	color: rgba(255, 255, 255, 0.82);
}

.student-hero__name {
	margin-top: 6px;
	font-size: 24px;
	font-weight: 700;
	line-height: 1.25;
}

.student-hero__grade {
	margin-top: 8px;
	font-size: 13px;
	line-height: 1.5;
	color: rgba(255, 255, 255, 0.88);
}

.student-hero__point {
	min-width: 86px;
	margin-left: 12px;
	padding: 12px 10px;
	border-radius: 18px;
	background: rgba(255, 255, 255, 0.16);
	text-align: center;
}

.student-hero__point-value {
	font-size: 24px;
	font-weight: 700;
	line-height: 1.2;
}

.student-hero__point-label {
	margin-top: 6px;
	font-size: 12px;
	color: rgba(255, 255, 255, 0.84);
}

.student-hero__stats {
	display: flex;
	margin-top: 20px;
	padding-top: 18px;
	border-top: 1px solid rgba(255, 255, 255, 0.2);
}

.student-hero__stat {
	flex: 1;
}

.student-hero__stat--right {
	padding-left: 18px;
	margin-left: 18px;
	border-left: 1px solid rgba(255, 255, 255, 0.2);
}

.student-hero__stat-value {
	font-size: 28px;
	font-weight: 700;
	line-height: 1.2;
}

.student-hero__stat-label {
	margin-top: 8px;
	font-size: 13px;
	color: rgba(255, 255, 255, 0.84);
}

.student-hero__tip {
	margin-top: 16px;
	padding: 12px 14px;
	border-radius: 16px;
	background: rgba(255, 255, 255, 0.14);
	font-size: 13px;
	line-height: 1.6;
	color: rgba(255, 255, 255, 0.88);
}

.section-card {
	margin-top: 16px;
	padding: 18px 16px;
	border-radius: 24px;
	background: #fff;
	box-shadow: 0 12px 30px rgba(15, 23, 42, 0.06);
}

.section-card__header {
	margin-bottom: 8px;
}

.section-card__title {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.section-card__subtitle {
	margin-top: 6px;
	font-size: 13px;
	line-height: 1.6;
	color: #6b7280;
}

.student-card {
	padding: 16px;
	border: 1px solid #e8eef5;
	border-radius: 22px;
	background: #fff;
}

.student-card + .student-card {
	margin-top: 12px;
}

.student-card--current {
	border-color: rgba(49, 199, 165, 0.36);
	background: linear-gradient(180deg, #f4fffb 0%, #ffffff 100%);
	box-shadow: 0 10px 22px rgba(49, 199, 165, 0.12);
}

.student-card__main {
	display: flex;
	align-items: center;
}

.student-card__avatar {
	width: 50px;
	height: 50px;
	flex-shrink: 0;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 18px;
	background: #effbf7;
	font-size: 22px;
	font-weight: 700;
	color: #15916f;
}

.student-card__content {
	flex: 1;
	margin-left: 12px;
	min-width: 0;
}

.student-card__title-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
}

.student-card__name {
	font-size: 17px;
	font-weight: 700;
	color: #111827;
}

.student-card__badge {
	margin-left: 12px;
	padding: 4px 10px;
	border-radius: 999px;
	background: #dcfcef;
	font-size: 12px;
	color: #15916f;
	flex-shrink: 0;
}

.student-card__meta {
	margin-top: 8px;
	font-size: 14px;
	color: #6b7280;
}

.student-card__actions {
	display: flex;
	margin-top: 16px;
}

.student-card__actions button + button {
	margin-left: 12px;
}

.state-card {
	margin-top: 14px;
	padding: 40px 20px;
	border: 1px dashed #dbe4ee;
	border-radius: 22px;
	background: #fbfcff;
	text-align: center;
}

.state-card--empty {
	margin-top: 18px;
}

.state-card__icon {
	width: 52px;
	height: 52px;
	margin: 0 auto 14px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 20px;
	background: #effbf7;
}

.state-card__icon--spin {
	animation: student-spin 1.1s linear infinite;
}

.state-card__title {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.state-card__desc {
	margin-top: 8px;
	font-size: 13px;
	line-height: 1.6;
	color: #6b7280;
}

.student-modal {
	width: 86vw;
	max-width: 420px;
	padding: 20px 18px;
	border-radius: 26px;
	background: #fff;
}

.student-modal__badge {
	display: inline-flex;
	align-items: center;
	padding: 6px 12px;
	border-radius: 999px;
	background: #effbf7;
	font-size: 12px;
	font-weight: 600;
	color: #15916f;
}

.student-modal__title {
	margin-top: 14px;
	font-size: 22px;
	font-weight: 700;
	color: #111827;
}

.student-modal__desc {
	margin-top: 8px;
	font-size: 14px;
	line-height: 1.6;
	color: #6b7280;
}

.form-field {
	margin-top: 16px;
}

.form-field__label {
	margin-bottom: 8px;
	font-size: 14px;
	font-weight: 600;
	color: #374151;
}

.form-field__shell {
	padding: 0 14px;
	border: 1px solid #e5edf6;
	border-radius: 16px;
	background: #f8fafc;
}

.form-field__input {
	width: 100%;
	height: 48px;
	font-size: 15px;
	color: #111827;
}

.picker-shell {
	height: 48px;
	padding: 0 14px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border: 1px solid #e5edf6;
	border-radius: 16px;
	background: #f8fafc;
}

.picker-shell__text {
	font-size: 15px;
	color: #111827;
}

.picker-shell__text--placeholder {
	color: #9ca3af;
}

.modal-actions {
	display: flex;
	margin-top: 24px;
}

.modal-actions button + button {
	margin-left: 12px;
}

.primary-btn,
.ghost-btn {
	flex: 1;
	height: 46px;
	border-radius: 16px;
	display: flex;
	align-items: center;
	justify-content: center;
	font-size: 15px;
	font-weight: 600;
}

.primary-btn {
	color: #fff;
	border: none;
	background: linear-gradient(135deg, #31c7a5 0%, #20b486 100%);
	box-shadow: 0 12px 24px rgba(49, 199, 165, 0.22);
}

.ghost-btn {
	color: #4b5563;
	border: 1px solid #e5edf6;
	background: #fff;
}

.ghost-btn--tint {
	color: #15916f;
	border-color: transparent;
	background: #effbf7;
}

.ghost-btn--danger {
	color: #e35b5b;
	border-color: transparent;
	background: #fff5f5;
}

.primary-btn::after,
.ghost-btn::after {
	border: none;
}

.primary-btn:disabled,
.ghost-btn:disabled {
	opacity: 0.65;
}

@keyframes student-spin {
	from {
		transform: rotate(0deg);
	}

	to {
		transform: rotate(360deg);
	}
}
</style>
