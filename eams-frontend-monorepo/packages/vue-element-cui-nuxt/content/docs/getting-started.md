# 快速开始

欢迎使用 Vue Element CUI 组件库！本指南将帮助您快速上手。

## 安装

使用您喜欢的包管理器安装：

### pnpm (推荐)

```bash
pnpm add @eams/vue-element-cui
```

### npm

```bash
npm install @eams/vue-element-cui
```

### yarn

```bash
yarn add @eams/vue-element-cui
```

## 基础使用

### 全局注册

在您的 `main.ts` 或 `main.js` 中：

```typescript
import { createApp } from 'vue'
import App from './App.vue'
import VueElementCui from '@eams/vue-element-cui'
import '@eams/vue-element-cui/dist/style.css'

const app = createApp(App)
app.use(VueElementCui)
app.mount('#app')
```

### 按需导入

推荐使用按需导入以减小打包体积：

```vue
<script setup lang="ts">
import { CuiTable, CuiForm } from '@eams/vue-element-cui'
import '@eams/vue-element-cui/dist/style.css'
</script>

<template>
  <div>
    <CuiTable :data="tableData" :columns="columns" />
    <CuiForm :model="formData" :rules="rules" />
  </div>
</template>
```

## 样式导入

组件库依赖 Element Plus，请确保已安装并导入样式：

```typescript
import 'element-plus/dist/index.css'
import '@eams/vue-element-cui/dist/style.css'
```

## TypeScript 支持

组件库完全使用 TypeScript 编写，提供完整的类型定义：

```typescript
import type { CuiTableColumn, CuiFormRule } from '@eams/vue-element-cui'

const columns: CuiTableColumn[] = [
  { prop: 'name', label: '姓名' },
  { prop: 'age', label: '年龄' }
]
```

## 下一步

- 查看 [CuiTable 表格](/docs/components/table) 组件文档
- 查看 [CuiForm 表单](/docs/components/form) 组件文档
- 查看 [CuiSearch 搜索](/docs/components/search) 组件文档

## 示例项目

查看我们的示例项目了解更多用法：

```bash
git clone https://github.com/eams/vue-element-cui-examples.git
cd vue-element-cui-examples
pnpm install
pnpm dev
```

## 获取帮助

如果您遇到问题或有建议，欢迎：

- 提交 [Issue](https://github.com/eams/vue-element-cui/issues)
- 查看 [常见问题](/docs/faq)
- 联系技术支持团队
