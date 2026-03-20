<template>
	<el-dialog
		v-model="dialogVisible"
		:title="title"
		:width="width"
		:close-on-click-modal="false"
		:close-on-press-escape="false"
		@close="handleClose"
	>
		<div class="file-import-dialog">
			<!-- 步骤提示 -->
			<div class="step-tips">
				<el-steps :active="currentStep" finish-status="success" simple>
					<el-step title="下载模板" />
					<el-step title="选择文件" />
					<el-step title="预览数据" />
					<el-step title="导入完成" />
				</el-steps>
			</div>

			<!-- 模板下载区 -->
			<div v-if="currentStep === 0" class="step-content">
				<el-alert type="info" :closable="false" show-icon>
					<template #title>
						请先下载模板，按模板格式填写数据后再上传
					</template>
				</el-alert>
				<div class="template-download">
					<el-button type="primary" :icon="Download" @click="downloadTemplate">
						下载导入模板
					</el-button>
				</div>
			</div>

			<!-- 文件选择区 -->
			<div v-if="currentStep === 1" class="step-content">
				<el-alert
					:title="`支持格式：${accept}，文件大小不超过 ${maxSize}MB`"
					type="info"
					:closable="false"
					show-icon
				/>
				<div class="file-upload">
					<el-upload
						ref="uploadRef"
						class="upload-area"
						:action="action"
						:headers="headers"
						:data="uploadData"
						:accept="accept"
						:auto-upload="false"
						:show-file-list="false"
						:before-upload="beforeUpload"
						:on-change="handleFileChange"
						:disabled="importStatus === 'uploading' || importStatus === 'parsing'"
						drag
					>
						<el-icon class="upload-icon"><UploadFilled /></el-icon>
						<div class="upload-text">
							<p>点击或拖拽文件到此区域上传</p>
							<p class="upload-hint">仅支持 .xlsx、.xls 格式文件</p>
						</div>
					</el-upload>
					<!-- 已选文件 -->
					<div v-if="selectedFile" class="selected-file">
						<el-icon><Document /></el-icon>
						<span class="file-name">{{ selectedFile.name }}</span>
						<span class="file-size">({{ formatFileSize(selectedFile.size) }})</span>
						<el-button
							type="danger"
							:icon="Delete"
							size="small"
							text
							@click="removeFile"
						/>
					</div>
				</div>
			</div>

			<!-- 数据预览区 -->
			<div v-if="currentStep === 2 && importStatus === 'parsed'" class="step-content">
				<div class="preview-header">
					<span class="preview-title">数据预览</span>
					<span class="preview-count">共 {{ parseResult.totalRows }} 条数据</span>
					<span v-if="parseResult.errorRows > 0" class="error-count">
						{{ parseResult.errorRows }} 条错误
					</span>
				</div>

				<!-- 错误汇总 -->
				<el-alert
					v-if="showErrorSummary && parseResult.errorRows > 0"
					:title="`检测到 ${parseResult.errorRows} 条数据存在错误，请检查后重新上传`"
					type="error"
					:closable="false"
					show-icon
					class="error-summary"
				/>

				<!-- 预览表格 -->
				<el-table
					:data="previewData"
					border
					stripe
					max-height="400"
					class="preview-table"
					:row-class-name="getRowClassName"
				>
					<el-table-column
						type="index"
						label="序号"
						width="60"
						:index="getRowIndex"
					/>
					<el-table-column
						v-for="header in parseResult.headers"
						:key="header"
						:prop="`data.${header}`"
						:label="header"
						min-width="120"
						show-overflow-tooltip
					/>
					<el-table-column
						v-if="parseResult.errorRows > 0"
						label="状态"
						width="80"
						fixed="right"
					>
						<template #default="{ row }">
							<el-tag v-if="row.hasError" type="danger" size="small">异常</el-tag>
							<el-tag v-else type="success" size="small">正常</el-tag>
						</template>
					</el-table-column>
				</el-table>

				<!-- 分页提示 -->
				<div v-if="parseResult.totalRows > previewLimit" class="preview-pagination-tip">
					<el-text type="info">
						仅展示前 {{ previewLimit }} 条数据，完整数据将在导入后显示
					</el-text>
				</div>
			</div>

			<!-- 进度显示区 -->
			<div v-if="importStatus === 'uploading' || importStatus === 'parsing'" class="step-content">
				<div class="progress-container">
					<el-icon class="is-loading"><Loading /></el-icon>
					<p class="progress-text">
						{{ importStatus === 'parsing' ? '正在解析文件...' : '正在导入数据...' }}
					</p>
					<el-progress
						:percentage="uploadProgress.percent"
						:status="showProgressError ? 'exception' : undefined"
					/>
				</div>
			</div>

			<!-- 导入成功区 -->
			<div v-if="currentStep === 3 && importStatus === 'success'" class="step-content">
				<el-result icon="success" title="导入成功" sub-title="数据已成功导入">
					<template #extra>
						<el-statistic title="成功导入" :value="parseResult.totalRows" />
					</template>
				</el-result>
			</div>

			<!-- 导入失败区 -->
			<div v-if="importStatus === 'error'" class="step-content">
				<el-result icon="error" title="导入失败" :sub-title="errorMessage">
					<template #extra>
						<el-button type="primary" @click="retry">重新上传</el-button>
					</template>
				</el-result>
			</div>
		</div>

		<!-- 底部按钮 -->
		<template #footer>
			<div class="dialog-footer">
				<el-button @click="handleClose">
					{{ currentStep === 3 && importStatus === 'success' ? '完成' : '取消' }}
				</el-button>
				<el-button
					v-if="currentStep === 1 && selectedFile"
					type="primary"
					:loading="importStatus === 'parsing' || importStatus === 'uploading'"
					@click="handlePreview"
				>
					下一步：预览数据
				</el-button>
				<el-button
					v-if="currentStep === 2 && importStatus === 'parsed'"
					type="primary"
					:loading="false"
					@click="handleImport"
				>
					确认导入
				</el-button>
			</div>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { ref, computed, watch } from 'vue'
