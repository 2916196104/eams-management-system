<template>
	<div class="appointment-page">
		<!-- 视图切换按钮 -->
		<el-card class="view-card">
			<el-radio-group v-model="viewMode">
				<el-radio-button value="list">列表视图</el-radio-button>
				<el-radio-button value="calendar">日历视图</el-radio-button>
			</el-radio-group>
		</el-card>

		<!-- ==================== 列表视图 ==================== -->
		<div v-if="viewMode === 'list'">
			<!-- 搜索表单 -->
			<el-card class="search-card">
				<el-form :inline="true" :model="searchForm">
					<el-form-item label="预约人">
						<el-input v-model="searchForm.studentName" placeholder="请输入预约人姓名" clearable style="width: 150px" />
					</el-form-item>
					<el-form-item label="预约课程">
						<el-input v-model="searchForm.courseName" placeholder="请输入课程名称" clearable style="width: 150px" />
					</el-form-item>
					<el-form-item label="预约日期">
						<el-date-picker
							v-model="searchForm.dateRange"
							type="daterange"
							range-separator="至"
							start-placeholder="开始日期"
							end-placeholder="结束日期"
							value-format="YYYY-MM-DD"
							style="width: 260px"
						/>
					</el-form-item>
					<el-form-item label="状态">
						<el-select v-model="searchForm.verifyState" placeholder="请选择状态" clearable style="width: 120px">
							<el-option label="待审核" value="0" />
							<el-option label="已确认" value="1" />
							<el-option label="已取消" value="2" />
						</el-select>
					</el-form-item>
					<el-form-item>
						<el-button type="primary" @click="handleSearch">查询</el-button>
						<el-button @click="handleReset">重置</el-button>
					</el-form-item>
				</el-form>
			</el-card>

			<!-- 操作按钮 -->
			<el-card class="action-card">
				<el-button type="success" :disabled="selectedIds.length === 0" @click="handleBatchApprove">批量确认</el-button>
				<el-button type="danger" :disabled="selectedIds.length === 0" @click="handleBatchCancel">批量取消</el-button>
				<el-button type="warning" :disabled="selectedIds.length === 0" @click="handleBatchReschedule">
					批量调课
				</el-button>
			</el-card>

			<!-- 表格 -->
			<el-card>
				<!-- 表格工具栏 -->
				<div class="table-toolbar">
					<div class="toolbar-left">
						<span class="total-info">共 {{ pagination.total }} 条记录</span>
					</div>
					<div class="toolbar-right">
						<el-button @click="handleRefresh">
							<el-icon><Refresh /></el-icon>
							刷新
						</el-button>
						<el-button @click="handlePrint">
							<el-icon><Printer /></el-icon>
							打印
						</el-button>
						<el-dropdown @command="handleColumnCommand">
							<el-button>
								<el-icon><Setting /></el-icon>
								自定义列
								<el-icon><ArrowDown /></el-icon>
							</el-button>
							<template #dropdown>
								<el-dropdown-menu>
									<el-dropdown-item v-for="col in allColumns" :key="col.key" :command="col.key">
										<el-checkbox
											:model-value="visibleColumns.includes(col.key)"
											@change="toggleColumn(col.key)"
											@click.stop
										>
											{{ col.label }}
										</el-checkbox>
									</el-dropdown-item>
								</el-dropdown-menu>
							</template>
						</el-dropdown>
					</div>
				</div>

				<el-table :data="tableData" v-loading="loading" border stripe @selection-change="handleSelectionChange">
					<el-table-column type="selection" width="55" />
					<el-table-column
						v-if="visibleColumns.includes('studentName')"
						prop="studentName"
						label="预约人"
						min-width="120"
					/>
					<el-table-column
						v-if="visibleColumns.includes('studentMobile')"
						prop="studentMobile"
						label="手机号"
						width="130"
					/>
					<el-table-column
						v-if="visibleColumns.includes('lessonTitle')"
						prop="lessonTitle"
						label="预约课程"
						min-width="150"
					/>
					<el-table-column
						v-if="visibleColumns.includes('lessonTime')"
						prop="lessonTime"
						label="上课时间"
						width="160"
					/>
					<el-table-column v-if="visibleColumns.includes('addTime')" prop="addTime" label="预约时间" width="160" />
					<el-table-column v-if="visibleColumns.includes('verifyState')" label="状态" width="100">
						<template #default="{ row }">
							<el-tag :type="getStateType(row.verifyState)">
								{{ getStateText(row.verifyState) }}
							</el-tag>
						</template>
					</el-table-column>
					<el-table-column v-if="visibleColumns.includes('action')" label="操作" width="180" fixed="right">
						<template #default="{ row }">
							<el-button link type="primary" @click="handleReschedule(row)">调课</el-button>
							<template v-if="row.verifyState === '0'">
								<el-button link type="success" @click="handleApprove(row)">确认</el-button>
								<el-button link type="danger" @click="handleCancel(row)">取消</el-button>
							</template>
							<el-button v-else link type="info" disabled>已处理</el-button>
						</template>
					</el-table-column>
				</el-table>

				<!-- 分页 -->
				<div class="pagination-wrapper">
					<el-pagination
						v-model:current-page="pagination.pageIndex"
						v-model:page-size="pagination.pageSize"
						:total="pagination.total"
						:page-sizes="[10, 20, 50, 100]"
						layout="total, sizes, prev, pager, next, jumper"
						@size-change="handleSizeChange"
						@current-change="handleCurrentChange"
					/>
				</div>
			</el-card>
		</div>

		<!-- ==================== 日历视图 ==================== -->
		<div v-else>
			<el-card>
				<!-- 日历头部：日期导航 + 视图切换 -->
				<div class="calendar-header">
					<div class="calendar-nav">
						<el-button @click="prevPeriod">
							上一{{ calendarView === "month" ? "月" : calendarView === "week" ? "周" : "天" }}
						</el-button>
						<span class="current-date">{{ currentDateText }}</span>
						<el-button @click="nextPeriod">
							下一{{ calendarView === "month" ? "月" : calendarView === "week" ? "周" : "天" }}
						</el-button>
						<el-button type="primary" @click="goToday">今天</el-button>
					</div>
					<div class="calendar-view-type">
						<el-radio-group v-model="calendarView" @change="handleCalendarViewChange">
							<el-radio-button value="month">月视图</el-radio-button>
							<el-radio-button value="week">周视图</el-radio-button>
							<el-radio-button value="day">日视图</el-radio-button>
						</el-radio-group>
					</div>
				</div>

				<!-- 月视图 -->
				<div v-if="calendarView === 'month'" class="month-view">
					<el-calendar v-model="calendarDate">
						<template #date-cell="{ data }">
							<div class="calendar-cell" @click="handleDateClick(data)">
								<span class="day">{{ data.day.split("-")[2] }}</span>
								<div class="appointments">
									<div
										v-for="item in getAppointmentsByDate(data.day)"
										:key="item.id"
										class="appointment-item"
										:class="getStateClass(item.verifyState)"
										@click.stop="showAppointmentDetail(item)"
									>
										<el-tooltip :content="`${item.studentName} - ${item.lessonTitle}`" placement="top">
											<span>{{ item.studentName }}</span>
										</el-tooltip>
									</div>
								</div>
							</div>
						</template>
					</el-calendar>
				</div>

				<!-- 周视图 -->
				<div v-else-if="calendarView === 'week'" class="week-view">
					<div class="week-header">
						<div v-for="day in weekDays" :key="day.date" class="week-day-header">
							<div class="weekday">{{ day.weekday }}</div>
							<div class="date">{{ day.date }}</div>
						</div>
					</div>
					<div class="week-body">
						<div class="time-column">
							<div v-for="hour in 24" :key="hour" class="time-slot">{{ hour }}:00</div>
						</div>
						<div v-for="day in weekDays" :key="day.date" class="day-column">
							<div v-for="hour in 24" :key="hour" class="hour-slot" @click="handleTimeSlotClick(day.date, hour)">
								<div
									v-for="item in getAppointmentsByDateTime(day.date, hour)"
									:key="item.id"
									class="appointment-block"
									:class="getStateClass(item.verifyState)"
									@click.stop="showAppointmentDetail(item)"
								>
									{{ item.studentName }}
								</div>
							</div>
						</div>
					</div>
				</div>

				<!-- 日视图 -->
				<div v-else-if="calendarView === 'day'" class="day-view">
					<div class="day-header">
						<div class="day-date">{{ dayDateText }}</div>
					</div>
					<div class="day-body">
						<div class="time-column">
							<div v-for="hour in 24" :key="hour" class="time-slot">{{ hour }}:00</div>
						</div>
						<div class="day-content">
							<div v-for="hour in 24" :key="hour" class="hour-slot" @click="handleTimeSlotClick(selectedDate, hour)">
								<div
									v-for="item in getAppointmentsByDateTime(selectedDate, hour)"
									:key="item.id"
									class="appointment-block"
									:class="getStateClass(item.verifyState)"
									@click.stop="showAppointmentDetail(item)"
								>
									{{ item.studentName }} - {{ item.lessonTitle }}
								</div>
							</div>
						</div>
					</div>
				</div>

				<!-- 缩减版预约列表（当天预约） -->
				<el-card class="daily-list-card" v-if="selectedDateAppointments.length > 0">
					<template #header>
						<span>{{ selectedDateText }} 的预约</span>
						<el-button type="primary" size="small" @click="goToListView">查看更多</el-button>
					</template>
					<el-table :data="selectedDateAppointments" border stripe size="small">
						<el-table-column prop="studentName" label="预约人" width="120" />
						<el-table-column prop="lessonTitle" label="预约课程" min-width="150" />
						<el-table-column prop="lessonTime" label="上课时间" width="160" />
						<el-table-column label="状态" width="100">
							<template #default="{ row }">
								<el-tag :type="getStateType(row.verifyState)" size="small">
									{{ getStateText(row.verifyState) }}
								</el-tag>
							</template>
						</el-table-column>
						<el-table-column label="操作" width="120">
							<template #default="{ row }">
								<el-button link type="primary" size="small" @click="handleReschedule(row)">调课</el-button>
								<template v-if="row.verifyState === '0'">
									<el-button link type="success" size="small" @click="handleApprove(row)">确认</el-button>
									<el-button link type="danger" size="small" @click="handleCancel(row)">取消</el-button>
								</template>
							</template>
						</el-table-column>
					</el-table>
				</el-card>
			</el-card>
		</div>

		<!-- 调课弹窗 -->
		<el-dialog v-model="rescheduleVisible" title="调课" width="500px">
			<el-form :model="rescheduleForm" label-width="80px">
				<el-form-item label="学生姓名">
					<span>{{ rescheduleForm.studentName }}</span>
				</el-form-item>
				<el-form-item label="原上课时间">
					<span>{{ rescheduleForm.oldTime }}</span>
				</el-form-item>
				<el-form-item label="新上课时间" required>
					<el-date-picker
						v-model="rescheduleForm.newTime"
						type="datetime"
						placeholder="选择新的上课时间"
						value-format="YYYY-MM-DD HH:mm:ss"
						style="width: 100%"
					/>
				</el-form-item>
				<el-form-item label="调课原因">
					<el-input v-model="rescheduleForm.reason" type="textarea" :rows="2" placeholder="请输入调课原因" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="rescheduleVisible = false">取消</el-button>
				<el-button type="primary" :loading="rescheduleLoading" @click="confirmReschedule">确定调课</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, computed, onMounted } from "vue";
