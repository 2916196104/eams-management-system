# 2026-03-13 Vue Element CUI 组件库迁移主计划

> 本文件合并并取代两份 2026-03-10 的旧迁移计划文件。

## 目标

以当前仓库真实状态为准，完成 `@eams-monorepo/vue-element-cui` 组件库迁移的剩余收尾工作，并将 `@eams-monorepo/vue-element-cui-nuxt` 文档站从旧 `docus` 方案重建为基于 `shadcn-docs-nuxt` 的组件库官网型文档应用。

这份计划不再假设“从零初始化组件库”。当前仓库里：

- `packages/vue-element-cui` 已经是一个可构建、可导出的 Vue 3 组件库包。
- `packages/vue-element-cui-nuxt` 已经存在内容资产，但文档站底座仍是旧方案。
- 迁移工作的重点已经从“初始化工程”转为“统一收尾、补足质量、重建文档站”。

## 当前状态快照

### 核心组件库 `packages/vue-element-cui`

当前已确认状态：

- 包名已为 `@eams-monorepo/vue-element-cui`
- 版本已为 `1.0.0`
- 构建脚本当前以 `vite build` 为主
- 已导出 16 个真实组件
- 已具备 `install(app)` 插件入口和 `version` 导出
- 已存在一批 `vitest` 测试

当前以 `src/index.ts` 为准的组件范围：

1. `CuiTable`
2. `CuiForm`
3. `CuiSearch`
4. `CuiDialog`
5. `CuiDialogForm`
6. `CuiDetail`
7. `CuiTab`
8. `CuiExcel`
9. `CuiSelectBox`
10. `CuiSelect`
11. `CuiSelectEnum`
12. `CuiSelectDict`
13. `CuiRadioEnum`
14. `CuiRadioDict`
15. `CuiCheckboxEnum`
16. `CuiAutocomplete`

### 文档站 `packages/vue-element-cui-nuxt`

当前已确认状态：

- 包名已为 `@eams-monorepo/vue-element-cui-nuxt`
- 仍依赖 `@nuxt-themes/docus`
- 现有内容目录仍是旧结构
- 已有组件文档文案资产
- 已有基础 demo 容器，但能力不足以支撑“组件库官网化”

## 已明确淘汰的旧假设

以下内容在旧计划中出现过，但现在都不能再作为实施基线：

1. “从零初始化 `packages/vue-element-cui` 和 `packages/vue-element-cui-nuxt`”
   当前两个包都已存在，且核心包已进入可用状态。

2. “文档站继续沿用 `Nuxt Content + pages/docs` 结构”
   当前已决定文档站必须走 `shadcn-docs-nuxt` 重构路线。

3. “文档站目标是 playground + docs 的旧 All-in-One 结构”
   当前目标已经升级为组件库官网型文档应用。

4. “迁移范围以历史 17 个组件为绝对真值”
   当前计划以仓库内真实导出和真实目录为准，而不是沿用旧计数。

5. “构建主线仍以 tsdown 为基准”
   当前核心包实际构建脚本是 Vite 主线；`tsdown` 是否保留，只作为后续清理决策，不再作为计划前提。

## 总体实施策略

迁移工作分为两条主线，但必须在一份主计划下统一管理：

1. 组件库核心包收尾
2. 文档站官网化重建

两条主线共享同一目标：

- 让 `@eams-monorepo/vue-element-cui` 成为可发布、可维护、测试与类型边界清晰的组件库
- 让 `@eams-monorepo/vue-element-cui-nuxt` 成为符合当前设计结论的组件库官网型文档站

## 主线 A：组件库核心包收尾计划

### A1. 以当前代码为准完成组件范围核对

- 以 `packages/vue-element-cui/src/index.ts`
- `packages/vue-element-cui/src/components/`
- `packages/vue-element-cui/src/tests/`

作为实际完成度判断依据，不再以旧设计文档中的组件总数和阶段划分作为唯一依据。

### A2. 核查每个组件的 4 个完成面

对每个已导出组件逐项检查：

1. 实现是否完整
2. 类型是否完整
3. 样式是否接入
4. 测试是否覆盖

当前优先关注的缺口不是“是否存在组件目录”，而是“是否达到可交付质量”。

### A3. 剩余高优先级收尾项

根据当前代码与本地记忆，核心包后续重点不应再是初始化，而应集中在以下事项：

