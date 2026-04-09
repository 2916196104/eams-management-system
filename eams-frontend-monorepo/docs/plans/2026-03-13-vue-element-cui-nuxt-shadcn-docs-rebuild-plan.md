<!--
  认定基本完成对 shadcn-docs-nuxt 模板的转录与使用 不需要继续跟进了
  未来在考虑酌情删除
-->

# Vue Element CUI Nuxt Shadcn Docs Rebuild Implementation Plan

> **For agentic workers:** REQUIRED: Use superpowers:subagent-driven-development (if subagents available) or superpowers:executing-plans to implement this plan. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在保持 `packages/vue-element-cui-nuxt/content` 当前目录层级不变的前提下，使用 `shadcn-docs-nuxt` 重建稳定的组件库文档应用，并把配置与样式基线严格收敛到参考项目的简洁实现。

**Architecture:** 以 `shadcn-docs-nuxt` 为文档底座，以 `ijkml/nuxt-umami-docs` 为最高优先级的配置与样式参考，重点收敛 `package.json`、`nuxt.config.ts`、`app.config.ts`、`assets/css`、`tailwind.config.js`。当前阶段不再继续重排 `content/` 目录，只修正文档站底层配置和样式边界，避免在 `i18n` 与 `icon` 模块上走偏，并让 live demo 继续跑真实的 `@eams-monorepo/vue-element-cui` 组件。

**Tech Stack:** Nuxt 3, shadcn-docs-nuxt, @nuxt/content, Vue 3, TypeScript, Tailwind CSS, vitest, Vue Test Utils, @eams-monorepo/vue-element-cui, Element Plus

---

## Strict Constraints for Current Phase

- 参考项目优先级必须固定为：
  1. `ijkml/nuxt-umami-docs`
  2. `ZTL-UwU/shadcn-docs-nuxt-starter`
  3. `ZTL-UwU/shadcn-docs-nuxt`
  4. `isbrandonw/shadcn-docs-ui-thing`
- 本阶段必须重点阅读并优先照搬以下文件族：
  - `nuxt.config.ts`
  - `app.config.ts`
  - `assets/css`
  - `tailwind.config.js`
- 样式层优先参考 `tailwind.config.js` 与 `assets/css`；不允许再凭主观调整文档主版心，不允许把桌面宽屏页面做成窄小页面。
- `packages/vue-element-cui-nuxt/content` 当前目录结构视为已确认方案，本阶段禁止继续改动其层级与分组。
- `nuxt.config.ts` 与 `app.config.ts` 应尽量保持 `nuxt-umami-docs` 那种最小可用复杂度；多余配置应先删减，再按构建错误最小补回。
- 避免在 `i18n` 模块和 `icon` 模块上折腾兼容写法；图标仅沿用 `shadcn-docs-nuxt` 默认可工作的方式，不单独扩展图标体系。
- 当前执行范围优先处理配置与样式收敛，页面内容与信息架构改造延后，除非为修复构建或布局回归所必需。

## File Structure Map

### 目标目录结构

- `packages/vue-element-cui-nuxt/package.json`
  负责文档站依赖、脚本、测试脚本和最小必要的 `shadcn-docs-nuxt` 相关依赖声明。
- `packages/vue-element-cui-nuxt/nuxt.config.ts`
  负责以 `nuxt-umami-docs` 为主参考的最小核心配置。
- `packages/vue-element-cui-nuxt/app.config.ts`
  负责 `shadcnDocs` 站点级配置，包括导航、侧边栏行为、搜索、页脚等，要求保持简洁。
- `packages/vue-element-cui-nuxt/tailwind.config.js`
  负责文档站主题、颜色、动画与样式扫描范围，优先直接参考 `nuxt-umami-docs` 与 starter。
- `packages/vue-element-cui-nuxt/assets/css/tailwind.css`
  负责 Tailwind 与站点级基础样式入口，应优先直接照搬参考项目的稳定实现。
