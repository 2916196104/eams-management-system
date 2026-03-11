# CuiSelectDict 组件

CuiSelectDict 是一个基于字典代码的选择器组件，自动加载字典选项。

## 基础用法

```vue
<template>
  <CuiSelectDict
    v-model="value"
    dict-code="GENDER"
    placeholder="请选择性别"
  />
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiSelectDict } from '@ruan-cat/vue-element-cui';

const value = ref('');
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| modelValue | any | - | 绑定值 |
| dictCode | string | - | 字典代码 |
| placeholder | string | '请选择' | 占位符 |
| disabled | boolean | false | 是否禁用 |
| clearable | boolean | true | 是否可清空 |
| filterable | boolean | true | 是否可过滤 |

## Events

| 事件名 | 说明 | 回调参数 |
|--------|------|---------|
| update:modelValue | 值变化时触发 | (value: any) |
| change | 值变化时触发 | (value: any) |

## CuiSelectDictOption 接口

```typescript
interface CuiSelectDictOption {
  label: string;
  value: string;
}
```

## 说明

- 组件会在挂载时自动加载指定 `dictCode` 的字典选项
- 实际的字典加载逻辑需要根据项目的字典系统实现
- 支持与 Element Plus 的 Select 组件相同的所有功能
