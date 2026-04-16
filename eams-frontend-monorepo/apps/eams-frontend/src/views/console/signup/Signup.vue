<template>
	<div class="page-container">
		<!-- 搜索栏 -->
		<div class="search-bar">
			<el-input
				v-model="query.studentName"
				placeholder="请输入学员姓名"
				clearable
				@keyup.enter="loadData"
				style="width: 200px"
			/>
			<el-date-picker
				v-model="query.startDateBegin"
				type="date"
				placeholder="开始日期"
				style="width: 150px"
				clearable
			/>
			<el-date-picker v-model="query.startDateEnd" type="date" placeholder="结束日期" style="width: 150px" clearable />
			<el-select v-model="query.courseId" placeholder="课程" style="width: 150px" clearable>
				<el-option v-for="item in courseList" :key="item.id" :label="item.name" :value="item.id" />
			</el-select>
			<el-button type="primary" @click="handleSearch">搜索</el-button>
		</div>

		<!-- 工具栏 -->
		<div class="toolbar">
			<div class="right">
				<el-button @click="loadData">刷新</el-button>
				<el-button @click="handlePrint">打印</el-button>
			</div>
		</div>

		<!-- 表格 -->
		<el-table :data="tableData" border style="width: 100%" v-loading="loading">
			<el-table-column type="index" label="序号" width="60" />
			<el-table-column prop="createTime" label="添加时间" width="160" />
			<el-table-column prop="studentName" label="学生" width="120" />
			<el-table-column prop="courseName" label="课程" width="120" />
			<el-table-column prop="subjectName" label="科目" width="120" />
			<el-table-column prop="buyLessonCount" label="购买课次" width="100" />
			<el-table-column prop="contractAmount" label="合约金额" width="120" />
			<el-table-column prop="paidAmount" label="实付金额" width="120" />
			<el-table-column prop="arrearsAmount" label="欠费" width="100" />
			<el-table-column prop="startDate" label="开始日期" width="140" />
			<el-table-column prop="validUntil" label="有效期至" width="140" />
			<el-table-column prop="refundAmount" label="退费金额" width="120" />
			<el-table-column prop="refundCount" label="退课次数" width="100" />
			<el-table-column prop="refundNote" label="退费说明" width="200" />
			<el-table-column prop="refundStatus" label="退费状态" width="120" />
		</el-table>

		<!-- 分页 -->
		<div class="pagination">
			<el-pagination
				v-model:current-page="query.pageNum"
				v-model:page-size="query.pageSize"
				:total="total"
				layout="total, sizes, prev, pager, next, jumper"
				@current-change="loadData"
				@size-change="loadData"
			/>
		</div>
	</div>
</template>

<script setup>
import { ref, onMounted } from "vue";
import { useEnrollmentStore } from "@/stores/console";

const enrollmentStore = useEnrollmentStore();
const loading = ref(false);
const query = ref({
	studentName: "",
	startDateBegin: "",
	startDateEnd: "",
	courseId: "",
	pageNum: 1,
	pageSize: 10,
});
const tableData = ref([]);
const total = ref(0);
const courseList = ref([]); // 可通过接口获取课程列表

onMounted(async () => {
	await loadData();
	// 假设 store 提供总条数
	total.value = enrollmentStore.total;
});

const loadData = async () => {
	loading.value = true;
	try {
		await enrollmentStore.fetchList(query.value);
		tableData.value = enrollmentStore.tableData.map((item) => ({
			createTime: item.enrollmentTime,
			studentName: item.studentName,
			courseName: item.courseName,
			subjectName: item.subjectName,
			buyLessonCount: item.purchaseLessonCount,
			contractAmount: item.contractAmount,
			paidAmount: item.paidAmount,
			arrearsAmount: item.arrearsAmount,
			startDate: item.startDate,
			validUntil: item.expireDate,
			refundAmount: item.refundTotalAmount,
			refundCount: item.refundTotalCount,
			refundNote: item.refundRemark,
			refundStatus: item.refundTotalCount > 0 ? "有退费" : "无退费",
		}));
		total.value = enrollmentStore.total;
	} finally {
		loading.value = false;
	}
};

const handleSearch = () => {
	query.value.pageNum = 1;
	loadData();
};

const handlePrint = () => {
	window.print();
};
</script>

<style scoped>
.page-container {
	padding: 15px;
	background: #fff;
}

.search-bar {
	margin-bottom: 10px;
	display: flex;
	gap: 10px;
	align-items: center;
}

.toolbar {
	display: flex;
	justify-content: space-between;
	margin-bottom: 10px;
}

.pagination {
	margin-top: 15px;
	display: flex;
	justify-content: flex-end;
}
</style>
