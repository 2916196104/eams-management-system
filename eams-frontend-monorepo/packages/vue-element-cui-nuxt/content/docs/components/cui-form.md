# CuiForm 表单组件

CuiForm 是基于 Element Plus Form 组件封装的增强型表单组件，提供了动态字段渲染、表单验证、多种字段类型支持等功能。

## 基础用法

使用 `fields` 和 `v-model` 定义表单字段配置和数据绑定。

```vue
<template>
  <CuiForm
    ref="formRef"
    v-model="formData"
    :fields="fields"
  />
  <el-button type="primary" @click="handleSubmit">提交</el-button>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiForm } from '@eams/vue-element-cui';
import type { CuiFormField } from '@eams/vue-element-cui';

const formRef = ref();
const formData = ref({
  name: '',
  email: '',
  age: 0,
});

const fields: CuiFormField[] = [
  {
    prop: 'name',
    label: '姓名',
    type: 'input',
    placeholder: '请输入姓名',
    required: true,
  },
  {
    prop: 'email',
    label: '邮箱',
    type: 'input',
    placeholder: '请输入邮箱',
    required: true,
  },
  {
    prop: 'age',
    label: '年龄',
    type: 'number',
    placeholder: '请输入年龄',
  },
];

const handleSubmit = async () => {
  const result = await formRef.value?.submit();
  if (result?.valid) {
    console.log('表单数据:', formData.value);
  }
};
</script>
```

## 行内表单

通过 `inline` 属性将表单设置为行内布局。

```vue
<CuiForm
  v-model="formData"
  :fields="fields"
  inline
/>
```

## 表单验证

通过 `required` 属性和 `rules` 属性配置表单验证规则。

```vue
<template>
  <CuiForm
    ref="formRef"
    v-model="formData"
    :fields="fields"
  />
</template>

<script setup lang="ts">
const fields: CuiFormField[] = [
  {
    prop: 'username',
    label: '用户名',
    type: 'input',
    placeholder: '请输入用户名',
    required: true,
    rules: [
      { min: 3, max: 20, message: '用户名长度在 3 到 20 个字符', trigger: 'blur' },
    ],
  },
  {
    prop: 'email',
    label: '邮箱',
    type: 'input',
    placeholder: '请输入邮箱',
    required: true,
    rules: [
      { type: 'email', message: '请输入正确的邮箱格式', trigger: 'blur' },
    ],
  },
  {
    prop: 'phone',
    label: '手机号',
    type: 'input',
    placeholder: '请输入手机号',
    rules: [
      { pattern: /^1[3-9]\d{9}$/, message: '请输入正确的手机号', trigger: 'blur' },
    ],
  },
];
</script>
```

## 字段类型

CuiForm 支持多种字段类型。

### 文本输入框

```vue
{
  prop: 'name',
  label: '姓名',
  type: 'input',
  placeholder: '请输入姓名',
}
```

### 多行文本框

```vue
{
  prop: 'description',
  label: '描述',
  type: 'textarea',
  placeholder: '请输入描述',
}
```

### 数字输入框

```vue
{
  prop: 'age',
  label: '年龄',
  type: 'number',
  placeholder: '请输入年龄',
}
```

### 选择框

```vue
{
  prop: 'gender',
  label: '性别',
  type: 'select',
  placeholder: '请选择性别',
  options: [
    { label: '男', value: 'male' },
    { label: '女', value: 'female' },
  ],
}
```

### 日期选择器

```vue
{
  prop: 'birthday',
  label: '生日',
  type: 'date',
  placeholder: '请选择生日',
}
```

## 自定义字段

通过 `slot` 属性和具名插槽自定义字段渲染。

```vue
<template>
  <CuiForm
    v-model="formData"
    :fields="fields"
  >
    <template #customField="{ value, updateValue }">
      <el-slider
        :model-value="value"
        :min="0"
        :max="100"
        @update:model-value="updateValue"
      />
    </template>
  </CuiForm>
</template>

<script setup lang="ts">
const fields: CuiFormField[] = [
  {
    prop: 'score',
    label: '评分',
    type: 'input',
    slot: 'customField',
  },
];
</script>
```

## 表单方法

组件暴露了以下方法供父组件调用。

### validate

验证整个表单。

```vue
<script setup lang="ts">
const formRef = ref();

const handleSubmit = async () => {
  const result = await formRef.value?.validate();
  if (result.valid) {
    console.log('验证通过');
  } else {
    console.log('验证失败', result.errors);
  }
};
</script>
```

### validateField

验证指定字段。

```vue
<script setup lang="ts">
const formRef = ref();

const validateEmail = async () => {
  const valid = await formRef.value?.validateField('email');
  console.log('邮箱验证结果:', valid);
};
</script>
```

### resetFields

重置表单。

```vue
<script setup lang="ts">
const formRef = ref();

const handleReset = () => {
  formRef.value?.resetFields();
};
</script>
```

### clearValidate

清除验证状态。

```vue
<script setup lang="ts">
const formRef = ref();

const clearValidation = () => {
  formRef.value?.clearValidate();
  // 或清除指定字段的验证
  formRef.value?.clearValidate(['email', 'phone']);
};
</script>
```

