<template>
	<div class="salary-page">
		<el-alert v-if="store.error" class="error-alert" type="error" :closable="false" :title="store.error" />

		<el-row :gutter="12">
			<el-col :span="6">
				<OrgTreePanel :data="store.orgTree" :loading="store.loading.org" :selected-id="store.selectedOrgId" @select="handleSelectOrg" />
			</el-col>
			<el-col :span="18">
				<el-card shadow="never">
					<div class="salary-toolbar">
						<div />
						<div class="toolbar-icons">
							<el-tooltip content="刷新" placement="top">
								<el-button circle @click="handleRefresh">
									<el-icon><Refresh /></el-icon>
								</el-button>
							</el-tooltip>
							<el-tooltip content="打印" placement="top">
								<el-button circle @click="handlePrint">
									<el-icon><Printer /></el-icon>
								</el-button>
							</el-tooltip>
							<el-tooltip content="自定义列" placement="top">
								<el-button circle @click="handleColumnConfig">
									<el-icon><Grid /></el-icon>
								</el-button>
							</el-tooltip>
						</div>
					</div>

					<el-table v-loading="store.loading.list" :data="store.list" border>
						<el-table-column type="index" label="序号" width="60" />
						<el-table-column prop="teacherName" label="姓名/电话" min-width="200">
							<template #default="scope">
								<div>{{ scope.row.teacherName }}</div>
								<div class="sub-text">{{ scope.row.phone }}</div>
							</template>
						</el-table-column>
						<el-table-column prop="orgName" label="所属机构" min-width="240" />
						<el-table-column label="薪资设置" min-width="260">
							<template #default="scope">
								<div class="salary-summary">
									<span class="salary-mode">{{ scope.row.salaryMode }}</span>
									<span class="salary-detail">{{ getSalarySummary(scope.row) }}</span>
								</div>
							</template>
						</el-table-column>
						<el-table-column label="操作" width="120" fixed="right">
							<template #default="scope">
								<el-button link type="primary" @click="openEdit(scope.row)">修改</el-button>
							</template>
						</el-table-column>
					</el-table>

					<div class="pagination-wrap">
						<el-pagination
							background
							layout="total, sizes, prev, pager, next"
							:total="store.total"
							:current-page="store.page"
							:page-size="store.pageSize"
							:page-sizes="[10, 20, 50]"
							@current-change="handlePageChange"
							@size-change="handlePageSizeChange"
						/>
					</div>
				</el-card>
			</el-col>
		</el-row>

		<el-dialog v-model="editVisible" title="薪资设置" width="1020px">
			<el-form ref="editFormRef" :model="editForm" :rules="rules" label-width="120px">
				<el-form-item label="员工姓名">
					<div class="name-text">{{ editingRow?.teacherName || "" }}</div>
				</el-form-item>
				<el-form-item label="薪资模式" prop="salaryMode" required>
					<el-radio-group v-model="editForm.salaryMode">
						<el-radio label="非底薪模式">非底薪模式</el-radio>
						<el-radio label="底薪模式">底薪模式</el-radio>
					</el-radio-group>
				</el-form-item>

				<div v-if="editForm.salaryMode === '底薪模式'" class="base-salary-block">
					<el-form-item label="底薪" prop="baseSalary" required>
						<el-input-number v-model="editForm.baseSalary" :min="0" :step="100" class="full-width" />
						<span class="unit-text">元/月</span>
					</el-form-item>
					<el-form-item label="达标课时数" prop="targetLessonCount" required>
						<el-input-number v-model="editForm.targetLessonCount" :min="0" :step="10" class="full-width" />
					</el-form-item>
					<div class="desc-text">若开启系统配置老师上课数达标后才有课时费，则上完达标课时数后才统计课时费。</div>
				</div>

				<div class="section-title-wrap">
					<div class="line"></div>
					<div class="section-title">课时费设置</div>
					<div class="line"></div>
					<el-button class="add-btn" @click="handleAddFeeRow">添加</el-button>
				</div>

				<el-table :data="editForm.lessonFeeSettings" border empty-text="暂无数据">
					<el-table-column label="课时时长(分钟)" min-width="180">
						<template #default="scope">
							<el-select v-model="scope.row.duration" placeholder="请选择">
								<el-option label="60分钟" value="60分钟" />
								<el-option label="90分钟" value="90分钟" />
								<el-option label="120分钟" value="120分钟" />
							</el-select>
						</template>
					</el-table-column>
					<el-table-column label="课时费(元)" min-width="160">
						<template #default="scope">
							<el-input-number v-model="scope.row.lessonFee" :min="0" :step="10" class="full-width" />
						</template>
					</el-table-column>
					<el-table-column label="助教费(元)" min-width="160">
						<template #default="scope">
							<el-input-number v-model="scope.row.assistFee" :min="0" :step="10" class="full-width" />
						</template>
					</el-table-column>
					<el-table-column label="操作" width="100">
						<template #default="scope">
							<el-button link type="danger" @click="handleRemoveFeeRow(scope.$index)">删除</el-button>
						</template>
					</el-table-column>
				</el-table>
			</el-form>
			<template #footer>
				<el-button @click="handleCancelEdit">取消</el-button>
				<el-button type="primary" :loading="store.loading.update" @click="handleSubmitEdit">提交</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { onMounted, ref } from "vue";
