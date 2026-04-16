<template>
	<div class="schedule-plan-page">
		<!-- 搜索表单 -->
		<el-card class="search-card">
			<el-form :inline="true" :model="searchForm">
				<el-form-item label="班级名称">
					<el-input v-model="searchForm.className" placeholder="请输入班级名称" clearable style="width: 150px" />
				</el-form-item>
				<el-form-item label="课程名称">
					<el-input v-model="searchForm.courseName" placeholder="请输入课程名称" clearable style="width: 150px" />
				</el-form-item>
				<el-form-item>
					<el-button type="primary" @click="handleSearch">查询</el-button>
					<el-button @click="handleReset">重置</el-button>
				</el-form-item>
			</el-form>
		</el-card>

		<!-- 操作按钮 -->
		<el-card class="action-card">
			<el-button type="primary" @click="handleAdd">新增计划</el-button>
			<el-button type="warning" :disabled="selectedIds.length === 0" @click="handleBatchGenerate">
				批量生成课表
			</el-button>
			<el-button type="danger" :disabled="selectedIds.length === 0" @click="handleBatchDelete">删除计划</el-button>
			<el-button type="info" :disabled="selectedIds.length === 0" @click="handleCheckConflict">冲突检查</el-button>
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
					v-if="visibleColumns.includes('className')"
					prop="className"
					label="班级名称"
					min-width="150"
				/>
				<el-table-column
					v-if="visibleColumns.includes('courseName')"
					prop="courseName"
					label="所属课程"
					min-width="150"
				/>
				<el-table-column
					v-if="visibleColumns.includes('teacherNames')"
					prop="teacherNames"
					label="上课老师"
					min-width="120"
				/>
				<el-table-column
					v-if="visibleColumns.includes('assistantNames')"
					prop="assistantNames"
					label="助教"
					min-width="100"
				/>
				<el-table-column v-if="visibleColumns.includes('startDate')" prop="startDate" label="开始日期" width="120" />
				<el-table-column v-if="visibleColumns.includes('endDate')" prop="endDate" label="结束日期" width="120" />
				<el-table-column
					v-if="visibleColumns.includes('decLessonCount')"
					prop="decLessonCount"
					label="消课基数"
					width="100"
				/>
				<el-table-column v-if="visibleColumns.includes('times')" prop="times" label="排课次数" width="100" />
				<el-table-column v-if="visibleColumns.includes('excludeHoliday')" label="排除节假日" width="100">
					<template #default="{ row }">{{ row.excludeHoliday ? "是" : "否" }}</template>
				</el-table-column>
				<el-table-column v-if="visibleColumns.includes('action')" label="操作" width="100" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="handleEdit(row)">编辑</el-button>
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

		<!-- 新增/编辑弹窗 -->
		<el-dialog v-model="dialogVisible" :title="dialogTitle" width="700px">
			<el-form ref="formRef" :model="formData" :rules="formRules" label-width="100px">
				<el-form-item label="班级" prop="classId">
					<el-select v-model="formData.classId" placeholder="请选择班级" filterable style="width: 100%">
						<el-option v-for="item in classOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="课程" prop="courseId">
					<el-select v-model="formData.courseId" placeholder="请选择课程" filterable style="width: 100%">
						<el-option v-for="item in courseOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="上课老师" prop="teacherIds">
					<el-select v-model="formData.teacherIds" multiple placeholder="请选择老师" filterable style="width: 100%">
						<el-option v-for="item in teacherOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="助教" prop="assistantIds">
					<el-select v-model="formData.assistantIds" multiple placeholder="请选择助教" filterable style="width: 100%">
						<el-option v-for="item in assistantOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-row :gutter="20">
					<el-col :span="12">
						<el-form-item label="开始日期" prop="startDate">
							<el-date-picker
								v-model="formData.startDate"
								type="date"
								placeholder="选择日期"
								value-format="YYYY-MM-DD"
								style="width: 100%"
							/>
						</el-form-item>
					</el-col>
					<el-col :span="12">
						<el-form-item label="结束日期" prop="endDate">
							<el-date-picker
								v-model="formData.endDate"
								type="date"
								placeholder="选择日期"
								value-format="YYYY-MM-DD"
								style="width: 100%"
							/>
						</el-form-item>
					</el-col>
				</el-row>
				<el-row :gutter="20">
					<el-col :span="12">
						<el-form-item label="消课基数" prop="decLessonCount">
							<el-input-number v-model="formData.decLessonCount" :min="1" style="width: 100%" />
						</el-form-item>
					</el-col>
					<el-col :span="12">
						<el-form-item label="排课次数" prop="times">
							<el-input-number v-model="formData.times" :min="0" style="width: 100%" />
						</el-form-item>
					</el-col>
				</el-row>
				<el-form-item label="排除节假日" prop="excludeHoliday">
					<el-switch v-model="formData.excludeHoliday" />
				</el-form-item>
				<el-form-item label="排课设置" prop="setting">
					<div class="setting-list">
						<div v-for="(item, index) in formData.setting" :key="index" class="setting-item">
							<el-select v-model="item.weeks" multiple placeholder="星期" style="width: 150px">
								<el-option label="周一" :value="1" />
								<el-option label="周二" :value="2" />
								<el-option label="周三" :value="3" />
								<el-option label="周四" :value="4" />
								<el-option label="周五" :value="5" />
								<el-option label="周六" :value="6" />
								<el-option label="周日" :value="7" />
							</el-select>
							<el-time-picker v-model="item.startTime" placeholder="开始时间" format="HH:mm" style="width: 120px" />
							<el-time-picker v-model="item.endTime" placeholder="结束时间" format="HH:mm" style="width: 120px" />
							<el-select v-model="item.roomId" placeholder="教室" filterable style="width: 150px">
								<el-option v-for="room in roomOptions" :key="room.id" :label="room.name" :value="room.id" />
							</el-select>
							<el-button type="danger" @click="removeSetting(index)">删除</el-button>
						</div>
						<el-button type="primary" @click="addSetting">添加上课时间</el-button>
					</div>
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="dialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="submitLoading" @click="handleSubmit">确定</el-button>
			</template>
		</el-dialog>

		<!-- 冲突检查弹窗 -->
		<el-dialog v-model="conflictDialogVisible" title="冲突检查结果" width="700px">
			<div v-if="conflictResult?.hasConflict === false" class="conflict-success">
				<el-icon><SuccessFilled /></el-icon>
				<span>未发现冲突</span>
			</div>
			<el-table v-else-if="conflictResult?.conflicts?.length" :data="conflictResult.conflicts" border>
				<el-table-column prop="className" label="班级名称" />
				<el-table-column prop="courseName" label="课程名称" />
				<el-table-column prop="conflictTypeName" label="冲突类型" />
				<el-table-column prop="conflictObjectName" label="冲突对象" />
				<el-table-column prop="conflictDate" label="冲突日期" />
				<el-table-column prop="conflictStartTime" label="开始时间" />
				<el-table-column prop="conflictEndTime" label="结束时间" />
			</el-table>
			<div v-else class="conflict-empty">暂无冲突数据</div>
			<template #footer>
				<el-button @click="conflictDialogVisible = false">关闭</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Refresh, Printer, Setting, ArrowDown, SuccessFilled } from "@element-plus/icons-vue";
