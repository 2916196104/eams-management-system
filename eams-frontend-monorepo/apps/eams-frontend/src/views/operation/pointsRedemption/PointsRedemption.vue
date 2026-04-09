<template>
	<FilterToolbar
		@refresh="refresh"
		@print="print"
		@column-setting="handleColumnSetting"
		@search="search"
		@reset="clear"
	>
		<template #left>
			<div class="filter-grid">
				<div class="filter-item">
					<span>礼品名称：</span>
					<el-input v-model="form.searchTitle" placeholder="请输入" clearable />
				</div>
				<div class="filter-item">
					<span>审核状态：</span>
					<el-select v-model="form.enabled" placeholder="请选择状态">
						<el-option label="已取消" value="1" />
						<el-option label="待审核" value="0" />
						<el-option label="审核通过" value="2" />
						<el-option label="已驳回" value="3" />
					</el-select>
				</div>
				<div class="filter-item">
					<span>开始日期：</span>
					<el-date-picker v-model="form.startDate" type="date" value-format="yyyy-MM-dd" placeholder="请选择开始日期" />
				</div>
				<div class="filter-item">
					<span>结束日期：</span>
					<el-date-picker v-model="form.endDate" type="date" value-format="yyyy-MM-dd" placeholder="请选择结束日期" />
				</div>
			</div>
			<div class="btn">
				<el-button type="primary" @click="auditClick" size="small">
					<el-icon><EditPen /></el-icon>
					<span>审核</span>
				</el-button>
			</div>
		</template>
	</FilterToolbar>
	<div class="table-pagination-wrapper">
		<MyTable
			:istabmultiple="true"
			:tabdatacolumns="visibleColumns"
			:tabdata="tabdata"
			:tabtitle="''"
			:istabexpand="false"
			:istabseq="false"
			:istabpage="true"
			:istabselection="true"
			@selection-change="handleSelectionChange"
			@taboper-click="editClick"
		/>
		<el-pagination
			v-model:page-size="pageSize"
			:size="'default'"
			:total="tabdata.rows?.length || 0"
			:page-sizes="[10, 20, 50, 100, 200]"
			background
			layout="total, sizes, prev, pager, next, jumper"
		/>
	</div>

	<MyFormDialog ref="formDialog" :="formDialogProps" @confirm="onSubmit">
		<template #itemdefault="{ item }">
			<!-- 审核状态单选 -->
			<el-radio-group v-if="item.prop === 'auditStatus'" v-model="formDialogProps.data[item.prop]">
				<el-radio label="通过">通过</el-radio>
				<el-radio label="驳回">驳回</el-radio>
			</el-radio-group>

			<!-- 审核说明文本域 -->
			<el-input
				v-else-if="item.prop === 'auditRemark'"
				v-model="formDialogProps.data[item.prop]"
				type="textarea"
				:rows="4"
				placeholder="请输入审核说明"
			/>
		</template>
	</MyFormDialog>
	<PrintTable
		ref="printRef"
		print-title="学生积分记录表"
		:column-list="tabdatacolumns"
		:table-data="tabdata.rows || []"
	/>
	<ColumnSetting
		v-model="columnSettingVisible"
		:columns="allColumns"
		@change="handleColumnChange"
		@confirm="handleColumnConfirm"
		@reset="handleColumnReset"
	/>
</template>
<script setup lang="ts">
import FilterToolbar from "@/views/material/components/FilterToolbar.vue";
import { ref, reactive, onMounted } from "vue";
import { EditPen } from "@element-plus/icons-vue";
import MyTable from "@/components/mytable/MyTable.vue";
import type { PageDTO, MyTableColumn } from "@/components/mytable/type";
import MyFormDialog from "@/components/mydialog/MyFormDialog.vue";
import type { MyFormItemAttr } from "@/components/myform/type";
import type { SampleFormData } from "@/apis/sample/type";
import type { MyFormDialogProps } from "@/components/mydialog/type";
import type { MyFormInputProps } from "@/components/myform/props/input.ts";
import type { MyFormSelectProps } from "@/components/myform/props/select.ts";
import ColumnSetting from "../components/ColumnSetting.vue";
import type { ColumnOption } from "../components/ColumnSetting.vue";
import { computed } from "vue";
import PrintTable from "../components/PrintTable.vue";
import { getRedemptionApplicationList } from "@/apis/operation/pointsRedemption";
import { ElMessage } from "element-plus";
import { reviewRedemptionApplication } from "@/apis/operation/pointsRedemption";

interface RedemptionAuditForm extends SampleFormData {
	auditStatus: string;
	auditRemark: string;
}

// 保存当前选中的行数据
const selectedRow = ref<Record<string, any> | null>(null);
// 控制审核弹窗显示
const formDialog = ref();

// 监听表格复选框选择（MyTable 组件需支持 @selection-change 事件）
const handleSelectionChange = (selection: Record<string, any>[]) => {
	if (selection.length > 1) {
		ElMessage.warning("只能选择一条数据进行审核");
		return;
	}
	selectedRow.value = selection[0] || null;
};