import { ElMessage, type FormInstance, type FormRules } from "element-plus";
import OrgTreePanel from "@/components/org/employee/OrgTreePanel.vue";
import { useSalarySettingsStore } from "@/stores/org/salarySettings";
import type { LessonFeeSetting, SalaryRow, SalaryUpdatePayload } from "@/apis/org/salarySettings";
import { Grid, Printer, Refresh } from "@element-plus/icons-vue";

const store = useSalarySettingsStore();
const editVisible = ref(false);
const editingRow = ref<SalaryRow | null>(null);
const editFormRef = ref<FormInstance>();
const DRAFT_KEY = "salary-settings-edit-draft:v1";
const editForm = ref<SalaryUpdatePayload>({
	id: "",
	salaryMode: "非底薪模式",
	baseSalary: 0,
	targetLessonCount: 0,
	trialLessonPay: 0,
	lessonDuration: "60分钟",
	lessonBonus: 0,
	performancePay: 0,
	lessonFeeSettings: [],
});

const rules: FormRules = {
	salaryMode: [{ required: true, message: "请选择薪资模式", trigger: "change" }],
	baseSalary: [{ required: true, message: "请输入底薪", trigger: "change" }],
	targetLessonCount: [{ required: true, message: "请输入达标课时数", trigger: "change" }],
	trialLessonPay: [{ required: true, message: "请输入试听课时薪资", trigger: "change" }],
	lessonDuration: [{ required: true, message: "请选择课时时长", trigger: "change" }],
	lessonBonus: [{ required: true, message: "请输入课时提成", trigger: "change" }],
	performancePay: [{ required: true, message: "请输入绩效薪资", trigger: "change" }],
};

onMounted(async () => {
	await store.initPage();
});

async function handleSelectOrg(orgId: string) {
	await store.setOrgAndQuery(orgId);
}

async function handlePageChange(page: number) {
	await store.setPage(page);
}

async function handlePageSizeChange(size: number) {
	await store.setPageSize(size);
}

function openEdit(row: SalaryRow) {
	editingRow.value = row;
	editForm.value = {
		id: row.id,
		salaryMode: row.salaryMode,
		baseSalary: row.baseSalary,
		targetLessonCount: row.targetLessonCount,
		trialLessonPay: row.trialLessonPay,
		lessonDuration: row.lessonDuration,
		lessonBonus: row.lessonBonus,
		performancePay: row.performancePay,
		lessonFeeSettings: row.lessonFeeSettings.map((i) => ({ ...i })),
	};
	restoreDraft(row.id);
	editVisible.value = true;
}

