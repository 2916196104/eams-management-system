<template>
	<section class="calendar-container">
		<!-- 顶部栏：标题 -->
		<section class="calendar-header">
			<h3 class="calendar-title">{{ title }}</h3>
			<section class="header-slot">
				<slot name="header" :current-date="currentDate" :view-mode="viewMode"></slot>
			</section>
		</section>
		<!-- 工具栏：视图切换(左) + 月份居中 + 今天/前后月(右) -->
		<section class="calendar-toolbar">
			<div class="toolbar-left view-mode-group">
				<el-button
					v-for="item in viewModeOptions"
					:key="item.value"
					:type="viewMode === item.value ? 'primary' : 'default'"
					size="default"
					class="view-mode-btn"
					@click="viewMode = item.value"
				>
					{{ item.label }}
				</el-button>
			</div>
			<div class="toolbar-center">
				<span class="current-month">{{ displayTitle }}</span>
			</div>
			<div class="toolbar-right">
				<el-button type="primary" class="today-btn" size="default" @click="goToday">今天</el-button>
				<el-button type="primary" size="default" class="nav-btn" @click="prev">&lt;</el-button>
				<el-button type="primary" size="default" class="nav-btn" @click="next">&gt;</el-button>
			</div>
		</section>
		<!-- 月视图 -->
		<template v-if="viewMode === 'month'">
			<section class="calendar-weekdays">
				<span v-for="w in weekdays" :key="w" class="weekday-cell">{{ w }}</span>
			</section>
			<section class="calendar-grid">
				<div
					v-for="(cell, index) in monthCells"
					:key="index"
					class="calendar-cell"
					:class="{
						'is-other-month': !cell.isCurrentMonth,
						'is-today': cell.isToday,
						'is-selected': cell.isSelected,
					}"
					@click="handleCellClick(cell)"
				>
					<span class="cell-day">{{ cell.day }}日</span>
					<slot name="cell" :cell="cell"></slot>
				</div>
			</section>
		</template>
		<!-- 周视图：一周 7 天 + 时间段 -->
		<template v-else-if="viewMode === 'week'">
			<section class="week-view-header">
				<span class="time-col-label">时段</span>
				<span
					v-for="(day, idx) in weekViewDays"
					:key="idx"
					class="weekday-cell"
					:class="{ 'is-today': isToday(day), 'is-selected': isSameDay(day, selectedDate) }"
					@click="selectDate(day)"
				>
					{{ weekdays[idx] }}
					<br />
					{{ formatWeekDay(day) }}
				</span>
			</section>
			<section class="week-grid">
				<template v-for="hour in timeSlots" :key="hour">
					<div class="week-time-label">{{ String(hour).padStart(2, "0") }}:00</div>
					<div
						v-for="(day, dIdx) in weekViewDays"
						:key="`${hour}-${dIdx}`"
						class="week-cell"
						@click="handleWeekCellClick(day, hour)"
					>
						<slot name="week-cell" :date="day" :hour="hour"></slot>
					</div>
				</template>
			</section>
		</template>
		<!-- 日视图：单日时间段 -->
		<template v-else-if="viewMode === 'day'">
			<section class="day-view-header">
				<span class="day-view-date">{{ formatDay(viewCursor) }}</span>
			</section>
			<section class="day-grid">
				<div v-for="hour in dayViewHours" :key="hour" class="day-row">
					<div class="day-time-label">{{ String(hour).padStart(2, "0") }}:00</div>
					<div class="day-cell" @click="handleDayCellClick(hour)">
						<slot name="day-cell" :date="dayViewDate" :hour="hour"></slot>
					</div>
				</div>
			</section>
		</template>
	</section>
</template>

<script setup lang="ts">
import { ref, computed, watch } from "vue";
import type { CalendarViewMode, CalendarCell } from "./type";

const WEEKDAYS = ["周一", "周二", "周三", "周四", "周五", "周六", "周日"];

const props = withDefaults(
	defineProps<{
		title?: string;
		year?: number;
		month?: number;
		selectedDate?: Date | null;
		viewMode?: CalendarViewMode;
	}>(),
	{
		title: "",
		viewMode: "month",
	},
);

const emit = defineEmits<{
	(e: "update:selectedDate", value: Date | null): void;
	(e: "date-select", value: Date): void;
	(e: "update:year", value: number): void;
	(e: "update:month", value: number): void;
	(e: "update:viewMode", value: CalendarViewMode): void;
	(e: "week-cell-click", dateTime: Date): void;
	(e: "day-cell-click", dateTime: Date): void;
}>();

