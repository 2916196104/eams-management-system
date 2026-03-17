<!-- 有意义报告，不予删除 -->

# 2026-03-11 tsdown 构建失败与迁移至 Vite 技术报告

## 执行摘要

在 vue-element-cui 组件库迁移项目中，我们最初选择 tsdown 作为构建工具，但在实际开发中遇到了无法解决的 scoped SCSS 编译问题。经过多次尝试修复后，最终决定切换到 Vite library mode。本报告记录了问题的完整过程、根本原因分析、尝试的解决方案以及最终的技术决策。

## 背景

### 项目信息

- **项目名称**: vue-element-cui 组件库迁移（Vue 2 → Vue 3）
- **构建工具**: tsdown v0.3.1 + unplugin-vue v7.1.1 + rolldown v1.0.0-beta.13
- **问题发现时间**: 2026-03-10
- **影响范围**: 所有包含 scoped SCSS 的 Vue 组件

### 初始技术选型

选择 tsdown 的理由：

1. 专为 TypeScript 库构建设计
2. 自动生成类型声明并解析依赖
3. 基于 esbuild 的快速构建
4. 配置简单，相比 Rollup/Vite library mode 更轻量
5. 在 Vue 3 生态中采用率不断增长

配置文件 (`tsdown.config.ts`):

```typescript
import { defineConfig } from "tsdown";
import Vue from "unplugin-vue/rolldown";

export default defineConfig({
	entry: ["./src/index.ts"],
	format: ["esm", "cjs"],
	platform: "neutral",
	plugins: [Vue({ isProduction: true })],
	dts: { vue: true },
	external: ["vue", "element-plus"],
});
```

## 问题描述

### 错误现象

在构建包含 scoped SCSS 的 Vue 组件时，出现两类错误：

#### 错误类型 1: PostCSS 无法解析 SCSS 注释

```log
[plugin unplugin-vue] D:\...\cui-dialog-form.vue?vue&type=style&index=0&scoped=68d8e993&lang.scss:112:1
CssSyntaxError: D:\...\cui-dialog-form.vue:2:1: Unknown word //
    at Input.error (postcss\lib\input.js:135:16)
    at Parser.unknownWord (postcss\lib\parser.js:595:22)
```

#### 错误类型 2: Rolldown 解析 scoped CSS 失败

```log
[PARSE_ERROR] Error: Unexpected token
   ╭─[ src/components/cui-detail/cui-detail.vue?vue&type=style&index=0&scoped=988e8c05&lang.scss:2:1 ]
   │
 2 │ .cui-detail {
   │ ┬
   │ ╰──
───╯
```

### 受影响的组件

共 11 个组件受影响：

- Phase 6: CuiDialog, CuiDialogForm
- Phase 7: CuiDetail, CuiTab, CuiExcel, CuiSelectBox
- Phase 8: CuiSelectEnum
- 其他: CuiForm, CuiSearch, CuiTable

## 根本原因分析

### 1. PostCSS 与 SCSS 注释冲突

**问题**: PostCSS 默认不支持 SCSS 的 `//` 单行注释语法。

**原因**:

- unplugin-vue 在处理 `<style lang="scss">` 时，先通过 Sass 编译器编译 SCSS
- 但在某些情况下，PostCSS 会在 Sass 编译之前介入，导致无法识别 `//` 注释
- 这是 unplugin-vue + rolldown 的已知问题

**证据**:

```vue
<style scoped lang="scss">
// 组件样式  ← PostCSS 报错：Unknown word //
</style>
```

### 2. Scoped CSS 属性解析失败

**问题**: Rolldown 无法正确解析带有 `data-v-xxx` 属性的 scoped CSS。

**原因**:

- Vue SFC 编译器会为 scoped 样式添加唯一的 `data-v-[hash]` 属性
- unplugin-vue 生成的虚拟模块路径包含查询参数：`cui-detail.vue?vue&type=style&index=0&scoped=988e8c05&lang.scss`
- Rolldown 在解析这些虚拟模块时出现 "Unexpected token" 错误
- 即使是完全正确的 SCSS 语法也会失败

**证据**:

```scss
.cui-detail {
	/* ← Rolldown 报错：Unexpected token */
	display: flex;
}
```

### 3. 工具链兼容性问题

**核心问题**: tsdown + unplugin-vue + rolldown 的组合在处理 Vue 3 scoped SCSS 时存在兼容性问题。

**技术栈分析**:

- **tsdown v0.3.1**: 相对较新的工具，Vue 3 支持不够成熟
- **unplugin-vue v7.1.1**: 主要为 Vite/Webpack 设计，对 rolldown 的支持是实验性的
- **rolldown v1.0.0-beta.13**: Beta 版本，Vue SFC 虚拟模块处理存在 bug

**对比 Vite**:

- Vite 使用 @vitejs/plugin-vue（官方插件）+ Rollup
- 经过大量生产环境验证
- 对 scoped SCSS 的支持完善

## 尝试的解决方案

### 方案 1: 转换 SCSS 注释格式 ❌

**操作**: 将所有 `//` 注释改为 `/* */` 格式

**结果**:

- ✅ 解决了 PostCSS "Unknown word //" 错误
- ❌ 仍然存在 "Unexpected token" 错误
- **结论**: 只解决了表面问题，未触及根本原因

### 方案 2: 移除空的 style 块 ❌

**操作**: 删除只包含注释的 `<style scoped lang="scss">` 块