import { ElMessage } from 'element-plus'
import {
	Download,
	UploadFilled,
	Document,
	Delete,
	Loading
} from '@element-plus/icons-vue'
import type { UploadFile, UploadRawFile } from 'element-plus'
import * as XLSX from 'xlsx'
import type {
	FileImportDialogProps,
	FileImportDialogEmits,
	ParseResult,
	ParsedRow,
	UploadProgress,
	ImportStatus
} from './type'

// Props 定义
const props = withDefaults(
	defineProps<FileImportDialogProps & { modelValue?: boolean }>(),
	{
		title: '数据导入',
		width: '700px',
		mode: 'frontend',
		templateUrl: '',
		templateFileName: '导入模板.xlsx',
		action: '',
		headers: () => ({}),
		data: () => ({}),
		maxSize: 10,
		accept: '.xlsx,.xls',
		showPreview: true,
		previewLimit: 100,
		showErrorSummary: true,
		modelValue: false
	}
)

// Emits 定义
const emit = defineEmits<FileImportDialogEmits & { (e: 'update:modelValue', value: boolean): void }>()

// 响应式数据
const dialogVisible = ref(false)
const currentStep = ref(0)
const selectedFile = ref<File | null>(null)
const importStatus = ref<ImportStatus>('idle')
const parseResult = ref<ParseResult>({
	data: [],
	headers: [],
	totalRows: 0,
	errorRows: 0
})
const uploadProgress = ref<UploadProgress>({ loaded: 0, total: 0, percent: 0 })
const errorMessage = ref('')
const uploadRef = ref()

// 计算属性：上传额外参数（避免与 props.data 冲突）
const uploadData = computed(() => props.data)

// 计算属性：是否显示错误状态（用于进度条）
const showProgressError = computed(() => importStatus.value === 'error')

// 计算属性：预览数据
const previewData = computed(() => {
	if (!props.showPreview) return []
	return parseResult.value.data.slice(0, props.previewLimit)
})

// 方法：格式化文件大小
function formatFileSize(bytes: number): string {
	if (bytes === 0) return '0 B'
	const k = 1024
	const sizes = ['B', 'KB', 'MB', 'GB']
	const i = Math.floor(Math.log(bytes) / Math.log(k))
	return (bytes / Math.pow(k, i)).toFixed(2) + ' ' + sizes[i]
}

// 方法：下载模板
function downloadTemplate() {
	if (props.templateUrl) {
		// 如果有完整的URL地址，直接下载
		window.open(props.templateUrl, '_blank')
	} else {
		// 否则创建一个空模板文件并下载
		createEmptyTemplate()
	}
}

// 方法：创建空模板并下载
function createEmptyTemplate() {
	try {
		const workbook = XLSX.utils.book_new()
		const worksheet = XLSX.utils.aoa_to_sheet([['示例列1', '示例列2', '示例列3']])
		XLSX.utils.book_append_sheet(workbook, worksheet, 'Sheet1')
		XLSX.writeFile(workbook, props.templateFileName)
		ElMessage.success('模板下载成功')
	} catch (error) {
		ElMessage.error('模板下载失败')
		console.error('模板下载失败:', error)
	}
}