### submit

提交表单（自动验证）。

```vue
<script setup lang="ts">
const formRef = ref();

const handleSubmit = async () => {
  const result = await formRef.value?.submit();
  if (result?.valid) {
    console.log('提交成功');
  }
};
</script>
```

## 禁用状态

通过 `disabled` 属性禁用整个表单，或在字段配置中设置 `disabled` 禁用单个字段。

```vue
<!-- 禁用整个表单 -->
<CuiForm
  v-model="formData"
  :fields="fields"
  disabled
/>

<!-- 禁用单个字段 -->
<script setup lang="ts">
const fields: CuiFormField[] = [
  {
    prop: 'name',
    label: '姓名',
    type: 'input',
    disabled: true,
  },
];
</script>
```

## 标签位置

通过 `label-position` 属性设置标签位置。

```vue
<!-- 标签在顶部 -->
<CuiForm
  v-model="formData"
  :fields="fields"
  label-position="top"
/>

<!-- 标签在左侧（默认） -->
<CuiForm
  v-model="formData"
  :fields="fields"
  label-position="left"
/>

<!-- 标签在右侧 -->
<CuiForm
  v-model="formData"
  :fields="fields"
  label-position="right"
/>
```

## API 参考

### CuiFormProps

| 属性 | 说明 | 类型 | 默认值 |
| --- | --- | --- | --- |
| fields | 表单字段配置 | `CuiFormField<T>[]` | `[]` |
| modelValue | 表单数据（双向绑定） | `T` | - |
| labelWidth | 标签宽度 | `string \| number` | `'100px'` |
| inline | 是否行内表单 | `boolean` | `false` |
| disabled | 是否禁用整个表单 | `boolean` | `false` |
| labelPosition | 标签位置 | `'left' \| 'right' \| 'top'` | `'right'` |

### CuiFormField

| 属性 | 说明 | 类型 | 默认值 |
| --- | --- | --- | --- |
| prop | 字段属性名 | `string` | - |
| label | 字段标签 | `string` | - |
| type | 字段类型 | `'input' \| 'select' \| 'date' \| 'textarea' \| 'number'` | - |
| placeholder | 占位符文本 | `string` | - |
| required | 是否必填 | `boolean` | `false` |
| rules | 验证规则 | `FormItemRule[]` | - |
| options | 选择框选项（type 为 select 时使用） | `CuiFormSelectOption[]` | - |
| disabled | 是否禁用 | `boolean` | `false` |
| defaultValue | 默认值 | `any` | - |
| slot | 自定义插槽名称 | `string` | - |

### CuiFormSelectOption

| 属性 | 说明 | 类型 | 默认值 |
| --- | --- | --- | --- |
| label | 选项标签 | `string` | - |
| value | 选项值 | `any` | - |
| disabled | 是否禁用 | `boolean` | `false` |

### Events

| 事件名 | 说明 | 回调参数 |
| --- | --- | --- |
| update:modelValue | 表单数据更新时触发 | `value: T` |
| submit | 表单提交时触发（验证通过） | `value: T` |
| reset | 表单重置时触发 | - |

### Methods

| 方法名 | 说明 | 参数 | 返回值 |
| --- | --- | --- | --- |
| validate | 验证整个表单 | - | `Promise<CuiFormValidateResult>` |
| validateField | 验证指定字段 | `prop: string` | `Promise<boolean>` |
| resetFields | 重置表单 | - | - |
| clearValidate | 清除验证状态 | `props?: string \| string[]` | - |
| submit | 提交表单（自动验证） | - | `Promise<CuiFormValidateResult>` |

### Slots

| 插槽名 | 说明 | 参数 |
| --- | --- | --- |
| [field.slot] | 自定义字段内容 | `{ field: CuiFormField, value: any, updateValue: (val: any) => void }` |

## 注意事项

1. `fields` 和 `modelValue` 是必需的属性
2. 使用自定义插槽时，需要在字段配置中设置 `slot` 属性
3. 验证规则遵循 Element Plus Form 的验证规则格式
4. 组件基于 Element Plus Form，通过 `v-bind="$attrs"` 透传其他 props 和事件
5. 支持 TypeScript 泛型，可以为表单数据指定类型
6. 表单提交前会自动进行验证，验证失败时不会触发 `submit` 事件

## 类型定义

```typescript
type CuiFormFieldType = 'input' | 'select' | 'date' | 'textarea' | 'number';

interface CuiFormSelectOption {
  label: string;
  value: any;
  disabled?: boolean;
}

interface CuiFormField<T = any> {
  prop: keyof T & string;
  label: string;
  type: CuiFormFieldType;
  placeholder?: string;
  required?: boolean;
  rules?: FormItemRule[];
  options?: CuiFormSelectOption[];
  disabled?: boolean;
  defaultValue?: any;
  slot?: string;
}

interface CuiFormProps<T = any> {
  fields: CuiFormField<T>[];
  modelValue: T;
  labelWidth?: string | number;
  inline?: boolean;
  disabled?: boolean;
  labelPosition?: 'left' | 'right' | 'top';
}

interface CuiFormValidateResult {
  valid: boolean;
  errors?: Record<string, string[]>;
}
```
