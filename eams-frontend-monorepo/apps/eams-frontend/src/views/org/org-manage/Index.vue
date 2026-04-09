<template>
	<div class="org-manage-page">
		<el-card shadow="never" class="filter-card">
			<el-form :inline="true" class="filter-form" @submit.prevent="handleSearch">
				<el-form-item label="机构名称">
					<el-input v-model="filterOrgName" clearable placeholder="模糊查询" style="width: 200px" />
				</el-form-item>
				<el-form-item label="机构级别">
					<el-select v-model="filterOrgType" clearable placeholder="全部" style="width: 120px">
						<el-option label="集团" :value="1" />
						<el-option label="分校" :value="2" />
						<el-option label="部门" :value="3" />
					</el-select>
				</el-form-item>
				<el-form-item label="状态">
					<el-select v-model="filterStatus" clearable placeholder="全部" style="width: 120px">
						<el-option label="启用" :value="1" />
						<el-option label="禁用" :value="0" />
					</el-select>
				</el-form-item>
				<el-form-item>
					<el-button type="primary" @click="handleSearch">查询</el-button>
					<el-button @click="handleReset">重置</el-button>
					<el-button type="primary" plain @click="openAddRoot">新增顶级机构</el-button>
				</el-form-item>
			</el-form>
		</el-card>

		<el-card shadow="never">
			<el-table
				v-loading="store.loading"
				:data="store.tree"
				row-key="orgId"
				border
				:tree-props="{ children: 'children' }"
				default-expand-all
			>
				<el-table-column prop="orgName" label="机构名称" min-width="200" />
				<el-table-column prop="orgFullName" label="全称" min-width="280" show-overflow-tooltip />
				<el-table-column prop="orgTypeDesc" label="级别" min-width="90" />
				<el-table-column prop="contact" label="联系人" min-width="100" />
				<el-table-column prop="phone" label="电话" min-width="130" />
				<el-table-column label="操作" min-width="280" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="openAddChild(row)">添加子机构</el-button>
						<el-button link type="primary" @click="openEdit(row)">编辑</el-button>
						<el-button link type="danger" @click="handleDelete(row)">删除</el-button>
						<el-button link type="primary" @click="handleView(row)">查看</el-button>
					</template>
				</el-table-column>
			</el-table>
		</el-card>

		<el-dialog v-model="editVisible" :title="dialogTitle" width="780px" destroy-on-close @closed="resetForm">
			<el-form ref="formRef" :model="formModel" :rules="rules" label-width="110px">
				<el-form-item label="机构名称" prop="orgName" required>
					<el-input v-model="formModel.orgName" />
				</el-form-item>
				<el-form-item label="机构级别" prop="orgType" required>
					<el-select v-model="formModel.orgType" class="full-width">
						<el-option label="集团" :value="1" />
						<el-option label="分校" :value="2" />
						<el-option label="部门" :value="3" />
					</el-select>
				</el-form-item>
				<el-form-item label="父机构ID">
					<el-input :model-value="String(formModel.parentOrgId)" disabled />
				</el-form-item>
				<el-form-item label="简称">
					<el-input v-model="formModel.orgShortName" />
				</el-form-item>
				<el-form-item label="联系人">
					<el-input v-model="formModel.contact" />
				</el-form-item>
				<el-form-item label="电话">
					<el-input v-model="formModel.phone" />
				</el-form-item>
				<el-form-item label="传真">
					<el-input v-model="formModel.fax" />
				</el-form-item>
				<el-form-item label="邮箱">
					<el-input v-model="formModel.email" />
				</el-form-item>
				<el-form-item label="排序号">
					<el-input-number v-model="formModel.sortOrder" :min="0" class="full-width" />
				</el-form-item>
				<el-form-item label="状态">
					<el-radio-group v-model="formModel.status">
						<el-radio :label="1">启用</el-radio>
						<el-radio :label="0">禁用</el-radio>
					</el-radio-group>
				</el-form-item>
				<el-form-item label="说明">
					<el-input v-model="formModel.remark" type="textarea" :rows="3" />
				</el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="editVisible = false">取消</el-button>
				<el-button type="primary" :loading="store.submitting" @click="handleSubmit">保存</el-button>
			</template>
		</el-dialog>

		<el-dialog v-model="viewVisible" title="机构详情" width="640px" destroy-on-close>
			<div v-loading="store.detailLoading">
				<el-descriptions v-if="viewDetail" :column="1" border>
					<el-descriptions-item label="机构名称">{{ viewDetail.orgName }}</el-descriptions-item>
					<el-descriptions-item label="简称">{{ viewDetail.orgShortName || "—" }}</el-descriptions-item>
					<el-descriptions-item label="级别">{{ viewDetail.orgTypeDesc || "—" }}</el-descriptions-item>
					<el-descriptions-item label="父机构">{{ viewDetail.parentOrgName || viewDetail.parentOrgId }}</el-descriptions-item>
					<el-descriptions-item label="联系人">{{ viewDetail.contact || "—" }}</el-descriptions-item>
					<el-descriptions-item label="电话">{{ viewDetail.phone || "—" }}</el-descriptions-item>
					<el-descriptions-item label="传真">{{ viewDetail.fax || "—" }}</el-descriptions-item>
					<el-descriptions-item label="邮箱">{{ viewDetail.email || "—" }}</el-descriptions-item>
					<el-descriptions-item label="地区">{{ viewDetail.region || "—" }}</el-descriptions-item>
					<el-descriptions-item label="营业执照">{{ viewDetail.businessLicense || "—" }}</el-descriptions-item>
					<el-descriptions-item label="排序号">{{ viewDetail.sortOrder ?? "—" }}</el-descriptions-item>
					<el-descriptions-item label="状态">{{ viewDetail.statusDesc || "—" }}</el-descriptions-item>
					<el-descriptions-item label="说明">{{ viewDetail.remark || "—" }}</el-descriptions-item>
				</el-descriptions>
			</div>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, ref } from "vue";
