<template>
	<div class="subject-management">
		<!-- 搜索栏 -->
		<div class="search-bar">
			<el-input
				v-model="searchName"
				placeholder="搜索名称："
				prefix-icon="Search"
				clearable
				style="width: 250px"
				@keyup.enter="handleSearch"
			/>
			<el-button type="primary" @click="handleSearch">搜索</el-button>
			<el-button @click="handleReset">重置</el-button>
		</div>

		<!-- 表格 -->
		<el-table :data="tableData" v-loading="loading" border stripe>
			<el-table-column prop="subjectName" label="科目" min-width="150" />
			<el-table-column prop="sortNum" label="排序权重" width="120" align="center" />
			<el-table-column prop="info" label="简介" min-width="300" />
			<el-table-column label="操作" width="100" align="center">
				<template #default="{ row }">
					<el-button link type="primary" @click="handleEdit(row)">编辑</el-button>
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

		<!-- 编辑弹窗 -->
		<el-dialog v-model="dialogVisible" :title="dialogTitle" width="500px">
			<el-form :model="editForm" label-width="100px">
				<el-form-item label="科目" required>
					<el-input v-model="editForm.name" placeholder="请输入科目名称" />
				</el-form-item>
				<el-form-item label="排序权重">
					<el-input-number v-model="editForm.sortNum" :min="0" />
				</el-form-item>
				<el-form-item label="简介">
					<el-input v-model="editForm.info" type="textarea" rows="3" placeholder="请输入简介" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="dialogVisible = false">取消</el-button>
				<el-button type="primary" @click="handleSubmit">确定</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup>
import { ref, reactive, onMounted } from "vue";
import { ElMessage } from "element-plus";
import { getSubjectList, saveSubject, deleteSubject } from "@/apis/subject";

const searchName = ref("");
const tableData = ref([]);
const loading = ref(false);
const pageNum = ref(1);
const pageSize = ref(20);
const total = ref(0);
const dialogVisible = ref(false);
const isEdit = ref(false);
const dialogTitle = ref("新增科目");

const editForm = reactive({
	id: "",
	name: "",
	sortNum: 0,
	info: "",
});

// 获取科目列表
const fetchData = async () => {
	loading.value = true;
	try {
		const params = {
			pageNum: pageNum.value,
			pageSize: pageSize.value,
		};
		if (searchName.value) {
			params.name = searchName.value;
		}

		const res = await getSubjectList(params);

		// 根据接口文档，返回格式为 { errCode: 0, data: { records: [], total: 0 } }
		if (res.errCode === 0) {
			tableData.value = res.data?.rows || [];
			total.value = res.data?.total || 0;
		} else {
			ElMessage.error(res.msg || "获取数据失败");
		}
	} catch (error) {
		console.error("获取数据失败", error);
		ElMessage.error("获取数据失败");
	} finally {
		loading.value = false;
	}
};

const handleSearch = () => {
	pageNum.value = 1;
	fetchData();
};

const handleReset = () => {
	searchName.value = "";
	handleSearch();
};

// 编辑
const handleEdit = (row) => {
	isEdit.value = true;
	dialogTitle.value = "编辑科目";
	editForm.id = row.id;
	editForm.name = row.name;
	editForm.sortNum = row.sortNum;
	editForm.info = row.info || "";
	dialogVisible.value = true;
};

// 新增
const handleAdd = () => {
	isEdit.value = false;
	dialogTitle.value = "新增科目";
	editForm.id = "";
	editForm.name = "";
	editForm.sortNum = 0;
	editForm.info = "";
	dialogVisible.value = true;
};

// 提交保存
const handleSubmit = async () => {
	if (!editForm.name) {
		ElMessage.warning("请输入科目名称");
		return;
	}

	try {
		const res = await saveSubject(editForm);

		if (res.errCode === 0) {
			ElMessage.success(isEdit.value ? "修改成功" : "添加成功");
			dialogVisible.value = false;
			fetchData();
		} else {
			ElMessage.error(res.msg || "保存失败");
		}
	} catch (error) {
		console.error("保存失败", error);
		ElMessage.error("保存失败");
	}
};

const handleSizeChange = (val) => {
	pageSize.value = val;
	fetchData();
};

const handleCurrentChange = (val) => {
	pageNum.value = val;
	fetchData();
};

onMounted(() => {
	fetchData();
});
</script>

<style scoped lang="scss">
.subject-management {
	padding: 20px;

	.search-bar {
		background: #fff;
		padding: 20px;
		border-radius: 8px;
		margin-bottom: 20px;
		display: flex;
		gap: 12px;
	}
}
</style>
