<template>
	<FilterToolbar
		@search="handleSearch"
		@reset="handleReset"
		@refresh="handleRefresh"
		@print="handlePrint"
		@column-setting="handleColumnSetting"
	>
		<template #left>
			<div class="filter-grid">
				<div class="filter-item">
					<span>搜索标题：</span>
					<el-input v-model="form.searchTitle" placeholder="请输入" clearable />
				</div>
				<div class="filter-item">
					<span>搜索课程：</span>
					<SelectTablePopover
						v-model="form.materialLabel"
						display-prop="name"
						:search-fields="materialSearchFields"
						:columns="materialColumns"
						:data="materialPickerRows"
						:total="total"
						:loading="materialPickerLoading"
						@search="loadMaterialPicker"
						@select="onMaterialSelect"
						:width="500"
					/>
				</div>
			</div>
			<div class="btn">
				<el-button type="primary" @click="addTrialCardClick" size="small">+ 添加体验卡</el-button>
				<el-button @click="deleteClick" size="small">
					<el-icon><DeleteFilled /></el-icon>
					<span>删除</span>
				</el-button>
			</div>
		</template>
	</FilterToolbar>

	<!-- 打印组件 -->
	<PrintTable
		ref="printRef"
		print-title="体验卡管理列表"
		:column-list="tabdatacolumns"
		:table-data="tabdata.rows || []"
	/>

	<!-- 列配置组件 -->
	<ColumnSetting
		v-model="columnSettingVisible"
		:columns="allColumns"
		@change="handleColumnChange"
		@confirm="handleColumnConfirm"
		@reset="handleColumnReset"
	/>

	<MyTable
		:istabmultiple="true"
		:tabdatacolumns="visibleColumns"
		:taboperbtns="taboperbtns"
		:tabdata="tabdata"
		:tabtitle="''"
		:istabexpand="false"
		:istabseq="false"
		:istabpage="true"
		@taboper-click="handleTableOperate"
		@selection-change="handleSelectionChange"
	/>

	<!-- 新增/编辑体验卡弹窗 -->
	<MyFormDialog ref="formDialog" v-bind="formDialogProps" @confirm="handleSubmit">
		<template #itemdefault="{ item }">
			<el-date-picker
				v-if="item.prop === 'endDate'"
				v-model="formDialogProps.data[item.prop]"
				type="date"
				value-format="YYYY-MM-DD"
				placeholder="请选择发行结束日期"
				style="width: 100%"
				@change="
					(val: string | null) => {
						// 手动同步值，确保表单能拿到最新值
						formDialogProps.data.endDate = val;
						// 立即触发校验，消除红框
						nextTick(() => formDialog?.formRef?.validateField('endDate'));
					}
				"
			/>
			<el-switch
				v-else-if="item.prop === 'enabled'"
				v-model="formDialogProps.data[item.prop]"
				active-text="启用"
				inactive-text="禁用"
			/>
			<SelectTablePopover
				v-else-if="item.prop === 'courseId'"
				v-model="formDialogProps.data.courseName"
				display-prop="courseName"
				:label="formDialogProps.data.courseName"
				:search-fields="materialSearchFields"
				:columns="materialColumns"
				:data="materialPickerRows"
				:total="total"
				:loading="materialPickerLoading"
				@search="loadMaterialPicker"
				@select="(row) => onSelectCourse(row)"
				:width="500"
			/>
		</template>
	</MyFormDialog>

	<!-- 👇 新增：领取记录弹窗 -->
	<el-dialog
		v-model="recordDialogVisible"
		title="体验卡领取列表"
		width="80%"
		:close-on-click-modal="false"
		@close="closeRecordDialog"
	>
		<MyTable
			:istabmultiple="false"
			:tabdatacolumns="recordTableColumns"
			:taboperbtns="[]"
			:tabdata="recordTableData"
			:tabtitle="''"
			:istabexpand="false"
			:istabseq="false"
			:istabpage="true"
		/>
		<template #footer>
			<div style="text-align: right">
				<el-button @click="closeRecordDialog">关闭</el-button>
			</div>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import FilterToolbar from "@/views/material/components/FilterToolbar.vue";