- `packages/vue-element-cui-nuxt/assets/css/main.css`
  负责本项目最小必要的 demo 隔离与表格补充样式，不得覆盖文档主版心宽度。
- `packages/vue-element-cui-nuxt/app/components/demo/`
  存放 live demo 组件，示例由文档站内部手写维护。
- `packages/vue-element-cui-nuxt/app/components/site/`
  存放首页、分类入口、组件卡片、规范入口等站点 UI 组件。
- `packages/vue-element-cui-nuxt/components/content/`
  存放 markdown / mdc 调用的内容组件，例如 `DemoPlayground`、`ApiTable`、`FeatureList`。
- `packages/vue-element-cui-nuxt/plugins/vue-element-cui.ts`
  负责真实组件库接入，重建后必须重新确认样式加载方式。
- `packages/vue-element-cui-nuxt/content/index.md`
  负责新的入口型首页文档。
- `packages/vue-element-cui-nuxt/content/1.getting-started/`
  负责安装、快速开始、迁移、排障。
- `packages/vue-element-cui-nuxt/content/2.components/`
  负责按组件类型组织的新组件文档体系。
- `packages/vue-element-cui-nuxt/content/3.guidelines/`
  负责独立顶级规范栏目。
- `packages/vue-element-cui-nuxt/content/4.updates/`
  负责更新日志与版本说明。
- `packages/vue-element-cui-nuxt/tests/`
  负责文档站自有内容组件与 demo 容器的 vitest 测试。
- `.gitignore`
  负责补充忽略 `.superpowers/`，避免视觉协作文件进入版本控制。

### 建议创建或重写的关键文件

- Create: `packages/vue-element-cui-nuxt/tailwind.config.js`
- Modify: `packages/vue-element-cui-nuxt/assets/css/tailwind.css`
- Modify: `packages/vue-element-cui-nuxt/assets/css/main.css`
- Create: `packages/vue-element-cui-nuxt/app/components/site/HomeCategoryGrid.vue`
- Create: `packages/vue-element-cui-nuxt/app/components/site/HomeQuickStartLinks.vue`
- Create: `packages/vue-element-cui-nuxt/app/components/demo/data-display/TableBasicDemo.vue`
- Create: `packages/vue-element-cui-nuxt/app/components/demo/form-input/FormBasicDemo.vue`
- Create: `packages/vue-element-cui-nuxt/app/components/demo/selectors/SelectorsOverviewDemo.vue`
- Create: `packages/vue-element-cui-nuxt/app/components/demo/feedback-overlay/DialogFormBasicDemo.vue`
- Create: `packages/vue-element-cui-nuxt/components/content/DemoPlayground.vue`
- Create: `packages/vue-element-cui-nuxt/components/content/DemoCodePanel.vue`
- Create: `packages/vue-element-cui-nuxt/components/content/ApiTable.vue`
- Create: `packages/vue-element-cui-nuxt/components/content/FeatureList.vue`
- Create: `packages/vue-element-cui-nuxt/tests/content/demo-playground.test.ts`
- Create: `packages/vue-element-cui-nuxt/tests/content/api-table.test.ts`
- Create: `packages/vue-element-cui-nuxt/content/2.components/3.selectors/1.overview.md`
- Create: `packages/vue-element-cui-nuxt/content/3.guidelines/1.component-design.md`
- Create: `packages/vue-element-cui-nuxt/content/3.guidelines/2.form-and-table-best-practices.md`
- Create: `packages/vue-element-cui-nuxt/content/3.guidelines/3.overlay-and-interaction-guidelines.md`
- Create: `packages/vue-element-cui-nuxt/content/3.guidelines/4.development-conventions.md`

### 建议删除或废弃的旧文件