function handleCancelEdit() {
	saveDraft();
	editVisible.value = false;
}

function saveDraft() {
	if (!editingRow.value) return;
	try {
		localStorage.setItem(`${DRAFT_KEY}:${editingRow.value.id}`, JSON.stringify(editForm.value));
	} catch {
		// ignore
	}
}

function restoreDraft(id: string) {
	try {
		const raw = localStorage.getItem(`${DRAFT_KEY}:${id}`);
		if (!raw) return;
		editForm.value = JSON.parse(raw);
		ElMessage.info("已恢复上次未提交的编辑内容");
	} catch {
		// ignore
	}
}

function clearDraft(id: string) {
	try {
		localStorage.removeItem(`${DRAFT_KEY}:${id}`);
	} catch {
		// ignore
	}
}

async function handleSubmitEdit() {
	try {
		const firstFee = editForm.value.lessonFeeSettings[0];
		if (!firstFee) return ElMessage.warning("请至少添加一条课时费设置");
		editForm.value.lessonDuration = firstFee.duration;
		editForm.value.trialLessonPay = firstFee.lessonFee;
		editForm.value.lessonBonus = firstFee.assistFee;
		await editFormRef.value?.validate();
		await store.updateRow(editForm.value);
		if (editingRow.value) clearDraft(editingRow.value.id);
		editVisible.value = false;
		ElMessage.success("薪资设置修改成功");
	} catch (e) {
		const err = e as Error;
		ElMessage.error(err?.message || "修改失败");
	}
}

function handleAddFeeRow() {
	const row: LessonFeeSetting = {
		id: `tmp-${Date.now()}`,
		duration: "60分钟",
		lessonFee: 0,
		assistFee: 0,
	};
	editForm.value.lessonFeeSettings.push(row);
}

function handleRemoveFeeRow(index: number) {
	editForm.value.lessonFeeSettings.splice(index, 1);
}

function getSalarySummary(row: SalaryRow) {
	if (row.salaryMode === "底薪模式") {
		return `底薪${row.baseSalary}/月，达标${row.targetLessonCount}课时，课时费${row.trialLessonPay}/${row.lessonDuration}`;
	}
	return `非底薪模式，课时费${row.trialLessonPay}/${row.lessonDuration}`;
}

async function handleRefresh() {
	await store.fetchList();
	ElMessage.success("已刷新");
}

function handlePrint() {
	window.print();
}

function handleColumnConfig() {
	ElMessage.info("自定义列功能暂未接入");
}
</script>

<style scoped>
.salary-page {
	padding: 0 8px 12px;
}

.error-alert {
	margin-bottom: 12px;
}

.sub-text {
	color: #909399;
	font-size: 12px;
}

.pagination-wrap {
	margin-top: 12px;
	display: flex;
	justify-content: flex-end;
}

.full-width {
	width: 100%;
}

.salary-toolbar {
	display: flex;
	align-items: center;
	justify-content: space-between;
	margin-bottom: 8px;
}

.toolbar-icons {
	display: flex;
	align-items: center;
	gap: 8px;
}

.salary-summary {
	display: flex;
	flex-direction: column;
	gap: 4px;
}

.salary-mode {
	font-weight: 600;
}

.salary-detail {
	color: #909399;
	font-size: 12px;
}

.name-text {
	font-size: 24px;
	font-weight: 500;
	color: #606266;
}

.unit-text {
	margin-left: 10px;
	color: #909399;
}

.base-salary-block {
	padding: 0 0 8px;
}

.desc-text {
	margin: -6px 0 12px 120px;
	color: #909399;
	font-size: 13px;
}

.section-title-wrap {
	display: flex;
	align-items: center;
	margin: 14px 0 10px;
}

.line {
	flex: 1;
	height: 1px;
	background: #ebeef5;
}

.section-title {
	margin: 0 20px;
	color: #606266;
	font-size: 24px;
}

.add-btn {
	margin-left: 16px;
}
</style>

