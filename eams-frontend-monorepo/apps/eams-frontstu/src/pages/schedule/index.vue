<script setup lang="ts">
import { computed, ref, watch } from "vue";
import { storeToRefs } from "pinia";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import ParentSectionCard from "@/components/parent/ParentSectionCard.vue";
import { useGlobalMessage } from "@/composables/useGlobalMessage";
import { useGlobalToast } from "@/composables/useGlobalToast";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "schedule",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "课表",
		titleNView: false,
	},
});

// 课表记录结构
interface ScheduleItem {
	id?: number;
	startTime?: string;
	endTime?: string;
	courseStatusText?: string;
	scheduleType?: number;
	className?: string;
	courseName?: string;
	teacherName?: string;
	classroomName?: string;
	signInStatusText?: string;
	canSignIn?: boolean;
	canLeave?: boolean;
	canReserve?: boolean;
}

// 日历面板单元结构
interface CalendarCell {
	key: string;
	day: number;
	date: string;
	currentMonth: boolean;
	selected: boolean;
	today: boolean;
	hasCourse: boolean;
}

const weekdayList = ["一", "二", "三", "四", "五", "六", "日"];
// 页面基础状态
const userStore = useUserStore();
const globalToast = useGlobalToast();
const globalMessage = useGlobalMessage();
const { currentStudent } = storeToRefs(userStore);

const today = new Date();
const currentMonth = ref(new Date(today.getFullYear(), today.getMonth(), 1));
const selectedDate = ref(formatDate(today));
const calendarCollapsed = ref(false);
const loading = ref(false);
const actionLoadingId = ref<number | null>(null);
const scheduleList = ref<Array<ScheduleItem>>([]);

// 当前学生与页面展示数据
const studentId = computed(() => Number(currentStudent.value?.id || 0));
const monthLabel = computed(() => {
	const year = currentMonth.value.getFullYear();
	const month = `${currentMonth.value.getMonth() + 1}`.padStart(2, "0");
	return `${year}年${month}月`;
});

const selectedDayText = computed(() => {
	const date = parseDate(selectedDate.value);
	return `${date.getMonth() + 1}.${date.getDate()}`;
});

const courseList = computed(() => scheduleList.value.filter((item) => item.scheduleType !== 2 && !item.canReserve));

const reserveList = computed(() => scheduleList.value.filter((item) => item.scheduleType === 2 || item.canReserve));

// 根据当前月份构建日历面板
const calendarCells = computed<Array<CalendarCell>>(() => {
	const year = currentMonth.value.getFullYear();
	const month = currentMonth.value.getMonth();
	const firstDay = new Date(year, month, 1);
	const lastDay = new Date(year, month + 1, 0);
	const firstWeekday = (firstDay.getDay() + 6) % 7;
	const totalDays = lastDay.getDate();
	const cells: Array<CalendarCell> = [];

	for (let i = 0; i < firstWeekday; i += 1) {
		cells.push({
			key: `empty-prev-${i}`,
			day: 0,
			date: "",
			currentMonth: false,
			selected: false,
			today: false,
			hasCourse: false,
		});
	}

	for (let day = 1; day <= totalDays; day += 1) {
		const date = formatDate(new Date(year, month, day));
		cells.push({
			key: date,
			day,
			date,
			currentMonth: true,
			selected: selectedDate.value === date,
			today: formatDate(today) === date,
			hasCourse: scheduleList.value.length > 0 && selectedDate.value === date,
		});
	}

	for (let i = cells.length; i < 35; i += 1) {
		cells.push({
			key: `empty-next-${i}`,
			day: 0,
			date: "",
			currentMonth: false,
			selected: false,
			today: false,
			hasCourse: false,
		});
	}

	return cells;
});

function formatDate(date: Date) {
	const year = date.getFullYear();
	const month = `${date.getMonth() + 1}`.padStart(2, "0");
	const day = `${date.getDate()}`.padStart(2, "0");
	return `${year}-${month}-${day}`;
}

function parseDate(dateText: string) {
	const [year, month, day] = dateText.split("-").map(Number);
	return new Date(year, month - 1, day);
}

function normalizeScheduleList(data: any): Array<ScheduleItem> {
	const rows = Array.isArray(data?.rows) ? data.rows : Array.isArray(data) ? data : [];
	return rows.map((item: any) => ({
		id: Number(item?.id || 0) || undefined,
		startTime: item?.startTime,
		endTime: item?.endTime,
		courseStatusText: item?.state,
		scheduleType: item?.bookable ? 2 : 1,
		className: item?.className,
		courseName: item?.courseName,
		teacherName: item?.teacherNames,
		classroomName: item?.classroom,
		signInStatusText: item?.studentSignState,
		canSignIn: Boolean(item?.studentCanSign),
		canLeave: Boolean(item?.studentCanLeave),
		canReserve: Boolean(item?.bookable),
	}));
}

