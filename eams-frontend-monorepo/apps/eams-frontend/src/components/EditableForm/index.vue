<template>
	<div class="editable-form">
		<!-- 查看模式 -->
		<div v-if="!isEditing" class="view-mode">
			<div v-for="(value, key) in formData" :key="key" class="form-item">
				<label>{{ getFieldLabel(key) }}：</label>
				<span class="value">{{ formatValue(value) }}</span>
			</div>
			<el-button type="primary" size="small" @click="startEdit" v-if="editable">编辑</el-button>
		</div>

		<!-- 编辑模式 -->
		<div v-else class="edit-mode">
			<el-form :model="formData" label-width="100px" size="small">
				<el-form-item v-for="(value, key) in formData" :key="key" :label="getFieldLabel(key)">
					<!-- 根据数据类型显示不同的输入组件 -->
					<el-input
						v-if="typeof value === 'string' && !isLongText(key)"
						v-model="formData[key]"
						placeholder="请输入"
					/>
					<el-input
						v-else-if="typeof value === 'string' && isLongText(key)"
						v-model="formData[key]"
						type="textarea"
						:rows="3"
						placeholder="请输入"
					/>
					<el-input-number
						v-else-if="typeof value === 'number'"
						v-model="formData[key]"
						:min="0"
						:precision="0"
					/>
					<el-switch v-else-if="typeof value === 'boolean'" v-model="formData[key]" />
					<el-date-picker
						v-else-if="isDateField(key)"
						v-model="formData[key]"
						type="date"
						placeholder="选择日期"
						value-format="yyyy-MM-dd"
					/>
					<el-input v-else v-model="formData[key]" type="textarea" :rows="2" placeholder="请输入" />
				</el-form-item>
			</el-form>
			<div class="form-actions">
				<el-button type="primary" size="small" @click="save">保存</el-button>
				<el-button size="small" @click="cancel">取消</el-button>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import { reactive, ref, watch } from 'vue'

const props = withDefaults(
	defineProps<{
		value: Record<string, any>
		fieldLabels?: Record<string, string>
		longTextFields?: string[]
		dateFields?: string[]
		editable?: boolean
	}>(),
	{
		fieldLabels: () => ({}),
		longTextFields: () => [],
		dateFields: () => [],
		editable: true
	}
)

const emit = defineEmits<{
	(e: 'input', v: Record<string, any>): void
	(e: 'save', v: Record<string, any>): void
	(e: 'cancel'): void
	(e: 'edit-start'): void
}>()

const isEditing = ref(false)
const formData = reactive<Record<string, any>>({})

function clone<T>(v: T): T {
	return JSON.parse(JSON.stringify(v)) as T
}

watch(
	() => props.value,
	(v) => {
		const next = clone(v ?? {})
		for (const k of Object.keys(formData)) delete formData[k]
		Object.assign(formData, next)
	},
	{ immediate: true, deep: true }
)

function getFieldLabel(key: string) {
	return props.fieldLabels[key] || key
}

function isLongText(key: string) {
	return props.longTextFields.includes(key)
}

function isDateField(key: string) {
	return props.dateFields.includes(key)
}

function formatValue(value: unknown) {
	if (value === null || value === undefined) return '-'
	if (typeof value === 'boolean') return value ? '是' : '否'
	if (value instanceof Date) return value.toLocaleDateString()
	if (typeof value === 'object') return JSON.stringify(value)
	return String(value)
}

function startEdit() {
	isEditing.value = true
	emit('edit-start')
}

function save() {
	isEditing.value = false
	const payload = clone(formData)
	emit('input', payload)
	emit('save', payload)
}

function cancel() {
	isEditing.value = false
	const next = clone(props.value ?? {})
	for (const k of Object.keys(formData)) delete formData[k]
	Object.assign(formData, next)
	emit('cancel')
}
</script>

<style scoped>
.editable-form {
	padding: 20px;
	border: 1px solid #dcdfe6;
	border-radius: 4px;
	background-color: #fff;
}

.view-mode .form-item {
	margin-bottom: 15px;
	display: flex;
	align-items: flex-start;
}

.view-mode label {
	color: #909399;
	width: 100px;
	text-align: right;
	margin-right: 15px;
	font-size: 14px;
}

.view-mode .value {
	color: #303133;
	font-size: 14px;
	flex: 1;
}

.form-actions {
	margin-top: 20px;
	text-align: right;
}

.form-actions .el-button + .el-button {
	margin-left: 10px;
}

/* 编辑模式下的样式 */
.edit-mode {
	padding: 10px 0;
}
</style>