import { useRouter } from "vue-router";
import { ElMessage, ElMessageBox } from "element-plus";
import { Refresh, Printer, Setting, ArrowDown } from "@element-plus/icons-vue";
import dayjs from "dayjs";
import {
	getAppointmentList,
	getAppointmentCalendar,
	approveAppointment,
	cancelAppointment,
	getAppointmentDetail,
	type AppointmentItem,
	type AppointmentListParams,
	type CalendarParams,
	type AppointmentCalendarVo,
} from "@/apis/academic/appointment";

const router = useRouter();

// 视图模式
const viewMode = ref<"list" | "calendar">("list");
const calendarView = ref<"month" | "week" | "day">("month");
const calendarDate = ref(new Date());
const selectedDate = ref(dayjs().format("YYYY-MM-DD"));

// 列定义
const allColumns = [
	{ key: "studentName", label: "预约人" },
	{ key: "studentMobile", label: "手机号" },
	{ key: "lessonTitle", label: "预约课程" },
	{ key: "lessonTime", label: "上课时间" },
	{ key: "addTime", label: "预约时间" },
	{ key: "verifyState", label: "状态" },
	{ key: "action", label: "操作" },
];
const visibleColumns = ref<string[]>(allColumns.map((col) => col.key));

// 列配置
const loadColumnConfig = () => {
	const saved = localStorage.getItem("appointment-columns");
	if (saved) visibleColumns.value = JSON.parse(saved);
};
const saveColumnConfig = () => localStorage.setItem("appointment-columns", JSON.stringify(visibleColumns.value));
const toggleColumn = (key: string) => {
	const index = visibleColumns.value.indexOf(key);
	if (index === -1) visibleColumns.value.push(key);
	else visibleColumns.value.splice(index, 1);
	saveColumnConfig();
};
const handleColumnCommand = (command: string) => toggleColumn(command);
const handleRefresh = () => {
	if (viewMode.value === "list") loadListData();
	else loadCalendarData();
};
const handlePrint = () => window.print();

