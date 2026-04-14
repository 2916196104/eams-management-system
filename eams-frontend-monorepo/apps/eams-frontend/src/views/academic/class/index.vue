<template>
	<div class="class-page">
		<!-- 搜索表单 -->
		<el-card class="search-card">
			<el-form :inline="true" :model="searchForm" label-width="80px">
				<el-form-item label="班级名称">
					<el-input v-model="searchForm.className" placeholder="请输入班级名称" clearable style="width: 180px" />
				</el-form-item>
				<el-form-item label="选择分校">
					<el-select v-model="searchForm.branch" placeholder="请选择分校" clearable style="width: 150px">
						<el-option label="HN校区" value="HN校区" />
						<el-option label="四川职业技术学院龙岗校区" value="四川职业技术学院龙岗校区" />
					</el-select>
				</el-form-item>
				<el-form-item label="默认课程">
					<el-select v-model="searchForm.courseId" placeholder="请选择课程" clearable filterable style="width: 180px">
						<el-option v-for="item in courseOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="教室">
					<el-select
						v-model="searchForm.classroomId"
						placeholder="请选择教室"
						clearable
						filterable
						style="width: 150px"
					>
						<el-option v-for="item in classroomOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="班主任">
					<el-select
						v-model="searchForm.teacherId"
						placeholder="请选择班主任"
						clearable
						filterable
						style="width: 150px"
					>
						<el-option v-for="item in teacherOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="年级">
					<el-select v-model="searchForm.gradeId" placeholder="请选择年级" clearable filterable style="width: 150px">
						<el-option v-for="item in gradeOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="班级状态">
					<el-select v-model="searchForm.beOver" placeholder="请选择状态" clearable style="width: 120px">
						<el-option label="进行中" :value="false" />
						<el-option label="已结业" :value="true" />
					</el-select>
				</el-form-item>
				<el-form-item>
					<el-button type="primary" @click="handleSearch">查询</el-button>
					<el-button @click="handleReset">重置</el-button>
				</el-form-item>
			</el-form>
		</el-card>

		<!-- 操作按钮 -->
		<el-card class="action-card">
			<el-button type="primary" @click="handleAdd">新增班级</el-button>
			<el-button type="danger" :disabled="selectedIds.length === 0" @click="handleBatchDelete">批量删除</el-button>
			<el-button type="warning" :disabled="selectedIds.length === 0" @click="handleBatchOver">批量结业</el-button>
		</el-card>

		<!-- 表格 -->
		<el-card>
			<el-table :data="tableData" v-loading="loading" border stripe @selection-change="handleSelectionChange">
				<el-table-column type="selection" width="55" />
				<el-table-column prop="name" label="班级名称" min-width="150" />
				<el-table-column prop="courseName" label="默认课程" min-width="150" />
				<el-table-column prop="classroom" label="教室" width="100" />
				<el-table-column prop="teacherName" label="班主任" width="100" />
				<el-table-column prop="plannedStudentCount" label="预招数" width="80" />
				<el-table-column prop="studentCount" label="学生数" width="80" />
				<el-table-column prop="plannedLessonCount" label="计划课次" width="100" />
				<el-table-column prop="startDate" label="开班时间" width="120" />
				<el-table-column prop="endDate" label="结业时间" width="120" />
				<el-table-column label="状态" width="100">
					<template #default="{ row }">
						<el-tag :type="row.beOver ? 'info' : 'success'">
							{{ row.beOver ? "已结业" : "进行中" }}
						</el-tag>
					</template>
				</el-table-column>
				<el-table-column label="操作" width="150" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="handleEdit(row)">编辑</el-button>
						<el-button v-if="!row.beOver" link type="warning" @click="handleOver(row)">结业</el-button>
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
			<el-form ref="formRef" :model="formData" :rules="formRules" label-width="100px">
				<el-form-item label="班级名称" prop="name">
					<el-input v-model="formData.name" placeholder="请输入班级名称" />
				</el-form-item>
				<el-form-item label="课程" prop="courseId">
					<el-select v-model="formData.courseId" placeholder="请选择课程" filterable style="width: 100%">
						<el-option v-for="item in courseOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="教室" prop="classroomId">
					<el-select v-model="formData.classroomId" placeholder="请选择教室" filterable style="width: 100%">
						<el-option v-for="item in classroomOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="班主任" prop="teacherId">
					<el-select v-model="formData.teacherId" placeholder="请选择班主任" filterable style="width: 100%">
						<el-option v-for="item in teacherOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="预招人数" prop="plannedStudentCount">
					<el-input-number v-model="formData.plannedStudentCount" :min="1" style="width: 100%" />
				</el-form-item>
				<el-form-item label="计划课次" prop="plannedLessonCount">
					<el-input-number v-model="formData.plannedLessonCount" :min="0" style="width: 100%" />
				</el-form-item>
				<el-form-item label="开班时间" prop="startDate">
					<el-date-picker
						v-model="formData.startDate"
						type="date"
						placeholder="选择日期"
						value-format="YYYY-MM-DD"
						style="width: 100%"
					/>
				</el-form-item>
				<el-form-item label="结业时间" prop="endDate">
					<el-date-picker
						v-model="formData.endDate"
						type="date"
						placeholder="选择日期"
						value-format="YYYY-MM-DD"
						style="width: 100%"
					/>
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
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import {
	getClassList,
	saveClass,
	deleteClass,
	overClass,
	getClassOptions,
	type ClassItem,
	type ClassListParams,
	type SaveClassParams,
} from "@/apis/academic/class";
const gradeOptions = ref<Array<{ id: number; name: string }>>([]);

