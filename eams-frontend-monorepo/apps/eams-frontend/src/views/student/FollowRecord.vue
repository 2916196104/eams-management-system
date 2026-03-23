<template>
	<div class="follow-record-container">
		<div class="follow-record-content">
			<div class="top-bar">
				<div class="filter-area">
					<div class="filter-item">
						<label class="filter-label">学员姓名:</label>
						<el-input v-model="filters.studentName" placeholder="请输入学员姓名" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">跟进阶段:</label>
						<el-select v-model="filters.stage" placeholder="请选择跟进阶段" clearable class="filter-input">
							<el-option
								v-for="(item, index) in stageList"
								:key="item.id || index"
								:label="item.name || '未知阶段'"
								:value="item.id || ''"
							/>
						</el-select>
					</div>
					<div class="filter-item">
						<label class="filter-label">跟进人:</label>
						<el-input v-model="filters.follower" placeholder="请输入跟进人" clearable class="filter-input" />
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
					<template v-if="['followTime', 'nextFollow', 'recordTime'].includes(prop)">
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
import { getFollowRecordPage, getFollowStageList } from "@/apis/student";
import type { FollowRecordItemDTO, FollowStageItemDTO } from "@/apis/student/type";

const filters = reactive({
	studentName: "",
	stage: "",
	follower: "",
	startTime: "",
	endTime: "",
});

const stageList = ref<FollowStageItemDTO[]>([]);

const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};

const tableColumns: MyTableColumn[] = [
	{ prop: "followTime", label: "跟进时间", width: "160px", align: "center" },
	{ prop: "follower", label: "跟进人", "min-width": 100 },
	{ prop: "customer", label: "客户", "min-width": 120 },
	{ prop: "stage", label: "阶段", "min-width": 120 },
	{ prop: "followMethod", label: "跟进方式", "min-width": 100 },
	{ prop: "nextFollow", label: "下次跟进", width: "160px", align: "center" },
	{ prop: "recordTime", label: "记录时间", width: "160px", align: "center" },
	{ prop: "followContent", label: "跟进内容", "min-width": 200, "show-overflow-tooltip": true },
];

const pageIndex = ref(1);
const pageSize = ref(20);
const pageData = ref(createPageDTO<FollowRecordItemDTO>());
const selectedRows = ref<FollowRecordItemDTO[]>([]);

const displayPageData = computed(() => {
	return pageData.value;
});

function getCellClass(prop: string, _row: FollowRecordItemDTO) {
	if (prop === "followTime") return "cell-follow-time";
	if (prop === "nextFollow") return "cell-next-follow";
	if (prop === "recordTime") return "cell-record-time";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		studentName: "",
		stage: "",
		follower: "",
		startTime: "",
		endTime: "",
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

function handlePageChange(data: PageDTO<FollowRecordItemDTO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: FollowRecordItemDTO[]) {
	selectedRows.value = rows;
}

async function loadStageList() {
	try {
		const res = await getFollowStageList();
		if (res.data) {
			stageList.value = res.data;
		}
	} catch (error) {
		console.error("加载跟进阶段列表失败:", error);
		ElMessage.error("加载跟进阶段列表失败");
	}
}

async function loadData() {
	try {
		const res = await getFollowRecordPage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			studentName: filters.studentName,
			stage: filters.stage,
			follower: filters.follower,
			startTime: filters.startTime,
			endTime: filters.endTime,
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
	loadStageList();
	loadData();
});
</script>

<style scoped>
.follow-record-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.follow-record-content {
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

:deep(.cell-follow-time) {
	color: #409eff;
	font-weight: bold;
}

:deep(.cell-next-follow) {
	color: #e6a23c;
	font-weight: bold;
}

:deep(.cell-record-time) {
	color: #909399;
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
