<template>
	<div class="compact-range">
		<el-date-picker
			v-model="startModel"
			class="range-input"
			type="date"
			value-format="YYYY-MM-DD"
			placeholder="开始日期"
			:disabled="disabled"
			:size="size"
		/>
		<span class="range-sep">至</span>
		<el-date-picker
			v-model="endModel"
			class="range-input"
			type="date"
			value-format="YYYY-MM-DD"
			placeholder="结束日期"
			:disabled="disabled"
			:size="size"
		/>
	</div>
</template>

<script setup lang="ts">
import { computed } from "vue";
import { ElMessage } from "element-plus";

const props = withDefaults(
	defineProps<{
		startDate: string;
		endDate: string;
		disabled?: boolean;
		size?: "large" | "default" | "small";
	}>(),
	{
		disabled: false,
		size: "small",
	},
);

const emit = defineEmits<{
	(e: "change", payload: { startDate: string; endDate: string }): void;
}>();

const startModel = computed({
	get: () => props.startDate,
	set: (val: string) => {
		emitIfValid(val, props.endDate);
	},
});

const endModel = computed({
	get: () => props.endDate,
	set: (val: string) => {
		emitIfValid(props.startDate, val);
	},
});

function emitIfValid(startDate: string, endDate: string) {
	if (!startDate || !endDate) return;
	if (new Date(startDate).getTime() > new Date(endDate).getTime()) {
		ElMessage.warning("开始日期不能晚于结束日期");
		return;
	}
	emit("change", { startDate, endDate });
}
</script>

<style scoped>
.compact-range {
	display: flex;
	align-items: center;
	gap: 8px;
}

.range-input {
	width: 140px;
}

.range-sep {
	font-size: 12px;
	color: #606266;
}
</style>
