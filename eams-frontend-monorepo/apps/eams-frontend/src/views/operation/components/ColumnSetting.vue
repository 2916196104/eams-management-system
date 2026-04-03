<template>
	<el-dialog
		v-model="dialogVisible"
		title="自定义显示列"
		width="600px"
		:close-on-click-modal="false"
		@close="handleClose"
	>
		<div class="column-setting-content">
			<div class="column-list">
				<div v-for="(item, index) in columnOptions" :key="item.prop" class="column-item">
					<el-checkbox v-model="item.visible" :label="item.label" @change="handleColumnChange" />
				</div>
			</div>
		</div>
		<template #footer>
			<div class="dialog-footer">
				<el-button @click="handleReset">恢复</el-button>
				<el-button type="primary" @click="handleConfirm">确认</el-button>
			</div>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { ref, watch, computed } from "vue";

// 列配置项类型
export interface ColumnOption {
	label: string;
	prop: string;
	visible: boolean;
}

// Props 定义
interface Props {
	modelValue: boolean;
	// 所有可选列配置
	columns: ColumnOption[];
}

const props = defineProps<Props>();
const emit = defineEmits<{
	"update:modelValue": [value: boolean];
	change: [columns: ColumnOption[]];
	confirm: [columns: ColumnOption[]];
	reset: [];
}>();

// 弹窗显示状态
const dialogVisible = computed({
	get: () => props.modelValue,
	set: (val) => emit("update:modelValue", val),
});

// 本地列配置副本（避免直接修改父组件数据）
const columnOptions = ref<ColumnOption[]>([]);

// 监听 columns 变化，同步到本地副本
watch(
	() => props.columns,
	(newVal) => {
		columnOptions.value = JSON.parse(JSON.stringify(newVal));
	},
	{ immediate: true },
);

// 列勾选变化
const handleColumnChange = () => {
	emit("change", columnOptions.value);
};

// 恢复默认列
const handleReset = () => {
	emit("reset");
};

// 确认保存
const handleConfirm = () => {
	emit("confirm", columnOptions.value);
	dialogVisible.value = false;
};

// 关闭弹窗
const handleClose = () => {
	dialogVisible.value = false;
};
</script>

<style scoped>
.column-setting-content {
	padding: 16px 0;
}
.column-list {
	display: grid;
	grid-template-columns: repeat(3, 1fr);
	gap: 20px 16px;
}
.column-item {
	display: flex;
	align-items: center;
	font-size: 20px;
}
.dialog-footer {
	display: flex;
	justify-content: flex-end;
	gap: 16px;
}
</style>
