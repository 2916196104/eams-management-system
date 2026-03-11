# 2026-03-11 Docus 框架研究报告

## 概述

Docus 是一个基于 Nuxt 4 的现代化文档框架，专为构建美观、高性能的组件库文档而设计。它提供开箱即用的主题、搜索功能、国际化支持和 AI 集成。

## 核心特性

- **Markdown 优先**：使用标准 Markdown 编写文档，支持 MDC（Markdown Components）语法
- **组件丰富**：集成 Nuxt UI 组件，支持在 Markdown 中直接使用 Vue 组件
- **多语言支持**：原生 i18n 支持，基于 @nuxtjs/i18n 模块
- **搜索功能**：内置全文搜索，自动生成搜索索引
- **AI 集成**：包含 MCP 服务器，支持 Claude、Cursor 等 AI 工具集成
- **主题定制**：基于 Tailwind CSS v4 和 CSS 变量的灵活主题系统
- **性能优化**：Nuxt 4 + TypeScript 支持，SEO 优化

## 项目结构

### 基础目录结构

```
project/
├── content/                 # Markdown 文档目录
│   ├── en/                 # 英文文档（多语言时）
│   ├── zh/                 # 中文文档（多语言时）
│   └── index.md            # 首页
├── app/
│   ├── components/         # 自定义 Vue 组件
│   ├── layouts/            # 自定义布局
│   └── pages/              # 自定义页面
├── public/                 # 静态资源
├── assets/
│   ├── css/
│   │   └── main.css       # 主样式文件（包含 @theme）
│   └── icons/             # 自定义 SVG 图标
├── app.config.ts          # 应用配置
├── nuxt.config.ts         # Nuxt 配置
└── package.json
```

### 内容组织规则

- **单语言**：文件直接放在 `content/` 下，`getting-started.md` → `/getting-started`
- **多语言**：使用语言前缀文件夹，`content/en/guide.md` → `/en/guide`，`content/zh/guide.md` → `/zh/guide`
- **嵌套结构**：目录结构自动映射为路由，`content/docs/components/button.md` → `/docs/components/button`

## app.config.ts 配置

### 基础配置示例

```typescript
export default defineAppConfig({
  docus: {
    // 基础信息
    title: 'Vue Element CUI',
    description: '企业级 Vue 组件库文档',
    url: 'https://your-domain.com',
    image: '/social-card-preview.png',

    // 头部配置
    header: {
      title: 'Vue Element CUI',
      logo: {
        light: '/logo-light.svg',
        dark: '/logo-dark.svg'
      },
      showSearchBar: true,
      links: [
        {
          icon: 'i-simple-icons-github',
          to: 'https://github.com/your-repo',
          target: '_blank'
        }
      ]
    },

    // 社交链接
    socials: {
      github: 'your-username/your-repo',
      twitter: 'your-handle',
      discord: 'your-discord-link'
    },

    // 目录配置
    aside: {
      level: 0,
      collapsed: false,
      exclude: []
    },

    // 语言配置
    locale: 'en'
  },

  // UI 主题配置
  ui: {
    colors: {
      primary: 'green',
      secondary: 'blue',
      success: 'green',
      info: 'blue',
      warning: 'yellow',
      error: 'red',
      neutral: 'slate'
    }
  }
})
```

### GitHub 集成

```typescript
export default defineAppConfig({
  docus: {
    github: {
      owner: 'your-org',
      repo: 'your-repo',
      branch: 'main',
      rootDir: 'packages/docs'  // 如果文档在子目录
    }
    // 或禁用：github: false
  }
})
```

## MDC 组件使用

### 基础语法

```markdown
::component-name
Content goes here
::
```

### 嵌套组件

```markdown
:::parent-component
::child-component
Content
::
:::
```

### 带属性的组件

```markdown
::card{title="My Card" icon="i-lucide-star" color="blue"}
Card content here
::
```

## 常用 MDC 组件

### 1. Callout（提示框）

```markdown
::callout{type="info"}
This is an informational callout
::

::callout{type="warning"}
This is a warning
::

::callout{type="success"}
This is a success message
::
```

### 2. Tabs（标签页）

```markdown
::tabs
  ::tab{label="Vue"}
  Vue code example
  ::
  ::tab{label="React"}
  React code example
  ::
::
```

### 3. Steps（步骤）

```markdown
::steps
  ::step
  First step description
  ::
  ::step
  Second step description
  ::
::
```

### 4. Card/CardGroup（卡片）

```markdown
::card-group
  ::card
  Card 1 content
  ::
  ::card
  Card 2 content
  ::
::
```

### 5. Accordion（折叠框）

```markdown
::accordion
  ::accordion-item{label="Question 1"}
  Answer 1
  ::
  ::accordion-item{label="Question 2"}
  Answer 2
  ::
::
```

### 6. Badge（标签）

```markdown
::badge
v1.0.0
::
```

## 自定义 MDC 组件

### 创建交互式演示组件

在 `app/components/` 中创建 Vue 组件，自动在 Markdown 中可用：

```vue
<!-- app/components/ComponentDemo.vue -->
<template>
  <div class="component-demo">
    <div class="demo-preview">
      <slot />
    </div>
    <div class="demo-code">
      <pre><code>{{ code }}</code></pre>
    </div>
  </div>
</template>

<script setup lang="ts">
defineProps({
  code: {
    type: String,
    required: true
  }
})
</script>

<style scoped>
.component-demo {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 1rem;
  border: 1px solid var(--color-gray-200);
  border-radius: 0.5rem;
  padding: 1rem;
}

.demo-preview {
  padding: 1rem;
  background: var(--color-gray-50);
  border-radius: 0.25rem;
}

.demo-code {
  overflow-x: auto;
  background: var(--color-gray-900);
  color: var(--color-gray-50);
  padding: 1rem;
  border-radius: 0.25rem;
}
</style>
```

