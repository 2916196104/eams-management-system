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
					<span>选择学生：</span>
					<SelectTablePopover
						ref="studentDialog"
						@confirm="onStudentSelect"
						v-model="form.student"
						:search-fields="studentSearchFields"
						:columns="studentColumns"
						:data="studentData"
						placeholder="请选择学生"
						@select="onStudentSelect"
					/>
				</div>
				<div class="filter-item">
					<span>手机号：</span>
					<el-input v-model="form.phone" placeholder="请输入" clearable />
				</div>
				<div class="filter-item">
					<span>变动原因：</span>
					<el-select v-model="form.changeType" placeholder="请选择变动原因">
						<el-option label="课后点评奖励" value="1" />
						<el-option label="积分商城兑换礼品消费" value="0" />
						<el-option label="积分商城兑换失败返还" value="2" />
						<el-option label="积分调整" value="3" />
						<el-option label="修改课后点评" value="4" />
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
			<div class="text">
				<span>积分的设置以促学为目的，主要来自老师对学生的课后点评。</span>
			</div>
			<div class="btn">
				<el-button type="primary" @click="adjustPointsFormClick" size="small">
					<span>调整积分</span>
				</el-button>
			</div>
		</template>
	</FilterToolbar>
	<div class="table-pagination-wrapper">
		<MyTable
			:istabmultiple="true"
			:tabdatacolumns="visibleColumns"
			:taboperbtns="taboperbtns"
			:tabdata="tabdata"
			:tabtitle="''"
			:istabexpand="false"
			:istabseq="false"
			:istabpage="true"
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

	<MyFormDialog
		ref="adjustPointsFormDialog"
		:formitemdata="formDialogProps.formitemdata"
		@confirm="onSubmit"
		:data="formDialogProps.data"
		:title="formDialogProps.title"
	>
		<template #itemdefault="{ item }">
			<!-- 其他字段用默认渲染 -->
			<my-form-render
				v-if="item.prop !== 'student'"
				:item="item"
				:model="formDialogProps.data[item.prop]"
				@update:model="(val: unknown) => (formDialogProps.data[item.prop] = val)"
			/>
			<!-- 学生选择弹窗 -->
			<SelectTablePopover
				v-if="item.prop === 'student'"
				v-model="formDialogProps.data.student"
				:search-fields="studentSearchFields"
				:columns="studentColumns"
				:data="studentData"
				placeholder="请选择学生"
				@select="onStudentSelect"
			/>
		</template>
	</MyFormDialog>
	<!-- 通用打印组件 -->
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
import { ref, reactive } from "vue";
import SelectTablePopover from "@/views/material/components/SelectTablePopover.vue";
import MyTable from "@/components/mytable/MyTable.vue";
import type { MyTableOperationsBtn } from "@/components/mytable/type";
import type { PageDTO, MyTableColumn } from "@/components/mytable/type";
import MyFormDialog from "@/components/mydialog/MyFormDialog.vue";
import { ElMessage } from "element-plus";
import type { MyFormItemAttr } from "@/components/myform/type";
import type { SampleFormData } from "@/apis/sample/type";
import type { MyFormDialogProps } from "@/components/mydialog/type";
import type { MyFormInputProps } from "@/components/myform/props/input.ts";
import type { SearchField, SelectionTablePopoverProps } from "@/views/material/components/type";
import dayjs from "dayjs";
import { getPointsRecordList } from "@/apis/operation/pointsRecord";
import { onMounted } from "vue";
import { adjustPointsRecord } from "@/apis/operation/pointsRecord";
import PrintTable from "../components/PrintTable.vue";
import ColumnSetting from "../components/ColumnSetting.vue";
import type { ColumnOption } from "../components/ColumnSetting.vue";
import { computed } from "vue";
const originalRows = ref<any[]>([]);
// 弹窗显示状态
const columnSettingVisible = ref(false);
const visibleColumns = computed(() => {
	return allColumns.value.filter((col) => col.visible);
});
// 列配置（和你截图完全对应）
const allColumns = ref<ColumnOption[]>([
	{ label: "序号", prop: "index", visible: true },
	{ label: "学生姓名", prop: "studentName", visible: true },
	{ label: "变动原因", prop: "reason", visible: true },
	{ label: "变动积分", prop: "changePoints", visible: true },
	{ label: "剩余积分", prop: "remainingPoints", visible: true },
	{ label: "说明", prop: "description", visible: true },
	{ label: "变动时间", prop: "changeTime", visible: true },
]);

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
// 模板ref绑定
const printRef = ref<InstanceType<typeof PrintTable>>();
const pageSize = ref(20);
const form = reactive({
	searchTitle: "",
	materialId: "" as string,
	materialLabel: "",
	student: "",
	phone: "",
	employee: "",
	changeType: "",
	startDate: "",
	endDate: "",
	enabled: "",
});
const tabdatacolumns = ref<MyTableColumn[]>([
	{
		label: "序号",
		prop: "index",
	},
	{
		label: "学生姓名",
		prop: "studentName",
	},
	{
		label: "变动原因",
		prop: "reason",
	},
	{
		label: "变动积分",
		prop: "changePoints",
	},
	{
		label: "剩余积分",
		prop: "remainingPoints",
	},
	{
		label: "说明",
		prop: "description",
	},
	{
		label: "变动时间",
		prop: "changeTime",
	},
]);
const taboperbtns = ref<MyTableOperationsBtn[]>([
	{
		text: "编辑",
		evtname: "edit",
		attr: {
			size: "small",
			type: "primary",
		},
	},
]);
const onSubmit = async (data: SampleFormData) => {
	if (!data?.student) {
		ElMessage.warning("请选择学生");
		return;
	}

	if (!data.points) {
		ElMessage.warning("请输入积分");
		return;
	}

	// 1️⃣ 查找该学生当前剩余积分（最后一条记录）
	const lastRecord = [...(tabdata.value.rows || [])].reverse().find((r) => r.studentName === data.student);

	const oldPoints = lastRecord?.remainingPoints || 0;

	// 2️⃣ 计算新积分
	const newRemainingPoints = oldPoints + Number(data.points);

	// 3️⃣ 生成新记录
	const newRow = {
		index: (tabdata.value.rows?.length || 0) + 1,
		studentName: data.student,
		reason: form.changeType || "积分调整",
		changePoints: data.points,
		remainingPoints: newRemainingPoints,
		description: data.changeReason || "",
		changeTime: dayjs().format("YYYY-MM-DD HH:mm:ss"),
	};

	// 4️⃣ 插入表格
	tabdata.value.rows?.unshift(newRow);
	const res = await adjustPointsRecord({
		name: data.student,
		content: form.changeType,
		point: Number(data.points),
	});
	if (!res) return;
	console.log(res);
	// 5️⃣ 关闭弹窗
	adjustPointsFormDialog.value?.closeDialog();

	ElMessage.success("积分调整成功");
};
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
const formDialog = ref();
const studentDialog = ref();
const adjustPointsFormDialog = ref();
const adjustPointsFormClick = () => {
	formDialogProps.title = "修改到期日期";
	// 初始化弹窗数据：学生名称默认选中
	formDialogProps.data = {
		student: form.student,
		points: 0,
		changeReason: "",
	};
	adjustPointsFormDialog.value?.openDialog(true);
};
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
const formDialogProps = reactive<MyFormDialogProps<SampleFormData>>({
	// 表单数据
	data: reactive<SampleFormData>({}),
	// 表单域数据
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "input", // 保持合法类型
			prop: "student",
			label: "选择学生",
			fprops: {
				placeholder: "请选择学生",
				readonly: true, // 不允许直接输入
			},
		},
		{
			type: "number",
			prop: "points",
			label: "调整积分数",
			fprops: {
				placeholder: "请输入调整积分数",
				clearable: true,
				width: "100%",
			} as MyFormInputProps,
		},
		{
			type: "input",
			prop: "changeReason",
			label: "调整原因",
			fprops: {
				type: "textarea",
				rows: 4, // 直接控制高度
				placeholder: "请输入调整原因",
				clearable: true,
				width: "100%",
			} as MyFormInputProps,
		},
	]),
	cancelText: "取消",
	submitText: "提交",
	title: "修改到期日期",
});
const studentSearchFields = ref<SearchField[]>([
	{
		label: "学生姓名",
		prop: "name",
		component: "input",
	},
	{
		label: "手机号",
		prop: "phone",
		component: "input",
	},
]);
const studentColumns = ref<SelectionTablePopoverProps["columns"]>([
	{
		label: "学生姓名",
		prop: "name",
	},
	{
		label: "分校",
		prop: "branch",
	},
	{
		label: "阶段",
		prop: "stage",
	},
]);
const studentData = ref([
	{
		name: "张三",
		phone: "13800138000",
		school: "北京大学",
	},
	{
		name: "李四",
		phone: "13900139000",
		school: "清华大学",
	},
]);
const onStudentSelect = (row: any) => {
	form.student = row.name;
	// 同步更新弹窗中的学生选择
	formDialogProps.data.student = row.name;
};
const search = () => {
	console.log("执行搜索条件：", form);
	// 从原始数据开始过滤
	let filtered = [...originalRows.value];

	// 1. 学生姓名：不为空时精确匹配
	if (form.student) {
		filtered = filtered.filter((row) => row.studentName === form.student);
	}

	// 2. 手机号：不为空时模糊匹配（包含输入的号码）
	if (form.phone) {
		filtered = filtered.filter((row) => row.phoneNumber?.includes(form.phone));
	}

	// 3. 变动原因：不为空时，把value转成文字后匹配
	if (form.changeType) {
		const reasonMap: Record<string, string> = {
			"1": "课后点评奖励",
			"0": "积分商城兑换礼品消费",
			"2": "积分商城兑换失败返还",
			"3": "积分调整",
			"4": "修改课后点评",
		};
		const reasonText = reasonMap[form.changeType];
		filtered = filtered.filter((row) => row.reason === reasonText);
	}

	// 4. 开始日期：不为空时，变动时间 >= 开始日期
	if (form.startDate) {
		filtered = filtered.filter((row) => row.changeTime >= form.startDate);
	}

	// 5. 结束日期：不为空时，变动时间 <= 结束日期
	if (form.endDate) {
		filtered = filtered.filter((row) => row.changeTime <= form.endDate);
	}

	// 更新表格为筛选后的数据
	tabdata.value.rows = filtered;
};
onMounted(() => {
	try {
		getPointsRecordList().then((res) => {
			console.log("res", res);
			tabdata.value.rows = res.data || [];
			// 保存原始数据
			originalRows.value = res.data || [];
		});
	} catch (error) {
		console.log(error);
	}
});
const refresh = () => {
	getPointsRecordList().then((res) => {
		console.log("res", res);
		tabdata.value.rows = res.data || [];
		originalRows.value = res.data || [];
	});
};
const clear = () => {
	console.log("清空筛选条件");
	// 重置form里的所有筛选字段
	Object.assign(form, {
		student: "",
		phone: "",
		changeType: "",
		startDate: "",
		endDate: "",
	});
	// 恢复原始数据
	tabdata.value.rows = originalRows.value;
};
const print = () => {
	printRef.value?.handlePrint();
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
.text {
	margin: 20px 0;
	color: #909399;
	font-size: 14px;
	line-height: 1.5;
}
</style>
