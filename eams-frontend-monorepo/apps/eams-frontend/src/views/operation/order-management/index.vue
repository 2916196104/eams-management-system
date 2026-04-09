<template>
	<div class="order-management">
		<!-- 页面标题 -->
		<div class="page-header">
			<h2>订单管理</h2>
		</div>

		<!-- 筛选区域 -->
		<div class="filter-bar">
			<el-form :inline="true" :model="searchForm" class="search-form">
				<el-form-item label="订单号：">
					<el-input v-model="searchForm.orderNo" placeholder="请输入" clearable style="width: 180px" />
				</el-form-item>
				<el-form-item label="分校：">
					<el-select v-model="searchForm.campus" placeholder="请选择" clearable style="width: 140px">
						<el-option label="HN校区" value="HN校区" />
						<el-option label="江苏南京校区-清北信奥" value="江苏南京校区-清北信奥" />
						<el-option label="四川职业技术学院龙风校区" value="四川职业技术学院龙风校区" />
					</el-select>
				</el-form-item>
				<el-form-item label="学生：">
					<el-input
						v-model="searchForm.studentName"
						placeholder="请选择"
						readonly
						style="width: 140px"
						@click="openStudentDialog"
					>
						<template #suffix>
							<el-icon><ArrowDown /></el-icon>
						</template>
					</el-input>
				</el-form-item>
				<el-form-item label="课程：">
					<el-input
						v-model="searchForm.courseName"
						placeholder="请选择"
						readonly
						style="width: 140px"
						@click="openCourseDialog"
					>
						<template #suffix>
							<el-icon><ArrowDown /></el-icon>
						</template>
					</el-input>
				</el-form-item>
				<el-form-item label="开始日期：">
					<el-date-picker
						v-model="searchForm.startDate"
						type="date"
						placeholder="请选择"
						value-format="YYYY-MM-DD"
						style="width: 140px"
					/>
				</el-form-item>
				<el-form-item label="结束日期：">
					<el-date-picker
						v-model="searchForm.endDate"
						type="date"
						placeholder="请选择"
						value-format="YYYY-MM-DD"
						style="width: 140px"
					/>
				</el-form-item>
				<el-form-item>
					<el-button type="primary" @click="handleSearch">搜索</el-button>
					<el-button @click="handleReset">重置</el-button>
					<el-button type="default" @click="toggleStatusFilter">
						{{ showStatusFilter ? "收起" : "展开" }}
					</el-button>
				</el-form-item>
			</el-form>

			<!-- 确认已付款按钮行 -->
			<div class="action-row">
				<el-button type="primary" @click="handleBatchConfirmPayment" :disabled="selectedOrders.length === 0">
					确认已付款
				</el-button>
			</div>

			<!-- 订单状态筛选（点击展开后显示） -->
			<div class="status-filter" v-if="showStatusFilter">
				<span class="filter-label">订单状态：</span>
				<el-checkbox-group v-model="searchForm.orderStatusList">
					<el-checkbox value="未支付">未支付</el-checkbox>
					<el-checkbox value="已付款">已付款</el-checkbox>
					<el-checkbox value="已评价">已评价</el-checkbox>
					<el-checkbox value="已取消">已取消</el-checkbox>
				</el-checkbox-group>
			</div>
		</div>

		<!-- 表格 -->
		<el-table
			:data="tableData"
			v-loading="loading"
			border
			stripe
			row-key="id"
			:expand-row-keys="expandedRows"
			@expand-change="handleExpandChange"
			@selection-change="handleSelectionChange"
		>
			<!-- 多选框列 -->
			<el-table-column type="selection" width="55" />

			<!-- 展开行：显示购买项详情 -->
			<el-table-column type="expand">
				<template #default="{ row }">
					<div class="expand-content">
						<div class="expand-section">
							<div class="expand-title">购买项</div>
							<el-table :data="row.orderItems" border size="small" style="width: 100%">
								<el-table-column label="类型" width="80">
									<template #default>课程</template>
								</el-table-column>
								<el-table-column prop="courseName" label="课程名称" min-width="200" />
								<el-table-column prop="price" label="单价" width="120">
									<template #default="{ row: item }">¥{{ item.price }}</template>
								</el-table-column>
								<el-table-column prop="quantity" label="数量" width="80" />
								<el-table-column prop="subtotal" label="小计" width="120">
									<template #default="{ row: item }">¥{{ item.subtotal }}</template>
								</el-table-column>
							</el-table>
						</div>
						<!-- 退款信息（如果有） -->
						<div v-if="row.refundItems && row.refundItems.length" class="expand-section">
							<div class="expand-title">退款项</div>
							<el-table :data="row.refundItems" border size="small" style="width: 100%">
								<el-table-column prop="amount" label="退款金额" width="120">
									<template #default="{ row: item }">¥{{ item.amount }}</template>
								</el-table-column>
								<el-table-column prop="reason" label="退款原因" min-width="200" />
								<el-table-column prop="status" label="退款状态" width="100">
									<template #default="{ row: item }">
										<el-tag :type="getRefundStatusType(item.status)">
											{{ getRefundStatusText(item.status) }}
										</el-tag>
									</template>
								</el-table-column>
							</el-table>
						</div>
					</div>
				</template>
			</el-table-column>

			<!-- 主表格列 -->
			<el-table-column prop="orderNo" label="订单号" min-width="200" />
			<el-table-column prop="studentName" label="学生" width="100" />
			<el-table-column prop="phone" label="电话" width="120" />
			<el-table-column prop="campus" label="分校" min-width="150" />
			<el-table-column prop="registrationMode" label="报名模式" width="100" />
			<el-table-column prop="orderAmount" label="订单金额" width="100">
				<template #default="{ row }">¥{{ row.orderAmount }}</template>
			</el-table-column>
			<el-table-column prop="paidAmount" label="付款金额" width="100">
				<template #default="{ row }">¥{{ row.paidAmount }}</template>
			</el-table-column>
			<el-table-column prop="orderRemark" label="订单备注" min-width="120" show-overflow-tooltip />
			<el-table-column prop="isRefund" label="是否退款" width="90">
				<template #default="{ row }">
					<el-tag :type="row.isRefund ? 'danger' : 'info'">
						{{ row.isRefund ? "是" : "否" }}
					</el-tag>
				</template>
			</el-table-column>
			<el-table-column prop="orderTime" label="订单时间" width="160" />
			<el-table-column prop="paymentTime" label="付款时间" width="160" />
			<el-table-column prop="orderStatus" label="订单状态" width="100">
				<template #default="{ row }">
					<el-tag :type="getOrderStatusType(row.orderStatus)">
						{{ row.orderStatus }}
					</el-tag>
				</template>
			</el-table-column>
			<el-table-column label="操作" fixed="right" width="180">
				<template #default="{ row }">
					<el-button link type="primary" @click="handleStudent(row)">学员</el-button>
					<el-button link type="primary" @click="handleRefund(row)">订单退款</el-button>
					<el-button
						link
						type="primary"
						@click="handleSingleConfirmPayment(row)"
						:disabled="row.orderStatus !== '未支付'"
					>
						确认已付款
					</el-button>
					<el-button link type="primary" @click="handleEvaluation(row)">订单评价</el-button>
				</template>
			</el-table-column>
		</el-table>

		<!-- 分页 -->
		<el-pagination
			v-model:current-page="pageNum"
			v-model:page-size="pageSize"
			:total="total"
			:page-sizes="[10, 20, 50, 100]"
			layout="total, sizes, prev, pager, next, jumper"
			@size-change="handleSizeChange"
			@current-change="handleCurrentChange"
		/>

		<!-- 学员选择弹窗 -->
		<el-dialog v-model="studentDialogVisible" title="选择学员" width="700px">
			<div class="dialog-search">
				<el-input
					v-model="studentSearchKeyword"
					placeholder="姓名或电话"
					clearable
					style="width: 250px"
					@keyup.enter="searchStudents"
				/>
				<el-button type="primary" @click="searchStudents">搜索</el-button>
			</div>
			<el-table :data="studentList" v-loading="studentLoading" border style="margin-top: 15px">
				<el-table-column prop="name" label="学员姓名" width="120" />
				<el-table-column prop="campus" label="分校" width="150" />
				<el-table-column prop="stage" label="阶段" width="100" />
				<el-table-column label="操作" width="80">
					<template #default="{ row }">
						<el-button link type="primary" @click="selectStudent(row)">选择</el-button>
					</template>
				</el-table-column>
			</el-table>
			<el-pagination
				v-model:current-page="studentPageNum"
				v-model:page-size="studentPageSize"
				:total="studentTotal"
				layout="prev, pager, next"
				@current-change="searchStudents"
				style="margin-top: 15px; justify-content: flex-end"
			/>
		</el-dialog>

		<!-- 课程选择弹窗 -->
		<el-dialog v-model="courseDialogVisible" title="选择课程" width="800px">
			<div class="dialog-search">
				<el-input
					v-model="courseSearchKeyword"
					placeholder="搜名称："
					clearable
					style="width: 250px"
					@keyup.enter="searchCourses"
				/>
				<el-button type="primary" @click="searchCourses">搜索</el-button>
			</div>
			<el-table :data="courseList" v-loading="courseLoading" border style="margin-top: 15px">
				<el-table-column prop="name" label="课程名称" min-width="180" />
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
			<el-pagination
				v-model:current-page="coursePageNum"
				v-model:page-size="coursePageSize"
				:total="courseTotal"
				layout="prev, pager, next"
				@current-change="searchCourses"
				style="margin-top: 15px; justify-content: flex-end"
			/>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { ArrowDown } from "@element-plus/icons-vue";

