# Vue Element CUI 组件库迁移实施计划

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** 将 old/vue-element-cui (Vue 2) 完全重写为现代化组件库 packages/vue-element-cui (Vue 3 + TypeScript + Vite)，并配套 Nuxt 3 playground + docs

**Architecture:** 采用 Nuxt 3 All-in-One 架构（playground + docs 合并），核心组件库使用 Vite 构建，支持 ESM/CJS 双格式输出和完整的 TypeScript 类型声明

**Tech Stack:** Vue 3, TypeScript, Vite, Element Plus, SCSS, Nuxt 3, Nuxt Content, vitest

---

## 阶段 1：基础设施搭建

### Task 1.1: 初始化 vue-element-cui 核心包

**Files:**
- Create: `packages/vue-element-cui/package.json`
- Create: `packages/vue-element-cui/tsconfig.json`
- Create: `packages/vue-element-cui/vite.config.ts`
- Create: `packages/vue-element-cui/src/index.ts`
- Create: `packages/vue-element-cui/.gitignore`

**Step 1: 创建 package.json**

```json
{
  "name": "vue-element-cui",
  "version": "0.1.0",
  "description": "Modern Vue 3 component library based on Element Plus",
  "type": "module",
  "main": "./dist/index.cjs",
  "module": "./dist/index.js",
  "types": "./dist/index.d.ts",
  "exports": {
    ".": {
      "types": "./dist/index.d.ts",
      "import": "./dist/index.js",
      "require": "./dist/index.cjs"
    },
    "./styles": "./dist/styles/index.css",
    "./styles/*": "./dist/styles/*.css"
  },
  "files": ["dist"],
  "scripts": {
    "dev": "vite build --watch",
    "build": "vite build && pnpm run build:styles",
    "test": "vitest run",
    "test:watch": "vitest",
    "test:coverage": "vitest run --coverage"
  },
  "peerDependencies": {
    "vue": "^3.4.0",
    "element-plus": "^2.8.0"
  },
  "devDependencies": {
    "@vitejs/plugin-vue": "^5.0.0",
    "@vue/test-utils": "^2.4.0",
    "element-plus": "^2.8.0",
    "jsdom": "^24.0.0",
    "sass": "^1.70.0",
    "typescript": "^5.3.0",
    "vite": "^5.0.0",
    "vite-plugin-dts": "^7.0.0",
    "vitest": "^1.2.0",
    "vue": "^3.4.0"
  }
}
```

**Step 2: 创建 tsconfig.json**

```json
{
  "compilerOptions": {
    "target": "ES2020",
    "module": "ESNext",
    "moduleResolution": "bundler",
    "strict": true,
    "jsx": "preserve",
    "declaration": true,
    "declarationMap": true,
    "skipLibCheck": true,
    "esModuleInterop": true,
    "resolveJsonModule": true,
    "isolatedModules": true,
    "lib": ["ES2020", "DOM", "DOM.Iterable"]
  },
  "include": ["src/**/*"],
  "exclude": ["node_modules", "dist", "**/*.test.ts"]
}
```

**Step 3: 创建 vite.config.ts**

```typescript
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import dts from 'vite-plugin-dts'

export default defineConfig({
  plugins: [
    vue(),
    dts({
      include: ['src/**/*.ts', 'src/**/*.vue'],
      exclude: ['src/**/*.test.ts']
    })
  ],
  build: {
    lib: {
      entry: 'src/index.ts',
      name: 'VueElementCui',
      formats: ['es', 'cjs'],
      fileName: (format) => `index.${format === 'es' ? 'js' : 'cjs'}`
    },
    rollupOptions: {
      external: ['vue', 'element-plus', '@element-plus/icons-vue', 'xlsx'],
      output: {
        globals: {
          vue: 'Vue',
          'element-plus': 'ElementPlus'
        }
      }
    }
  }
})
```

**Step 4: 创建 src/index.ts 占位文件**

