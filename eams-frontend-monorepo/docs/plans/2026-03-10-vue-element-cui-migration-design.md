# 2026-03-10 Vue Element CUI 组件库迁移设计方案

## 项目概述

本文档描述了将 `old\vue-element-cui` 旧组件库迁移到现代化技术栈的完整设计方案。新组件库将位于 `packages\vue-element-cui`，采用 Vue 3 + TypeScript + tsdown 构建，并配套 Nuxt 3 的 playground 和文档系统。

## 核心决策

### 迁移策略
- **完全重写**：从零开始用 Vue 3 Composition API + TypeScript 重新实现所有 17 个组件
- **UI 基础库**：基于 Element Plus（Element UI 的 Vue 3 版本）
- **组件范围**：迁移全部 17 个组件
- **样式方案**：继续使用 SCSS
- **项目结构**：Nuxt 3 All-in-One 架构（playground + docs 合并）

### 技术栈

| 类别 | 技术选型 |
|------|---------|
| 构建工具 | tsdown |
| 开发语言 | TypeScript（严格模式） |
| Vue 版本 | Vue 3 |
| 测试工具 | vitest |
| UI 基础库 | Element Plus |
| 样式语言 | SCSS |
| 文档系统 | Nuxt 3 + Nuxt Content |

## 第一部分：整体架构设计

### Monorepo 包结构

```
packages/
  vue-element-cui/              # 核心组件库包
    src/
      components/               # 组件源码
        cui-table/
          index.ts
          cui-table.vue
          types.ts
        cui-form/
        ...
      styles/                   # 样式文件
        index.scss              # 主样式入口
        variables.scss          # SCSS 变量
        mixins.scss
      index.ts                  # 组件库主入口
      global.d.ts               # 全局类型声明（Volar 支持）
    package.json
    tsconfig.json
    tsdown.config.ts            # tsdown 构建配置

  vue-element-cui-nuxt/         # Nuxt 3 项目（playground + docs）
    pages/
      index.vue                 # 首页
      components/               # 组件演示页面
        cui-table.vue
        cui-form.vue
        ...
    content/                    # Nuxt Content 文档
      docs/
        getting-started.md
        components/
          cui-table.md
          cui-form.md
    components/                 # Nuxt 项目自身组件
      demo-wrapper.vue          # 演示容器组件
    nuxt.config.ts
    package.json
```

### 构建产物

**vue-element-cui 包的输出**：
- `dist/index.js` - ESM 格式
- `dist/index.cjs` - CommonJS 格式
- `dist/index.d.ts` - TypeScript 类型声明
- `dist/styles/index.css` - 编译后的样式
- `dist/styles/` - 各组件独立样式（支持按需导入）

### 类型提示支持

在 `vue-element-cui/src/global.d.ts` 中导出全局组件类型，适配 Volar：

```typescript
declare module '@vue/runtime-core' {
  export interface GlobalComponents {
    CuiTable: typeof import('./components/cui-table')['CuiTable']
    CuiForm: typeof import('./components/cui-form')['CuiForm']
    // ... 其他组件
  }
}
```

## 第二部分：组件设计与实现策略

### 组件分类与优先级

根据旧组件库的 17 个组件，按复杂度和重要性分为三个层级：

**P0 核心组件（复杂度高，使用频率高）**：
1. **CuiTable** - 数据表格，支持排序、选择、分页、自定义列
2. **CuiForm** - 表单构建器，支持动态表单、验证
3. **CuiSearch** - 搜索表单，通常与 CuiTable 配合使用
4. **CuiDialogForm** - 弹窗表单，表单 + 弹窗的组合

**P1 功能组件（中等复杂度）**：
5. **CuiDialog** - 弹窗容器
6. **CuiDetail** - 详情展示
7. **CuiExcel** - Excel 导入导出
8. **CuiTab** - 标签页容器
9. **CuiSelectBox** / **CuiSelectBox2** - 选择框容器

**P2 表单控件（基于 Element Plus 的轻量封装）**：
10. **CuiSelect** - 下拉选择
11. **CuiSelectEnum** - 枚举下拉选择
12. **CuiSelectDict** - 字典下拉选择
13. **CuiRadioEnum** - 枚举单选
14. **CuiRadioDict** - 字典单选
15. **CuiCheckboxEnum** - 枚举多选
16. **CuiAutocomplete** - 自动完成输入

### 组件实现原则

**1. Composition API 优先**
- 使用 `<script setup>` 语法
- 复杂逻辑抽取为 composables（如 `useTableSelection`、`useFormValidation`）

**2. TypeScript 严格模式**
- 所有 props 使用 Interface 定义完整类型
- 使用泛型支持数据类型推断（如 `CuiTable<T>`）
- 导出所有公共类型接口

**3. 样式隔离**
- 每个组件独立 SCSS 文件
- 使用 BEM 命名规范：`.cui-table__header`、`.cui-table__row--selected`
- 支持 CSS 变量覆盖主题

