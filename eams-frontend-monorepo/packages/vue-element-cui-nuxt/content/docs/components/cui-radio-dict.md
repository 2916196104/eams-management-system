# CuiRadioDict 组件

CuiRadioDict 是一个基于字典代码的单选框组件，自动加载字典选项。

## 基础用法

```vue
<template>
  <CuiRadioDict
    v-model="value"
    dict-code="GENDER"
  />
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiRadioDict } from '@eams/vue-element-cui';

const value = ref('');
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| modelValue | any | - | 绑定值 |
| dictCode | string | - | 字典代码 |
| disabled | boolean | false | 是否禁用 |

## Events

| 事件名 | 说明 | 回调参数 |
|--------|------|---------|
| update:modelValue | 值变化时触发 | (value: any) |
| change | 值变化时触发 | (value: any) |

## CuiRadioDictOption 接口

```typescript
interface CuiRadioDictOption {
  label: string;
  value: string;
}
```

## 说明

- 组件会在挂载时自动加载指定 `dictCode` 的字典选项
- 实际的字典加载逻辑需要根据项目的字典系统实现
- 支持与 Element Plus 的 Radio 组件相同的所有功能