- Delete or replace: `packages/vue-element-cui-nuxt/README.md`
- Delete or replace: `packages/vue-element-cui-nuxt/PHASE2-COMPLETION.md`
- Delete or replace: `packages/vue-element-cui-nuxt/components/NavSection.vue`
- Delete or replace: `packages/vue-element-cui-nuxt/components/NavLink.vue`
- Delete or replace: `packages/vue-element-cui-nuxt/components/ComponentCard.vue`
- Delete or replace: 旧 `content/` 下按旧路径组织的组件页面文件

## Chunk 1: Foundation and Style Baseline Reset

### Task 1: 以 `nuxt-umami-docs` 为主参考重置配置与样式底座

**Files:**

- Modify: `packages/vue-element-cui-nuxt/package.json`
- Modify: `packages/vue-element-cui-nuxt/nuxt.config.ts`
- Modify: `packages/vue-element-cui-nuxt/app.config.ts`
- Create: `packages/vue-element-cui-nuxt/tailwind.config.js`
- Modify: `packages/vue-element-cui-nuxt/assets/css/tailwind.css`
- Modify: `packages/vue-element-cui-nuxt/assets/css/main.css`
- Modify: `.gitignore`

- [ ] **Step 1: 精简依赖与脚本声明**

将 `packages/vue-element-cui-nuxt/package.json` 收敛到最小必要依赖集合，优先移除 `shadcn-docs-nuxt` 已内置或已间接提供的重复模块声明，并保留文档站测试脚本。

关键结果：

- 保留 `shadcn-docs-nuxt`
- 保留 `@eams-monorepo/vue-element-cui`、`element-plus`、`nuxt`、`vue`
- 删除当前子包中重复声明的 `@nuxt/icon`、`@nuxtjs/i18n`、`@nuxt/image`、`@nuxt/fonts`、`@nuxt/scripts`、`@vueuse/nuxt`、`@ztl-uwu/nuxt-content`、`shadcn-nuxt`、`nuxt-og-image`
- 保留 `test` 脚本与测试依赖

- [ ] **Step 2: 安装依赖并生成锁文件更新**

Run: `pnpm install --filter @eams-monorepo/vue-element-cui-nuxt...`
Expected: `packages/vue-element-cui-nuxt` 依赖安装成功，`pnpm-lock.yaml` 更新

- [ ] **Step 3: 以最小复杂度重写 `nuxt.config.ts`**

目标：

- `extends: ['shadcn-docs-nuxt']`
- 仅保留 `nuxt-umami-docs` 级别的最小必要配置骨架
- 保留 `build.transpile`、必要的 `vite.ssr.noExternal`、`content.highlight`、`icon.clientBundle`
- 先删除当前的 `i18n`、`nitro.prerender`、`prerender:routes`、路径别名和 shim 配置；只有在构建失败时才最小补回

- [ ] **Step 4: 按参考项目简化 `app.config.ts`**

目标：

- 一级导航包含 `快速开始`、`组件`、`规范`、`更新`
- 侧边栏与 TOC 行为贴近 `shadcn-docs-nuxt`
- 不做额外品牌营销页扩张
- 不扩展 `i18n` 和图标模块配置，只沿用 `shadcnDocs` 的常规写法

- [ ] **Step 5: 直接参考稳定样式建立 Tailwind 与 CSS 入口**

创建 `packages/vue-element-cui-nuxt/tailwind.config.js`，并重写 `packages/vue-element-cui-nuxt/assets/css/tailwind.css` 与 `packages/vue-element-cui-nuxt/assets/css/main.css`。

要求：

- `tailwind.config.js` 直接参考 `nuxt-umami-docs` 与 starter 的 container / colors / borderRadius / animation 配置
- `assets/css/tailwind.css` 直接以参考项目为底稿，避免自定义破坏宽屏布局
- `assets/css/main.css` 只保留 demo 隔离和表格类最小补充
- 扫描范围覆盖：

- `content/**/*`
- `components/content/**/*`
- `app/components/**/*`
- 不新增会压缩主内容宽度的自定义容器规则