// 搜索表单
const searchForm = reactive({ studentName: "", courseName: "", dateRange: [] as string[], verifyState: "" });

// 分页
const pagination = reactive({ pageIndex: 1, pageSize: 20, total: 0 });

// 表格数据
const tableData = ref<AppointmentItem[]>([]);
const loading = ref(false);
const selectedIds = ref<number[]>([]);

// 日历数据
const calendarData = ref<AppointmentCalendarVo[]>([]);

// 调课弹窗
const rescheduleVisible = ref(false);
const rescheduleLoading = ref(false);
const rescheduleForm = reactive({ id: 0, studentName: "", oldTime: "", newTime: "", reason: "" });

// 计算属性
const currentDateText = computed(() => {
	if (calendarView.value === "month") return dayjs(calendarDate.value).format("YYYY年MM月");
	if (calendarView.value === "week") {
		const start = dayjs(calendarDate.value).startOf("week");
		const end = dayjs(calendarDate.value).endOf("week");
		return `${start.format("MM月DD日")} - ${end.format("MM月DD日")}`;
	}
	return dayjs(calendarDate.value).format("YYYY年MM月DD日");
});

const dayDateText = computed(() => dayjs(selectedDate.value).format("YYYY年MM月DD日 dddd"));
const selectedDateText = computed(() => dayjs(selectedDate.value).format("YYYY年MM月DD日"));
const weekDays = computed(() => {
	const start = dayjs(calendarDate.value).startOf("week");
	return Array.from({ length: 7 }, (_, i) => ({
		date: start.add(i, "day").format("YYYY-MM-DD"),
		weekday: start.add(i, "day").format("dddd"),
	}));
});