// 点击审核按钮
const auditClick = () => {
	if (!selectedRow.value) {
		ElMessage.warning("请选择一条待审核的数据");
		return;
	}
	// 禁止选择已通过的数据
	if (selectedRow.value.auditStatus === "已通过") {
		ElMessage.warning("该数据已通过审核，无法再次操作");
		return;
	}
	// 打开审核弹窗
	formDialogProps.title = "请审核";
	formDialogProps.data = {
		auditStatus: "", // 重置单选状态
		auditRemark: "", // 重置审核说明
	};
	formDialog.value?.openDialog(true);
};

// 提交审核
const onSubmit = async (data: RedemptionAuditForm) => {
	if (!selectedRow.value) {
		ElMessage.warning("请选择一条待审核的数据");
		return;
	}

	const { auditStatus, auditRemark } = data;
	if (!auditStatus) {
		ElMessage.warning("请选择审核状态");
		return;
	}

	// 1. 组装后端需要的参数（核心！匹配截图）
	const requestParams = {
		id: Number(selectedRow.value.id), // 兑换记录 ID（必需）
		auditResult: auditStatus === "通过" ? 2 : 3, // 2=通过, 3=驳回（必需）
		remark: auditRemark || "", // 审核说明（可选）
	};

	console.log("发送审核请求：", requestParams);

	try {
		// 2. 调用真实审核接口（替换成你的实际接口）
		const res = await reviewRedemptionApplication(requestParams);

		// 3. 检查接口返回状态（根据截图：code:10000 表示成功）
		if (res.data && res.code === 10000) {
			ElMessage.success("审核成功");

			// 4. 【关键】更新本地表格数据
			const rows = tabdata.value.rows;
			const targetIndex = rows?.findIndex((row) => row.id === selectedRow.value?.id) ?? -1;
			if (rows && targetIndex !== -1) {
				rows[targetIndex] = {
					...rows[targetIndex],
					auditStatus: auditStatus === "通过" ? "审核通过" : "已驳回", // 同步前端状态
					auditor: "当前登录用户", // 可替换为实际用户名
					auditRemark: auditRemark || "",
				};
			}
			// 5. 关闭弹窗
			formDialog.value?.closeDialog();
			selectedRow.value = null; // 同步置空变量
		} else {
			ElMessage.warning(res.message || "审核失败");
		}
	} catch (error) {
		console.error("审核异常：", error);
		ElMessage.error("审核请求失败，请重试");
	}
};
const originalRows = ref<any[]>([]);
const columnSettingVisible = ref(false);
const pageSize = ref(20);
const form = reactive({
	searchTitle: "",
	materialId: "" as string,
	materialLabel: "",
	student: "",
	employee: "",
	changeType: "",
	startDate: "",
	endDate: "",
	enabled: "",
});
const allColumns = ref<ColumnOption[]>([
	{ label: "编号", prop: "id", visible: true },
	{ label: "学生姓名", prop: "studentName", visible: true },
	{ label: "手机号", prop: "phoneNumber", visible: true },
	{ label: "学校", prop: "school", visible: true },
	{ label: "兑换礼品", prop: "gift", visible: true },
	{ label: "兑换数量", prop: "quantity", visible: true },
	{ label: "花费积分", prop: "points", visible: true },
	{ label: "申请时间", prop: "applyTime", visible: true },
	{ label: "审核状态", prop: "auditStatus", visible: true },
	{ label: "审核人", prop: "auditor", visible: true },
	{ label: "审核备注", prop: "auditRemark", visible: true },
]);
const visibleColumns = computed(() => {
	return allColumns.value.filter((col) => col.visible);
});
const tabdatacolumns = ref<MyTableColumn[]>([
	{
		label: "编号",
		prop: "id",
		fixed: "left",
	},
	{
		label: "学生姓名",
		prop: "studentName",
	},
	{
		label: "手机号",
		prop: "phoneNumber",
	},
	{
		label: "学校",
		prop: "school",
	},
	{
		label: "兑换礼品",
		prop: "gift",
	},
	{
		label: "兑换数量",
		prop: "quantity",
	},
	{
		label: "花费积分",
		prop: "points",
	},
	{
		label: "申请时间",
		prop: "createTime",
	},
	{
		label: "审核状态",
		prop: "auditStatus",
	},
	{
		label: "审核人",
		prop: "auditor",
	},
	{
		label: "审核备注",
		prop: "auditRemark",
	},
]);
const tabdata = ref<PageDTO<any>>({
	rows: [
		{
			id: "1",
			studentName: "张三",
			phoneNumber: "13800138000",
			school: "北京大学",
			gift: "笔记本电脑",
			quantity: 1,
			points: 5000,
			applyTime: "2023-10-01 10:00:00",
			auditStatus: "已通过",
			auditor: "李四",
			auditRemark: "符合要求",
		},
		{
			id: "2",
			studentName: "李四",
			phoneNumber: "13900139000",
			school: "清华大学",
			gift: "平板电脑",
			quantity: 2,
			points: 4000,
			applyTime: "2023-10-02 11:00:00",
			auditStatus: "待审核",
			auditor: "",
			auditRemark: "",
		},
	],
	total: 2,
	pageIndex: 1,
	pageSize: 10,
});
//const auditClick = () => {
//	console.log("审核");
//	formDialogProps.title = "请审核";
//	formDialogProps.data = {};
//	formDialog.value?.openDialog(true);
//};
// const editClick = (index: number, row: any, evtname: string) => {
// 	console.log("编辑", row);
// 	formDialogProps.title = "修改礼品";
// 	formDialogProps.data = { ...row };
// 	formDialog.value?.openDialog();
// };
const editClick = (index: number, row: any) => {
	if (!row) return;

	formDialogProps.title = "修改礼品";

	Object.assign(formDialogProps.data, {
		giftName: row.giftName,
		schoolName: row.schoolName,
		category: row.category || "",
		points: row.points,
		giftDesc: row.giftDesc || "",
		avatar: row.image,
	});
	formDialog.value?.openDialog(true);
};
const formDialogProps = reactive<MyFormDialogProps<RedemptionAuditForm>>({
	// 表单数据
	data: reactive<RedemptionAuditForm>({
		auditStatus: "",
		auditRemark: "",
	}),
	// 表单域数据
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			label: "审核状态",
			prop: "auditStatus",
			type: "radio-group",
			fprops: {
				options: [
					{
						label: "通过",
						value: "通过",
					},
					{
						label: "驳回",
						value: "驳回",
					},
				],
			} as MyFormSelectProps,
		},
		{
			type: "input",
			prop: "auditRemark",
			label: "审核说明",
			fprops: {
				type: "textarea",
				rows: 4, // 直接控制高度
				placeholder: "请输入审核说明",
				clearable: true,
			} as MyFormInputProps,
		},
	]),
	cancelText: "取消",
	submitText: "提交",
	title: "请审核",
});
// const onSubmit = (data: boolean) => {
// 	if (!data) return;
// 	console.log("提交", formDialogProps.data);
// };
const printRef = ref();
const print = () => {
	printRef.value?.handlePrint();
};
// 列配置按钮点击
const handleColumnSetting = () => {
	console.log("列设置");
	columnSettingVisible.value = true;
};
// 列配置变化回调
const handleColumnChange = (newColumns: ColumnOption[]) => {
	allColumns.value = newColumns;
};

