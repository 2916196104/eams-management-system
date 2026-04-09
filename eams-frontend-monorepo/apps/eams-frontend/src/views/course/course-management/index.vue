<template>
	<div class="course-management">
		<!-- 筛选区域 -->
		<div class="filter-bar">
			<el-form :inline="true" :model="searchForm" class="search-form">
				<el-form-item label="课程名称：">
					<el-input v-model="searchForm.name" placeholder="请输入" clearable />
				</el-form-item>
				<el-form-item label="科目：">
					<el-select v-model="searchForm.subjectId" placeholder="请选择" clearable>
						<el-option v-for="item in subjectOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="状态：">
					<el-select v-model="searchForm.state" placeholder="请选择" clearable>
						<el-option label="启用" value="1" />
						<el-option label="禁用" value="0" />
					</el-select>
				</el-form-item>
				<el-form-item>
					<el-button type="primary" @click="handleSearch">搜索</el-button>
					<el-button @click="handleReset">重置</el-button>
				</el-form-item>
			</el-form>
		</div>

		<!-- 操作栏 -->
		<div class="action-bar">
			<el-button type="primary" @click="handleExport">
				<el-icon><Download /></el-icon>
				导出
			</el-button>
		</div>

		<!-- 表格 -->
		<el-table :data="tableData" v-loading="loading" border stripe>
			<el-table-column prop="name" label="课程" min-width="150" />
			<el-table-column prop="subjectName" label="科目" width="100" />
			<el-table-column prop="lessonType" label="课型" width="100" />
			<el-table-column prop="unitPrice" label="单价" width="100">
				<template #default="{ row }">¥{{ row.unitPrice }}</template>
			</el-table-column>
			<el-table-column prop="price" label="总售价" width="100">
				<template #default="{ row }">¥{{ row.price }}</template>
			</el-table-column>
			<el-table-column prop="lessonCount" label="课时数" width="80" />
			<el-table-column prop="unitName" label="班型" width="100" />
			<el-table-column prop="linkCount" label="关联数" width="80" />
			<el-table-column prop="forSale" label="上架状态" width="100">
				<template #default="{ row }">
					<el-tag :type="row.forSale ? 'success' : 'danger'">
						{{ row.forSale ? "已上架" : "未上架" }}
					</el-tag>
				</template>
			</el-table-column>
			<el-table-column prop="storage" label="库存" width="80" />
			<el-table-column prop="saleCount" label="销售量" width="80" />
			<el-table-column prop="saleAmount" label="销售额" width="100" />
			<el-table-column prop="closeDate" label="销售截至" width="120" />
			<el-table-column prop="state" label="课程状态" width="100">
				<template #default="{ row }">
					<el-tag :type="row.state === '1' ? 'success' : 'danger'">
						{{ row.state === "1" ? "启用" : "禁用" }}
					</el-tag>
				</template>
			</el-table-column>
			<el-table-column label="操作" fixed="right" width="180">
				<template #default="{ row }">
					<el-button link type="primary" @click="handleEdit(row)">编辑</el-button>
					<el-button link type="primary" @click="handleLinkCourse(row)">关联课程</el-button>
					<el-button link type="primary" @click="handleChapterSetting(row)">章节设置</el-button>
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
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage } from "element-plus";
import { Download } from "@element-plus/icons-vue";
import { getCourseList } from "@/apis/course";
import { getSubjectList } from "@/apis/subject";

// 搜索表单
const searchForm = reactive({
	name: "",
	subjectId: "",
	state: "",
});

// 表格数据
const tableData = ref<any[]>([]);
const loading = ref(false);
const pageNum = ref(1);
const pageSize = ref(20);
const total = ref(0);

// 科目选项
const subjectOptions = ref<any[]>([]);

// 获取科目列表（用于筛选下拉框）
const fetchSubjects = async () => {
	try {
		const res = await getSubjectList({ pageNum: 1, pageSize: 1000 });
		if (res.errCode === 0) {
			subjectOptions.value = res.data?.records || [];
		}
	} catch (error) {
		console.error("获取科目列表失败", error);
	}
};

// 获取课程列表
const fetchData = async () => {
	loading.value = true;
	try {
		const params: any = {
			pageNum: pageNum.value,
			pageSize: pageSize.value,
			...searchForm,
		};
		// 过滤空值
		Object.keys(params).forEach((key) => {
			if (params[key] === "" || params[key] === null || params[key] === undefined) {
				delete params[key];
			}
		});

		const res = await getCourseList(params);

		if (res.errCode === 0) {
			tableData.value = res.data?.records || [];
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

// 搜索
const handleSearch = () => {
	pageNum.value = 1;
	fetchData();
};

// 重置
const handleReset = () => {
	searchForm.name = "";
	searchForm.subjectId = "";
	searchForm.state = "";
	handleSearch();
};

// 导出
const handleExport = () => {
	ElMessage.info("导出功能开发中");
};

// 编辑
const handleEdit = (row: any) => {
	console.log("编辑", row);
	// TODO: 打开编辑弹窗
};

// 关联课程
const handleLinkCourse = (row: any) => {
	console.log("关联课程", row);
	// TODO: 跳转到关联课程页面
};

// 章节设置
const handleChapterSetting = (row: any) => {
	console.log("章节设置", row);
	// TODO: 跳转到章节设置页面
};

// 分页
const handleSizeChange = (val: number) => {
	pageSize.value = val;
	fetchData();
};

const handleCurrentChange = (val: number) => {
	pageNum.value = val;
	fetchData();
};

onMounted(() => {
	fetchSubjects();
	fetchData();
});
</script>

<style scoped lang="scss">
.course-management {
	padding: 20px;

	.filter-bar {
		background: #fff;
		padding: 20px;
		border-radius: 8px;
		margin-bottom: 20px;
	}

	.action-bar {
		margin-bottom: 20px;
	}
}
</style>