import { ElMessage, ElMessageBox, type FormInstance, type FormRules } from "element-plus";
import { useOrgManageStore } from "@/stores/org/orgManage";
import type { OrgDetail, OrgSavePayload, OrgTreeRow } from "@/apis/org/orgManage";
import { toZhUserMessage } from "@/utils/apiError";

const store = useOrgManageStore();
const editVisible = ref(false);
const viewVisible = ref(false);
const viewDetail = ref<OrgDetail | null>(null);
const mode = ref<"add" | "edit">("add");
const formRef = ref<FormInstance>();

const filterOrgName = ref("");
const filterOrgType = ref<number | "">("");
const filterStatus = ref<number | "">("");

type FormModel = OrgSavePayload;

const emptyForm = (): FormModel => ({
	parentOrgId: 0,
	orgName: "",
	orgShortName: "",
	orgType: 2,
	contact: "",
	phone: "",
	email: "",
	fax: "",
	remark: "",
	sortOrder: 0,
	status: 1,
});

const formModel = ref<FormModel>(emptyForm());

const rules: FormRules = {
	orgName: [{ required: true, message: "请输入机构名称", trigger: "blur" }],
	orgType: [{ required: true, message: "请选择机构级别", trigger: "change" }],
};

const dialogTitle = computed(() => (mode.value === "add" ? "新增机构" : "编辑机构"));

onMounted(async () => {
	await store.initPage();
});

async function handleSearch() {
	store.setListQuery({
		orgName: filterOrgName.value.trim() || undefined,
		orgType: filterOrgType.value === "" ? undefined : Number(filterOrgType.value),
		status: filterStatus.value === "" ? undefined : Number(filterStatus.value),
	});
	await store.fetchTree();
}

async function handleReset() {
	filterOrgName.value = "";
	filterOrgType.value = "";
	filterStatus.value = "";
	store.setListQuery({});
	await store.fetchTree();
}

function mapDetailToForm(d: OrgDetail | undefined, row: OrgTreeRow): FormModel {
	const base = d ?? {};
	return {
		orgId: base.orgId ?? row.orgId,
		parentOrgId: base.parentOrgId ?? row.parentOrgId ?? 0,
		orgName: base.orgName ?? row.orgName ?? "",
		orgShortName: base.orgShortName ?? "",
		orgType: base.orgType ?? row.orgType ?? 2,
		contact: base.contact ?? row.contact ?? "",
		phone: base.phone != null ? String(base.phone) : (row.phone ?? ""),
		email: base.email ?? "",
		fax: base.fax ?? "",
		remark: base.remark ?? "",
		sortOrder: base.sortOrder ?? 0,
		status: base.status ?? 1,
	};
}

function openAddRoot() {
	mode.value = "add";
	formModel.value = { ...emptyForm(), parentOrgId: 0 };
	editVisible.value = true;
}

function openAddChild(row: OrgTreeRow) {
	if (row.orgId == null) return;
	mode.value = "add";
	formModel.value = { ...emptyForm(), parentOrgId: row.orgId };
	editVisible.value = true;
}

async function openEdit(row: OrgTreeRow) {
	if (row.orgId == null) return;
	mode.value = "edit";
	try {
		const d = await store.loadDetail(row.orgId);
		formModel.value = mapDetailToForm(d, row);
		editVisible.value = true;
	} catch {
		ElMessage.error("加载数据失败");
	}
}

async function handleView(row: OrgTreeRow) {
	if (row.orgId == null) return;
	viewDetail.value = null;
	viewVisible.value = true;
	try {
		viewDetail.value = (await store.loadDetail(row.orgId)) ?? null;
	} catch {
		ElMessage.error("加载数据失败");
		viewVisible.value = false;
	}
}

async function handleDelete(row: OrgTreeRow) {
	if (row.orgId == null) return;
	try {
		await ElMessageBox.confirm(`确定删除机构「${row.orgName}」吗？若存在子机构，后端将拒绝删除。`, "提示", { type: "warning" });
	} catch {
		return;
	}
	try {
		await store.removeNode(row.orgId);
		ElMessage.success("删除成功");
	} catch (e: unknown) {
		ElMessage.error(toZhUserMessage(e, "删除失败"));
	}
}

function resetForm() {
	formRef.value?.resetFields();
	formModel.value = emptyForm();
}

async function handleSubmit() {
	try {
		await formRef.value?.validate();
	} catch {
		return;
	}
	const m = formModel.value;
	const payload: OrgSavePayload = {
		orgName: m.orgName,
		orgType: m.orgType,
		parentOrgId: m.parentOrgId,
		orgShortName: m.orgShortName || undefined,
		contact: m.contact || undefined,
		phone: m.phone || undefined,
		email: m.email || undefined,
		fax: m.fax || undefined,
		remark: m.remark || undefined,
		sortOrder: m.sortOrder,
		status: m.status,
	};
	if (mode.value === "edit" && m.orgId != null) {
		payload.orgId = m.orgId;
	}
	try {
		await store.save(payload);
		editVisible.value = false;
		ElMessage.success("保存成功");
	} catch (e: unknown) {
		ElMessage.error(toZhUserMessage(e, "保存失败"));
	}
}
</script>

<style scoped>
.org-manage-page {
	padding: 0 8px 12px;
}

.filter-card {
	margin-bottom: 12px;
}

.filter-form {
	margin-bottom: 0;
}

.full-width {
	width: 100%;
}
</style>
