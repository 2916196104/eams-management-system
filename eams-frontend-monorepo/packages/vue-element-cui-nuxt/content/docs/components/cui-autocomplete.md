# CuiAutocomplete 组件

CuiAutocomplete 是一个基于 Element Plus 的自动完成组件，支持建议过滤和选择事件。

## 基础用法

```vue
<template>
  <CuiAutocomplete
    v-model="value"
    :suggestions="suggestions"
    placeholder="输入以搜索"
  />
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiAutocomplete } from '@eams/vue-element-cui';
import type { CuiAutocompleteSuggestion } from '@eams/vue-element-cui';

const value = ref('');
const suggestions: CuiAutocompleteSuggestion[] = [
  { value: 'apple', label: 'Apple' },
  { value: 'banana', label: 'Banana' },
];
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| modelValue | string | - | 绑定值 |
| suggestions | CuiAutocompleteSuggestion[] | - | 建议列表 |
| placeholder | string | '请输入' | 占位符 |
| disabled | boolean | false | 是否禁用 |
| clearable | boolean | true | 是否可清空 |

## Events

| 事件名 | 说明 | 回调参数 |
|--------|------|---------|
| update:modelValue | 值变化时触发 | (value: string) |
| select | 选择建议时触发 | (item: CuiAutocompleteSuggestion) |

## CuiAutocompleteSuggestion 接口

```typescript
interface CuiAutocompleteSuggestion {
  value: string;
  label: string;
}
```

## 选择事件示例

```vue
<template>
  <CuiAutocomplete
    v-model="value"
    :suggestions="suggestions"
    @select="handleSelect"
  />
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiAutocomplete } from '@eams/vue-element-cui';
import type { CuiAutocompleteSuggestion } from '@eams/vue-element-cui';

const value = ref('');
const suggestions: CuiAutocompleteSuggestion[] = [
  { value: 'apple', label: 'Apple' },
];

const handleSelect = (item: CuiAutocompleteSuggestion) => {
  console.log('Selected:', item);
};
</script>
```

## 说明

- 组件会自动根据输入值过滤建议列表
- 过滤是不区分大小写的
- 支持与 Element Plus 的 Autocomplete 组件相同的所有功能
