# CuiDetail 组件文档

## 概述

CuiDetail 是一个用于展示详情信息的组件，支持多列布局和自定义渲染。

## 基础用法

```vue
<template>
  <cui-detail
    :fields="fields"
    :data="data"
  />
</template>

<script setup>
import { ref } from 'vue';
import { CuiDetail } from '@packages/vue-element-cui';

const fields = [
  { label: '姓名', prop: 'name' },
  { label: '邮箱', prop: 'email' },
  { label: '电话', prop: 'phone' },
];

const data = ref({
  name: 'John Doe',
  email: 'john@example.com',
  phone: '13800138000',
});
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `fields` | `CuiDetailField[]` | - | 字段配置（必需） |
| `data` | `Record<string, any>` | - | 详情数据（必需） |
| `labelWidth` | `string` | `'140px'` | 标签宽度 |
| `columns` | `number` | `2` | 列数 |

## 字段配置

```typescript
interface CuiDetailField {
  /** 字段标签 */
  label: string;
  /** 字段属性名 */
  prop: string;
  /** 字段宽度 */
  width?: string;
  /** 自定义渲染函数 */
  render?: (row: any) => any;
}
```

## 示例

### 自定义列数

```vue
<template>
  <cui-detail
    :fields="fields"
    :data="data"
    :columns="3"
  />
</template>
```

### 自定义渲染

```vue
<template>
  <cui-detail
    :fields="fields"
    :data="data"
  />
</template>

<script setup>
const fields = [
  { label: '姓名', prop: 'name' },
  {
    label: '状态',
    prop: 'status',
    render: (row) => row.status === 1 ? '活跃' : '禁用',
  },
  {
    label: '创建时间',
    prop: 'createdAt',
    render: (row) => new Date(row.createdAt).toLocaleDateString(),
  },
];
</script>
```
