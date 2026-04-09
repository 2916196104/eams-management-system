<template>
	<el-popover
		placement="bottom-start"
		trigger="click"
		v-model:visible="visible"
		:width="panelWidth + 20"
		popper-class="full-width-popover"
	>
		<div class="panel" :style="{ width: `${panelWidth}px` }">
			<div class="search-wrapper">
				<div class="search-fields">
					<div v-for="item in visibleFields" :key="item.prop" class="search-item">
						<span class="label">{{ item.label }}</span>

						<el-input
							v-if="item.component === 'input' || !item.component"
							v-model="query[item.prop]"
							:placeholder="item.placeholder || '请输入'"
							clearable
						/>

						<el-select
							v-else-if="item.component === 'select'"
							v-model="query[item.prop]"
							:placeholder="item.placeholder || '请选择'"
							clearable
						>
							<el-option v-for="opt in item.options" :key="opt.value" :label="opt.label" :value="opt.value" />
						</el-select>

						<el-date-picker
							v-else-if="item.component === 'date'"
							v-model="query[item.prop]"
							type="date"
							value-format="YYYY-MM-DD"
							:placeholder="item.placeholder || '请选择'"
							style="width: 100%"
						/>
					</div>
				</div>

				<div class="actions">
					<el-link v-if="needFieldExpand" type="primary" :underline="false" @click="fieldExpanded = !fieldExpanded">
						{{ fieldExpanded ? "收起" : "展开" }}
						<el-icon class="actions__chevron">
							<ArrowUp v-if="fieldExpanded" />
							<ArrowDown v-else />
						</el-icon>
					</el-link>

					<el-tooltip content="查询" placement="top">
						<el-button link type="primary" class="filter-toolbar__icon-btn" @click="emitSearch">
							<el-icon :size="18"><Search /></el-icon>
						</el-button>
					</el-tooltip>

					<el-tooltip content="重置" placement="top">
						<el-button link @click="resetInnerQuery">
							<el-icon :size="18"><CircleClose /></el-icon>
						</el-button>
					</el-tooltip>
				</div>
			</div>

			<el-table :data="data" :height="tableHeight" v-loading="loading" :fit="true">
				<el-table-column v-for="col in columns" :key="col.prop" :label="col.label" :prop="col.prop" />

				<el-table-column label="操作" fixed="right">
					<template #default="{ row }">
						<el-button link type="primary" @click="choose(row)">选择</el-button>
					</template>
				</el-table-column>
			</el-table>

			<div v-if="total !== undefined" class="pagination">
				<el-pagination
					v-model:current-page="page"
					v-model:page-size="pageSize"
					background
					:layout="paginationLayout"
					:page-sizes="pageSizes"
					:total="total"
					@current-change="emitSearch"
					@size-change="onPageSizeChange"
				/>
			</div>
		</div>

		<template #reference>
			<el-input
				:model-value="modelValue"
				:placeholder="placeholder"
				readonly
				clearable
				class="trigger-input"
				@clear="onClearTrigger"
			>
				<template #suffix>
					<el-icon class="trigger-input__icon"><ArrowDown /></el-icon>
				</template>
			</el-input>
		</template>
	</el-popover>
</template>

<script setup lang="ts">
import { computed, type PropType, reactive, ref, watch } from "vue";
import type { SearchField, TableColumn } from "./type";
import { ArrowDown, ArrowUp, CircleClose, Search } from "@element-plus/icons-vue";
const SEARCH_FIELD_EXPAND_THRESHOLD = 1;

/** 使用运行时 props + `default`，避免 `withDefaults` 在部分工具链下未注入宏全局声明的问题。 */
const props = defineProps({
	modelValue: String,
	placeholder: { type: String, default: "请选择" },
	displayProp: String,
	searchFields: { type: Array as PropType<SearchField[]>, required: true },
	columns: { type: Array as PropType<TableColumn[]>, required: true },
	data: { type: Array as PropType<any[]>, required: true },
	total: Number,
	loading: Boolean,
	width: { type: Number, default: 720 },
	pageSizes: { type: Array as PropType<number[]>, default: () => [10, 20, 50, 100] },
	defaultPageSize: { type: Number, default: 20 },
	multiple: Boolean,
});

