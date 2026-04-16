<template>
	<div class="page-container">
		<!-- 搜索栏 -->
		<div class="search-bar">
			<el-input v-model="query.name" placeholder="请输入学员姓名" clearable style="width: 200px" />
			<el-date-picker v-model="query.startDate" type="date" placeholder="开始日期" style="width: 150px" />
			<el-date-picker v-model="query.endDate" type="date" placeholder="结束日期" style="width: 150px" />
			<el-select v-model="query.status" placeholder="审核状态" style="width: 150px" clearable>
				<el-option label="待审核" value="pending" />
				<el-option label="审核通过" value="approved" />
				<el-option label="已驳回" value="rejected" />
			</el-select>
			<el-button type="primary" @click="handleSearch">搜索</el-button>
		</div>

		<!-- 工具栏 -->
		<div class="toolbar">
			<div class="left">
				<el-button type="primary" @click="handleAdd">添加请款</el-button>
			</div>
			<div class="right">
				<el-button @click="loadData">刷新</el-button>
				<el-button @click="handlePrint">打印</el-button>
			</div>
		</div>

		<!-- 表格 -->
		<el-table :data="tableData" border style="width: 100%" v-loading="loading">
			<el-table-column type="index" label="序号" width="60" />
			<el-table-column prop="project" label="请款项目" width="150" />
			<el-table-column prop="type" label="款项类型" width="120" />
			<el-table-column prop="applicant" label="申请人" width="120" />
			<el-table-column prop="receiver" label="收款人" width="120" />
			<el-table-column prop="amount" label="请款金额" width="120" />
			<el-table-column prop="applyTime" label="申请时间" width="180" />
			<el-table-column prop="account" label="收款账号" width="180" />
			<el-table-column prop="remark" label="请款说明" width="200" />
			<el-table-column prop="statusText" label="审核状态" width="120" />
			<el-table-column prop="auditInfo" label="审核信息" width="200" />

			<!-- 操作列 -->
			<el-table-column label="操作" width="100" fixed="right">
				<template #default="scope">
					<el-button text size="small" type="primary" @click="handleView(scope.row)">查看</el-button>
				</template>
			</el-table-column>
		</el-table>

		<!-- 分页 -->
		<div class="pagination">
			<el-pagination
				v-model:current-page="query.pageIndex"
				v-model:page-size="query.pageSize"
				:total="total"
				layout="total, sizes, prev, pager, next, jumper"
				@current-change="loadData"
				@size-change="loadData"
			/>
		</div>

		<payment-form ref="paymentFormRef" />
		<payment-info ref="paymentInfoRef" />
	</div>
</template>

<script setup>
import { ref, onMounted } from "vue";
import { usePaymentStore } from "@/stores/console";
import PaymentForm from "./components/PaymentForm.vue";
import PaymentInfo from "./components/PaymentInfo.vue";
const paymentStore = usePaymentStore();
const loading = ref(false);
const paymentFormRef = ref();
const paymentInfoRef = ref();
const query = ref({
	name: "",
	startDate: "",
	endDate: "",
	status: "",
	pageIndex: 1,
	pageSize: 10,
});
const tableData = ref([]);
const total = ref(0);

onMounted(async () => {
	await loadData();
});

const loadData = async () => {
	loading.value = true;
	try {
		await paymentStore.fetchList(query.value);
		tableData.value = paymentStore.tableData.map((item) => ({
			id: item.id,
			project: item.title,
			type: item.type,
			applicant: item.applicantName,
			receiver: item.payeeName,
			amount: item.amount,
			applyTime: item.applyTime,
			account: item.account,
			remark: item.info,
			statusText:
				item.verifyState === 0
					? "待审核"
					: item.verifyState === 1
						? "审核通过"
						: item.verifyState === 2
							? "已驳回"
							: item.verifyState === 3
								? "已作废"
								: "",
			auditInfo: item.verifyRemark,
		}));
		total.value = paymentStore.total;
	} finally {
		loading.value = false;
	}
};

const handleSearch = () => {
	query.value.pageIndex = 1;
	loadData();
};

const handleAdd = () => {
	paymentFormRef.value.open();
};

const handlePrint = () => {
	window.print();
};

const handleView = async (row) => {
	const data = await paymentStore.fetchDetail(row.id);
	paymentInfoRef.value.open(data);
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
	flex-wrap: wrap;
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
