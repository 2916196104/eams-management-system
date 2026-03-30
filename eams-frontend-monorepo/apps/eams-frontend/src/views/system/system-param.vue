<template>
	<div class="system-param">
		<!-- 搜索区域 -->
		<MySearch :model="searchForm" :items="searchItems" formtitle="系统参数查询" @do-search="handleSearch">
			<template #footer>
				<div class="toolbar-right">
					<el-tooltip content="刷新" placement="top">
						<el-button link :icon="Refresh" @click="handleRefresh">刷新</el-button>
					</el-tooltip>
				</div>
			</template>
		</MySearch>

		<!-- 主体内容：左右分栏 -->
		<div class="param-layout">
			<!-- 左侧：设置分类列表 -->
			<div class="param-categories">
				<div class="categories-header">
					<span>参数分类</span>
				</div>
				<el-scrollbar v-loading="paramStore.categoriesLoading">
					<div class="categories-list">
						<div
							v-for="category in filteredCategories"
							:key="category.id"
							class="category-card"
							:class="{ active: paramStore.currentCategoryId === category.id }"
							@click="handleSelectCategory(category.id)"
						>
							<div class="category-name">{{ category.name }}</div>
							<div class="category-code">{{ category.code }}</div>
							<div v-if="category.remark" class="category-remark">{{ category.remark }}</div>
						</div>
						<el-empty v-if="filteredCategories.length === 0" description="暂无分类" :image-size="60" />
					</div>
				</el-scrollbar>
			</div>

			<!-- 右侧：参数选项表格 -->
			<div class="param-options">
				<div class="options-header">
					<span>{{ currentCategoryName }} - 参数配置</span>
				</div>
				<el-scrollbar v-loading="paramStore.optionsLoading">
					<div class="options-list">
						<el-table :data="paramStore.options" border stripe style="width: 100%">
							<el-table-column prop="name" label="参数名称" width="180" />
							<el-table-column prop="code" label="参数编码" width="180" />
							<el-table-column prop="info" label="描述" min-width="150" show-overflow-tooltip />
							<el-table-column prop="valueType" label="值类型" width="80" />
							<el-table-column label="参数值" min-width="200">
								<template #default="{ row }">
									<template v-if="editingId === row.id">
										<el-input
											v-model="editValue"
											size="small"
											style="width: 140px; margin-right: 8px"
											@keyup.enter="handleSaveOption(row)"
										/>
										<el-button type="primary" size="small" @click="handleSaveOption(row)">保存</el-button>
										<el-button size="small" @click="handleCancelEdit">取消</el-button>
									</template>
									<template v-else>
										<span>{{ row.value }}</span>
										<el-button type="primary" link size="small" style="margin-left: 8px" @click="handleStartEdit(row)">
											编辑
										</el-button>
									</template>
								</template>
							</el-table-column>
						</el-table>
						<el-empty v-if="paramStore.options.length === 0" description="暂无参数配置" :image-size="80" />
					</div>
				</el-scrollbar>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, computed, onMounted } from "vue";
import { ElMessage } from "element-plus";
import { Refresh } from "@element-plus/icons-vue";
import MySearch from "@/components/mysearch/MySearch.vue";
import type { MyFormItemAttr } from "@/components/myform/type";
import { useSystemParamStore, type ParamOption } from "@/stores/systemParam";

const paramStore = useSystemParamStore();

// ==================== 搜索表单 ====================

const searchForm = reactive({
	name: "",
});

const searchItems: MyFormItemAttr[] = [
	{
		prop: "name",
		label: "分类名称",
		type: "input",
		fprops: {
			placeholder: "请输入分类名称",
			clearable: true,
		},
	},
];

// ==================== 分类过滤 ====================

const filteredCategories = computed(() => {
	const keyword = searchForm.name.trim().toLowerCase();
	if (!keyword) return paramStore.categories;
	return paramStore.categories.filter((item) => item.name.toLowerCase().includes(keyword));
});

const currentCategoryName = computed(() => {
	const current = paramStore.categories.find((item) => item.id === paramStore.currentCategoryId);
	return current?.name ?? "未选择";
});

// ==================== 行内编辑 ====================

const editingId = ref<number | null>(null);
const editValue = ref<string | number>("");

function handleStartEdit(row: ParamOption) {
	editingId.value = row.id;
	editValue.value = row.value;
}

function handleCancelEdit() {
	editingId.value = null;
	editValue.value = "";
}

async function handleSaveOption(row: ParamOption) {
	const success = await paramStore.saveOption({
		...row,
		value: editValue.value,
	});
	if (success) {
		ElMessage.success("保存成功");
		handleCancelEdit();
	}
}

// ==================== 事件处理 ====================

function handleSearch() {
	// 搜索通过 computed 过滤，无需额外操作
}

function handleRefresh() {
	paramStore.fetchCategories();
}

function handleSelectCategory(categoryId: number) {
	handleCancelEdit();
	paramStore.selectCategory(categoryId);
}

// ==================== 生命周期 ====================

onMounted(() => {
	paramStore.fetchCategories();
});
</script>

<style scoped lang="scss">
.system-param {
	padding: 16px;
	height: 100%;
	display: flex;
	flex-direction: column;
}

.toolbar-right {
	display: flex;
	gap: 8px;
	align-items: center;
}

.param-layout {
	flex: 1;
	display: flex;
	gap: 16px;
	margin-top: 16px;
	min-height: 0;
}

.param-categories {
	width: 260px;
	flex-shrink: 0;
	display: flex;
	flex-direction: column;
	border: 1px solid var(--el-border-color-light);
	border-radius: 8px;
	overflow: hidden;
}

.categories-header {
	padding: 12px 16px;
	font-weight: 600;
	font-size: 15px;
	border-bottom: 1px solid var(--el-border-color-light);
	background-color: var(--el-fill-color-light);
}

.categories-list {
	padding: 8px;
}

.category-card {
	padding: 12px;
	border-radius: 6px;
	cursor: pointer;
	transition: all 0.2s;
	margin-bottom: 4px;

	&:hover {
		background-color: var(--el-fill-color-light);
	}

	&.active {
		background-color: var(--el-color-primary-light-9);
		border-left: 3px solid var(--el-color-primary);
	}

	.category-name {
		font-weight: 500;
		font-size: 14px;
		margin-bottom: 4px;
	}

	.category-code {
		font-size: 12px;
		color: var(--el-text-color-secondary);
		font-family: monospace;
	}

	.category-remark {
		font-size: 12px;
		color: var(--el-text-color-placeholder);
		margin-top: 4px;
	}
}

.param-options {
	flex: 1;
	min-width: 0;
	display: flex;
	flex-direction: column;
	border: 1px solid var(--el-border-color-light);
	border-radius: 8px;
	overflow: hidden;
}

.options-header {
	padding: 12px 16px;
	font-weight: 600;
	font-size: 15px;
	border-bottom: 1px solid var(--el-border-color-light);
	background-color: var(--el-fill-color-light);
}

.options-list {
	padding: 16px;
	flex: 1;
}
</style>
