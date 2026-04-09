## ADDED Requirements

### Requirement: 文档站必须建立在 shadcn-docs-nuxt 底座上

系统 SHALL 将 `packages/vue-element-cui-nuxt` 重建为基于 `shadcn-docs-nuxt` 的 Nuxt 文档应用，而不是继续使用旧文档主题结构。

#### Scenario: Nuxt 配置切换到底座扩展模式

- **WHEN** 开发者查看 `packages/vue-element-cui-nuxt/nuxt.config.ts`
- **THEN** 配置必须以 `extends: ['shadcn-docs-nuxt']` 为基础来构建文档站

#### Scenario: 旧文档主题依赖被移除

- **WHEN** 开发者查看 `packages/vue-element-cui-nuxt/package.json`
- **THEN** 旧文档主题依赖不应再作为正式底座依赖保留

### Requirement: 文档站必须具备独立的展示层目录结构

系统 SHALL 在 `packages/vue-element-cui-nuxt` 内建立独立的 `app/`、`components/content/` 和新的 `content/` 结构，以区分展示逻辑与文档内容。

#### Scenario: 展示层与内容层分离

- **WHEN** 开发者查看文档站目录结构
- **THEN** 必须能区分 `app/` 展示层、`components/content/` 内容组件层和 `content/` 文档内容层

#### Scenario: 首页和站点 UI 具备独立组件承载位置

- **WHEN** 首页入口组件、分类卡片或站点 UI 被实现
- **THEN** 这些组件必须位于文档站自有的展示层目录，而不是混入文档内容目录

### Requirement: 文档站必须直接接入真实组件库和样式

系统 SHALL 通过文档站插件接入真实的 `@eams-monorepo/vue-element-cui` 组件库和必要样式，使文档页中的演示与实际组件行为保持一致。

#### Scenario: 文档页可以直接使用真实组件

- **WHEN** 文档页或 demo 组件渲染 `@eams-monorepo/vue-element-cui` 的组件
- **THEN** 无需为文档站额外维护伪造组件实现

#### Scenario: 演示样式保持真实呈现

- **WHEN** live demo 在文档页中加载
- **THEN** 组件样式必须正常生效，不能出现因样式链缺失导致的裸渲染状态