const now = new Date();
const currentYear = ref(props.year ?? now.getFullYear());
const currentMonth = ref(props.month ?? now.getMonth());
const viewMode = ref<CalendarViewMode>(props.viewMode);
const selectedDate = ref<Date | null>(props.selectedDate ?? null);

watch(
	() => [props.year, props.month],
	([y, m]) => {
		if (y != null) currentYear.value = y;
		if (m != null) currentMonth.value = m;
	},
);
watch(selectedDate, (v) => emit("update:selectedDate", v));
watch(viewMode, (v) => emit("update:viewMode", v));
watch(currentYear, (v) => emit("update:year", v));
watch(currentMonth, (v) => emit("update:month", v));

watch(viewMode, (mode) => {
	if (mode === "week") viewCursor.value = getMonday(selectedDate.value || new Date());
	else if (mode === "day") viewCursor.value = selectedDate.value ? new Date(selectedDate.value) : new Date();
});

const currentDate = computed(() => new Date(currentYear.value, currentMonth.value, 1));
const weekdays = WEEKDAYS;

function getInitialViewCursor(): Date {
	const d = props.selectedDate ? new Date(props.selectedDate) : new Date();
	d.setHours(0, 0, 0, 0);
	return d;
}

/** 周视图/日视图的锚点日期：周视图表示该周周一，日视图表示当前查看的日期 */
const viewCursor = ref<Date>(getInitialViewCursor());

/** 获取某日期所在周的周一 */
function getMonday(d: Date): Date {
	const date = new Date(d);
	date.setHours(0, 0, 0, 0);
	const day = date.getDay();
	const diff = (day + 6) % 7;
	date.setDate(date.getDate() - diff);
	return date;
}

/** 工具栏中间标题：月=年月，周=周范围，日=单日 */
const displayTitle = computed(() => {
	if (viewMode.value === "month") {
		return `${currentYear.value}年${currentMonth.value + 1}月`;
	}
	if (viewMode.value === "week") {
		const mon = getMonday(viewCursor.value);
		const sun = new Date(mon);
		sun.setDate(sun.getDate() + 6);
		return `${mon.getFullYear()}年${mon.getMonth() + 1}月${mon.getDate()}日 - ${sun.getMonth() + 1}月${sun.getDate()}日`;
	}
	return formatDay(viewCursor.value);
});

function isSameDay(a: Date, b: Date | null) {
	if (!b) return false;
	return a.getFullYear() === b.getFullYear() && a.getMonth() === b.getMonth() && a.getDate() === b.getDate();
}

function isToday(d: Date) {
	const t = new Date();
	return isSameDay(d, t);
}

/** 周视图：当前周 7 天 [周一..周日] */
const weekViewDays = computed<Date[]>(() => {
	const mon = getMonday(viewCursor.value);
	const days: Date[] = [];
	for (let i = 0; i < 7; i++) {
		const d = new Date(mon);
		d.setDate(mon.getDate() + i);
		days.push(d);
	}
	return days;
});

/** 周视图时间段（小时），默认 8–22 */
const timeSlots = computed(() => {
	const list: number[] = [];
	for (let h = 8; h <= 22; h++) list.push(h);
	return list;
});

/** 日视图时间段（小时），0–23 */
const dayViewHours = computed(() => {
	const list: number[] = [];
	for (let h = 0; h <= 23; h++) list.push(h);
	return list;
});

/** 日视图当前显示的日期 */
const dayViewDate = computed(() => {
	const d = new Date(viewCursor.value);
	d.setHours(0, 0, 0, 0);
	return d;
});

function formatWeekDay(d: Date) {
	return `${d.getMonth() + 1}/${d.getDate()}`;
}

function formatDay(d: Date) {
	return `${d.getFullYear()}年${d.getMonth() + 1}月${d.getDate()}日`;
}

function selectDate(d: Date) {
	selectedDate.value = new Date(d.getFullYear(), d.getMonth(), d.getDate());
	emit("date-select", selectedDate.value!);
}

function handleWeekCellClick(day: Date, hour: number) {
	const d = new Date(day.getFullYear(), day.getMonth(), day.getDate(), hour, 0, 0, 0);
	selectedDate.value = new Date(day.getFullYear(), day.getMonth(), day.getDate());
	emit("date-select", selectedDate.value);
	emit("week-cell-click", d);
}

function handleDayCellClick(hour: number) {
	const d = new Date(
		viewCursor.value.getFullYear(),
		viewCursor.value.getMonth(),
		viewCursor.value.getDate(),
		hour,
		0,
		0,
		0,
	);
	selectedDate.value = new Date(
		viewCursor.value.getFullYear(),
		viewCursor.value.getMonth(),
		viewCursor.value.getDate(),
	);
	emit("date-select", selectedDate.value);
	emit("day-cell-click", d);
}

