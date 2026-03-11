# CuiSelectBox 组件文档

## 概述

CuiSelectBox 是一个高级选择框组件，支持弹出式选择器和自定义选择逻辑。

## 基础用法

```vue
<template>
  <div>
    <cui-select-box
      v-model="selectedValue"
      type="course"
      @submit="handleSubmit"
    >
      <template #selector="{ condition, onSubmit }">
        <!-- 自定义选择器内容 -->
        <div>选择器内容</div>
      </template>
    </cui-select-box>
  </div>
</template>

<script setup>
import { ref } from 'vue';
import { CuiSelectBox } from '@packages/vue-element-cui';

const selectedValue = ref('');

const handleSubmit = (value) => {
  console.log('选择值:', value);
};
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `modelValue` | `string \| string[]` | - | 选中的值（必需） |
| `type` | `string` | - | 选择框类型标识（必需） |
| `limit` | `number` | `0` | 选择限制数量（0 表示不限制） |
| `disabled` | `boolean` | `false` | 是否禁用 |
| `condition` | `Record<string, any>` | `{}` | 搜索条件 |
| `placeholder` | `string` | `'请选择'` | 占位符 |

## Events

| 事件名 | 参数 | 说明 |
|--------|------|------|
| `update:modelValue` | `value: string \| string[]` | 选中值更新 |
| `submit` | `value: string \| string[]` | 选择提交 |

## Slots

| 插槽名 | 参数 | 说明 |
|--------|------|------|
| `selector` | `{ condition, onSubmit }` | 选择器内容 |

## 示例

### 单选

```vue
<template>
  <cui-select-box
    v-model="courseId"
    type="course"
    :limit="1"
    @submit="handleSubmit"
  >
    <template #selector="{ onSubmit }">
      <div class="selector">
        <el-button @click="onSubmit([{ id: '1', label: '课程 1' }])">
          选择课程 1
        </el-button>
      </div>
    </template>
  </cui-select-box>
</template>
```

### 多选

```vue
<template>
  <cui-select-box
    v-model="studentIds"
    type="student"
    @submit="handleSubmit"
  >
    <template #selector="{ onSubmit }">
      <div class="selector">
        <el-checkbox-group v-model="selected">
          <el-checkbox label="学生 1" value="1" />
          <el-checkbox label="学生 2" value="2" />
          <el-checkbox label="学生 3" value="3" />
        </el-checkbox-group>
        <el-button @click="handleSelectSubmit(onSubmit)">确认</el-button>
      </div>
    </template>
  </cui-select-box>
</template>

<script setup>
const selected = ref([]);

const handleSelectSubmit = (onSubmit) => {
  const items = selected.value.map(id => ({
    id,
    label: `学生 ${id}`,
  }));
  onSubmit(items);
};
</script>
```