const selectedDateAppointments = computed(() => {
	return calendarData.value.filter((item) => item.lessonTime?.startsWith(selectedDate.value));
});

// 状态映射
const getStateType = (state: string): "warning" | "success" | "info" | "primary" | "danger" => {
	const map: Record<string, any> = { "0": "warning", "1": "success", "2": "info" };
	return map[state] || "info";
};
const getStateText = (state: string) => ({ "0": "待审核", "1": "已确认", "2": "已取消" })[state] || "未知";
const getStateClass = (state: string) => ({ "0": "pending", "1": "confirmed", "2": "cancelled" })[state] || "";

// 列表视图方法
const loadListData = async () => {
  loading.value = true;
  try {
    const params: AppointmentListParams = {
      pageIndex: pagination.pageIndex,
      pageSize: pagination.pageSize,
      studentNames: searchForm.studentName ? [searchForm.studentName] : undefined,
      courseNames: searchForm.courseName ? [searchForm.courseName] : undefined,
      startDate: searchForm.dateRange[0],
      endDate: searchForm.dateRange[1],
      verifyState: searchForm.verifyState || undefined,
    };
    const res = await getAppointmentList(params);
    if (res.code === 10000) {
      tableData.value = res.data?.rows || [];
      pagination.total = res.data?.total || 0;
    } else {
      ElMessage.error(res.message || "请求失败");
    }
  } catch (error) {
    ElMessage.error("加载数据失败");
  } finally {
    loading.value = false;
  }
};

