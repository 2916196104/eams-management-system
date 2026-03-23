<template>
	<div class="class-summary-container">
		<div class="class-summary-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学员姓名:</label>
						<el-input v-model="filters.name" placeholder="请输入学员姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">分校区:</label>
						<el-select v-model="filters.campusId" placeholder="请选择分校区" clearable class="filter-input">
							<el-option
								v-for="(item, index) in campusList"
								:key="item.id || index"
								:label="item.name || '未知校区'"
								:value="item.id || ''"
							/>
						</el-select>
					</div>
					<div class="filter-item">
						<label class="filter-label">课程:</label>
						<el-select v-model="filters.courseId" placeholder="请选择课程" clearable class="filter-input">
							<el-option
								v-for="(item, index) in courseList"
								:key="item.id || index"
								:label="item.name || '未知课程'"
								:value="item.id || ''"
							/>
						</el-select>
					</div>
					<div class="filter-buttons">
						<el-button :icon="Search" circle @click="handleSearch" />
						<el-button :icon="CircleClose" circle @click="handleReset" />
					</div>
				</div>
				<div class="action-buttons">
					<el-button :icon="RefreshRight" circle @click="handleRefresh" />
					<el-button :icon="Printer" circle @click="handlePrint" />
					<el-button :icon="Menu" circle @click="handleCustomSort" />
				</div>
			</div>
			<my-table
				:istabmultiple="true"
				:tabattr="tableAttr"
				:tabdatacolumns="tableColumns"
				:tabdata="displayPageData"
				@page-change="handlePageChange"
				@selection-change="handleSelectionChange"
			>
				<template #customercell="{ prop, row }">
					<template v-if="['totalHours', 'completedHours', 'sickLeave', 'personalLeave'].includes(prop)">
						<span :class="getCellClass(prop, row)">{{ row[prop] }}</span>
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
import { CircleClose, Menu, Printer, RefreshRight, Search } from "@element-plus/icons-vue";
import MyTable from "@/components/mytable/MyTable.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import { getClassSummaryPage, getCampusList, getCourseListForClassSummary } from "@/apis/student";
import type { ClassSummaryItemDTO, CampusItemDTO, CourseItemDTO } from "@/apis/student/type";

const filters = reactive({
	advisorId: "",
	name: "",
	phone: "",
	status: "",
	studentId: "",
	campusId: "",
	courseId: "",
});

const campusList = ref<CampusItemDTO[]>([]);
const courseList = ref<CourseItemDTO[]>([]);

const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};

const tableColumns: MyTableColumn[] = [
	{ prop: "courseName", label: "课程名称", "min-width": 150 },
	{ prop: "subjectName", label: "科目名称", "min-width": 120 },
	{ prop: "totalCount", label: "总数量", width: "100px", align: "center" },
	{ prop: "completeCount", label: "已完成数量", width: "120px", align: "center" },
	{ prop: "remainingCount", label: "剩余数量", width: "100px", align: "center" },
	{ prop: "remainingAmount", label: "剩余金额", width: "120px", align: "center" },
	{ prop: "unitPrice", label: "单价", width: "100px", align: "center" },
	{ prop: "expireDate", label: "过期日期", width: "150px", align: "center" },
];

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<ClassSummaryItemDTO>());
const selectedRows = ref<ClassSummaryItemDTO[]>([]);

const displayPageData = computed(() => {
	return pageData.value;
});

function getCellClass(prop: string, _row: ClassSummaryItemDTO) {
	if (prop === "totalCount") return "cell-total";
	if (prop === "completeCount") return "cell-completed";
	if (prop === "remainingCount") return "cell-remaining";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		advisorId: "",
		name: "",
		phone: "",
		status: "",
		studentId: "",
		campusId: "",
		courseId: "",
	});
	pageIndex.value = 1;
	loadData();
}

function handleRefresh() {
	loadData();
}

function handlePrint() {
	ElMessage.info("打印功能待接入");
}

function handleCustomSort() {
	ElMessage.info("自定义排序功能待接入");
}

function handlePageChange(data: PageDTO<ClassSummaryItemDTO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: ClassSummaryItemDTO[]) {
	selectedRows.value = rows;
}

// 加载数据
async function loadData() {
	try {
		const res = await getClassSummaryPage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			advisorId: filters.advisorId,
			name: filters.name,
			phone: filters.phone,
			status: filters.status,
			studentId: filters.studentId,
			campusId: filters.campusId,
			courseId: filters.courseId,
		});
		if (res.data) {
			pageData.value = res.data;
		}
	} catch (error) {
		console.error("加载数据失败:", error);
		ElMessage.error("加载数据失败");
	}
}

async function loadCampusList() {
	try {
		const res = await getCampusList();
		if (res.data) {
			campusList.value = res.data;
		}
	} catch (error) {
		console.error("加载分校区列表失败:", error);
		ElMessage.error("加载分校区列表失败");
	}
}

async function loadCourseList() {
	try {
		const res = await getCourseListForClassSummary();
		if (res.data) {
			courseList.value = res.data;
		}
	} catch (error) {
		console.error("加载课程列表失败:", error);
		ElMessage.error("加载课程列表失败");
	}
}

onMounted(() => {
	loadCampusList();
	loadCourseList();
	loadData();
});
</script>

<style scoped>
.class-summary-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.class-summary-content {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
	display: flex;
	flex-direction: column;
	gap: 16px;
	min-height: 0;
}

.top-bar {
	display: flex;
	justify-content: space-between;
	align-items: center;
	gap: 16px;
}

.filter-area {
	display: flex;
	align-items: center;
	gap: 16px;
	flex-wrap: wrap;
}

.filter-item {
	display: flex;
	align-items: center;
	gap: 10px;
}

.filter-label {
	min-width: 72px;
	color: #303133;
	text-align: right;
}

.filter-input {
	width: 200px;
}

.filter-buttons {
	display: flex;
	align-items: center;
	gap: 10px;
}

.action-buttons {
	display: flex;
	align-items: center;
	gap: 10px;
}

:deep(.cell-total) {
	color: #409eff;
	font-weight: bold;
}

:deep(.cell-completed) {
	color: #67c23a;
	font-weight: bold;
}

:deep(.cell-remaining) {
	color: #f56c6c;
	font-weight: bold;
}

@media (max-width: 1200px) {
	.top-bar {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-area {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-item {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-label {
		min-width: auto;
		text-align: left;
	}

	.filter-input {
		width: 100%;
	}

	.filter-buttons,
	.action-buttons {
		flex-wrap: wrap;
		justify-content: flex-start;
	}
}
</style>
