<template>
  <el-dialog v-model="dialogVisible" :="props" destroy-on-close>
    <!-- 定义头部插槽 -->
    <template #header="{ close, titleClass, titleId }">
      <slot name="header" :close :titleClass :titleId :="props"></slot>
    </template>
    <!-- 定义内容插槽 -->
    <template #default>
      <slot name="default" :data="props.data">你的对话框没有定义任何内容</slot>
    </template>
    <!-- 定义底部插槽 -->
    <template #footer>
      <slot name="footer">
        <el-button type="primary" @click="dialogVisible = false">关闭</el-button>
      </slot>
    </template>
  </el-dialog>
</template>
<script setup lang="ts" generic="T extends Object">
import { ref } from 'vue'
import type { MyDialogProps } from './type'

// 定义组件属性
const props = defineProps<MyDialogProps<T>>()

// 是否显示对话框
const dialogVisible = ref(false)

// 暴露方法
defineExpose({
  /**
   * 打开对话框
   */
  openDialog() {
    dialogVisible.value = true
  },
  /**
   * 关闭对话框
   */
  closeDialog() {
    dialogVisible.value = false
  }
})
</script>
