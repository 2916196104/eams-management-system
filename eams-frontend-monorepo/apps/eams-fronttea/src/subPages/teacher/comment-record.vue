<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { Apis } from "@/api";

definePage({
	name: "teacherCommentRecord",
	style: {
		navigationBarTitleText: "点评记录",
		titleNView: false,
	},
});

interface TeacherCommentItem {
	id?: string;
	studentName?: string;
	commentText?: string;
	commentDate?: string;
	score?: number;
	isSign?: boolean;
	teacherId?: number | string;
	teacherName?: string;
	studentId?: number | string;
	lessonId?: number | string;
	courseTitle?: string;
}

const userStore = useUserStore();
const { teacherInfo } = storeToRefs(userStore);

const loading = ref(false);
const loadingMore = ref(false);
const submitting = ref(false);
const pageIndex = ref(1);
const total = ref(0);
const pages = ref(0);
const pageSize = 10;
const commentList = ref<Array<TeacherCommentItem>>([]);
const popupVisible = ref(false);
const currentComment = ref<TeacherCommentItem | null>(null);

const commentForm = reactive({
	overallScore: 5,
	atmosphereScore: 5,
	attitudeScore: 5,
	effectScore: 5,
	content: "",
});

const scoreOptions = [1, 2, 3, 4, 5];
const hasMore = computed(() => pageIndex.value < pages.value);
const hasReadonlyRows = computed(() => commentList.value.some((item) => !canComment(item)));

function normalizePage(source: any) {
	const payload = source?.data?.data ?? source?.data ?? source ?? {};
	const rows = Array.isArray(payload.rows)
		? payload.rows
		: Array.isArray(payload.list)
			? payload.list
			: Array.isArray(payload.records)
				? payload.records
				: Array.isArray(payload)
					? payload
					: [];

	return {
		pageIndex: Number(payload.pageIndex ?? payload.page ?? 1),
		pages: Number(payload.pages ?? payload.total_page ?? 0),
		total: Number(payload.total ?? rows.length),
		rows: rows.map((item: any) => {
			const scoreValue = Number(item.score);
			return {
				id: item.id ? String(item.id) : undefined,
				studentName: item.studentName ?? item.name ?? "--",
				commentText: item.commentText ?? item.evaluation ?? "",
				commentDate: item.commentDate ?? item.operationTime ?? "",
				score: Number.isFinite(scoreValue) ? scoreValue : undefined,
				isSign: typeof item.isSign === "boolean" ? item.isSign : item.is_signed,
				teacherId: item.teacherId,
				teacherName: item.teacherName ?? item.Operator,
				studentId: item.studentId,
				lessonId: item.lessonId,
				courseTitle: item.courseTitle,
			} satisfies TeacherCommentItem;
		}),
	};
}

function canComment(item: TeacherCommentItem) {
	return Boolean(item.id && item.studentId && item.lessonId);
}

function scoreClass(score?: number) {
	if (typeof score !== "number") return "teacher-comment__score--empty";
	if (score <= 5) {
		if (score >= 5) return "teacher-comment__score--excellent";
		if (score >= 4) return "teacher-comment__score--good";
		if (score >= 3) return "teacher-comment__score--pass";
		return "teacher-comment__score--warn";
	}
	if (score >= 90) return "teacher-comment__score--excellent";
	if (score >= 80) return "teacher-comment__score--good";
	if (score >= 60) return "teacher-comment__score--pass";
	return "teacher-comment__score--warn";
}

function scoreText(score?: number) {
	if (typeof score !== "number") return "未评分";
	return score <= 5 ? `${score}星` : `${score}分`;
}

function openCommentPopup(item: TeacherCommentItem) {
	if (!canComment(item)) {
		uni.showToast({ title: "当前记录缺少点评主键，只支持查看", icon: "none" });
		return;
	}

	currentComment.value = item;
	const baseScore = typeof item.score === "number"
		? item.score <= 5
			? Math.min(Math.max(Math.round(item.score), 1), 5)
			: Math.min(Math.max(Math.round(item.score / 20), 1), 5)
		: 5;
	commentForm.overallScore = baseScore;
	commentForm.atmosphereScore = baseScore;
	commentForm.attitudeScore = baseScore;
	commentForm.effectScore = baseScore;
	commentForm.content = item.commentText || "";
	popupVisible.value = true;
}

function closeCommentPopup() {
	popupVisible.value = false;
	currentComment.value = null;
}

async function loadComments(nextPage = 1, append = false) {
	if (!teacherInfo.value.id) {
		await userStore.loadCurrentUserInfo();
	}

	const targetLoading = append ? loadingMore : loading;
	targetLoading.value = true;

	try {
		const res: any = await (Apis as any).workbench.get_workbench_remark({
			params: {
				pageIndex: nextPage,
				pageSize,
			},
		});

		const pageData = normalizePage(res);
		pageIndex.value = pageData.pageIndex;
		pages.value = pageData.pages;
		total.value = pageData.total;
		commentList.value = append ? [...commentList.value, ...pageData.rows] : pageData.rows;
	} catch {
		if (!append) commentList.value = [];
		uni.showToast({ title: "点评记录加载失败", icon: "none" });
	} finally {
		targetLoading.value = false;
	}
}

