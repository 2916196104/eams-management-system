<template>
	<div class="student-leave-container">
		<div class="student-leave-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学生姓名/电话:</label>
						<el-input v-model="filters.nameOrPhone" placeholder="请输入学生姓名或电话" clearable class="filter-input" />
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
			<div class="batch-actions">
				<el-button @click="handleRevoke">
					<el-icon><RefreshRight /></el-icon>
					请假撤销
				</el-button>
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
					<template v-if="['addTime', 'state'].includes(prop)">
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
import { ElMessage, ElMessageBox } from "element-plus";
import { CircleClose, Menu, Printer, RefreshRight, Search } from "@element-plus/icons-vue";
import MyTable from "@/components/mytable/MyTable.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import { getStudentLeavePage, cancelStudentLeave } from "@/apis/academic";
import type { StudentLeaveItemDTO } from "@/apis/academic/type";

const filters = reactive({
	pageIndex: 1,
	pageSize: 20,
	nameOrPhone: "",
	teacherId: undefined as number | undefined,
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
	{ prop: "mobile", label: "电话", width: "130px", align: "center" },
	{ prop: "courseInfo", label: "请假课次", "min-width": 200, "show-overflow-tooltip": true },
	{ prop: "teacherNames", label: "任课老师", "min-width": 150, "show-overflow-tooltip": true },
	{ prop: "reason", label: "请假原因", "min-width": 150, "show-overflow-tooltip": true },
	{ prop: "addTime", label: "请假时间", width: "160px", align: "center" },
	{ prop: "state", label: "请假状态", width: "100px", align: "center" },
];

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<StudentLeaveItemDTO>());
const selectedRows = ref<StudentLeaveItemDTO[]>([]);

const displayPageData = computed(() => {
	return pageData.value;
});

function getCellClass(prop: string, _row: StudentLeaveItemDTO) {
	if (prop === "addTime") return "cell-add-time";
	if (prop === "state") return "cell-state";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		pageIndex: 1,
		pageSize: 20,
		nameOrPhone: "",
		teacherId: undefined,
		startDate: "",
		endDate: "",
	});
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

async function handleRevoke() {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请先选择要撤销的请假记录");
		return;
	}
	try {
		await ElMessageBox.confirm(`确认撤销选中的 ${selectedRows.value.length} 条请假记录吗？`, "请假撤销确认", {
			confirmButtonText: "确定",
			cancelButtonText: "取消",
			type: "warning",
		});
		const ids = selectedRows.value.map((row) => row.id).filter((id): id is number => id !== undefined);
		await cancelStudentLeave(ids);
		ElMessage.success("请假撤销成功");
		loadData();
	} catch (error) {
		if (error === "cancel") {
			return;
		}
		console.error("请假撤销失败:", error);
		ElMessage.error("请假撤销失败");
	}
}

async function loadData() {
	try {
		const res = await getStudentLeavePage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			nameOrPhone: filters.nameOrPhone,
			teacherId: filters.teacherId,
			startDate: filters.startDate,
			endDate: filters.endDate,
		});
		if (res.data) {
			// 将数组包装成 PageDTO 格式
			pageData.value = createPageDTO<StudentLeaveItemDTO>({
				pageIndex: pageIndex.value,
				pageSize: pageSize.value,
				total: res.data.length,
				rows: res.data,
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

.batch-actions {
	display: flex;
	gap: 12px;
	margin-top: 12px;
}

:deep(.cell-add-time) {
	color: #e6a23c;
	font-weight: bold;
}

:deep(.cell-state) {
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
