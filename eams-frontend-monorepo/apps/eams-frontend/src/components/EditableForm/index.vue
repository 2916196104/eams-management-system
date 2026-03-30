<template>
  <div class="editable-form">
    <!-- 查看模式 -->
    <div v-if="!isEditing" class="view-mode">
      <div v-for="(value, key) in formData" :key="key" class="form-item">
        <label>{{ getFieldLabel(key) }}：</label>
        <span class="value">{{ formatValue(value) }}</span>
      </div>
      <el-button v-if="editable" type="primary" size="small" @click="startEdit">
        编辑
      </el-button>
    </div>

    <!-- 编辑模式 -->
    <div v-else class="edit-mode">
      <el-form :model="formData" label-width="100px" size="small">
        <el-form-item
          v-for="(value, key) in formData"
          :key="key"
          :label="getFieldLabel(key)"
        >
          <!-- 根据数据类型显示不同的输入组件 -->
          <!-- 普通文本输入 -->
          <el-input
            v-if="typeof value === 'string' && !isLongText(key)"
            v-model="formData[key]"
            placeholder="请输入"
          />
          <!-- 多行文本输入 -->
          <el-input
            v-else-if="typeof value === 'string' && isLongText(key)"
            v-model="formData[key]"
            type="textarea"
            :rows="3"
            placeholder="请输入"
          />
          <!-- 数字输入 -->
          <el-input-number
            v-else-if="typeof value === 'number'"
            v-model="formData[key]"
            :min="0"
            :precision="0"
          />
          <!-- 开关 -->
          <el-switch
            v-else-if="typeof value === 'boolean'"
            v-model="formData[key]"
          />
          <!-- 日期选择器 -->
          <el-date-picker
            v-else-if="isDateField(key)"
            v-model="formData[key]"
            type="date"
            placeholder="选择日期"
            value-format="yyyy-MM-dd"
          />
          <!-- 其他类型使用文本域 -->
          <el-input
            v-else
            v-model="formData[key]"
            type="textarea"
            :rows="2"
            placeholder="请输入"
          />
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
import { ref, watch } from 'vue'

// 定义 Props
interface Props {
  // 表单数据（支持 v-model）
  modelValue?: Record<string, any>
  // 字段标签映射
  fieldLabels?: Record<string, string>
  // 长文本字段（需要显示为textarea）
  longTextFields?: string[]
  // 日期字段
  dateFields?: string[]
  // 是否可编辑
  editable?: boolean
}

// 定义 Emits
interface Emits {
  (e: 'update:modelValue', value: Record<string, any>): void
  (e: 'edit-start'): void
  (e: 'save', value: Record<string, any>): void
  (e: 'cancel'): void
}

const props = withDefaults(defineProps<Props>(), {
  modelValue: () => ({}),
  fieldLabels: () => ({}),
  longTextFields: () => [],
  dateFields: () => [],
  editable: true,
})

const emit = defineEmits<Emits>()

// 编辑状态
const isEditing = ref(false)

// 表单数据（深拷贝 props 的值）
const formData = ref<Record<string, any>>({})

// 监听 props.modelValue 的变化
watch(
  () => props.modelValue,
  (newVal) => {
    if (newVal) {
      // 深拷贝，避免直接修改 props
      formData.value = JSON.parse(JSON.stringify(newVal))
    }
  },
  { immediate: true, deep: true }
)

// 获取字段显示名称
const getFieldLabel = (key: string): string => {
  return props.fieldLabels[key] || key
}

// 判断是否是长文本字段
const isLongText = (key: string): boolean => {
  return props.longTextFields.includes(key)
}

// 判断是否是日期字段
const isDateField = (key: string): boolean => {
  return props.dateFields.includes(key)
}

// 格式化显示值
const formatValue = (value: any): string => {
  if (value === null || value === undefined) return '-'
  if (typeof value === 'boolean') return value ? '是' : '否'
  if (value instanceof Date) return value.toLocaleDateString()
  if (typeof value === 'object') return JSON.stringify(value)
  return String(value)
}

// 开始编辑
const startEdit = () => {
  isEditing.value = true
  emit('edit-start')
}

// 保存
const save = () => {
  isEditing.value = false
  // 触发 v-model 更新（Vue 3 语法）
  emit('update:modelValue', formData.value)
  // 触发 save 事件
  emit('save', formData.value)
}

// 取消
const cancel = () => {
  isEditing.value = false
  // 恢复原始数据
  formData.value = JSON.parse(JSON.stringify(props.modelValue))
  emit('cancel')
}

// 暴露方法给父组件
defineExpose({
  startEdit,
  save,
  cancel,
  getFormData: () => formData.value,
})
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