import {
	getSchedulePlanList,
	saveSchedulePlan,
	deleteSchedulePlan,
	batchGenerateLesson,
	checkConflict,
	getTeacherList,
	type SchedulePlanItem,
	type SchedulePlanListParams,
	type SaveSchedulePlanParams,
} from "@/apis/academic/schedule-plan";

// 列定义
const allColumns = [
	{ key: "className", label: "班级名称" },
	{ key: "courseName", label: "所属课程" },
	{ key: "teacherNames", label: "上课老师" },
	{ key: "assistantNames", label: "助教" },
	{ key: "startDate", label: "开始日期" },
	{ key: "endDate", label: "结束日期" },
	{ key: "decLessonCount", label: "消课基数" },
	{ key: "times", label: "排课次数" },
	{ key: "excludeHoliday", label: "排除节假日" },
	{ key: "action", label: "操作" },
];

// 可见列
const visibleColumns = ref<string[]>(allColumns.map((col) => col.key));

// 从 localStorage 加载列配置
const loadColumnConfig = () => {
	const saved = localStorage.getItem("schedule-plan-columns");
	if (saved) {
		try {
			visibleColumns.value = JSON.parse(saved);
		} catch (e) {
			console.error("加载列配置失败", e);
		}
	}
};

// 保存列配置
const saveColumnConfig = () => {
	localStorage.setItem("schedule-plan-columns", JSON.stringify(visibleColumns.value));
};

// 切换列显示
const toggleColumn = (key: string) => {
	const index = visibleColumns.value.indexOf(key);
	if (index === -1) {
		visibleColumns.value.push(key);
	} else {
		visibleColumns.value.splice(index, 1);
	}
	saveColumnConfig();
};

