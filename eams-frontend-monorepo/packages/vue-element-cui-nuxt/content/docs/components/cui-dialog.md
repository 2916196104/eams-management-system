# CuiDialog 组件文档

## 概述

CuiDialog 是一个基于 Element Plus 的对话框组件，提供了简洁的 API 和灵活的配置选项。

## 基础用法

```vue
<template>
  <div>
    <el-button @click="visible = true">打开对话框</el-button>

    <cui-dialog
      v-model="visible"
      title="对话框标题"
      @confirm="handleConfirm"
      @cancel="handleCancel"
    >
      <p>对话框内容</p>
    </cui-dialog>
  </div>
</template>

<script setup>
import { ref } from 'vue';
import { CuiDialog } from '@eams/vue-element-cui';

const visible = ref(false);

const handleConfirm = () => {
  console.log('确认');
  visible.value = false;
};

const handleCancel = () => {
  console.log('取消');
};
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `modelValue` | `boolean` | - | 对话框是否显示（必需） |
| `title` | `string` | `'提示'` | 对话框标题 |
| `width` | `string \| number` | `'50%'` | 对话框宽度 |
| `showClose` | `boolean` | `true` | 是否显示关闭按钮 |
| `closeOnClickModal` | `boolean` | `false` | 点击遮罩层是否关闭对话框 |
| `beforeClose` | `(done: () => void) => void` | - | 对话框关闭前的回调 |
| `showFooter` | `boolean` | `true` | 是否显示底部按钮栏 |
| `confirmText` | `string` | `'确认'` | 确认按钮文本 |
| `cancelText` | `string` | `'取消'` | 取消按钮文本 |
| `confirmDisabled` | `boolean` | `false` | 是否禁用确认按钮 |
| `loading` | `boolean` | `false` | 是否显示加载状态 |

## Events

| 事件名 | 参数 | 说明 |
|--------|------|------|
| `update:modelValue` | `value: boolean` | 对话框显示状态更新 |
| `confirm` | - | 确认按钮点击事件 |
| `cancel` | - | 取消按钮点击事件 |
| `open` | - | 对话框打开事件 |
| `close` | - | 对话框关闭事件 |

## Slots

| 插槽名 | 说明 |
|--------|------|
| `default` | 对话框内容 |
| `footer-left` | 底部左侧内容 |
| `footer-center` | 底部中间内容（按钮之间） |

## 示例

### 加载状态

```vue
<template>
  <cui-dialog
    v-model="visible"
    title="提交表单"
    :loading="isLoading"
    @confirm="handleSubmit"
  >
    <p>请确认提交</p>
  </cui-dialog>
</template>

<script setup>
import { ref } from 'vue';

const visible = ref(false);
const isLoading = ref(false);

const handleSubmit = async () => {
  isLoading.value = true;
  await new Promise(resolve => setTimeout(resolve, 2000));
  isLoading.value = false;
  visible.value = false;
};
</script>
```

### 自定义按钮文本

```vue
<template>
  <cui-dialog
    v-model="visible"
    title="删除确认"
    confirm-text="删除"
    cancel-text="保留"
    @confirm="handleDelete"
  >
    <p>确定要删除吗？此操作不可撤销。</p>
  </cui-dialog>
</template>
```

### 禁用确认按钮

```vue
<template>
  <cui-dialog
    v-model="visible"
    title="同意条款"
    :confirm-disabled="!agreedToTerms"
    @confirm="handleConfirm"
  >
    <el-checkbox v-model="agreedToTerms">我已阅读并同意条款</el-checkbox>
  </cui-dialog>
</template>

<script setup>
import { ref } from 'vue';

const visible = ref(false);
const agreedToTerms = ref(false);
</script>
```
