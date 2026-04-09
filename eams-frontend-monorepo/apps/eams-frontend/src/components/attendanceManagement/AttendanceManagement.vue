<template>
	<el-dialog v-model="visible" :title="title" width="80%" :close-on-click-modal="false">
		<!-- 提示文字 -->
		<div v-if="tip" class="tip">
			{{ tip }}
		</div>
		<!-- 按钮区域 -->
		<div v-if="actions?.length" class="toolbar">
			<el-button
				v-for="(btn, index) in actions"
				:key="index"
				:type="btn.type || 'default'"
				@click="btn.onClick(selectedRows)"
			>
				{{ btn.label }}
			</el-button>
		</div>

		<!-- 表格 -->
		<el-table :data="tableData" style="width: 100%" @selection-change="handleSelectionChange">
			<!-- 多选 -->
			<el-table-column type="selection" width="50" />

			<!-- 动态列 -->
			<el-table-column v-for="(col, index) in columns" :key="index" :prop="col.prop" :label="col.label" />

			<!-- 操作列（插槽） -->
			<el-table-column v-if="$slots.action" label="操作">
				<template #default="scope">
					<slot name="action" :row="scope.row" />
				</template>
			</el-table-column>
		</el-table>
		<!-- 底部 -->
		<template #footer>
			<el-button @click="visible = false">关闭</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { ref, watch } from "vue";
import type ActionItem from "./type";

/** Props */
const props = defineProps({
	modelValue: Boolean,
	title: {
		type: String,
		default: "点名管理",
	},
	tip: String,
	tableData: {
		type: Array,
		default: () => [],
	},
	columns: {
		type: Array as () => { label: string; prop: string }[],
		default: () => [],
	},
	actions: {
		type: Array as () => ActionItem[],
		default: () => [],
	},
});

/** emits */
const emit = defineEmits(["selection-change"]);

/** 弹窗控制 */
const visible = ref(false);

/** 选中数据 */
const selectedRows = ref<any[]>([]);

const handleSelectionChange = (rows: any[]) => {
	selectedRows.value = rows;
	emit("selection-change", rows);
};
const showDialog = () => {
	visible.value = true;
};
defineExpose({
	showDialog,
});
</script>

<style scoped>
.tip {
	font-size: 13px;
	color: #666;
	margin-bottom: 12px;
}

.toolbar {
	margin-bottom: 12px;
	display: flex;
	gap: 10px;
	flex-wrap: wrap;
}
</style>
