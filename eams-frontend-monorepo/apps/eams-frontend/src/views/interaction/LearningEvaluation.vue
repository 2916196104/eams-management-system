<template>
	<div class="learning-evaluation">
		<!-- 搜索行 -->
		<div class="search-row">
			<div class="search-box">
				<div class="search-item">
					<span class="search-label">课次标题</span>
					<el-input v-model="searchForm.lessonTitle" placeholder="请输入课次标题" clearable />
				</div>
				<template v-if="searchExpanded">
					<div class="search-item">
						<span class="search-label">评价时间</span>
						<el-date-picker
							v-model="searchForm.dateRange"
							type="datetimerange"
							range-separator="至"
							start-placeholder="开始时间"
							end-placeholder="结束时间"
							value-format="YYYY-MM-DD HH:mm:ss"
							:default-time="[new Date(2026, 0, 1, 0, 0, 0), new Date(2026, 0, 1, 23, 59, 59)]"
						/>
					</div>
					<div class="search-item">
						<span class="search-label">老师姓名</span>
						<el-input v-model="searchForm.teacherName" placeholder="请输入老师姓名" clearable />
					</div>
					<div class="search-item">
						<span class="search-label">学员姓名</span>
						<el-input v-model="searchForm.studentName" placeholder="请输入学员姓名" clearable />
					</div>
				</template>
				<div class="search-actions">
					<el-button type="primary" :icon="Search" @click="handleSearch">搜索</el-button>
					<el-button :icon="Delete" @click="handleResetSearch">重置</el-button>
					<el-button link type="primary" @click="searchExpanded = !searchExpanded">
						{{ searchExpanded ? "收起" : "展开" }}
						<el-icon class="expand-icon" :class="{ 'is-expanded': searchExpanded }"><ArrowDown /></el-icon>
					</el-button>
				</div>
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
			<template #overallScore="{ row }">
				<el-tag :type="getScoreTagType(row.overallScore)">{{ row.overallScore }}</el-tag>
			</template>
			<template #atmosphereScore="{ row }">
				<el-tag :type="getScoreTagType(row.atmosphereScore)">{{ row.atmosphereScore }}</el-tag>
			</template>
			<template #attitudeScore="{ row }">
				<el-tag :type="getScoreTagType(row.attitudeScore)">{{ row.attitudeScore }}</el-tag>
			</template>
			<template #effectScore="{ row }">
				<el-tag :type="getScoreTagType(row.effectScore)">{{ row.effectScore }}</el-tag>
			</template>
			<template #content="{ row }">
				<el-text truncated>{{ row.content }}</el-text>
			</template>
		</F1Table>

		<!-- 评价详情弹窗 -->
		<el-dialog v-model="detailDialogVisible" title="评价详情" width="600px" destroy-on-close>
			<template v-if="currentDetail">
				<el-descriptions :column="2" border>
					<el-descriptions-item label="学员姓名">{{ currentDetail.studentName }}</el-descriptions-item>
					<el-descriptions-item label="老师姓名">{{ currentDetail.teacherName }}</el-descriptions-item>
					<el-descriptions-item label="课次标题" :span="2">{{ currentDetail.lessonTitle }}</el-descriptions-item>
					<el-descriptions-item label="综合评分">
						<el-tag :type="getScoreTagType(currentDetail.overallScore)" size="large">{{ currentDetail.overallScore }}</el-tag>
					</el-descriptions-item>
					<el-descriptions-item label="评价时间">{{ currentDetail.addTime }}</el-descriptions-item>
				</el-descriptions>
				<el-descriptions :column="3" border style="margin-top: 16px">
					<el-descriptions-item label="课堂气氛">
						<el-tag :type="getScoreTagType(currentDetail.atmosphereScore)">{{ currentDetail.atmosphereScore }}</el-tag>
					</el-descriptions-item>
					<el-descriptions-item label="授课态度">
						<el-tag :type="getScoreTagType(currentDetail.attitudeScore)">{{ currentDetail.attitudeScore }}</el-tag>
					</el-descriptions-item>
					<el-descriptions-item label="教学效果">
						<el-tag :type="getScoreTagType(currentDetail.effectScore)">{{ currentDetail.effectScore }}</el-tag>
					</el-descriptions-item>
				</el-descriptions>
				<div class="detail-content-section">
					<div class="detail-content-label">评价内容</div>
					<div class="detail-content-text">{{ currentDetail.content }}</div>
				</div>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { Search, Delete, ArrowDown } from "@element-plus/icons-vue";
