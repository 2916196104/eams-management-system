## Context

当前 `@eams-monorepo/vue-element-cui-nuxt` 使用基础的 Nuxt 3 + Nuxt Content + Tailwind CSS 配置，虽然能够展示文档内容，但缺乏专业组件库文档站点应有的特性：

- 缺少统一的导航系统（顶部导航、侧边栏、面包屑）
- 缺少交互式组件演示能力
- 缺少搜索功能
- 缺少深色模式支持
- 样式系统需要手动配置和维护

Docus 是 Nuxt Content 团队官方提供的文档模板，专为技术文档和组件库文档设计，提供开箱即用的导航、搜索、主题、MDC 组件等功能。参考项目 vunix 和 vue-final-modal 已成功使用 Docus 构建了专业的组件库文档站点。

**约束条件**:

- 必须保持与 `@eams-monorepo/vue-element-cui` 核心库的 workspace 依赖关系
- 必须支持在文档中实时演示组件
- 必须保持现有文档内容的迁移路径清晰
- 必须支持中文文档

**利益相关者**:

- 组件库开发者：需要易于维护的文档系统
- 组件库用户：需要清晰、易用的文档和示例

## Goals / Non-Goals

**Goals:**

- 迁移到 Docus 框架，获得专业的文档站点体验
- 实现交互式组件演示系统，支持实时预览和代码展示
- 配置完整的导航系统（顶部导航、侧边栏、目录）
- 集成搜索功能（优先使用 Docus 内置方案）
- 支持深色模式
- 建立标准化的组件 API 文档结构（Props、Events、Slots、Methods）
- 保持与核心组件库的 workspace 依赖

**Non-Goals:**

- 不修改 `@eams-monorepo/vue-element-cui` 核心组件库的任何代码
- 不实现自定义的文档构建系统（使用 Docus 提供的能力）
- 不实现在线代码编辑器（使用 Docus 的 MDC 组件即可）
- 不实现多语言支持（当前仅支持中文）

## Decisions

### 决策 1: 使用 Docus 而非继续使用基础 Nuxt Content

**选择**: 迁移到 Docus 框架

**理由**:

- Docus 是 Nuxt Content 官方文档模板，维护活跃，社区支持好
- 提供开箱即用的导航、搜索、主题、MDC 组件等功能，减少自定义开发
- vunix 和 vue-final-modal 等成功案例证明 Docus 适合组件库文档
- Docus 基于 Nuxt Content，迁移成本相对较低

**替代方案**:

- VitePress: Vue 官方文档工具，但不是 Nuxt 生态，迁移成本高
- 继续使用基础 Nuxt Content + 自定义开发: 开发和维护成本高，难以达到专业水平

### 决策 2: 移除 Tailwind CSS，使用 Docus 内置样式系统

**选择**: 完全移除 Tailwind CSS 配置，使用 Docus 的 `@nuxt/ui-pro` 样式系统

**理由**:

- Docus 内置的样式系统已经提供了完整的主题和组件样式
- 避免样式冲突和重复配置
- Docus 的主题系统通过 `app.config.ts` 和 `tokens.config.ts` 配置，更加集中和易维护
- 参考项目 vunix 和 vue-final-modal 都没有使用 Tailwind

**替代方案**:

- 保留 Tailwind 并与 Docus 共存: 会导致样式冲突，增加配置复杂度

### 决策 3: 文档内容结构采用 Docus 标准

**选择**: 将文档从 `content/docs/` 迁移到 `content/` 根目录，采用 Docus 的标准目录结构

**理由**:

- Docus 的导航和路由系统基于 `content/` 根目录
- 标准结构便于使用 Docus 的自动导航生成功能
- 参考项目都采用这种结构

**目录结构**:

```plain
content/
├── 0.index.md              # 首页
├── 1.getting-started/      # 入门指南
│   ├── 1.installation.md
│   └── 2.quick-start.md
├── 2.components/           # 组件文档
│   ├── 1.table.md
│   ├── 2.form.md
│   └── ...
└── 3.api/                  # API 参考（可选）
```

**替代方案**:

- 保持 `content/docs/` 结构: 需要额外配置 Docus 的路由，不符合最佳实践

### 决策 4: 交互式组件演示使用 Docus 的 MDC 组件

**选择**: 使用 Docus 提供的 `::code-group` 和自定义 MDC 组件实现交互式演示

**理由**:

- Docus 的 MDC 语法支持在 Markdown 中直接嵌入 Vue 组件
- `::code-group` 可以同时展示代码和预览
- 可以创建自定义的 `ComponentDemo.vue` 组件来标准化演示格式

**实现方式**:

````markdown
## ::component-demo

## title: 表格基础用法

#preview
<CuiTable :data="tableData" :columns="columns" />

#code

```vue
<template>
	<CuiTable :data="tableData" :columns="columns" />
</template>
```
````

::

````plain

**替代方案**:
- 使用第三方组件演示库（如 vue-live）: 增加依赖，Docus 的 MDC 已经足够

### 决策 5: 搜索功能使用 Docus 内置方案

