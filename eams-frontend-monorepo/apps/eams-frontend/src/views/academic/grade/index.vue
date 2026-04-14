<template>
	<div class="grade-page">
		<!-- 搜索表单 -->
		<el-card class="search-card">
			<el-form :inline="true" :model="searchForm">
				<el-form-item label="年级名称">
					<el-input v-model="searchForm.name" placeholder="请输入年级名称" clearable style="width: 180px" />
				</el-form-item>
				<el-form-item label="入学年份">
					<el-input v-model="searchForm.year" placeholder="请输入入学年份" clearable style="width: 150px" />
				</el-form-item>
				<el-form-item>
					<el-button type="primary" @click="handleSearch">查询</el-button>
					<el-button @click="handleReset">重置</el-button>
				</el-form-item>
			</el-form>
		</el-card>

		<!-- 操作按钮 -->
		<el-card class="action-card">
			<el-button type="primary" @click="handleAdd">新增年级</el-button>
			<el-button type="danger" :disabled="selectedIds.length === 0" @click="handleBatchDelete">批量删除</el-button>
			<el-button type="warning" :disabled="selectedIds.length === 0" @click="handleUpgrade">升级</el-button>
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
				<el-table-column v-if="visibleColumns.includes('name')" prop="name" label="年级名称" min-width="150" />
				<el-table-column v-if="visibleColumns.includes('year')" prop="year" label="入学年份" width="120" />
				<el-table-column v-if="visibleColumns.includes('sortNum')" prop="sortNum" label="排序值" width="100" />
				<el-table-column v-if="visibleColumns.includes('remark')" prop="remark" label="备注" min-width="200" />
				<el-table-column v-if="visibleColumns.includes('action')" label="操作" width="100" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="handleEdit(row)">编辑</el-button>
						<el-button link type="danger" @click="handleDelete(row)">删除</el-button>
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
		<el-dialog v-model="dialogVisible" :title="dialogTitle" width="500px">
			<el-form ref="formRef" :model="formData" :rules="formRules" label-width="80px">
				<el-form-item label="年级名称" prop="name">
					<el-input v-model="formData.name" placeholder="请输入年级名称" />
				</el-form-item>
				<el-form-item label="入学年份" prop="year">
					<el-input-number v-model="formData.year" :min="1900" :max="2100" style="width: 100%" />
				</el-form-item>
				<el-form-item label="排序值" prop="sortNum">
					<el-input-number v-model="formData.sortNum" :min="0" style="width: 100%" />
				</el-form-item>
				<el-form-item label="备注" prop="remark">
					<el-input v-model="formData.remark" type="textarea" :rows="2" placeholder="请输入备注" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="dialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="submitLoading" @click="handleSubmit">确定</el-button>
			</template>
		</el-dialog>

		<!-- 升级弹窗 -->
		<el-dialog v-model="upgradeDialogVisible" title="年级升级" width="400px">
			<el-alert
				title="升级说明"
				type="info"
				description="升级会将选中的年级名称中的数字自动递增，例如一年级变成二年级，2024级变成2025级"
				:closable="false"
				show-icon
			/>
			<div class="upgrade-tip">
				<p>即将升级以下年级：</p>
				<ul>
					<li v-for="item in selectedGrades" :key="item.id">{{ item.name }} → {{ getUpgradedName(item.name) }}</li>
				</ul>
			</div>
			<template #footer>
				<el-button @click="upgradeDialogVisible = false">取消</el-button>
				<el-button type="primary" :loading="upgradeLoading" @click="confirmUpgrade">确定升级</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Refresh, Printer, Setting, ArrowDown } from "@element-plus/icons-vue";
import {
	getGradeList,
	saveGrade,
	deleteGrade,
	upgradeGrade,
	type GradeItem,
	type GradeListParams,
	type SaveGradeParams,
} from "@/apis/academic/grade";

// 列定义
const allColumns = [
	{ key: "name", label: "年级名称" },
	{ key: "year", label: "入学年份" },
	{ key: "sortNum", label: "排序值" },
	{ key: "remark", label: "备注" },
	{ key: "action", label: "操作" },
];

// 可见列
const visibleColumns = ref<string[]>(allColumns.map((col) => col.key));

// 从 localStorage 加载列配置
const loadColumnConfig = () => {
	const saved = localStorage.getItem("grade-columns");
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
	localStorage.setItem("grade-columns", JSON.stringify(visibleColumns.value));
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
	name: "",
	year: "",
});

// 分页
const pagination = reactive({
	pageIndex: 1,
	pageSize: 20,
	total: 0,
});