```typescript
// Vue Element CUI - Modern Component Library
export const version = '0.1.0'
```

**Step 5: 创建 .gitignore**

```
node_modules
dist
*.log
.DS_Store
coverage
```

**Step 6: 安装依赖**

Run: `cd packages/vue-element-cui && pnpm install`
Expected: 依赖安装成功

**Step 7: 测试构建**

Run: `pnpm build`
Expected: 在 dist/ 目录生成 index.js, index.cjs, index.d.ts

**Step 8: Commit**

```bash
git add packages/vue-element-cui
git commit -m "🎉 init(vue-element-cui): 初始化核心组件库包结构

- 配置 Vite 构建工具
- 配置 TypeScript 严格模式
- 配置 vitest 测试框架
- 支持 ESM/CJS 双格式输出

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
```

---

### Task 1.2: 配置 vitest 测试环境

**Files:**
- Create: `packages/vue-element-cui/vitest.config.ts`
- Create: `packages/vue-element-cui/src/tests/.gitkeep`

**Step 1: 创建 vitest.config.ts**

```typescript
import { defineConfig } from 'vitest/config'
import vue from '@vitejs/plugin-vue'
import { resolve } from 'path'

export default defineConfig({
  plugins: [vue()],
  test: {
    environment: 'jsdom',
    globals: true,
    coverage: {
      provider: 'v8',
      reporter: ['text', 'json', 'html'],
      exclude: [
        'node_modules/',
        'dist/',
        '**/*.test.ts',
        '**/*.config.ts'
      ]
    }
  },
  resolve: {
    alias: {
      '@': resolve(__dirname, 'src')
    }
  }
})
```

**Step 2: 创建测试目录占位文件**

```bash
mkdir -p packages/vue-element-cui/src/tests
touch packages/vue-element-cui/src/tests/.gitkeep
```

**Step 3: 编写示例测试验证配置**

Create: `packages/vue-element-cui/src/tests/setup.test.ts`

```typescript
import { describe, test, expect } from 'vitest'

describe('Test Environment', () => {
  test('vitest is working', () => {
    expect(1 + 1).toBe(2)
  })
})
```

**Step 4: 运行测试验证**

Run: `pnpm test`
Expected: ✓ Test Environment > vitest is working

**Step 5: Commit**

```bash
git add packages/vue-element-cui/vitest.config.ts packages/vue-element-cui/src/tests
git commit -m "🔧 config(vue-element-cui): 配置 vitest 测试环境

- 配置 jsdom 环境
- 配置测试覆盖率报告
- 添加路径别名支持

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
```

---

### Task 1.3: 初始化样式系统

**Files:**
- Create: `packages/vue-element-cui/src/styles/index.scss`
- Create: `packages/vue-element-cui/src/styles/variables.scss`
- Create: `packages/vue-element-cui/src/styles/mixins.scss`

**Step 1: 创建 variables.scss**

```scss
// Color System
$cui-primary-color: #409eff;
$cui-success-color: #67c23a;
$cui-warning-color: #e6a23c;
$cui-danger-color: #f56c6c;
$cui-info-color: #909399;

// Typography
$cui-font-size-base: 14px;
$cui-font-size-small: 12px;
$cui-font-size-large: 16px;

// Spacing
$cui-spacing-xs: 4px;
$cui-spacing-sm: 8px;
$cui-spacing-md: 16px;
$cui-spacing-lg: 24px;
$cui-spacing-xl: 32px;

// Border
$cui-border-radius-base: 4px;
$cui-border-color-base: #dcdfe6;

// Component Prefix
$cui-namespace: 'cui';
```

**Step 2: 创建 mixins.scss**

