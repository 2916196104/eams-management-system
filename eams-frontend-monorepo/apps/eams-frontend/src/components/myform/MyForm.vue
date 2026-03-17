<template>
  <section class="bar-container">
    <!-- 顶部栏 -->
    <section class="bar-header">
      <h3>{{ formtitle }}</h3>
      <section class="header-slot">
        <slot name="header" :form="formRef" :="props"></slot>
        <el-button v-if="showback" type="info" size="small" icon="IconBack" @click="handleBack()">
          返回
        </el-button>
      </section>
    </section>
    <!-- 表单 -->
    <section class="bar-body">
      <el-form ref="formRef" :model="localmodel" :rules="rules" :="formattr">
        <template v-for="item in items" :key="item.prop">
          <el-form-item :="item">
            <!-- 表单项前置插槽 -->
            <slot name="itemahead" :item :model="localmodel"></slot>
            <!-- 表单项默认插槽 -->
            <slot name="itemdefault" :item :model="localmodel">
              <!-- 默认实现.根据表单类型渲染表单组件 -->
              <my-form-render
                :item="item"
                :model="localmodel[item.prop]"
                @update:model="
                  ($event: any) => {
                    localmodel[item.prop] = $event
                    emit('model-change', item.prop, $event)
                  }
                "
              />
            </slot>
            <!-- 表单项后置插槽 -->
            <slot name="itemtail" :item :model="localmodel"></slot>
          </el-form-item>
        </template>
      </el-form>
    </section>
    <!-- 底部栏 -->
    <section class="bar-footer">
      <section class="footer-slot">
        <slot name="footer" :form="formRef" :="props"></slot>
      </section>
      <section>
        <el-button
          v-if="showreset && !props.formattr?.disabled"
          type="warning"
          icon="IconReset"
          @click="formRef?.resetFields()"
        >
          重置
        </el-button>
        <el-button
          v-if="!props.formattr?.disabled"
          type="success"
          icon="IconFinished"
          @click="submitForm"
        >
          {{ props.submittext }}
        </el-button>
      </section>
    </section>
  </section>
</template>
<script setup lang="ts" generic="T extends Record<string, any> = Record<string, any>">
import { ref, reactive } from 'vue'
import { ElMessage, ElMessageBox, type FormInstance } from 'element-plus'
import type { MyFormProps } from '@/components/myform/type'
import MyFormRender from '../myform/MyFormRender.vue'
import { useRouter } from 'vue-router'
import { isEqualWithEmpty } from '@/utils/object'

// 获取路由操作对象
const router = useRouter()

// 组件属性定义
const props = withDefaults(defineProps<MyFormProps<T>>(), {
  showback: true,
  showreset: true,
  submittext: '提交'
})

// 数据本地存储
const localmodel = reactive({ ...props.model })

// 声明emit事件
const emit = defineEmits<{
  /** 表单值改变事件 */
  (event: 'model-change', prop: string, val: any): void
  /** 提交事件 */
  (event: 'do-submit', data: T): void
}>()

// 表单实例
const formRef = ref<FormInstance>()

/**
 * 提交表单
 */
function submitForm() {
  formRef.value?.validate((valid) => {
    if (valid) {
      emit('do-submit', localmodel as T)
    } else {
      ElMessage.error('请检查你的表单数据是否均填写正确')
    }
  })
}

/**
 * 返回逻辑
 */
function handleBack() {
  if (
    props.disableBeforeClose ||
    props.formattr?.disabled ||
    isEqualWithEmpty(localmodel, props.model)
  ) {
    router.go(-1)
  } else {
    ElMessageBox.confirm('你有尚未提交的更改，是确定否返回？', '提示', {
      confirmButtonText: '确定返回',
      cancelButtonText: '点错了',
      type: 'warning'
    })
      .then(() => router.go(-1))
      .catch(() => {})
  }
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
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  align-items: center;
  .header-slot {
    display: flex;
    justify-content: flex-end;
    align-items: center;
    gap: 10px;
  }
}
.bar-body {
  margin-top: 14px;
  display: flex;
  flex-direction: row;
  justify-content: center;
  .el-form {
    width: 95%;
  }
}
.bar-footer {
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
