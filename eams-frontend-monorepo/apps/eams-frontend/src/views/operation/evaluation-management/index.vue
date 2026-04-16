<template>
	<div class="evaluation-management">
		<!-- 搜索区域 -->
		<div class="search-section">
			<div class="search-row">
				<div class="search-item">
					<label>搜索学生:</label>
					<el-input v-model="searchStudent" placeholder="请选择学生" readonly @click="showStudentSelect = true">
						<template #suffix>
							<el-icon><ArrowDown /></el-icon>
						</template>
					</el-input>
				</div>
				<div class="search-item">
					<label>搜索课程:</label>
					<el-input v-model="searchCourse" placeholder="请选择课程" readonly @click="showCourseSelect = true">
						<template #suffix>
							<el-icon><ArrowDown /></el-icon>
						</template>
					</el-input>
				</div>
				<div class="search-item">
					<label>订单号:</label>
					<el-input v-model="orderNo" placeholder="请输入订单号" clearable />
				</div>
			</div>

			<!-- 操作按钮 -->
			<div class="action-buttons">
				<el-button type="primary" @click="handleSearch">搜索</el-button>
				<el-button @click="resetSearch">重置</el-button>
			</div>
		</div>

		<!-- 批量操作区域 -->
		<div class="batch-actions">
			<el-button type="primary" size="small" @click="handleBatchShow" :disabled="selectedRows.length === 0">
				批量显示
			</el-button>
			<el-button size="small" @click="handleBatchHide" :disabled="selectedRows.length === 0">批量隐藏</el-button>
			<el-button size="small" @click="handleBatchDelete" :disabled="selectedRows.length === 0">批量删除</el-button>
		</div>

		<!-- 数据表格 -->
		<el-table
			:data="evaluationList"
			v-loading="loading"
			border
			stripe
			style="width: 100%"
			@selection-change="handleSelectionChange"
		>
			<el-table-column type="selection" width="55" />
			<el-table-column prop="courseName" label="课程名称" min-width="180" />
			<el-table-column prop="evaluator" label="评价人" width="100" />
			<el-table-column prop="rating" label="评价分数" width="120">
				<template #default="{ row }">
					<el-rate v-model="row.rating" disabled show-score text-color="#ff9900" />
				</template>
			</el-table-column>
			<el-table-column prop="content" label="评价内容" min-width="200" show-overflow-tooltip />
			<el-table-column prop="orderId" label="订单号" min-width="280" />
			<el-table-column prop="createTime" label="评价时间" width="160" />
			<el-table-column prop="isVisible" label="是否显示" width="90">
				<template #default="{ row }">
					<el-tag :type="row.isVisible ? 'success' : 'info'">
						{{ row.isVisible ? "显示" : "隐藏" }}
					</el-tag>
				</template>
			</el-table-column>
			<el-table-column label="操作" width="100" fixed="right">
				<template #default="{ row }">
					<el-button size="small" :type="row.isVisible ? 'warning' : 'success'" @click="handleToggleVisibility(row)">
						{{ row.isVisible ? "隐藏" : "显示" }}
					</el-button>
				</template>
			</el-table-column>
		</el-table>

		<!-- 分页 -->
		<div class="pagination">
			<el-pagination
				v-model:current-page="currentPage"
				v-model:page-size="pageSize"
				:total="total"
				:page-sizes="[10, 20, 50, 100]"
				layout="total, sizes, prev, pager, next, jumper"
				@size-change="handleSizeChange"
				@current-change="handleCurrentChange"
			/>
		</div>

		<!-- 学生选择弹窗 -->
		<el-dialog v-model="showStudentSelect" title="搜索学员" width="700px">
			<div class="student-search">
				<el-input v-model="studentSearch" placeholder="姓名或电话" clearable @keyup.enter="searchStudents" />
				<el-button type="primary" @click="searchStudents">搜索</el-button>
			</div>
			<div class="student-list">
				<el-table :data="studentList" v-loading="studentLoading" border style="width: 100%">
					<el-table-column prop="name" label="学员姓名" width="120" />
					<el-table-column prop="branch" label="分校" min-width="150" />
					<el-table-column prop="stage" label="阶段" width="100" />
					<el-table-column prop="phone" label="电话" width="120" />
					<el-table-column label="操作" width="80">
						<template #default="{ row }">
							<el-button link type="primary" @click="selectStudent(row)">选择</el-button>
						</template>
					</el-table-column>
				</el-table>
			</div>
			<div class="dialog-footer">
				<el-pagination
					v-model:current-page="studentPage"
					v-model:page-size="studentPageSize"
					:total="studentTotal"
					layout="total, sizes, prev, pager, next, jumper"
					@size-change="handleStudentSizeChange"
					@current-change="handleStudentCurrentChange"
				/>
			</div>
		</el-dialog>

		<!-- 课程选择弹窗 -->
		<el-dialog v-model="showCourseSelect" title="搜索课程" width="800px">
			<div class="course-search">
				<el-input v-model="courseSearch" placeholder="课程名称" clearable @keyup.enter="searchCourses" />
				<el-button type="primary" @click="searchCourses">搜索</el-button>
			</div>
			<div class="course-list">
				<el-table :data="courseList" v-loading="courseLoading" border style="width: 100%">
					<el-table-column prop="name" label="课程名称" min-width="200" />
					<el-table-column prop="lessonCount" label="课时" width="80" />
					<el-table-column prop="unitPrice" label="单价" width="100">
						<template #default="{ row }">¥{{ row.unitPrice }}</template>
					</el-table-column>
					<el-table-column prop="price" label="总价" width="100">
						<template #default="{ row }">¥{{ row.price }}</template>
					</el-table-column>
					<el-table-column prop="unitName" label="单位" width="80" />
					<el-table-column label="操作" width="80">
						<template #default="{ row }">
							<el-button link type="primary" @click="selectCourse(row)">选择</el-button>
						</template>
					</el-table-column>
				</el-table>
			</div>
			<div class="dialog-footer">
				<el-pagination
					v-model:current-page="coursePage"
					v-model:page-size="coursePageSize"
					:total="courseTotal"
					layout="total, sizes, prev, pager, next, jumper"
					@size-change="handleCourseSizeChange"
					@current-change="handleCourseCurrentChange"
				/>
			</div>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { ArrowDown } from "@element-plus/icons-vue";