- [ ] **Step 6: 补 `.gitignore` 并清理与新基线冲突的残留**

目标：

- `.gitignore` 增加 `.superpowers/`
- 清理已不再被最小配置使用的 shim/脚本残留文件

- [ ] **Step 7: 运行构建与桌面宽屏冒烟验证**

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt build`
Expected: Nuxt 构建通过，桌面端不再出现主内容区被做窄的问题

- [ ] **Step 8: 提交基础底座重建**

```bash
git add .gitignore packages/vue-element-cui-nuxt/package.json packages/vue-element-cui-nuxt/nuxt.config.ts packages/vue-element-cui-nuxt/app.config.ts packages/vue-element-cui-nuxt/tailwind.config.js packages/vue-element-cui-nuxt/assets/css/tailwind.css packages/vue-element-cui-nuxt/assets/css/main.css pnpm-lock.yaml
git commit -m "feat(vue-element-cui-nuxt): reset docs config and style baseline"
```

## Chunk 2: Demo and Content Component System

> Current phase note: 该 Chunk 仅处理为配置与样式基线验证所必需的 demo / 内容组件问题；不再扩展新的内容结构设计。

### Task 2: 建立文档站自有 live demo 与内容组件体系

**Files:**

- Create: `packages/vue-element-cui-nuxt/app/components/demo/data-display/TableBasicDemo.vue`
- Create: `packages/vue-element-cui-nuxt/app/components/demo/form-input/FormBasicDemo.vue`
- Create: `packages/vue-element-cui-nuxt/app/components/demo/selectors/SelectorsOverviewDemo.vue`
- Create: `packages/vue-element-cui-nuxt/app/components/demo/feedback-overlay/DialogFormBasicDemo.vue`
- Create: `packages/vue-element-cui-nuxt/components/content/DemoPlayground.vue`
- Create: `packages/vue-element-cui-nuxt/components/content/DemoCodePanel.vue`
- Create: `packages/vue-element-cui-nuxt/components/content/ApiTable.vue`
- Create: `packages/vue-element-cui-nuxt/components/content/FeatureList.vue`
- Create: `packages/vue-element-cui-nuxt/tests/content/demo-playground.test.ts`
- Create: `packages/vue-element-cui-nuxt/tests/content/api-table.test.ts`
- Modify: `packages/vue-element-cui-nuxt/plugins/vue-element-cui.ts`

- [ ] **Step 1: 为文档站测试环境写失败测试**

先为内容组件写最小失败测试，验证：

- `DemoPlayground` 能渲染预览区与代码区
- `ApiTable` 能渲染配置项表格

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt test -- --run tests/content/demo-playground.test.ts tests/content/api-table.test.ts`
Expected: FAIL，提示组件不存在或结构不匹配

- [ ] **Step 2: 实现内容组件基础壳层**

实现：

- `DemoPlayground.vue`
- `DemoCodePanel.vue`
- `ApiTable.vue`
- `FeatureList.vue`

要求：

- 预览优先，代码可折叠
- 支持在 markdown 中直接调用
- 不把业务交互逻辑塞进内容组件

- [ ] **Step 3: 运行测试让内容组件通过**

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt test -- --run tests/content/demo-playground.test.ts tests/content/api-table.test.ts`
Expected: PASS

- [ ] **Step 4: 创建核心 demo 组件**

至少先建立这 4 个 demo：

- `TableBasicDemo.vue`
- `FormBasicDemo.vue`
- `SelectorsOverviewDemo.vue`
- `DialogFormBasicDemo.vue`

要求：

- 直接使用真实 `@eams-monorepo/vue-element-cui` 组件
- 示例数据和交互逻辑留在文档站内部

- [ ] **Step 5: 重新确认组件库插件与样式接入**

重写 `plugins/vue-element-cui.ts`，确认：

- Element Plus 与 `@eams-monorepo/vue-element-cui` 正确注册
- 组件样式能够正常展示

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt dev`
Expected: 核心 demo 样式与交互正常，不出现裸组件状态

