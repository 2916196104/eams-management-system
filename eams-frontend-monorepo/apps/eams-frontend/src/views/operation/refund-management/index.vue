<template>
	<div class="refund-management">
		<!-- 筛选区域 -->
		<div class="filter-section">
			<div class="filter-row">
				<div class="filter-item">
					<label>分校:</label>
					<el-input v-model="filters.branch" placeholder="请输入分校" clearable />
				</div>
				<div class="filter-item">
					<label>退款单号:</label>
					<el-input v-model="filters.refundNo" placeholder="请输入退款单号" clearable />
				</div>
				<div class="filter-item">
					<label>订单号:</label>
					<el-input v-model="filters.orderNo" placeholder="请输入订单号" clearable />
				</div>
				<div class="filter-item">
					<label>学生:</label>
					<el-input v-model="filters.student" placeholder="请选择学生" readonly @click="showStudentSelect = true">
						<template #suffix>
							<el-icon><ArrowDown /></el-icon>
						</template>
					</el-input>
				</div>
				<div class="filter-item">
					<label>原因类型:</label>
					<el-select v-model="filters.reasonType" placeholder="请选择原因类型" clearable>
						<el-option label="提前结课" value="early_completion" />
						<el-option label="教学质量问题" value="quality" />
						<el-option label="时间冲突" value="conflict" />
						<el-option label="其他原因" value="other" />
					</el-select>
				</div>
				<div class="filter-item">
					<label>开始日期:</label>
					<el-date-picker
						v-model="filters.startDate"
						type="date"
						placeholder="选择日期"
						value-format="YYYY-MM-DD"
						clearable
					/>
				</div>
				<div class="filter-item">
					<label>结束日期:</label>
					<el-date-picker
						v-model="filters.endDate"
						type="date"
						placeholder="选择日期"
						value-format="YYYY-MM-DD"
						clearable
					/>
				</div>
			</div>

			<!-- 订单状态筛选 -->
			<div class="status-filters">
				<div class="filter-item">
					<label>退款状态:</label>
					<div class="status-options">
						<el-checkbox :checked="filters.statuses.includes('applied')" @change="toggleStatus('applied')">
							已申请
						</el-checkbox>
						<el-checkbox
							:checked="filters.statuses.includes('pending_refund')"
							@change="toggleStatus('pending_refund')"
						>
							已审核待退款
						</el-checkbox>
						<el-checkbox :checked="filters.statuses.includes('completed')" @change="toggleStatus('completed')">
							退款完成
						</el-checkbox>
						<el-checkbox :checked="filters.statuses.includes('failed')" @change="toggleStatus('failed')">
							退款失败
						</el-checkbox>
						<el-checkbox :checked="filters.statuses.includes('rejected')" @change="toggleStatus('rejected')">
							退款驳回
						</el-checkbox>
					</div>
				</div>
			</div>

			<!-- 操作按钮 -->
			<div class="action-buttons">
				<el-button type="primary" @click="handleSearch">搜索</el-button>
				<el-button @click="resetFilters">重置</el-button>
			</div>
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

		<!-- 主要内容区域 -->
		<div class="main-content">
			<!-- 操作按钮 -->
			<div class="operation-buttons">
				<el-button type="primary" @click="handleRefundReview" :disabled="selectedRows.length === 0">退款审核</el-button>
				<el-button @click="handleReject" :disabled="selectedRows.length === 0">驳回申请</el-button>
				<el-button type="success" @click="handleExecuteRefund" :disabled="selectedRows.length === 0">
					执行退款
				</el-button>
			</div>

			<!-- 数据表格 -->
			<el-table :data="refundList" border stripe style="width: 100%" @selection-change="handleSelectionChange">
				<el-table-column type="selection" width="55" />
				<el-table-column prop="refundNo" label="退款单号" min-width="280" />
				<el-table-column prop="orderNo" label="订单号" min-width="260" />
				<el-table-column prop="studentName" label="学生" width="100" />
				<el-table-column prop="phone" label="电话" width="120" />
				<el-table-column prop="branch" label="分校" min-width="180" />
				<el-table-column prop="amount" label="退款金额" width="100">
					<template #default="{ row }">¥{{ row.amount }}</template>
				</el-table-column>
				<el-table-column prop="reasonType" label="原因类型" width="100" />
				<el-table-column prop="reason" label="退款原因" min-width="150" show-overflow-tooltip />
				<el-table-column prop="applyTime" label="申请时间" width="160" />
				<el-table-column prop="reviewTime" label="审核时间" width="160" />
				<el-table-column prop="reviewInfo" label="审核信息" width="100" />
				<el-table-column prop="executor" label="退款执行人" width="100" />
				<el-table-column prop="executeTime" label="退款执行时间" width="160" />
				<el-table-column prop="status" label="审核状态" width="100">
					<template #default="{ row }">
						<el-tag :type="getStatusType(row.status)">
							{{ row.statusText }}
						</el-tag>
					</template>
				</el-table-column>
				<el-table-column label="操作" width="100" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" size="small" @click="handleEditRefund(row)">修改退款额</el-button>
					</template>
				</el-table-column>
			</el-table>

			<!-- 分页 -->
			<div class="pagination">
				<el-pagination
					v-model:current-page="currentPage"
					v-model:page-size="pageSize"
					:total="total"
					:layout="'total, sizes, prev, pager, next, jumper'"
					:page-sizes="[10, 20, 50, 100]"
					@size-change="handleSizeChange"
					@current-change="handleCurrentChange"
				/>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { ArrowDown } from "@element-plus/icons-vue";