const monthCells = computed<CalendarCell[]>(() => {
	const year = currentYear.value;
	const month = currentMonth.value;
	const first = new Date(year, month, 1);
	const firstWeekday = (first.getDay() + 6) % 7;
	const startOffset = 1 - firstWeekday;
	const cells: CalendarCell[] = [];
	const today = new Date();
	today.setHours(0, 0, 0, 0);

	for (let i = 0; i < 42; i++) {
		const d = new Date(year, month, startOffset + i);
		d.setHours(0, 0, 0, 0);
		const isCurrentMonth = d.getMonth() === month;
		const isToday =
			d.getFullYear() === today.getFullYear() && d.getMonth() === today.getMonth() && d.getDate() === today.getDate();
		const isSelected = isSameDay(d, selectedDate.value);
		cells.push({
			date: d,
			isCurrentMonth,
			day: d.getDate(),
			isToday,
			isSelected,
		});
	}
	return cells;
});

const viewModeOptions = [
	{ label: "月视图", value: "month" as CalendarViewMode },
	{ label: "周视图", value: "week" as CalendarViewMode },
	{ label: "日视图", value: "day" as CalendarViewMode },
];

function addDays(d: Date, delta: number): Date {
	const r = new Date(d);
	r.setDate(r.getDate() + delta);
	return r;
}

function syncSelectedDateByCursor() {
	const nextDate = new Date(viewCursor.value.getFullYear(), viewCursor.value.getMonth(), viewCursor.value.getDate());
	selectedDate.value = nextDate;
	emit("date-select", nextDate);
}

function prev() {
	if (viewMode.value === "month") {
		if (currentMonth.value === 0) {
			currentYear.value--;
			currentMonth.value = 11;
		} else {
			currentMonth.value--;
		}
	} else if (viewMode.value === "week") {
		viewCursor.value = addDays(viewCursor.value, -7);
		syncSelectedDateByCursor();
	} else {
		viewCursor.value = addDays(viewCursor.value, -1);
		syncSelectedDateByCursor();
	}
}

function next() {
	if (viewMode.value === "month") {
		if (currentMonth.value === 11) {
			currentYear.value++;
			currentMonth.value = 0;
		} else {
			currentMonth.value++;
		}
	} else if (viewMode.value === "week") {
		viewCursor.value = addDays(viewCursor.value, 7);
		syncSelectedDateByCursor();
	} else {
		viewCursor.value = addDays(viewCursor.value, 1);
		syncSelectedDateByCursor();
	}
}

function goToday() {
	const t = new Date();
	t.setHours(0, 0, 0, 0);
	currentYear.value = t.getFullYear();
	currentMonth.value = t.getMonth();
	viewCursor.value = new Date(t);
	selectedDate.value = new Date(t.getFullYear(), t.getMonth(), t.getDate());
	emit("date-select", selectedDate.value);
}

function handleCellClick(cell: CalendarCell) {
	selectedDate.value = new Date(cell.date.getFullYear(), cell.date.getMonth(), cell.date.getDate());
	emit("date-select", selectedDate.value);
}
</script>

<style scoped>
.calendar-container {
	width: 100%;
	background-color: #fff;
	border-radius: 5px;
	box-sizing: border-box;
	padding: 16px;
}

.calendar-header {
	margin-bottom: 16px;
	display: flex;
	flex-direction: row;
	justify-content: space-between;
	align-items: center;
}

.calendar-title {
	margin: 0;
	font-size: 16px;
	font-weight: 600;
	color: #303133;
}

.header-slot {
	display: flex;
	align-items: center;
	gap: 10px;
}

/* 工具栏：左-视图组 | 中-月份 | 右-今天/前后 */
.calendar-toolbar {
	display: grid;
	grid-template-columns: 1fr auto 1fr;
	align-items: center;
	margin-bottom: 16px;
	gap: 12px;
}

.toolbar-left {
	display: flex;
	justify-content: flex-start;
}

.toolbar-center {
	display: flex;
	justify-content: center;
	align-items: center;
}

.toolbar-right {
	display: flex;
	justify-content: flex-end;
	align-items: center;
	gap: 8px;
}

/* 视图切换按钮组：胶囊状紧密排列 */
.view-mode-group {
	display: inline-flex;
}

.view-mode-group .view-mode-btn {
	margin-left: 0;
	border-radius: 0;
}

.view-mode-group .view-mode-btn:first-child {
	border-radius: 4px 0 0 4px;
}

