<template>
  <my-dialog ref="dialog" :="props" :before-close="handleClose">
    <!-- 定义头部插槽 -->
    <template #header="{ close, titleClass, titleId }">
      <slot name="header" :="props" :close :titleClass :titleId></slot>
    </template>
    <!-- 默认插槽显示表单 -->
    <template #default>
      <el-form ref="formRef" :model="localmodel" :rules="rules" :="formattr">
        <template v-for="item in formitemdata" :key="item.prop">
          <el-form-item :="item">
            <!-- 表单项前置插槽 -->
            <slot name="itemahead" :item :model="localmodel"></slot>
            <!-- 表单项默认插槽 -->
            <slot name="itemdefault" :item :model="localmodel">
              <!-- 根据表单类型渲染表单组件 -->
              <my-form-render
                :item="item"
                :model="localmodel[item.prop]"
                @update:model="
                  ($event: any) => {
                    localmodel[item.prop] = $event
                    $emit('model-change', item.prop, $event)
                  }
                "
              />
            </slot>
            <!-- 表单项后置插槽 -->
            <slot name="itemtail" :item :model="localmodel"></slot>
          </el-form-item>
        </template>
      </el-form>
    </template>
    <!-- 底部显示确认和关闭按钮 -->
    <template #footer>
      <slot name="footer" :dialog :form="formRef" :="props">
        <el-button type="info" @click="handleClose()">
          {{ props.cancelText || '关闭' }}
        </el-button>
        <el-button
          v-if="!props.formattr?.disabled && props.reset"
          type="warning"
          @click="resetForm()"
        >
          重置
        </el-button>
        <el-button
          v-if="!props.formattr?.disabled"
          :type="props.danger ? 'danger' : 'success'"
          @click="submitForm"
        >
          {{ props.submitText || '提交' }}
        </el-button>
      </slot>
    </template>
  </my-dialog>
</template>
<script lang="ts" setup generic="T extends Record<string, any>">
import { reactive, ref } from 'vue'
import { type FormInstance, ElMessage, ElMessageBox } from 'element-plus'
import MyDialog from './MyDialog.vue'
import type { MyFormDialogProps } from './type'
import { cloneDeep } from 'lodash-es'
import { isEqualWithEmpty } from '@/utils/object'

// 定义组件属性
const props = withDefaults(defineProps<MyFormDialogProps<T>>(), {
  width: '40vw',
  draggable: true
})

// 数据本地存储
const localmodel = reactive({ ...props.data })

// 对话框引用
const dialog = ref()
// 表单引用
const formRef = ref<FormInstance>()

// 定义事件
const emit = defineEmits<{
  /** 表单值改变事件 */
  (event: 'model-change', prop: string, val: any): void
  /** 提交修改事件 */
  (event: 'confirm', data: T): void
}>()

/**
 * 提交表单
 */
function submitForm() {
  formRef.value?.validate((valid) => {
    if (valid) {
      emit('confirm', localmodel as T)
    } else {
      ElMessage.error('请检查你的表单数据是否均填写正确')
    }
  })
}

/**
 * 重置表单
 */
function resetForm() {
  formRef.value?.resetFields()
}

/**
 * 关闭前检查属性变化
 * @param done 关闭对话框
 */
function handleClose(done?: () => void) {
  // 只读方式打开表单或表单中数据没有发生变化时，可以关闭对话框
  if (
    props.disableBeforeClose ||
    props.formattr?.disabled ||
    isEqualWithEmpty(localmodel, props.data)
  ) {
    if (done) done()
    else dialog.value.closeDialog()
  } else {
    ElMessageBox.confirm('你有尚未提交的更改，是确定否关闭？', '提示', {
      confirmButtonText: '确定关闭',
      cancelButtonText: '点错了',
      type: 'warning'
    })
      .then(() => {
        if (done) done()
        else dialog.value.closeDialog()
      })
      .catch(() => {})
  }
}

// 响应式模型重置函数
const resetReactiveModel = <T extends Record<string, any>>(target: T, source: T) => {
  // 1. 清空目标对象所有属性
  Object.keys(target).forEach((key) => {
    delete (target as Record<string, any>)[key]
  })

  // 2. 深度复制源对象属性
  const clonedSource = cloneDeep(source)

  // 添加类型断言确保类型安全
  Object.assign(target, clonedSource)
}

// 暴露方法
defineExpose({
  /**
   * 打开对话框
   * @param reload 是否刷新表单数据
   */
  openDialog(reload?: boolean) {
    if (reload) resetReactiveModel(localmodel, props.data as Record<string, any>)
    dialog?.value.openDialog()
  },
  /**
   * 关闭对话框
   */
  closeDialog() {
    dialog?.value.closeDialog()
  }
})
</script>
