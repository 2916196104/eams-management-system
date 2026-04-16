<template>
	<div class="system-param">
		<div class="legacy-panel">
			<aside class="param-sidebar" v-loading="paramStore.categoriesLoading">
				<el-scrollbar class="sidebar-scroll">
					<div class="category-list">
						<div class="category-group-label">参数分类</div>
						<button
							v-for="category in paramStore.categories"
							:key="category.id"
							type="button"
							class="category-item"
							:class="{ active: paramStore.currentCategoryId === category.id }"
							@click="handleSelectCategory(category.id)"
						>
							{{ category.name }}
						</button>
						<el-empty v-if="paramStore.categories.length === 0" description="暂无参数分类" :image-size="72" />
					</div>
				</el-scrollbar>
			</aside>

			<section class="param-content">
				<div class="content-category-title">{{ currentCategory?.name ?? "参数设置" }}</div>
				<div class="content-header">
					<div class="header-cell">设置项</div>
					<div class="header-cell">设置值</div>
				</div>

				<div v-loading="paramStore.optionsLoading" class="content-body">
					<template v-if="currentCategory && optionRows.length > 0">
						<div
							v-for="row in optionRows"
							:key="row.option.id"
							class="option-row"
							:class="{ saving: savingIds.has(row.option.id) }"
						>
							<div class="option-meta">
								<div class="option-name">{{ row.displayName }}</div>
								<p v-for="line in row.infoLines" :key="line" class="option-info">{{ line }}</p>
							</div>

							<div class="option-editor">
								<el-switch
									v-if="getOptionEditorKind(row.option) === 'switch'"
									:model-value="toSwitchValue(row.option.value)"
									:loading="savingIds.has(row.option.id)"
									@change="(value) => handleSwitchChange(row.option, value)"
								/>

								<el-input
									v-else
									v-model="draftValues[row.option.id]"
									:disabled="savingIds.has(row.option.id)"
									clearable
									@keyup.enter="handleInputSave(row.option)"
									@blur="handleInputSave(row.option)"
								/>
							</div>
						</div>
					</template>

					<el-empty v-else-if="currentCategory" description="当前分类暂无参数项" :image-size="88" />
					<el-empty v-else description="请选择左侧参数分类" :image-size="88" />
				</div>
			</section>
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, watch } from "vue";
import { ElMessage } from "element-plus";
import { useSystemParamStore, type ParamOption } from "@/stores/systemParam";
import { buildOptionMeta, getOptionEditorKind, normalizeSubmitValue } from "./systemParam.utils";

const paramStore = useSystemParamStore();

const draftValues = reactive<Record<number, string>>({});
const savingIds = reactive(new Set<number>());

const currentCategory = computed(() => {
	return paramStore.categories.find((item) => item.id === paramStore.currentCategoryId) ?? null;
});

const optionRows = computed(() => {
	return paramStore.options.map((option) => ({
		option,
		...buildOptionMeta(option),
	}));
});

watch(
	() => paramStore.options,
	(options) => {
		for (const key of Object.keys(draftValues)) {
			delete draftValues[Number(key)];
		}

		for (const option of options) {
			draftValues[option.id] = String(option.value ?? "");
		}
	},
	{ immediate: true },
);

function toSwitchValue(value: boolean | number | string) {
	if (typeof value === "boolean") {
		return value;
	}

	return String(value) === "1" || String(value).toLowerCase() === "true";
}

async function persistOption(option: ParamOption, rawValue: string | boolean) {
	const nextValue = normalizeSubmitValue(option, rawValue);
	if (nextValue === option.value) {
		return;
	}

	savingIds.add(option.id);
	const success = await paramStore.saveOption({
		...option,
		value: nextValue,
	});
	savingIds.delete(option.id);

	if (success) {
		ElMessage.success("保存成功");
		return;
	}

	draftValues[option.id] = String(option.value ?? "");
	ElMessage.error("保存失败，请检查接口或稍后重试");
}

async function handleSelectCategory(categoryId: number) {
	const success = await paramStore.selectCategory(categoryId);
	if (!success) {
		ElMessage.error("参数项加载失败，请检查接口配置");
	}
}

