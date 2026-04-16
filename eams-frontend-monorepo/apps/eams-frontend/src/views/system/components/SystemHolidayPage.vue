<template>
	<section class="holiday-page">
		<section class="panel-card holiday-list">
			<div class="holiday-list__header">
				<div class="holiday-list__title">节假日</div>
				<el-tag effect="plain">{{ selectedDates.length }} 天</el-tag>
			</div>

			<div v-if="selectedDates.length" class="holiday-list__items">
				<div v-for="item in selectedDates" :key="item.id || item.iso" class="holiday-list__item">
					<div>
						<div class="holiday-list__date">{{ item.label }}</div>
						<div class="holiday-list__week">{{ item.weekday }}</div>
					</div>
					<el-button link type="danger" :loading="savingDate === item.iso" @click="removeHoliday(item)">删除</el-button>
				</div>
			</div>
			<div v-else class="holiday-list__empty">点击右侧日期后，这里会自动加入节假日日期。</div>
		</section>

		<section class="panel-card holiday-calendar">
			<div class="holiday-calendar__toolbar">
				<div>
					<div class="holiday-calendar__title">节假日管理</div>
					<div class="holiday-calendar__hint">点击日期可将其加入左侧节假日列表并标蓝，再次点击可取消。</div>
				</div>
				<el-select v-model="selectedYear" class="holiday-calendar__year">
					<el-option v-for="year in yearOptions" :key="year" :label="`${year} 年`" :value="year" />
				</el-select>
			</div>

			<div class="holiday-calendar__grid">
				<section v-for="month in months" :key="month.month" class="holiday-month">
					<div class="holiday-month__title">{{ month.title }}</div>
					<div class="holiday-month__weekdays">
						<span v-for="day in weekdays" :key="day">{{ day }}</span>
					</div>
					<div class="holiday-month__days">
						<div
							v-for="day in month.days"
							:key="day.key"
							:class="[
								'holiday-day',
								{
									'holiday-day--empty': !day.date,
									'holiday-day--selected': day.date && isHoliday(day.iso),
									'holiday-day--loading': day.date && savingDate === day.iso,
								},
							]"
							@click="day.date && toggleHoliday(day.iso)"
						>
							{{ day.date || "" }}
						</div>
					</div>
				</section>
			</div>
		</section>
	</section>
</template>

<script setup lang="ts">
import { computed, onMounted, ref, watch } from "vue";
import { ElMessage } from "element-plus";
import { addHoliday, deleteHoliday, listHolidays } from "@/apis/system";
import type { HolidayDTO } from "@/apis/system/type";

interface HolidayListItem {
	id?: string;
	iso: string;
	label: string;
	weekday: string;
}

interface HolidayMonthDay {
	key: string;
	date?: number;
	iso: string;
}

const currentYear = new Date().getFullYear();
const selectedYear = ref(currentYear);
const holidayList = ref<HolidayDTO[]>([]);
const savingDate = ref("");

const weekdays = ["日", "一", "二", "三", "四", "五", "六"];
const yearOptions = Array.from({ length: 7 }, (_, index) => currentYear - 2 + index);

const holidayMap = computed(() => {
	const map = new Map<string, HolidayDTO>();
	for (const item of holidayList.value) {
		map.set(item.holidayTime, item);
	}
	return map;
});

const months = computed(() => Array.from({ length: 12 }, (_, index) => createMonthData(selectedYear.value, index + 1)));

const selectedDates = computed<HolidayListItem[]>(() =>
	holidayList.value
		.filter((item) => item.holidayTime.startsWith(`${selectedYear.value}-`))
		.sort((a, b) => a.holidayTime.localeCompare(b.holidayTime))
		.map((item) => {
			const date = new Date(`${item.holidayTime}T00:00:00`);
			return {
				id: item.id,
				iso: item.holidayTime,
				label: `${date.getMonth() + 1} 月 ${date.getDate()} 日`,
				weekday: `星期${weekdays[date.getDay()]}`,
			};
		}),
);

function createMonthData(year: number, month: number) {
	const firstDay = new Date(year, month - 1, 1);
	const lastDate = new Date(year, month, 0).getDate();
	const leadingDays = firstDay.getDay();
	const days: HolidayMonthDay[] = [];

	for (let index = 0; index < leadingDays; index += 1) {
		days.push({ key: `empty-${month}-${index}`, iso: "" });
	}

	for (let date = 1; date <= lastDate; date += 1) {
		const iso = `${year}-${String(month).padStart(2, "0")}-${String(date).padStart(2, "0")}`;
		days.push({ key: iso, date, iso });
	}

	return {
		month,
		title: `${month} 月`,
		days,
	};
}

