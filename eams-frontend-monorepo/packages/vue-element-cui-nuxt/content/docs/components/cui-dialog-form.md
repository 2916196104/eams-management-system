# CuiDialogForm 组件文档

## 概述

CuiDialogForm 是一个结合了对话框和表单功能的组件，用于在对话框中展示和提交表单数据。

## 基础用法

```vue
<template>
  <div>
    <el-button @click="visible = true">打开表单对话框</el-button>

    <cui-dialog-form
      :visible="visible"
      title="用户信息"
      :fields="formFields"
      :model-value="formData"
      @update:visible="visible = $event"
      @update:model-value="formData = $event"
      @submit="handleSubmit"
    />
  </div>
</template>

<script setup>
import { ref } from 'vue';
import { CuiDialogForm } from '@eams/vue-element-cui';

const visible = ref(false);
const formData = ref({ name: '', email: '' });

const formFields = [
  {
    prop: 'name',
    label: '姓名',
    type: 'input',
    placeholder: '请输入姓名',
  },
  {
    prop: 'email',
    label: '邮箱',
    type: 'input',
    placeholder: '请输入邮箱',
  },
];

const handleSubmit = (data) => {
  console.log('提交数据:', data);
  visible.value = false;
};
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `visible` | `boolean` | - | 对话框是否显示（必需） |
| `modelValue` | `object` | - | 表单数据（必需） |
| `title` | `string` | `'表单对话框'` | 对话框标题 |
| `width` | `string \| number` | `'50%'` | 对话框宽度 |
| `showClose` | `boolean` | `true` | 是否显示关闭按钮 |
| `closeOnClickModal` | `boolean` | `false` | 点击遮罩层是否关闭对话框 |
| `fields` | `CuiFormField[]` | - | 表单字段配置（必需） |
| `labelWidth` | `string \| number` | `'100px'` | 标签宽度 |
| `inline` | `boolean` | `false` | 是否行内表单 |
| `disabled` | `boolean` | `false` | 是否禁用整个表单 |
| `labelPosition` | `'left' \| 'right' \| 'top'` | `'right'` | 标签位置 |
| `confirmText` | `string` | `'确认'` | 确认按钮文本 |
| `cancelText` | `string` | `'取消'` | 取消按钮文本 |
| `confirmDisabled` | `boolean` | `false` | 是否禁用确认按钮 |
| `loading` | `boolean` | `false` | 是否显示加载状态 |

## Events

| 事件名 | 参数 | 说明 |
|--------|------|------|
| `update:visible` | `value: boolean` | 对话框显示状态更新 |
| `update:modelValue` | `value: object` | 表单数据更新 |
| `submit` | `value: object` | 表单提交事件 |
| `cancel` | - | 取消按钮点击事件 |
| `open` | - | 对话框打开事件 |
| `close` | - | 对话框关闭事件 |

## Methods

通过 `ref` 可以调用以下方法：

| 方法名 | 参数 | 说明 |
|--------|------|------|
| `resetForm` | - | 重置表单 |
| `setFormData` | `data: object` | 设置表单数据 |

## 表单字段配置

```typescript
interface CuiFormField {
  /** 字段属性名 */
  prop: string;
  /** 字段标签 */
  label: string;
  /** 字段类型：input, textarea, number, select, date */
  type: string;
  /** 占位符 */
  placeholder?: string;
  /** 是否必填 */
  required?: boolean;
  /** 验证规则 */
  rules?: FormItemRule[];
  /** 选择框选项 */
  options?: Array<{ label: string; value: any }>;
  /** 是否禁用 */
  disabled?: boolean;
  /** 默认值 */
  defaultValue?: any;
  /** 自定义插槽名称 */
  slot?: string;
}
```

## 示例

### 带验证的表单

```vue
<template>
  <cui-dialog-form
    v-model="visible"
    title="注册表单"
    :fields="formFields"
    :model-value="formData"
    @submit="handleSubmit"
  />
</template>

<script setup>
import { ref } from 'vue';

const visible = ref(false);
const formData = ref({ username: '', password: '' });

const formFields = [
  {
    prop: 'username',
    label: '用户名',
    type: 'input',
    required: true,
    rules: [{ required: true, message: '用户名不能为空' }],
  },
  {
    prop: 'password',
    label: '密码',
    type: 'input',
    required: true,
    rules: [{ required: true, message: '密码不能为空' }],
  },
];

const handleSubmit = (data) => {
  console.log('提交:', data);
};
</script>
```

### 加载状态

```vue
<template>
  <cui-dialog-form
    ref="dialogFormRef"
    v-model="visible"
    title="提交表单"
    :fields="formFields"
    :model-value="formData"
    :loading="isSubmitting"
    @submit="handleSubmit"
  />
</template>

<script setup>
import { ref } from 'vue';

const visible = ref(false);
const isSubmitting = ref(false);
const formData = ref({ title: '', content: '' });

const formFields = [
  { prop: 'title', label: '标题', type: 'input' },
  { prop: 'content', label: '内容', type: 'textarea' },
];

const handleSubmit = async (data) => {
  isSubmitting.value = true;
  try {
    await submitForm(data);
    visible.value = false;
  } finally {
    isSubmitting.value = false;
  }
};
</script>
```

### 编程式控制

```vue
<template>
  <div>
    <el-button @click="openForm">打开表单</el-button>

    <cui-dialog-form
      ref="dialogFormRef"
      v-model="visible"
      title="编辑用户"
      :fields="formFields"
      :model-value="formData"
      @submit="handleSubmit"
    />
  </div>
</template>

<script setup>
import { ref } from 'vue';

const dialogFormRef = ref();
const visible = ref(false);
const formData = ref({ name: '', email: '' });

const formFields = [
  { prop: 'name', label: '姓名', type: 'input' },
  { prop: 'email', label: '邮箱', type: 'input' },
];

const openForm = (userId) => {
  // 获取用户数据
  const userData = { name: 'John', email: 'john@example.com' };
  dialogFormRef.value.setFormData(userData);
  visible.value = true;
};

const handleSubmit = (data) => {
  console.log('提交:', data);
};
</script>
```