async function handleSwitchChange(option: ParamOption, value: string | number | boolean) {
	await persistOption(option, Boolean(value));
}

async function handleInputSave(option: ParamOption) {
	await persistOption(option, draftValues[option.id] ?? "");
}

onMounted(async () => {
	const success = await paramStore.fetchCategories();
	if (!success) {
		ElMessage.error("系统参数加载失败，请检查接口配置");
	}
});
</script>

<style scoped lang="scss">
.system-param {
	height: 100%;
	padding: 8px 12px 12px;
	box-sizing: border-box;
	background: #f3f5f8;
}

.legacy-panel {
	display: grid;
	grid-template-columns: 340px minmax(0, 1fr);
	height: 100%;
	background: #fff;
	border: 1px solid #dfe6ee;
	overflow: hidden;
}

.param-sidebar {
	display: flex;
	flex-direction: column;
	min-width: 0;
	border-right: 1px solid #dfe6ee;
	background: #fff;
}

.sidebar-scroll {
	flex: 1;
	min-height: 0;
}

.category-list {
	padding: 18px 0 26px;
}

.category-group-label {
	padding: 0 38px 14px;
	font-size: 13px;
	line-height: 1.2;
	font-weight: 600;
	letter-spacing: 0.08em;
	color: #98a2b3;
}

.category-item {
	display: block;
	width: 100%;
	padding: 14px 38px;
	border: 0;
	background: transparent;
	text-align: left;
	font-size: 17px;
	line-height: 1.35;
	color: #303133;
	cursor: pointer;

	&:hover {
		background: #f7fbff;
	}

	&.active {
		color: #409eff;
		background: #fff;
	}
}

.param-content {
	display: flex;
	flex-direction: column;
	min-width: 0;
	background: #fff;
}

.content-category-title {
	padding: 24px 34px 10px;
	font-size: 20px;
	line-height: 1.2;
	font-weight: 500;
	color: #409eff;
}

.content-header {
	display: grid;
	grid-template-columns: minmax(380px, 1fr) minmax(300px, 44%);
	padding: 0 18px;
	border-bottom: 1px solid #dfe6ee;
	background: #fff;
}

.header-cell {
	padding: 16px 16px 14px;
	font-size: 15px;
	font-weight: 600;
	color: #909399;
}

.content-body {
	flex: 1;
	min-height: 0;
	overflow: auto;
	padding: 0 18px 16px;
}

.option-row {
	display: grid;
	grid-template-columns: minmax(380px, 1fr) minmax(300px, 44%);
	align-items: center;
	min-height: 62px;
	border-bottom: 1px solid #e8edf3;

	&.saving {
		background: #fafcff;
	}
}

.option-meta {
	padding: 12px 16px 12px 2px;
	color: #303133;
}

.option-name {
	font-size: 15px;
	line-height: 1.55;
	color: #303133;
	word-break: break-all;
}

.option-info {
	margin: 0;
	font-size: 14px;
	line-height: 1.55;
	color: #606266;
	word-break: break-all;
}

.option-editor {
	display: flex;
	align-items: center;
	min-width: 0;
	padding: 12px 0;

	:deep(.el-input),
	:deep(.el-input__wrapper) {
		width: 100%;
	}

	:deep(.el-input__wrapper) {
		border-radius: 4px;
	}
}

@media (max-width: 1080px) {
	.legacy-panel {
		grid-template-columns: 260px minmax(0, 1fr);
	}

	.content-header,
	.option-row {
		grid-template-columns: minmax(260px, 1fr) minmax(220px, 42%);
	}
}

@media (max-width: 820px) {
	.system-param {
		padding: 8px;
	}

	.legacy-panel {
		grid-template-columns: 1fr;
		height: auto;
	}

	.param-sidebar {
		border-right: 0;
		border-bottom: 1px solid #dfe6ee;
	}

	.content-header,
	.option-row {
		grid-template-columns: 1fr;
	}

	.content-header {
		padding-bottom: 0;
	}

	.header-cell:last-child {
		display: none;
	}

	.option-editor {
		padding: 0 0 14px;
	}
}
</style>