import F1Table from "@/components/f1table/F1Table.vue";
import { TableType } from "@/components/f1table/type";
import type { TableConfig } from "@/components/f1table/type";
import { listLearningEvaluation } from "@/apis/interaction/learning-evaluation";
import type { TeachEvaluationVO } from "@/apis/interaction/learning-evaluation/type";

// ==================== 搜索相关 ====================

const searchExpanded = ref(false);

const searchForm = reactive({
	lessonTitle: "",
	dateRange: [] as string[],
	teacherName: "",
	studentName: "",
	pageIndex: 1,
	pageSize: 10,
});

function handleSearch() {
	searchForm.pageIndex = 1;
	loadData();
}

function handleResetSearch() {
	searchForm.lessonTitle = "";
	searchForm.dateRange = [];
	searchForm.teacherName = "";
	searchForm.studentName = "";
	handleSearch();
}

// ==================== 表格相关 ====================

const tableConfig = ref<TableConfig>({
	tableProperties: {
		stripe: true,
		border: true,
	},
	tableList: [
		{ type: TableType.index, width: "60px", label: "序号", fixed: true },
		{ type: TableType.normal, prop: "studentName", label: "学员姓名", width: "100px" },
		{ type: TableType.normal, prop: "teacherName", label: "老师姓名", width: "100px" },
		{ type: TableType.normal, prop: "lessonTitle", label: "课次标题", minWidth: "160px", showOverflowTooltip: true },
		{ type: TableType.normal, prop: "overallScore", label: "综合评分", width: "100px" },
		{ type: TableType.normal, prop: "atmosphereScore", label: "课堂气氛", width: "100px" },
		{ type: TableType.normal, prop: "attitudeScore", label: "授课态度", width: "100px" },
		{ type: TableType.normal, prop: "effectScore", label: "教学效果", width: "100px" },
		{ type: TableType.normal, prop: "content", label: "评价内容", minWidth: "200px" },
		{ type: TableType.normal, prop: "addTime", label: "评价时间", width: "170px" },
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

const tableData = ref<TeachEvaluationVO[]>([]);
const loading = ref(false);

async function loadData() {
	loading.value = true;
	try {
		const query = {
			lessonTitle: searchForm.lessonTitle || undefined,
			addTimeStart: searchForm.dateRange?.[0] || undefined,
			addTimeEnd: searchForm.dateRange?.[1] || undefined,
			teacherId: searchForm.teacherName ? 1 : undefined, // Mock 阶段暂用固定 ID
			studentId: searchForm.studentName ? 1 : undefined,
			pageIndex: searchForm.pageIndex,
			pageSize: searchForm.pageSize,
		};
		const res = await listLearningEvaluation(query);
		if (res.code === 10000 && res.data) {
			tableData.value = res.data.rows || [];
			tableConfig.value.pagination!.total = res.data.total;
		}
	} catch (error) {
		console.error("获取学评教列表失败:", error);
	} finally {
		loading.value = false;
	}
}

function handlePageChange(page: number, size: number) {
	searchForm.pageIndex = page;
	searchForm.pageSize = size;
	loadData();
}

/** 根据分数返回 tag 类型 */
function getScoreTagType(score: number): "success" | "warning" | "danger" {
	if (score >= 90) return "success";
	if (score >= 80) return "warning";
	return "danger";
}

// ==================== 详情弹窗 ====================

const detailDialogVisible = ref(false);
const currentDetail = ref<TeachEvaluationVO | null>(null);

function handleDetail(row: TeachEvaluationVO) {
	currentDetail.value = row;
	detailDialogVisible.value = true;
}

// ==================== 初始化 ====================

onMounted(() => {
	loadData();
});
</script>

<style scoped lang="scss">
.learning-evaluation {
	padding: 16px;
}

.search-row {
	margin-bottom: 12px;
}

.search-box {
	display: flex;
	flex-wrap: wrap;
	align-items: center;
	gap: 16px;
	padding: 12px 16px;
	background: #fff;
	border: 1px solid #e4e7ed;
	border-radius: 4px;
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
	margin-left: auto;

	.expand-icon {
		transition: transform 0.3s;

		&.is-expanded {
			transform: rotate(180deg);
		}
	}
}

.detail-content-section {
	margin-top: 16px;
}

.detail-content-label {
	font-size: 14px;
	font-weight: 600;
	color: #303133;
	margin-bottom: 8px;
}

.detail-content-text {
	font-size: 14px;
	color: #606266;
	line-height: 1.6;
	padding: 12px;
	background: #f5f7fa;
	border-radius: 4px;
}
</style>
