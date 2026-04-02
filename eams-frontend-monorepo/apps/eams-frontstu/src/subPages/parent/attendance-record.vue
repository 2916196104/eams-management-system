<script setup lang="ts">
import { computed, ref, watch } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useGlobalMessage } from "@/composables/useGlobalMessage";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "attendanceRecord",
	style: {
		navigationBarTitleText: "上课记录",
		titleNView: false,
	},
});

type AttendanceTab = "all" | "sign" | "leave" | "absent" | "patch";

interface AttendanceRecordItem {
	id?: number;
	signState?: string;
	decLessonCount?: number;
	signType?: string;
	signTime?: string;
	lessonId?: number;
	teacherId?: number;
	lessonTitle?: string;
	courseName?: string;
	canEvaluate?: boolean;
	date?: string;
	startTime?: string;
	endTime?: string;
}

interface AttendanceEvaluateDetail {
	id?: number;
	date?: string;
	startTime?: string;
	endTime?: string;
	title?: string;
	teacherNames?: string;
	assistantNames?: string;
	courseName?: string;
	className?: string;
	classroom?: string;
	teachType?: string;
	studentSignState?: string;
	studentDecLessonCount?: number;
	remark?: string;
	state?: string;
}

const userStore = useUserStore();
const globalMessage = useGlobalMessage();
const { currentStudent } = storeToRefs(userStore);

const activeTab = ref<AttendanceTab>("all");
const loading = ref(false);
const actionLoadingId = ref<number | null>(null);
const records = ref<Array<AttendanceRecordItem>>([]);

const studentId = computed(() => Number(currentStudent.value?.id || 0));

function normalizeRows(data: any): Array<AttendanceRecordItem> {
	const rows = Array.isArray(data?.rows) ? data.rows : [];
	return rows.map((item: any, index: number) => ({
		id: item?.id ?? item?.lesson_id ?? item?.lessonId ?? index + 1,
		signState: typeof item?.signState === "string" ? item.signState : Number(item?.signState) === 1 ? "补签" : "签到",
		decLessonCount: item?.decLessonCount,
		signType: item?.signType,
		signTime: item?.signTime,
		lessonId: Number(item?.lesson_id ?? item?.lessonId ?? 0) || undefined,
		teacherId: Number(item?.teacher_id ?? item?.teacherId ?? 0) || undefined,
		lessonTitle: item?.lessonTitle,
		courseName: item?.courseName,
		canEvaluate: Number(item?.canEvaluate || 0) === 1 || item?.canEvaluate === true,
		date: item?.date,
		startTime: item?.startTime,
		endTime: item?.endTime,
	}));
}

function resolveRecordCategory(record: AttendanceRecordItem): Exclude<AttendanceTab, "all"> {
	const text = `${record.signType || ""} ${record.signState || ""}`.toLowerCase();

	if (text.includes("请假") || text.includes("leave")) return "leave";
	if (text.includes("旷课") || text.includes("absent")) return "absent";
	if (text.includes("补签") || text.includes("patch")) return "patch";
	return "sign";
}

const countMap = computed(() =>
	records.value.reduce(
		(map, item) => {
			map.all += 1;
			map[resolveRecordCategory(item)] += 1;
			return map;
		},
		{ all: 0, sign: 0, leave: 0, absent: 0, patch: 0 },
	),
);

const tabs = computed(() => [
	{ label: "全部", value: "all" as const, count: countMap.value.all },
	{ label: "签到", value: "sign" as const, count: countMap.value.sign },
	{ label: "请假", value: "leave" as const, count: countMap.value.leave },
	{ label: "旷课", value: "absent" as const, count: countMap.value.absent },
	{ label: "补签", value: "patch" as const, count: countMap.value.patch },
]);

const filteredRecords = computed(() => {
	if (activeTab.value === "all") return records.value;
	return records.value.filter((item) => resolveRecordCategory(item) === activeTab.value);
});

function getStatusLabel(record: AttendanceRecordItem) {
	return record.signState || record.signType || "签到";
}