function isHoliday(iso: string) {
	return holidayMap.value.has(iso);
}

async function loadHolidays() {
	const res = await listHolidays({
		pageIndex: 1,
		pageSize: 366,
		year: selectedYear.value,
	});
	holidayList.value = res.rows || [];
}

async function toggleHoliday(iso: string) {
	if (savingDate.value) return;
	savingDate.value = iso;

	try {
		const current = holidayMap.value.get(iso);
		if (current) {
			await deleteHoliday(current.holidayTime);
			ElMessage.success("节日已删除");
		} else {
			await addHoliday(iso);
			ElMessage.success("节日已添加");
		}
		await loadHolidays();
	} catch (error) {
		const message = error instanceof Error ? error.message : "节假日操作失败";
		ElMessage.error(message);
	} finally {
		savingDate.value = "";
	}
}

async function removeHoliday(item: HolidayListItem) {
	if (savingDate.value) return;
	savingDate.value = item.iso;

	try {
		await deleteHoliday(item.iso);
		ElMessage.success("节日已删除");
		await loadHolidays();
	} catch (error) {
		const message = error instanceof Error ? error.message : "节假日删除失败";
		ElMessage.error(message);
	} finally {
		savingDate.value = "";
	}
}

watch(selectedYear, () => {
	loadHolidays();
});

onMounted(() => {
	loadHolidays();
});
</script>

<style scoped>
.holiday-page {
	display: grid;
	grid-template-columns: 320px minmax(0, 1fr);
	gap: 16px;
	padding: 16px;
}

.panel-card {
	background: #fff;
	border: 1px solid #edf0f5;
	box-shadow: 0 1px 2px rgb(31 45 61 / 4%);
}

.holiday-list {
	padding: 20px;
}

.holiday-list__header {
	display: flex;
	align-items: center;
	justify-content: space-between;
	margin-bottom: 18px;
}

.holiday-list__title,
.holiday-calendar__title {
	font-size: 20px;
	font-weight: 700;
	color: #293852;
}

.holiday-list__items {
	display: grid;
	gap: 12px;
}

.holiday-list__item {
	padding: 14px 16px;
	border-radius: 14px;
	background: #f8fbff;
	border: 1px solid #e3edf9;
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.holiday-list__date {
	font-weight: 600;
	color: #30415d;
}

.holiday-list__week {
	margin-top: 4px;
	font-size: 13px;
	color: #7b879c;
}

.holiday-list__empty {
	min-height: 180px;
	border: 1px dashed #d9e2f2;
	border-radius: 16px;
	display: flex;
	align-items: center;
	justify-content: center;
	text-align: center;
	color: #7b879c;
	background: #fafcff;
}

.holiday-calendar {
	padding: 20px;
}

.holiday-calendar__toolbar {
	margin-bottom: 20px;
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	gap: 16px;
}

.holiday-calendar__hint {
	margin-top: 6px;
	color: #7b879c;
}

.holiday-calendar__year {
	width: 140px;
}

.holiday-calendar__grid {
	display: grid;
	grid-template-columns: repeat(3, minmax(0, 1fr));
	gap: 16px;
}

.holiday-month {
	padding: 16px;
	border-radius: 18px;
	background: #fbfcff;
	border: 1px solid #ecf1f8;
}

.holiday-month__title {
	margin-bottom: 12px;
	font-size: 16px;
	font-weight: 700;
	color: #33415c;
}

.holiday-month__weekdays,
.holiday-month__days {
	display: grid;
	grid-template-columns: repeat(7, minmax(0, 1fr));
	gap: 6px;
}

.holiday-month__weekdays {
	margin-bottom: 8px;
	color: #8b97aa;
	font-size: 12px;
	text-align: center;
}

.holiday-day {
	height: 36px;
	border-radius: 10px;
	display: flex;
	align-items: center;
	justify-content: center;
	font-size: 14px;
	color: #33415c;
	cursor: pointer;
	background: #fff;
	border: 1px solid transparent;
	transition:
		background 0.2s ease,
		color 0.2s ease,
		box-shadow 0.2s ease;
}

.holiday-day--empty {
	cursor: default;
	background: transparent;
}

.holiday-day--selected {
	background: #4a89f3;
	color: #fff;
	box-shadow: 0 8px 16px rgb(74 137 243 / 22%);
}

.holiday-day--loading {
	opacity: 0.72;
	pointer-events: none;
}

@media (max-width: 1360px) {
	.holiday-page {
		grid-template-columns: 1fr;
	}

	.holiday-calendar__grid {
		grid-template-columns: repeat(2, minmax(0, 1fr));
	}
}

@media (max-width: 900px) {
	.holiday-calendar__grid {
		grid-template-columns: 1fr;
	}
}
</style>