// 方法：文件上传前校验
function beforeUpload(rawFile: UploadRawFile): boolean {
	const isValidType =
		rawFile.type === 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' ||
		rawFile.type === 'application/vnd.ms-excel'
	const isValidSize = rawFile.size / 1024 / 1024 < props.maxSize

	if (!isValidType) {
		ElMessage.error('只支持上传 .xlsx 或 .xls 格式的文件')
		return false
	}
	if (!isValidSize) {
		ElMessage.error(`文件大小不能超过 ${props.maxSize}MB`)
		return false
	}
	return true
}

// 方法：文件选择变化
function handleFileChange(file: UploadFile) {
	if (file.raw) {
		selectedFile.value = file.raw
		importStatus.value = 'selected'
		emit('file-select', file.raw)
	}
}

// 方法：移除文件
function removeFile() {
	selectedFile.value = null
	importStatus.value = 'idle'
	currentStep.value = 1
}

// 方法：解析Excel文件（前端模式）
async function parseExcelFile(file: File): Promise<ParseResult> {
	return new Promise((resolve, reject) => {
		const reader = new FileReader()

		reader.onload = (e) => {
			try {
				const data = e.target?.result
				const workbook = XLSX.read(data, { type: 'binary' })
				const firstSheetName = workbook.SheetNames[0]
				const worksheet = workbook.Sheets[firstSheetName]

				// 获取表格数据
				const jsonData = XLSX.utils.sheet_to_json(worksheet, { header: 1 }) as any[][]

				if (jsonData.length < 2) {
					reject(new Error('文件内容为空或格式不正确'))
					return
				}

				// 第一行为表头
				const headers = jsonData[0].map((h) => String(h).trim())
				const rows: ParsedRow[] = []

				// 解析数据行（从第二行开始）
				for (let i = 1; i < jsonData.length; i++) {
					const rowData = jsonData[i]
					const row: ParsedRow = {
						rowNumber: i,
						data: {},
						hasError: false,
						errors: []
					}

					// 将数据映射到表头
					headers.forEach((header, index) => {
						row.data[header] = rowData[index] ?? ''
					})

					// 基础校验：检查空行
					const isEmpty = headers.every(
						(header) => row.data[header] === '' || row.data[header] == null
					)

					if (isEmpty) {
						row.hasError = true
						row.errors.push('该行为空行')
					}

					rows.push(row)
				}

				const errorRows = rows.filter((r) => r.hasError).length

				resolve({
					data: rows,
					headers,
					totalRows: rows.length,
					errorRows
				})
			} catch (error) {
				reject(new Error('文件解析失败，请检查文件格式'))
			}
		}

		reader.onerror = () => reject(new Error('文件读取失败'))
		reader.readAsBinaryString(file)
	})
}

// 方法：预览数据
async function handlePreview() {
	if (!selectedFile.value) return

	importStatus.value = 'parsing'

	try {
		const result = await parseExcelFile(selectedFile.value)
		parseResult.value = result
		importStatus.value = 'parsed'
		currentStep.value = 2
		emit('parse-success', result)
	} catch (error) {
		importStatus.value = 'error'
		errorMessage.value = error instanceof Error ? error.message : '解析失败'
		emit('parse-error', error instanceof Error ? error : new Error('解析失败'))
		ElMessage.error(errorMessage.value)
	}
}

// 方法：执行导入
async function handleImport() {
	if (props.mode === 'backend') {
		await handleBackendImport()
	} else {
		await handleFrontendImport()
	}
}

// 方法：后端模式导入
async function handleBackendImport() {
	if (!selectedFile.value || !uploadRef.value) return

	importStatus.value = 'uploading'

	try {
		// 使用 el-upload 的 submit 方法
		const formData = new FormData()
		formData.append('file', selectedFile.value)

		// 添加额外参数
		Object.entries(props.data).forEach(([key, value]) => {
			formData.append(key, value as string)
		})

		const response = await fetch(props.action, {
			method: 'POST',
			headers: props.headers,
			body: formData
		})

		if (!response.ok) {
			throw new Error(`上传失败: ${response.statusText}`)
		}

		const result = await response.json()
		importStatus.value = 'success'
		currentStep.value = 3
		emit('import-success', result)
		ElMessage.success('导入成功')
	} catch (error) {
		importStatus.value = 'error'
		errorMessage.value = error instanceof Error ? error.message : '导入失败'
		emit('import-error', error instanceof Error ? error : new Error('导入失败'))
		ElMessage.error(errorMessage.value)
	}
}

