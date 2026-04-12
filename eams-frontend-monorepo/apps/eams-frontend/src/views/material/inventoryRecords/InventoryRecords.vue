<template>
	<section class="material-page">
		<FilterToolbar
			:collapsible-item-count="6"
			:collapse-threshold="4"
			@search="handleSearch"
			@reset="handleReset"
			@refresh="handleRefresh"
			@print="handlePrint"
			@column-setting="handleColumnSetting"
		>
			<template #left="{ showAll, limit }">
				<div class="filter-grid">
					<div v-show="showAll || 0 < limit" class="filter-cell">
						<span class="filter-label">选择物料</span>
						<SelectTablePopover
							v-model="form.materialLabel"
							display-prop="name"
							:search-fields="materialSearchFields"
							:columns="materialColumns"
							:data="materialPickerRows"
							:total="materialPickerTotal"
							:loading="materialPickerLoading"
							@search="loadMaterialPicker"
							@select="onMaterialSelect"
						/>
					</div>

					<div v-show="showAll || 1 < limit" class="filter-cell">
						<span class="filter-label">涉及学生</span>
						<SelectTablePopover
							v-model="form.studentName"
							display-prop="name"
							:search-fields="studentSearchFields"
							:columns="studentColumns"
							:data="studentPickerRows"
							:total="studentPickerTotal"
							:loading="studentPickerLoading"
							@search="loadStudentPicker"
							@select="onStudentSelect"
							:width="500"
						/>
					</div>

					<div v-show="showAll || 2 < limit" class="filter-cell">
						<span class="filter-label">申请员工</span>
						<SelectTablePopover
							v-model="form.employeeName"
							display-prop="name"
							:search-fields="employeeSearchFields"
							:columns="employeeColumns"
							:data="employeePickerRows"
							:total="employeePickerTotal"
							:loading="employeePickerLoading"
							@search="loadEmployeePicker"
							@select="onEmployeeSelect"
							:width="500"
						/>
					</div>

					<div v-show="showAll || 3 < limit" class="filter-cell">
						<span class="filter-label">变动类型</span>
						<el-select v-model="form.changeType" placeholder="请选择" clearable style="width: 100%">
							<el-option label="入库" :value="1" />
							<el-option label="出库" :value="2" />
							<el-option label="调整" :value="3" />
						</el-select>
					</div>

					<div v-show="showAll || 4 < limit" class="filter-cell">
						<span class="filter-label">开始日期</span>
						<el-date-picker
							v-model="form.beginDate"
							type="date"
							value-format="YYYY-MM-DD"
							placeholder="请选择"
							style="width: 100%"
						/>
					</div>

					<div v-show="showAll || 5 < limit" class="filter-cell">
						<span class="filter-label">结束日期</span>
						<el-date-picker
							v-model="form.endDate"
							type="date"
							value-format="YYYY-MM-DD"
							placeholder="请选择"
							style="width: 100%"
						/>
					</div>
				</div>
			</template>
		</FilterToolbar>

		<section class="table-card">
			<el-table v-loading="tableLoading" :data="tableRows" border stripe row-key="id">
				<!-- 根据列配置动态生成列 -->
				<el-table-column
					v-for="(col, idx) in visibleColumns"
					:key="idx"
					:label="col.label"
					:prop="col.prop"
					:min-width="col.minWidth || 100"
					:width="col.width || undefined"
					show-overflow-tooltip
				>
					<template #default="{ row }" v-if="col.prop === 'changeQty'">
						<span :class="Number(row.changeQty) < 0 ? 'qty-neg' : 'qty-pos'">
							{{ Number(row.changeQty) > 0 ? `+${row.changeQty}` : String(row.changeQty ?? "") }}
						</span>
					</template>
					<template #default="{ row }" v-if="col.prop === 'changeType'">
						{{ row.changeType === 1 ? "入库" : row.changeType === 2 ? "出库" : "调整" }}
					</template>
				</el-table-column>
			</el-table>
		</section>

		<!-- 打印组件 -->
		<PrintTable ref="printRef" print-title="物料出入库记录表" :column-list="allColumns" :table-data="tableRows" />

		<!-- 列配置组件 -->
		<ColumnSetting
			v-model="columnSettingVisible"
			:columns="allColumns"
			@change="handleColumnChange"
			@confirm="handleColumnConfirm"
			@reset="handleColumnReset"
		/>
	</section>
