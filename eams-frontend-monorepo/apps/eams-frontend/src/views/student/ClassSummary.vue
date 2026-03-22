<template>
	<div class="class-summary-container">
		<div class="class-summary-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学员姓名:</label>
						<el-input v-model="filters.studentName" placeholder="请输入学员姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">分校区:</label>
						<el-select v-model="filters.campus" placeholder="请选择分校区" clearable class="filter-input">
							<el-option label="主校区" value="main" />
							<el-option label="一分校" value="branch1" />
							<el-option label="二分校" value="branch2" />
						</el-select>
					</div>
					<div class="filter-item">
						<label class="filter-label">课程:</label>
						<el-select v-model="filters.course" placeholder="请选择课程" clearable class="filter-input">
							<el-option label="少儿编程" value="kids" />
							<el-option label="Python" value="python" />
							<el-option label="Java" value="java" />
							<el-option label="C++" value="cpp" />
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

const filters = reactive({
	studentName: "",
	campus: "",
	course: "",
});

const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	striped: true,
	"highlight-current-row": true,
};

const tableColumns: MyTableColumn[] = [
	{ prop: "studentName", label: "学员姓名", "min-width": 120 },
	{ prop: "campus", label: "分校区", "min-width": 100 },
	{ prop: "course", label: "课程", "min-width": 120 },
	{ prop: "classRecord", label: "上课记录", "min-width": 180, "show-overflow-tooltip": true },
	{ prop: "totalHours", label: "总课时", width: 100, align: "center" },
	{ prop: "completedHours", label: "已上课时", width: 100, align: "center" },
	{ prop: "sickLeave", label: "病假", width: 80, align: "center" },
	{ prop: "personalLeave", label: "事假", width: 80, align: "center" },
];

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<Record<string, any>>());
const selectedRows = ref<Record<string, any>[]>([]);

const displayPageData = computed(() => {
	return pageData.value;
});

function getCellClass(prop: string, row: Record<string, any>) {
	if (prop === "totalHours") return "cell-total";
	if (prop === "completedHours") return "cell-completed";
	if (prop === "sickLeave") return "cell-sick";
	if (prop === "personalLeave") return "cell-personal";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		studentName: "",
		campus: "",
		course: "",
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

function handlePageChange(data: PageDTO<Record<string, any>>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: Record<string, any>[]) {
	selectedRows.value = rows;
}

async function loadData() {
	const mockData = Array.from({ length: 20 }, (_, i) => ({
		id: i + 1,
		studentName: `学员${i + 1}`,
		campus: i % 3 === 0 ? "主校区" : i % 3 === 1 ? "一分校" : "二分校",
		course: i % 4 === 0 ? "少儿编程" : i % 4 === 1 ? "Python" : i % 4 === 2 ? "Java" : "C++",
		classRecord: `上课记录 ${i + 1}`,
		totalHours: Math.floor(Math.random() * 100) + 20,
		completedHours: Math.floor(Math.random() * 80) + 10,
		sickLeave: Math.floor(Math.random() * 5),
		personalLeave: Math.floor(Math.random() * 5),
	}));

	pageData.value = createPageDTO({
		pageIndex: pageIndex.value,
		pageSize: pageSize.value,
		total: 127,
		rows: mockData,
	});
}

onMounted(() => {
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
	color: #409EFF;
	font-weight: bold;
}

:deep(.cell-completed) {
	color: #67C23A;
	font-weight: bold;
}

:deep(.cell-sick) {
	color: #E6A23C;
}

:deep(.cell-personal) {
	color: #F56C6C;
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