// 下拉菜单命令
const handleColumnCommand = (command: string) => {
	toggleColumn(command);
};

// 刷新
const handleRefresh = () => {
	loadData();
};

// 打印
const handlePrint = () => {
	window.print();
};

// 搜索表单
const searchForm = reactive({
	className: "",
	courseName: "",
});

// 分页
const pagination = reactive({
	pageIndex: 1,
	pageSize: 20,
	total: 0,
});

// 表格数据
const tableData = ref<SchedulePlanItem[]>([]);
const loading = ref(false);
const selectedIds = ref<number[]>([]);

// 弹窗
const dialogVisible = ref(false);
const dialogTitle = ref("");
const submitLoading = ref(false);
const formRef = ref();

// 冲突检查
const conflictDialogVisible = ref(false);
const conflictResult = ref<any>(null);

// 表单数据
const formData = reactive<any>({
	classId: 0,
	courseId: 0,
	assistantIds: [],
	decLessonCount: 1,
	endDate: "",
	excludeHoliday: false,
	setting: [],
	startDate: "",
	teacherIds: [],
	times: 0,
});

// 表单校验
const formRules = {
	classId: [{ required: true, message: "请选择班级", trigger: "change" }],
	startDate: [{ required: true, message: "请选择开始日期", trigger: "change" }],
	endDate: [{ required: true, message: "请选择结束日期", trigger: "change" }],
};

// 下拉选项
const classOptions = ref<Array<{ id: number; name: string }>>([]);
const courseOptions = ref<Array<{ id: number; name: string }>>([]);
const teacherOptions = ref<Array<{ id: number; name: string }>>([]);
const assistantOptions = ref<Array<{ id: number; name: string }>>([]);
const roomOptions = ref<Array<{ id: number; name: string }>>([]);

/**
 * 加载列表数据
 */