在 Markdown 中使用：

```markdown
::component-demo{code="<button>Click me</button>"}
<button class="px-4 py-2 bg-blue-500 text-white rounded">
  Click me
</button>
::
```

## 导航配置

### 自定义头部组件

在 `app/components/` 中创建以下组件来覆盖默认行为：

- `AppHeaderLogo` — 自定义 Logo
- `AppHeaderCTA` — 添加 CTA 按钮
- `AppHeaderCenter` — 自定义搜索栏区域
- `AppHeaderBody` — 移动菜单显示

### 自定义侧边栏

- `DocsAsideLeftTop` — 左侧边栏顶部
- `DocsAsideLeftBody` — 左侧导航区域
- `DocsAsideRightBottom` — 右侧边栏底部（目录）

### 自定义图标

在 `assets/icons/` 中添加 SVG 文件，使用 `i-custom:icon-name` 引用：

```markdown
::card{icon="i-custom:my-icon"}
Card with custom icon
::
```

## 主题定制

### CSS 变量配置

在 `assets/css/main.css` 中定义自定义颜色：

```css
@theme {
  --color-primary-50: #f0f9ff;
  --color-primary-100: #e0f2fe;
  --color-primary-500: #0ea5e9;
  --color-primary-900: #0c2d6b;

  --color-neutral-50: #fafafa;
  --color-neutral-900: #171717;
}
```

### 颜色别名

在 `app.config.ts` 中配置颜色别名：

```typescript
export default defineAppConfig({
  ui: {
    colors: {
      primary: 'blue',      // 主色
      secondary: 'indigo',  // 辅助色
      success: 'green',     // 成功色
      warning: 'yellow',    // 警告色
      error: 'red',         // 错误色
      neutral: 'slate'      // 中性色
    }
  }
})
```

## 搜索功能

Docus 内置全文搜索，自动生成搜索索引。搜索功能特性：

- **自动索引**：所有 Markdown 文件自动被索引
- **搜索模态框**：内置搜索 UI，支持快捷键（Cmd/Ctrl + K）
- **多语言搜索**：支持多语言文档的搜索
- **自动导航**：搜索结果点击自动导航到对应页面

无需额外配置，开箱即用。

## 国际化（i18n）

### 多语言设置

```typescript
export default defineAppConfig({
  docus: {
    // 默认语言
    locale: 'en'
  }
})
```

### 内容组织

```
content/
├── en/
│   ├── index.md
│   ├── guide.md
│   └── components/
│       └── button.md
├── zh/
│   ├── index.md
│   ├── guide.md
│   └── components/
│       └── button.md
```

自动生成路由：
- `/en/guide` → 英文指南
- `/zh/guide` → 中文指南

## 参考项目实现模式

### Vunix 项目

- **结构**：Yarn monorepo，包含 core、vue、nuxt 等多个包
- **文档**：使用 Docus 驱动的 Nuxt 应用
- **特点**：Utility-first CSS 框架集成（Tailwind、Unocss、WindiCSS）
- **TypeScript**：全量 TypeScript 支持

### Vue Final Modal 项目

- **结构**：pnpm workspaces monorepo
- **文档**：多版本文档站点（v2、v3、v4）
- **特点**：包含交互式 Stackblitz 演示
- **开发**：Vite + viteplay 交互式组件演示

## 最佳实践

### 1. 内容组织

- 使用清晰的目录结构，按功能模块组织
- 为每个组件创建独立的文档文件
- 使用 `_dir.yml` 配置目录级别的元数据

### 2. 组件演示

- 创建可交互的 MDC 组件展示实际效果
- 提供代码示例和实时预览
- 使用 Tabs 组件展示不同框架的用法

### 3. 导航体验

- 配置清晰的侧边栏导航
- 使用面包屑导航帮助用户定位
- 提供搜索功能快速查找内容

### 4. 主题一致性

- 使用 CSS 变量保持颜色一致性
- 利用 Tailwind CSS v4 的主题系统
- 支持亮色/暗色主题切换

### 5. SEO 优化

- 配置正确的 OG 图片
- 为每个页面设置合适的标题和描述
- 自动生成 sitemap.xml

## 关键配置检查清单

- [ ] `app.config.ts` 中配置基础信息（title、description、url）
- [ ] 配置 GitHub 集成用于"编辑此页"功能
- [ ] 设置社交链接
- [ ] 自定义主题颜色（primary、neutral 等）
- [ ] 创建自定义 MDC 组件用于演示
- [ ] 配置多语言内容结构（如需要）
- [ ] 自定义头部和侧边栏组件
- [ ] 添加自定义 SVG 图标
- [ ] 配置搜索功能
- [ ] 测试亮色/暗色主题切换

## 资源链接

- [Docus 官方文档](https://docus.dev/en)
- [Docus GitHub 仓库](https://github.com/nuxt-content/docus)
- [Vunix 参考项目](https://github.com/gaetansenn/vunix)
- [Vue Final Modal 参考项目](https://github.com/vue-final/vue-final-modal)
- [Nuxt Content 文档](https://content.nuxt.com)
- [Nuxt UI 文档](https://ui.nuxt.com)
- [Tailwind CSS v4 文档](https://tailwindcss.com)
