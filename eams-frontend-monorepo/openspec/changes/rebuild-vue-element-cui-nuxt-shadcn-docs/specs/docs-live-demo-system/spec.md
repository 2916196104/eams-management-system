## ADDED Requirements

### Requirement: 组件文档页面必须以实时演示为优先

系统 SHALL 让核心组件页优先展示可交互的 live demo，再展示代码和说明，而不是仅提供静态代码片段。

#### Scenario: 页面首屏优先展示预览区

- **WHEN** 用户进入核心组件文档页
- **THEN** 页面应先看到可交互的预览区，而不是仅看到大段代码或纯文本说明

#### Scenario: 代码展示为演示的补充层

- **WHEN** 用户查看示例代码
- **THEN** 页面必须在演示之后提供代码展示，并允许代码区折叠或展开

### Requirement: live demo 必须由文档站内部手写维护

系统 SHALL 在文档站内部维护 demo 组件，不依赖旧文档页、测试场景或外部示例仓库作为主要演示来源。

#### Scenario: 演示组件位于文档站自有目录

- **WHEN** 开发者查看 demo 实现
- **THEN** 关键 demo 组件必须位于 `app/components/demo/` 或等价的文档站内部目录

#### Scenario: 特定组件页可以拥有独立演示实现

- **WHEN** 某个组件体系页需要特定交互演示
- **THEN** 文档站必须允许为该页面编写独立 demo，而不是强制复用旧示例结构

### Requirement: 文档内容组件必须支持预览、代码、API 和说明块

系统 SHALL 提供可在 markdown 或 MDC 中复用的内容组件，以统一组织预览区、代码区、API 表和说明信息。

#### Scenario: 预览与代码通过统一容器渲染

- **WHEN** 文档页接入 demo 容器
- **THEN** 容器必须同时支持预览区和代码区，并保持统一的展示样式

#### Scenario: API 与说明块可以复用于多个组件页

- **WHEN** 文档页展示属性表、功能列表或使用建议
- **THEN** 页面必须使用统一的内容组件来呈现，而不是在每页中重复造结构

### Requirement: live demo 必须运行真实组件库能力

系统 SHALL 让文档中的 live demo 直接运行真实的 `@eams-monorepo/vue-element-cui` 组件，并以真实交互状态展示。

#### Scenario: 演示使用真实组件实例

- **WHEN** 文档页展示表单、表格、选择器或弹层 demo
- **THEN** 这些 demo 必须基于真实组件实例，而不是静态占位图或伪造交互

#### Scenario: 核心演示覆盖主要组件体系

- **WHEN** 文档站完成首轮重建
- **THEN** 至少应有覆盖数据展示、表单输入、选择器、反馈与弹层等核心体系的 live demo
