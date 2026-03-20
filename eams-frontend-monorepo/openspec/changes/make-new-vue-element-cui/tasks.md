# Vue Element CUI 组件库迁移任务清单

## 任务进度总览（截至 2026-03-11）

### 已完成的阶段

- ✅ Phase 1: 基础设施搭建（9/9 任务完成）
- ✅ Phase 2: Nuxt 文档系统（9/9 任务完成）
- ✅ Phase 3: CuiTable 组件（13/13 任务完成）
- ✅ Phase 4: CuiForm 组件（10/10 任务完成）
- ✅ Phase 5: CuiSearch 组件（9/9 任务完成）
- ✅ Phase 6: CuiDialogForm 组件（10/10 任务完成）
- ✅ Phase 7: P1 功能组件（14/14 任务完成）
- ✅ Phase 8: P2 表单控件（12/12 任务完成）
- ✅ Phase 9: 组件样式（10/10 任务完成）
- ✅ Phase 10: 类型系统完善（8/8 任务完成）
- ⏸️ Phase 11-14: 测试、文档、构建、验证（待开始）
- ✅ Phase 15: 构建工具切换（10/10 任务完成）

### 关键里程碑

- ✅ 2026-03-10: 完成 CuiForm、CuiSearch、CuiDialogForm 核心组件
- ✅ 2026-03-11: 发现 tsdown 构建问题，切换到 Vite library mode
- ✅ 2026-03-11: 编写 tsdown 失败技术报告
- ✅ 2026-03-11: 修复 Vue 组件语法错误（移除 \*/ 后缀）
- ✅ 2026-03-11: 配置 Vite external 依赖，验证构建成功
- ✅ 2026-03-11: 更新项目文档（3 个文件）和 OpenSpec 变更记录
- ✅ 2026-03-11: 完成 P1 组件测试和文档（4 个测试文件，5 个演示页面，5 个文档页面）
- ✅ 2026-03-11: 完成 CuiTable 组件（P0 核心组件）
- ✅ 2026-03-11: 完成全部 P2 表单控件组件

### 下一步行动（优先级排序）

1. **完善测试与质量** - 运行完整测试套件，验证覆盖率（Phase 11）
2. **补充组件文档** - 为所有组件添加 API 参考和交互式示例（Phase 12）
3. **构建与部署准备** - 验证类型声明和 CSS 编译（Phase 13）
4. **最终验证** - 手动测试、性能审计、可访问性审计（Phase 14）

---

## 1. 基础设施搭建

- [x] 1.1 初始化 packages/vue-element-cui 包，包含 package.json、tsconfig.json 和目录结构
- [x] 1.2 配置构建系统，支持 ESM/CJS 双输出（已从 tsdown 切换到 Vite library mode）
- [x] 1.3 配置 vitest 测试框架，使用 jsdom 环境
- [x] 1.4 配置 SCSS 编译管道，使用 sass
- [x] 1.5 创建 src/styles/ 目录，包含 variables.scss、mixins.scss 和 index.scss
- [x] 1.6 配置 TypeScript 严格模式和路径别名
- [x] 1.7 创建 src/global.d.ts 用于 Volar 全局组件类型
- [x] 1.8 设置 package.json 导出配置，包括主入口、样式和类型
- [x] 1.9 验证构建输出（dist/index.js、dist/index.cjs、dist/index.d.ts、dist/styles/）

## 2. Nuxt 文档系统

- [x] 2.1 使用 Nuxt 3 初始化 packages/vue-element-cui-nuxt
- [x] 2.2 安装并配置 @nuxt/content 模块
- [x] 2.3 配置 Tailwind CSS 用于文档样式
- [x] 2.4 创建 pages/index.vue 首页
- [x] 2.5 创建 pages/docs/[...slug].vue 文档模板，包含侧边栏导航
- [x] 2.6 创建 content/docs/getting-started.md，包含安装和快速开始指南
- [x] 2.7 配置语法高亮，使用 github-dark 主题
- [x] 2.8 设置工作区依赖到 vue-element-cui 包
- [x] 2.9 验证 Nuxt 开发服务器启动并渲染文档

## 3. P0 核心组件：CuiTable

- [x] 3.1 创建 src/components/cui-table/ 目录，包含 index.ts、cui-table.vue、types.ts
- [x] 3.2 在 types.ts 中定义 CuiTableProps 和 CuiTableColumn 接口
- [x] 3.3 实现 CuiTable 组件，使用 ElTable 进行基础表格渲染
- [x] 3.4 添加可排序列支持，使用 sort-change 事件
- [x] 3.5 添加行选择支持，使用 selection-change 事件
- [x] 3.6 添加索引行支持（序号列）
- [x] 3.7 通过插槽添加自定义单元格渲染支持
- [x] 3.8 添加加载状态支持
- [x] 3.9 创建 src/tests/cui-table.test.ts 单元测试（目标：85% 覆盖率）
- [x] 3.10 从 src/index.ts 导出 CuiTable
- [x] 3.11 更新 src/global.d.ts，添加 CuiTable 类型声明
- [x] 3.12 创建 pages/components/cui-table.vue 演示示例
- [x] 3.13 创建 content/docs/components/cui-table.md 文档