```scss
@use 'variables' as *;

// BEM Naming Convention
@mixin b($block) {
  $B: $cui-namespace + '-' + $block;
  .#{$B} {
    @content;
  }
}

@mixin e($element) {
  $selector: &;
  @at-root {
    #{$selector}__#{$element} {
      @content;
    }
  }
}

@mixin m($modifier) {
  $selector: &;
  @at-root {
    #{$selector}--#{$modifier} {
      @content;
    }
  }
}

// Utility Mixins
@mixin clearfix {
  &::after {
    content: '';
    display: table;
    clear: both;
  }
}

@mixin ellipsis {
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
}
```

**Step 3: 创建 index.scss**

```scss
@use 'variables';
@use 'mixins';

// Global Styles
* {
  box-sizing: border-box;
}

// Component styles will be imported here
// @use './components/cui-table';
// @use './components/cui-form';
```

**Step 4: 配置样式构建**

Modify: `packages/vue-element-cui/package.json`

Add to scripts:
```json
"build:styles": "sass src/styles/index.scss dist/styles/index.css --no-source-map",
"build": "vite build && pnpm run build:styles"
```

**Step 5: 测试样式构建**

Run: `pnpm build`
Expected: dist/styles/index.css 文件生成

**Step 6: Commit**

```bash
git add packages/vue-element-cui/src/styles packages/vue-element-cui/package.json
git commit -m "💄 style(vue-element-cui): 初始化 SCSS 样式系统

- 定义颜色、字体、间距等设计变量
- 实现 BEM 命名规范的 mixin
- 配置样式构建流程

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
```

---

### Task 1.4: 初始化 vue-element-cui-nuxt 项目

**Files:**
- Create: `packages/vue-element-cui-nuxt/package.json`
- Create: `packages/vue-element-cui-nuxt/nuxt.config.ts`
- Create: `packages/vue-element-cui-nuxt/tsconfig.json`
- Create: `packages/vue-element-cui-nuxt/app.vue`
- Create: `packages/vue-element-cui-nuxt/.gitignore`

**Step 1: 创建 package.json**

```json
{
  "name": "vue-element-cui-nuxt",
  "version": "0.1.0",
  "private": true,
  "type": "module",
  "scripts": {
    "dev": "nuxt dev",
    "build": "nuxt build",
    "generate": "nuxt generate",
    "preview": "nuxt preview"
  },
  "dependencies": {
    "element-plus": "^2.8.0",
    "vue-element-cui": "workspace:*"
  },
  "devDependencies": {
    "@nuxt/content": "^2.12.0",
    "@nuxtjs/tailwindcss": "^6.11.0",
    "nuxt": "^3.10.0",
    "sass": "^1.70.0",
    "vue": "^3.4.0"
  }
}
```

**Step 2: 创建 nuxt.config.ts**

```typescript
export default defineNuxtConfig({
  modules: ['@nuxt/content', '@nuxtjs/tailwindcss'],

  content: {
    highlight: {
      theme: 'github-dark',
      preload: ['vue', 'typescript', 'bash']
    },
    markdown: {
      toc: {
        depth: 3,
        searchDepth: 3
      }
    }
  },

  css: [
    'element-plus/dist/index.css',
    'vue-element-cui/dist/styles/index.css'
  ],

  vite: {
    optimizeDeps: {
      include: ['element-plus', 'vue-element-cui']
    }
  },

  devtools: { enabled: true }
})
```

**Step 3: 创建 tsconfig.json**

```json
{
  "extends": "./.nuxt/tsconfig.json"
}
```

**Step 4: 创建 app.vue**

```vue
<template>
  <div>
    <NuxtPage />
  </div>
</template>
```

**Step 5: 创建 .gitignore**

```
node_modules
.nuxt
.output
dist
*.log
.DS_Store
.env
```

**Step 6: 安装依赖**

Run: `cd packages/vue-element-cui-nuxt && pnpm install`
Expected: 依赖安装成功

**Step 7: 创建首页**

Create: `packages/vue-element-cui-nuxt/pages/index.vue`

```vue
<template>
  <div class="container mx-auto px-4 py-8">
    <h1 class="text-4xl font-bold mb-4">Vue Element CUI</h1>
    <p class="text-lg text-gray-600">
      Modern Vue 3 Component Library
    </p>
  </div>
</template>
```

