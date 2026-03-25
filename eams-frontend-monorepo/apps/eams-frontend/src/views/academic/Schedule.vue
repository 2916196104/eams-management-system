<template>
	<div class="schedule-container">
		<div class="schedule-content">
			<!-- 筛选区域 -->
			<div class="filter-area">
				<div class="filter-row">
					<div class="filter-item">
						<label class="filter-label">周期:</label>
						<el-select v-model="filters.cycle" placeholder="请选择" clearable class="filter-input">
							<el-option label="本周" :value="1" />
							<el-option label="上周" :value="2" />
							<el-option label="本周及以后" :value="3" />
						</el-select>
					</div>
					<div class="filter-item">
						<label class="filter-label">班级:</label>
						<el-input v-model="filters.className" placeholder="请输入班级名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">课程:</label>
						<el-input v-model="filters.courseName" placeholder="请输入课程名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">老师:</label>
						<el-input v-model="filters.teacherName" placeholder="请输入老师姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">学生:</label>
						<el-input v-model="filters.studentName" placeholder="请输入学生姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">开始日期:</label>
						<el-date-picker
							v-model="filters.startDate"
							type="date"
							placeholder="请选择"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
						/>
					</div>
					<div class="filter-item">
						<label class="filter-label">结束日期:</label>
						<el-date-picker
							v-model="filters.endDate"
							type="date"
							placeholder="请选择"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
						/>
					</div>
					<div class="filter-buttons">
						<el-button :icon="Search" circle @click="handleSearch" />
						<el-button :icon="CircleClose" circle @click="handleReset" />
					</div>
				</div>
				<div class="filter-actions">
					<el-button :icon="Refresh" circle @click="handleRefresh" />
					<el-button :icon="Printer" circle @click="handlePrint" />
					<el-button :icon="Download" circle @click="handleExport" />
					<el-button :icon="Menu" circle @click="handleCustomColumn" />
				</div>
			</div>

			<!-- 批量操作栏 -->
			<div class="batch-actions">
				<el-button type="primary" @click="handleScheduleCalendar">
					<el-icon><Calendar /></el-icon>
					课表日历
				</el-button>
				<el-button @click="handleRepeatSchedule">
					<el-icon><RefreshRight /></el-icon>
					+ 重复排课
				</el-button>
				<el-button @click="handleFreeSchedule">
					<el-icon><Edit /></el-icon>
					+ 自由排课
				</el-button>
				<el-button @click="handleBatchDelete">
					<el-icon><Delete /></el-icon>
					删除
				</el-button>
				<el-button @click="handleBatchModify">
					<el-icon><EditPen /></el-icon>
					批量修改
				</el-button>
				<el-button @click="handleStop">
					<el-icon><VideoPause /></el-icon>
					停课
				</el-button>
				<el-button @click="handleResume">
					<el-icon><VideoPlay /></el-icon>
					恢复
				</el-button>
				<el-button @click="handleReservationOpen">
					<el-icon><Open /></el-icon>
					预约开
				</el-button>
				<el-button @click="handleReservationClose">
					<el-icon><Close /></el-icon>
					预约关
				</el-button>
			</div>

			<!-- 表格区域 -->
			<my-table
				:istabmultiple="true"
				:tabattr="tableAttr"
				:tabdatacolumns="tableColumns"
				:tabdata="displayPageData"
				@page-change="handlePageChange"
				@selection-change="handleSelectionChange"
			>
				<template #customercell="{ prop, row }">
					<template v-if="['classTime', 'state'].includes(prop)">
						<span :class="getCellClass(prop, row)">{{ row[prop] }}</span>
					</template>
					<template v-else-if="prop === 'action'">
						<el-button link type="primary" size="small" @click="handleEdit(row)">编辑</el-button>
					</template>
					<template v-else>
						{{ row[prop] }}
					</template>
				</template>
			</my-table>
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref } from "vue";
import { ElMessage } from "element-plus";
import {
	Calendar,
	Close,
	CircleClose,
	Delete,
	Download,
	Edit,
	EditPen,
	Menu,
	Open,
	Printer,
	Refresh,
	RefreshRight,
	Search,
	VideoPause,
	VideoPlay,
} from "@element-plus/icons-vue";
import MyTable from "@/components/mytable/MyTable.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import { getCourseListPage } from "@/apis/academic";
import type { CourseListVO } from "@/apis/academic/type";

const filters = reactive({
	pageIndex: 1,
	pageSize: 30,
	cycle: undefined as number | undefined,
	className: "",
	courseName: "",
	teacherName: "",
	studentName: "",
	startDate: "",
	endDate: "",
});

const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};