**4. API 设计原则**
- 保持与 Element Plus 风格一致
- 提供合理的默认值，减少必填 props
- 支持插槽（slots）扩展
- 事件命名遵循 Vue 3 规范（`update:modelValue`）

### 示例：CuiTable 组件设计

```typescript
// types.ts
export interface CuiTableColumn<T = any> {
  prop: keyof T
  label: string
  width?: string | number
  sortable?: boolean
  align?: 'left' | 'center' | 'right'
  formatter?: (row: T, column: CuiTableColumn<T>) => string
  slot?: string
}

export interface CuiTableProps<T = any> {
  data: T[]
  columns: CuiTableColumn<T>[]
  loading?: boolean
  selectable?: boolean
  height?: string | number
}

// cui-table.vue
<script setup lang="ts" generic="T extends Record<string, any>">
import { computed } from 'vue'
import type { CuiTableProps } from './types'

const props = withDefaults(defineProps<CuiTableProps<T>>(), {
  loading: false,
  selectable: false
})

const emit = defineEmits<{
  'selection-change': [selection: T[]]
  'sort-change': [prop: keyof T, order: 'asc' | 'desc']
}>()
</script>
```

## 第三部分：构建配置与类型系统

### tsdown 构建配置

**vue-element-cui/tsdown.config.ts**：

```typescript
import { defineConfig } from 'tsdown'

export default defineConfig({
  entry: ['src/index.ts'],
  format: ['esm', 'cjs'],
  dts: {
    resolve: true,  // 解析类型依赖
    entry: 'src/index.ts'
  },
  clean: true,
  external: ['vue', 'element-plus'],  // 外部依赖不打包
  esbuildOptions: (options) => {
    options.drop = ['debugger']
    return options
  }
})
```

### 样式构建策略

**样式导入路径设计**：

```typescript
// 方式 1：全量导入
import 'vue-element-cui/dist/styles/index.css'

// 方式 2：按需导入单个组件样式
import 'vue-element-cui/dist/styles/cui-table.css'
import 'vue-element-cui/dist/styles/cui-form.css'
```

**SCSS 编译配置**：
- 使用 sass 编译 SCSS 到 CSS
- 输出到 `dist/styles/` 目录
- 保留源码 SCSS 文件供高级用户自定义

### 类型声明导出

**package.json 配置**：

```json
{
  "name": "vue-element-cui",
  "version": "1.0.0",
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
  "peerDependencies": {
    "vue": "^3.4.0",
    "element-plus": "^2.8.0"
  }
}
```

### Volar 类型支持

**src/global.d.ts**：

```typescript
import type { DefineComponent } from 'vue'

declare module '@vue/runtime-core' {
  export interface GlobalComponents {
    CuiTable: DefineComponent<typeof import('./components/cui-table')['cuiTableProps']>
    CuiForm: DefineComponent<typeof import('./components/cui-form')['cuiFormProps']>
    CuiDialog: DefineComponent<typeof import('./components/cui-dialog')['cuiDialogProps']>
    // ... 其他组件
  }
}

export {}
```

