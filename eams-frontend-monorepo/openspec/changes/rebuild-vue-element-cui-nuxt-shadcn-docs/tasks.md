## 1. 重建文档站底座

- [x] 1.1 重写 `packages/vue-element-cui-nuxt/package.json`，移除旧文档主题依赖并接入 `shadcn-docs-nuxt` 所需依赖与脚本
- [x] 1.2 重写 `packages/vue-element-cui-nuxt/nuxt.config.ts`、`app.config.ts` 和 `app.vue`，建立 `shadcn-docs-nuxt` 底座与首页/导航基础配置
- [x] 1.3 建立文档站自有的 `app/`、`components/content/`、样式入口与 Tailwind 扫描配置，并确认 `.superpowers/` 已被 Git 忽略
- [x] 1.4 重写 `packages/vue-element-cui-nuxt/plugins/vue-element-cui.ts`，确认真实组件库与样式链路可被文档站正确加载

## 2. 建立首页与导航体验

- [x] 2.1 实现首页入口组件，使首页优先提供安装、快速开始、组件分类和规范入口
- [x] 2.2 配置顶部导航、侧边导航和必要的页脚信息，确保一级栏目固定为"快速开始 / 组件 / 规范 / 更新"
- [x] 2.3 验证桌面端与移动端导航均可正常访问文档结构

## 3. 建立 live demo 与内容组件体系

- [x] 3.1 先为 `DemoPlayground`、`ApiTable` 等核心内容组件补最小失败测试
- [x] 3.2 实现统一的 demo 容器、代码面板、API 表和说明块内容组件
- [x] 3.3 在 `app/components/demo/` 中创建覆盖核心组件体系的手写 live demo
- [x] 3.4 让 live demo 直接运行真实 `@eams-monorepo/vue-element-cui` 组件，并验证预览优先、代码可折叠的页面模型成立

## 4. 重排内容信息架构并迁移文案

- [x] 4.1 重建 `content/` 顶级目录为"快速开始 / 组件 / 规范 / 更新"结构，并创建新的首页文档
- [x] 4.2 迁移安装、快速开始、迁移指南、排障和更新内容，尽量保留原有 markdown 文案
- [x] 4.3 按组件类型重组组件文档，并将可合并的旧页面重编排为新的体系页
- [x] 4.4 清理旧文档路径和旧内容入口，确保导航与正式入口中不再暴露旧结构
- [x] 4.5 核对并统一「resolver / 自动导入 / 组件库接入」文档与 `packages/vue-element-cui/src/resolver.ts` 实现及 `package.json` 导出的一致性；统一 README 与 Nuxt 安装页的 API 说明与用语（含 VueElementCuiAutoImportResolver 与 Volar 类型）

## 5. 新增规范栏目

- [x] 5.1 创建组件设计约定、表单与表格最佳实践、弹层与交互建议、开发约定四类规范页面
- [x] 5.2 抽离原组件页中的共性约定与最佳实践，避免在多个组件页重复散落
- [x] 5.3 将规范栏目接入首页入口、一级导航和侧边栏结构

## 6. 验证与收尾

- [x] 6.1 运行 `pnpm --filter @eams-monorepo/vue-element-cui-nuxt test`，验证文档站自有测试通过
- [x] 6.2 运行 `pnpm --filter @eams-monorepo/vue-element-cui-nuxt build`，验证文档站生产构建通过
- [x] 6.3 手工核对首页、快速开始页、至少一个组件体系页、至少一个规范页和更新页的最终呈现
- [x] 6.4 复核现有文案是否已迁入新结构、旧路径是否已正式废弃、live demo 是否可正常交互