- [ ] **Step 6: 提交 demo 与内容组件体系**

```bash
git add packages/vue-element-cui-nuxt/app/components/demo packages/vue-element-cui-nuxt/components/content packages/vue-element-cui-nuxt/tests/content packages/vue-element-cui-nuxt/plugins/vue-element-cui.ts
git commit -m "feat(vue-element-cui-nuxt): add docs-owned live demo system"
```

## Chunk 3: Information Architecture and Content Migration

> Current phase note: 该 Chunk 已冻结。`packages/vue-element-cui-nuxt/content` 当前结构已被用户确认，本阶段禁止继续重排目录层级；仅允许做最小内容修补。

### Task 3: 重排内容目录并迁移“快速开始 / 更新”内容

**Files:**

- Modify or create: `packages/vue-element-cui-nuxt/content/index.md`
- Create: `packages/vue-element-cui-nuxt/content/1.getting-started/1.installation.md`
- Create: `packages/vue-element-cui-nuxt/content/1.getting-started/2.quick-start.md`
- Create: `packages/vue-element-cui-nuxt/content/1.getting-started/3.migration.md`
- Create: `packages/vue-element-cui-nuxt/content/1.getting-started/4.troubleshooting.md`
- Create: `packages/vue-element-cui-nuxt/content/4.updates/1.changelog.md`
- Delete or archive content from old paths after migration

- [ ] **Step 1: 创建新首页文档骨架**

`content/index.md` 目标：

- 首页是入口页，不是营销页
- 首屏给安装、快速开始、组件入口、规范入口
- 可嵌入少量 live demo 或类别卡片，但不喧宾夺主

- [ ] **Step 2: 一对一迁移快速开始类文案**

从旧内容中迁移并尽量保留原文案：

- installation
- quick-start
- migration-guide
- troubleshooting

- [ ] **Step 3: 迁移 changelog 到更新栏目**

把旧 `changelog` 内容迁移到 `content/4.updates/1.changelog.md`