function scheduleStatusClass(text?: string) {
	if (!text) return "schedule-card__tag--default";
	if (text.includes("进行")) return "schedule-card__tag--success";
	if (text.includes("开始")) return "schedule-card__tag--warn";
	return "schedule-card__tag--default";
}

function goPrevMonth() {
	const next = new Date(currentMonth.value);
	next.setMonth(next.getMonth() - 1);
	currentMonth.value = new Date(next.getFullYear(), next.getMonth(), 1);
	selectedDate.value = formatDate(new Date(next.getFullYear(), next.getMonth(), 1));
}

function goNextMonth() {
	const next = new Date(currentMonth.value);
	next.setMonth(next.getMonth() + 1);
	currentMonth.value = new Date(next.getFullYear(), next.getMonth(), 1);
	selectedDate.value = formatDate(new Date(next.getFullYear(), next.getMonth(), 1));
}

function selectDate(cell: CalendarCell) {
	if (!cell.currentMonth || !cell.date) return;
	selectedDate.value = cell.date;
}

function toggleCalendar() {
	calendarCollapsed.value = !calendarCollapsed.value;
}

// 拉取当前日期课表
async function loadSchedule() {
	loading.value = true;
	try {
		const res: any = await (Apis as any).schedule.get_schedule_query({
			params: {
				date: selectedDate.value,
				pageIndex: 1,
				pageSize: 100,
			},
		});
		scheduleList.value = normalizeScheduleList(res?.data);
	} catch {
		scheduleList.value = [];
		globalToast.error("课表加载失败");
	} finally {
		loading.value = false;
	}
}

// 课表操作
async function handleReserve(item: ScheduleItem) {
	const scheduleId = Number(item.id || 0);
	if (!scheduleId || !studentId.value) {
		globalToast.error("缺少预约信息");
		return;
	}

	globalMessage.confirm({
		title: "预约课程",
		msg: `确认预约“${item.courseName || item.className || "当前课次"}”吗？`,
		success: async (res) => {
			if (res.action !== "confirm") return;

			actionLoadingId.value = scheduleId;
			try {
				const response: any = await (Apis as any).schedule.post_schedule_appointment({
					data: {
						lessonId: scheduleId,
						studentId: studentId.value,
					},
				});
				globalToast.success(response?.message || "预约成功");
				await loadSchedule();
			} catch {
				globalToast.error("预约失败");
			} finally {
				actionLoadingId.value = null;
			}
		},
	});
}

async function handleSignIn(item: ScheduleItem) {
	const scheduleId = Number(item.id || 0);
	if (!scheduleId) {
		globalToast.error("缺少签到信息");
		return;
	}

	globalMessage.confirm({
		title: "课程签到",
		msg: `确认签到“${item.courseName || item.className || "当前课次"}”吗？`,
		success: async (res) => {
			if (res.action !== "confirm") return;

			actionLoadingId.value = scheduleId;
			try {
				const response: any = await (Apis as any).schedule.post_schedule_sign_in({
					pathParams: {
						lessonId: scheduleId,
					},
				});
				globalToast.success(response?.message || "签到成功");
				await loadSchedule();
			} catch {
				globalToast.error("签到失败");
			} finally {
				actionLoadingId.value = null;
			}
		},
	});
}

function handleLeave(item: ScheduleItem) {
	const scheduleId = Number(item.id || 0);
	if (!scheduleId || !studentId.value) {
		globalToast.error("缺少请假信息");
		return;
	}

	globalMessage.prompt({
		title: "请假申请",
		msg: `请填写“${item.courseName || item.className || "当前课次"}”的请假原因`,
		inputPlaceholder: "请输入请假原因",
		success: async (res) => {
			if (res.action !== "confirm") return;

			const reason = `${res.value || ""}`.trim();
			if (!reason) {
				globalToast.warning("请假原因不能为空");
				return;
			}

			actionLoadingId.value = scheduleId;
			try {
				const response: any = await (Apis as any).schedule.post_schedule_leave({
					data: {
						lessonId: scheduleId,
						studentId: studentId.value,
						reason,
					},
				});
				globalToast.success(response?.message || "请假成功");
				await loadSchedule();
			} catch {
				globalToast.error("请假失败");
			} finally {
				actionLoadingId.value = null;
			}
		},
	});
}