// ============ 搜索表单 ============
const searchForm = reactive({
	orderNo: "",
	campus: "",
	studentName: "",
	studentId: "",
	courseName: "",
	courseId: "",
	startDate: "",
	endDate: "",
	orderStatusList: [] as string[],
});

// 显示/隐藏状态筛选
const showStatusFilter = ref(false);

// 展开/收起状态
const expandedRows = ref<string[]>([]);

// 选中的订单
const selectedOrders = ref<any[]>([]);

// ============ 表格数据 ============
const tableData = ref<any[]>([]);
const loading = ref(false);
const pageNum = ref(1);
const pageSize = ref(20);
const total = ref(0);

// ============ 学员选择弹窗 ============
const studentDialogVisible = ref(false);
const studentSearchKeyword = ref("");
const studentList = ref<any[]>([]);
const studentLoading = ref(false);
const studentPageNum = ref(1);
const studentPageSize = ref(20);
const studentTotal = ref(0);

// ============ 课程选择弹窗 ============
const courseDialogVisible = ref(false);
const courseSearchKeyword = ref("");
const courseList = ref<any[]>([]);
const courseLoading = ref(false);
const coursePageNum = ref(1);
const coursePageSize = ref(20);
const courseTotal = ref(0);

// ============ 辅助函数 ============
const getOrderStatusType = (status: string): "info" | "success" | "warning" | "danger" => {
	const map: Record<string, "info" | "success" | "warning" | "danger"> = {
		未支付: "warning",
		已付款: "success",
		已评价: "info",
		已取消: "danger",
	};
	return map[status] || "info";
};