// ============ 搜索条件 ============
const searchStudent = ref("");
const searchStudentId = ref("");
const searchCourse = ref("");
const searchCourseId = ref("");
const orderNo = ref("");

// ============ 弹窗控制 ============
const showStudentSelect = ref(false);
const showCourseSelect = ref(false);

// ============ 学生搜索相关 ============
const studentSearch = ref("");
const studentList = ref<any[]>([]);
const studentLoading = ref(false);
const studentPage = ref(1);
const studentPageSize = ref(20);
const studentTotal = ref(0);

// ============ 课程搜索相关 ============
const courseSearch = ref("");
const courseList = ref<any[]>([]);
const courseLoading = ref(false);
const coursePage = ref(1);
const coursePageSize = ref(20);
const courseTotal = ref(0);

// ============ 表格数据 ============
const evaluationList = ref<any[]>([]);
const loading = ref(false);
const currentPage = ref(1);
const pageSize = ref(20);
const total = ref(0);

// 选中项
const selectedRows = ref<any[]>([]);

// ============ 模拟学生数据 ============
const mockStudents = [
	{ id: "s001", name: "小米", branch: "HN校区", stage: "在学学员", phone: "138****8000" },
	{ id: "s002", name: "321", branch: "HN校区", stage: "在学学员", phone: "138****8001" },
	{ id: "s003", name: "小楚", branch: "的撒", stage: "在学学员", phone: "138****8002" },
	{ id: "s004", name: "李四", branch: "HN校区", stage: "在学学员", phone: "138****8003" },
	{ id: "s005", name: "梧桐", branch: "ZXX校区", stage: "在学学员", phone: "138****8004" },
];

