<template>
	<div class="system-notice">
		<!-- 搜索区域 -->
		<MySearch :model="searchForm" :items="searchItems" formtitle="公告查询" @do-search="handleSearch">
			<template #header>
				<el-button type="primary" :icon="Plus" @click="handleAdd">新增</el-button>
				<el-button type="danger" :icon="Delete" :disabled="selectedRows.length === 0" @click="handleBatchDelete">
					删除
				</el-button>
				<el-button :icon="Message">发内部消息</el-button>
			</template>
		</MySearch>

		<!-- 表格区域 -->
		<F1Table
			:config="tableConfig"
			:data="tableData"
			:loading="loading"
			@page-change="handlePageChange"
			@edit="handleEdit"
			@selection-change="handleSelectionChange"
		>
			<template #title="{ row }">
				<el-text type="primary">{{ row.title }}</el-text>
			</template>
		</F1Table>

		<!-- 新增/编辑对话框 -->
		<el-dialog v-model="dialogVisible" :title="dialogTitle" width="600px" destroy-on-close>
			<el-form ref="formRef" :model="formData" :rules="formRules" label-width="80px">
				<el-form-item label="标题" prop="title">
					<el-input v-model="formData.title" placeholder="请输入标题" />
				</el-form-item>
				<el-form-item label="内容" prop="content">
					<el-input v-model="formData.content" type="textarea" :rows="6" placeholder="请输入内容" />
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
import { ElMessage, ElMessageBox, type FormInstance } from "element-plus";
import { Plus, Delete, Message } from "@element-plus/icons-vue";
import F1Table from "@/components/f1table/F1Table.vue";
import { TableType } from "@/components/f1table/type";
import type { TableConfig } from "@/components/f1table/type";
import MySearch from "@/components/mysearch/MySearch.vue";
import type { MyFormItemAttr } from "@/components/myform/type";

interface NoticeItem {
	id: number;
	title: string;
	content: string;
	createTime: string;
	updateTime: string;
}

const searchForm = reactive({
	title: "",
	pageSize: 10,
	pageNum: 1,
});

const searchItems: MyFormItemAttr[] = [
	{
		prop: "title",
		label: "标题",
		type: "input",
		fprops: {
			placeholder: "请输入标题",
			clearable: true,
		},
	},
];

const tableConfig = ref<TableConfig>({
	tableProperties: {
		stripe: true,
		border: true,
	},
	tableList: [
		{ type: TableType.selection, width: "55px", label: "选择" },
		{ type: TableType.normal, prop: "title", label: "标题", minWidth: "200px" },
		{ type: TableType.normal, prop: "createTime", label: "添加时间", width: "180px" },
		{ type: TableType.normal, prop: "updateTime", label: "修改时间", width: "180px" },
		{ type: TableType.handler as any, label: "操作", width: "100px", editText: "编辑" },
	],
	pagination: {
		enabled: true,
		currentPage: 1,
		pageSize: 10,
		total: 0,
	},
	handler: {
		edit: true,
		view: false,
		delete: false,
		editText: "编辑",
	},
});

const mockData: NoticeItem[] = [
	{
		id: 1,
		title: "系统升级通知",
		content: "系统将于今晚10点进行升级",
		createTime: "2026-03-20 10:00:00",
		updateTime: "2026-03-20 10:00:00",
	},
	{
		id: 2,
		title: "春季优惠活动",
		content: "春季报名优惠活动开始啦",
		createTime: "2026-03-18 14:30:00",
		updateTime: "2026-03-19 09:00:00",
	},
	{
		id: 3,
		title: "课程调整公告",
		content: "部分课程时间有所调整",
		createTime: "2026-03-15 16:00:00",
		updateTime: "2026-03-15 16:00:00",
	},
	{
		id: 4,
		title: "端午节放假通知",
		content: "端午节放假三天",
		createTime: "2026-03-10 08:00:00",
		updateTime: "2026-03-12 10:30:00",
	},
	{
		id: 5,
		title: "新员工入职培训",
		content: "本周五进行新员工培训",
		createTime: "2026-03-08 11:00:00",
		updateTime: "2026-03-08 11:00:00",
	},
];

const tableData = ref<NoticeItem[]>([]);
const loading = ref(false);
const selectedRows = ref<NoticeItem[]>([]);

const dialogVisible = ref(false);
const dialogTitle = ref("新增公告");
const submitLoading = ref(false);
const formRef = ref<FormInstance>();
const formData = reactive({
	id: 0,
	title: "",
	content: "",
});

const formRules = {
	title: [{ required: true, message: "请输入标题", trigger: "blur" }],
	content: [{ required: true, message: "请输入内容", trigger: "blur" }],
};

function loadData() {
	loading.value = true;
	setTimeout(() => {
		const filtered = mockData.filter((item) => item.title.toLowerCase().includes(searchForm.title.toLowerCase()));
		const start = (searchForm.pageNum - 1) * searchForm.pageSize;
		const end = start + searchForm.pageSize;
		tableData.value = filtered.slice(start, end);
		tableConfig.value.pagination!.total = filtered.length;
		loading.value = false;
	}, 300);
}

function handleSearch() {
	searchForm.pageNum = 1;
	loadData();
}

function handlePageChange(page: number, size: number) {
	searchForm.pageNum = page;
	searchForm.pageSize = size;
	loadData();
}

function handleSelectionChange(selection: NoticeItem[]) {
	selectedRows.value = selection;
}

function handleAdd() {
	dialogTitle.value = "新增公告";
	formData.id = 0;
	formData.title = "";
	formData.content = "";
	dialogVisible.value = true;
}

function handleEdit(row: NoticeItem) {
	dialogTitle.value = "编辑公告";
	formData.id = row.id;
	formData.title = row.title;
	formData.content = row.content;
	dialogVisible.value = true;
}

function handleBatchDelete() {
	if (selectedRows.value.length === 0) return;
	ElMessageBox.confirm(`确定要删除选中的 ${selectedRows.value.length} 条公告吗？`, "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	})
		.then(() => {
			const ids = selectedRows.value.map((item) => item.id);
			for (let i = mockData.length - 1; i >= 0; i--) {
				if (ids.includes(mockData[i].id)) {
					mockData.splice(i, 1);
				}
			}
			ElMessage.success("删除成功");
			loadData();
		})
		.catch(() => {});
}

async function handleSubmit() {
	await formRef.value?.validate();
	submitLoading.value = true;
	setTimeout(() => {
		if (formData.id === 0) {
			const newId = mockData.length > 0 ? Math.max(...mockData.map((i) => i.id)) + 1 : 1;
			mockData.unshift({
				id: newId,
				title: formData.title,
				content: formData.content,
				createTime: new Date().toLocaleString("zh-CN"),
				updateTime: new Date().toLocaleString("zh-CN"),
			});
			ElMessage.success("新增成功");
		} else {
			const index = mockData.findIndex((item) => item.id === formData.id);
			if (index !== -1) {
				mockData[index].title = formData.title;
				mockData[index].content = formData.content;
				mockData[index].updateTime = new Date().toLocaleString("zh-CN");
			}
			ElMessage.success("修改成功");
		}
		dialogVisible.value = false;
		loadData();
		submitLoading.value = false;
	}, 300);
}

onMounted(() => {
	loadData();
});
</script>

<style scoped lang="scss">
.system-notice {
	padding: 16px;
}
</style>
