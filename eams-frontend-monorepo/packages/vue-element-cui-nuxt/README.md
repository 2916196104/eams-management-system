# Vue Element CUI - Nuxt Documentation

基于 Nuxt 3 和 shadcn-docs-nuxt 的 Vue Element CUI 组件库文档系统。

> **Monorepo 包名**：`@eams-monorepo/vue-element-cui-nuxt`（私有包）
>
> 与 `@eams-monorepo/vue-element-cui` 工作区联动，承载组件库文档内容和组件示例展示。

## 功能特性

- 📝 基于 Markdown 的文档编写（MDC 语法）
- 🎨 Tailwind CSS 样式系统
- 🌙 代码语法高亮（github-dark 主题）
- 📱 响应式设计
- 🔍 侧边栏导航
- ⚡️ 快速热更新

## 本地开发

在 monorepo 根目录执行：

```bash
# 启动开发服务器
pnpm --filter @eams-monorepo/vue-element-cui-nuxt dev

# 构建生产版本
pnpm --filter @eams-monorepo/vue-element-cui-nuxt build

# 静态生成
pnpm --filter @eams-monorepo/vue-element-cui-nuxt generate

# 预览生产版本
pnpm --filter @eams-monorepo/vue-element-cui-nuxt preview
```

> 该包已配置 `predev/prebuild/postinstall -> nuxt prepare`，用于保证 Nuxt 运行前置产物。

## 测试

```bash
pnpm --filter @eams-monorepo/vue-element-cui-nuxt test
pnpm --filter @eams-monorepo/vue-element-cui-nuxt test:watch
```

## 项目结构

```plain
vue-element-cui-nuxt/
├── app.config.ts
├── nuxt.config.ts
├── tailwind.config.js
├── pages/
│   ├── index.vue              # 首页
│   └── docs/
│       └── [...slug].vue      # 文档页面模板
├── content/
│   └── docs/
│       └── getting-started.md # 快速开始文档
├── components/
│   ├── ComponentCard.vue      # 组件卡片
│   ├── NavLink.vue           # 导航链接
│   └── NavSection.vue        # 导航分组
├── shims/                     # 兼容修复（如 debug shim）
├── public/                    # 静态资源
└── package.json
```

## 添加新文档

1. 在 `content/docs/` 目录下创建 Markdown 文件
2. 在 `pages/docs/[...slug].vue` 中添加导航链接
3. 文档会自动渲染并支持语法高亮

## 文档内容维护

- 推荐在 `content/` 中维护文档内容。
- 修改 `content/**/*.md` 时，优先保持 MDC 语法结构完整（尤其是容器和 frontmatter 的紧邻关系）。
- 若需要新增演示组件，建议同步补充相应说明文档。

## 技术栈

- [Nuxt 3](https://nuxt.com/) - Vue 3 框架
- [shadcn-docs-nuxt](https://github.com/ZTL-UwU/shadcn-docs-nuxt) - 文档主题
- [@nuxt/content](https://content.nuxt.com/) - 文档系统
- [Tailwind CSS](https://tailwindcss.com/) - CSS 框架
- [TypeScript](https://www.typescriptlang.org/) - 类型支持

## 访问地址

- 开发环境: http://localhost:3000
- 首页: http://localhost:3000
- 文档: http://localhost:3000/docs/getting-started

## 关联包

- 组件库实现：`packages/vue-element-cui`
- 根目录说明：`README.md`