// 恢复默认列
const handleColumnReset = () => {
	allColumns.value.forEach((col) => (col.visible = true));
};

// 确认保存列配置
const handleColumnConfirm = (newColumns: ColumnOption[]) => {
	allColumns.value = newColumns;
	// 这里可以把配置存入 localStorage 做持久化
	localStorage.setItem("creditExchangeColumns", JSON.stringify(newColumns));
};
onMounted(async () => {
	try {
		getRedemptionApplicationList().then((res) => {
			console.log("res", res);
			tabdata.value.rows = res.data || [];
			// 保存原始数据
			originalRows.value = res.data || [];
		});
	} catch (error) {
		console.log(error);
	}
});
const search = () => {
	console.log("执行搜索条件：", form);
	// 从原始数据开始过滤
	let filtered = [...originalRows.value];
	//let filtered = [...tabdata.value.rows];
	// 1. 礼品名称：不为空时模糊匹配（包含输入的名称）
	if (form.searchTitle) {
		filtered = filtered.filter((row) => row.gift?.includes(form.searchTitle));
	}

	// 2. 审核状态：不为空时精确匹配（value 转成文字）
	if (form.enabled) {
		const statusMap: Record<string, string> = {
			"1": "已取消",
			"0": "待审核",
			"2": "审核通过",
			"3": "已驳回",
		};
		const statusText = statusMap[form.enabled];
		filtered = filtered.filter((row) => row.auditStatus === statusText);
	}

	// 3. 开始日期：不为空时，申请时间 >= 开始日期
	if (form.startDate) {
		filtered = filtered.filter((row) => row.createTime >= form.startDate);
	}

	// 4. 结束日期：不为空时，申请时间 <= 结束日期
	if (form.endDate) {
		filtered = filtered.filter((row) => row.createTime <= form.endDate);
	}

	// 更新表格为筛选后的数据
	tabdata.value.rows = filtered;
};
const clear = () => {
	console.log("清空筛选条件");
	// 重置所有筛选字段为空
	Object.assign(form, {
		searchTitle: "",
		enabled: "",
		startDate: "",
		endDate: "",
	});
	// 恢复表格为原始数据
	tabdata.value.rows = originalRows.value;
};
const refresh = () => {
	getRedemptionApplicationList().then((res) => {
		console.log("res", res);
		tabdata.value.rows = res.data || [];
		originalRows.value = res.data || [];
	});
};
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
	gap: 8px; /* 标签和输入框之间的间距 */
	flex: 1; /* 平均分配空间 */
	min-width: 0; /* 防止溢出 */
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
	gap: 8px;
	align-items: center;
}
.table-pagination-wrapper {
	background: #ffffff;
	border: 1px solid #ebeef5;
	border-radius: 4px;
	padding: 0;
	margin-top: 16px;
	overflow: hidden;
	padding-bottom: 10px;
	padding-left: 10px;
}
</style>
