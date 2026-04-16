<script setup lang="ts">
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import TeacherSectionCard from "@/components/teacher/TeacherSectionCard.vue";
import { Apis } from "@/api";

definePage({
	name: "teacherStudentArchive",
	style: {
		navigationBarTitleText: "学生档案",
		titleNView: false,
	},
});

type StudentStage = "all" | "intentional" | "active" | "graduated";

interface StudentArchiveItem {
	id: string;
	name: string;
	phone: string;
	className: string;
	stage: Exclude<StudentStage, "all">;
	remaining: number;
	parentName: string;
	note: string;
}

const toast = useGlobalToast();
const keyword = ref("");
const activeStage = ref<StudentStage>("all");
const loading = ref(false);
const studentList = ref<StudentArchiveItem[]>([]);

const stageOptions = [
	{ label: "全部", value: "all" },
	{ label: "意向", value: "intentional" },
	{ label: "在读", value: "active" },
	{ label: "结课", value: "graduated" },
] as const;

const filteredStudents = computed(() => {
	const keywordValue = keyword.value.trim();

	return studentList.value.filter((item) => {
		const matchStage = activeStage.value === "all" || item.stage === activeStage.value;
		const matchKeyword =
			!keywordValue ||
			item.name.includes(keywordValue) ||
			item.phone.includes(keywordValue) ||
			item.className.includes(keywordValue);

		return matchStage && matchKeyword;
	});
});

function stageText(stage: StudentArchiveItem["stage"]) {
	switch (stage) {
		case "intentional":
			return "意向学员";
		case "active":
			return "在读学员";
		default:
			return "已结课";
	}
}

function stageClass(stage: StudentArchiveItem["stage"]) {
	switch (stage) {
		case "intentional":
			return "teacher-archive-card__badge--intentional";
		case "active":
			return "teacher-archive-card__badge--active";
		default:
			return "teacher-archive-card__badge--graduated";
	}
}

async function loadStudentArchive() {
	loading.value = true;
	try {
		const response = await (Apis as any).workbench.get_workbench_StuProfileDetails();
		// 假设API返回的数据结构与我们的接口匹配
		// 这里可能需要根据实际API返回格式进行调整
		studentList.value = response || [];
	} catch (error) {
		console.error("加载学生档案失败:", error);
		toast.show("学生档案加载失败");
		studentList.value = [];
	} finally {
		loading.value = false;
	}
}

function refreshPage() {
	loadStudentArchive();
}

// 页面加载时获取学生档案数据
loadStudentArchive();
</script>

<template>
	<view class="teacher-archive-page">
		<teacher-nav-bar title="学生档案" @refresh="refreshPage" />

		<view class="teacher-archive-page__content">
			<view class="teacher-archive-search">
				<view class="i-carbon:search text-18px text-#98a2b3" />
				<input
					v-model="keyword"
					class="teacher-archive-search__input"
					type="text"
					placeholder="搜索学员姓名、手机号或班级"
				/>
			</view>

			<teacher-section-card title="档案概览" :extra="`学员 ${studentList.length} 名`">
				<view class="teacher-archive-summary">
					<view class="teacher-archive-summary__item">
						<text class="teacher-archive-summary__value">{{ studentList.filter((item) => item.stage === "active").length }}</text>
						<text class="teacher-archive-summary__label">在读</text>
					</view>
					<view class="teacher-archive-summary__item">
						<text class="teacher-archive-summary__value">{{ studentList.filter((item) => item.stage === "intentional").length }}</text>
						<text class="teacher-archive-summary__label">意向</text>
					</view>
					<view class="teacher-archive-summary__item">
						<text class="teacher-archive-summary__value">{{ studentList.filter((item) => item.stage === "graduated").length }}</text>
						<text class="teacher-archive-summary__label">结课</text>
					</view>
				</view>
			</teacher-section-card>

			<teacher-section-card title="学员列表" :extra="`筛选结果 ${filteredStudents.length} 名`">
				<view class="teacher-archive-filter">
					<view
						v-for="option in stageOptions"
						:key="option.value"
						class="teacher-archive-filter__chip"
						:class="{ 'teacher-archive-filter__chip--active': activeStage === option.value }"
						@click="activeStage = option.value"
					>
						{{ option.label }}
					</view>
				</view>

				<view class="teacher-archive-list">
					<view v-if="loading" class="teacher-archive-loading">
						<text>加载中...</text>
					</view>
					<view v-else-if="filteredStudents.length === 0" class="teacher-archive-empty">
						<view class="i-carbon:document-search text-36px text-#d1d5db" />
						<text>暂无学员数据</text>
					</view>
					<view v-else v-for="item in filteredStudents" :key="item.id" class="teacher-archive-card">
						<view class="teacher-archive-card__header">
							<view>
								<view class="teacher-archive-card__title">{{ item.name }}</view>
								<view class="teacher-archive-card__meta">{{ item.className }} / {{ item.phone }}</view>
							</view>
							<view class="teacher-archive-card__badge" :class="stageClass(item.stage)">
								{{ stageText(item.stage) }}
							</view>
						</view>

						<view class="teacher-archive-card__line">家长联系人：{{ item.parentName }}</view>
						<view class="teacher-archive-card__line">剩余课次：{{ item.remaining }}</view>
						<view class="teacher-archive-card__note">{{ item.note }}</view>
					</view>
				</view>
			</teacher-section-card>
		</view>
	</view>
