<template>
	<el-popover
		:visible="showPopover"
		placement="bottom"
		:width="limit === 1 ? 400 : 700"
		trigger="click"
		@update:visible="showPopover = $event"
	>
		<template #reference>
			<el-input
				:model-value="displayLabel"
				:placeholder="placeholder"
				readonly
				:disabled="disabled"
				clearable
				@clear="handleClear"
			/>
		</template>

		<!-- 选择器内容插槽 -->
		<slot name="selector" :condition="condition" @submit="handleSubmit" />
	</el-popover>
</template>

<script setup lang="ts">
import { ref, computed, watch } from "vue";
import { ElPopover, ElInput } from "element-plus";
import type { CuiSelectBoxProps, CuiSelectBoxEmits } from "./types";

const props = withDefaults(defineProps<CuiSelectBoxProps>(), {
	limit: 0,
	disabled: false,
	placeholder: "请选择",
	condition: () => ({}),
});

const emit = defineEmits<CuiSelectBoxEmits>();

const showPopover = ref(false);
const displayLabel = ref("");

/* 监听 modelValue 变化 */
watch(
	() => props.modelValue,
	(newVal) => {
		if (!newVal || (Array.isArray(newVal) && newVal.length === 0)) {
			displayLabel.value = "";
		}
	},
	{ immediate: true },
);

const handleSubmit = (selectedItems: any[]) => {
	const values = selectedItems.map((item) => item.id);
	const result = props.limit === 1 ? values[0] : values.join(",");

	emit("update:modelValue", result);
	emit("submit", result);
	showPopover.value = false;

	/* 更新显示标签 */
	displayLabel.value = selectedItems.map((item) => item.label).join(", ");
};

const handleClear = () => {
	emit("update:modelValue", props.limit === 1 ? "" : "");
	displayLabel.value = "";
};
</script>
