<template>
	<div class="org-manage-page">
		<el-alert v-if="store.error" class="error-alert" type="error" :closable="false" :title="store.error" />
		<el-card shadow="never">
			<el-table
				ref="tableRef"
				v-loading="store.loading"
				:data="store.tree"
				row-key="id"
				border
				:tree-props="{ children: 'children' }"
				:default-expand-all="false"
			>
				<el-table-column prop="name" label="机构名称" min-width="220" />
				<el-table-column prop="fullName" label="全称" min-width="300" />
				<el-table-column prop="level" label="级别" min-width="90" />
				<el-table-column prop="contact" label="联系人" min-width="90" />
				<el-table-column prop="phone" label="电话" min-width="140" />
				<el-table-column label="操作" min-width="220" fixed="right">
					<template #default="scope">
						<el-button link type="primary" @click="openAdd(scope.row)">添加子机构</el-button>
						<el-button link type="primary" @click="openEdit(scope.row)">编辑</el-button>
						<el-button link type="primary" @click="handleDelete(scope.row)">删除</el-button>
						<el-button link type="primary" @click="handleView(scope.row)">查看</el-button>
					</template>
				</el-table-column>
			</el-table>
		</el-card>

		<el-dialog v-model="editVisible" :title="dialogTitle" width="760px" @close="handleCloseDialog">
			<el-form ref="formRef" :model="formModel" :rules="rules" label-width="100px">
				<el-form-item label="机构名" prop="name" required><el-input v-model="formModel.name" /></el-form-item>
				<el-form-item label="级别" prop="level" required>
					<el-select v-model="formModel.level" class="full-width">
						<el-option label="机构" value="机构" />
						<el-option label="分校" value="分校" />
					</el-select>
				</el-form-item>
				<el-form-item label="简称"><el-input v-model="formModel.shortName" /></el-form-item>
				<el-form-item label="联系人"><el-input v-model="formModel.contact" /></el-form-item>
				<el-form-item label="电话"><el-input v-model="formModel.phone" /></el-form-item>
				<el-form-item label="传真"><el-input v-model="formModel.fax" /></el-form-item>
				<el-form-item label="邮箱"><el-input v-model="formModel.email" /></el-form-item>
				<el-form-item label="排序"><el-input-number v-model="formModel.sortNo" :min="0" class="full-width" /></el-form-item>
				<el-form-item label="状态"><el-switch v-model="formModel.enabled" /></el-form-item>
				<el-form-item label="说明"><el-input v-model="formModel.desc" type="textarea" :rows="4" /></el-form-item>
			</el-form>
			<template #footer>
				<el-button @click="handleCloseDialog">取消</el-button>
				<el-button type="primary" :loading="store.submitting" @click="handleSubmit">提交</el-button>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, ref } from "vue";
import { ElMessage, ElMessageBox, type FormInstance, type FormRules } from "element-plus";
import { useOrgManageStore } from "@/stores/org/orgManage";
import type { OrgEditPayload, OrgManageNode } from "@/apis/org/orgManage";

const store = useOrgManageStore();
const tableRef = ref();
const editVisible = ref(false);
const mode = ref<"add" | "edit">("add");
const currentRow = ref<OrgManageNode | null>(null);
const DRAFT_KEY = "org-manage-form-draft:v1";
const formRef = ref<FormInstance>();
const formModel = ref<OrgEditPayload>({
	id: "",
	parentId: "",
	name: "",
	level: "分校",
	shortName: "",
	contact: "",
	phone: "",
	fax: "",
	email: "",
	sortNo: 0,
	enabled: true,
	desc: "",
});

const rules: FormRules = {
	name: [{ required: true, message: "请输入机构名", trigger: "blur" }],
	level: [{ required: true, message: "请选择级别", trigger: "change" }],
};

const dialogTitle = computed(() => (mode.value === "add" ? "新增子机构" : "修改机构信息"));

onMounted(async () => {
	await store.initPage();
});

function openAdd(row: OrgManageNode) {
	mode.value = "add";
	currentRow.value = row;
	formModel.value = { parentId: row.id, name: "", level: "分校", shortName: "", contact: "", phone: "", fax: "", email: "", sortNo: 0, enabled: true, desc: "" };
	restoreDraft("add");
	editVisible.value = true;
}

function openEdit(row: OrgManageNode) {
	mode.value = "edit";
	currentRow.value = row;
	formModel.value = {
		id: row.id,
		parentId: row.parentId,
		name: row.name,
		level: row.level,
		shortName: row.shortName || "",
		contact: row.contact || "",
		phone: row.phone || "",
		fax: row.fax || "",
		email: row.email || "",
		sortNo: row.sortNo || 0,
		enabled: row.enabled,
		desc: row.desc || "",
	};
	restoreDraft(`edit:${row.id}`);
	editVisible.value = true;
}

async function handleDelete(row: OrgManageNode) {
	try {
		await ElMessageBox.confirm(`确定删除机构【${row.name}】吗？`, "提示", { type: "warning" });
		await store.removeNode(row.id);
		ElMessage.success("删除成功");
	} catch {
		// cancel
	}
}

function handleView(row: OrgManageNode) {
	ElMessage.info(`机构：${row.fullName}`);
}

function handleCloseDialog() {
	const key = mode.value === "add" ? "add" : `edit:${formModel.value.id}`;
	saveDraft(key);
	editVisible.value = false;
}

function saveDraft(key: string) {
	try {
		localStorage.setItem(`${DRAFT_KEY}:${key}`, JSON.stringify(formModel.value));
	} catch {
		// ignore
	}
}

function restoreDraft(key: string) {
	try {
		const raw = localStorage.getItem(`${DRAFT_KEY}:${key}`);
		if (!raw) return;
		formModel.value = JSON.parse(raw);
		ElMessage.info("已恢复上次未提交表单");
	} catch {
		// ignore
	}
}

function clearDraft(key: string) {
	try {
		localStorage.removeItem(`${DRAFT_KEY}:${key}`);
	} catch {
		// ignore
	}
}

async function handleSubmit() {
	try {
		await formRef.value?.validate();
		if (mode.value === "add") {
			await store.addNode(formModel.value);
			clearDraft("add");
		} else {
			await store.editNode(formModel.value);
			clearDraft(`edit:${formModel.value.id}`);
		}
		editVisible.value = false;
		ElMessage.success("提交成功");
	} catch (e: any) {
		ElMessage.error(e?.message || "提交失败");
	}
}
</script>

<style scoped>
.org-manage-page {
	padding: 0 8px 12px;
}

.error-alert {
	margin-bottom: 12px;
}

.full-width {
	width: 100%;
}
</style>

