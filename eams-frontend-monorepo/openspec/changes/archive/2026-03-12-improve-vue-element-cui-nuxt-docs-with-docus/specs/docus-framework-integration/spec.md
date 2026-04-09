## ADDED Requirements

### Requirement: Docus 依赖安装

系统 SHALL 安装 Docus 框架及其必需的依赖包。

#### Scenario: 安装 Docus 核心依赖

- **WHEN** 开发者运行 `pnpm install`
- **THEN** 系统应当安装 `@nuxt/ui-pro` 包

#### Scenario: 移除 Tailwind CSS 依赖

- **WHEN** 开发者检查 `package.json`
- **THEN** 系统不应包含 `@nuxtjs/tailwindcss` 依赖

### Requirement: Nuxt 配置迁移到 Docus

系统 SHALL 将 `nuxt.config.ts` 配置迁移到 Docus 标准配置。

#### Scenario: 配置 Docus 模块

- **WHEN** 开发者查看 `nuxt.config.ts`
- **THEN** 配置应当包含 `@nuxt/ui-pro` 模块

#### Scenario: 配置 Nuxt Content

- **WHEN** 开发者查看 `nuxt.config.ts`
- **THEN** 配置应当包含 `@nuxt/content` 模块及其 Docus 相关配置

#### Scenario: 移除 Tailwind 配置

- **WHEN** 开发者查看项目根目录
- **THEN** 不应存在 `tailwind.config.ts` 文件

### Requirement: Docus 应用配置

系统 SHALL 创建 `app.config.ts` 文件来配置 Docus 应用。

#### Scenario: 创建应用配置文件

- **WHEN** 开发者查看项目根目录
- **THEN** 应当存在 `app.config.ts` 文件

#### Scenario: 配置站点元信息

- **WHEN** 开发者查看 `app.config.ts`
- **THEN** 配置应当包含站点名称、描述、URL 等元信息

#### Scenario: 配置顶部导航

- **WHEN** 开发者查看 `app.config.ts`
- **THEN** 配置应当包含 `header.navigation` 数组定义顶部导航项

### Requirement: 简化应用入口

系统 SHALL 简化 `app.vue` 为 Docus 标准布局。

#### Scenario: 使用 Docus 布局组件

- **WHEN** 开发者查看 `app.vue`
- **THEN** 文件应当仅包含 `<NuxtLayout>` 和 `<NuxtPage>` 组件

#### Scenario: 移除自定义布局代码

- **WHEN** 开发者查看 `app.vue`
- **THEN** 不应包含自定义的导航栏、侧边栏等布局代码

### Requirement: 主题 Tokens 配置（可选）

系统 MAY 创建 `tokens.config.ts` 文件来自定义主题 tokens。

#### Scenario: 自定义主题颜色

- **WHEN** 开发者需要自定义品牌颜色
- **THEN** 可以在 `tokens.config.ts` 中定义颜色 tokens

#### Scenario: 自定义字体

- **WHEN** 开发者需要自定义字体
- **THEN** 可以在 `tokens.config.ts` 中定义字体 tokens