// ============ 模拟课程数据 ============
const mockCourses = [
	{ id: "c001", name: "apex猎杀教程", lessonCount: 10, unitPrice: 10000, price: 100000, unitName: "期" },
	{ id: "c002", name: "古典语文", lessonCount: 30, unitPrice: 3.33, price: 100, unitName: "期" },
	{ id: "c003", name: "近世代数", lessonCount: 99, unitPrice: 1, price: 99, unitName: "次" },
	{ id: "c004", name: "傻瓜ghastly", lessonCount: 10, unitPrice: 1111.1, price: 11111, unitName: "期" },
	{ id: "c005", name: "C++编程基础及提高", lessonCount: 108, unitPrice: 150, price: 16200, unitName: "期" },
];

// ============ 模拟评价数据 ============
const mockEvaluations = [
	{
		id: 1,
		courseName: "跆拳道体验课",
		courseId: "c001",
		evaluator: "小崔A",
		rating: 5,
		content: "默认好评",
		orderId: "75fc04588724b13a9db05583ec2f032",
		createTime: "2026-03-14 15:13",
		isVisible: false,
	},
	{
		id: 2,
		courseName: "数学",
		courseId: "c003",
		evaluator: "小崔A",
		rating: 5,
		content: "课程内容很丰富，老师讲解清晰",
		orderId: "75fc04588724b13a9db05583ec2f033",
		createTime: "2026-03-14 15:13",
		isVisible: true,
	},
	{
		id: 3,
		courseName: "测试",
		courseId: "c004",
		evaluator: "小崔A",
		rating: 4,
		content: "还不错，继续努力",
		orderId: "75fc04588724b13a9db05583ec2f034",
		createTime: "2026-03-14 15:13",
		isVisible: true,
	},
	{
		id: 4,
		courseName: "C++编程基础及提高",
		courseId: "c005",
		evaluator: "张洁",
		rating: 5,
		content: "非常好的课程，老师专业负责",
		orderId: "49cc3ae4831c4f22a6dd47d001d45b96",
		createTime: "2026-03-18 18:59",
		isVisible: true,
	},
];

// ============ 获取评价列表 ============
const fetchData = async () => {
	loading.value = true;
	try {
		await new Promise((resolve) => setTimeout(resolve, 500));

		let data = [...mockEvaluations];

		// 筛选
		if (searchStudentId.value) {
			// 模拟按学生筛选
			data = data.filter((item) => item.evaluator.includes(searchStudent.value));
		}
		if (searchCourseId.value) {
			data = data.filter((item) => item.courseId === searchCourseId.value);
		}
		if (orderNo.value) {
			data = data.filter((item) => item.orderId.includes(orderNo.value));
		}

		total.value = data.length;
		const start = (currentPage.value - 1) * pageSize.value;
		const end = start + pageSize.value;
		evaluationList.value = data.slice(start, end);
	} catch (error) {
		console.error("获取数据失败", error);
		ElMessage.error("获取数据失败");
	} finally {
		loading.value = false;
	}
};

// ============ 搜索学员 ============
const searchStudents = async () => {
	studentLoading.value = true;
	try {
		await new Promise((resolve) => setTimeout(resolve, 300));
		let data = [...mockStudents];
		if (studentSearch.value) {
			data = data.filter((item) => item.name.includes(studentSearch.value) || item.phone.includes(studentSearch.value));
		}
		studentTotal.value = data.length;
		const start = (studentPage.value - 1) * studentPageSize.value;
		const end = start + studentPageSize.value;
		studentList.value = data.slice(start, end);
	} finally {
		studentLoading.value = false;
	}
};

// ============ 选择学员 ============
const selectStudent = (student: any) => {
	searchStudent.value = student.name;
	searchStudentId.value = student.id;
	showStudentSelect.value = false;
	handleSearch();
};

