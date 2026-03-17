## 为什么需要这个改变

旧的 vue-element-cui 组件库基于 Vue 2 + Element UI，使用 JavaScript 和 Options API 开发，缺乏类型安全和现代化开发体验。随着 Vue 3 生态成熟和项目技术栈升级需求，需要将组件库完全重写为 Vue 3 + TypeScript 版本，提供更好的类型提示、开发体验和性能。

## 改变内容

- **破坏性变更**: 完全重写所有 17 个组件，从 Vue 2 Options API 迁移到 Vue 3 Composition API
- **破坏性变更**: 从 Element UI 迁移到 Element Plus
- **破坏性变更**: 从 JavaScript 迁移到 TypeScript 严格模式
- 新增 tsdown 构建工具支持，输出 ESM/CJS 双格式
- 新增完整的 TypeScript 类型声明和 Volar 全局类型支持
- 新增 Nuxt 3 playground 和 Nuxt Content 交互式文档系统
- 新增 vitest 测试框架和完整的单元测试覆盖
- 新增 SCSS 样式系统，支持按需导入和主题定制
- 保持组件 API 设计风格与 Element Plus 一致

## 能力清单

### 新增能力

- `component-library-core`: 核心组件库包，包含 17 个 Vue 3 组件的实现、类型定义、样式系统
- `build-system`: tsdown 构建配置，支持 ESM/CJS 输出、类型声明生成、样式编译
- `type-system`: TypeScript 类型系统，包括全局类型声明、Volar 支持、泛型组件类型
- `testing-infrastructure`: vitest 测试框架配置和测试工具集
- `documentation-system`: Nuxt 3 + Docus 文档系统，包含 playground 和交互式文档（详见 `improve-vue-element-cui-nuxt-docs-with-docus` 变更）
- `p0-core-components`: P0 核心组件（CuiTable, CuiForm, CuiSearch, CuiDialogForm）
- `p1-functional-components`: P1 功能组件（CuiDialog, CuiDetail, CuiExcel, CuiTab, CuiSelectBox）
- `p2-form-controls`: P2 表单控件（7 个基于 Element Plus 的封装组件）
- `style-system`: SCSS 样式系统，包含变量、mixins、BEM 命名规范

### 修改的能力

<!-- 无现有能力需要修改 -->

## 影响范围

**新增代码**:

- `packages/vue-element-cui/` - 核心组件库包（全新创建）
- `packages/vue-element-cui-nuxt/` - Nuxt 3 playground 和文档（全新创建）
- `openspec/specs/` - 各能力的规范文档

**依赖变更**:

- 新增 peerDependencies: `vue@^3.4.0`, `element-plus@^2.8.0`
- 新增 devDependencies: `tsdown`, `vitest`, `@vue/test-utils`, `sass`, `nuxt`, `@nuxt/content`

**构建流程**:

- 新增 tsdown 构建流程
- 新增 SCSS 编译流程
- 新增 vitest 测试流程

**文档和演示**:

- 新增 Nuxt 3 开发服务器
- 新增 Docus 框架文档站点（详见 `improve-vue-element-cui-nuxt-docs-with-docus` 变更）

**不影响**:

- 旧组件库 `old/vue-element-cui` 保持不变，作为参考
- 现有项目可以继续使用旧组件库，迁移是独立的新包