// 方法：前端模式导入
async function handleFrontendImport() {
	importStatus.value = 'uploading'
	uploadProgress.value = { loaded: 50, total: 100, percent: 50 }

	// 模拟上传进度
	const interval = setInterval(() => {
		if (uploadProgress.value.percent < 90) {
			uploadProgress.value.percent += 10
			uploadProgress.value.loaded = (uploadProgress.value.percent / 100) * uploadProgress.value.total
		}
	}, 200)

	try {
		// 延迟模拟网络请求
		await new Promise((resolve) => setTimeout(resolve, 1000))

		clearInterval(interval)
		uploadProgress.value = { loaded: 100, total: 100, percent: 100 }

		importStatus.value = 'success'
		currentStep.value = 3
		emit('import-success', parseResult.value)
		ElMessage.success('导入成功')
	} catch (error) {
		clearInterval(interval)
		importStatus.value = 'error'
		errorMessage.value = error instanceof Error ? error.message : '导入失败'
		emit('import-error', error instanceof Error ? error : new Error('导入失败'))
		ElMessage.error(errorMessage.value)
	}
}

// 方法：重试
function retry() {
	errorMessage.value = ''
	importStatus.value = 'idle'
	currentStep.value = 1
}

// 方法：获取表格行类名
function getRowClassName({ row }: { row: ParsedRow }) {
	return row.hasError ? 'error-row' : ''
}

// 方法：获取表格行索引
function getRowIndex(index: number) {
	return index + 1
}

// 方法：关闭弹窗
function handleClose() {
	dialogVisible.value = false
	emit('update:modelValue', false)
	// 延迟重置状态，等待动画结束
	setTimeout(() => {
		currentStep.value = 0
		selectedFile.value = null
		importStatus.value = 'idle'
		parseResult.value = { data: [], headers: [], totalRows: 0, errorRows: 0 }
		errorMessage.value = ''
		uploadProgress.value = { loaded: 0, total: 0, percent: 0 }
	}, 300)
}

// 方法：打开弹窗（供父组件调用）
function open() {
	dialogVisible.value = true
}

// 方法：关闭弹窗（供父组件调用）
function close() {
	handleClose()
}

// 监听外部 visible 变化
watch(
	() => props.modelValue,
	(val) => {
		dialogVisible.value = val ?? false
	},
	{ immediate: true }
)

watch(dialogVisible, (val) => {
	if (val !== props.modelValue) {
		emit('update:modelValue', val)
	}
})

// 暴露方法给父组件
defineExpose({
	open,
	close
})
</script>

<style scoped>
.file-import-dialog {
	padding: 10px 0;
}

.step-tips {
	margin-bottom: 24px;
}

.step-content {
	min-height: 200px;
}

/* 模板下载 */
.template-download {
	display: flex;
	justify-content: center;
	padding: 40px 0;
}

/* 文件上传 */
.file-upload {
	padding: 20px 0;
}

.upload-area {
	width: 100%;
}

.upload-icon {
	font-size: 48px;
	color: #409eff;
	margin-bottom: 16px;
}

.upload-text {
	font-size: 14px;
	color: #606266;
}

.upload-text p {
	margin: 8px 0;
}

.upload-hint {
	font-size: 12px;
	color: #909399;
}

.selected-file {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-top: 16px;
	padding: 10px 16px;
	background: #f5f7fa;
	border-radius: 4px;
}

.file-name {
	font-size: 14px;
	color: #303133;
}

.file-size {
	font-size: 12px;
	color: #909399;
}

/* 数据预览 */
.preview-header {
	display: flex;
	align-items: center;
	gap: 16px;
	margin-bottom: 16px;
}

.preview-title {
	font-size: 14px;
	font-weight: 500;
	color: #303133;
}

.preview-count {
	font-size: 12px;
	color: #909399;
}

.error-count {
	color: #f56c6c;
	font-size: 12px;
}

.error-summary {
	margin-bottom: 16px;
}

.preview-table {
	margin-top: 16px;
}

.preview-pagination-tip {
	margin-top: 12px;
	text-align: center;
}

:deep(.el-table .error-row) {
	background-color: #fef0f0;
}

/* 进度显示 */
.progress-container {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	padding: 40px 0;
}

.progress-container .el-icon {
	font-size: 48px;
	color: #409eff;
	margin-bottom: 16px;
}

.progress-text {
	font-size: 14px;
	color: #606266;
	margin-bottom: 24px;
}

/* 底部按钮 */
.dialog-footer {
	display: flex;
	justify-content: flex-end;
	gap: 12px;
}
</style>
