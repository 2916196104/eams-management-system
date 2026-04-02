<script setup lang="ts">
import { computed, ref } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useGlobalMessage } from "@/composables/useGlobalMessage";
import { useGlobalToast } from "@/composables/useGlobalToast";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "homeworkDetail",
	style: {
		navigationBarTitleText: "作业详情",
		titleNView: false,
	},
});

interface HomeworkDetail {
	id?: number;
	title?: string;
	classId?: number;
	content?: string;
	addTime?: string;
}

interface HomeworkSubmitResult {
	recordId?: number;
	homeworkId?: number;
	studentId?: number;
	content?: string;
	images?: string;
	addTime?: string;
}

const route = useRoute() as any;
const userStore = useUserStore();
const globalMessage = useGlobalMessage();
const globalToast = useGlobalToast();
const { currentStudent } = storeToRefs(userStore);

const loading = ref(false);
const submitLoading = ref(false);
const deleteLoading = ref(false);
const detail = ref<HomeworkDetail | null>(null);
const submitResult = ref<HomeworkSubmitResult | null>(null);

const homeworkId = computed(() => Number(route.query?.id || 0));
const studentId = computed(() => Number(currentStudent.value?.id || 0));
const deleteRecordId = computed(() => Number(submitResult.value?.recordId || 0));

function normalizeSubmitResult(res: any): HomeworkSubmitResult | null {
	if (!res) return null;
	return res.data && typeof res.data === "object" ? res.data : res;
}

