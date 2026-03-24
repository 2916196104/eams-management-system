<template>
	<div class="signup-record-container">
		<div class="signup-record-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学员姓名:</label>
						<el-input v-model="filters.studentName" placeholder="请输入学员姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">开始日期:</label>
						<el-date-picker
							v-model="filters.startTime"
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
							v-model="filters.endTime"
							type="date"
							placeholder="请选择结束日期"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
						/>
					</div>
					<div class="filter-item">
						<label class="filter-label">课程名称:</label>
						<el-select v-model="filters.courseName" placeholder="请选择课程" clearable class="filter-input">
							<el-option
								v-for="(item, index) in courseList"
								:key="item.id || index"
								:label="item.name || '未知课程'"
								:value="item.id || ''"
							/>
						</el-select>
					</div>
					<div class="filter-item">
						<label class="filter-label">经办人:</label>
						<el-input v-model="filters.operatorName" placeholder="请输入经办人" clearable class="filter-input" />
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
					<el-button :icon="Download" circle @click="handleExport" />
				</div>
			</div>
			<div class="batch-actions">
				<el-button @click="handleBatchSignup">
					<el-icon><List /></el-icon>
					批量报名
				</el-button>
				<el-button @click="handleBatchDelete">
					<el-icon><Delete /></el-icon>
					删除
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
					<template v-if="['amount', 'remainingLessons', 'verifyState'].includes(prop)">
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
import { CircleClose, Delete, Download, List, Menu, Printer, RefreshRight, Search } from "@element-plus/icons-vue";
import MyTable from "@/components/mytable/MyTable.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import { getSignupRecordPage, getCourseList, batchSignup, batchDelete, exportSignupRecord } from "@/apis/student";
import type { SignupRecordItemDTO, CourseItemDTO, ExportSignupRecordRequest } from "@/apis/student/type";

const filters = reactive({
	callBackId: undefined,
	changeType: undefined,
	courseName: "",
	endTime: "",
	startTime: "",
	studentName: "",
	operatorName: "",
});

// 课程列表
const courseList = ref<CourseItemDTO[]>([]);

// 报名记录表格属性
const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};
// 报名记录表格列
const tableColumns: MyTableColumn[] = [
	{ prop: "addTime", label: "报名时间", width: "160px", align: "center" },
	{ prop: "studentName", label: "学员", "min-width": 120 },
	{ prop: "courseName", label: "课程", "min-width": 120 },
	{ prop: "subjectName", label: "科目", "min-width": 100 },
	{ prop: "operatorName", label: "经办人", "min-width": 100 },
	{ prop: "amount", label: "金额", width: "100px", align: "center" },
	{ prop: "countLessonComplete", label: "已完成课时", width: "100px", align: "center" },
	{ prop: "countLessonTotal", label: "总课时", width: "100px", align: "center" },
	{ prop: "remainingLessons", label: "剩余课次", width: "100px", align: "center" },
	{ prop: "verifyState", label: "审核状态", width: "100px", align: "center" },
];

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<SignupRecordItemDTO>());
const selectedRows = ref<SignupRecordItemDTO[]>([]);

const displayPageData = computed(() => {
	return pageData.value;
});

// 获取表格单元格类名
function getCellClass(prop: string, _row: SignupRecordItemDTO) {
	if (prop === "amount") return "cell-amount";
	if (prop === "remainingLessons") return "cell-remaining";
	if (prop === "verifyState") return "cell-verify-state";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		callBackId: undefined,
		changeType: undefined,
		courseName: "",
		endTime: "",
		startTime: "",
		studentName: "",
		operatorName: "",
	});
	pageIndex.value = 1;
	loadData();
}
// 刷新数据
function handleRefresh() {
	loadData();
}
// 打印
function handlePrint() {
	ElMessage.info("打印功能待接入");
}
// 自定义排序
function handleCustomSort() {
	ElMessage.info("自定义排序功能待接入");
}

async function handleExport() {
	try {
		const params: ExportSignupRecordRequest = {
			studentName: filters.studentName,
			startTime: filters.startTime,
			endTime: filters.endTime,
			courseName: filters.courseName,
			operatorName: filters.operatorName,
		};
		const res = await exportSignupRecord(params);

		// 创建下载链接
		const blob = new Blob([res.data], { type: "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet" });
		const url = window.URL.createObjectURL(blob);
		const link = document.createElement("a");
		link.href = url;
		link.download = `报名记录_${new Date().getTime()}.xlsx`;
		link.click();
		window.URL.revokeObjectURL(url);

		ElMessage.success("导出成功");
	} catch (error) {
		console.error("导出失败:", error);
		ElMessage.error("导出失败");
	}
}

function handlePageChange(data: PageDTO<SignupRecordItemDTO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: SignupRecordItemDTO[]) {
	selectedRows.value = rows;
}

async function handleBatchSignup() {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请先选择要批量报名的记录");
		return;
	}
	try {
		await ElMessageBox.confirm(`确认批量报名选中的 ${selectedRows.value.length} 条记录吗？`, "批量报名确认", {
			confirmButtonText: "确定",
			cancelButtonText: "取消",
			type: "warning",
		});
		const ids = selectedRows.value.map((row) => row.id).filter((id): id is number => id !== undefined);
		await batchSignup({ ids });
		ElMessage.success("批量报名成功");
		loadData();
	} catch (error) {
		if (error === "cancel") {
			return;
		}
		console.error("批量报名失败:", error);
		ElMessage.error("批量报名失败");
	}
}

async function handleBatchDelete() {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请先选择要删除的记录");
		return;
	}
	try {
		await ElMessageBox.confirm(
			`确认删除选中的 ${selectedRows.value.length} 条记录吗？此操作不可恢复！`,
			"批量删除确认",
			{
				confirmButtonText: "确定",
				cancelButtonText: "取消",
				type: "warning",
			},
		);
		const ids = selectedRows.value.map((row) => row.id).filter((id): id is number => id !== undefined);
		await batchDelete({ ids });
		ElMessage.success("批量删除成功");
		loadData();
	} catch (error) {
		if (error === "cancel") {
			return;
		}
		console.error("批量删除失败:", error);
		ElMessage.error("批量删除失败");
	}
}

async function loadCourseList() {
	try {
		const res = await getCourseList();
		if (res.data) {
			courseList.value = res.data;
		}
	} catch (error) {
		console.error("加载课程列表失败:", error);
		ElMessage.error("加载课程列表失败");
	}
}

// 加载数据
async function loadData() {
	try {
		const res = await getSignupRecordPage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			callBackId: filters.callBackId,
			changeType: filters.changeType,
			courseName: filters.courseName,
			endTime: filters.endTime,
			startTime: filters.startTime,
			studentName: filters.studentName,
			operatorName: filters.operatorName,
		});
		if (res.data) {
			pageData.value = res.data;
		}
	} catch (error) {
		console.error("加载数据失败:", error);
		ElMessage.error("加载数据失败");
	}
}

// 初始化加载数据
onMounted(() => {
	loadCourseList();
	loadData();
});
</script>

<style scoped>
.signup-record-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.signup-record-content {
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

.batch-actions {
	display: flex;
	gap: 12px;
	margin-top: 12px;
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

:deep(.cell-amount) {
	color: #409eff;
	font-weight: bold;
}

:deep(.cell-remaining) {
	color: #67c23a;
	font-weight: bold;
}

:deep(.cell-verify-state) {
	color: #e6a23c;
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