// 搜索表单
const searchForm = reactive({
	className: "",
	branch: "",
	courseId: undefined as number | undefined,
	classroomId: undefined as number | undefined,
	teacherId: undefined as number | undefined,
	gradeId: undefined as number | undefined,
	beOver: undefined as boolean | undefined,
	courseName: "",
	teacherName: "",
});

// 分页
const pagination = reactive({
	pageIndex: 1,
	pageSize: 20,
	total: 0,
});

// 表格数据
const tableData = ref<ClassItem[]>([]);
const loading = ref(false);
const selectedIds = ref<number[]>([]);

// 弹窗
const dialogVisible = ref(false);
const dialogTitle = ref("");
const submitLoading = ref(false);
const formRef = ref();

// 表单数据
const formData = reactive<SaveClassParams>({
	name: "",
	courseId: 0,
	classroomId: 0,
	teacherId: 0,
	plannedStudentCount: 1,
	plannedLessonCount: 0,
	startDate: "",
	endDate: "",
	remark: "",
});

// 表单校验
const formRules = {
	name: [{ required: true, message: "请输入班级名称", trigger: "blur" }],
	courseId: [{ required: true, message: "请选择课程", trigger: "change" }],
	teacherId: [{ required: true, message: "请选择班主任", trigger: "change" }],
	startDate: [{ required: true, message: "请选择开班时间", trigger: "change" }],
};

// 下拉选项
const courseOptions = ref<Array<{ id: number; name: string }>>([]);
const classroomOptions = ref<Array<{ id: number; name: string }>>([]);
const teacherOptions = ref<Array<{ id: number; name: string }>>([]);