// ============ 筛选条件 ============
const filters = reactive({
	branch: "",
	refundNo: "",
	orderNo: "",
	student: "",
	studentId: "",
	reasonType: "",
	startDate: "",
	endDate: "",
	statuses: [] as string[],
});

// ============ 学生选择相关 ============
const showStudentSelect = ref(false);
const studentSearch = ref("");
const studentList = ref<any[]>([]);
const studentLoading = ref(false);
const studentPage = ref(1);
const studentPageSize = ref(20);
const studentTotal = ref(0);

// ============ 表格数据 ============
const refundList = ref<any[]>([]);
const currentPage = ref(1);
const pageSize = ref(20);
const total = ref(0);
const loading = ref(false);

// 选中项
const selectedRows = ref<any[]>([]);

// ============ 模拟学生数据 ============
const mockStudents = [
	{ id: "s001", name: "小米", branch: "HN校区", stage: "在学学员", phone: "138****8000" },
	{ id: "s002", name: "321", branch: "HN校区", stage: "在学学员", phone: "138****8001" },
	{ id: "s003", name: "水电费", branch: "四川职业技术学院龙凤校区", stage: "在学学员", phone: "156****3771" },
	{ id: "s004", name: "大盆友", branch: "四川职业技术学院龙凤校区", stage: "在学学员", phone: "156****3772" },
	{ id: "s005", name: "张洁", branch: "江苏南京校区-清北信奥", stage: "在学学员", phone: "139****9008" },
];

// ============ 模拟退款数据 ============
const mockRefundList = [
	{
		id: 1,
		refundNo: "619c9a5e68574b5e89eb3ae6b22e2114",
		orderNo: "e6112e3862074f8ca9eb059ac7226804",
		studentName: "水电费",
		studentId: "s003",
		phone: "156****3771",
		branch: "四川职业技术学院龙凤校区",
		amount: 18888,
		reasonType: "提前结课",
		reason: "123",
		applyTime: "2026-02-05 11:08",
		reviewTime: "2026-01-23 15:06",
		reviewInfo: "提前结课",
		executor: "",
		executeTime: "",
		status: "applied",
		statusText: "已申请",
	},
	{
		id: 2,
		refundNo: "b0b814acb2d34480990e8944728417a9",
		orderNo: "05e0580b8e8424fb10a72b8759fe0a5",
		studentName: "大盆友",
		studentId: "s004",
		phone: "156****3772",
		branch: "四川职业技术学院龙凤校区",
		amount: 1500,
		reasonType: "提前结课",
		reason: "提前结课",
		applyTime: "2025-11-11 23:45",
		reviewTime: "2026-01-23 15:06",
		reviewInfo: "提前结课",
		executor: "",
		executeTime: "",
		status: "rejected",
		statusText: "退款驳回",
	},
	{
		id: 3,
		refundNo: "a1b2c3d4e5f67890abcdef1234567890",
		orderNo: "1c0df1b493314416bd74e7074a33b9f6",
		studentName: "1111",
		studentId: "s001",
		phone: "156****3771",
		branch: "HN校区",
		amount: 11111,
		reasonType: "提前结课",
		reason: "课程不合适",
		applyTime: "2026-02-10 14:30",
		reviewTime: "",
		reviewInfo: "",
		executor: "",
		executeTime: "",
		status: "pending_refund",
		statusText: "已审核待退款",
	},
	{
		id: 4,
		refundNo: "f9e8d7c6b5a4321098765432109876",
		orderNo: "49cc3ae4831c4f22a6dd47d001d45b96",
		studentName: "张洁",
		studentId: "s005",
		phone: "139****9008",
		branch: "江苏南京校区-清北信奥",
		amount: 16200,
		reasonType: "教学质量问题",
		reason: "老师教学方式不适应",
		applyTime: "2026-02-15 09:20",
		reviewTime: "2026-02-16 10:30",
		reviewInfo: "同意退款",
		executor: "管理员",
		executeTime: "2026-02-17 14:00",
		status: "completed",
		statusText: "退款完成",
	},
];

