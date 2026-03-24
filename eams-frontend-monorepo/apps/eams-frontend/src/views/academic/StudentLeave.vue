<template>
	<div class="student-leave-container">
		<div class="student-leave-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学员姓名:</label>
						<el-input v-model="filters.studentName" placeholder="请输入学员姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">任课老师:</label>
						<el-input v-model="filters.teacherName" placeholder="请输入任课老师" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">开始日期:</label>
						<el-date-picker
							v-model="filters.startDate"
							type="date"
							placeholder="请选择开始日期"
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
							placeholder="请选择结束日期"
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
					<template v-if="['leaveTime', 'status'].includes(prop)">
						<span :class="getCellClass(prop, row)">{{ row[prop] }}</span>
					</template>
					<template v-else-if="prop === 'leavePhotos'">
						<el-image
							v-if="row[prop] && row[prop].length > 0"
							:src="row[prop][0]"
							:preview-src-list="row[prop]"
							:preview-teleported="true"
							style="width: 50px; height: 50px"
							fit="cover"
						/>
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
import { getStudentLeavePage } from "@/apis/academic";
import type { StudentLeaveItemDTO } from "@/apis/academic/type";

const filters = reactive({
	studentName: "",
	teacherName: "",
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
	{ prop: "studentName", label: "学员姓名", "min-width": 120 },
	{ prop: "phone", label: "电话", width: "130px" },
	{ prop: "leaveLessons", label: "请假课次", "min-width": 200, "show-overflow-tooltip": true },
	{ prop: "teacherName", label: "任课老师", "min-width": 100 },
	{ prop: "leaveReason", label: "请假原因", "min-width": 150, "show-overflow-tooltip": true },
	{ prop: "leaveTime", label: "请假时间", width: "160px", align: "center" },
	{ prop: "leavePhotos", label: "请假照片", width: "100px", align: "center" },
	{ prop: "status", label: "状态", width: "100px", align: "center" },
];

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<StudentLeaveItemDTO>());
const selectedRows = ref<StudentLeaveItemDTO[]>([]);

const displayPageData = computed(() => {
	return pageData.value;
});

function getCellClass(prop: string, _row: StudentLeaveItemDTO) {
	if (prop === "leaveTime") return "cell-leave-time";
	if (prop === "status") return "cell-status";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		studentName: "",
		teacherName: "",
		startDate: "",
		endDate: "",
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

function handlePageChange(data: PageDTO<StudentLeaveItemDTO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: StudentLeaveItemDTO[]) {
	selectedRows.value = rows;
}

async function loadData() {
	try {
		const res = await getStudentLeavePage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			studentName: filters.studentName,
			teacherName: filters.teacherName,
			startDate: filters.startDate,
			endDate: filters.endDate,
		});
		if (res.data) {
			pageData.value = res.data;
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
.student-leave-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.student-leave-content {
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

:deep(.cell-leave-time) {
	color: #e6a23c;
	font-weight: bold;
}

:deep(.cell-status) {
	color: #67c23a;
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