import SelectTablePopover from "@/views/material/components/SelectTablePopover.vue";
import { ref, reactive, nextTick, computed, onMounted } from "vue";
import { DeleteFilled } from "@element-plus/icons-vue";
import MyTable from "@/components/mytable/MyTable.vue";
import MyFormDialog from "@/components/mydialog/MyFormDialog.vue";
import type { MyTableOperationsBtn } from "@/components/mytable/type";
import type { PageDTO, MyTableColumn } from "@/components/mytable/type";
import type { MyFormDialogProps } from "@/components/mydialog/type";
import type { MyFormItemAttr } from "@/components/myform/type";
import {
	getTrialCardList,
	deleteTrialCard,
	saveTrialCard,
	getTrialCardRecord,
} from "@/apis/operation/trialCardManagement";

// 👇 新增：打印和列配置组件引入
import ColumnSetting from "../../operation/components/ColumnSetting.vue";
import PrintTable from "../../operation/components/PrintTable.vue";
import type { ColumnOption } from "../../operation/components/ColumnSetting.vue";
import { ElMessage, ElMessageBox } from "element-plus";

// ==================== 原有变量 ====================
const form = reactive({
	searchTitle: "",
	materialId: "" as string,
	materialLabel: "",
	student: "",
	employee: "",
	changeType: "",
	startDate: "",
	endDate: "",
});
// 弹窗配置
const formDialog = ref();
const formDialogProps = reactive<MyFormDialogProps<any>>({
	data: reactive({
		name: "",
		courseId: "",
		courseName: "",
		issueCount: "",
		classHours: "",
		validDays: "",
		endDate: "",
		enabled: false,
	}),
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "input",
			prop: "name",
			label: "体验卡名称",
			required: true,
			rules: [{ required: true, message: "请输入体验卡名称" }],
			fprops: { placeholder: "请输入体验卡名称" },
		},
		{
			type: "input",
			prop: "courseId",
			label: "选择课程",
			rules: [{ message: "请选择课程" }],
		},
		{
			type: "number",
			prop: "issueCount",
			label: "发行数量",
			required: true,
			rules: [{ required: true, message: "请输入发行数量" }],
			fprops: { placeholder: "请输入发行数量", width: "100%" },
		},
		{
			type: "number",
			prop: "classHours",
			label: "包含课时数",
			required: true,
			rules: [{ required: true, message: "请输入包含课时数" }],
			fprops: { placeholder: "请输入包含课时数", width: "100%" },
		},
		{
			type: "number",
			prop: "validDays",
			label: "有效天数",
			required: true,
			rules: [{ required: true, message: "请输入有效天数" }],
			fprops: { placeholder: "请输入有效天数", width: "100%" },
		},
		{
			type: "date",
			prop: "endDate",
			label: "发行结束日期",
			fprops: { placeholder: "请选择发行结束日期" },
		},
		{ type: "select", prop: "enabled", label: "是否启用", rules: [] },
	]),
	formattr: { disabled: false, "label-width": "120px" },
	title: "体验卡信息",
	width: "70vw",
	reset: false,
	submitText: "提交",
	cancelText: "取消",
});
// 课程选择器配置
const materialSearchFields: any[] = [{ label: "搜名称", prop: "name", component: "input", placeholder: "请输入" }];
const materialColumns: any[] = [
	{ label: "id", prop: "id", fixed: "left" },
	{ label: "课程名称", prop: "courseName", minWidth: 120 },
	{ label: "课时", prop: "classHours", width: 80 },
	{ label: "单价", prop: "unitPrice", width: 80 },
	{ label: "总价", prop: "totalPrice", width: 100 },
	{ label: "单位", prop: "unit", width: 60 },
	{ label: "时长", prop: "duration", width: 80 },
	{ label: "类型", prop: "type", width: 100 },
];
const selectedRows = ref<any[]>([]);
const materialPickerRows = ref([
	{
		id: "1",
		courseName: "apex猎杀教程",
		classHours: 10000,
		unitPrice: 10,
		totalPrice: 10000,
		unit: "期",
		duration: 90,
		type: "大班课",
	},
	{
		id: "2",
		courseName: "古典语文",
		classHours: 50,
		unitPrice: 20,
		totalPrice: 1000,
		unit: "期",
		duration: 45,
		type: "小班课",
	},
]);
const total = ref(100);
const materialPickerLoading = ref(false);