// ============ 辅助函数 ============
const getStatusType = (status: string): "info" | "success" | "warning" | "danger" => {
	const map: Record<string, "info" | "success" | "warning" | "danger"> = {
		applied: "warning",
		pending_refund: "info",
		completed: "success",
		failed: "danger",
		rejected: "danger",
	};
	return map[status] || "info";
};

// ============ 获取退款列表 ============
const fetchData = async () => {
	loading.value = true;
	try {
		await new Promise((resolve) => setTimeout(resolve, 500));

		let data = [...mockRefundList];

		// 筛选
		if (filters.branch) {
			data = data.filter((item) => item.branch.includes(filters.branch));
		}
		if (filters.refundNo) {
			data = data.filter((item) => item.refundNo.includes(filters.refundNo));
		}
		if (filters.orderNo) {
			data = data.filter((item) => item.orderNo.includes(filters.orderNo));
		}
		if (filters.studentId) {
			data = data.filter((item) => item.studentId === filters.studentId);
		}
		if (filters.reasonType) {
			data = data.filter((item) => item.reasonType === filters.reasonType);
		}
		if (filters.statuses.length > 0) {
			data = data.filter((item) => filters.statuses.includes(item.status));
		}
		if (filters.startDate) {
			data = data.filter((item) => item.applyTime >= filters.startDate);
		}
		if (filters.endDate) {
			data = data.filter((item) => item.applyTime <= `${filters.endDate} 23:59:59`);
		}

		total.value = data.length;
		const start = (currentPage.value - 1) * pageSize.value;
		const end = start + pageSize.value;
		refundList.value = data.slice(start, end);
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
	filters.student = student.name;
	filters.studentId = student.id;
	showStudentSelect.value = false;
	handleSearch();
};

// ============ 搜索 ============
const handleSearch = () => {
	currentPage.value = 1;
	fetchData();
};

// ============ 重置筛选 ============
const resetFilters = () => {
	filters.branch = "";
	filters.refundNo = "";
	filters.orderNo = "";
	filters.student = "";
	filters.studentId = "";
	filters.reasonType = "";
	filters.startDate = "";
	filters.endDate = "";
	filters.statuses = [];
	handleSearch();
};

// ============ 切换状态筛选 ============
const toggleStatus = (status: string) => {
	if (filters.statuses.includes(status)) {
		filters.statuses = filters.statuses.filter((s) => s !== status);
	} else {
		filters.statuses.push(status);
	}
	handleSearch();
};

// ============ 表格选择变化 ============
const handleSelectionChange = (selection: any[]) => {
	selectedRows.value = selection;
};

// ============ 退款审核 ============
const handleRefundReview = () => {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请选择要审核的退款申请");
		return;
	}
	console.log("退款审核:", selectedRows.value);
	ElMessage.info("退款审核功能开发中");
};

// ============ 驳回申请 ============
const handleReject = () => {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请选择要驳回的退款申请");
		return;
	}
	ElMessageBox.confirm(`确定驳回选中的 ${selectedRows.value.length} 个退款申请吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(() => {
			ElMessage.success("驳回成功");
			fetchData();
		})
		.catch(() => {});
};

// ============ 执行退款 ============
const handleExecuteRefund = () => {
	if (selectedRows.value.length === 0) {
		ElMessage.warning("请选择要执行退款的申请");
		return;
	}
	ElMessageBox.confirm(`确定执行选中的 ${selectedRows.value.length} 个退款吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(() => {
			ElMessage.success("退款执行成功");
			fetchData();
		})
		.catch(() => {});
};

// ============ 修改退款额 ============
const handleEditRefund = (row: any) => {
	console.log("修改退款额:", row);
	ElMessage.info("修改退款额功能开发中");
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
.refund-management {
	padding: 20px;
}

.filter-section {
	margin-bottom: 20px;
	background-color: #fff;
	padding: 20px;
	border-radius: 8px;
}

.filter-row {
	display: flex;
	flex-wrap: wrap;
	gap: 20px;
	margin-bottom: 20px;
}

.filter-item {
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

.status-filters {
	margin-bottom: 20px;

	.filter-item {
		flex-direction: row;
		align-items: center;
		gap: 15px;

		label {
			margin-bottom: 0;
		}
	}
}

.status-options {
	display: flex;
	flex-wrap: wrap;
	gap: 20px;
}

.action-buttons {
	display: flex;
	gap: 10px;
	margin-top: 10px;
}

.main-content {
	background-color: #fff;
	padding: 20px;
	border-radius: 8px;
}

.operation-buttons {
	margin-bottom: 20px;
	display: flex;
	gap: 10px;
}

.pagination {
	margin-top: 20px;
	display: flex;
	justify-content: flex-end;
}

.student-search {
	display: flex;
	gap: 10px;
	margin-bottom: 15px;
}

.student-list {
	max-height: 400px;
	overflow-y: auto;
}

.dialog-footer {
	margin-top: 15px;
	display: flex;
	justify-content: flex-end;
}
</style>