## 4. P0 核心组件：CuiForm

- [x] 4.1 创建 src/components/cui-form/ 目录结构
- [x] 4.2 定义 CuiFormProps 和字段配置接口
- [x] 4.3 实现 CuiForm 组件，支持动态字段渲染
- [x] 4.4 使用 ElForm 验证规则添加表单验证支持
- [x] 4.5 添加不同字段类型支持（输入框、选择框、日期等）
- [x] 4.6 实现带验证的表单提交
- [x] 4.7 添加表单重置功能
- [x] 4.8 创建 CuiForm 单元测试（目标：85% 覆盖率）
- [x] 4.9 导出并文档化 CuiForm
- [x] 4.10 创建演示示例和文档

## 5. P0 核心组件：CuiSearch

- [x] 5.1 创建 src/components/cui-search/ 目录结构
- [x] 5.2 定义 CuiSearchProps 接口
- [x] 5.3 实现 CuiSearch 组件，支持搜索字段渲染
- [x] 5.4 添加搜索按钮，触发搜索事件
- [x] 5.5 添加重置按钮，触发重置事件
- [x] 5.6 添加可折叠的高级搜索字段支持
- [x] 5.7 创建 CuiSearch 单元测试（目标：85% 覆盖率）
- [x] 5.8 导出并文档化 CuiSearch
- [x] 5.9 创建演示示例和文档

## 6. P0 核心组件：CuiDialogForm

- [x] 6.1 创建 src/components/cui-dialog-form/ 目录结构
- [x] 6.2 定义 CuiDialogFormProps 接口
- [x] 6.3 实现 CuiDialogForm，结合 ElDialog 和 CuiForm
- [x] 6.4 使用 v-model:visible 添加对话框可见性控制
- [x] 6.5 添加带验证的表单提交处理
- [x] 6.6 添加取消/关闭功能
- [x] 6.7 添加提交期间的加载状态
- [x] 6.8 创建 CuiDialogForm 单元测试（目标：85% 覆盖率）
- [x] 6.9 导出并文档化 CuiDialogForm
- [x] 6.10 创建演示示例和文档

## 7. P1 功能组件

- [x] 7.1 实现 CuiDialog 组件（带插槽的对话框容器）
- [x] 7.2 创建 CuiDialog 单元测试（目标：75% 覆盖率）
- [x] 7.3 实现 CuiDetail 组件（结构化数据展示）
- [x] 7.4 创建 CuiDetail 单元测试（目标：75% 覆盖率）
- [x] 7.5 实现 CuiExcel 组件（Excel 导入/导出）
- [x] 7.6 创建 CuiExcel 单元测试（目标：75% 覆盖率）
- [x] 7.7 实现 CuiTab 组件（标签页容器）
- [x] 7.8 创建 CuiTab 单元测试（目标：75% 覆盖率）
- [x] 7.9 实现 CuiSelectBox 组件（选择容器）
- [x] 7.10 创建 CuiSelectBox 单元测试（目标：75% 覆盖率）
- [x] 7.11 从 src/index.ts 导出所有 P1 组件
- [x] 7.12 更新 src/global.d.ts，添加 P1 组件类型
- [x] 7.13 为所有 P1 组件创建演示示例
- [x] 7.14 为所有 P1 组件创建文档

## 8. P2 表单控件

- [x] 8.1 实现 CuiSelect 组件（增强选择框）
- [x] 8.2 实现 CuiSelectEnum 组件（枚举选择框）
- [x] 8.3 实现 CuiSelectDict 组件（字典选择框）
- [x] 8.4 实现 CuiRadioEnum 组件（枚举单选组）
- [x] 8.5 实现 CuiRadioDict 组件（字典单选组）
- [x] 8.6 实现 CuiCheckboxEnum 组件（枚举复选组）
- [x] 8.7 实现 CuiAutocomplete 组件（自动完成输入框）
- [x] 8.8 为所有 P2 组件创建单元测试（目标：每个 70% 覆盖率）
- [x] 8.9 从 src/index.ts 导出所有 P2 组件
- [x] 8.10 更新 src/global.d.ts，添加 P2 组件类型
- [x] 8.11 为所有 P2 组件创建演示示例
- [x] 8.12 为所有 P2 组件创建文档

## 9. 组件样式