const handleSearch = () => {
	pagination.pageIndex = 1;
	loadListData();
};
const handleReset = () => {
	Object.assign(searchForm, { studentName: "", courseName: "", dateRange: [], verifyState: "" });
	handleSearch();
};
const handleSelectionChange = (rows: AppointmentItem[]) => {
	selectedIds.value = rows.map((row) => row.id);
};
const handleSizeChange = (size: number) => {
	pagination.pageSize = size;
	loadListData();
};
const handleCurrentChange = (page: number) => {
	pagination.pageIndex = page;
	loadListData();
};

const handleApprove = async (row: AppointmentItem) => {
	await ElMessageBox.confirm(`确定确认 ${row.studentName} 的预约吗？`, "提示", { type: "info" });
	const res = await approveAppointment([row.id]);
	if (res.data?.code === 10000) {
		ElMessage.success("确认成功");
		loadListData();
	} else ElMessage.error(res.data?.message || "确认失败");
};

const handleCancel = async (row: AppointmentItem) => {
	await ElMessageBox.confirm(`确定取消 ${row.studentName} 的预约吗？`, "提示", { type: "warning" });
	const res = await cancelAppointment([row.id]);
	if (res.data?.code === 10000) {
		ElMessage.success("取消成功");
		loadListData();
	} else ElMessage.error(res.data?.message || "取消失败");
};

const handleBatchApprove = async () => {
	await ElMessageBox.confirm(`确定确认选中的 ${selectedIds.value.length} 个预约吗？`, "提示", { type: "info" });
	const res = await approveAppointment(selectedIds.value);
	if (res.data?.code === 10000) {
		ElMessage.success("确认成功");
		selectedIds.value = [];
		loadListData();
	} else ElMessage.error(res.data?.message || "确认失败");
};

const handleBatchCancel = async () => {
	await ElMessageBox.confirm(`确定取消选中的 ${selectedIds.value.length} 个预约吗？`, "提示", { type: "warning" });
	const res = await cancelAppointment(selectedIds.value);
	if (res.data?.code === 10000) {
		ElMessage.success("取消成功");
		selectedIds.value = [];
		loadListData();
	} else ElMessage.error(res.data?.message || "取消失败");
};

const handleBatchReschedule = () => {
	ElMessage.info("批量调课功能开发中");
};

// 调课方法
const handleReschedule = (row: AppointmentItem) => {
	Object.assign(rescheduleForm, {
		id: row.id,
		studentName: row.studentName,
		oldTime: row.lessonTime,
		newTime: "",
		reason: "",
	});
	rescheduleVisible.value = true;
};

