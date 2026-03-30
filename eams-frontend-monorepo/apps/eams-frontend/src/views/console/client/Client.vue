<template>
	<div class="page-container">
		<!-- 搜索栏 -->
		<div class="search-bar">
			<el-input
				v-model="query.name"
				placeholder="请输入学员姓名"
				clearable
				@keyup.enter="loadData"
				style="width: 250px"
			/>
			<el-button type="primary" @click="handleSearch">搜索</el-button>
		</div>

		<!-- 工具栏 -->
		<div class="toolbar">
			<div class="left">
				<el-button type="primary" @click="handleAdd">添加线索</el-button>
			</div>

			<div class="right">
				<el-button @click="loadData">刷新</el-button>
				<el-button @click="handlePrint">打印</el-button>
				<!-- <el-button @click="handleColumnSetting">自定义表格列</el-button> -->
			</div>
		</div>

		<!-- 表格 -->
		<el-table :data="tableData" border style="width: 100%" v-loading="loading">
			<el-table-column type="selection" width="50" />
			<el-table-column type="index" label="序号" width="60" />

			<el-table-column prop="name" label="学生姓名" width="120" />
			<el-table-column prop="parent" label="家长(关系)" width="140" />
			<el-table-column prop="phone" label="联系电话" width="140" />
			<el-table-column prop="stage" label="学习阶段" width="120" />
			<el-table-column prop="gender" label="性别" width="80" />
			<el-table-column prop="age" label="年龄" width="80" />
			<el-table-column prop="source" label="来源" width="120" />
			<el-table-column prop="remain" label="剩余课次" width="100" />
			<el-table-column prop="lack" label="不足" width="80" />
			<el-table-column prop="createTime" label="添加时间" width="180" />
			<el-table-column prop="updateTime" label="最新更新日期" width="180" />
			<el-table-column prop="updateContent" label="最新更新内容" width="200" />
			<el-table-column prop="nextFollowTime" label="下次跟进时间" width="180" />
			<el-table-column prop="remark" label="备注" />

			<!-- 操作列 -->
			<el-table-column label="操作" width="160" fixed="right">
				<template #default="scope">
					<el-button text size="small" type="primary">报名</el-button>
					<el-button text size="small" type="primary">跟进</el-button>
				</template>
			</el-table-column>
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
	<clue-form ref="clueFormRef" />
</template>

<script setup>
import { ref, onMounted } from "vue";
import { useClientStore } from "@/stores/console";
import ClueForm from "./components/ClueForm.vue";

const clientStore = useClientStore();
const loading = ref(false);
const clueFormRef = ref();
const query = ref({
	name: "",
	pageNum: 1,
	pageSize: 10,
});
const tableData = ref([]);
const total = ref(0);

onMounted(async () => {
	await loadData();
	total.value = clientStore.total;
});

const loadData = async () => {
	loading.value = true;
	try {
		// 1. 请求接口
		await clientStore.fetchList(query.value);

		// 2. 数据转换（后端字段 -> 表格字段）
		tableData.value = clientStore.tableData.map((item) => ({
			name: item.studentName,
			parent: `${item.parentName}(${item.familyRelName})`,
			phone: item.contactPhone,
			stage: item.stageName,
			gender: item.genderName === 1 ? "男" : "女",
			age: item.age,
			source: item.sourceName,
			remain: item.remainLessonCount,
			lack: item.deficiencyStatus,
			createTime: item.addTime,
			updateTime: item.lastFollowTime,
			updateContent: item.lastFollowContent,
			nextFollowTime: item.nextFollowTime,
			remark: item.remark,
		}));

		// 3. 总条数
		total.value = clientStore.total;
	} finally {
		loading.value = false;
	}
};
const handleSearch = () => {
	query.value.pageNum = 1;
	loadData();
};
const handleAdd = () => {
	clueFormRef.value.open();
};

const handlePrint = () => {
	window.print();
};

const handleColumnSetting = () => {
	console.log("自定义列");
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
