<template>
	<!-- 输入框 -->
	<el-input
		v-if="item.type === 'input'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@input="$emit('update:model', $event)"
	/>
	<!-- 数字输入框 -->
	<el-input-number
		v-else-if="item.type === 'number'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@change="$emit('update:model', $event)"
	/>
	<!-- 下拉选择框 -->
	<el-select
		v-else-if="item.type === 'select'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@change="$emit('update:model', $event)"
	>
		<el-option v-for="(option, index) in (item.fprops as MyFormSelectProps).options" :key="index" :="option" />
	</el-select>
	<!-- 日期选择器 -->
	<el-date-picker
		v-else-if="item.type === 'date'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@change="$emit('update:model', $event)"
	/>
	<!-- 复选框 -->
	<el-checkbox
		v-else-if="item.type === 'checkbox'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@change="$emit('update:model', $event)"
	/>
	<!-- 复选框组 -->
	<el-checkbox-group
		v-else-if="item.type === 'checkbox-group'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@change="$emit('update:model', $event)"
	>
		<el-checkbox
			v-for="(checkbox, index) in (item.fprops as MyFormCheckBoxGroupProps).checkboxes"
			:key="index"
			:style="{ width: item.fprops?.width }"
			:="checkbox"
		/>
	</el-checkbox-group>
	<!-- 单选框 -->
	<el-radio
		v-else-if="item.type === 'radio'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@change="$emit('update:model', $event)"
	/>
	<!-- 单选框组 -->
	<el-radio-group
		v-else-if="item.type === 'radio-group'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@change="$emit('update:model', $event)"
	>
		<el-radio
			v-for="(radio, index) in (item.fprops as MyFormRadioBoxGroupProps).radioboxes"
			:key="index"
			:style="{ width: item.fprops?.width }"
			:="radio"
		/>
	</el-radio-group>
	<!-- 级联选择器 -->
	<el-cascader
		v-else-if="item.type === 'cascader'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@change="$emit('update:model', $event)"
	/>
	<!-- 级联面板 -->
	<el-cascader-panel
		v-else-if="item.type === 'cascader-panel'"
		v-model="localmodel"
		:style="{ width: item.fprops?.width }"
		:="item.fprops"
		@change="$emit('update:model', $event)"
	/>
	<!-- //FIXME 扩充其他表单组件需要在这里扩展代码 -->
</template>

<script setup lang="ts">
import { ref, watch } from "vue";
import type { MyFormItemAttr, MyFormSelectProps, MyFormCheckBoxGroupProps, MyFormRadioBoxGroupProps } from "./type";

// 定义组件属性
const props = defineProps<{
	item: MyFormItemAttr;
	model: any;
}>();

// 使用本地状态代替props.model
const localmodel = ref(props.model);
// 监听props.model变化，保持本地状态同步
watch(
	() => props.model,
	(val) => {
		localmodel.value = val;
	},
);
</script>
<style scoped>
/* 解决内联模式宽度异常问题,设置一个默认宽度 */
.el-form--inline {
	.el-form-item {
		.el-input,
		.el-input-number,
		.el-select,
		.el-cascader,
		.el-autocomplete {
			width: 188px;
		}
	}
}
</style>