const getRefundStatusType = (status: string): "info" | "success" | "warning" | "danger" => {
	const map: Record<string, "info" | "success" | "warning" | "danger"> = {
		已申请: "warning",
		退款驳回: "danger",
		已退款: "success",
	};
	return map[status] || "info";
};

const getRefundStatusText = (status: string) => {
	const map: Record<string, string> = {
		已申请: "已申请退款",
		退款驳回: "退款驳回",
		已退款: "已退款",
	};
	return map[status] || status;
};

// ============ 模拟数据 ============
const mockOrders = [
	{
		id: "1",
		orderNo: "f0fac39821bb4fd6b5d692d7ce7eb98c",
		studentName: "1111",
		studentId: "s001",
		phone: "156****3771",
		campus: "HN校区",
		registrationMode: "在线报名",
		orderAmount: 99,
		paidAmount: 0,
		orderRemark: "",
		isRefund: false,
		orderTime: "2026-03-23 22:13",
		paymentTime: "",
		orderStatus: "未支付",
		orderItems: [{ courseName: "近世代数", price: 99, quantity: 1, subtotal: 99 }],
		refundItems: [],
	},
	{
		id: "2",
		orderNo: "8b7e49c6c289bf523b6bc0f2840feaaf",
		studentName: "李四",
		studentId: "s002",
		phone: "156****3771",
		campus: "HN校区",
		registrationMode: "在线报名",
		orderAmount: 11111,
		paidAmount: 0,
		orderRemark: "",
		isRefund: false,
		orderTime: "2026-03-22 15:25",
		paymentTime: "",
		orderStatus: "未支付",
		orderItems: [{ courseName: "傻瓜ghastly", price: 11111, quantity: 1, subtotal: 11111 }],
		refundItems: [],
	},
	{
		id: "3",
		orderNo: "1c0df1b493314416bd74e7074a33b9f6",
		studentName: "1111",
		studentId: "s001",
		phone: "156****3771",
		campus: "HN校区",
		registrationMode: "在线报名",
		orderAmount: 11111,
		paidAmount: 11111,
		orderRemark: "",
		isRefund: false,
		orderTime: "2026-03-19 20:57",
		paymentTime: "2026-03-19 21:29",
		orderStatus: "已付款",
		orderItems: [{ courseName: "傻瓜ghastly", price: 11111, quantity: 1, subtotal: 11111 }],
		refundItems: [],
	},
	{
		id: "4",
		orderNo: "db3f408d5bdebab1393893265f44b0b7",
		studentName: "1111",
		studentId: "s001",
		phone: "156****3771",
		campus: "HN校区",
		registrationMode: "在线报名",
		orderAmount: 99,
		paidAmount: 99,
		orderRemark: "",
		isRefund: false,
		orderTime: "2026-03-19 21:02",
		paymentTime: "2026-03-19 21:05",
		orderStatus: "已付款",
		orderItems: [{ courseName: "近世代数", price: 99, quantity: 1, subtotal: 99 }],
		refundItems: [],
	},
	{
		id: "5",
		orderNo: "49cc3ae4831c4f22a6dd47d001d45b96",
		studentName: "张洁",
		studentId: "s003",
		phone: "139****9008",
		campus: "江苏南京校区-清北信奥",
		registrationMode: "在线报名",
		orderAmount: 16200,
		paidAmount: 16200,
		orderRemark: "",
		isRefund: false,
		orderTime: "2026-03-18 18:59",
		paymentTime: "2026-03-19 14:04",
		orderStatus: "已付款",
		orderItems: [{ courseName: "C++编程基础及提高", price: 16200, quantity: 1, subtotal: 16200 }],
		refundItems: [],
	},
	{
		id: "6",
		orderNo: "6dcc67bb77ab468ca999f66379e70b72",
		studentName: "1111",
		studentId: "s001",
		phone: "156****3771",
		campus: "HN校区",
		registrationMode: "在线报名",
		orderAmount: 300,
		paidAmount: 300,
		orderRemark: "",
		isRefund: false,
		orderTime: "2026-01-17 11:13",
		paymentTime: "2026-01-21 10:04",
		orderStatus: "已评价",
		orderItems: [{ courseName: "跆拳道体验课", price: 300, quantity: 1, subtotal: 300 }],
		refundItems: [],
	},
];