const emit = defineEmits<{
	search: [payload: Record<string, any> & { page: number; pageSize: number }];
	select: [row: any];
	"update:modelValue": [value: string];
}>();

const visible = ref(false);
const fieldExpanded = ref(false);

const page = ref(1);
const pageSize = ref(props.defaultPageSize);

const query = reactive<Record<string, any>>({});

const panelWidth = computed(() => props.width ?? 720);

const tableHeight = 280;

const paginationLayout = "total, sizes, prev, pager, next";

watch(
	() => props.searchFields,
	(fields: SearchField[]) => {
		for (const f of fields) {
			if (query[f.prop] === undefined) {
				query[f.prop] = "";
			}
		}
	},
	{ immediate: true, deep: true },
);

const needFieldExpand = computed(() => props.searchFields.length > SEARCH_FIELD_EXPAND_THRESHOLD);

const visibleFields = computed(() => {
	if (!needFieldExpand.value) {
		return props.searchFields;
	}
	return fieldExpanded.value ? props.searchFields : props.searchFields.slice(0, SEARCH_FIELD_EXPAND_THRESHOLD);
});

function displayTextFromRow(row: any): string {
	const key = props.displayProp ?? props.columns[0]?.prop;
	if (!key) {
		return "";
	}
	const v = row?.[key];
	return v != null ? String(v) : "";
}

function emitSearch() {
	emit("search", {
		...query,
		page: page.value,
		pageSize: pageSize.value,
	});
}

function onPageSizeChange() {
	page.value = 1;
	emitSearch();
}

function resetInnerQuery() {
	for (const f of props.searchFields) {
		query[f.prop] = "";
	}
	page.value = 1;
	emitSearch();
}

function choose(row: any) {
	emit("update:modelValue", displayTextFromRow(row));
	emit("select", row);
	visible.value = false;
}

function onClearTrigger() {
	emit("update:modelValue", "");
}

watch(visible, (open: boolean) => {
	if (open) {
		emitSearch();
	}
});
</script>

<style scoped>
.panel {
	width: 760px; /* 固定宽度，保证表格有足够空间 */
	max-width: 96vw;
	padding: 4px 0 0;
	box-sizing: border-box;
}

.search-wrapper {
	display: flex;
	align-items: flex-start;
	gap: 12px;
	margin-bottom: 12px;
}

.search-fields {
	display: flex;
	flex-direction: column;
	gap: 12px;
	flex: 1;
	min-width: 0;
}

.search-item {
	display: flex;
	align-items: center;
	gap: 8px;
	min-width: 0; /* 必须！防止输入框撑开父容器 */
}

.label {
	flex-shrink: 0;
	color: #606266;
	font-size: 13px;
	min-width: 72px;
	text-align: right;
	white-space: nowrap;
}

.label::after {
	content: " ";
}

.search-item :deep(.el-input),
.search-item :deep(.el-select),
.search-item :deep(.el-date-editor) {
	flex: 1;
	min-width: 0;
}

.actions {
	display: flex;
	align-items: center;
	gap: 8px;
	flex-shrink: 0;
	padding-top: 2px;
}

.pagination {
	display: flex;
	justify-content: flex-end;
	margin-top: 12px;
}

.trigger-input {
	cursor: pointer;
}

.trigger-input :deep(.el-input__inner) {
	cursor: pointer;
}
/* 穿透 el-popover 的 popper 容器，强制最小宽度 = panelWidth */
:deep(.full-width-popover) {
	min-width: 760px !important; /* 和你的 panelWidth 保持一致 */
	width: auto !important;
}
</style>