- [ ] **Step 4: 运行内容导航检查**

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt dev`
Expected: 首页、快速开始、更新栏目在导航中可见，旧路径不再暴露

- [ ] **Step 5: 提交第一批内容迁移**

```bash
git add packages/vue-element-cui-nuxt/content
git commit -m "feat(vue-element-cui-nuxt): migrate getting-started and updates content"
```

### Task 4: 按组件类型重组并合并旧组件文档

**Files:**

- Create: `packages/vue-element-cui-nuxt/content/2.components/1.data-display/1.table.md`
- Create: `packages/vue-element-cui-nuxt/content/2.components/1.data-display/2.detail.md`
- Create: `packages/vue-element-cui-nuxt/content/2.components/1.data-display/3.excel.md`
- Create: `packages/vue-element-cui-nuxt/content/2.components/2.form-input/1.form.md`
- Create: `packages/vue-element-cui-nuxt/content/2.components/2.form-input/2.autocomplete.md`
- Create: `packages/vue-element-cui-nuxt/content/2.components/3.selectors/1.overview.md`
- Create: `packages/vue-element-cui-nuxt/content/2.components/4.feedback-overlay/1.dialog.md`
- Create: `packages/vue-element-cui-nuxt/content/2.components/4.feedback-overlay/2.dialog-form.md`
- Create: `packages/vue-element-cui-nuxt/content/2.components/5.navigation-layout/1.search.md`
- Create: `packages/vue-element-cui-nuxt/content/2.components/5.navigation-layout/2.tab.md`

- [ ] **Step 1: 迁移 `data-display` 相关页面**

目标：

- `table`、`detail`、`excel` 独立成新类型下的页面
- 文案尽量保留，但 frontmatter 与路径改成新结构

- [ ] **Step 2: 迁移 `form-input` 相关页面**

目标：

- 保留 `form` 与 `autocomplete` 核心说明
- 在页面内插入新的 live demo 调用块

- [ ] **Step 3: 合并选择器体系页**

将旧内容合并到 `content/2.components/3.selectors/1.overview.md`：

- `select`
- `select-dict`
- `select-enum`
- `radio-dict`
- `radio-enum`
- `checkbox-enum`
- `select-box`

要求：

- 原文案尽量保留
- 合并为“场景 -> demo -> 配置说明 -> 注意事项”的新结构

- [ ] **Step 4: 迁移弹层与交互类页面**

迁移：

- `dialog`
- `dialog-form`
- `search`
- `tab`

- [ ] **Step 5: 删除旧路径内容文件或迁移后留空占位检查**

Run: `rg --files packages/vue-element-cui-nuxt/content`
Expected: 旧路径结构不再残留为正式入口

- [ ] **Step 6: 提交组件内容重组**

```bash
git add packages/vue-element-cui-nuxt/content/2.components
git commit -m "feat(vue-element-cui-nuxt): reorganize component docs by type"
```

## Chunk 4: Guidelines and Site Experience

> Current phase note: 该 Chunk 已冻结。仅当配置与样式收敛完成后，且用户再次明确要求时，才重新打开。

### Task 5: 新增独立“规范”顶级栏目

**Files:**

- Create: `packages/vue-element-cui-nuxt/content/3.guidelines/1.component-design.md`
- Create: `packages/vue-element-cui-nuxt/content/3.guidelines/2.form-and-table-best-practices.md`
- Create: `packages/vue-element-cui-nuxt/content/3.guidelines/3.overlay-and-interaction-guidelines.md`
- Create: `packages/vue-element-cui-nuxt/content/3.guidelines/4.development-conventions.md`

- [ ] **Step 1: 写组件设计约定页**

目标：

- 说明 `vue-element-cui` 的组件封装边界、命名与一致性要求

- [ ] **Step 2: 写表单与表格最佳实践页**

目标：

- 抽出原组件文档中的通用经验，不在多个组件页重复散落

- [ ] **Step 3: 写弹层与交互约定页**

目标：

- 统一对话框、弹窗表单、搜索交互的推荐模式

- [ ] **Step 4: 写开发约定页**

目标：

- 说明 demo 编写方式、文档结构约定、内容组件使用约定

- [ ] **Step 5: 运行导航检查**

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt dev`
Expected: “规范”作为独立顶级栏目出现

- [ ] **Step 6: 提交规范栏目**

```bash
git add packages/vue-element-cui-nuxt/content/3.guidelines
git commit -m "feat(vue-element-cui-nuxt): add top-level guidelines section"
```

### Task 6: 完善首页入口体验与站点导航

**Files:**

- Create: `packages/vue-element-cui-nuxt/app/components/site/HomeCategoryGrid.vue`
- Create: `packages/vue-element-cui-nuxt/app/components/site/HomeQuickStartLinks.vue`
- Modify: `packages/vue-element-cui-nuxt/content/index.md`
- Modify: `packages/vue-element-cui-nuxt/app.config.ts`

- [ ] **Step 1: 实现首页类别入口组件**

目标：

- 首页明确导向“快速开始”“组件”“规范”“更新”
- 组件入口按类型展示

- [ ] **Step 2: 实现快速开始入口组件**

目标：

- 首页直接链接安装、快速开始、核心组件体系页

- [ ] **Step 3: 把入口组件接入首页内容**

要求：

- 首页依旧偏文档入口，而不是营销页
- 可有少量演示亮点，但不替代正文入口

- [ ] **Step 4: 调整导航与页脚信息**

在 `app.config.ts` 中保证：

- 一级栏目稳定
- 侧边栏行为符合新结构
- 页脚与链接符合组件库文档定位

