# CuiSelect 组件

CuiSelect 是一个基于 Element Plus 的选择器组件，支持单选、多选、过滤等功能。

## 基础用法

```vue
<template>
  <CuiSelect
    v-model="value"
    :options="options"
    placeholder="请选择"
  />
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiSelect } from '@eams/vue-element-cui';
import type { CuiSelectOption } from '@eams/vue-element-cui';

const value = ref('');
const options: CuiSelectOption[] = [
  { label: '选项 1', value: 'opt1' },
  { label: '选项 2', value: 'opt2' },
];
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| modelValue | any | - | 绑定值 |
| options | CuiSelectOption[] | [] | 选项列表 |
| placeholder | string | '请选择' | 占位符 |
| disabled | boolean | false | 是否禁用 |
| clearable | boolean | true | 是否可清空 |
| filterable | boolean | true | 是否可过滤 |
| multiple | boolean | false | 是否多选 |

## Events

| 事件名 | 说明 | 回调参数 |
|--------|------|---------|
| update:modelValue | 值变化时触发 | (value: any) |
| change | 值变化时触发 | (value: any) |

## CuiSelectOption 接口

```typescript
interface CuiSelectOption {
  label: string;
  value: any;
  disabled?: boolean;
}
```

## 多选示例

```vue
<template>
  <CuiSelect
    v-model="values"
    :options="options"
    multiple
    placeholder="请选择多个选项"
  />
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiSelect } from '@eams/vue-element-cui';

const values = ref([]);
</script>
```
