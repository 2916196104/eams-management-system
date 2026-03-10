# CuiExcel 组件文档

## 概述

CuiExcel 是一个用于 Excel 文件导入的组件，提供了拖拽上传和模板下载功能。

## 基础用法

```vue
<template>
  <div>
    <el-button @click="visible = true">打开 Excel 导入</el-button>

    <cui-excel
      v-model="visible"
      title="导入 Excel 数据"
      upload-url="http://example.com/upload"
      @success="handleSuccess"
    />
  </div>
</template>

<script setup>
import { ref } from 'vue';
import { CuiExcel } from '@packages/vue-element-cui';

const visible = ref(false);

const handleSuccess = (response, file, fileList) => {
  console.log('上传成功', response);
};
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `modelValue` | `boolean` | - | 对话框是否显示（必需） |
| `uploadUrl` | `string` | - | 上传 URL（必需） |
| `title` | `string` | `'导入 Excel'` | 对话框标题 |
| `templateUrl` | `string` | - | 模板下载 URL |
| `headers` | `Record<string, string>` | `{}` | 上传请求头 |
| `params` | `Record<string, any>` | `{}` | 上传额外参数 |
| `accept` | `string` | `'.xls,.xlsx'` | 接受的文件类型 |

## Events

| 事件名 | 参数 | 说明 |
|--------|------|------|
| `update:modelValue` | `value: boolean` | 对话框显示状态更新 |
| `success` | `response, file, fileList` | 上传成功 |
| `error` | `error` | 上传失败 |

## 示例

### 带模板下载

```vue
<template>
  <cui-excel
    v-model="visible"
    title="导入学生数据"
    upload-url="http://example.com/upload"
    template-url="http://example.com/template.xlsx"
    @success="handleSuccess"
  />
</template>
```

### 自定义请求头和参数

```vue
<template>
  <cui-excel
    v-model="visible"
    upload-url="http://example.com/upload"
    :headers="{ Authorization: 'Bearer token' }"
    :params="{ type: 'student' }"
    @success="handleSuccess"
  />
</template>

<script setup>
const handleSuccess = (response) => {
  if (response.code === 0) {
    ElMessage.success('导入成功');
  }
};
</script>
```