// ==================== 新增：领取记录相关变量 ====================
// 弹窗显示控制
const recordDialogVisible = ref(false);
// 领取记录表格数据
const recordTableData = ref<PageDTO<any>>({
	rows: [],
	total: 0,
	pageIndex: 1,
	pageSize: 20,
});
// 领取记录表格列配置（和截图完全一致）
const recordTableColumns = ref<MyTableColumn[]>([
	{ label: "序号", prop: "index", width: "80" },
	{ label: "体验卡名称", prop: "trialName" },
	{ label: "领取人", prop: "userName" },
	{ label: "电话", prop: "phone" },
	{ label: "领取时间", prop: "createTime" },
]);
// 当前操作的体验卡ID
const currentTrialId = ref<string | number>("");

// ==================== 原有方法 ====================
async function loadMaterialPicker(payload: Record<string, any>) {
	console.log(payload);
}

function onMaterialSelect(row: Record<string, any>) {
	form.materialId = String(row.id ?? "");
	form.materialLabel = row.courseName ?? "";
}

function onSelectCourse(row: Record<string, any>) {
	formDialogProps.data.courseId = row.id; // 接口需要的值
	formDialogProps.data.courseName = row.courseName; // 用于显示
	formDialogProps.data.classHours = row.classHours ?? 0;
	nextTick(() => formDialog.value?.formRef?.validateField("courseId"));
}

// 表格配置
function handleEndDateChange(val: string | null) {
	formDialogProps.data.endDate = val ?? "";
	nextTick(() => formDialog.value?.formRef?.validateField("endDate"));
}

function handleSelectionChange(rows: any[]) {
	selectedRows.value = rows;
}

const tabdatacolumns = ref<MyTableColumn[]>([
	{ label: "id", prop: "courseId", fixed: "left" },
	{ label: "体验卡名称", prop: "name" },
	{ label: "所属课程", prop: "courseName" },
	{ label: "包含课时数", prop: "classHours" },
	{ label: "发行数量", prop: "issueCount" },
	{ label: "已领取数量", prop: "claimedCount" },
	{ label: "领取后有效天数", prop: "validDays" },
	{ label: "发行结束日期", prop: "endDate" },
	{ label: "是否启用", prop: "enabled" },
	{ label: "操作", prop: "operate", width: "140", fixed: "right" },
]);

// ✅ 按钮样式（两个按钮同一行，透明蓝色文字）
const taboperbtns = ref<MyTableOperationsBtn[]>([
	{
		text: "编辑",
		evtname: "edit",
		attr: {
			type: "primary",
			style: { background: "transparent", color: "#409eff", border: "none", fontSize: "11px", padding: "0 8px" },
		},
	},
	{
		text: "领取记录",
		evtname: "record",
		attr: {
			type: "primary",
			style: { background: "transparent", color: "#409eff", border: "none", fontSize: "11px", padding: "0 8px" },
		},
	},
]);

const tabdata = ref<PageDTO<any>>({
	rows: [
		{
			id: "1",
			name: "apex猎杀教程体验卡",
			courseName: "apex猎杀教程",
			classHours: 10000,
			issueCount: 100,
			claimedCount: 20,
			validDays: 30,
			endDate: "2026-04-30",
			enabled: "启用",
		},
		{
			id: "2",
			name: "古典语文体验卡",
			courseName: "古典语文",
			classHours: 50,
			issueCount: 50,
			claimedCount: 10,
			validDays: 15,
			endDate: "2026-05-15",
			enabled: "禁用",
		},
	],
	total: 2,
	pageIndex: 1,
	pageSize: 10,
});

// 打开弹窗
const addTrialCardClick = () => {
	Object.assign(formDialogProps.data, {
		name: "",
		courseId: "",
		courseName: "",
		issueCount: "",
		classHours: "",
		validDays: "",
		endDate: "",
		enabled: false,
	});
	nextTick(() => formDialog.value?.openDialog(true));
};