// 模拟学员数据
const mockStudents = [
	{ id: "s001", name: "小米", campus: "HN校区", stage: "在学学员" },
	{ id: "s002", name: "321", campus: "HN校区", stage: "在学学员" },
	{ id: "s003", name: "张洁", campus: "江苏南京校区-清北信奥", stage: "在学学员" },
	{ id: "s004", name: "李四", campus: "HN校区", stage: "在学学员" },
];

// 模拟课程数据
const mockCourses = [
	{ id: "c001", name: "apex猎杀教程", lessonCount: 10, unitPrice: 10000, price: 100000, unitName: "期" },
	{ id: "c002", name: "古典语文", lessonCount: 30, unitPrice: 3.33, price: 100, unitName: "期" },
	{ id: "c003", name: "近世代数", lessonCount: 99, unitPrice: 1, price: 99, unitName: "次" },
	{ id: "c004", name: "傻瓜ghastly", lessonCount: 10, unitPrice: 1111.1, price: 11111, unitName: "期" },
	{ id: "c005", name: "C++编程基础及提高", lessonCount: 108, unitPrice: 150, price: 16200, unitName: "期" },
];

// ============ 获取订单列表 ============
const fetchData = async () => {
	loading.value = true;
	try {
		await new Promise((resolve) => setTimeout(resolve, 500));

		let data = [...mockOrders];

		if (searchForm.orderNo) {
			data = data.filter((item) => item.orderNo.includes(searchForm.orderNo));
		}
		if (searchForm.campus) {
			data = data.filter((item) => item.campus === searchForm.campus);
		}
		if (searchForm.studentId) {
			data = data.filter((item) => item.studentId === searchForm.studentId);
		}
		if (searchForm.courseId) {
			const selectedCourse = mockCourses.find((course) => course.id === searchForm.courseId);
			if (selectedCourse) {
				data = data.filter((item) => item.orderItems.some((orderItem) => orderItem.courseName === selectedCourse.name));
			}
		}
		if (searchForm.orderStatusList.length > 0) {
			data = data.filter((item) => searchForm.orderStatusList.includes(item.orderStatus));
		}
		if (searchForm.startDate) {
			data = data.filter((item) => item.orderTime >= searchForm.startDate);
		}
		if (searchForm.endDate) {
			data = data.filter((item) => item.orderTime <= `${searchForm.endDate} 23:59:59`);
		}

		total.value = data.length;
		const start = (pageNum.value - 1) * pageSize.value;
		const end = start + pageSize.value;
		tableData.value = data.slice(start, end);
	} catch (error) {
		console.error("获取数据失败", error);
		ElMessage.error("获取数据失败");
	} finally {
		loading.value = false;
	}
};

