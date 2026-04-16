## ADDED Requirements

### Requirement: 自定义 ComponentDemo MDC 组件

系统 SHALL 创建自定义的 `ComponentDemo.vue` MDC 组件用于展示交互式组件演示。

#### Scenario: 创建 MDC 组件文件

- **WHEN** 开发者查看 `components/content/` 目录
- **THEN** 应当存在 `ComponentDemo.vue` 文件

#### Scenario: 支持预览和代码双栏展示

- **WHEN** 开发者在 Markdown 中使用 `::component-demo`
- **THEN** 组件应当同时显示实时预览和代码示例

#### Scenario: 支持标题和描述

- **WHEN** 开发者在 frontmatter 中定义 `title` 和 `description`
- **THEN** 组件应当显示标题和描述文本

### Requirement: 在 Markdown 中使用 MDC 语法嵌入组件

系统 SHALL 支持在 Markdown 文档中使用 MDC 语法嵌入 Vue 组件。

#### Scenario: 使用 slot 传递预览内容

- **WHEN** 开发者在 `#preview` slot 中编写组件代码
- **THEN** 组件应当在预览区域实时渲染

#### Scenario: 使用 slot 传递代码示例

- **WHEN** 开发者在 `#code` slot 中编写代码块
- **THEN** 组件应当在代码区域显示高亮的代码

#### Scenario: 支持多个代码示例

- **WHEN** 开发者提供多个代码块（如 template、script、style）
- **THEN** 组件应当支持标签页切换显示不同代码块

### Requirement: 组件导入和注册

系统 SHALL 自动导入和注册 `@eams-monorepo/vue-element-cui` 中的组件。

#### Scenario: 全局注册核心组件

- **WHEN** 开发者在文档中使用 `<CuiTable>` 等组件
- **THEN** 组件应当无需手动导入即可使用

#### Scenario: 支持 workspace 依赖

- **WHEN** 系统导入组件
- **THEN** 应当从 `@eams-monorepo/vue-element-cui` workspace 包导入

### Requirement: 代码高亮

系统 SHALL 为代码示例提供语法高亮。

#### Scenario: 支持 Vue 语法高亮

- **WHEN** 代码块语言为 `vue`
- **THEN** 应当提供 Vue 单文件组件的语法高亮

#### Scenario: 支持 TypeScript 语法高亮

- **WHEN** 代码块语言为 `ts` 或 `typescript`
- **THEN** 应当提供 TypeScript 语法高亮

#### Scenario: 支持 JavaScript 语法高亮

- **WHEN** 代码块语言为 `js` 或 `javascript`
- **THEN** 应当提供 JavaScript 语法高亮

### Requirement: 响应式布局

系统 SHALL 支持组件演示在不同屏幕尺寸下的响应式布局。

#### Scenario: 桌面端双栏布局

- **WHEN** 用户在桌面端浏览
- **THEN** 预览和代码应当并排显示

#### Scenario: 移动端单栏布局

- **WHEN** 用户在移动端浏览
- **THEN** 预览和代码应当上下堆叠显示

#### Scenario: 支持折叠代码区域

- **WHEN** 用户点击折叠按钮
- **THEN** 代码区域应当可以折叠/展开