- 为选择器与枚举类组件补齐缺失测试
- 核查 `install(app)` 导出、类型导出和 `global.d.ts` 的一致性
- 核查样式构建产物与按需导出路径是否稳定
- 评估并清理已经不再承担主流程职责的残留依赖或旧配置
- 补齐仍缺失的高价值集成测试和类型测试

### A4. 核心包完成标准

核心包收尾完成时，应满足：

- 所有正式导出组件都可构建
- 类型声明与导出入口一致
- 关键组件具备测试覆盖
- 构建产物与样式产物稳定
- 不再依赖旧迁移阶段中的临时占位实现

## 主线 B：文档站官网化重建计划

### B1. 文档站方案以 2026-03-13 新计划为准

文档站部分不再沿用旧的 `Nuxt Content + pages/docs` 计划，而以以下文件为正式执行蓝本：

- `docs/plans/2026-03-13-vue-element-cui-nuxt-shadcn-docs-rebuild-plan.md`

该计划已经明确：

- 使用 `shadcn-docs-nuxt`
- 首页定位为组件库入口页
- 一级栏目为“快速开始 / 组件 / 规范 / 更新”
- 组件文档按组件类型分组
- 允许合并旧页面
- live demo 由文档站内部手写维护
- 现有 markdown 文案尽量保留
- 旧路径全部废弃

### B2. 文档站迁移的核心动作

1. 替换文档站底座
2. 重建首页与导航
3. 建立 docs 自有 live demo 体系
4. 重排内容目录
5. 将现有组件文案迁入新结构
6. 新增独立“规范”栏目
7. 补充文档站自有测试与构建验证

### B3. 文档站完成标准

- 不再依赖旧 `docus` 结构作为正式底座
- 首页能够承担组件库入口职责
- live demo 可运行真实 `@eams-monorepo/vue-element-cui` 组件
- 现有关键内容已迁入新结构
- 桌面端和移动端导航可用
- 文档站可通过测试与构建验证

## 联合执行顺序

推荐按以下顺序推进：

### 第 1 阶段：冻结事实基线

- 核对核心包真实导出范围
- 核对当前测试覆盖范围
- 核对文档站现有内容资产
- 以当前仓库状态替换旧计划中的历史假设

### 第 2 阶段：核心包质量收尾

- 先补核心包缺失测试与类型/导出问题
- 保证文档站重构时依赖的组件行为是稳定的

### 第 3 阶段：文档站重建

- 执行 `shadcn-docs-nuxt` 重构计划
- 将原文案迁入新结构
- 搭建 docs 自有 live demo 体系

### 第 4 阶段：联合验证

- 联合验证组件库构建
- 联合验证文档站构建
- 人工核对组件库包与文档站展示一致性

## 验证清单

### 核心包验证

- [ ] `pnpm --filter @eams-monorepo/vue-element-cui test` 通过
- [ ] `pnpm --filter @eams-monorepo/vue-element-cui build` 通过
- [ ] 组件导出与类型导出一致
- [ ] 样式产物可被文档站正确消费

### 文档站验证

- [ ] `pnpm --filter @eams-monorepo/vue-element-cui-nuxt test` 通过
- [ ] `pnpm --filter @eams-monorepo/vue-element-cui-nuxt build` 通过
- [ ] 首页与一级导航符合最新设计
- [ ] 核心组件 live demo 可正常运行
- [ ] 现有文案已迁入新结构

## 破坏性变更说明

这份合并后的主计划确认以下破坏性变更已经是正式方向：

- 废弃旧文档路径
- 废弃旧 `docus` 文档站底座
- 允许重排 `packages/vue-element-cui-nuxt/content/`
- 允许删除旧导航与旧 demo 容器实现
- 不再保留“从零初始化工程”的旧阶段任务

## 计划文件关系

从现在开始，各计划文件职责如下：

- `docs/plans/2026-03-13-vue-element-cui-migration-master-plan.md`
  作为 Vue Element CUI 整体迁移主计划

- `docs/plans/2026-03-13-vue-element-cui-nuxt-shadcn-docs-rebuild-plan.md`
  作为文档站重构的专项实施计划

## 后续要求

今后如果继续更新 Vue Element CUI 的迁移计划，必须遵循以下规则：

1. 以当前仓库真实状态为准，不得继续复制旧初始化步骤
2. 文档站规划必须与 `shadcn-docs-nuxt` 重构方案保持一致
3. 组件数量、测试覆盖、导出状态必须以实际代码为准，不得沿用历史计数
4. 如果专项计划已经存在，主计划只做汇总与编排，不再写出彼此冲突的第二套方案