const confirmReschedule = async () => {
	if (!rescheduleForm.newTime) {
		ElMessage.warning("请选择新的上课时间");
		return;
	}
	rescheduleLoading.value = true;
	try {
		// TODO: 调用调课接口
		setTimeout(() => {
			ElMessage.success("调课成功");
			rescheduleVisible.value = false;
			loadListData();
			rescheduleLoading.value = false;
		}, 500);
	} catch {
		ElMessage.error("调课失败");
	} finally {
		rescheduleLoading.value = false;
	}
};

// 日历视图方法
const loadCalendarData = async () => {
  const startDate = dayjs(calendarDate.value).startOf("month").format("YYYY-MM-DD");
  const endDate = dayjs(calendarDate.value).endOf("month").format("YYYY-MM-DD");
  try {
    const res = await getAppointmentCalendar({ startDate, endDate });
    if (res.code === 10000) {
      calendarData.value = res.data || [];
    }
  } catch {
    console.error("加载日历数据失败");
  }
};

const getAppointmentsByDate = (date: string) => calendarData.value.filter((item) => item.lessonTime?.startsWith(date));
const getAppointmentsByDateTime = (date: string, hour: number) =>
	calendarData.value.filter(
		(item) =>
			item.lessonTime?.startsWith(date) && parseInt(item.lessonTime?.split(" ")[1]?.split(":")[0] || "0") === hour,
	);

const showAppointmentDetail = async (item: AppointmentCalendarVo) => {
	const res = await getAppointmentDetail(item.id);
	if (res.data?.code === 10000 && res.data?.data) {
		await ElMessageBox.confirm(
			`学生：${res.data.data.studentName}\n课程：${res.data.data.lessonTitle}\n时间：${res.data.data.lessonTime}\n状态：${getStateText(res.data.data.verifyState)}`,
			"预约详情",
			{ confirmButtonText: "关闭", showCancelButton: false },
		);
	}
};

const handleDateClick = (data: any) => {
	selectedDate.value = data.day;
};
const handleTimeSlotClick = (date: string, hour: number) => {
	console.log("点击时间格子:", date, hour);
};
const handleCalendarViewChange = () => {
	loadCalendarData();
};
const prevPeriod = () => {
	if (calendarView.value === "month") calendarDate.value = dayjs(calendarDate.value).subtract(1, "month").toDate();
	else if (calendarView.value === "week") calendarDate.value = dayjs(calendarDate.value).subtract(1, "week").toDate();
	else calendarDate.value = dayjs(calendarDate.value).subtract(1, "day").toDate();
	loadCalendarData();
};
const nextPeriod = () => {
	if (calendarView.value === "month") calendarDate.value = dayjs(calendarDate.value).add(1, "month").toDate();
	else if (calendarView.value === "week") calendarDate.value = dayjs(calendarDate.value).add(1, "week").toDate();
	else calendarDate.value = dayjs(calendarDate.value).add(1, "day").toDate();
	loadCalendarData();
};
const goToday = () => {
	calendarDate.value = new Date();
	selectedDate.value = dayjs().format("YYYY-MM-DD");
	loadCalendarData();
};
const goToListView = () => {
	viewMode.value = "list";
};

onMounted(() => {
	loadColumnConfig();
	loadListData();
	loadCalendarData();
});
</script>

