# Vue Element CUI - Nuxt Documentation

基于 Nuxt 3 和 @nuxt/content 的 Vue Element CUI 组件库文档系统。

## 功能特性

- 📝 基于 Markdown 的文档编写
- 🎨 Tailwind CSS 样式系统
- 🌙 代码语法高亮（github-dark 主题）
- 📱 响应式设计
- 🔍 侧边栏导航
- ⚡️ 快速热更新

## 开发

```bash
# 安装依赖
pnpm install

# 启动开发服务器
pnpm dev

# 构建生产版本
pnpm build

# 预览生产版本
pnpm preview
```

## 项目结构

```
vue-element-cui-nuxt/
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
├── public/                    # 静态资源
├── app.vue                    # 根组件
├── nuxt.config.ts            # Nuxt 配置
├── tailwind.config.ts        # Tailwind 配置
└── package.json
```

## 添加新文档

1. 在 `content/docs/` 目录下创建 Markdown 文件
2. 在 `pages/docs/[...slug].vue` 中添加导航链接
3. 文档会自动渲染并支持语法高亮

## 技术栈

- [Nuxt 3](https://nuxt.com/) - Vue 3 框架
- [@nuxt/content](https://content.nuxt.com/) - 文档系统
- [Tailwind CSS](https://tailwindcss.com/) - CSS 框架
- [TypeScript](https://www.typescriptlang.org/) - 类型支持

## 访问地址

- 开发环境: http://localhost:3000
- 首页: http://localhost:3000
- 文档: http://localhost:3000/docs/getting-started
