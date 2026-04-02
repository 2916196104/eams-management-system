<template>
	<div class="filter-toolbar">
		<div class="filter-toolbar__main">
			<div class="filter-toolbar__left">
				<div class="filter-toolbar__fields">
					<slot name="left" :show-all="expanded" :limit="collapseThreshold" />
				</div>

				<el-link
					v-if="showExpandToggle"
					type="primary"
					class="filter-toolbar__toggle"
					:underline="false"
					@click="expanded = !expanded"
				>
					{{ expanded ? "收起" : "展开" }}
					<el-icon class="filter-toolbar__toggle-icon">
						<ArrowUp v-if="expanded" />
						<ArrowDown v-else />
					</el-icon>
				</el-link>
			</div>

			<div class="filter-toolbar__right">
				<div class="filter-toolbar__primary-btns">
					<el-tooltip content="查询" placement="top">
						<el-button link type="primary" class="filter-toolbar__icon-btn" @click="emit('search')">
							<el-icon :size="12"><Search /></el-icon>
						</el-button>
					</el-tooltip>
					<span class="filter-toolbar__primary-divider" role="presentation" />
					<el-tooltip content="重置" placement="top">
						<el-button link type="primary" class="filter-toolbar__icon-btn" @click="emit('reset')">
							<el-icon :size="12"><CircleClose /></el-icon>
						</el-button>
					</el-tooltip>
				</div>

				<div v-if="showTableTools" class="filter-toolbar__secondary-btns">
					<el-tooltip content="刷新" placement="top">
						<el-button link type="primary" :icon="RefreshRight" @click="emit('refresh')" />
					</el-tooltip>
					<el-tooltip content="打印" placement="top">
						<el-button link type="primary" :icon="Printer" @click="emit('print')" />
					</el-tooltip>
					<el-tooltip content="列设置" placement="top">
						<el-button link type="primary" :icon="Grid" @click="emit('column-setting')" />
					</el-tooltip>
				</div>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, ref, watch } from "vue";
import { ArrowDown, ArrowUp, CircleClose, Grid, Printer, RefreshRight, Search } from "@element-plus/icons-vue";

const props = withDefaults(
	defineProps<{
		/** 参与「超过 4 条可展开」计数的筛选项数量（不含右侧按钮区） */
		collapsibleItemCount?: number;
		/** 收起时最多展示的筛选项个数 */
		collapseThreshold?: number;
		/** 是否展示刷新 / 打印 / 列设置 */
		showTableTools?: boolean;
	}>(),
	{
		collapsibleItemCount: 0,
		collapseThreshold: 4,
		showTableTools: true,
	},
);

const emit = defineEmits<{
	search: [];
	reset: [];
	refresh: [];
	print: [];
	"column-setting": [];
}>();

const expanded = ref(false);

const showExpandToggle = computed(() => props.collapsibleItemCount > props.collapseThreshold);

watch(
	() => props.collapsibleItemCount,
	(count) => {
		if (count <= props.collapseThreshold) {
			expanded.value = false;
		}
	},
);
</script>

<style scoped>
.filter-toolbar {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
	margin-bottom: 12px;
}

.filter-toolbar__main {
	display: flex;
	justify-content: space-between;
	align-items: flex-start;
	gap: 16px;
}

.filter-toolbar__left {
	flex: 1;
	display: flex;
	align-items: flex-start;
	gap: 12px;
	min-width: 0;
}

.filter-toolbar__fields {
	flex: 1;
	min-width: 0;
}

.filter-toolbar__fields :deep(.filter-grid) {
	display: grid;
	grid-template-columns: repeat(auto-fill, minmax(240px, 1fr));
	gap: 14px 20px;
	align-items: center;
}

.filter-toolbar__fields :deep(.filter-cell) {
	display: flex;
	align-items: center;
	gap: 8px;
	min-width: 0;
}

.filter-toolbar__fields :deep(.filter-label) {
	flex-shrink: 0;
	color: #303133;
	font-size: 14px;
	text-align: right;
	white-space: nowrap;
}

.filter-toolbar__fields :deep(.filter-label)::after {
	content: "：";
}

.filter-toolbar__toggle {
	flex-shrink: 0;
	display: inline-flex;
	align-items: center;
	gap: 2px;
	padding-top: 6px;
	font-size: 14px;
}

.filter-toolbar__toggle-icon {
	font-size: 14px;
}

.filter-toolbar__right {
	flex-shrink: 0;
	display: flex;
	flex-direction: column;
	align-items: flex-end;
	gap: 10px;
}

.filter-toolbar__primary-btns {
	display: inline-flex;
	align-items: center;
	gap: 0;
	padding: 2px 4px;
	border: 1px solid var(--el-border-color);
	border-radius: 4px;
	background: var(--el-fill-color-blank);
}

.filter-toolbar__primary-divider {
	align-self: stretch;
	width: 1px;
	min-height: 18px;
	margin: 4px 2px;
	background-color: var(--el-border-color);
	flex-shrink: 0;
}

.filter-toolbar__icon-btn {
	padding: 6px 10px;
	min-height: auto;
}

.filter-toolbar__secondary-btns {
	display: flex;
	align-items: center;
	gap: 4px;
}

@media (max-width: 960px) {
	.filter-toolbar__main {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-toolbar__left {
		flex-direction: column;
	}

	.filter-toolbar__right {
		align-items: flex-start;
	}
}
</style>