// 表格数据
const tableData = ref<GradeItem[]>([]);
const loading = ref(false);
const selectedIds = ref<number[]>([]);
const selectedGrades = ref<GradeItem[]>([]);

// 弹窗
const dialogVisible = ref(false);
const dialogTitle = ref("");
const submitLoading = ref(false);
const formRef = ref();

// 升级弹窗
const upgradeDialogVisible = ref(false);
const upgradeLoading = ref(false);

// 表单数据
const formData = reactive<SaveGradeParams>({
	name: "",
	year: undefined,
	sortNum: 0,
	remark: "",
});

// 表单校验
const formRules = {
	name: [{ required: true, message: "请输入年级名称", trigger: "blur" }],
};

/**
 * 升级名称（将名称中的数字递增）
 */
const getUpgradedName = (name: string): string => {
	return name.replace(/\d+/g, (match) => {
		const num = parseInt(match, 10);
		return (num + 1).toString();
	});
};

/**
 * 加载年级列表
 */
const loadData = async () => {
  loading.value = true;
  try {
    const params = {
      name: searchForm.name || undefined,
      year: searchForm.year ? parseInt(searchForm.year) : undefined,
      pageIndex: pagination.pageIndex,
      pageSize: pagination.pageSize,
    };
    const res = await getGradeList(params);
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
	searchForm.name = "";
	searchForm.year = "";
	handleSearch();
};

/**
 * 表格选中变化
 */
const handleSelectionChange = (rows: GradeItem[]) => {
	selectedIds.value = rows.map((row) => row.id);
	selectedGrades.value = rows;
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
	dialogTitle.value = "新增年级";
	Object.assign(formData, {
		id: undefined,
		name: "",
		year: undefined,
		sortNum: 0,
		remark: "",
	});
	dialogVisible.value = true;
};

/**
 * 编辑
 */
const handleEdit = (row: GradeItem) => {
	dialogTitle.value = "编辑年级";
	Object.assign(formData, {
		id: row.id,
		name: row.name,
		year: row.year,
		sortNum: row.sortNum || 0,
		remark: row.remark || "",
	});
	dialogVisible.value = true;
};

/**
 * 删除年级
 */
const handleDelete = (row: GradeItem) => {
	ElMessageBox.confirm(`确定删除年级 "${row.name}" 吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	}).then(async () => {
		try {
			const res = await deleteGrade([row.id]);
			if (res.data?.code === 10000) {
				ElMessage.success("删除成功");
				if (tableData.value.length === 1 && pagination.pageIndex > 1) pagination.pageIndex--;
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
 * 批量删除
 */
const handleBatchDelete = () => {
	ElMessageBox.confirm(`确定删除选中的 ${selectedIds.value.length} 个年级吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	}).then(async () => {
		try {
			const res = await deleteGrade(selectedIds.value);
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
 * 打开升级弹窗
 */
const handleUpgrade = () => {
	upgradeDialogVisible.value = true;
};

/**
 * 确认升级
 */
const confirmUpgrade = async () => {
	upgradeLoading.value = true;
	try {
		const res = await upgradeGrade(selectedIds.value);
		if (res.data?.code === 10000) {
			ElMessage.success("升级成功");
			upgradeDialogVisible.value = false;
			selectedIds.value = [];
			selectedGrades.value = [];
			loadData();
		} else {
			ElMessage.error(res.data?.message || "升级失败");
		}
	} catch (error) {
		ElMessage.error("升级失败");
	} finally {
		upgradeLoading.value = false;
	}
};

/**
 * 提交表单
 */
const handleSubmit = async () => {
	await formRef.value?.validate();
	submitLoading.value = true;
	try {
		const res = await saveGrade(formData);
		if (res.data?.code === 10000) {
			ElMessage.success("保存成功");
			dialogVisible.value = false;
			loadData();
		} else {
			ElMessage.error(res.data?.message || "保存失败");
		}
	} catch (error) {
		ElMessage.error("保存失败");
	} finally {
		submitLoading.value = false;
	}
};

// 初始化
onMounted(() => {
	console.log('年级管理页面 onMounted 执行了');
	loadColumnConfig();
	loadData();
});
</script>

<style scoped lang="scss">
.grade-page {
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

	.upgrade-tip {
		margin-top: 16px;
		padding: 12px;
		background: #f5f7fa;
		border-radius: 4px;

		ul {
			margin: 8px 0 0 20px;
			padding: 0;

			li {
				margin: 4px 0;
				color: #409eff;
			}
		}
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
