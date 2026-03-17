## 1. 依赖和配置准备

- [x] 1.1 更新 `package.json`，移除 `@nuxtjs/tailwindcss` 依赖
- [x] 1.2 更新 `package.json`，添加 `@nuxt/ui-pro` 依赖
- [x] 1.3 运行 `pnpm install` 安装新依赖
- [x] 1.4 删除 `tailwind.config.ts` 文件
- [x] 1.5 备份现有的 `nuxt.config.ts` 文件

## 2. Docus 框架配置

- [x] 2.1 创建 `app.config.ts` 文件，配置站点元信息（名称、描述、URL）
- [x] 2.2 在 `app.config.ts` 中配置顶部导航（header.navigation）
- [x] 2.3 在 `app.config.ts` 中配置 Logo（header.logo）
- [x] 2.4 在 `app.config.ts` 中配置页脚信息（footer）
- [x] 2.5 在 `app.config.ts` 中启用搜索功能（search）
- [x] 2.6 更新 `nuxt.config.ts`，配置 Docus 模块（@nuxt/ui-pro）
- [x] 2.7 更新 `nuxt.config.ts`，配置 Nuxt Content 模块
- [x] 2.8 简化 `app.vue` 为 Docus 标准布局（仅包含 NuxtLayout 和 NuxtPage）

## 3. 文档内容迁移

- [x] 3.1 创建新的 `content/` 目录结构（0.index.md, 1.getting-started/, 2.components/）
- [x] 3.2 创建 `content/0.index.md` 首页文件
- [x] 3.3 迁移入门指南到 `content/1.getting-started/` 目录
- [x] 3.4 迁移组件文档到 `content/2.components/` 目录
- [x] 3.5 更新所有文档中的内部链接，适配新的路由结构
- [x] 3.6 删除旧的 `content/docs/` 目录（迁移完成后）
- [x] 3.7 删除 `pages/` 目录（Docus 使用基于内容的路由）

## 4. 交互式组件演示系统

- [x] 4.1 创建 `components/content/` 目录
- [x] 4.2 创建 `components/content/ComponentDemo.vue` 自定义 MDC 组件
- [x] 4.3 实现 ComponentDemo 组件的预览和代码双栏布局
- [x] 4.4 实现 ComponentDemo 组件的标题和描述显示
- [x] 4.5 实现 ComponentDemo 组件的代码高亮功能
- [x] 4.6 实现 ComponentDemo 组件的响应式布局（桌面端并排，移动端堆叠）
- [x] 4.7 实现 ComponentDemo 组件的代码折叠/展开功能
- [x] 4.8 配置全局组件自动导入（从 @eams-monorepo/vue-element-cui 导入）

## 5. 组件文档内容更新

**当前状态**：✅ 已完成

**完成情况**：

- ✅ `component-explorer`：已完成 P0 核心组件源码分析，提取 API 信息
- ✅ `table-doc-editor`：已完成 CuiTable 文档更新
- ✅ `form-doc-editor`：已完成 CuiForm 文档更新
- ✅ `other-components-editor`：已完成 CuiSearch 和 CuiDialogForm 文档更新
- ✅ `doc-quality-checker`：已验证所有文档质量，全部通过

**任务清单**：

- [x] 5.1 更新 CuiTable 组件文档，使用 ComponentDemo 添加交互式演示
- [x] 5.2 更新 CuiTable 组件文档，添加标准化的 Props API 表格
- [x] 5.3 更新 CuiTable 组件文档，添加 Events API 表格
- [x] 5.4 更新 CuiTable 组件文档，添加 Slots API 表格
- [x] 5.5 更新 CuiForm 组件文档，使用 ComponentDemo 添加交互式演示
- [x] 5.6 更新 CuiForm 组件文档，添加标准化的 API 表格
- [x] 5.7 更新其他核心组件文档（CuiSearch, CuiDialogForm 等），添加交互式演示和 API 表格

## 6. 导航系统配置

- [ ] 6.1 在 `app.config.ts` 中配置侧边栏导航（aside.navigation）或使用自动生成
- [ ] 6.2 测试顶部导航的显示和跳转功能
- [ ] 6.3 测试侧边栏导航的显示、高亮和展开/折叠功能
- [ ] 6.4 测试面包屑导航的显示和跳转功能
- [ ] 6.5 测试页面目录（TOC）的显示和跳转功能

## 7. 主题和样式定制

- [ ] 7.1 （可选）创建 `tokens.config.ts` 文件
- [ ] 7.2 （可选）在 `tokens.config.ts` 中配置品牌主色调
- [ ] 7.3 测试深色模式和浅色模式的切换功能
- [ ] 7.4 测试主题切换按钮的显示和功能
- [ ] 7.5 验证自定义颜色在深色模式下的适配效果

## 8. 搜索功能配置

- [ ] 8.1 验证搜索按钮在顶部导航栏的显示
- [ ] 8.2 测试搜索快捷键（Ctrl+K / Cmd+K）
- [ ] 8.3 测试搜索功能的中文支持
- [ ] 8.4 测试搜索结果的显示和跳转
- [ ] 8.5 测试搜索结果的键盘导航功能

## 9. 测试和验证

- [ ] 9.1 本地运行 `pnpm dev`，验证开发服务器正常启动
- [ ] 9.2 访问首页，验证页面正常显示
- [ ] 9.3 访问入门指南页面，验证内容正常显示
- [ ] 9.4 访问组件文档页面，验证交互式演示正常工作
- [ ] 9.5 测试所有导航功能（顶部导航、侧边栏、面包屑、TOC）
- [ ] 9.6 测试搜索功能
- [ ] 9.7 测试深色模式切换
- [ ] 9.8 测试响应式布局（桌面端、平板、移动端）
- [ ] 9.9 验证所有内部链接正常工作
- [ ] 9.10 验证组件在文档中正常渲染（从 @eams-monorepo/vue-element-cui 导入）

## 10. 构建和部署验证

- [ ] 10.1 运行 `pnpm build`，验证构建成功
- [ ] 10.2 运行 `pnpm preview`，验证生产构建正常运行
- [ ] 10.3 检查构建产物大小，确保没有异常增大
- [ ] 10.4 验证生产构建的所有功能正常（导航、搜索、主题切换等）

## 11. 文档和清理

- [ ] 11.1 更新 `packages/vue-element-cui-nuxt/README.md`，说明 Docus 的使用方式
- [ ] 11.2 （可选）创建迁移指南文档，说明从旧版本迁移的步骤
- [ ] 11.3 删除所有旧的、不再使用的文件和目录
- [ ] 11.4 验证 Git 状态，确保没有遗漏的文件
- [ ] 11.5 提交所有更改，编写清晰的提交信息
