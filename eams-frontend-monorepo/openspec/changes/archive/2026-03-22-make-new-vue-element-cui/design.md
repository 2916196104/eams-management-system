## 背景

现有的 vue-element-cui 组件库使用 Vue 2、Element UI 和 JavaScript Options API 构建。它包含 17 个面向业务的组件，封装和增强了 Element UI 组件，提供了数据表格、表单、对话框等常见模式。该库在多个内部项目中使用，但缺乏类型安全、现代化开发体验，且与 Vue 3 生态不兼容。

随着 Vue 3 成熟和 TypeScript 成为标准，我们需要从头重建组件库以：

- 提供完整 TypeScript 支持的类型安全组件
- 利用 Vue 3 Composition API 实现更好的代码组织
- 使用现代构建工具（tsdown）优化包体积和 tree-shaking
- 集成 Nuxt 3 实现文档和 playground

**约束条件：**

- 尽可能保持 API 兼容性以简化迁移
- 必须同时支持 ESM 和 CommonJS 以实现广泛兼容
- 必须与 Element Plus（Element UI 的 Vue 3 版本）配合使用
- 必须提供完整的 TypeScript 类型，包括 Volar 支持
- 开发时间线：完整迁移约 6 周

**利益相关方：**

- 使用组件库的前端开发者
- 依赖这些组件的项目团队
- DevOps 团队（负责构建和部署）

## 目标 / 非目标

**目标：**

- 使用 Vue 3 + TypeScript 完全重写所有 17 个组件
- 完整的 TypeScript 类型安全，支持泛型组件
- 使用 vitest 进行全面测试（80%+ 覆盖率）
- 使用 Nuxt 3 + Nuxt Content 构建交互式文档
- 使用 tsdown 构建现代化构建系统（ESM/CJS 双输出）
- 基于 SCSS 的样式系统，支持 BEM 命名和主题定制
- Volar IDE 支持，包含全局组件类型声明

**非目标：**

- 与 Vue 2 的向后兼容（可接受破坏性变更）
- Nuxt 自动导入模块（推迟到 v2）
- 迁移工具或 codemods（预期手动迁移）
- 超出标准实践的性能优化（可在发布后进行）

## 决策

### 决策 1：完全重写 vs 渐进式迁移

**选择：** 从头完全重写

**理由：**

- Vue 2 到 Vue 3 的迁移并不简单（Options API → Composition API）
- JavaScript 到 TypeScript 的转换需要重新思考组件接口
- Element UI 到 Element Plus 有破坏性 API 变更
- 全新开始可以修复累积的技术债务
- 比尝试增量迁移同时保持兼容性更快

**考虑的替代方案：**

- 渐进式迁移：需要同时维护两个版本，增加复杂性
- 自动化迁移工具：对于包含业务逻辑的复杂组件不可靠

### 决策 2：Nuxt 3 + Docus 一体化 vs 独立 Playground 和文档

**选择：** Nuxt 3 + Docus 一体化架构（playground + docs 在单个项目中）

**理由：**

- Docus 基于 Nuxt Content，提供专业的组件库文档模板
- MDC 语法允许直接在文档中嵌入实时组件
- 单个开发服务器减少上下文切换
- 更简单的部署（一个站点而不是两个）
- 更容易保持文档和演示同步
- 遵循参考项目使用的模式（vunix、vue-final-modal）

**考虑的替代方案：**

- 独立的 VitePress 文档 + Vite playground：更模块化但需要维护两个项目
- Storybook：适合组件目录但对叙述性文档不够灵活
- 基础 Nuxt Content：缺少专业文档站点的开箱即用功能

**注意：** 文档系统的详细实现规范请参考 `improve-vue-element-cui-nuxt-docs-with-docus` 变更

### 决策 3：Vite Library Mode vs 其他构建工具

**选择：** 使用 Vite library mode 构建组件库

**理由：**

- 初期选择 tsdown，但在实际构建中发现 Vue 组件语法兼容性问题
- Vite library mode 提供更成熟的 Vue 3 单文件组件支持
- 通过 vite-plugin-dts 完整支持 TypeScript 类型声明生成
- 更灵活的 external 依赖配置，避免打包第三方库
- 与 Nuxt 3 开发工具链保持一致，便于调试

**实施细节：**

- 配置 external 依赖：vue, element-plus, @element-plus/icons-vue, xlsx
- 使用 vite-plugin-dts 自动生成 .d.ts 文件
- 支持 ESM/CJS 双格式输出
- 构建输出：dist/index.js (ESM), dist/index.cjs (CJS), dist/index.d.ts (类型)