**tsconfig.json 配置**：

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
    "esModuleInterop": true
  },
  "include": ["src/**/*"],
  "exclude": ["node_modules", "dist"]
}
```

### Nuxt 项目配置

**vue-element-cui-nuxt/nuxt.config.ts**：

```typescript
export default defineNuxtConfig({
  modules: ['@nuxt/content'],

  content: {
    highlight: {
      theme: 'github-dark',
      preload: ['vue', 'typescript']
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
  }
})
```

## 第四部分：测试策略

### 测试框架配置

**vitest.config.ts**（在 vue-element-cui 包中）：

```typescript
import { defineConfig } from 'vitest/config'
import vue from '@vitejs/plugin-vue'

export default defineConfig({
  plugins: [vue()],
  test: {
    environment: 'jsdom',
    globals: true,
    coverage: {
      provider: 'v8',
      reporter: ['text', 'json', 'html'],
      exclude: ['node_modules/', 'dist/', '**/*.test.ts']
    }
  }
})
```

### 测试分层策略

**1. 单元测试（Unit Tests）**
- 测试单个组件的 props、events、slots
- 测试 composables 的逻辑
- 覆盖率目标：80%+

**测试文件位置**：`packages/vue-element-cui/src/tests/`

**示例：CuiTable 单元测试**：

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

  test('emits selection-change event', async () => {
    const wrapper = mount(CuiTable, {
      props: {
        data: [{ id: 1, name: 'Test' }],
        columns: [{ prop: 'id', label: 'ID' }],
        selectable: true
      }
    })

    await wrapper.find('input[type="checkbox"]').trigger('click')
    expect(wrapper.emitted('selection-change')).toBeTruthy()
  })
})
```

**2. 组件集成测试（Integration Tests）**
- 测试组件之间的交互（如 CuiSearch + CuiTable）
- 测试表单提交流程（CuiForm + CuiDialogForm）

**3. 类型测试（Type Tests）**
- 使用 `tsd` 或 `vitest` 的类型测试功能
- 验证泛型推断是否正确

```typescript
// src/tests/types.test.ts
import { describe, test, expectTypeOf } from 'vitest'
import type { CuiTableProps } from '../components/cui-table'

describe('CuiTable types', () => {
  test('generic type inference', () => {
    interface User {
      id: number
      name: string
    }

    const props: CuiTableProps<User> = {
      data: [{ id: 1, name: 'Test' }],
      columns: [
        { prop: 'id', label: 'ID' },
        { prop: 'name', label: 'Name' }
      ]
    }

    expectTypeOf(props.data[0]).toEqualTypeOf<User>()
  })
})
```

### 测试覆盖率要求

- **P0 核心组件**：覆盖率 ≥ 85%
- **P1 功能组件**：覆盖率 ≥ 75%
- **P2 表单控件**：覆盖率 ≥ 70%

### CI/CD 集成

在 monorepo 根目录的 `package.json` 中添加测试脚本：

```json
{
  "scripts": {
    "test": "pnpm -r run test",
    "test:cui": "pnpm --filter vue-element-cui test",
    "test:coverage": "pnpm --filter vue-element-cui test --coverage"
  }
}
```

## 第五部分：开发工作流与迁移路径

### 开发工作流

**1. 本地开发流程**

```bash
# 安装依赖
pnpm install

# 启动 Nuxt playground（热重载组件库）
cd packages/vue-element-cui-nuxt
pnpm dev

# 在另一个终端监听组件库构建
cd packages/vue-element-cui
pnpm dev  # 使用 tsdown --watch
```

**2. 组件开发标准流程**

每个新组件的开发遵循以下步骤：
1. 在 `src/components/` 创建组件目录
2. 编写组件 `.vue` 文件和 `types.ts`
3. 编写单元测试 `src/tests/组件名.test.ts`
4. 在 `src/index.ts` 中导出组件
5. 在 Nuxt playground 中创建演示页面
6. 编写 Nuxt Content 文档

### 迁移路径规划

**阶段 1：基础设施搭建（Week 1）**
- 初始化 `vue-element-cui` 包结构
- 配置 tsdown、TypeScript、vitest
- 初始化 `vue-element-cui-nuxt` 项目
- 配置 Nuxt Content
- 建立 monorepo workspace 依赖关系

**阶段 2：P0 核心组件迁移（Week 2-3）**
- CuiTable（最复杂，优先攻克）
- CuiForm
- CuiSearch
- CuiDialogForm

**阶段 3：P1 功能组件迁移（Week 4）**
- CuiDialog
- CuiDetail
- CuiExcel
- CuiTab
- CuiSelectBox / CuiSelectBox2

**阶段 4：P2 表单控件迁移（Week 5）**
- 批量迁移 7 个表单控件（相对简单）

**阶段 5：文档与优化（Week 6）**
- 完善所有组件的 Nuxt Content 文档
- 补充交互式示例
- 性能优化
- 发布 1.0.0 版本

### 使用 Agent Team 的任务分配策略

根据要求，使用蜂群架构完成迁移：

**探索子代理（2个并行）**：
- **Explorer-1**：深度探索 tsdown 构建器文档和最佳实践
- **Explorer-2**：分析参考项目（plus-pro-components、easyest）的架构设计

**编辑子代理（按阶段动态创建）**：
- **Editor-P0-Table**：负责 CuiTable 迁移
- **Editor-P0-Form**：负责 CuiForm 迁移
- **Editor-P1-Batch**：负责 P1 组件批量迁移
- **Editor-P2-Batch**：负责 P2 组件批量迁移

**检查复核子代理（1个）**：
- **Reviewer**：检查代码质量、类型安全、测试覆盖率、文档完整性

### 质量检查清单

每个组件完成后必须通过以下检查：
- [ ] TypeScript 类型完整，无 `any` 类型
- [ ] Props 使用 Interface 定义
- [ ] 单元测试覆盖率达标
- [ ] Volar 类型提示正常工作
- [ ] 样式独立可按需导入
- [ ] Nuxt playground 演示页面完整
- [ ] Nuxt Content 文档编写完成
- [ ] 支持 `<script setup>` 语法

## 参考项目

- [plus-pro-components](https://github.com/plus-pro-components/plus-pro-components)
- [easyest](https://github.com/qddidi/easyest)

## 总结

本设计方案采用完全重写策略，基于 Vue 3 + TypeScript + Element Plus 构建现代化组件库。通过 Nuxt 3 All-in-One 架构统一管理 playground 和文档，使用 tsdown 构建工具确保类型安全和构建性能。整个迁移过程分为 5 个阶段，预计 6 周完成，并通过 Agent Team 蜂群架构并行推进开发工作。