- [ ] **Step 5: 手工验证桌面与移动端**

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt dev`
Expected:

- 桌面端导航可用
- 移动端侧边导航可展开
- 首页入口不混乱

- [ ] **Step 6: 提交首页与导航优化**

```bash
git add packages/vue-element-cui-nuxt/app/components/site packages/vue-element-cui-nuxt/content/index.md packages/vue-element-cui-nuxt/app.config.ts
git commit -m "feat(vue-element-cui-nuxt): polish home entry and navigation"
```

## Chunk 5: Verification and Cleanup

### Task 7: 为文档站自有能力补最小有效验证

**Files:**

- Modify: `packages/vue-element-cui-nuxt/package.json`
- Create: `packages/vue-element-cui-nuxt/tests/content/demo-playground.test.ts`
- Create: `packages/vue-element-cui-nuxt/tests/content/api-table.test.ts`
- Optionally create: `packages/vue-element-cui-nuxt/tests/site/home-navigation.test.ts`

- [ ] **Step 1: 确认测试脚本可运行**

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt test`
Expected: 能进入 vitest，不因 Nuxt 配置缺失直接崩溃

- [ ] **Step 2: 补首页或导航最小行为测试**

如果首页入口组件存在可测试逻辑，为其补最小测试。

- [ ] **Step 3: 跑一次文档站自有测试集合**

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt test`
Expected: PASS

- [ ] **Step 4: 跑一次生产构建**

Run: `pnpm --filter @eams-monorepo/vue-element-cui-nuxt build`
Expected: PASS

- [ ] **Step 5: 手工核对关键页面**

手工检查：

- `/`
- `/getting-started/installation`
- 一个 `data-display` 页面
- 一个 `selectors` 体系页
- 一个 `guidelines` 页面
- `/updates/changelog`

- [ ] **Step 6: 提交验证与清理**

```bash
git add packages/vue-element-cui-nuxt/tests packages/vue-element-cui-nuxt/package.json
git commit -m "test(vue-element-cui-nuxt): verify rebuilt docs application"
```

## Breaking Changes

- [ ] 废弃现有全部旧文档路径，不做兼容保留
- [ ] 废弃当前 `@nuxt-themes/docus` 方案
- [ ] 当前阶段不再重排 `packages/vue-element-cui-nuxt/content/` 目录
- [ ] 允许合并旧组件页面为新的体系页
- [ ] 允许重写 demo 容器与导航辅助组件
- [ ] 允许新增完整 `app/` 层级并将文档站升级为完整应用结构

## Verification Checklist

- [ ] 首页是组件库入口页而不是营销页
- [ ] 一级导航包含 `快速开始`、`组件`、`规范`、`更新`
- [ ] 旧路径不再作为正式入口出现
- [ ] 选择器等同类页面已合并为体系页
- [ ] 核心 live demo 能运行且样式正常
- [ ] 原有关键文案已迁入新结构
- [ ] `.superpowers/` 已加入 `.gitignore`
- [ ] `pnpm --filter @eams-monorepo/vue-element-cui-nuxt test` 通过
- [ ] `pnpm --filter @eams-monorepo/vue-element-cui-nuxt build` 通过

## Execution Notes

- 当前优先只执行 Chunk 1；Chunk 2 仅做构建与样式验证所需的最小补充；Chunk 3 和 Chunk 4 暂不推进。
- 优先按 Chunk 顺序执行，避免同时大面积改配置和改内容导致回归难定位。
- 每个 Chunk 完成后先跑对应验证，再进入下一个 Chunk。
- 如发现 `@eams-monorepo/vue-element-cui` 样式接入问题，优先在 Chunk 2 解决，不要把样式问题拖到内容迁移末期。
- 内容迁移坚持“尽量保留原文案”，优先重编排，谨慎重写。
- 如果需要补充 OpenSpec，后续应以本计划为执行蓝本拆分任务，而不是另起一套结构。