</template>

<style scoped>
.teacher-archive-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-archive-page__content {
	padding: 12px;
}

.teacher-archive-tip {
	display: flex;
	align-items: flex-start;
	gap: 8px;
	border-radius: 14px;
	background: #fff7ed;
	padding: 14px 16px;
	font-size: 13px;
	line-height: 1.7;
	color: #c2410c;
}

.teacher-archive-search {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-top: 12px;
	border-radius: 12px;
	background: #fff;
	padding: 12px 14px;
}

.teacher-archive-search__input {
	flex: 1;
	min-width: 0;
	font-size: 14px;
	color: #344054;
}

.teacher-archive-summary {
	display: grid;
	grid-template-columns: repeat(3, minmax(0, 1fr));
}

.teacher-archive-summary__item {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 8px;
	min-height: 100px;
	border-right: 1px solid #eef1f6;
}

.teacher-archive-summary__item:last-child {
	border-right: 0;
}

.teacher-archive-summary__value {
	font-size: 24px;
	font-weight: 700;
	color: #111827;
}

.teacher-archive-summary__label {
	font-size: 13px;
	color: #98a2b3;
}

.teacher-archive-filter {
	display: flex;
	flex-wrap: wrap;
	gap: 10px;
	padding: 14px 16px 0;
}

.teacher-archive-filter__chip {
	border-radius: 999px;
	padding: 7px 14px;
	background: #f3f4f6;
	font-size: 13px;
	color: #667085;
}

.teacher-archive-filter__chip--active {
	background: #e8f8f4;
	color: #1ca386;
	font-weight: 600;
}

.teacher-archive-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
	padding: 14px 16px 16px;
}

.teacher-archive-card {
	border-radius: 16px;
	background: #f8fafc;
	padding: 14px;
}

.teacher-archive-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.teacher-archive-card__title {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.teacher-archive-card__meta {
	margin-top: 6px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-archive-card__badge {
	flex-shrink: 0;
	border-radius: 999px;
	padding: 4px 10px;
	font-size: 12px;
	font-weight: 600;
}

.teacher-archive-card__badge--intentional {
	background: rgba(245, 158, 11, 0.14);
	color: #d97706;
}

.teacher-archive-card__badge--active {
	background: rgba(49, 199, 165, 0.14);
	color: #1ca386;
}

.teacher-archive-card__badge--graduated {
	background: rgba(148, 163, 184, 0.14);
	color: #64748b;
}

.teacher-archive-card__line {
	margin-top: 10px;
	font-size: 13px;
	line-height: 1.6;
	color: #475467;
}

.teacher-archive-card__note {
	margin-top: 12px;
	border-radius: 12px;
	background: #fff;
	padding: 10px 12px;
	font-size: 12px;
	line-height: 1.7;
	color: #667085;
}

.teacher-archive-loading,
.teacher-archive-empty {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	gap: 12px;
	padding: 40px 20px;
	text-align: center;
}

.teacher-archive-loading text,
.teacher-archive-empty text {
	font-size: 14px;
	color: #667085;
}
</style>
