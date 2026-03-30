<script setup lang="ts">
interface CalendarDay {
	key: string;
	label: number;
	date: string;
	currentMonth: boolean;
	selected: boolean;
}

const props = defineProps<{
	modelValue: string;
}>();

const emit = defineEmits<{
	(event: "update:modelValue", value: string): void;
}>();

const weekdays = ["一", "二", "三", "四", "五", "六", "日"];

const currentMonth = computed(() => {
	const baseDate = props.modelValue ? new Date(`${props.modelValue}T00:00:00`) : new Date();
	return new Date(baseDate.getFullYear(), baseDate.getMonth(), 1);
});

const currentLabel = computed(() => {
	const year = currentMonth.value.getFullYear();
	const month = currentMonth.value.getMonth() + 1;
	return `${year}年${String(month).padStart(2, "0")}月`;
});

const days = computed<CalendarDay[]>(() => {
	const base = currentMonth.value;
	const year = base.getFullYear();
	const month = base.getMonth();
	const firstDay = new Date(year, month, 1);
	const startWeekday = (firstDay.getDay() + 6) % 7;
	const daysInMonth = new Date(year, month + 1, 0).getDate();
	const prevMonthDays = new Date(year, month, 0).getDate();
	const list: CalendarDay[] = [];

	for (let index = 0; index < 42; index += 1) {
		const dayOffset = index - startWeekday + 1;
		const current = new Date(year, month, dayOffset);
		const currentMonthFlag = current.getMonth() === month;
		const label = currentMonthFlag ? dayOffset : dayOffset <= 0 ? prevMonthDays + dayOffset : dayOffset - daysInMonth;
		const date = formatDate(current);
		list.push({
			key: `${date}-${index}`,
			label,
			date,
			currentMonth: currentMonthFlag,
			selected: date === props.modelValue,
		});
	}

	return list;
});

function formatDate(date: Date) {
	const year = date.getFullYear();
	const month = String(date.getMonth() + 1).padStart(2, "0");
	const day = String(date.getDate()).padStart(2, "0");
	return `${year}-${month}-${day}`;
}

function changeMonth(offset: number) {
	const base = currentMonth.value;
	const next = new Date(base.getFullYear(), base.getMonth() + offset, 1);
	const currentDay = props.modelValue ? new Date(`${props.modelValue}T00:00:00`).getDate() : 1;
	const lastDay = new Date(next.getFullYear(), next.getMonth() + 1, 0).getDate();
	const target = new Date(next.getFullYear(), next.getMonth(), Math.min(currentDay, lastDay));
	emit("update:modelValue", formatDate(target));
}

function selectDay(day: CalendarDay) {
	emit("update:modelValue", day.date);
}
</script>

<template>
	<view class="teacher-calendar">
		<view class="teacher-calendar__header">
			<view class="teacher-calendar__btn" @click="changeMonth(-1)">上个月</view>
			<text class="teacher-calendar__title">{{ currentLabel }}</text>
			<view class="teacher-calendar__btn" @click="changeMonth(1)">下个月</view>
		</view>
		<view class="teacher-calendar__weekdays">
			<text v-for="weekday in weekdays" :key="weekday" class="teacher-calendar__weekday">
				{{ weekday }}
			</text>
		</view>
		<view class="teacher-calendar__grid">
			<view
				v-for="day in days"
				:key="day.key"
				class="teacher-calendar__cell"
				:class="{
					'teacher-calendar__cell--muted': !day.currentMonth,
					'teacher-calendar__cell--selected': day.selected,
				}"
				@click="selectDay(day)"
			>
				{{ day.label }}
			</view>
		</view>
	</view>
</template>

<style scoped>
.teacher-calendar {
	border-radius: 18px;
	background: #fff;
	padding: 14px 14px 10px;
}

.teacher-calendar__header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	padding: 0 4px 10px;
}

.teacher-calendar__btn {
	min-width: 68px;
	border: 1px solid #d5def0;
	border-radius: 8px;
	padding: 4px 8px;
	text-align: center;
	font-size: 13px;
	color: #4c7cff;
}

.teacher-calendar__title {
	font-size: 18px;
	font-weight: 600;
	color: #25324b;
}

.teacher-calendar__weekdays,
.teacher-calendar__grid {
	display: grid;
	grid-template-columns: repeat(7, 1fr);
}

.teacher-calendar__weekdays {
	margin-bottom: 8px;
}

.teacher-calendar__weekday {
	padding: 8px 0;
	text-align: center;
	font-size: 14px;
	color: #1ac7c6;
}

.teacher-calendar__cell {
	display: flex;
	align-items: center;
	justify-content: center;
	height: 42px;
	margin: 2px;
	border-radius: 999px;
	font-size: 15px;
	color: #2e3a59;
}

.teacher-calendar__cell--muted {
	color: #cad2e1;
}

.teacher-calendar__cell--selected {
	background: #4c7cff;
	color: #fff;
	font-weight: 600;
}
</style>