**Step 8: 测试启动**

Run: `pnpm dev`
Expected: Nuxt 开发服务器启动，访问 http://localhost:3000 显示首页

**Step 9: Commit**

```bash
git add packages/vue-element-cui-nuxt
git commit -m "🎉 init(vue-element-cui-nuxt): 初始化 Nuxt 3 playground 项目

- 配置 Nuxt Content 文档系统
- 集成 Element Plus 和 vue-element-cui
- 配置 Tailwind CSS
- 创建首页

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
```

---

### Task 1.5: 配置 Nuxt Content 文档结构

**Files:**
- Create: `packages/vue-element-cui-nuxt/content/docs/getting-started.md`
- Create: `packages/vue-element-cui-nuxt/content/docs/components/.gitkeep`
- Create: `packages/vue-element-cui-nuxt/pages/docs/[...slug].vue`

**Step 1: 创建文档首页**

```markdown
# Getting Started

欢迎使用 Vue Element CUI 组件库！

## 安装

```bash
pnpm add vue-element-cui element-plus
```

## 快速开始

```typescript
import { createApp } from 'vue'
import ElementPlus from 'element-plus'
import VueElementCui from 'vue-element-cui'
import 'element-plus/dist/index.css'
import 'vue-element-cui/dist/styles/index.css'

const app = createApp(App)
app.use(ElementPlus)
app.use(VueElementCui)
app.mount('#app')
```

## 组件列表

- [CuiTable](/docs/components/cui-table) - 数据表格
- [CuiForm](/docs/components/cui-form) - 表单构建器
- 更多组件开发中...
```

**Step 2: 创建文档页面模板**

```vue
<template>
  <div class="docs-container">
    <aside class="docs-sidebar">
      <ContentNavigation v-slot="{ navigation }">
        <nav>
          <ul>
            <li v-for="link in navigation" :key="link._path">
              <NuxtLink :to="link._path">
                {{ link.title }}
              </NuxtLink>
            </li>
          </ul>
        </nav>
      </ContentNavigation>
    </aside>

    <main class="docs-content">
      <ContentDoc />
    </main>
  </div>
</template>

<style scoped>
.docs-container {
  display: flex;
  max-width: 1200px;
  margin: 0 auto;
  padding: 2rem;
}

.docs-sidebar {
  width: 250px;
  margin-right: 2rem;
}

.docs-content {
  flex: 1;
}
</style>
```

**Step 3: 创建组件文档目录占位**

```bash
mkdir -p packages/vue-element-cui-nuxt/content/docs/components
touch packages/vue-element-cui-nuxt/content/docs/components/.gitkeep
```

**Step 4: 测试文档访问**

Run: `pnpm dev`
Visit: `http://localhost:3000/docs/getting-started`
Expected: 显示 Getting Started 文档

**Step 5: Commit**

```bash
git add packages/vue-element-cui-nuxt/content packages/vue-element-cui-nuxt/pages/docs
git commit -m "📃 docs(vue-element-cui-nuxt): 配置 Nuxt Content 文档结构

- 创建 Getting Started 文档
- 创建文档页面模板
- 配置文档导航

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
```

---

### Task 1.6: 配置 Volar 全局类型支持

**Files:**
- Create: `packages/vue-element-cui/src/global.d.ts`
- Modify: `packages/vue-element-cui/tsconfig.json`

**Step 1: 创建 global.d.ts**

```typescript
import type { DefineComponent } from 'vue'

declare module '@vue/runtime-core' {
  export interface GlobalComponents {
    // Components will be added here as they are implemented
    // CuiTable: DefineComponent<typeof import('./components/cui-table')['cuiTableProps']>
  }
}

export {}
```

**Step 2: 更新 tsconfig.json**

Modify include array:
```json
{
  "include": ["src/**/*", "src/global.d.ts"]
}
```

**Step 3: 更新 package.json exports**

