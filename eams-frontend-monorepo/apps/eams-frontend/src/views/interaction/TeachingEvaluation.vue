<template>
	<div class="teaching-evaluation">
		<!-- 搜索行 -->
		<div class="search-row">
			<div class="search-box" :class="{ collapsed: !searchExpanded }">
				<div class="search-item">
					<span class="search-label">评价内容</span>
					<el-input v-model="searchForm.content" placeholder="请输入评价内容" clearable />
				</div>
				<div class="search-item">
					<span class="search-label">课次</span>
					<el-input v-model="searchForm.courseTitle" placeholder="请输入课次" clearable />
				</div>
				<div v-show="searchExpanded" class="search-item">
					<span class="search-label">老师</span>
					<el-input v-model="searchForm.creatorName" placeholder="请输入老师姓名" clearable />
				</div>
				<div v-show="searchExpanded" class="search-item">
					<span class="search-label">学生</span>
					<el-input v-model="searchForm.studentName" placeholder="请输入学生姓名" clearable />
				</div>
				<div v-show="searchExpanded" class="search-item">
					<span class="search-label">点评时间</span>
					<el-date-picker
						v-model="dateRange"
						type="daterange"
						start-placeholder="开始日期"
						end-placeholder="结束日期"
						value-format="YYYY-MM-DD HH:mm:ss"
						clearable
					/>
				</div>
			</div>
			<div class="search-actions">
				<el-button type="primary" :icon="Search" @click="handleSearch">搜索</el-button>
				<el-button :icon="Refresh" @click="handleResetSearch">重置</el-button>
				<el-button link type="primary" @click="searchExpanded = !searchExpanded">
					{{ searchExpanded ? "收起" : "展开" }}
					<el-icon class="expand-icon" :class="{ rotated: searchExpanded }"><ArrowDown /></el-icon>
				</el-button>
			</div>
		</div>

		<!-- 表格区域 -->
		<F1Table
			:config="tableConfig"
			:data="tableData"
			:loading="loading"
			@page-change="handlePageChange"
			@edit="handleDetail"
		>
			<template #studentName="{ row }">
				<el-text type="primary">{{ row.studentName }}</el-text>
			</template>
			<template #score="{ row }">
				<el-tag :type="row.score >= 90 ? 'success' : row.score >= 80 ? 'info' : 'warning'">{{ row.score }}</el-tag>
			</template>
			<template #content="{ row }">
				<el-text truncated>{{ row.content }}</el-text>
			</template>
		</F1Table>

		<!-- 详情弹窗 -->
		<el-dialog v-model="detailDialogVisible" title="点评详情" width="500px" destroy-on-close>
			<template v-if="currentDetail">
				<el-descriptions :column="1" border>
					<el-descriptions-item label="学员姓名">{{ currentDetail.studentName }}</el-descriptions-item>
					<el-descriptions-item label="课次标题">{{ currentDetail.courseTitle }}</el-descriptions-item>
					<el-descriptions-item label="点评得分">
						<el-tag :type="currentDetail.score >= 90 ? 'success' : currentDetail.score >= 80 ? 'info' : 'warning'">{{ currentDetail.score }}</el-tag>
					</el-descriptions-item>
					<el-descriptions-item label="点评内容">{{ currentDetail.content }}</el-descriptions-item>
					<el-descriptions-item label="点评老师">{{ currentDetail.creatorName }}</el-descriptions-item>
					<el-descriptions-item label="点评时间">{{ currentDetail.addTime }}</el-descriptions-item>
				</el-descriptions>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { Search, Refresh, ArrowDown } from "@element-plus/icons-vue";
import F1Table from "@/components/f1table/F1Table.vue";
import { TableType } from "@/components/f1table/type";
import type { TableConfig } from "@/components/f1table/type";
import { listCourseComment } from "@/apis/interaction/teaching-evaluation";
import type { CourseCommentVO } from "@/apis/interaction/teaching-evaluation/type";

// ==================== 搜索与列表 ====================

