<template>
	<el-form :inline="inline" :model="formData" class="cui-search">
		<!-- 基础搜索字段 -->
		<template v-for="field in basicFields" :key="field.prop">
			<el-form-item :label="field.label">
				<!-- 文本输入 -->
				<el-input
					v-if="field.type === 'input'"
					v-model="formData[field.prop]"
					:placeholder="field.placeholder"
					clearable
				/>

				<!-- 选择器 -->
				<el-select
					v-else-if="field.type === 'select'"
					v-model="formData[field.prop]"
					:placeholder="field.placeholder"
					clearable
				>
					<el-option v-for="option in field.options" :key="option.value" :label="option.label" :value="option.value" />
				</el-select>

				<!-- 日期选择器 -->
				<el-date-picker
					v-else-if="field.type === 'date'"
					v-model="formData[field.prop]"
					type="date"
					:placeholder="field.placeholder"
					clearable
				/>

				<!-- 日期范围选择器 -->
				<el-date-picker
					v-else-if="field.type === 'daterange'"
					v-model="formData[field.prop]"
					type="daterange"
					range-separator="至"
					start-placeholder="开始日期"
					end-placeholder="结束日期"
					clearable
				/>
			</el-form-item>
		</template>

		<!-- 高级搜索字段 -->
		<template v-if="hasAdvancedFields">
			<div v-show="!collapsible || advancedVisible" class="cui-search__advanced">
				<template v-for="field in advancedFields" :key="field.prop">
					<el-form-item :label="field.label">
						<!-- 文本输入 -->
						<el-input
							v-if="field.type === 'input'"
							v-model="formData[field.prop]"
							:placeholder="field.placeholder"
							clearable
						/>

						<!-- 选择器 -->
						<el-select
							v-else-if="field.type === 'select'"
							v-model="formData[field.prop]"
							:placeholder="field.placeholder"
							clearable
						>
							<el-option
								v-for="option in field.options"
								:key="option.value"
								:label="option.label"
								:value="option.value"
							/>
						</el-select>

						<!-- 日期选择器 -->
						<el-date-picker
							v-else-if="field.type === 'date'"
							v-model="formData[field.prop]"
							type="date"
							:placeholder="field.placeholder"
							clearable
						/>

						<!-- 日期范围选择器 -->
						<el-date-picker
							v-else-if="field.type === 'daterange'"
							v-model="formData[field.prop]"
							type="daterange"
							range-separator="至"
							start-placeholder="开始日期"
							end-placeholder="结束日期"
							clearable
						/>
					</el-form-item>
				</template>
			</div>
		</template>

		<!-- 操作按钮 -->
		<el-form-item>
			<el-button type="primary" @click="handleSearch">搜索</el-button>
			<el-button @click="handleReset">重置</el-button>
			<el-button v-if="hasAdvancedFields && collapsible" link @click="toggleAdvanced">
				{{ advancedVisible ? "收起" : "展开" }}
				<el-icon>
					<component :is="advancedVisible ? 'ArrowUp' : 'ArrowDown'" />
				</el-icon>
			</el-button>
		</el-form-item>
	</el-form>
</template>

<script setup lang="ts">
import { ref, computed, watch } from "vue";
import { ElForm, ElFormItem, ElInput, ElSelect, ElOption, ElDatePicker, ElButton, ElIcon } from "element-plus";
import { ArrowUp, ArrowDown } from "@element-plus/icons-vue";
import type { CuiSearchProps } from "./types";

/* 定义 Props */
const props = withDefaults(defineProps<CuiSearchProps>(), {
	inline: true,
	collapsible: true,
});

/* 定义 Emits */
const emit = defineEmits<{
	"update:modelValue": [value: Record<string, any>];
	search: [value: Record<string, any>];
	reset: [value: Record<string, any>];
}>();

/* 表单数据 */
const formData = ref<Record<string, any>>({ ...props.modelValue });

/* 高级搜索展开状态 */
const advancedVisible = ref(false);

/* 基础搜索字段 */
const basicFields = computed(() => props.fields.filter((field) => !field.advanced));

/* 高级搜索字段 */
const advancedFields = computed(() => props.fields.filter((field) => field.advanced));

/* 是否有高级搜索字段 */
const hasAdvancedFields = computed(() => advancedFields.value.length > 0);

/* 监听 modelValue 变化 */
watch(
	() => props.modelValue,
	(newValue) => {
		formData.value = { ...newValue };
	},
	{ deep: true },
);

/* 监听 formData 变化，同步到 modelValue */
watch(
	formData,
	(newValue) => {
		emit("update:modelValue", newValue);
	},
	{ deep: true },
);

/* 搜索按钮点击 */
const handleSearch = () => {
	emit("search", formData.value);
};

/* 重置按钮点击 */
const handleReset = () => {
	formData.value = {};
	emit("reset", {});
};

/* 切换高级搜索展开状态 */
const toggleAdvanced = () => {
	advancedVisible.value = !advancedVisible.value;
};

/* 启用属性继承以透传其他 ElForm 的 props */
defineOptions({
	inheritAttrs: false,
});
</script>
