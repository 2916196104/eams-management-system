## Why

当前 `packages/vue-element-cui-nuxt` 仍停留在旧文档站结构上，无法承担 `vue-element-cui` 组件库官网型文档应用的职责：组件体系分组不清、实时演示能力不足、规范内容缺位，且现有路径与页面边界已经不适合继续演进。现在需要基于 `shadcn-docs-nuxt` 重新建立完整文档底座，同时尽量保留现有 markdown 文案资产。

## What Changes

- **BREAKING**: 废弃当前基于旧文档主题和旧路径约定的站点结构，整体重建 `packages/vue-element-cui-nuxt` 的配置、目录与导航。
- **BREAKING**: 删除现有旧文档路径，不做兼容保留，改为新的“快速开始 / 组件 / 规范 / 更新”信息架构。
- 引入 `shadcn-docs-nuxt` 作为文档底座，并按组件库官网需求补齐 `app/` 展示层、`components/content/` 内容组件层和新的 `content/` 内容结构。
- 新建由文档站内部手写维护的 live demo 体系，直接运行真实的 `@eams-monorepo/vue-element-cui` 组件，而不是复用旧示例结构。
- 按组件类型重组组件文档，允许合并旧页面，优先保留原有 markdown 内容并在新结构中重编排。
- 新增独立的“规范”顶级栏目，承载组件设计约定、最佳实践和开发约定。
- 为文档站自有内容组件和关键导航/入口行为补充最小但有效的测试与验证要求。

## Capabilities

### New Capabilities

- `shadcn-docs-foundation`: 用 `shadcn-docs-nuxt` 重建文档站底座，替换旧配置、依赖和站点壳层。
- `docs-home-navigation`: 提供组件库入口型首页和稳定的一级导航、侧边导航、移动端导航体验。
- `docs-live-demo-system`: 建立文档站自有的 live demo 与内容组件体系，支持预览、代码、API 和说明块。
- `docs-information-architecture`: 按新的组件类型信息架构重排内容目录，并迁移现有文案到新的栏目结构。
- `docs-guidelines-system`: 新增独立“规范”栏目，承载设计规范、最佳实践和开发约定。

### Modified Capabilities

- 无

## Impact

- 主要影响目录：`packages/vue-element-cui-nuxt/`
- 主要影响文件：
  - `packages/vue-element-cui-nuxt/package.json`
  - `packages/vue-element-cui-nuxt/nuxt.config.ts`
  - `packages/vue-element-cui-nuxt/app.config.ts`
  - `packages/vue-element-cui-nuxt/app.vue`
  - `packages/vue-element-cui-nuxt/plugins/vue-element-cui.ts`
  - `packages/vue-element-cui-nuxt/components/content/**/*`
  - `packages/vue-element-cui-nuxt/app/components/**/*`
  - `packages/vue-element-cui-nuxt/content/**/*`
  - `packages/vue-element-cui-nuxt/tests/**/*`
- 依赖影响：新增或重排 `shadcn-docs-nuxt` 及其文档站相关依赖，移除旧文档主题依赖。
- 版本控制影响：`.superpowers/` 需要被 Git 忽略，避免本地协作产物进入版本库。
