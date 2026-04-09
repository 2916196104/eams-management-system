<template>
	<el-dialog v-model="visible" title="请款详情" width="600px" destroy-on-close>
		<el-form label-width="120px">
			<el-row :gutter="20">
				<el-col :span="12">
					<el-form-item label="请款项目">{{ form.project }}</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="款项类型">{{ form.type }}</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="申请人">{{ form.applicant }}</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="收款人">{{ form.receiver }}</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="请款金额">{{ form.amount }} 元</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="申请时间">{{ form.applyTime }}</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="收款账号">{{ form.account }}</el-form-item>
				</el-col>
				<el-col :span="24">
					<el-form-item label="请款说明">{{ form.remark }}</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="审核状态">{{ form.status }}</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="审核人">{{ form.auditor }}</el-form-item>
				</el-col>
				<el-col :span="12">
					<el-form-item label="审核时间">{{ form.auditTime }}</el-form-item>
				</el-col>
				<el-col :span="24">
					<el-form-item label="审核备注">{{ form.auditRemark }}</el-form-item>
				</el-col>
			</el-row>
		</el-form>

		<template #footer>
			<el-button type="primary" @click="visible = false">关闭</el-button>
		</template>
	</el-dialog>
</template>

<script setup>
import { ref } from "vue";

const visible = ref(false);

const form = ref({});

// 暴露方法给父组件打开弹窗
const open = (data = null) => {
	if (data) {
		form.value.project = data.title || "";
		form.value.type = data.typeName || "";
		form.value.applicant = data.creatorName || "";
		form.value.receiver = data.payeeName || "";
		form.value.amount = data.amount ?? null;
		form.value.applyTime = data.applyTime || "";
		form.value.account = data.account || "";
		form.value.remark = data.info || "";
		form.value.status =
			data.verifyState === 0
				? "待审核"
				: data.verifyState === 1
					? "审核通过"
					: data.verifyState === 2
						? "已驳回"
						: data.verifyState === 3
							? "已作废"
							: "未知";
		form.value.auditor = data.verifyStaff || "";
		form.value.auditTime = data.verifyTime || "";
		form.value.auditRemark = data.verifyRemark || "";
	}
	visible.value = true;
};

defineExpose({ open });
</script>

<style scoped>
.el-form-item {
	margin-bottom: 10px;
}
</style>