async function loadHomeworkDetail() {
	if (!homeworkId.value) {
		detail.value = null;
		return;
	}

	loading.value = true;
	try {
		const res: any = await Apis.home.get_c1_homework_detail({
			params: {
				id: homeworkId.value,
			},
		});
		detail.value = res?.data || null;
	} catch {
		detail.value = null;
		uni.showToast({ title: "作业详情加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

function askSubmitContent() {
	if (!studentId.value || !homeworkId.value) {
		globalToast.error("缺少学生或作业信息");
		return;
	}

	globalMessage.prompt({
		title: "提交作业",
		msg: "请输入作业内容",
		inputPlaceholder: "请输入本次作业说明",
		success: async (res) => {
			if (res.action !== "confirm") return;

			const content = `${res.value || ""}`.trim();
			if (!content) {
				globalToast.warning("作业内容不能为空");
				return;
			}

			await submitHomework(content);
		},
	});
}

async function submitHomework(content: string) {
	submitLoading.value = true;
	try {
		const res: any = await (Apis as any).home.post_c1_homework_submit({
			data: {
				homeworkId: homeworkId.value,
				studentId: studentId.value,
				editor: Number(userStore.userInfo.id || 0),
				homework_content: detail.value?.content || content,
				homework_record_content: content,
				images: "",
				editTime: new Date().toISOString(),
			},
		});

		submitResult.value = normalizeSubmitResult(res);
		globalToast.success("作业提交成功");
	} catch {
		globalToast.error("作业提交失败");
	} finally {
		submitLoading.value = false;
	}
}

function confirmDeleteHomework() {
	if (!homeworkId.value) {
		globalToast.error("缺少作业信息");
		return;
	}

	globalMessage.confirm({
		title: "删除作业",
		msg: "删除后将无法恢复，确定要删除这份作业吗？",
		success: async (res) => {
			if (res.action !== "confirm") return;
			await deleteHomework();
		},
	});
}

async function deleteHomework() {
	if (!deleteRecordId.value) {
		globalToast.warning("当前缺少作业记录 ID，暂时无法删除");
		return;
	}

	deleteLoading.value = true;
	try {
		await (Apis as any).home.delete_c1_homework_delete({
			pathParams: {
				id: deleteRecordId.value,
			},
			params: {
				homeworkId: homeworkId.value,
				studentId: studentId.value,
			},
		});

		globalToast.success("作业已删除");
		setTimeout(() => {
			uni.navigateBack();
		}, 250);
	} catch {
		globalToast.error("删除作业失败");
	} finally {
		deleteLoading.value = false;
	}
}

async function refreshPage() {
	await loadHomeworkDetail();
	uni.showToast({ title: "已刷新", icon: "none" });
}

onMounted(() => {
	loadHomeworkDetail();
});
</script>

<template>
	<view class="detail-page">
		<ParentNavBar title="作业详情" :show-refresh="true" @refresh="refreshPage" />
		<view class="detail-page__content">
			<view v-if="detail" class="detail-card">
				<view class="detail-card__section">
					<view class="detail-card__label">作业标题</view>
					<view class="detail-card__title">{{ detail.title || "未命名作业" }}</view>
				</view>

				<view class="detail-card__section">
					<view class="detail-card__label">班级名称</view>
					<view class="detail-card__text">{{ detail.classId || "未设置班级" }}</view>
				</view>

				<view class="detail-card__section">
					<view class="detail-card__label">作业内容</view>
					<view class="detail-card__content">{{ detail.content || "暂无作业内容" }}</view>
				</view>

				<view v-if="submitResult" class="detail-card__section detail-card__submit">
					<view class="detail-card__label">最近一次提交</view>
					<view class="detail-card__text">提交时间：{{ submitResult.addTime || "刚刚提交" }}</view>
					<view class="detail-card__content">{{ submitResult.content || "已提交作业" }}</view>
				</view>
			</view>

			<ParentEmptyState v-else :text="loading ? '加载中...' : '暂无详情'" min-height="180px" />
		</view>

		<view v-if="detail" class="detail-page__footer">
			<view class="detail-page__footer-actions">
				<view
					class="detail-page__delete-btn"
					:class="{ 'detail-page__delete-btn--loading': deleteLoading }"
					@click="confirmDeleteHomework"
				>
					{{ deleteLoading ? "删除中..." : "删除作业" }}
				</view>
				<view
					class="detail-page__submit-btn"
					:class="{ 'detail-page__submit-btn--loading': submitLoading }"
					@click="askSubmitContent"
				>
					{{ submitLoading ? "提交中..." : "提交作业" }}
				</view>
			</view>
		</view>
	</view>
</template>

<style scoped>
.detail-page {
	min-height: 100vh;
	background: #f5f7fb;
}

.detail-page__content {
	padding: 12px 12px 92px;
}

.detail-card {
	padding: 18px 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
	display: flex;
	flex-direction: column;
	gap: 18px;
}

.detail-card__section {
	display: flex;
	flex-direction: column;
	gap: 8px;
}

.detail-card__label {
	font-size: 13px;
	font-weight: 600;
	color: #94a3b8;
}

.detail-card__title {
	font-size: 18px;
	font-weight: 700;
	line-height: 1.6;
	color: #1f2937;
}

.detail-card__text {
	font-size: 15px;
	line-height: 1.6;
	color: #475569;
}

.detail-card__content {
	font-size: 15px;
	line-height: 1.8;
	color: #334155;
	white-space: pre-wrap;
	word-break: break-all;
}

.detail-card__submit {
	padding-top: 14px;
	border-top: 1px solid #eef2f7;
}

.detail-page__footer {
	position: fixed;
	left: 0;
	right: 0;
	bottom: 0;
	padding: 12px 16px calc(12px + env(safe-area-inset-bottom));
	background: rgba(245, 247, 251, 0.96);
}

.detail-page__footer-actions {
	display: grid;
	grid-template-columns: 132px 1fr;
	gap: 12px;
}

.detail-page__delete-btn,
.detail-page__submit-btn {
	height: 46px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	font-size: 16px;
	font-weight: 700;
}

.detail-page__delete-btn {
	background: #fff;
	color: #ef4444;
	border: 1px solid rgba(239, 68, 68, 0.18);
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.detail-page__submit-btn {
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	color: #fff;
	box-shadow: 0 10px 20px rgba(49, 199, 165, 0.22);
}

.detail-page__delete-btn--loading,
.detail-page__submit-btn--loading {
	opacity: 0.75;
}
</style>