const loadData = async () => {
  loading.value = true;
  try {
    const params: SchedulePlanListParams = {
      pageIndex: pagination.pageIndex,
      pageSize: pagination.pageSize,
      courseName: searchForm.courseName || undefined,
    };
    const res = await getSchedulePlanList(params);
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

/**
 * 搜索
 */
const handleSearch = () => {
	pagination.pageIndex = 1;
	loadData();
};

/**
 * 重置搜索
 */
const handleReset = () => {
	searchForm.className = "";
	searchForm.courseName = "";
	handleSearch();
};

/**
 * 表格选中变化
 */
const handleSelectionChange = (rows: SchedulePlanItem[]) => {
	selectedIds.value = rows.map((row) => row.id);
};

/**
 * 分页大小变化
 */
const handleSizeChange = (size: number) => {
	pagination.pageSize = size;
	loadData();
};

/**
 * 页码变化
 */
const handleCurrentChange = (page: number) => {
	pagination.pageIndex = page;
	loadData();
};

/**
 * 新增
 */
const handleAdd = () => {
	dialogTitle.value = "新增排课计划";
	Object.assign(formData, {
		id: undefined,
		classId: 0,
		teacherIds: [],
		assistantIds: [],
		startDate: "",
		endDate: "",
		decLessonCount: 1,
		times: 0,
		excludeHoliday: false,
		setting: [],
	});
	dialogVisible.value = true;
};

/**
 * 编辑
 */
const handleEdit = (row: SchedulePlanItem) => {
	dialogTitle.value = "编辑排课计划";
	Object.assign(formData, {
		id: row.id,
		classId: row.classId,
		teacherIds: row.teacherIds ? row.teacherIds.split(",").map(Number) : [],
		assistantIds: row.assistantIds ? row.assistantIds.split(",").map(Number) : [],
		startDate: row.startDate,
		endDate: row.endDate,
		decLessonCount: row.decLessonCount,
		times: row.times,
		excludeHoliday: row.excludeHoliday,
		setting: [],
	});
	dialogVisible.value = true;
};

/**
 * 添加排课设置
 */
const addSetting = () => {
	formData.setting.push({ weeks: [], startTime: "", endTime: "", roomId: 0 });
};

/**
 * 删除排课设置
 */
const removeSetting = (index: number | string) => {
	const idx = typeof index === "string" ? parseInt(index) : index;
	formData.setting.splice(idx, 1);
};

/**
 * 批量生成课表
 */
const handleBatchGenerate = () => {
	ElMessageBox.confirm(`确定为选中的 ${selectedIds.value.length} 个排课计划生成课表吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "info",
	}).then(async () => {
		try {
			const res = await batchGenerateLesson({ scheduleIds: selectedIds.value });
			if (res.data?.code === 10000) {
				ElMessage.success("生成成功");
				loadData();
			} else {
				ElMessage.error(res.data?.message || "生成失败");
			}
		} catch (error) {
			ElMessage.error("生成失败");
		}
	});
};

/**
 * 批量删除计划
 */
const handleBatchDelete = () => {
	ElMessageBox.confirm(`确定删除选中的 ${selectedIds.value.length} 个排课计划吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	}).then(async () => {
		try {
			const res = await deleteSchedulePlan(selectedIds.value);
			if (res.data?.code === 10000) {
				ElMessage.success("删除成功");
				selectedIds.value = [];
				if (tableData.value.length === selectedIds.value.length && pagination.pageIndex > 1) pagination.pageIndex--;
				loadData();
			} else {
				ElMessage.error(res.data?.message || "删除失败");
			}
		} catch (error) {
			ElMessage.error("删除失败");
		}
	});
};

/**
 * 冲突检查
 */
const handleCheckConflict = async () => {
	try {
		const res = await checkConflict({ scheduleIds: selectedIds.value });
		if (res.data?.code === 10000) {
			conflictResult.value = res.data.data;
			conflictDialogVisible.value = true;
		} else {
			ElMessage.error(res.data?.message || "检查失败");
		}
	} catch (error) {
		ElMessage.error("检查失败");
	}
};

/**
 * 提交表单
 */
const handleSubmit = async () => {
  await formRef.value?.validate();
  submitLoading.value = true;
  try {
    // 直接使用原始数组，不要 join 成字符串
    const submitData = {
      ...formData,
      // 确保 teacherIds 和 assistantIds 是数组（即使是空数组也传 []）
      teacherIds: Array.isArray(formData.teacherIds) ? formData.teacherIds : [],
      assistantIds: Array.isArray(formData.assistantIds) ? formData.assistantIds : [],
      // 如果 setting 中的 weeks 需要调整为字符串，可以在这里转换
      setting: formData.setting.map(s => ({
        ...s,
        weeks: s.weeks, // 保持数组，如果后端要求字符串则改为 s.weeks.join(',')
      })),
    };
    const res = await saveSchedulePlan(submitData);
    if (res.code === 10000) {
      ElMessage.success("保存成功");
      dialogVisible.value = false;
      loadData();
    } else {
      ElMessage.error(res.message || "保存失败");
    }
  } catch (error) {
    ElMessage.error("保存失败");
  } finally {
    submitLoading.value = false;
  }
};

/**
 * 加载下拉选项
 */
const loadOptions = async () => {
	// TODO: 从后端获取班级、课程、教室列表
	classOptions.value = [
		{ id: 1, name: "与世无争班级" },
		{ id: 2, name: "足球特长班" },
	];
	courseOptions.value = [
		{ id: 1, name: "近世代数" },
		{ id: 2, name: "C语言" },
	];
	teacherOptions.value = [
		{ id: 1, name: "王伟大" },
		{ id: 2, name: "李三" },
	];
	assistantOptions.value = [
		{ id: 1, name: "李助教" },
		{ id: 2, name: "王助教" },
	];
	roomOptions.value = [
		{ id: 1, name: "101教室" },
		{ id: 2, name: "102教室" },
	];

	// 真实接口调用
	// try {
	//   const res = await getTeacherList({ type: 1 });
	//   if (res.data?.code === 10000) {
	//     teacherOptions.value = res.data.data.records;
	//   }
	// } catch (error) {
	//   console.error('加载教师选项失败', error);
	// }
};

// 初始化
onMounted(() => {
	loadColumnConfig();
	loadData();
	loadOptions();
});
</script>

<style scoped lang="scss">
.schedule-plan-page {
	padding: 20px;

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

		.toolbar-left {
			.total-info {
				font-size: 14px;
				color: #606266;
			}
		}

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

	.setting-list {
		width: 100%;

		.setting-item {
			display: flex;
			gap: 10px;
			margin-bottom: 10px;
			align-items: center;
			flex-wrap: wrap;
		}
	}

	.conflict-success,
	.conflict-empty {
		display: flex;
		justify-content: center;
		align-items: center;
		padding: 40px;
		font-size: 16px;
	}

	.conflict-success {
		color: #67c23a;
		gap: 10px;
	}

	.conflict-empty {
		color: #909399;
	}
}

@media print {
	.search-card,
	.action-card,
	.table-toolbar,
	.pagination-wrapper {
		display: none;
	}
}
</style>
