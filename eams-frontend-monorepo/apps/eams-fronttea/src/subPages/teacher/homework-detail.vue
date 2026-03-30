<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import TeacherSectionCard from "@/components/teacher/TeacherSectionCard.vue";

definePage({
	name: "teacherHomeworkDetail",
	style: {
		navigationBarTitleText: "作业详情",
		titleNView: false,
	},
});

interface HomeworkSubmitRecord {
	recordId: string;
	canComment: boolean;
	studentId: string;
	submitContent: string;
	submitTime: string;
	score: number;
	comment: string;
	commentTime: string;
	commentTeacher: string;
}

interface HomeworkDetailInfo {
	id: string;
	title: string;
	className: string;
	classId: string;
	content: string;
	createTime: string;
	attachment: string;
	submitList: HomeworkSubmitRecord[];
}

const route = useRoute() as { query?: Record<string, string | string[] | undefined> };
const userStore = useUserStore();

const loading = ref(false);
const submitting = ref(false);
const popupVisible = ref(false);
const detail = ref<HomeworkDetailInfo | null>(null);
const currentSubmitRecord = ref<HomeworkSubmitRecord | null>(null);

const commentForm = reactive({
	score: "",
	content: "",
});

function readQuery(key: string) {
	const value = route.query?.[key];
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

const homeworkId = computed(() => readQuery("homework_id"));

function normalizeText(value: unknown, fallback = "--") {
	if (typeof value !== "string") return fallback;
	const trimmed = value.trim();
	return trimmed ? trimmed : fallback;
}

function normalizeEditableText(value: unknown) {
	if (typeof value !== "string") return "";
	const trimmed = value.trim();
	return trimmed === "--" ? "" : trimmed;
}

function normalizeSubmitList(source: any) {
	const rawList = Array.isArray(source?.submit_list)
		? source.submit_list
		: Array.isArray(source?.submitList)
			? source.submitList
			: [];

	return rawList.map((item: any, index: number) => {
		const hasRealRecordId = item.record_id !== undefined || item.recordId !== undefined;
		const score = Number(item.score ?? 0);

		return {
			recordId: String(item.record_id ?? item.recordId ?? `record-${index}`),
			canComment: hasRealRecordId,
			studentId: String(item.student_id ?? item.studentId ?? "--"),
			submitContent: normalizeText(item.submit_content ?? item.submitContent),
			submitTime: normalizeText(item.submit_time ?? item.submitTime),
			score: Number.isFinite(score) ? score : 0,
			comment: normalizeEditableText(item.comment),
			commentTime: normalizeText(item.comment_time ?? item.commentTime),
			commentTeacher: normalizeText(item.comment_teacher ?? item.commentTeacher),
		} satisfies HomeworkSubmitRecord;
	});
}

function normalizeDetail(source: unknown): HomeworkDetailInfo | null {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source;
	if (!payload || Array.isArray(payload)) return null;

	return {
		id: String(payload.homework_id ?? payload.id ?? homeworkId.value),
		title: normalizeText(payload.title, readQuery("title") || "--"),
		className: normalizeText(payload.class_name ?? payload.className),
		classId: String(payload.class_id ?? payload.classId ?? "--"),
		content: normalizeEditableText(payload.content) || "--",
		createTime: normalizeText(payload.create_time ?? payload.createTime),
		attachment: normalizeEditableText(payload.attachment) || "--",
		submitList: normalizeSubmitList(payload),
	};
}

async function loadDetail() {
	if (!homeworkId.value) return;

	loading.value = true;
	try {
		await userStore.loadCurrentUserInfo();
		const response = await (Apis as any).homework.get_homework_detail({
			params: {
				homework_id: homeworkId.value,
				teacher_id: userStore.teacherInfo.id,
			},
		});
		detail.value = normalizeDetail(response);
	} catch {
		detail.value = null;
		uni.showToast({ title: "作业详情加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

async function refreshPage() {
	await loadDetail();
	uni.showToast({ title: "已刷新", icon: "none" });
}

function openCommentPopup(item: HomeworkSubmitRecord) {
	if (!item.canComment) {
		uni.showToast({ title: "当前提交记录缺少 submit_id，暂不支持点评", icon: "none" });
		return;
	}

	currentSubmitRecord.value = item;
	commentForm.score = String(item.score > 0 ? item.score : "");
	commentForm.content = item.comment;
	popupVisible.value = true;
}

function closeCommentPopup() {
	popupVisible.value = false;
	currentSubmitRecord.value = null;
	commentForm.score = "";
	commentForm.content = "";
}

async function submitComment() {
	if (!currentSubmitRecord.value) return;

	const score = Number(commentForm.score);
	if (!Number.isInteger(score) || score < 0 || score > 100) {
		uni.showToast({ title: "请输入 0-100 的整数评分", icon: "none" });
		return;
	}

	await userStore.loadCurrentUserInfo();
	if (!userStore.teacherInfo.id) {
		uni.showToast({ title: "教师信息缺失，无法提交点评", icon: "none" });
		return;
	}

	submitting.value = true;
	try {
		const content = commentForm.content.trim();
		await (Apis as any).homework.post_homework_comment({
			data: {
				teacher_id: userStore.teacherInfo.id,
				submit_id: currentSubmitRecord.value.recordId,
				score,
				content: content || undefined,
				review: {
					score,
					content: content || undefined,
				},
			},
		});

		uni.showToast({ title: "点评成功", icon: "none" });
		closeCommentPopup();
		await loadDetail();
	} catch {
		uni.showToast({ title: "点评失败", icon: "none" });
	} finally {
		submitting.value = false;
	}
}

onShow(() => {
	void loadDetail();
});
</script>

<template>
	<view class="teacher-homework-detail-page">
		<teacher-nav-bar title="作业详情" @refresh="refreshPage" />

		<view class="teacher-homework-detail-page__content">
			<template v-if="detail">
				<view class="teacher-homework-detail-card">
					<view class="teacher-homework-detail-card__title">{{ detail.title }}</view>
					<view class="teacher-homework-detail-card__meta">班级：{{ detail.className }}</view>
					<view class="teacher-homework-detail-card__meta">班级ID：{{ detail.classId }}</view>
					<view class="teacher-homework-detail-card__meta">发布时间：{{ detail.createTime }}</view>
					<view class="teacher-homework-detail-card__content">{{ detail.content }}</view>
					<view class="teacher-homework-detail-card__attachment">
						<text class="teacher-homework-detail-card__attachment-label">附件</text>
						<text class="teacher-homework-detail-card__attachment-value">{{ detail.attachment }}</text>
					</view>
				</view>

				<teacher-section-card title="提交记录" :extra="detail.submitList.length ? `${detail.submitList.length} 条` : ''">
					<view v-if="detail.submitList.length" class="teacher-homework-submit-list">
						<view v-for="item in detail.submitList" :key="item.recordId" class="teacher-homework-submit-item">
							<view class="teacher-homework-submit-item__header">
								<view class="teacher-homework-submit-item__title">学员ID：{{ item.studentId }}</view>
								<view class="teacher-homework-submit-item__score">评分：{{ item.score }}</view>
							</view>
							<view class="teacher-homework-submit-item__meta">提交时间：{{ item.submitTime }}</view>
							<view class="teacher-homework-submit-item__block">
								<text class="teacher-homework-submit-item__label">提交内容</text>
								<text class="teacher-homework-submit-item__text">{{ item.submitContent }}</text>
							</view>
							<view class="teacher-homework-submit-item__block">
								<text class="teacher-homework-submit-item__label">点评内容</text>
								<text class="teacher-homework-submit-item__text">{{ item.comment || "暂无点评内容" }}</text>
							</view>
							<view class="teacher-homework-submit-item__meta">点评时间：{{ item.commentTime }}</view>
							<view class="teacher-homework-submit-item__meta">点评教师：{{ item.commentTeacher }}</view>
							<view class="teacher-homework-submit-item__actions">
								<wd-button size="small" plain :disabled="!item.canComment" @click="openCommentPopup(item)">
									{{ item.comment ? "重新点评" : "点评作业" }}
								</wd-button>
							</view>
						</view>
					</view>
					<teacher-empty-state v-else title="暂无提交记录" compact />
				</teacher-section-card>
			</template>

			<teacher-empty-state v-else :title="loading ? '加载中...' : '暂无作业详情'" compact />
		</view>

		<wd-popup v-model="popupVisible" position="bottom" custom-class="teacher-homework-comment-popup">
			<view class="teacher-homework-comment-popup__body">
				<view class="teacher-homework-comment-popup__title">点评作业</view>

				<view class="teacher-homework-comment-popup__group">
					<text class="teacher-homework-comment-popup__label">评分（0-100）</text>
					<input
						v-model="commentForm.score"
						class="teacher-homework-comment-popup__input"
						type="number"
						placeholder="请输入评分"
					/>
				</view>

				<view class="teacher-homework-comment-popup__group">
					<text class="teacher-homework-comment-popup__label">点评内容</text>
					<textarea
						v-model="commentForm.content"
						class="teacher-homework-comment-popup__textarea"
						placeholder="请输入点评内容"
						:maxlength="300"
					/>
				</view>

				<view class="teacher-homework-comment-popup__actions">
					<wd-button plain @click="closeCommentPopup">取消</wd-button>
					<wd-button type="primary" :loading="submitting" @click="submitComment">提交点评</wd-button>
				</view>
			</view>
		</wd-popup>
	</view>
</template>

<style scoped>
.teacher-homework-detail-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-homework-detail-page__content {
	padding: 12px;
}

.teacher-homework-detail-card {
	border-radius: 18px;
	background: #fff;
	padding: 18px 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-homework-detail-card__title {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.teacher-homework-detail-card__meta {
	margin-top: 10px;
	font-size: 13px;
	color: #98a2b3;
}

.teacher-homework-detail-card__content {
	margin-top: 16px;
	border-radius: 14px;
	background: #f8fafc;
	padding: 14px;
	font-size: 14px;
	line-height: 1.8;
	color: #475467;
	white-space: pre-wrap;
	word-break: break-word;
}

.teacher-homework-detail-card__attachment {
	margin-top: 16px;
	display: flex;
	flex-direction: column;
	gap: 8px;
	border-radius: 14px;
	background: #f8fafc;
	padding: 14px;
}

.teacher-homework-detail-card__attachment-label {
	font-size: 12px;
	color: #98a2b3;
}

.teacher-homework-detail-card__attachment-value {
	font-size: 14px;
	line-height: 1.7;
	color: #344054;
	word-break: break-word;
}

.teacher-homework-submit-list {
	padding: 12px 14px 16px;
}

.teacher-homework-submit-item {
	padding: 14px 0;
	border-bottom: 1px solid #edf0f5;
}

.teacher-homework-submit-item:last-child {
	border-bottom: 0;
}

.teacher-homework-submit-item__header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.teacher-homework-submit-item__title {
	font-size: 15px;
	font-weight: 600;
	color: #111827;
}

.teacher-homework-submit-item__score {
	flex-shrink: 0;
	border-radius: 999px;
	background: rgba(49, 199, 165, 0.12);
	padding: 4px 10px;
	font-size: 12px;
	font-weight: 600;
	color: #1ca386;
}

.teacher-homework-submit-item__meta {
	margin-top: 8px;
	font-size: 13px;
	color: #667085;
}

.teacher-homework-submit-item__block {
	margin-top: 10px;
	display: flex;
	flex-direction: column;
	gap: 6px;
}

.teacher-homework-submit-item__label {
	font-size: 12px;
	color: #98a2b3;
}

.teacher-homework-submit-item__text {
	font-size: 14px;
	line-height: 1.7;
	color: #475467;
	word-break: break-word;
	white-space: pre-wrap;
}

.teacher-homework-submit-item__actions {
	margin-top: 12px;
	display: flex;
	justify-content: flex-end;
}

.teacher-homework-comment-popup__body {
	padding: 22px 16px calc(env(safe-area-inset-bottom) + 20px);
	background: #fff;
}

.teacher-homework-comment-popup__title {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.teacher-homework-comment-popup__group {
	margin-top: 18px;
	display: flex;
	flex-direction: column;
	gap: 10px;
}

.teacher-homework-comment-popup__label {
	font-size: 14px;
	color: #344054;
}

.teacher-homework-comment-popup__input,
.teacher-homework-comment-popup__textarea {
	width: 100%;
	border-radius: 14px;
	background: #f8fafc;
	padding: 14px;
	font-size: 14px;
	color: #111827;
	box-sizing: border-box;
}

.teacher-homework-comment-popup__textarea {
	min-height: 120px;
	line-height: 1.7;
}

.teacher-homework-comment-popup__actions {
	margin-top: 22px;
	display: flex;
	justify-content: flex-end;
	gap: 10px;
}
</style>