async function refreshPage() {
	await loadComments(1, false);
	uni.showToast({ title: "已刷新", icon: "none" });
}

async function loadMore() {
	if (!hasMore.value || loadingMore.value) return;
	await loadComments(pageIndex.value + 1, true);
}

async function submitComment() {
	if (!currentComment.value) return;

	submitting.value = true;
	try {
		const teacherId = Number(teacherInfo.value.id);
		const recordId = currentComment.value.id ? Number(currentComment.value.id) : undefined;
		const studentId = Number(currentComment.value.studentId);
		const lessonId = Number(currentComment.value.lessonId);

		await (Apis as any).course.put_course_record_comment_comment_stu({
			data: {
				id: Number.isFinite(recordId) ? recordId : undefined,
				teacherId: Number.isFinite(teacherId) ? teacherId : currentComment.value.teacherId,
				teacherName: teacherInfo.value.name || currentComment.value.teacherName,
				studentId: Number.isFinite(studentId) ? studentId : undefined,
				studentName: currentComment.value.studentName,
				lessonId: Number.isFinite(lessonId) ? lessonId : undefined,
				courseTitle: currentComment.value.courseTitle,
				overallScore: commentForm.overallScore,
				atmosphereScore: commentForm.atmosphereScore,
				attitudeScore: commentForm.attitudeScore,
				effectScore: commentForm.effectScore,
				content: commentForm.content,
			},
		});

		uni.showToast({ title: "点评成功", icon: "none" });
		closeCommentPopup();
		await loadComments(1, false);
	} catch {
		uni.showToast({ title: "点评失败", icon: "none" });
	} finally {
		submitting.value = false;
	}
}

onShow(() => {
	void loadComments(1, false);
});
</script>

<template>
	<view class="teacher-comment-page">
		<teacher-nav-bar title="点评记录" @refresh="refreshPage" />
		<view class="teacher-comment-page__content">
			<view v-if="commentList.length" class="teacher-comment-page__list">
				<view class="teacher-comment-page__summary">
					<text>共 {{ total }} 条点评</text>
				</view>

				<view v-if="hasReadonlyRows" class="teacher-comment-page__tip">
					当前 c4 点评记录接口主要提供列表展示，缺少主键的记录将先只读展示。
				</view>

				<view v-for="item in commentList" :key="`${item.id ?? item.studentName}-${item.commentDate}`" class="teacher-comment">
					<view class="teacher-comment__header">
						<view>
							<view class="teacher-comment__student">{{ item.studentName || "未命名学员" }}</view>
							<view class="teacher-comment__meta">
								{{ item.commentDate || "暂无时间" }}
							</view>
						</view>
						<view class="teacher-comment__score" :class="scoreClass(item.score)">
							{{ scoreText(item.score) }}
						</view>
					</view>

					<view class="teacher-comment__tags">
						<view v-if="typeof item.isSign === 'boolean'" class="teacher-comment__tag" :class="{ 'teacher-comment__tag--active': item.isSign }">
							{{ item.isSign ? "已签到" : "未签到" }}
						</view>
						<view v-if="item.courseTitle" class="teacher-comment__tag">
							{{ item.courseTitle }}
						</view>
					</view>

					<view class="teacher-comment__body">
						{{ item.commentText || "暂无点评内容" }}
					</view>

					<view v-if="canComment(item)" class="teacher-comment__actions">
						<wd-button size="small" plain @click="openCommentPopup(item)">去点评</wd-button>
					</view>
				</view>

				<view v-if="hasMore" class="teacher-comment-page__more" @click="loadMore">
					{{ loadingMore ? "加载中..." : "加载更多" }}
				</view>
			</view>

			<teacher-empty-state v-else :title="loading ? '加载中...' : '暂无点评记录'" compact />
		</view>

		<wd-popup v-model="popupVisible" position="bottom" custom-class="teacher-comment-popup">
			<view class="teacher-comment-popup__body">
				<view class="teacher-comment-popup__title">
					点评 {{ currentComment?.studentName || "学员" }}
				</view>

				<view class="teacher-comment-popup__group">
					<text class="teacher-comment-popup__label">综合评分</text>
					<view class="teacher-comment-popup__scores">
						<view
							v-for="value in scoreOptions"
							:key="`overall-${value}`"
							class="teacher-comment-popup__score"
							:class="{ 'teacher-comment-popup__score--active': commentForm.overallScore === value }"
							@click="commentForm.overallScore = value"
						>
							{{ value }}星
						</view>
					</view>
				</view>

				<view class="teacher-comment-popup__group">
					<text class="teacher-comment-popup__label">课堂气氛</text>
					<view class="teacher-comment-popup__scores">
						<view
							v-for="value in scoreOptions"
							:key="`atmosphere-${value}`"
							class="teacher-comment-popup__score"
							:class="{ 'teacher-comment-popup__score--active': commentForm.atmosphereScore === value }"
							@click="commentForm.atmosphereScore = value"
						>
							{{ value }}星
						</view>
					</view>
				</view>

				<view class="teacher-comment-popup__group">
					<text class="teacher-comment-popup__label">授课态度</text>
					<view class="teacher-comment-popup__scores">
						<view
							v-for="value in scoreOptions"
							:key="`attitude-${value}`"
							class="teacher-comment-popup__score"
							:class="{ 'teacher-comment-popup__score--active': commentForm.attitudeScore === value }"
							@click="commentForm.attitudeScore = value"
						>
							{{ value }}星
						</view>
					</view>
				</view>

				<view class="teacher-comment-popup__group">
					<text class="teacher-comment-popup__label">教学效果</text>
					<view class="teacher-comment-popup__scores">
						<view
							v-for="value in scoreOptions"
							:key="`effect-${value}`"
							class="teacher-comment-popup__score"
							:class="{ 'teacher-comment-popup__score--active': commentForm.effectScore === value }"
							@click="commentForm.effectScore = value"
						>
							{{ value }}星
						</view>
					</view>
				</view>

				<view class="teacher-comment-popup__group">
					<text class="teacher-comment-popup__label">评语</text>
					<textarea
						v-model="commentForm.content"
						class="teacher-comment-popup__textarea"
						placeholder="请输入点评内容"
						:maxlength="300"
					/>
				</view>

				<view class="teacher-comment-popup__actions">
					<wd-button plain @click="closeCommentPopup">取消</wd-button>
					<wd-button type="primary" :loading="submitting" @click="submitComment">提交点评</wd-button>
				</view>
			</view>
		</wd-popup>
	</view>