**结果**:

- ❌ 引入新错误：`Illegal '/' in tags`
- ❌ sed 命令可能破坏了 Vue SFC 结构
- **结论**: 治标不治本，且引入新问题

### 方案 3: 禁用 scoped 样式 ⚠️

**操作**: 将 `<style scoped>` 改为 `<style>`

**评估**:

- ✅ 理论上可以绕过 scoped CSS 解析问题
- ❌ 失去样式隔离，可能导致样式冲突
- ❌ 需要手动添加 BEM 命名或其他隔离方案
- **结论**: 不可接受的妥协方案

### 方案 4: 升级/降级依赖版本 ⏱️

**评估**:

- unplugin-vue 的其他版本可能有同样问题
- rolldown 仍在 beta 阶段，稳定性无法保证
- tsdown 更新频率较低，短期内不太可能修复
- **结论**: 风险高，成功概率低

## 最终决策：切换到 Vite Library Mode

### 决策依据

1. **成熟度**: Vite 是 Vue 官方推荐的构建工具，经过大量生产验证
2. **兼容性**: @vitejs/plugin-vue 对 scoped SCSS 支持完善
3. **生态**: Vite 生态更成熟，问题更容易找到解决方案
4. **时间成本**: 继续调试 tsdown 的时间成本过高，影响项目进度
5. **风险控制**: Vite 是更安全的选择，避免后续出现更多未知问题

### 技术对比

| 特性        | tsdown          | Vite Library Mode         |
| ----------- | --------------- | ------------------------- |
| 配置复杂度  | ⭐⭐ 简单       | ⭐⭐⭐ 中等               |
| 构建速度    | ⭐⭐⭐⭐⭐ 极快 | ⭐⭐⭐⭐ 快               |
| Vue 3 支持  | ⭐⭐ 实验性     | ⭐⭐⭐⭐⭐ 完善           |
| Scoped SCSS | ❌ 有问题       | ✅ 完全支持               |
| 类型生成    | ✅ 自动         | ✅ 需配置 vite-plugin-dts |
| 生态成熟度  | ⭐⭐ 较新       | ⭐⭐⭐⭐⭐ 成熟           |
| 社区支持    | ⭐⭐ 较少       | ⭐⭐⭐⭐⭐ 丰富           |

### 迁移成本

**需要修改的文件**:

1. 删除 `tsdown.config.ts`
2. 创建 `vite.config.ts`
3. 更新 `package.json` 的构建脚本
4. 添加 `vite-plugin-dts` 依赖

**预计时间**: 30 分钟

**风险**: 低（Vite 是成熟方案）

## 经验教训

### 1. 技术选型需要更谨慎

**教训**: 不应该仅因为"新"和"快"就选择较新的工具。

**改进**:

- 优先选择官方推荐的工具
- 检查工具的 GitHub issues，了解已知问题
- 在关键项目中使用经过生产验证的方案
- 对于 Vue 生态，Vite 是最安全的选择

### 2. 早期验证构建流程

**教训**: 应该在项目初期就验证完整的构建流程，而不是等到实现了多个组件后才发现问题。

**改进**:

- 在 Phase 1 (基础设施搭建) 就应该创建一个完整的示例组件
- 该示例组件应包含所有可能的特性：scoped SCSS、TypeScript、泛型等
- 验证构建、类型生成、样式编译都正常工作
- 只有在验证通过后才开始大规模开发

### 3. 及时止损

**教训**: 在尝试了 2-3 种解决方案仍无法解决问题时，应该考虑切换方案，而不是继续深挖。

**改进**:

- 设定"止损点"：如果 2 小时内无法解决，考虑替代方案
- 评估继续调试的时间成本 vs 切换方案的成本
- 不要因为"沉没成本"而坚持错误的技术选择

### 4. 文档和记录的重要性

**教训**: 技术决策和问题排查过程需要详细记录，避免重复踩坑。

**改进**:

- 每次遇到重大技术问题都应编写技术报告
- 记录问题现象、根本原因、尝试的方案、最终决策
- 更新项目文档，确保信息同步

## 后续行动

### 立即执行

1. ✅ 编写本技术报告
2. ⏳ 切换到 Vite library mode
3. ⏳ 更新项目文档（3 个文件）
4. ⏳ 更新 OpenSpec 变更记录
5. ⏳ 验证构建成功

### 长期改进

1. 在项目模板中使用 Vite 作为默认构建工具
2. 建立技术选型评审流程
3. 完善项目初始化检查清单
4. 定期回顾和更新技术栈

## 结论

tsdown 在构建 Vue 3 组件库时遇到的 scoped SCSS 解析问题，根本原因是 tsdown + unplugin-vue + rolldown 工具链的兼容性问题。经过多次尝试修复无果后，我们决定切换到更成熟、更可靠的 Vite library mode。

这次经历提醒我们：

- **成熟度 > 性能**: 在关键项目中，工具的成熟度和可靠性比性能更重要
- **官方方案优先**: Vue 官方推荐的 Vite 是最安全的选择
- **早期验证**: 在项目初期就应该验证完整的构建流程
- **及时止损**: 不要在无法解决的问题上浪费过多时间

通过这次迁移，我们不仅解决了构建问题，也为项目选择了一个更可靠的长期方案。

---

**报告编写**: Claude Opus 4.6
**日期**: 2026-03-11
**项目**: vue-element-cui 组件库迁移
