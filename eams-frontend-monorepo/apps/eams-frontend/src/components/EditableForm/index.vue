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

<script>
export default {
	name: 'EditableForm',
	props: {
		// 表单数据（支持v-model）
		value: {
			type: Object,
			required: true,
			default: () => ({})
		},
		// 字段标签映射
		fieldLabels: {
			type: Object,
			default: () => ({})
		},
		// 长文本字段（需要显示为textarea）
		longTextFields: {
			type: Array,
			default: () => []
		},
		// 日期字段
		dateFields: {
			type: Array,
			default: () => []
		},
		// 是否可编辑
		editable: {
			type: Boolean,
			default: true
		}
	},
	data() {
		return {
			isEditing: false,
			formData: {}
		}
	},
	watch: {
		value: {
			handler(val) {
				// 深拷贝，避免直接修改props
				this.formData = JSON.parse(JSON.stringify(val))
			},
			immediate: true,
			deep: true
		}
	},
	methods: {
		// 获取字段显示名称
		getFieldLabel(key) {
			return this.fieldLabels[key] || key
		},
		// 判断是否是长文本字段
		isLongText(key) {
			return this.longTextFields.includes(key)
		},
		// 判断是否是日期字段
		isDateField(key) {
			return this.dateFields.includes(key)
		},
		// 格式化显示值
		formatValue(value) {
			if (value === null || value === undefined) return '-'
			if (typeof value === 'boolean') return value ? '是' : '否'
			if (value instanceof Date) return value.toLocaleDateString()
			if (typeof value === 'object') return JSON.stringify(value)
			return String(value)
		},
		startEdit() {
			this.isEditing = true
			this.$emit('edit-start')
		},
		save() {
			this.isEditing = false
			// 触发v-model更新
			this.$emit('input', this.formData)
			// 触发save事件
			this.$emit('save', this.formData)
		},
		cancel() {
			this.isEditing = false
			// 恢复原始数据
			this.formData = JSON.parse(JSON.stringify(this.value))
			this.$emit('cancel')
		}
	}
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