const handleSubmit = async (valid: boolean) => {
	if (!valid) return ElMessage.warning("请完善必填项");

	const { data } = formDialogProps;

	// 找到课程 ID，如果用户直接输入名称没选列表项
	if (!data.courseId) {
		const matched = materialPickerRows.value.find((m) => m.courseName === data.courseName);
		if (!matched) {
			return ElMessage.warning("请选择有效课程");
		}
		data.courseId = matched.id;
		data.classHours = matched.classHours ?? 0;
	}

	if (!data.endDate) return ElMessage.warning("请选择发行结束日期");

	// 构造接口参数
	const payload = {
		id: data.id || 0,
		name: data.name,
		courseId: Number(data.courseId),
		lessonCount: Number(data.classHours),
		totalIssue: Number(data.issueCount),
		validDays: Number(data.validDays),
		endDate: data.endDate,
		isActive: Boolean(data.enabled),
	};

	try {
		console.log(payload);
		await saveTrialCard(payload);

		// 更新表格
		if (data.id) {
			const index = tabdata.value.rows?.findIndex((r) => r.id === data.id) ?? -1;
			if (index !== -1 && tabdata.value.rows) {
				tabdata.value.rows[index] = {
					...tabdata.value.rows[index],
					name: data.name,
					courseId: data.courseId,
					courseName: data.courseName,
					classHours: data.classHours,
					issueCount: data.issueCount,
					validDays: data.validDays,
					endDate: data.endDate,
					enabled: data.enabled ? "启用" : "禁用",
				};
			}
			ElMessage.success("编辑体验卡成功");
		} else {
			const newRow = {
				id: String(Date.now()),
				name: data.name,
				courseId: data.courseId,
				courseName: data.courseName,
				classHours: data.classHours,
				issueCount: data.issueCount,
				claimedCount: 0,
				validDays: data.validDays,
				endDate: data.endDate,
				enabled: data.enabled ? "启用" : "禁用",
			};
			tabdata.value.rows?.unshift(newRow);
			tabdata.value.total += 1;
			ElMessage.success("添加体验卡成功");
		}

		formDialog.value?.closeDialog();
	} catch (error) {
		console.error(error);
		ElMessage.error("保存失败");
	}
};
const deleteClick = async () => {
	if (!selectedRows.value || selectedRows.value.length === 0) {
		return ElMessage.warning("请选择要删除的数据");
	}

	ElMessageBox.confirm("确定删除选中记录吗？", "提示", {
		confirmButtonText: "确定",
		cancelButtonText: "取消",
		type: "warning",
	}).then(async () => {
		try {
			const ids = selectedRows.value.map((item) => item.id);
			await deleteTrialCard({ value: ids });

			// 删除表格数据
			tabdata.value.rows = tabdata.value.rows?.filter((item) => !ids.includes(item.id));
			tabdata.value.total = tabdata.value.rows?.length || 0;

			// 清空选中行
			selectedRows.value = [];

			ElMessage.success("批量删除成功");
		} catch {
			ElMessage.error("批量删除失败");
		}
	});
};

const handleTableOperate = async (index: number, row: any, evtname: string) => {
	if (evtname === "edit") {
		// 1️⃣ 把当前行数据赋值到弹窗表单
		Object.assign(formDialogProps.data, {
			id: row.id,
			name: row.name,
			courseId: row.courseId, // 需要在表格里保留courseId
			courseName: row.courseName,
			lessonCount: row.classHours, // 对应接口 lessonCount
			totalIssue: row.issueCount, // 对应接口 totalIssue
			validDays: row.validDays,
			endDate: row.endDate,
			isActive: row.enabled === "启用", // boolean
		});

		// 2️⃣ 打开弹窗
		nextTick(() => formDialog.value?.openDialog(true));
	} else if (evtname === "delete") {
		await deleteTrialCard({ value: [row.id] });
		console.log("点击了删除按钮，row:", row);
	} else if (evtname === "record") {
		recordDialogVisible.value = true;
		// 👇 领取记录按钮逻辑
		try {
			currentTrialId.value = row.id;
			// 调用接口获取领取记录
			const res = await getTrialCardRecord({ trialId: row.id });
			console.log("领取记录接口返回：", res);

			// 处理接口数据，添加序号
			const recordList = res.data?.list || res.data || [];
			const listWithIndex = recordList.map((item: any, idx: number) => ({
				...item,
				index: idx + 1, // 序号从1开始
				trialName: row.name, // 回填体验卡名称（如果接口没返回）
			}));

			// 赋值给表格数据
			recordTableData.value = {
				rows: listWithIndex,
				total: listWithIndex.length,
				pageIndex: 1,
				pageSize: 20,
			};

			// 打开弹窗
			recordDialogVisible.value = true;
		} catch (error) {
			console.error("获取领取记录失败：", error);
			ElMessage.error("获取领取记录失败，请稍后重试");
		}
	}
};

// ==================== 新增：关闭领取记录弹窗方法 ====================
const closeRecordDialog = () => {
	recordDialogVisible.value = false;
	// 清空表格数据，避免下次打开残留
	recordTableData.value = {
		rows: [],
		total: 0,
		pageIndex: 1,
		pageSize: 20,
	};
	currentTrialId.value = "";
};