Add to exports:
```json
"./global": "./src/global.d.ts"
```

**Step 4: Commit**

```bash
git add packages/vue-element-cui/src/global.d.ts packages/vue-element-cui/tsconfig.json packages/vue-element-cui/package.json
git commit -m "🔧 config(vue-element-cui): 配置 Volar 全局类型支持

- 创建全局类型声明文件
- 配置 TypeScript 包含全局类型
- 导出全局类型声明

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
```

---

## 阶段 2：P0 核心组件迁移

### Task 2.1: 实现 CuiTable 组件（第 1 部分：基础结构）

**Files:**
- Create: `packages/vue-element-cui/src/components/cui-table/index.ts`
- Create: `packages/vue-element-cui/src/components/cui-table/types.ts`
- Create: `packages/vue-element-cui/src/components/cui-table/cui-table.vue`
- Create: `packages/vue-element-cui/src/tests/cui-table.test.ts`

**Step 1: 编写类型定义**

```typescript
// types.ts
export interface CuiTableColumn<T = any> {
  prop: keyof T
  label: string
  width?: string | number
  minWidth?: string | number
  sortable?: boolean
  align?: 'left' | 'center' | 'right'
  fixed?: boolean | 'left' | 'right'
  formatter?: (row: T, column: CuiTableColumn<T>, cellValue: any) => string
  slot?: string
}

export interface CuiTableProps<T = any> {
  data: T[]
  columns: CuiTableColumn<T>[]
  loading?: boolean
  selectable?: boolean
  indexed?: boolean
  height?: string | number
  maxHeight?: string | number
  border?: boolean
  stripe?: boolean
  emptyText?: string
}

export interface CuiTableEmits<T = any> {
  'selection-change': [selection: T[]]
  'sort-change': [column: CuiTableColumn<T>, order: 'ascending' | 'descending' | null]
  'row-click': [row: T, column: CuiTableColumn<T>, event: Event]
}
```

**Step 2: 编写失败的测试**

```typescript
// src/tests/cui-table.test.ts
import { describe, test, expect } from 'vitest'
import { mount } from '@vue/test-utils'
import { CuiTable } from '../components/cui-table'

describe('CuiTable', () => {
  test('renders table with data', () => {
    const wrapper = mount(CuiTable, {
      props: {
        data: [{ id: 1, name: 'Test' }],
        columns: [
          { prop: 'id', label: 'ID' },
          { prop: 'name', label: 'Name' }
        ]
      }
    })

    expect(wrapper.find('.cui-table').exists()).toBe(true)
    expect(wrapper.text()).toContain('Test')
  })

  test('renders with empty data', () => {
    const wrapper = mount(CuiTable, {
      props: {
        data: [],
        columns: [{ prop: 'id', label: 'ID' }],
        emptyText: 'No Data'
      }
    })

    expect(wrapper.text()).toContain('No Data')
  })
})
```

**Step 3: 运行测试验证失败**

Run: `pnpm test cui-table`
Expected: FAIL - CuiTable is not defined

**Step 4: 实现最小组件**