<style scoped lang="scss">
.appointment-page {
	padding: 20px;

	.view-card,
	.search-card,
	.action-card {
		margin-bottom: 20px;
	}

	.table-toolbar {
		display: flex;
		justify-content: space-between;
		align-items: center;
		margin-bottom: 16px;
		padding-bottom: 12px;
		border-bottom: 1px solid #ebeef5;
		.toolbar-right {
			display: flex;
			gap: 8px;
		}
	}

	.pagination-wrapper {
		margin-top: 20px;
		display: flex;
		justify-content: flex-end;
	}

	.calendar-header {
		display: flex;
		justify-content: space-between;
		align-items: center;
		margin-bottom: 20px;
		flex-wrap: wrap;
		gap: 10px;
		.calendar-nav {
			display: flex;
			align-items: center;
			gap: 12px;
		}
		.current-date {
			font-size: 18px;
			font-weight: bold;
			min-width: 200px;
			text-align: center;
		}
	}

	.month-view .calendar-cell {
		min-height: 80px;
		padding: 4px;
		cursor: pointer;
		.day {
			font-size: 12px;
			color: #666;
		}
		.appointments {
			margin-top: 4px;
			.appointment-item {
				font-size: 10px;
				padding: 2px 4px;
				margin-bottom: 2px;
				border-radius: 2px;
				overflow: hidden;
				text-overflow: ellipsis;
				white-space: nowrap;
				cursor: pointer;
				&.pending {
					background-color: #fff3e0;
					color: #e6a23c;
				}
				&.confirmed {
					background-color: #f0f9eb;
					color: #67c23a;
				}
				&.cancelled {
					background-color: #fef0f0;
					color: #f56c6c;
					text-decoration: line-through;
				}
				&:hover {
					opacity: 0.8;
				}
			}
		}
	}

	.week-view {
		overflow-x: auto;
		.week-header {
			display: flex;
			border-bottom: 1px solid #ebeef5;
		}
		.week-day-header {
			flex: 1;
			text-align: center;
			padding: 12px 0;
			border-right: 1px solid #ebeef5;
		}
		.week-body {
			display: flex;
		}
		.time-column {
			width: 60px;
			flex-shrink: 0;
			.time-slot {
				height: 60px;
				border-bottom: 1px solid #ebeef5;
				text-align: center;
				font-size: 12px;
				line-height: 60px;
			}
		}
		.day-column {
			flex: 1;
			border-right: 1px solid #ebeef5;
			.hour-slot {
				height: 60px;
				border-bottom: 1px solid #ebeef5;
				position: relative;
				cursor: pointer;
				&:hover {
					background-color: #f5f7fa;
				}
			}
		}
		.appointment-block {
			position: absolute;
			left: 2px;
			right: 2px;
			background-color: #f0f9eb;
			color: #67c23a;
			font-size: 10px;
			padding: 2px 4px;
			border-radius: 2px;
			overflow: hidden;
			text-overflow: ellipsis;
			white-space: nowrap;
			cursor: pointer;
		}
	}

	.day-view {
		.day-header {
			text-align: center;
			padding: 12px;
			border-bottom: 1px solid #ebeef5;
			.day-date {
				font-size: 16px;
				font-weight: bold;
			}
		}
		.day-body {
			display: flex;
		}
		.time-column {
			width: 60px;
			flex-shrink: 0;
			.time-slot {
				height: 60px;
				border-bottom: 1px solid #ebeef5;
				text-align: center;
				font-size: 12px;
				line-height: 60px;
			}
		}
		.day-content {
			flex: 1;
			.hour-slot {
				height: 60px;
				border-bottom: 1px solid #ebeef5;
				position: relative;
				cursor: pointer;
				&:hover {
					background-color: #f5f7fa;
				}
			}
		}
		.appointment-block {
			position: absolute;
			left: 2px;
			right: 2px;
			background-color: #f0f9eb;
			color: #67c23a;
			font-size: 10px;
			padding: 2px 4px;
			border-radius: 2px;
			overflow: hidden;
			text-overflow: ellipsis;
			white-space: nowrap;
			cursor: pointer;
		}
	}

	.daily-list-card {
		margin-top: 20px;
		:deep(.el-card__header) {
			display: flex;
			justify-content: space-between;
			align-items: center;
		}
	}
}

@media print {
	.search-card,
	.action-card,
	.table-toolbar,
	.pagination-wrapper,
	.calendar-header,
	.daily-list-card {
		display: none;
	}
}
</style>
