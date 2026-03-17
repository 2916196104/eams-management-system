## Why

当前 `@eams-monorepo/vue-element-cui-nuxt` 文档项目使用基础的 Nuxt 3 + Nuxt Content + Tailwind 配置，生成的文档页面效果不符合预期，缺乏专业组件库文档站点应有的交互性、导航体验和视觉呈现。需要迁移到 Docus 框架（Nuxt Content 的官方文档模板），参考 vunix 和 vue-final-modal 等成功案例，实现专业级的组件库文档站点。

## What Changes

- **BREAKING**: 移除 Tailwind CSS 配置，改用 Docus 内置的样式系统
- **BREAKING**: 重构 `nuxt.config.ts`，采用 Docus 的配置结构和模块
- **BREAKING**: 重构文档内容结构，从 `content/docs/` 迁移到 Docus 标准的 `content/` 目录结构
- 新增 Docus 框架依赖和配置
- 新增 Docus 主题配置（导航、侧边栏、页脚等）
- 新增交互式组件演示系统（基于 Docus 的 MDC 组件）
- 新增代码示例展示组件（支持实时预览和代码高亮）
- 改进文档导航结构（顶部导航 + 侧边栏 + 目录）
- 改进组件文档页面布局（API 表格、Props 说明、事件说明、插槽说明）
- 新增搜索功能（Docus 内置的 Algolia DocSearch 或本地搜索）
- 新增深色模式支持（Docus 内置）
- 更新现有组件文档内容，适配 Docus 的 Markdown 扩展语法

## Capabilities

### New Capabilities

- `docus-framework-integration`: Docus 框架集成，包括依赖安装、配置文件、主题定制
- `docus-navigation-system`: Docus 导航系统配置，包括顶部导航、侧边栏、面包屑、目录
- `interactive-component-demos`: 交互式组件演示系统，支持实时预览、代码展示、可编辑示例
- `component-api-documentation`: 组件 API 文档结构，包括 Props、Events、Slots、Methods 的标准化展示
- `docus-search-integration`: 搜索功能集成（Algolia DocSearch 或本地搜索）
- `docus-theme-customization`: Docus 主题定制，包括颜色、字体、布局、深色模式

### Modified Capabilities

- `documentation-system`: 从基础 Nuxt Content 升级到 Docus 框架，文档结构和配置方式发生变化

## Impact

**新增代码**:

- `packages/vue-element-cui-nuxt/app.config.ts` - Docus 应用配置
- `packages/vue-element-cui-nuxt/tokens.config.ts` - Docus 主题 tokens 配置（可选）
- `packages/vue-element-cui-nuxt/components/content/` - 自定义 MDC 组件目录
- `packages/vue-element-cui-nuxt/content/` - 重构后的文档内容目录

**修改代码**:

- `packages/vue-element-cui-nuxt/nuxt.config.ts` - 迁移到 Docus 配置
- `packages/vue-element-cui-nuxt/package.json` - 更新依赖（移除 Tailwind，新增 Docus）
- `packages/vue-element-cui-nuxt/app.vue` - 简化为 Docus 标准布局
- `packages/vue-element-cui-nuxt/content/**/*.md` - 更新文档内容以使用 Docus 特性

**移除代码**:

- `packages/vue-element-cui-nuxt/tailwind.config.ts` - 不再需要 Tailwind 配置
- `packages/vue-element-cui-nuxt/pages/` - Docus 使用基于内容的路由，不需要手动页面

**依赖变更**:

- 移除: `@nuxtjs/tailwindcss`
- 新增: `@nuxt/ui-pro` (Docus 依赖)
- 新增: `@nuxthq/studio` (可选，用于可视化编辑)

**文档和演示**:

- 文档站点视觉效果和交互体验显著提升
- 组件演示更加直观和专业
- 导航和搜索体验改善

**不影响**:

- `@eams-monorepo/vue-element-cui` 核心组件库包不受影响
- 组件 API 和功能不变，仅文档展示方式改变
