<script setup lang="ts">
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";
import { ref, reactive } from "vue";
import { useUserStore } from "@/store/userStore";
import { onShow } from "@dcloudio/uni-app";
import { Apis } from "@/api";

definePage({
	name: "teacherHomeworkPublish",
	style: {
		navigationBarTitleText: "布置作业内容",
		titleNView: false,
	},
});

interface HomeworkClassOption {
	id: string;
	name: string;
	label: string;
}

const userStore = useUserStore();
const showClassSheet = ref(false);
const classLoading = ref(false);
const submitting = ref(false);
const classOptions = ref<HomeworkClassOption[]>([]);

const publishForm = reactive({
	classId: "",
	className: "",
	title: "",
	content: "",
	attachment: "",
});

function normalizeClassOptions(source: unknown) {
	const payload = (source as any)?.data?.data ?? (source as any)?.data ?? source ?? {};
	const rawRows = Array.isArray(payload.rows)
		? payload.rows
		: Array.isArray(payload.list)
			? payload.list
			: Array.isArray(payload)
				? payload
				: [];

	return rawRows
		.map((item: any, index: number) => {
			const id = item.id ?? item.classId ?? item.class_id;
			if (id === undefined || id === null || id === "") return null;

			const name = item.className || item.classname || item.myclass || item.name || `班级${index + 1}`;
			const teacher = item.teacher || item.teacherName || item.masterTeacher || item.homeroom_teacher || "";
			const course = item.course || item.courseName || item.course_name || item.subject || "";

			return {
				id: String(id),
				name,
				label: [name, course, teacher].filter(Boolean).join(" / "),
			} satisfies HomeworkClassOption;
		})
		.filter((item: HomeworkClassOption | null): item is HomeworkClassOption => !!item);
}

async function ensureTeacherInfo() {
	if (userStore.teacherInfo.id) return;
	await userStore.loadCurrentUserInfo();
}

async function loadClassOptions() {
	classLoading.value = true;
	try {
		const response = await (Apis as any).class.get_class({
			params: {
				pageIndex: 1,
				pageSize: 50,
			},
		});

		classOptions.value = normalizeClassOptions(response);
		if (!publishForm.classId) {
			const firstItem = classOptions.value[0];
			if (firstItem) {
				publishForm.classId = firstItem.id;
				publishForm.className = firstItem.name;
			}
		}
	} catch {
		classOptions.value = [];
		uni.showToast({ title: "班级列表加载失败", icon: "none" });
	} finally {
		classLoading.value = false;
	}
}

async function refreshPage() {
	await Promise.all([ensureTeacherInfo(), loadClassOptions()]);
	uni.showToast({ title: "已刷新", icon: "none" });
}

function openClassSheet() {
	void loadClassOptions();
	showClassSheet.value = true;
}

function selectClass(item: HomeworkClassOption) {
	publishForm.classId = item.id;
	publishForm.className = item.name;
	showClassSheet.value = false;
}

async function submitForm() {
	if (!publishForm.classId) {
		uni.showToast({ title: "请选择班级", icon: "none" });
		return;
	}

	if (!publishForm.title.trim()) {
		uni.showToast({ title: "请输入作业标题", icon: "none" });
		return;
	}

	await ensureTeacherInfo();

	submitting.value = true;
	try {
		const response = await (Apis as any).workbench.post_workbench_homework_assign({
			data: {
				classId: publishForm.classId,
				title: publishForm.title.trim(),
				content: publishForm.content.trim() || undefined,
				images: publishForm.attachment.trim() || undefined,
			},
		});

		uni.showToast({ title: "发布作业成功", icon: "none" });
		const timer = setTimeout(() => {
			clearTimeout(timer);
			uni.navigateBack();
		}, 500);
	} catch {
		uni.showToast({ title: "发布作业失败", icon: "none" });
	} finally {
		submitting.value = false;
	}
}

onShow(() => {
	void Promise.all([ensureTeacherInfo(), loadClassOptions()]);
});
</script>