.view-mode-group .view-mode-btn:last-child {
	border-radius: 0 4px 4px 0;
}

.view-mode-group .el-button + .el-button {
	margin-left: -1px;
}

.current-month {
	font-size: 15px;
	color: #303133;
	font-weight: 500;
}

/* 今天按钮样式 */
.today-btn {
	/* 使用 primary 类型的默认蓝色 */
}

.nav-btn {
	min-width: 32px;
	padding-left: 10px;
	padding-right: 10px;
}

/* 星期标题行：灰色、居中、下方细线 */
.calendar-weekdays {
	display: grid;
	grid-template-columns: repeat(7, 1fr);
	font-size: 13px;
	color: #909399;
	text-align: center;
	border-bottom: 1px solid #ebeef5;
	background: #fff;
}

.weekday-cell {
	padding: 10px 0;
}

/* 日历网格：细灰色线分隔 */
.calendar-grid {
	display: grid;
	grid-template-columns: repeat(7, 1fr);
	font-size: 14px;
	border: 1px solid #ebeef5;
	border-right: none;
	border-bottom: none;
}

.calendar-cell {
	min-height: 80px;
	padding: 8px;
	display: flex;
	flex-direction: column;
	align-items: flex-start;
	justify-content: flex-start;
	cursor: pointer;
	box-sizing: border-box;
	border-right: 1px solid #ebeef5;
	border-bottom: 1px solid #ebeef5;
	background: #fff;
}

.calendar-cell:hover {
	background-color: #f5f7fa;
}

.calendar-cell.is-other-month .cell-day {
	color: #c0c4cc;
}

.calendar-cell .cell-day {
	color: #606266;
}

.calendar-cell.is-today .cell-day {
	color: var(--el-color-primary);
	font-weight: 600;
}

.calendar-cell.is-selected {
	background-color: #fcf5c4;
}

.calendar-cell.is-selected .cell-day {
	font-weight: 600;
	color: #606266;
}

.cell-day {
	line-height: 1.5;
}

/* 周视图：表头（时段 + 7 天），8 列 */
.week-view-header {
	display: grid;
	grid-template-columns: 60px repeat(7, 1fr);
	border: 1px solid #ebeef5;
	border-bottom: none;
	font-size: 13px;
	color: #909399;
	text-align: center;
	background: #fff;
}

.week-view-header .time-col-label {
	border-right: 1px solid #ebeef5;
	padding: 10px;
}

.week-view-header .weekday-cell {
	border-right: 1px solid #ebeef5;
	padding: 8px;
	cursor: pointer;
	line-height: 1.4;
}

.week-view-header .weekday-cell:last-child {
	border-right: none;
}

.week-view-header .weekday-cell.is-today {
	color: var(--el-color-primary);
	font-weight: 600;
}

.week-view-header .weekday-cell.is-selected {
	background-color: #fcf5c4;
	color: #606266;
}

.week-view-header .weekday-cell:hover {
	background-color: #f5f7fa;
}

/* 周视图：时间段网格 */
.week-grid {
	display: grid;
	grid-template-columns: 60px repeat(7, 1fr);
	border: 1px solid #ebeef5;
	font-size: 13px;
}

.week-time-label {
	padding: 8px 10px;
	color: #909399;
	border-right: 1px solid #ebeef5;
	border-bottom: 1px solid #ebeef5;
	background: #fafafa;
}

.week-cell {
	min-height: 48px;
	padding: 4px;
	border-right: 1px solid #ebeef5;
	border-bottom: 1px solid #ebeef5;
	cursor: pointer;
	background: #fff;
}

.week-cell:nth-child(7n + 1) {
	border-right: 1px solid #ebeef5;
}

/* 日视图：标题行 */
.day-view-header {
	border: 1px solid #ebeef5;
	border-bottom: none;
	padding: 12px 16px;
	background: #fafafa;
}

.day-view-date {
	font-size: 15px;
	color: #303133;
	font-weight: 500;
}

/* 日视图：时间段列表 */
.day-grid {
	border: 1px solid #ebeef5;
	border-top: none;
}

.day-row {
	display: grid;
	grid-template-columns: 60px 1fr;
	min-height: 48px;
	border-bottom: 1px solid #ebeef5;
}

.day-row:last-child {
	border-bottom: none;
}

.day-time-label {
	padding: 8px 10px;
	color: #909399;
	border-right: 1px solid #ebeef5;
	background: #fafafa;
	font-size: 13px;
}

.day-cell {
	padding: 8px;
	cursor: pointer;
	background: #fff;
}

.day-cell:hover {
	background-color: #f5f7fa;
}
</style>