// ============ 搜索课程 ============
const searchCourses = async () => {
	courseLoading.value = true;
	try {
		await new Promise((resolve) => setTimeout(resolve, 300));
		let data = [...mockCourses];
		if (courseSearch.value) {
			data = data.filter((item) => item.name.includes(courseSearch.value));
		}
		courseTotal.value = data.length;
		const start = (coursePage.value - 1) * coursePageSize.value;
		const end = start + coursePageSize.value;
		courseList.value = data.slice(start, end);
	} finally {
		courseLoading.value = false;
	}
};

// ============ 选择课程 ============
const selectCourse = (course: any) => {
	searchCourse.value = course.name;
	searchCourseId.value = course.id;
	showCourseSelect.value = false;
	handleSearch();
};

// ============ 搜索 ============
const handleSearch = () => {
	currentPage.value = 1;
	fetchData();
};

// ============ 重置搜索 ============
const resetSearch = () => {
	searchStudent.value = "";
	searchStudentId.value = "";
	searchCourse.value = "";
	searchCourseId.value = "";
	orderNo.value = "";
	handleSearch();
};

// ============ 批量显示 ============
const handleBatchShow = () => {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请选择要显示的评价");
		return;
	}
	selectedRows.value.forEach((row) => {
		row.isVisible = true;
	});
	ElMessage.success(`成功显示 ${selectedRows.value.length} 条评价`);
	fetchData();
};

// ============ 批量隐藏 ============
const handleBatchHide = () => {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请选择要隐藏的评价");
		return;
	}
	selectedRows.value.forEach((row) => {
		row.isVisible = false;
	});
	ElMessage.success(`成功隐藏 ${selectedRows.value.length} 条评价`);
	fetchData();
};

// ============ 批量删除 ============
const handleBatchDelete = () => {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请选择要删除的评价");
		return;
	}
	ElMessageBox.confirm(`确定删除选中的 ${selectedRows.value.length} 条评价吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(() => {
			ElMessage.success("删除成功");
			fetchData();
		})
		.catch(() => {});
};

// ============ 表格选择变化 ============
const handleSelectionChange = (selection: any[]) => {
	selectedRows.value = selection;
};

// ============ 切换显示/隐藏 ============
const handleToggleVisibility = (row: any) => {
	row.isVisible = !row.isVisible;
	ElMessage.success(`已${row.isVisible ? "显示" : "隐藏"}该评价`);
};

// ============ 分页 ============
const handleStudentSizeChange = (val: number) => {
	studentPageSize.value = val;
	searchStudents();
};

const handleStudentCurrentChange = (val: number) => {
	studentPage.value = val;
	searchStudents();
};

const handleCourseSizeChange = (val: number) => {
	coursePageSize.value = val;
	searchCourses();
};

const handleCourseCurrentChange = (val: number) => {
	coursePage.value = val;
	searchCourses();
};

const handleSizeChange = (val: number) => {
	pageSize.value = val;
	fetchData();
};

const handleCurrentChange = (val: number) => {
	currentPage.value = val;
	fetchData();
};

// ============ 初始化 ============
onMounted(() => {
	fetchData();
});
</script>

<style scoped lang="scss">
.evaluation-management {
	padding: 20px;
}

.search-section {
	margin-bottom: 20px;
	background-color: #fff;
	padding: 20px;
	border-radius: 8px;
}

.search-row {
	display: flex;
	flex-wrap: wrap;
	gap: 20px;
	margin-bottom: 20px;
}

.search-item {
	display: flex;
	flex-direction: column;
	min-width: 180px;

	label {
		margin-bottom: 8px;
		font-weight: 500;
		font-size: 14px;
		color: #606266;
	}
}

.action-buttons {
	display: flex;
	gap: 10px;
	margin-top: 10px;
}

.batch-actions {
	margin-bottom: 20px;
	display: flex;
	gap: 10px;
}

.pagination {
	margin-top: 20px;
	display: flex;
	justify-content: flex-end;
}

.student-search,
.course-search {
	display: flex;
	gap: 10px;
	margin-bottom: 15px;
}

.student-list,
.course-list {
	max-height: 400px;
	overflow-y: auto;
}

.dialog-footer {
	margin-top: 15px;
	display: flex;
	justify-content: flex-end;
}
</style>