//加载班级列表
const loadData = async () => {
  loading.value = true;
  try {
    const params: ClassListParams = {
      pageIndex: pagination.pageIndex,
      pageSize: pagination.pageSize,
      className: searchForm.className || undefined,
      courseName: searchForm.courseName || undefined,
      teacherName: searchForm.teacherName || undefined,
    };
    const res = await getClassList(params);
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
	searchForm.branch = "";
	searchForm.courseId = undefined;
	searchForm.classroomId = undefined;
	searchForm.teacherId = undefined;
	searchForm.gradeId = undefined;
	searchForm.beOver = undefined;
	handleSearch();
};

/**
 * 表格选中变化
 */
const handleSelectionChange = (rows: ClassItem[]) => {
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
	dialogTitle.value = "新增班级";
	Object.assign(formData, {
		id: undefined,
		name: "",
		courseId: 0,
		classroomId: 0,
		teacherId: 0,
		plannedStudentCount: 1,
		plannedLessonCount: 0,
		startDate: "",
		endDate: "",
		remark: "",
	});
	dialogVisible.value = true;
};

/**
 * 编辑
 */
const handleEdit = (row: ClassItem) => {
	dialogTitle.value = "编辑班级";
	Object.assign(formData, {
		id: row.id,
		name: row.name,
		courseId: row.courseId,
		classroomId: row.classroomId,
		teacherId: row.teacherId,
		plannedStudentCount: row.plannedStudentCount,
		plannedLessonCount: row.plannedLessonCount,
		startDate: row.startDate,
		endDate: row.endDate || "",
		remark: row.remark || "",
	});
	dialogVisible.value = true;
};

/**
 * 删除班级
 */
const handleDelete = (row: ClassItem) => {
	ElMessageBox.confirm(`确定删除班级 "${row.name}" 吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	}).then(async () => {
		try {
			const res = await deleteClass([row.id]);
			if (res.data?.code === 10000) {
				ElMessage.success("删除成功");
				if (tableData.value.length === 1 && pagination.pageIndex > 1) pagination.pageIndex--;
				loadData();
			} else {
				ElMessage.error(res.data?.message || "删除失败");
			}
		} catch {
			ElMessage.error("删除失败");
		}
	});
};

/**
 * 批量删除
 */
const handleBatchDelete = () => {
	ElMessageBox.confirm(`确定删除选中的 ${selectedIds.value.length} 个班级吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	}).then(async () => {
		try {
			const res = await deleteClass(selectedIds.value);
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
 * 单个结业
 */
const handleOver = (row: ClassItem) => {
	ElMessageBox.confirm(`确定将班级 "${row.name}" 结业吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	}).then(async () => {
		try {
			const res = await overClass([row.id]);
			if (res.data?.code === 10000) {
				ElMessage.success("结业成功");
				loadData();
			} else {
				ElMessage.error(res.data?.message || "结业失败");
			}
		} catch (error) {
			ElMessage.error("操作失败");
		}
	});
};

/**
 * 批量结业
 */
const handleBatchOver = () => {
	ElMessageBox.confirm(`确定将选中的 ${selectedIds.value.length} 个班级结业吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	}).then(async () => {
		try {
			const res = await overClass(selectedIds.value);
			if (res.data?.code === 10000) {
				ElMessage.success("结业成功");
				selectedIds.value = [];
				loadData();
			} else {
				ElMessage.error(res.data?.message || "结业失败");
			}
		} catch (error) {
			ElMessage.error("操作失败");
		}
	});
};

/**
 * 提交表单
 */
const handleSubmit = async () => {
	await formRef.value?.validate();
	submitLoading.value = true;
	try {
		const res = await saveClass(formData);
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

/**
 * 加载下拉选项
 */
// TODO: 从后端获取课程、教室、班主任列表
// 这里先用 Mock 数据
const loadOptions = async () => {
	// 课程选项
	courseOptions.value = [
		{ id: 1, name: "近世代数" },
		{ id: 2, name: "C语言" },
	];
	// 教室选项
	classroomOptions.value = [
		{ id: 1, name: "101教室" },
		{ id: 2, name: "102教室" },
	];
	// 班主任选项
	teacherOptions.value = [
		{ id: 1, name: "王伟大" },
		{ id: 2, name: "李三" },
	];
	// 年级选项
	gradeOptions.value = [
		{ id: 1, name: "一年级" },
		{ id: 2, name: "二年级" },
		{ id: 3, name: "三年级" },
	];
};

onMounted(() => {
	loadData();
	loadOptions();
});
</script>

<style scoped lang="scss">
.class-page {
	padding: 20px;

	.search-card,
	.action-card {
		margin-bottom: 20px;
	}

	.pagination-wrapper {
		margin-top: 20px;
		display: flex;
		justify-content: flex-end;
	}
}
</style>
