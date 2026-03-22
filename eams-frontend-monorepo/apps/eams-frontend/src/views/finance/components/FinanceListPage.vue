<template>
	<section class="finance-page">
		<section class="filter-panel">
			<div class="filter-grid">
				<div v-for="field in visibleFields" :key="field.prop" class="filter-item">
					<label class="filter-label">{{ field.label }}:</label>
					<el-input
						v-if="field.type === 'input'"
						v-model="filters[field.prop]"
						:placeholder="field.placeholder"
						clearable
					/>
					<el-select
						v-else-if="field.type === 'select'"
						v-model="filters[field.prop]"
						:placeholder="field.placeholder"
						clearable
					>
						<el-option
							v-for="option in field.options || []"
							:key="option.value"
							:label="option.label"
							:value="option.value"
						/>
					</el-select>
					<el-date-picker
						v-else
						v-model="filters[field.prop]"
						type="date"
						value-format="YYYY-MM-DD"
						:placeholder="field.placeholder"
					/>
				</div>
			</div>
			<div class="filter-actions">
				<el-button text type="primary" @click="isExpanded = !isExpanded">
					{{ isExpanded ? '收起' : '展开' }}
				</el-button>
				<el-button :icon="Search" circle @click="handleSearch" />
				<el-button :icon="CircleClose" circle @click="handleReset" />
				<el-button :icon="Download" @click="handleExport">导出</el-button>
			</div>
		</section>

		<p v-if="config.description" class="panel-description">{{ config.description }}</p>

		<section class="table-tools">
			<div class="batch-actions">
				<el-button
					v-for="action in config.batchActions || []"
					:key="action.key"
					:type="action.type || 'primary'"
					@click="handleBatchAction(action.label)"
				>
					{{ action.label }}
				</el-button>
			</div>
			<div class="icon-actions">
				<el-button :icon="RefreshRight" circle @click="handleRefresh" />
				<el-button :icon="Printer" circle @click="handlePrint" />
				<el-button :icon="Grid" circle @click="handleLayout" />
			</div>
		</section>

		<my-table
			:istabmultiple="true"
			:tabattr="tableAttr"
			:tabdatacolumns="config.columns"
			:tabdata="pageData"
			:taboperbtns="config.operationButtons || []"
			@page-change="handlePageChange"
			@selection-change="handleSelectionChange"
			@taboper-click="handleOperation"
		>
			<template #customercell="{ prop, row }">
				<template v-if="prop === 'amount' || prop === 'unitClassFee' || prop === 'classSubtotal' || prop === 'unitTutorFee' || prop === 'tutorSubtotal' || prop === 'unitReward' || prop === 'rewardSubtotal'">
					{{ formatCurrency(row[prop]) }}
				</template>
				<template v-else-if="prop === 'status' || prop === 'auditStatus'">
					<el-tag :type="getStatusType(row[prop])" effect="light">{{ row[prop] }}</el-tag>
				</template>
				<template v-else>
					{{ row[prop] }}
				</template>
			</template>
		</my-table>
	</section>
</template>

<script setup lang="ts">
import { computed, reactive, ref } from 'vue'
import { ElMessage } from 'element-plus'
import { CircleClose, Download, Grid, Printer, RefreshRight, Search } from '@element-plus/icons-vue'
import MyTable from '@/components/mytable/MyTable.vue'
import { createPageDTO, type MyTableAttr, type PageDTO } from '@/components/mytable/type'
import type { FinanceListConfig } from '../shared'

const props = defineProps<{
	config: FinanceListConfig<Record<string, any>>
}>()

const filters = reactive<Record<string, string>>({ ...props.config.initialFilters })
const isExpanded = ref(false)
const pageIndex = ref(1)
const pageSize = ref(10)
const selectedRows = ref<Record<string, any>[]>([])

const tableAttr: MyTableAttr = {
	'row-key': 'id',
	'max-height': 520
}

const visibleFields = computed(() => {
	if (isExpanded.value) return props.config.filters
	return props.config.filters.slice(0, 4)
})

const filteredRows = computed(() => {
	return props.config.rows.filter((row) =>
		props.config.filters.every((field) => {
			const keyword = String(filters[field.prop] || '').trim()
			if (!keyword) return true

			if (field.type === 'date') {
				const fieldValue = String(row[field.prop] || row.startDate || row.endDate || '')
				return fieldValue >= keyword
			}

			const rawValue = row[field.prop]
			return String(rawValue ?? '').includes(keyword)
		})
	)
})

const pageData = computed(() =>
	createPageDTO({
		pageIndex: pageIndex.value,
		pageSize: pageSize.value,
		total: filteredRows.value.length,
		rows: filteredRows.value.slice((pageIndex.value - 1) * pageSize.value, pageIndex.value * pageSize.value)
	})
)

function handleSearch() {
	pageIndex.value = 1
}

function handleReset() {
	Object.assign(filters, props.config.initialFilters)
	pageIndex.value = 1
}

function handleExport() {
	ElMessage.success(`已准备导出 ${props.config.title} 数据`)
}

function handleRefresh() {
	ElMessage.success(`${props.config.title} 已刷新`)
}

function handlePrint() {
	ElMessage.info(`请在联调接口后接入 ${props.config.title} 打印能力`)
}

function handleLayout() {
	ElMessage.info('布局切换已预留，可继续扩展为卡片视图')
}

function handleBatchAction(label: string) {
	if (!selectedRows.value.length) {
		ElMessage.warning(`请先勾选需要${label}的记录`)
		return
	}
	ElMessage.success(`已对 ${selectedRows.value.length} 条记录执行${label}`)
}

function handleSelectionChange(rows: Record<string, any>[]) {
	selectedRows.value = rows
}

function handlePageChange(data: PageDTO<Record<string, any>>) {
	pageIndex.value = data.pageIndex
	pageSize.value = data.pageSize
}

function handleOperation(_: number, row: Record<string, any>, evtname: string) {
	const actionMap: Record<string, string> = {
		detail: '查看详情',
		approve: '通过',
		reject: '驳回'
	}
	ElMessage.success(`${actionMap[evtname] || '处理'}：${row.project || row.title}`)
}

function formatCurrency(value: number | string) {
	const amount = Number(value || 0)
	return `¥ ${amount.toLocaleString('zh-CN')}`
}

function getStatusType(status: string) {
	if (status.includes('通过') || status.includes('已认款')) return 'success'
	if (status.includes('驳回')) return 'danger'
	return 'warning'
}
</script>

<style scoped>
.finance-page {
	padding: 16px;
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.filter-panel,
.table-tools {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
}

.filter-panel {
	display: flex;
	justify-content: space-between;
	align-items: flex-start;
	gap: 16px;
}

.filter-grid {
	flex: 1;
	display: grid;
	grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
	gap: 14px 20px;
}

.filter-item {
	display: flex;
	align-items: center;
	gap: 10px;
}

.filter-label {
	min-width: 72px;
	color: #303133;
	text-align: right;
}

.filter-actions,
.icon-actions,
.table-tools,
.batch-actions {
	display: flex;
	align-items: center;
	gap: 10px;
}

.table-tools {
	justify-content: space-between;
}

.panel-description {
	margin: -4px 0 0;
	padding: 0 4px;
	color: #909399;
	font-size: 13px;
}

@media (max-width: 960px) {
	.filter-panel,
	.table-tools {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-item {
		flex-direction: column;
		align-items: stretch;
	}

	.filter-label {
		min-width: auto;
		text-align: left;
	}

	.filter-actions,
	.icon-actions,
	.batch-actions {
		flex-wrap: wrap;
	}
}
</style>