```vue
<!-- cui-table.vue -->
<script setup lang="ts" generic="T extends Record<string, any>">
import { ElTable, ElTableColumn } from 'element-plus'
import type { CuiTableProps, CuiTableEmits } from './types'

const props = withDefaults(defineProps<CuiTableProps<T>>(), {
  loading: false,
  selectable: false,
  indexed: false,
  border: true,
  stripe: false,
  emptyText: '暂无数据'
})

const emit = defineEmits<CuiTableEmits<T>>()

const handleSelectionChange = (selection: T[]) => {
  emit('selection-change', selection)
}

const handleSortChange = ({ column, prop, order }: any) => {
  const tableColumn = props.columns.find(col => col.prop === prop)
  if (tableColumn) {
    emit('sort-change', tableColumn, order)
  }
}

const handleRowClick = (row: T, column: any, event: Event) => {
  const tableColumn = props.columns.find(col => col.prop === column.property)
  if (tableColumn) {
    emit('row-click', row, tableColumn, event)
  }
}
</script>

<template>
  <div class="cui-table">
    <ElTable
      :data="data"
      :border="border"
      :stripe="stripe"
      :height="height"
      :max-height="maxHeight"
      v-loading="loading"
      @selection-change="handleSelectionChange"
      @sort-change="handleSortChange"
      @row-click="handleRowClick"
    >
      <ElTableColumn
        v-if="selectable"
        type="selection"
        width="55"
        align="center"
      />

      <ElTableColumn
        v-if="indexed"
        type="index"
        label="序号"
        width="60"
        align="center"
      />

      <ElTableColumn
        v-for="column in columns"
        :key="String(column.prop)"
        :prop="String(column.prop)"
        :label="column.label"
        :width="column.width"
        :min-width="column.minWidth"
        :sortable="column.sortable"
        :align="column.align"
        :fixed="column.fixed"
        :formatter="column.formatter"
      >
        <template v-if="column.slot" #default="scope">
          <slot :name="column.slot" :row="scope.row" :column="column" />
        </template>
      </ElTableColumn>

      <template #empty>
        <span>{{ emptyText }}</span>
      </template>
    </ElTable>
  </div>
</template>

<style scoped lang="scss">
.cui-table {
  width: 100%;
}
</style>
```

**Step 5: 创建导出文件**

```typescript
// index.ts
import CuiTable from './cui-table.vue'
export { CuiTable }
export * from './types'
```

**Step 6: 运行测试验证通过**

Run: `pnpm test cui-table`
Expected: PASS - All tests passing

**Step 7: 更新主入口**

Modify: `packages/vue-element-cui/src/index.ts`

```typescript
export { CuiTable } from './components/cui-table'
export type { CuiTableProps, CuiTableColumn } from './components/cui-table/types'

export const version = '0.1.0'
```

**Step 8: Commit**

```bash
git add packages/vue-element-cui/src/components/cui-table packages/vue-element-cui/src/tests/cui-table.test.ts packages/vue-element-cui/src/index.ts
git commit -m "✨ feat(cui-table): 实现 CuiTable 基础功能

- 支持数据展示、排序、选择
- 支持自定义列配置
- 支持插槽扩展
- 完整的 TypeScript 类型定义
- 单元测试覆盖

Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>"
```

---

## 后续任务概览

由于完整的实施计划非常庞大（17 个组件 + 文档 + 测试），以下是剩余任务的概要：

### 阶段 2 剩余任务：
- Task 2.2: CuiForm 组件实现
- Task 2.3: CuiSearch 组件实现
- Task 2.4: CuiDialogForm 组件实现

### 阶段 3：P1 功能组件
- Task 3.1-3.5: CuiDialog, CuiDetail, CuiExcel, CuiTab, CuiSelectBox

### 阶段 4：P2 表单控件
- Task 4.1-4.7: 7 个表单控件批量实现

### 阶段 5：文档与优化
- Task 5.1: 为所有组件编写 Nuxt Content 文档
- Task 5.2: 创建交互式演示页面
- Task 5.3: 性能优化和打包体积优化
- Task 5.4: 发布 1.0.0 版本

---

## 执行建议

1. **使用 Agent Team 并行开发**：
   - Explorer 子代理：研究 tsdown 和参考项目
   - Editor 子代理：按优先级实现组件
   - Reviewer 子代理：代码审查和质量检查

2. **TDD 开发流程**：
   - 每个组件先写测试
   - 实现最小可用版本
   - 逐步完善功能
   - 保持测试覆盖率

3. **频繁提交**：
   - 每完成一个组件提交一次
   - 提交信息遵循 Conventional Commits
   - 使用 Emoji 前缀

4. **文档同步**：
   - 组件实现后立即编写文档
   - 在 Nuxt playground 中创建演示
   - 确保文档和代码同步更新
