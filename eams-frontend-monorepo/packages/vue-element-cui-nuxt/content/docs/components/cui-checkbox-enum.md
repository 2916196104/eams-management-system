# CuiCheckboxEnum 组件

CuiCheckboxEnum 是一个基于枚举代码的复选框组件，自动加载枚举选项。

## 基础用法

```vue
<template>
  <CuiCheckboxEnum
    v-model="values"
    enum-code="PERMISSIONS"
  />
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiCheckboxEnum } from '@eams/vue-element-cui';

const values = ref([]);
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| modelValue | any[] | - | 绑定值（数组） |
| enumCode | string | - | 枚举代码 |
| disabled | boolean | false | 是否禁用 |

## Events

| 事件名 | 说明 | 回调参数 |
|--------|------|---------|
| update:modelValue | 值变化时触发 | (value: any[]) |
| change | 值变化时触发 | (value: any[]) |

## CuiCheckboxEnumOption 接口

```typescript
interface CuiCheckboxEnumOption {
  label: string;
  value: string;
}
```

## 说明

- 组件会在挂载时自动加载指定 `enumCode` 的枚举选项
- `modelValue` 是一个数组，包含所有选中的值
- 实际的枚举加载逻辑需要根据项目的枚举系统实现
- 支持与 Element Plus 的 Checkbox 组件相同的所有功能