const tableColumns: MyTableColumn[] = [
	{ prop: "lessonTimeText", label: "上课时间", "min-width": 160, "show-overflow-tooltip": true },
	{ prop: "courseName", label: "课程", "min-width": 120, "show-overflow-tooltip": true },
	{ prop: "className", label: "班级名称", "min-width": 120, "show-overflow-tooltip": true },
	{ prop: "teacherNames", label: "上课老师", "min-width": 100, "show-overflow-tooltip": true },
	{ prop: "courseType", label: "类型", width: "80px", align: "center" },
	{ prop: "assistantNames", label: "助教", "min-width": 100, "show-overflow-tooltip": true },
	{ prop: "classroomName", label: "教室", "min-width": 100, "show-overflow-tooltip": true },
	{ prop: "canReserve", label: "可预约", width: "80px", align: "center" },
	{ prop: "studentCount", label: "学生数", width: "80px", align: "center" },
	{ prop: "checkInCount", label: "签到数", width: "80px", align: "center" },
	{ prop: "attendanceRate", label: "到课率", width: "80px", align: "center" },
	{ prop: "decLessonCount", label: "消课基数", width: "80px", align: "center" },
	{ prop: "consumedCount", label: "已消课数", width: "80px", align: "center" },
	{ prop: "lessonStatus", label: "上课情况", "min-width": 100, "show-overflow-tooltip": true },
	{ prop: "lessonStatus", label: "状态", width: "80px", align: "center" },
	{ prop: "action", label: "操作", width: "80px", align: "center", fixed: "right" },
];

const pageIndex = ref(1);
const pageSize = ref(30);
const pageData = ref(createPageDTO<CourseListVO>());

const displayPageData = computed(() => {
	return pageData.value;
});

function getCellClass(prop: string, _row: CourseListVO) {
	if (prop === "lessonTimeText") return "cell-class-time";
	if (prop === "lessonStatus") return "cell-state";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		pageIndex: 1,
		pageSize: 30,
		cycle: undefined,
		className: "",
		courseName: "",
		teacherName: "",
		studentName: "",
		startDate: "",
		endDate: "",
	});
	pageIndex.value = 1;
	loadData();
}

function handleRefresh() {
	ElMessage.info("刷新功能待接入");
}

function handlePrint() {
	ElMessage.info("打印功能待接入");
}

function handleExport() {
	ElMessage.info("导出功能待接入");
}

function handleCustomColumn() {
	ElMessage.info("自定义列功能待接入");
}

function handleScheduleCalendar() {
	ElMessage.info("课表日历功能待接入");
}

function handleRepeatSchedule() {
	ElMessage.info("重复排课功能待接入");
}

function handleFreeSchedule() {
	ElMessage.info("自由排课功能待接入");
}

function handleBatchDelete() {
	ElMessage.info("批量删除功能待接入");
}

function handleBatchModify() {
	ElMessage.info("批量修改功能待接入");
}

function handleStop() {
	ElMessage.info("停课功能待接入");
}

function handleResume() {
	ElMessage.info("恢复功能待接入");
}

function handleReservationOpen() {
	ElMessage.info("预约开功能待接入");
}

function handleReservationClose() {
	ElMessage.info("预约关功能待接入");
}

function handleEdit(_row: CourseListVO) {
	ElMessage.info("编辑功能待接入");
}

function handlePageChange(data: PageDTO<CourseListVO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(_rows: CourseListVO[]) {
	// 处理选中行变化
}

async function loadData() {
	try {
		const res = await getCourseListPage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			cycle: filters.cycle,
			className: filters.className,
			courseName: filters.courseName,
			teacherName: filters.teacherName,
			studentName: filters.studentName,
		});
		if (res.data) {
			pageData.value = createPageDTO<CourseListVO>({
				pageIndex: res.data.pageIndex || pageIndex.value,
				pageSize: res.data.pageSize || pageSize.value,
				total: res.data.total || 0,
				rows: res.data.rows || [],
			});
		}
	} catch (error) {
		console.error("加载数据失败:", error);
		ElMessage.error("加载数据失败");
	}
}

onMounted(() => {
	loadData();
});
</script>

<style scoped>
.schedule-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.schedule-content {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
	display: flex;
	flex-direction: column;
	gap: 16px;
	min-height: 0;
}

.filter-area {
	display: flex;
	justify-content: space-between;
	align-items: flex-start;
	gap: 16px;
}

.filter-row {
	display: flex;
	flex-wrap: wrap;
	gap: 16px;
	flex: 1;
}

.filter-item {
	display: flex;
	align-items: center;
	gap: 8px;
}

.filter-label {
	min-width: 56px;
	color: #303133;
	text-align: right;
	font-size: 14px;
}

.filter-input {
	width: 120px;
}

.filter-buttons {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-left: 8px;
}

.filter-actions {
	display: flex;
	align-items: center;
	gap: 8px;
	flex-shrink: 0;
}

.batch-actions {
	display: flex;
	gap: 12px;
	flex-wrap: wrap;
	padding: 12px 0;
	border-bottom: 1px solid #ebeef5;
}

:deep(.cell-class-time) {
	color: #409eff;
	font-weight: 500;
}

:deep(.cell-state) {
	color: #67c23a;
	font-weight: 500;
}

@media (max-width: 1400px) {
	.filter-row {
		flex-direction: column;
	}

	.filter-item {
		width: 100%;
	}

	.filter-label {
		min-width: 80px;
	}

	.filter-input {
		flex: 1;
	}
}
</style>