async function refreshPage() {
	await loadSchedule();
	globalToast.success("已刷新");
}

watch(selectedDate, () => {
	loadSchedule();
});

onMounted(() => {
	loadSchedule();
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="课表" :show-back="false" :show-refresh="true" @refresh="refreshPage" />

		<view class="page-shell__content">
			<!-- 月份切换与日历面板 -->
			<view class="calendar-card">
				<view class="calendar-card__toolbar">
					<view class="calendar-card__month-btn" @click="goPrevMonth">上个月</view>
					<view class="calendar-card__month-title">{{ monthLabel }}</view>
					<view class="calendar-card__month-btn" @click="goNextMonth">下个月</view>
				</view>

				<view v-show="!calendarCollapsed" class="calendar-card__body">
					<view class="calendar-card__weekdays">
						<text v-for="item in weekdayList" :key="item" class="calendar-card__weekday">{{ item }}</text>
					</view>

					<view class="calendar-card__grid">
						<view
							v-for="cell in calendarCells"
							:key="cell.key"
							class="calendar-card__cell"
							:class="{
								'calendar-card__cell--placeholder': !cell.currentMonth,
								'calendar-card__cell--selected': cell.selected,
								'calendar-card__cell--today': cell.today && !cell.selected,
							}"
							@click="selectDate(cell)"
						>
							<text v-if="cell.currentMonth" class="calendar-card__day">{{ cell.day }}</text>
							<view v-if="cell.hasCourse" class="calendar-card__dot" />
						</view>
					</view>
				</view>

				<view class="calendar-card__toggle" @click="toggleCalendar">
					<view
						class="i-carbon:chevron-up text-18px text-#a0a8b8"
						:class="{ 'calendar-card__toggle-icon--collapsed': calendarCollapsed }"
					/>
				</view>
			</view>

			<!-- 当日正式课表 -->
			<ParentSectionCard
				:title="`${selectedDayText} 课表`"
				:right-text="courseList.length ? `${courseList.length} 节` : '本日无课'"
			>
				<view v-if="courseList.length" class="schedule-list">
					<view v-for="item in courseList" :key="`course-${item.id}`" class="schedule-card">
						<view class="schedule-card__header">
							<view>
								<view class="schedule-card__title">{{ item.courseName || item.className || "未命名课程" }}</view>
								<view class="schedule-card__time">{{ item.startTime || "--:--" }} - {{ item.endTime || "--:--" }}</view>
							</view>
							<view class="schedule-card__tag" :class="scheduleStatusClass(item.courseStatusText)">
								{{ item.courseStatusText || "待安排" }}
							</view>
						</view>

						<view class="schedule-card__meta">
							<text>{{ item.className || "未分班" }}</text>
							<text>{{ item.teacherName || "待分配老师" }}</text>
							<text>{{ item.classroomName || "待分配教室" }}</text>
						</view>

						<view class="schedule-card__footer">
							<text class="schedule-card__signin">{{ item.signInStatusText || "未签到" }}</text>
							<view class="schedule-card__actions">
								<view
									v-if="item.canLeave"
									class="schedule-card__action schedule-card__action--secondary"
									@click="handleLeave(item)"
								>
									{{ actionLoadingId === item.id ? "请假中..." : "请假" }}
								</view>
								<view
									v-if="item.canSignIn"
									class="schedule-card__action schedule-card__action--primary"
									@click="handleSignIn(item)"
								>
									{{ actionLoadingId === item.id ? "签到中..." : "签到" }}
								</view>
							</view>
						</view>
					</view>
				</view>

				<ParentEmptyState v-else :text="loading ? '加载中...' : '本日无课'" min-height="160px" />
			</ParentSectionCard>

			<!-- 当日可预约课表 -->
			<ParentSectionCard
				:title="`${selectedDayText} 预约课`"
				:right-text="reserveList.length ? `${reserveList.length} 节` : '本日无可预约课程'"
			>
				<view v-if="reserveList.length" class="schedule-list">
					<view v-for="item in reserveList" :key="`reserve-${item.id}`" class="schedule-card">
						<view class="schedule-card__header">
							<view>
								<view class="schedule-card__title">{{ item.courseName || item.className || "未命名预约课" }}</view>
								<view class="schedule-card__time">{{ item.startTime || "--:--" }} - {{ item.endTime || "--:--" }}</view>
							</view>
							<view class="schedule-card__tag schedule-card__tag--reserve">
								{{ item.courseStatusText || "可预约" }}
							</view>
						</view>

						<view class="schedule-card__meta">
							<text>{{ item.className || "未分班" }}</text>
							<text>{{ item.teacherName || "待分配老师" }}</text>
							<text>{{ item.classroomName || "待分配教室" }}</text>
						</view>

						<view class="schedule-card__footer">
							<text class="schedule-card__signin">{{ item.signInStatusText || "未预约" }}</text>
							<view
								v-if="item.canReserve"
								class="schedule-card__action schedule-card__action--primary"
								@click="handleReserve(item)"
							>
								{{ actionLoadingId === item.id ? "预约中..." : "预约" }}
							</view>
						</view>
					</view>
				</view>

				<ParentEmptyState v-else :text="loading ? '加载中...' : '本日无可预约课程'" min-height="160px" />
			</ParentSectionCard>
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.page-shell__content {
	padding: 14px 12px 24px;
	display: flex;
	flex-direction: column;
	gap: 14px;
}

.calendar-card {
	border-radius: 18px;
	background: #fff;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.06);
	overflow: hidden;
}

.calendar-card__toolbar {
	padding: 16px 18px 12px;
	display: flex;
	align-items: center;
	justify-content: space-between;
}

.calendar-card__month-btn {
	padding: 6px 12px;
	border-radius: 999px;
	border: 1px solid rgba(39, 199, 159, 0.28);
	font-size: 13px;
	color: #12b48f;
}

.calendar-card__month-title {
	font-size: 24px;
	font-weight: 700;
	color: #1f2937;
}

.calendar-card__body {
	padding: 0 12px 8px;
}

.calendar-card__weekdays,
.calendar-card__grid {
	display: grid;
	grid-template-columns: repeat(7, minmax(0, 1fr));
}

.calendar-card__weekday {
	padding: 10px 0;
	text-align: center;
	font-size: 14px;
	color: #14b8a6;
}

.calendar-card__cell {
	height: 44px;
	position: relative;
	display: flex;
	align-items: center;
	justify-content: center;
}

.calendar-card__cell--placeholder {
	pointer-events: none;
}

.calendar-card__day {
	width: 30px;
	height: 30px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 50%;
	font-size: 16px;
	color: #334155;
}

.calendar-card__cell--today .calendar-card__day {
	color: #12b48f;
}

.calendar-card__cell--selected .calendar-card__day {
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	color: #fff;
}

.calendar-card__dot {
	position: absolute;
	bottom: 6px;
	width: 4px;
	height: 4px;
	border-radius: 50%;
	background: #12b48f;
}

.calendar-card__toggle {
	height: 28px;
	display: flex;
	align-items: center;
	justify-content: center;
}

.calendar-card__toggle-icon--collapsed {
	transform: rotate(180deg);
}

.schedule-list {
	padding: 12px;
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.schedule-card {
	padding: 14px;
	border-radius: 16px;
	background: #f8fafc;
}

.schedule-card__header {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 12px;
}

.schedule-card__title {
	font-size: 16px;
	font-weight: 700;
	line-height: 1.5;
	color: #111827;
}

.schedule-card__time {
	margin-top: 6px;
	font-size: 13px;
	color: #64748b;
}

.schedule-card__tag {
	flex-shrink: 0;
	padding: 4px 10px;
	border-radius: 999px;
	font-size: 12px;
	font-weight: 700;
}

.schedule-card__tag--success {
	background: rgba(34, 197, 94, 0.12);
	color: #16a34a;
}

.schedule-card__tag--warn {
	background: rgba(245, 158, 11, 0.12);
	color: #d97706;
}

.schedule-card__tag--default {
	background: rgba(148, 163, 184, 0.12);
	color: #64748b;
}

.schedule-card__tag--reserve {
	background: rgba(39, 199, 159, 0.12);
	color: #12b48f;
}

.schedule-card__meta {
	margin-top: 10px;
	display: flex;
	flex-wrap: wrap;
	gap: 10px;
	font-size: 12px;
	color: #8b95a7;
}

.schedule-card__footer {
	margin-top: 12px;
	padding-top: 12px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
	border-top: 1px solid #e9eef5;
}

.schedule-card__signin {
	font-size: 13px;
	color: #475569;
}

.schedule-card__actions {
	display: flex;
	align-items: center;
	gap: 8px;
}

.schedule-card__action {
	height: 34px;
	padding: 0 14px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	font-size: 13px;
	font-weight: 700;
}

.schedule-card__action--primary {
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	color: #fff;
}

.schedule-card__action--secondary {
	background: #fff;
	border: 1px solid #dbe5f0;
	color: #64748b;
}
</style>
