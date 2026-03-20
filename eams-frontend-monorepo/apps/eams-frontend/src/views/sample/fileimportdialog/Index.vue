<template>
	<section class="root-container">
		<el-card header="文件导入弹窗组件演示">
			<el-space wrap>
				<el-button type="primary" @click="openFrontendImport">前端解析模式</el-button>
				<el-button type="success" @click="openBackendImport">后端接口模式</el-button>
			</el-space>
		</el-card>

		<!-- 导入结果显示 -->
		<el-card v-if="importResult" header="导入结果" class="result-card">
			<el-descriptions :column="1" border>
				<el-descriptions-item label="总行数">{{ importResult.totalRows }}</el-descriptions-item>
				<el-descriptions-item label="错误行数">
					<el-tag :type="importResult.errorRows > 0 ? 'danger' : 'success'">
						{{ importResult.errorRows }}
					</el-tag>
				</el-descriptions-item>
				<el-descriptions-item label="表头">
					<el-tag v-for="header in importResult.headers" :key="header" size="small" class="mr-1">
						{{ header }}
					</el-tag>
				</el-descriptions-item>
			</el-descriptions>
			<el-divider />
			<el-table :data="importResult.data" border stripe max-height="400">
				<el-table-column type="index" label="序号" width="60" />
				<el-table-column
					v-for="header in importResult.headers"
					:key="header"
					:prop="`data.${header}`"
					:label="header"
					min-width="120"
				/>
				<el-table-column label="状态" width="80">
					<template #default="{ row }">
						<el-tag v-if="row.hasError" type="danger" size="small">异常</el-tag>
						<el-tag v-else type="success" size="small">正常</el-tag>
					</template>
				</el-table-column>
			</el-table>
		</el-card>
	</section>

	<!-- 前端解析模式 -->
	<FileImportDialog
		v-model="frontendVisible"
		title="学员信息导入（前端解析）"
		mode="frontend"
		template-file-name="学员导入模板.xlsx"
		@import-success="handleImportSuccess"
	/>

	<!-- 后端接口模式 -->
	<FileImportDialog
		v-model="backendVisible"
		title="批量数据导入（后端接口）"
		mode="backend"
		action="/api/import"
		template-file-name="批量导入模板.xlsx"
		@import-success="handleImportSuccess"
	/>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import { ElMessage } from 'element-plus'
import FileImportDialog from '@/components/FileImportDialog/index.vue'
import type { ParseResult } from '@/components/FileImportDialog/type'

const frontendVisible = ref(false)
const backendVisible = ref(false)
const importResult = ref<ParseResult | null>(null)

function openFrontendImport() {
	frontendVisible.value = true
}

function openBackendImport() {
	backendVisible.value = true
}

function handleImportSuccess(data: ParseResult | any) {
	importResult.value = data as ParseResult
	ElMessage.success(`导入成功！共 ${importResult.value.totalRows} 条数据`)
}
</script>

<style scoped>
.root-container {
	display: flex;
	flex-direction: column;
	gap: 20px;
}

.result-card {
	margin-top: 20px;
}

.mr-1 {
	margin-right: 4px;
}
</style>
