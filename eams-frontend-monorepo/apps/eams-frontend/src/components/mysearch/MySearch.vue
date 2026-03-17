<template>
  <section class="bar-container">
    <!-- 顶部栏 -->
    <section class="bar-header">
      <section class="header-slot">
        <h3 v-if="formtitle">{{ formtitle }}</h3>
        <slot name="header" :form="formRef" :props="props"></slot>
      </section>
      <el-button
        v-if="items.length > (relFormAttr?.['show-count'] || defShowCount)"
        type="primary"
        size="large"
        link
        @click="isExpand = !isExpand"
      >
        <template v-if="!isExpand">展开更多</template>
        <template v-else>收起更多</template>
        <el-icon class="el-icon--right">
          <IconArrowUpBold v-if="isExpand" />
          <IconArrowDownBold v-else />
        </el-icon>
      </el-button>
    </section>
    <!-- 表单 -->
    <section class="bar-body">
      <el-form ref="formRef" :model="model" :rules="rules" :="relFormAttr">
        <template v-for="(item, index) in items" :key="item.prop">
          <el-form-item
            v-show="index < (relFormAttr?.['show-count'] || defShowCount) || isExpand"
            :="item"
          >
            <!-- 根据表单类型渲染表单组件 -->
            <my-form-render
              :item="item"
              :model="model[item.prop]"
              @update:model="emit('model-change', item.prop, $event)"
            />
          </el-form-item>
        </template>
      </el-form>
    </section>
    <!-- 底部栏 -->
    <section class="bar-footer">
      <section class="footer-slot">
        <slot name="footer" :form="formRef" :props="props"></slot>
      </section>
      <section>
        <el-button type="primary" icon="icon-search" @click="submitForm">查询</el-button>
        <el-button type="primary" icon="icon-reset" @click="formRef?.resetFields()">重置</el-button>
      </section>
    </section>
  </section>
</template>
<script setup lang="ts" generic="T extends Record<string, any>">
import { computed, ref } from 'vue'
import { ElMessage, type FormInstance } from 'element-plus'
import type { MyFormAttr } from '@/components/myform/type'
import type { MySearchProps } from './type'
import MyFormRender from '../myform/MyFormRender.vue'

// 组件属性定义
const props = defineProps<MySearchProps<T>>()

// 声明emit事件
const emit = defineEmits<{
  /** 表单值改变事件 */
  (event: 'model-change', prop: string, val: any): void
  /** 查询事件 */
  (event: 'do-search'): void
}>()

// 表单实例
const formRef = ref<FormInstance>()
// 是否展开
const isExpand = ref(false)
// 默认显示表单域个数，默认4个
const defShowCount = ref(4)
// 合并表单默认属性与传入属性
const relFormAttr = computed<MyFormAttr>(() => {
  const defualt = {
    'show-count': defShowCount.value,
    inline: true
  }
  return {
    ...defualt,
    ...props.formattr
  }
})

/**
 * 提交表单
 */
function submitForm() {
  formRef.value?.validate((valid) => {
    if (valid) {
      emit('do-search')
    } else {
      ElMessage.error('请检查你的表单数据是否均填写正确')
    }
  })
}
</script>
<style scoped>
.bar-container {
  width: 100%;
  background-color: white;
  border-radius: 5px;
  box-sizing: border-box;
  padding: 10px;
}
.bar-header {
  margin: 0.5% 0.5%;
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  align-items: center;
  .header-slot {
    display: flex;
    justify-content: flex-start;
    align-items: center;
    gap: 10px;
  }
}
.bar-body {
  margin: 0 0.5%;
  display: flex;
  flex-direction: row;
  justify-content: flex-start;
}
.bar-footer {
  margin: 0.8% 0.5%;
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  align-items: flex-start;
  .footer-slot {
    display: flex;
    justify-content: flex-start;
    align-items: center;
    gap: 10px;
  }
}
</style>
