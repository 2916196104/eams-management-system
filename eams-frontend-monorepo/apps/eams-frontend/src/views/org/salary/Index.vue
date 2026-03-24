<template>
	<div class="salary-page">
		<el-alert v-if="store.error" class="error-alert" type="error" :closable="false" :title="store.error" />

		<el-row :gutter="12">
			<el-col :span="6">
				<OrgTreePanel :data="store.orgTree" :loading="store.loading.org" :selected-id="store.selectedOrgId" @select="handleSelectOrg" />
			</el-col>
			<el-col :span="18">
				<el-card shadow="never">
					<el-table v-loading="store.loading.list" :data="store.list" border>
						<el-table-column type="index" label="序号" width="60" />
						<el-table-column prop="teacherName" label="姓名/电话" min-width="180">
							<template #default="scope">
								<div>{{ scope.row.teacherName }}</div>
								<div class="sub-text">{{ scope.row.phone }}</div>
							</template>
						</el-table-column>
						<el-table-column prop="salaryMode" label="薪资模式" min-width="120" />
						<el-table-column prop="baseSalary" label="底薪" min-width="90" />
						<el-table-column prop="trialLessonPay" label="试听课时薪资" min-width="120" />
						<el-table-column prop="lessonDuration" label="课时时长" min-width="100" />
						<el-table-column prop="lessonBonus" label="课时提成" min-width="90" />
						<el-table-column prop="performancePay" label="绩效薪资" min-width="90" />
						<el-table-column label="操作" width="90" fixed="right">
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

		<el-dialog v-model="editVisible" title="修改薪资设置" width="620px">
			<el-form ref="editFormRef" :model="editForm" :rules="rules" label-width="110px">
				<el-form-item label="老师姓名">
					<el-input :model-value="editingRow?.teacherName || ''" disabled />
				</el-form-item>
				<el-form-item label="薪资模式" prop="salaryMode" required>
					<el-select v-model="editForm.salaryMode" class="full-width">
						<el-option label="非底薪模式" value="非底薪模式" />
						<el-option label="底薪模式" value="底薪模式" />
					</el-select>
				</el-form-item>
				<el-form-item label="底薪" prop="baseSalary" required>
					<el-input-number v-model="editForm.baseSalary" :min="0" :step="100" class="full-width" />
				</el-form-item>
				<el-form-item label="试听课时薪资" prop="trialLessonPay" required>
					<el-input-number v-model="editForm.trialLessonPay" :min="0" :step="10" class="full-width" />
				</el-form-item>
				<el-form-item label="课时时长" prop="lessonDuration" required>
					<el-select v-model="editForm.lessonDuration" class="full-width">
						<el-option label="60分钟" value="60分钟" />
						<el-option label="90分钟" value="90分钟" />
						<el-option label="120分钟" value="120分钟" />
					</el-select>
				</el-form-item>
				<el-form-item label="课时提成" prop="lessonBonus" required>
					<el-input-number v-model="editForm.lessonBonus" :min="0" :step="10" class="full-width" />
				</el-form-item>
				<el-form-item label="绩效薪资" prop="performancePay" required>
					<el-input-number v-model="editForm.performancePay" :min="0" :step="10" class="full-width" />
				</el-form-item>
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
import type { SalaryRow, SalaryUpdatePayload } from "@/apis/org/salarySettings";

const store = useSalarySettingsStore();
const editVisible = ref(false);
const editingRow = ref<SalaryRow | null>(null);
const editFormRef = ref<FormInstance>();
const DRAFT_KEY = "salary-settings-edit-draft:v1";
const editForm = ref<SalaryUpdatePayload>({
	id: "",
	salaryMode: "非底薪模式",
	baseSalary: 0,
	trialLessonPay: 0,
	lessonDuration: "60分钟",
	lessonBonus: 0,
	performancePay: 0,
});

const rules: FormRules = {
	salaryMode: [{ required: true, message: "请选择薪资模式", trigger: "change" }],
	baseSalary: [{ required: true, message: "请输入底薪", trigger: "change" }],
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
		trialLessonPay: row.trialLessonPay,
		lessonDuration: row.lessonDuration,
		lessonBonus: row.lessonBonus,
		performancePay: row.performancePay,
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
		await editFormRef.value?.validate();
		await store.updateRow(editForm.value);
		if (editingRow.value) clearDraft(editingRow.value.id);
		editVisible.value = false;
		ElMessage.success("薪资设置修改成功");
	} catch (e: any) {
		ElMessage.error(e?.message || "修改失败");
	}
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
</style>

