<template>
	<section>
		<el-card>
			<template #header>
				<div class="card-header">
					<span>MyDetailDialog 课时明细示例</span>
					<el-button type="primary" @click="openDialog">查看课时明细</el-button>
				</div>
			</template>
			<el-text type="info">
				本示例演示如何使用
				<code>MyDetailDialog</code>
				组件以弹窗表格形式展示课时明细数据。
			</el-text>
		</el-card>

		<my-detail-dialog ref="detailDialogRef" title="课时明细" :columns="columns" :data="rows" />
	</section>
</template>

<script setup lang="ts">
import { ref } from "vue";
import MyDetailDialog from "@/components/mydetaildialog/MyDetailDialog.vue";
import type { MyDetailDialogColumn } from "@/components/mydetaildialog/type";

interface CourseDetail {
	courseName: string;
	duration: string;
	mainCount: number;
	assistCount: number;
	totalCount: number;
	mainFee: number;
	assistFee: number;
	mainAmount: number;
	assistAmount: number;
	totalAmount: number;
}

const detailDialogRef = ref<any>();

const columns: MyDetailDialogColumn[] = [
	{ prop: "courseName", label: "课程", align: "left", minWidth: "180px" },
	{ prop: "duration", label: "时长", minWidth: "80px" },
	{ prop: "mainCount", label: "上课课时数", minWidth: "100px" },
	{ prop: "assistCount", label: "助教课时数", minWidth: "100px" },
	{ prop: "totalCount", label: "课时总数", minWidth: "80px" },
	{ prop: "mainFee", label: "单节上课费", minWidth: "100px" },
	{ prop: "assistFee", label: "单节助教费", minWidth: "100px" },
	{ prop: "mainAmount", label: "上课费小计", minWidth: "100px" },
	{ prop: "assistAmount", label: "助教费小计", minWidth: "100px" },
	{ prop: "totalAmount", label: "合计", minWidth: "80px" },
];

const rows: CourseDetail[] = [
	{
		courseName: "2025·KET考冲班-第1期",
		duration: "120分钟",
		mainCount: 2,
		assistCount: 0,
		totalCount: 2,
		mainFee: 300,
		assistFee: 0,
		mainAmount: 600,
		assistAmount: 0,
		totalAmount: 600,
	},
];

function openDialog() {
	detailDialogRef.value?.openDialog();
}
</script>

<style scoped>
.card-header {
	display: flex;
	align-items: center;
	justify-content: space-between;
}
</style>