</template>

<script setup lang="ts">
import { reactive, ref, onMounted, computed } from "vue";
import { ElMessage } from "element-plus";
import FilterToolbar from "@/views/material/components/FilterToolbar.vue";
import SelectTablePopover from "@/views/material/components/SelectTablePopover.vue";
import type { SearchField, TableColumn } from "@/views/material/components/type";
import { getMaterialList } from "@/apis/material/materialManagement/index.ts";
import type { MaterialRecordItem } from "@/apis/material/materialManagement/type";

// 引入你项目里的打印 + 列配置
import ColumnSetting from "../../operation/components/ColumnSetting.vue";
import PrintTable from "../../operation/components/PrintTable.vue";

// 表单数据
const form = reactive({
	materialId: "" as string | number,
	materialLabel: "",
	studentId: "" as string | number,
	studentName: "",
	employeeId: "" as string | number,
	employeeName: "",
	changeType: "" as number | "",
	beginDate: "",
	endDate: "",
});

// ==============================================
// 物料/学生/员工选择器（你原有代码不动）
// ==============================================
const materialSearchFields: SearchField[] = [
	{ label: "物料名称", prop: "name", component: "input", placeholder: "请输入" },
	{ label: "分类", prop: "category", component: "input", placeholder: "请输入" },
];
const materialColumns: TableColumn[] = [
	{ label: "物料名称", prop: "name", minWidth: 120 },
	{ label: "库存量", prop: "stock", width: 80 },
];
const materialPickerRows = ref<any[]>([]);
const materialPickerTotal = ref(0);
const materialPickerLoading = ref(false);

const studentSearchFields: SearchField[] = [{ label: "学员姓名/电话", prop: "keyword", component: "input" }];
const studentColumns: TableColumn[] = [
	{ label: "学员姓名", prop: "name" },
	{ label: "分校", prop: "branch" },
	{ label: "阶段", prop: "stage" },
];
const studentPickerRows = ref<any[]>([]);
const studentPickerTotal = ref(0);
const studentPickerLoading = ref(false);

const employeeSearchFields: SearchField[] = [{ label: "姓名", prop: "name", component: "input" }];
const employeeColumns: TableColumn[] = [
	{ label: "姓名", prop: "name" },
	{ label: "职位", prop: "position" },
];
const employeePickerRows = ref<any[]>([]);
const employeePickerTotal = ref(0);
const employeePickerLoading = ref(false);

// 模拟接口
function mockMaterialApi() {
	return { total: 3, rows: [{ id: 1, name: "水", stock: 200 }] };
}
function mockStudentApi() {
	return { total: 3, rows: [{ id: 1, name: "小明" }] };
}
function mockEmployeeApi() {
	return { total: 3, rows: [{ id: 1, name: "张三" }] };
}

async function loadMaterialPicker() {
	materialPickerLoading.value = true;
	const res = mockMaterialApi();
	materialPickerRows.value = res.rows;
	materialPickerLoading.value = false;
}
async function loadStudentPicker() {
	studentPickerLoading.value = true;
	const res = mockStudentApi();
	studentPickerRows.value = res.rows;
	studentPickerLoading.value = false;
}
async function loadEmployeePicker() {
	employeePickerLoading.value = true;
	const res = mockEmployeeApi();
	employeePickerRows.value = res.rows;
	employeePickerLoading.value = false;
}

function onMaterialSelect(row: any) {
	form.materialId = row.id;
	form.materialLabel = row.name;
}
function onStudentSelect(row: any) {
	form.studentId = row.id;
	form.studentName = row.name;
}
function onEmployeeSelect(row: any) {
	form.employeeId = row.id;
	form.employeeName = row.name;
}