- [x] 9.1 创建 src/styles/components/ 目录
- [x] 9.2 使用 BEM 命名实现 CuiTable 的 SCSS 文件
- [x] 9.3 使用 BEM 命名实现 CuiForm 的 SCSS 文件
- [x] 9.4 使用 BEM 命名实现 CuiSearch 的 SCSS 文件
- [x] 9.5 使用 BEM 命名实现 CuiDialogForm 的 SCSS 文件
- [x] 9.6 为所有 P1 组件实现 SCSS 文件
- [x] 9.7 为所有 P2 组件实现 SCSS 文件
- [x] 9.8 在 src/styles/index.scss 中导入所有组件样式
- [x] 9.9 验证可以单独导入各个组件样式
- [x] 9.10 通过 CSS 变量覆盖测试主题自定义

## 10. 类型系统完善

- [x] 10.1 验证所有组件 props 使用 Interface 定义
- [x] 10.2 验证所有组件从 types.ts 导出其类型
- [x] 10.3 验证 src/index.ts 重新导出所有组件类型
- [x] 10.4 完成 src/global.d.ts，包含所有 17 个组件类型声明
- [x] 10.5 为复杂类型添加 JSDoc 注释
- [x] 10.6 使用 expectTypeOf 为泛型组件创建类型测试
- [x] 10.7 验证 Volar 自动完成在 Nuxt 演示中工作
- [x] 10.8 验证 TypeScript 严格模式通过，无错误

## 11. 测试与质量

- [x] 11.1 运行完整测试套件并验证所有测试通过（278/278 通过）
- [x] 11.2 生成覆盖率报告并验证 P0 ≥85%、P1 ≥75%、P2 ≥70%（总体 76.81%）
- [x] 11.3 修复任何失败的测试或覆盖率缺口
- [x] 11.4 添加组件交互的集成测试（例如 CuiSearch + CuiTable）
- [x] 11.5 在 Nuxt 演示中测试所有组件以进行视觉验证
- [x] 11.6 测试构建输出（验证 dist/ 包含所有预期文件）
- [x] 11.7 在单独的测试项目中测试包导入

## 12. 文档完善

- [x] 12.1 审查并增强 getting-started.md，包含完整示例
- [x] 12.2 确保所有 17 个组件都有文档页面
- [x] 12.3 为每个组件文档添加 API 参考表（props、events、slots）
- [x] 12.4 使用 MDC 语法为每个组件文档添加交互式示例
- [x] 12.5 创建从旧版 vue-element-cui 到新版本的迁移指南
- [x] 12.6 在文档中添加故障排除部分
- [x] 12.7 创建变更日志，记录所有破坏性变更
- [ ] 12.8 如果计划开源，添加贡献指南
- [x] 12.9 编写 unplugin-vue-components 和 unplugin-auto-import 的 resolver 使用文档

## 13. 构建与部署

- [x] 13.1 验证构建工具生成正确的 ESM 和 CJS 输出（已切换到 Vite library mode）
- [x] 13.2 验证类型声明完整且正确
- [x] 13.3 验证 SCSS 编译生成所有 CSS 文件
- [x] 13.4 测试 package.json 导出配置
- [x] 13.5 构建 Nuxt 文档站点以供部署
- [ ] 13.6 设置 CI/CD 管道用于自动化测试和构建
- [ ] 13.7 配置 npm 发布脚本（如果发布）
- [ ] 13.8 创建 v1.0.0 发布说明
- [x] 13.9 为组件库提供 resolver 子路径导出与按需导入支持

## 15. 构建工具切换（tsdown → Vite）

- [x] 15.1 编写 tsdown 构建失败技术报告（docs/reports/2026-03-11-tsdown-build-failure-and-migration-to-vite.md）
- [x] 15.2 删除 tsdown.config.ts 配置文件
- [x] 15.3 创建 vite.config.ts 配置文件，配置 library mode
- [x] 15.4 更新 package.json 构建脚本（dev、build、build:js）
- [x] 15.5 添加 vite-plugin-dts 依赖用于类型生成
- [x] 15.6 验证 Vite 构建成功（运行 pnpm run build）
- [x] 15.7 更新组件库迁移设计计划中的构建工具变更说明（现已并入 2026-03-13 主计划）
- [x] 15.8 更新组件库迁移实施计划中的构建工具变更说明（现已并入 2026-03-13 主计划）
- [x] 15.9 更新 packages/vue-element-cui/docs/prompts/init-components-lib.md（构建工具变更说明）
- [x] 15.10 更新 OpenSpec 变更记录（design.md 已更新）

## 14. 最终验证

- [ ] 14.1 在演示中对所有组件进行完整的手动测试
- [ ] 14.2 在全新项目中测试库安装
- [x] 14.3 验证所有 TypeScript 类型在使用项目中正常工作
- [x] 14.4 验证 Volar 支持在使用项目中工作
- [ ] 14.5 性能审计（包大小、加载时间）
- [ ] 14.6 可访问性审计（键盘导航、屏幕阅读器）
- [ ] 14.7 跨浏览器测试（Chrome、Firefox、Safari、Edge）
- [ ] 14.8 审查并解决设计文档中的任何未决问题
- [ ] 14.9 获得利益相关者的发布批准
- [ ] 14.10 发布 v1.0.0 并向团队宣布