function getStatusClass(record: AttendanceRecordItem) {
	return `attendance-tag--${resolveRecordCategory(record)}`;
}

function getTimeRange(record: AttendanceRecordItem) {
	const dateText = record.date || "未设置日期";
	const timeText =
		record.startTime && record.endTime
			? `${record.startTime} - ${record.endTime}`
			: record.startTime || record.endTime || "未设置时间";
	return `${dateText} ${timeText}`;
}

function buildEvaluateMessage(detail?: AttendanceEvaluateDetail) {
	if (!detail) return "暂无可展示的课次信息";

	return [
		detail.courseName ? `课程：${detail.courseName}` : "",
		detail.title ? `课次：${detail.title}` : "",
		detail.className ? `班级：${detail.className}` : "",
		detail.teacherNames ? `教师：${detail.teacherNames}` : "",
		detail.assistantNames ? `助教：${detail.assistantNames}` : "",
		detail.classroom ? `教室：${detail.classroom}` : "",
		detail.teachType ? `授课方式：${detail.teachType}` : "",
		detail.date || detail.startTime || detail.endTime
			? `时间：${detail.date || ""} ${detail.startTime || ""}${detail.endTime ? ` - ${detail.endTime}` : ""}`.trim()
			: "",
		detail.studentSignState ? `签到状态：${detail.studentSignState}` : "",
		typeof detail.studentDecLessonCount === "number" ? `扣课时：${detail.studentDecLessonCount}` : "",
		detail.state ? `课程状态：${detail.state}` : "",
		detail.remark ? `备注：${detail.remark}` : "",
	]
		.filter(Boolean)
		.join("\n");
}