// ============ 表格选择变化 ============
const handleSelectionChange = (selection: any[]) => {
	selectedOrders.value = selection;
};

// ============ 批量确认已付款 ============
const handleBatchConfirmPayment = () => {
	const unpaidOrders = selectedOrders.value.filter((order) => order.orderStatus === "未支付");
	if (unpaidOrders.length === 0) {
		ElMessage.warning("请选择未支付的订单");
		return;
	}

	ElMessageBox.confirm(`确认将选中的 ${unpaidOrders.length} 个订单设为已付款吗？`, "批量确认", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(() => {
			unpaidOrders.forEach((order) => {
				order.orderStatus = "已付款";
				order.paidAmount = order.orderAmount;
				order.paymentTime = new Date().toLocaleString();
			});
			ElMessage.success(`成功确认 ${unpaidOrders.length} 个订单已付款`);
			fetchData();
		})
		.catch(() => {});
};

// ============ 单个确认已付款 ============
const handleSingleConfirmPayment = (row: any) => {
	ElMessageBox.confirm(`确认订单 ${row.orderNo} 已付款吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(() => {
			row.orderStatus = "已付款";
			row.paidAmount = row.orderAmount;
			row.paymentTime = new Date().toLocaleString();
			ElMessage.success("确认成功");
			fetchData();
		})
		.catch(() => {});
};

// ============ 显示/隐藏状态筛选 ============
const toggleStatusFilter = () => {
	showStatusFilter.value = !showStatusFilter.value;
};

// ============ 搜索学员 ============
const searchStudents = async () => {
	studentLoading.value = true;
	try {
		await new Promise((resolve) => setTimeout(resolve, 300));
		let data = [...mockStudents];
		if (studentSearchKeyword.value) {
			data = data.filter(
				(item) => item.name.includes(studentSearchKeyword.value) || item.id.includes(studentSearchKeyword.value),
			);
		}
		studentTotal.value = data.length;
		const start = (studentPageNum.value - 1) * studentPageSize.value;
		const end = start + studentPageSize.value;
		studentList.value = data.slice(start, end);
	} finally {
		studentLoading.value = false;
	}
};

const selectStudent = (student: any) => {
	searchForm.studentName = student.name;
	searchForm.studentId = student.id;
	studentDialogVisible.value = false;
	handleSearch();
};

// ============ 搜索课程 ============
const searchCourses = async () => {
	courseLoading.value = true;
	try {
		await new Promise((resolve) => setTimeout(resolve, 300));
		let data = [...mockCourses];
		if (courseSearchKeyword.value) {
			data = data.filter((item) => item.name.includes(courseSearchKeyword.value));
		}
		courseTotal.value = data.length;
		const start = (coursePageNum.value - 1) * coursePageSize.value;
		const end = start + coursePageSize.value;
		courseList.value = data.slice(start, end);
	} finally {
		courseLoading.value = false;
	}
};

const selectCourse = (course: any) => {
	searchForm.courseName = course.name;
	searchForm.courseId = course.id;
	courseDialogVisible.value = false;
	handleSearch();
};

// ============ 弹窗打开 ============
const openStudentDialog = () => {
	studentSearchKeyword.value = "";
	studentPageNum.value = 1;
	studentDialogVisible.value = true;
	searchStudents();
};

const openCourseDialog = () => {
	courseSearchKeyword.value = "";
	coursePageNum.value = 1;
	courseDialogVisible.value = true;
	searchCourses();
};

// ============ 其他操作 ============
const handleSearch = () => {
	pageNum.value = 1;
	fetchData();
};

const handleReset = () => {
	searchForm.orderNo = "";
	searchForm.campus = "";
	searchForm.studentName = "";
	searchForm.studentId = "";
	searchForm.courseName = "";
	searchForm.courseId = "";
	searchForm.startDate = "";
	searchForm.endDate = "";
	searchForm.orderStatusList = [];
	handleSearch();
};

const handleExpandChange = (row: any, expandedRowsList: any[]) => {
	// 由 el-table 自动处理
};

const handleStudent = (row: any) => {
	console.log("学员", row);
};

const handleRefund = (row: any) => {
	console.log("订单退款", row);
};

const handleEvaluation = (row: any) => {
	console.log("订单评价", row);
};

const handleSizeChange = (val: number) => {
	pageSize.value = val;
	fetchData();
};

const handleCurrentChange = (val: number) => {
	pageNum.value = val;
	fetchData();
};

onMounted(() => {
	fetchData();
});
</script>

<style scoped lang="scss">
.order-management {
	padding: 20px;

	.page-header {
		margin-bottom: 20px;

		h2 {
			margin: 0;
			font-size: 20px;
			font-weight: 500;
		}
	}

	.filter-bar {
		background: #fff;
		padding: 20px;
		border-radius: 8px;
		margin-bottom: 20px;

		.search-form {
			:deep(.el-form-item) {
				margin-bottom: 10px;
			}
		}

		.action-row {
			margin-top: 15px;
			padding-top: 15px;
			border-top: 1px solid #eee;
		}

		.status-filter {
			margin-top: 15px;
			padding-top: 15px;
			border-top: 1px solid #eee;

			.filter-label {
				margin-right: 15px;
				font-size: 14px;
				color: #606266;
			}

			:deep(.el-checkbox) {
				margin-right: 20px;
			}
		}
	}

	.expand-content {
		padding: 15px 20px;
		background: #f9f9f9;

		.expand-section {
			margin-bottom: 15px;

			&:last-child {
				margin-bottom: 0;
			}

			.expand-title {
				font-weight: 500;
				margin-bottom: 10px;
				font-size: 14px;
				color: #333;
			}
		}
	}

	.dialog-search {
		display: flex;
		gap: 12px;
	}
}
</style>