// ==============================================
// ✅ 列配置（新增）
// ==============================================
const columnSettingVisible = ref(false);
const allColumns = ref([
	{ label: "序号", prop: "index", width: 60, visible: true },
	{ label: "物料名", prop: "materialName", minWidth: 120, visible: true },
	{ label: "变动数量", prop: "changeQty", width: 100, visible: true },
	{ label: "申请员工", prop: "employeeName", minWidth: 100, visible: true },
	{ label: "涉及学生", prop: "studentName", minWidth: 100, visible: true },
	{ label: "变动类型", prop: "changeType", width: 100, visible: true },
	{ label: "原因", prop: "reason", minWidth: 140, visible: true },
	{ label: "备注", prop: "remark", minWidth: 140, visible: true },
	{ label: "变动时间", prop: "changeTime", minWidth: 165, visible: true },
]);

// 计算属性：显示的列
const visibleColumns = computed(() => {
	return allColumns.value.filter((c) => c.visible);
});

// 列配置事件
const handleColumnSetting = () => {
	columnSettingVisible.value = true;
};
const handleColumnChange = (cols: any) => {
	allColumns.value = cols;
};
const handleColumnConfirm = (cols: any) => {
	allColumns.value = cols;
	localStorage.setItem("materialColumns", JSON.stringify(cols));
};
const handleColumnReset = () => {
	allColumns.value.forEach((c) => (c.visible = true));
};

// ==============================================
// ✅ 打印功能（新增）
// ==============================================
const printRef = ref();
const handlePrint = () => {
	printRef.value?.handlePrint();
};

// ==============================================
// 表格数据（你原有逻辑）
// ==============================================
const tableLoading = ref(false);
const tableRows = ref<any[]>([]);

function formatDisplayValue(prefix: string, value?: number | string | null) {
	if (value === undefined || value === null || value === "") return "-";
	return `${prefix}${value}`;
}

function normalizeRecordRows(rows: MaterialRecordItem[]) {
	return rows.map((item, index) => ({
		...item,
		index: index + 1,
		materialName: item.materialName ?? formatDisplayValue("物料#", item.materialId),
		changeQty: item.amount ?? 0,
		employeeName: item.staffName ?? formatDisplayValue("员工#", item.staffId),
		studentName:
			item.studentName ??
			(item.studentId === undefined || item.studentId === null ? "-" : formatDisplayValue("学生#", item.studentId)),
		changeTime: item.addTime ?? "",
		remark: item.remark ?? "-",
	}));
}

async function handleSearch() {
	tableLoading.value = true;
	try {
		const params = {
			pageIndex: 1,
			pageSize: 10,
			...(form.materialId && { materialId: +form.materialId }),
			...(form.studentId && { studentId: +form.studentId }),
			...(form.employeeId && { staffId: +form.employeeId }),
			...(form.changeType && { changeType: form.changeType }),
		};
		const res = await getMaterialList(params);
		let rows = normalizeRecordRows(res.data?.rows || []);
		if (form.beginDate) {
			rows = rows.filter((row) => String(row.changeTime || "").slice(0, 10) >= form.beginDate);
		}
		if (form.endDate) {
			rows = rows.filter((row) => String(row.changeTime || "").slice(0, 10) <= form.endDate);
		}
		tableRows.value = rows;
	} catch (err) {
		ElMessage.error("查询失败");
	} finally {
		tableLoading.value = false;
	}
}

function handleReset() {
	Object.assign(form, {
		materialId: "",
		materialLabel: "",
		studentId: "",
		studentName: "",
		employeeId: "",
		employeeName: "",
		changeType: "",
		beginDate: "",
		endDate: "",
	});
	handleSearch();
	ElMessage.info("已重置");
}

function handleRefresh() {
	handleSearch();
}

onMounted(() => {
	// 读取本地保存的列配置
	const cache = localStorage.getItem("materialColumns");
	if (cache) allColumns.value = JSON.parse(cache);
	handleSearch();
});
</script>

<style scoped>
.material-page {
	padding: 16px;
}
.table-card {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
}
.qty-neg {
	color: var(--el-color-danger);
	font-weight: 500;
}
.qty-pos {
	color: var(--el-text-color-primary);
}
</style>
