## 新增需求

### 需求：包结构

组件库必须组织为位于 `packages/vue-element-cui/` 的 monorepo 包，清晰分离组件、样式、类型和测试。

#### 场景：包初始化

- **当** 开发者初始化包时
- **则** 包结构必须包含 `src/components/`、`src/styles/`、`src/tests/` 目录

#### 场景：组件组织

- **当** 开发者添加新组件时
- **则** 组件必须放置在 `src/components/<组件名>/` 目录中，包含 `index.ts`、`<组件名>.vue` 和 `types.ts` 文件

### 需求：组件实现

所有 17 个组件必须使用 Vue 3 Composition API 和 `<script setup>` 语法以及 TypeScript 实现。

#### 场景：Vue 3 Composition API 使用

- **当** 开发者实现组件时
- **则** 组件必须使用 `<script setup lang="ts">` 语法

#### 场景：TypeScript 严格模式

- **当** 组件被编译时
- **则** TypeScript 严格模式必须通过且无错误

### 需求：组件导出

组件库必须从主入口点 `src/index.ts` 导出所有组件及其类型。

#### 场景：组件导入

- **当** 用户导入组件 `import { CuiTable } from 'vue-element-cui'`
- **则** 组件必须可用且类型正确

#### 场景：类型导入

- **当** 用户导入类型 `import type { CuiTableProps } from 'vue-element-cui'`
- **则** 类型必须可用

### 需求：Element Plus 集成

所有组件必须基于 Element Plus 组件并遵循 Element Plus API 设计模式。

#### 场景：Element Plus 依赖

- **当** 组件使用 Element Plus 组件时
- **则** Element Plus 必须声明为 peerDependency

#### 场景：API 一致性

- **当** 组件暴露 props 和事件时
- **则** 命名和行为必须与 Element Plus 约定保持一致

### 需求：组件分类

组件必须组织为三个优先级类别：P0（核心）、P1（功能）、P2（表单控件）。

#### 场景：P0 核心组件

- **当** 实现 P0 组件时
- **则** 必须包含 CuiTable、CuiForm、CuiSearch、CuiDialogForm

#### 场景：P1 功能组件

- **当** 实现 P1 组件时
- **则** 必须包含 CuiDialog、CuiDetail、CuiExcel、CuiTab、CuiSelectBox

#### 场景：P2 表单控件

- **当** 实现 P2 组件时
- **则** 必须包含 CuiSelect、CuiSelectEnum、CuiSelectDict、CuiRadioEnum、CuiRadioDict、CuiCheckboxEnum、CuiAutocomplete