**迁移过程：**

1. 删除 tsdown.config.ts
2. 创建 vite.config.ts 并配置 library mode
3. 修复 Vue 组件语法错误（移除 \*/ 后缀）
4. 配置 external 依赖解决 Rollup 导入问题
5. 验证构建成功并生成所有必需文件

### 决策 4：使用 Interface 定义 Props

**选择：** 所有组件 props 必须使用 TypeScript interface 定义

**理由：**

- 更好的 IDE 自动完成和文档
- 更容易导出和重用类型
- 更清晰的关注点分离（types.ts 文件）
- 所有组件的一致模式
- Volar 全局类型支持所需

**考虑的替代方案：**

- 内联类型定义：可重用性差，难以维护
- 类型别名：interface 更具扩展性，提供更好的错误消息

### 决策 5：测试策略

**选择：** vitest + @vue/test-utils，分层覆盖率要求（P0: 85%, P1: 75%, P2: 70%）

**理由：**

- vitest 快速且对 Vue 3 支持出色
- @vue/test-utils 是官方 Vue 测试库
- 分层覆盖率反映组件复杂性和关键性
- 使用 expectTypeOf 的类型测试确保泛型类型正确工作

**考虑的替代方案：**

- Jest：更慢，ESM 需要更多配置
- Cypress 组件测试：对单元测试来说过于复杂，更适合 E2E

## 风险 / 权衡

**风险：** 破坏性变更需要所有使用项目进行迁移
→ **缓解：** 以新包名发布，允许逐步采用，提供迁移指南

**风险：** tsdown 相对较新，不如 Rollup 经过实战检验
→ **缓解：** 仔细监控构建输出，如果出现问题有 Rollup 备用方案

**风险：** 6 周时间线对于 17 个组件 + 文档可能过于乐观
→ **缓解：** 优先处理 P0 组件，P1/P2 可以增量交付

**风险：** Nuxt 3 文档站点可能比静态站点有更高的托管要求
→ **缓解：** 如果需要可以使用 `nuxt generate` 生成静态站点

**权衡：** 完全重写意味着无法增量交付价值
→ **接受：** 干净的架构值得前期投资

**变更说明：** 当前版本已补充 `unplugin-vue-components` / `unplugin-auto-import` 适配入口
→ **接受：** 继续保留手动导入与全量注册方式，自动导入作为额外接入能力

## 迁移计划

**阶段 1：基础设施（第 1 周）**

1. 使用 tsdown、TypeScript、vitest 初始化 packages/vue-element-cui
2. 使用 Nuxt 3 + Docus 初始化 packages/vue-element-cui-nuxt（详见 `improve-vue-element-cui-nuxt-docs-with-docus` 变更）
3. 设置 monorepo workspace 依赖关系
4. 配置构建脚本和 CI/CD

**阶段 2：P0 核心组件（第 2-3 周）**

1. CuiTable（最复杂，首先处理）
2. CuiForm
3. CuiSearch
4. CuiDialogForm

- 每个组件包括：实现、测试、playground 演示、文档

**阶段 3：P1 功能组件（第 4 周）**

1. CuiDialog、CuiDetail、CuiExcel、CuiTab、CuiSelectBox

- 这些组件可以并行开发

**阶段 4：P2 表单控件（第 5 周）**

1. 批量实现 7 个表单控件组件

- 这些是更简单的封装，可以快速完成

**阶段 5：文档和完善（第 6 周）**

1. 完成所有组件文档
2. 添加交互式示例
3. 性能审计和优化
4. 发布 v1.0.0

**回滚策略：**

- 旧库保留在 old/vue-element-cui 作为参考
- 项目可以继续使用旧库直到准备好迁移
- 没有强制迁移时间线

## 待解决问题

1. **是否应该支持 Vue 2 兼容层？**
   - 倾向于否：增加复杂性，Vue 3 已经稳定 2 年多
   - 决定：不提供兼容层，彻底分离

2. **包命名策略是什么？**
   - 选项 A：保持相同名称（vue-element-cui）但升级到 v2.0.0
   - 选项 B：新名称（vue-element-cui-next 或 @company/vue-element-cui）
   - 需要决定：与团队讨论

3. **是否应该发布到 npm 或保持内部？**
   - 目前仅内部使用
   - 如果组件足够通用可以开源
   - 决定推迟：先从内部开始，稍后评估
