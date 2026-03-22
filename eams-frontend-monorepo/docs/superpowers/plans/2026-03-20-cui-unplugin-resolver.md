# Vue Element CUI Unplugin Resolver Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 为 `@eams-monorepo/vue-element-cui` 提供适配 `unplugin-vue-components` 和 `unplugin-auto-import` 的按需导入工具，并补齐使用文档与验证。

**Architecture:** 在组件库内维护一份单一导出清单，用它同时驱动组件 resolver、auto-import resolver 与 imports preset，避免公开导出和工具映射漂移。构建层增加 `resolver` 子入口，文档站补充完整接入示例，测试覆盖 resolver 返回值与消费侧类型体验。

**Tech Stack:** Vue 3, TypeScript, Vite library mode, vitest, vue-tsc, unplugin-vue-components, unplugin-auto-import

---

### Task 1: Resolver API 测试先行

**Files:**

- Create: `packages/vue-element-cui/src/tests/resolver.test.ts`

- [ ] **Step 1: 写 resolver 的失败测试**
- [ ] **Step 2: 运行单测确认失败**
- [ ] **Step 3: 明确组件 resolver、auto-import resolver 与 imports preset 的期望返回结构**

### Task 2: Resolver 生产实现

**Files:**

- Create: `packages/vue-element-cui/src/resolver.ts`
- Modify: `packages/vue-element-cui/src/index.ts`
- Modify: `packages/vue-element-cui/package.json`
- Modify: `packages/vue-element-cui/vite.config.ts`

- [ ] **Step 1: 建立统一导出清单**
- [ ] **Step 2: 实现 `VueElementCuiResolver()`**
- [ ] **Step 3: 实现 `VueElementCuiAutoImportResolver()` 与 imports preset**
- [ ] **Step 4: 暴露 `./resolver` 子路径构建与类型入口**

### Task 3: 消费夹具与文档

**Files:**

- Modify: `packages/vue-element-cui/tests/fixtures/volar-consumer/consumer-types.ts`
- Modify: `packages/vue-element-cui-nuxt/content/1.getting-started/1.installation.md`
- Modify: `packages/vue-element-cui-nuxt/content/1.getting-started/2.quick-start.md`
- Modify: `openspec/changes/make-new-vue-element-cui/tasks.md`

- [ ] **Step 1: 在消费夹具里验证 resolver 入口的类型可用**
- [ ] **Step 2: 编写 unplugin-vue-components 与 unplugin-auto-import 接入文档**
- [ ] **Step 3: 如果对应 OpenSpec 任务存在，勾选并同步**

### Task 4: 验证闭环

**Files:**

- Verify only

- [ ] **Step 1: 运行 `pnpm --filter @eams-monorepo/vue-element-cui test`**
- [ ] **Step 2: 运行 `pnpm --filter @eams-monorepo/vue-element-cui typecheck`**
- [ ] **Step 3: 运行 `pnpm --filter @eams-monorepo/vue-element-cui build`**
- [ ] **Step 4: 运行 `pnpm --filter @eams-monorepo/vue-element-cui test:volar-consumer`**