const searchForm = reactive({
	content: "",
	courseTitle: "",
	creatorName: "",
	studentName: "",
	addTimeStart: "",
	addTimeEnd: "",
	pageIndex: 1,
	pageSize: 10,
});

/** 搜索栏展开状态 */
const searchExpanded = ref(false);

/** 日期范围选择绑定 */
const dateRange = ref<[string, string] | null>(null);

const tableConfig = ref<TableConfig>({
	tableProperties: {
		stripe: true,
		border: true,
	},
	tableList: [
		{ type: TableType.index, width: "60px", label: "序号", fixed: true },
		{ type: TableType.normal, prop: "studentName", label: "学员姓名", width: "120px" },
		{ type: TableType.normal, prop: "courseTitle", label: "课次标题", minWidth: "180px" },
		{ type: TableType.normal, prop: "score", label: "点评得分", width: "100px" },
		{ type: TableType.normal, prop: "content", label: "点评内容", minWidth: "200px" },
		{ type: TableType.normal, prop: "creatorName", label: "点评老师", width: "120px" },
		{ type: TableType.normal, prop: "addTime", label: "点评时间", width: "170px" },
		{ type: TableType.handler as any, label: "操作", width: "80px", editText: "详情" },
	],
	pagination: {
		enabled: true,
		currentPage: 1,
		pageSize: 10,
		total: 0,
	},
	handler: {
		edit: true,
		view: false,
		delete: false,
		editText: "详情",
	},
});

const tableData = ref<CourseCommentVO[]>([]);
const loading = ref(false);

async function loadData() {
	loading.value = true;
	try {
		// 同步日期范围到搜索参数
		if (dateRange.value) {
			searchForm.addTimeStart = dateRange.value[0];
			searchForm.addTimeEnd = dateRange.value[1];
		} else {
			searchForm.addTimeStart = "";
			searchForm.addTimeEnd = "";
		}

		const res = await listCourseComment(searchForm);
		if (res.code === 10000 && res.data) {
			tableData.value = res.data.rows || [];
			tableConfig.value.pagination!.total = res.data.total;
		}
	} catch (error) {
		console.error("获取教评学列表失败:", error);
	} finally {
		loading.value = false;
	}
}

function handleSearch() {
	searchForm.pageIndex = 1;
	loadData();
}

function handleResetSearch() {
	searchForm.content = "";
	searchForm.courseTitle = "";
	searchForm.creatorName = "";
	searchForm.studentName = "";
	dateRange.value = null;
	handleSearch();
}

function handlePageChange(page: number, size: number) {
	searchForm.pageIndex = page;
	searchForm.pageSize = size;
	loadData();
}

// ==================== 详情弹窗 ====================

const detailDialogVisible = ref(false);
const currentDetail = ref<CourseCommentVO | null>(null);

function handleDetail(row: CourseCommentVO) {
	currentDetail.value = row;
	detailDialogVisible.value = true;
}

// ==================== 初始化 ====================

onMounted(() => {
	loadData();
});
</script>

<style scoped lang="scss">
.teaching-evaluation {
	padding: 16px;
}

.search-row {
	display: flex;
	align-items: flex-start;
	justify-content: space-between;
	margin-bottom: 12px;
}

.search-box {
	display: flex;
	align-items: center;
	flex-wrap: wrap;
	gap: 16px;
	flex: 1;
	padding: 12px 16px;
	background: #fff;
	border: 1px solid #e4e7ed;
	border-radius: 4px;
	overflow: hidden;
	transition: max-height 0.3s ease;
}

.search-item {
	display: flex;
	align-items: center;
	gap: 8px;

	.search-label {
		font-size: 14px;
		color: #606266;
		white-space: nowrap;
	}

	.el-input {
		width: 180px;
	}
}

.search-actions {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-left: 16px;
	flex-shrink: 0;
	background: #fff;
	padding: 12px 0;
}

.expand-icon {
	transition: transform 0.3s;
	margin-left: 2px;
	&.rotated {
		transform: rotate(180deg);
	}
}
</style>