<template>
  <view class="teacher-publish-page">
    <teacher-nav-bar title="布置作业内容" @refresh="refreshPage" />

    <view class="teacher-publish-card">
      <view class="teacher-publish-row" @click="openClassSheet">
        <text class="teacher-publish-label teacher-publish-label--required">
          选择班级
        </text>
        <view class="teacher-publish-value-wrap">
          <text class="teacher-publish-value" :class="{ 'teacher-publish-value--selected': publishForm.className }">
            {{ publishForm.className || (classLoading ? "加载中..." : "请选择") }}
          </text>
          <view class="i-carbon:chevron-right text-16px text-#98a2b3" />
        </view>
      </view>

      <view class="teacher-publish-row">
        <text class="teacher-publish-label teacher-publish-label--required">
          作业标题
        </text>
        <input
          v-model="publishForm.title"
          class="teacher-publish-input"
          type="text"
          :maxlength="60"
          placeholder="请输入标题"
        >
      </view>

      <view class="teacher-publish-row teacher-publish-row--textarea">
        <text class="teacher-publish-label">
          作业内容
        </text>
        <textarea
          v-model="publishForm.content"
          class="teacher-publish-textarea"
          placeholder="请输入作业内容"
          :maxlength="500"
        />
      </view>

      <view class="teacher-publish-row teacher-publish-row--textarea">
        <text class="teacher-publish-label">
          附件说明/地址
        </text>
        <textarea
          v-model="publishForm.attachment"
          class="teacher-publish-textarea teacher-publish-textarea--small"
          placeholder="请输入附件说明或附件地址"
          :maxlength="300"
        />
      </view>
    </view>

    <view class="teacher-publish-action">
      <wd-button type="primary" block :loading="submitting" @click="submitForm">
        提交
      </wd-button>
    </view>

    <wd-action-sheet
      v-model="showClassSheet"
      title="选择班级"
      :close-on-click-action="false"
      :close-on-click-modal="true"
    >
      <view class="teacher-sheet">
        <view v-for="item in classOptions" :key="item.id" class="teacher-sheet__item" @click="selectClass(item)">
          <view class="teacher-sheet__content">
            <view class="teacher-sheet__title">
              {{ item.name }}
            </view>
            <view class="teacher-sheet__desc">
              {{ item.label }}
            </view>
          </view>
          <view v-if="publishForm.classId === item.id" class="i-carbon:checkmark text-18px text-#31c7a5" />
        </view>
        <view v-if="!classOptions.length" class="teacher-sheet__empty">
          {{ classLoading ? "班级加载中..." : "暂无班级数据" }}
        </view>
      </view>
    </wd-action-sheet>
  </view>
</template>

<style scoped>
.teacher-publish-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-publish-card {
	margin-top: 10px;
	background: #fff;
}

.teacher-publish-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
	padding: 16px;
	border-bottom: 1px solid #edf0f5;
}

.teacher-publish-row--textarea {
	align-items: flex-start;
	flex-direction: column;
}

.teacher-publish-label {
	font-size: 15px;
	color: #111827;
}

.teacher-publish-label--required::before {
	content: "*";
	margin-right: 2px;
	color: #f04438;
}

.teacher-publish-value-wrap {
	display: flex;
	align-items: center;
	gap: 8px;
	min-width: 0;
}

.teacher-publish-value {
	max-width: 210px;
	font-size: 15px;
	color: #98a2b3;
	text-align: right;
	overflow: hidden;
	text-overflow: ellipsis;
	white-space: nowrap;
}

.teacher-publish-value--selected {
	color: #344054;
}

.teacher-publish-input {
	flex: 1;
	min-width: 0;
	font-size: 15px;
	color: #111827;
	text-align: right;
}

.teacher-publish-textarea {
	width: 100%;
	min-height: 132px;
	font-size: 15px;
	line-height: 1.6;
	color: #111827;
}

.teacher-publish-textarea--small {
	min-height: 88px;
}

.teacher-publish-action {
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
	gap: 12px;
	padding: 14px 0;
	border-bottom: 1px solid #edf0f5;
}

.teacher-sheet__content {
	min-width: 0;
}

.teacher-sheet__title {
	font-size: 15px;
	color: #111827;
}

.teacher-sheet__desc {
	margin-top: 4px;
	font-size: 12px;
	color: #98a2b3;
	word-break: break-all;
}

.teacher-sheet__empty {
	padding: 18px 0;
	font-size: 14px;
	color: #98a2b3;
	text-align: center;
}
</style>