async function loadAttendanceRecords() {
	if (!studentId.value) {
		records.value = [];
		return;
	}

	loading.value = true;
	try {
		const res: any = await Apis.home.get_home_attendance_records_page_query_by_student_id({
			params: {
				student_id: studentId.value,
				pageIndex: 1,
				pageSize: 50,
			},
		});
		records.value = normalizeRows(res?.data);
	} catch {
		records.value = [];
		uni.showToast({ title: "上课记录加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

async function handleEvaluate(record: AttendanceRecordItem) {
	if (!record.canEvaluate || !studentId.value) return;
	if (!record.lessonId || !record.teacherId) {
		uni.showToast({ title: "当前记录缺少评价所需字段", icon: "none" });
		return;
	}

	globalMessage.prompt({
		title: "提交课次评价",
		msg: "请输入本次课次评价",
		inputPlaceholder: "请输入评价内容",
		success: async (res) => {
			if (res.action !== "confirm") return;

			const content = `${res.value || ""}`.trim();
			if (!content) {
				uni.showToast({ title: "评价内容不能为空", icon: "none" });
				return;
			}

			actionLoadingId.value = Number(record.id || 0);
			try {
				await (Apis as any).home.post_home_attendance_records_evaluate({
					data: {
						lesson_id: record.lessonId,
						teacher_id: record.teacherId,
						score1: 5,
						score2: 5,
						score3: 5,
						score4: 5,
						content,
						student_id: studentId.value,
						anonymity: 0,
					},
				});

				globalMessage.alert({
					title: "评价已提交",
					msg: buildEvaluateMessage({
						courseName: record.courseName,
						title: record.lessonTitle,
						date: record.date,
						startTime: record.startTime,
						endTime: record.endTime,
					}),
				});
			} catch {
				uni.showToast({ title: "提交评价失败", icon: "none" });
			} finally {
				actionLoadingId.value = null;
			}
		},
	});
}

async function refreshPage() {
	await loadAttendanceRecords();
	uni.showToast({ title: "已刷新", icon: "none" });
}

watch(
	studentId,
	() => {
		loadAttendanceRecords();
	},
	{ immediate: true },
);
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="上课记录" :show-refresh="true" @refresh="refreshPage" />
		<scroll-view class="tab-scroll" scroll-x>
			<view class="tab-bar">
				<view
					v-for="item in tabs"
					:key="item.value"
					class="tab-bar__item"
					:class="{ 'tab-bar__item--active': activeTab === item.value }"
					@click="activeTab = item.value"
				>
					{{ item.label }}({{ item.count }})
				</view>
			</view>
		</scroll-view>

		<view class="page-content">
			<view v-if="filteredRecords.length" class="record-list">
				<view v-for="item in filteredRecords" :key="item.id" class="record-card">
					<view class="record-card__header">
						<view>
							<view class="record-card__course">{{ item.courseName || "未命名课程" }}</view>
							<view class="record-card__lesson">{{ item.lessonTitle || "未命名课次" }}</view>
						</view>
						<view class="attendance-tag" :class="getStatusClass(item)">
							{{ getStatusLabel(item) }}
						</view>
					</view>

					<view class="record-card__meta">
						<view class="record-card__meta-item">
							<view class="i-carbon:calendar text-14px text-#94a3b8" />
							<text>{{ getTimeRange(item) }}</text>
						</view>
						<view class="record-card__meta-item">
							<view class="i-carbon:time text-14px text-#94a3b8" />
							<text>{{ item.signTime || "暂无签到时间" }}</text>
						</view>
					</view>

					<view class="record-card__footer">
						<text class="record-card__count">扣课时：{{ item.decLessonCount ?? 0 }}</text>
						<view
							v-if="item.canEvaluate"
							class="record-card__action"
							:class="{ 'record-card__action--loading': actionLoadingId === item.id }"
							@click="handleEvaluate(item)"
						>
							{{ actionLoadingId === item.id ? "加载中..." : "查看评价" }}
						</view>
					</view>
				</view>
			</view>

			<ParentEmptyState v-else :text="loading ? '加载中...' : '暂无记录'" min-height="180px" />
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.tab-scroll {
	white-space: nowrap;
	background: #f1f3f7;
}

.tab-bar {
	padding: 4px 0;
	display: inline-flex;
	min-width: 100%;
}

.tab-bar__item {
	flex-shrink: 0;
	min-width: 84px;
	height: 34px;
	display: flex;
	align-items: center;
	justify-content: center;
	font-size: 14px;
	color: #6b7280;
	border-radius: 8px;
	margin: 0 2px;
}

.tab-bar__item--active {
	background: #fff;
	color: #ff9800;
	font-weight: 600;
}

.page-content {
	padding: 12px;
}

.record-list {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.record-card {
	padding: 14px 16px;
	border-radius: 16px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
}

.record-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.record-card__course {
	font-size: 16px;
	font-weight: 700;
	color: #1f2937;
}

.record-card__lesson {
	margin-top: 6px;
	font-size: 13px;
	line-height: 1.5;
	color: #6b7280;
}

.attendance-tag {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 600;
}

.attendance-tag--sign {
	background: rgba(49, 199, 165, 0.12);
	color: #1ca386;
}

.attendance-tag--leave {
	background: rgba(91, 124, 255, 0.12);
	color: #4a67ef;
}

.attendance-tag--absent {
	background: rgba(255, 107, 107, 0.12);
	color: #e45454;
}

.attendance-tag--patch {
	background: rgba(255, 152, 0, 0.12);
	color: #d98a00;
}

.record-card__meta {
	margin-top: 12px;
	display: flex;
	flex-direction: column;
	gap: 8px;
}

.record-card__meta-item {
	display: flex;
	align-items: center;
	gap: 6px;
	font-size: 13px;
	color: #6b7280;
}

.record-card__footer {
	margin-top: 14px;
	padding-top: 12px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-top: 1px solid #eef2f7;
}

.record-card__count {
	font-size: 13px;
	color: #8b95a7;
}

.record-card__action {
	padding: 7px 12px;
	border-radius: 999px;
	background: rgba(49, 199, 165, 0.12);
	font-size: 13px;
	font-weight: 600;
	color: #1ca386;
}

.record-card__action--loading {
	opacity: 0.7;
}
</style>