</template>

<style scoped>
.teacher-comment-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-comment-page__content {
	padding: 12px;
}

.teacher-comment-page__list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.teacher-comment-page__summary {
	padding: 0 2px;
	font-size: 13px;
	color: #8b95a7;
}

.teacher-comment-page__tip {
	border-radius: 14px;
	background: #fff7ed;
	padding: 12px 14px;
	font-size: 13px;
	line-height: 1.7;
	color: #f97316;
}

.teacher-comment {
	border-radius: 16px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.teacher-comment__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.teacher-comment__student {
	font-size: 16px;
	font-weight: 700;
	color: #111827;
}

.teacher-comment__meta {
	margin-top: 6px;
	font-size: 12px;
	color: #94a3b8;
}

.teacher-comment__score {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 700;
}

.teacher-comment__score--excellent {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.teacher-comment__score--good {
	background: rgba(59, 130, 246, 0.12);
	color: #2563eb;
}

.teacher-comment__score--pass {
	background: rgba(245, 158, 11, 0.12);
	color: #d97706;
}

.teacher-comment__score--warn {
	background: rgba(239, 68, 68, 0.12);
	color: #dc2626;
}

.teacher-comment__score--empty {
	background: rgba(148, 163, 184, 0.12);
	color: #64748b;
}

.teacher-comment__tags {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-top: 14px;
}

.teacher-comment__tag {
	border-radius: 999px;
	background: rgba(148, 163, 184, 0.12);
	padding: 4px 10px;
	font-size: 12px;
	color: #64748b;
}

.teacher-comment__tag--active {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.teacher-comment__body {
	margin-top: 14px;
	border-radius: 14px;
	background: #f8fafc;
	padding: 14px;
	font-size: 14px;
	line-height: 1.8;
	color: #475569;
	white-space: pre-wrap;
	word-break: break-word;
}

.teacher-comment__actions {
	display: flex;
	justify-content: flex-end;
	margin-top: 14px;
}

.teacher-comment-page__more {
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

.teacher-comment-popup__body {
	padding: 20px 16px calc(env(safe-area-inset-bottom) + 18px);
	background: #fff;
	border-top-left-radius: 18px;
	border-top-right-radius: 18px;
}

.teacher-comment-popup__title {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.teacher-comment-popup__group {
	margin-top: 16px;
}

.teacher-comment-popup__label {
	display: block;
	margin-bottom: 10px;
	font-size: 14px;
	font-weight: 600;
	color: #344054;
}

.teacher-comment-popup__scores {
	display: flex;
	flex-wrap: wrap;
	gap: 8px;
}

.teacher-comment-popup__score {
	border: 1px solid #d9e0ec;
	border-radius: 999px;
	padding: 6px 12px;
	font-size: 13px;
	color: #667085;
}

.teacher-comment-popup__score--active {
	border-color: #31c7a5;
	background: rgba(49, 199, 165, 0.1);
	color: #1ca386;
}

.teacher-comment-popup__textarea {
	width: 100%;
	min-height: 110px;
	box-sizing: border-box;
	border-radius: 14px;
	background: #f8fafc;
	padding: 12px 14px;
	font-size: 14px;
	color: #344054;
}

.teacher-comment-popup__actions {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 12px;
	margin-top: 20px;
}
</style>