// ==================== 原有方法 ====================
const originalTableData = ref<PageDTO<any>>({
	rows: [],
	total: 0,
	pageIndex: 1,
	pageSize: 10,
});

// 1. 刷新功能
const handleRefresh = async () => {
	try {
		const res = await getTrialCardList();
		const rows = res.data?.rows || [];
		const total = res.data?.total || 0;

		// 保存原始数据
		originalTableData.value = {
			rows: [...rows],
			total,
			pageIndex: 1,
			pageSize: 10,
		};

		// 赋值给表格
		tabdata.value.rows = [...rows];
		tabdata.value.total = total;

		ElMessage.success("刷新成功");
	} catch {
		ElMessage.error("刷新失败");
	}
};

// 2. 查找/查询功能（条件为空显示全部数据）
const handleSearch = () => {
	// 如果没有任何查询条件 → 直接显示全部原始数据
	if (!form.searchTitle && !form.materialLabel) {
		tabdata.value.rows = [...(originalTableData.value.rows ?? [])];
		tabdata.value.total = originalTableData.value.total;
		ElMessage.success("查询成功");
		return;
	}

	// 有查询条件 → 从原始数据过滤
	let filtered = [...(originalTableData.value.rows ?? [])];

	// 按体验卡名称搜索
	if (form.searchTitle) {
		filtered = filtered.filter((row) => row.name?.includes(form.searchTitle));
	}

	// 按课程名称搜索
	if (form.materialLabel) {
		filtered = filtered.filter((row) => row.courseName === form.materialLabel);
	}

	// 只更新显示的数据
	tabdata.value.rows = filtered;
	tabdata.value.total = filtered.length;

	ElMessage.success("查询成功");
};

// 3. 重置功能
const handleReset = () => {
	// 清空条件
	form.searchTitle = "";
	form.materialId = "";
	form.materialLabel = "";

	// 恢复原始数据
	tabdata.value.rows = [...(originalTableData.value.rows ?? [])];
	tabdata.value.total = originalTableData.value.total;

	ElMessage.info("已重置筛选条件");
};

// 4. 打印功能
const printRef = ref();
const handlePrint = () => {
	printRef.value?.handlePrint();
};

// 5. 列配置功能
const columnSettingVisible = ref(false);
const allColumns = ref<ColumnOption[]>([
	{ label: "ID", prop: "id", visible: true },
	{ label: "体验卡名称", prop: "name", visible: true },
	{ label: "所属课程", prop: "courseName", visible: true },
	{ label: "包含课时数", prop: "classHours", visible: true },
	{ label: "发行数量", prop: "issueCount", visible: true },
	{ label: "已领取数量", prop: "claimedCount", visible: true },
	{ label: "领取后有效天数", prop: "validDays", visible: true },
	{ label: "发行结束日期", prop: "endDate", visible: true },
	{ label: "是否启用", prop: "enabled", visible: true },
	{ label: "操作", prop: "operate", visible: true },
]);

const visibleColumns = computed(() => {
	return allColumns.value.filter((col) => col.visible).slice();
});

const handleColumnSetting = () => {
	columnSettingVisible.value = true;
};

const handleColumnChange = (newColumns: any) => {
	allColumns.value = newColumns;
};

const handleColumnConfirm = (newColumns: any) => {
	allColumns.value = newColumns;
	localStorage.setItem("trialCardColumns", JSON.stringify(newColumns));
};

const handleColumnReset = () => {
	allColumns.value.forEach((col) => (col.visible = true));
};

// 页面加载
onMounted(() => {
	// 读取本地列配置
	const cache = localStorage.getItem("trialCardColumns");
	if (cache) {
		allColumns.value = JSON.parse(cache);
	}

	getTrialCardList().then((res) => {
		tabdata.value.rows = res.data?.rows || [];
		tabdata.value.total = res.data?.total || 0;
	});
});
</script>

<style scoped>
.filter-grid {
	display: flex;
	flex-wrap: wrap;
	gap: 16px;
}
.filter-item {
	display: flex;
	align-items: center;
	gap: 8px;
	flex: 1;
	min-width: 0;
}
.filter-item span {
	white-space: nowrap;
}
.btn {
	display: flex;
	gap: 8px;
	margin-top: 20px;
}
.my-table-operate-btn {
	display: flex;
	gap: 16px;
	align-items: center;
}
</style>