**选择**: 优先使用 Docus 内置的本地搜索，如果需要更强大的搜索再考虑 Algolia DocSearch

**理由**:
- Docus 内置的本地搜索对于中小型文档站点已经足够
- 无需额外配置和申请 Algolia 账号
- 支持中文搜索

**替代方案**:
- Algolia DocSearch: 功能更强大，但需要申请和配置，对于当前规模的文档可能过度

### 决策 6: 组件 API 文档使用标准化的 Markdown 表格

**选择**: 使用 Markdown 表格展示 Props、Events、Slots、Methods

**理由**:
- Markdown 表格简单直观，易于维护
- Docus 的表格样式已经很好
- 参考项目都采用这种方式

**格式示例**:
```markdown
## Props

| 属性名 | 类型 | 默认值 | 说明 |
|--------|------|--------|------|
| data | Array | [] | 表格数据 |
| columns | Array | [] | 列配置 |

## Events

| 事件名 | 参数 | 说明 |
|--------|------|------|
| row-click | (row, index) | 行点击事件 |
````

**替代方案**:

- 使用自动生成工具（如 vue-docgen-api）: 增加构建复杂度，当前手动维护即可

## Risks / Trade-offs

### 风险 1: Docus 版本更新可能带来破坏性变更

**风险**: Docus 作为相对较新的框架，未来版本更新可能引入破坏性变更

**缓解措施**:

- 锁定 Docus 和相关依赖的版本
- 关注 Docus 的 changelog 和社区动态
- 在升级前在测试环境验证

### 风险 2: 迁移过程中可能遗漏部分文档内容

**风险**: 从旧结构迁移到新结构时，可能遗漏某些文档页面或资源

**缓解措施**:

- 在迁移前列出所有现有文档页面清单
- 迁移后逐一对比验证
- 保留旧文档目录作为备份，直到确认迁移完成

### 风险 3: 自定义 MDC 组件可能与 Docus 更新冲突

**风险**: 自定义的 MDC 组件（如 ComponentDemo）可能在 Docus 更新后出现兼容性问题

**缓解措施**:

- 尽量使用 Docus 内置的组件和语法
- 自定义组件保持简单，避免深度依赖 Docus 内部 API
- 参考 vunix 等项目的实现方式

### 权衡 1: 灵活性 vs 开箱即用

**权衡**: Docus 提供了很多开箱即用的功能，但也限制了一些自定义的灵活性

**选择**: 优先使用 Docus 的标准功能，只在必要时进行自定义

**理由**: 对于组件库文档，标准化和易维护性比高度自定义更重要

### 权衡 2: 本地搜索 vs Algolia DocSearch

**权衡**: 本地搜索简单但功能有限，Algolia 功能强大但需要额外配置

**选择**: 先使用本地搜索，如果用户反馈搜索体验不足再升级到 Algolia

**理由**: 当前文档规模不大，本地搜索已经足够

## Migration Plan

### 阶段 1: 安装和配置 Docus (1-2 小时)

1. 更新 `package.json`，移除 Tailwind 依赖，添加 Docus 相关依赖
2. 创建 `app.config.ts` 配置文件
3. 更新 `nuxt.config.ts`，采用 Docus 配置
4. 删除 `tailwind.config.ts`
5. 简化 `app.vue` 为 Docus 标准布局

### 阶段 2: 迁移文档内容 (2-3 小时)

1. 创建新的 `content/` 目录结构
2. 迁移现有文档内容到新结构
3. 更新文档内的链接和引用
4. 调整 Markdown 格式以使用 Docus 的 MDC 语法

### 阶段 3: 实现交互式组件演示 (2-3 小时)

1. 创建 `components/content/ComponentDemo.vue` 自定义 MDC 组件
2. 更新组件文档，添加交互式演示
3. 测试组件在文档中的展示效果

### 阶段 4: 配置导航和主题 (1-2 小时)

1. 在 `app.config.ts` 中配置顶部导航
2. 配置侧边栏导航（可以自动生成或手动配置）
3. 配置主题颜色和样式（可选）
4. 测试深色模式

### 阶段 5: 测试和优化 (1-2 小时)

1. 本地测试所有文档页面
2. 测试搜索功能
3. 测试响应式布局
4. 优化加载性能

### 回滚策略

如果迁移过程中遇到严重问题，可以通过 Git 回滚到迁移前的状态：

```bash
git checkout HEAD -- packages/vue-element-cui-nuxt/
```

由于文档项目是独立的包，回滚不会影响核心组件库。

## Open Questions

1. **是否需要配置 Algolia DocSearch？**
   - 决策: 先使用本地搜索，根据用户反馈决定是否升级

2. **是否需要实现组件 API 的自动生成？**
   - 决策: 当前手动维护，如果组件数量增加到 30+ 再考虑自动化

3. **是否需要支持多语言（英文）？**
   - 决策: 当前不支持，如果有国际化需求再添加

4. **是否需要集成 Nuxt Studio 进行可视化编辑？**
   - 决策: 可选功能，不作为必需项，可以在后续迭代中添加
