## ADDED Requirements

### Requirement: 顶部导航配置

系统 SHALL 在 `app.config.ts` 中配置顶部导航栏。

#### Scenario: 定义导航项

- **WHEN** 开发者配置 `header.navigation`
- **THEN** 应当支持定义导航项的标题、链接、图标

#### Scenario: 支持外部链接

- **WHEN** 导航项链接到外部 URL
- **THEN** 链接应当在新标签页打开

#### Scenario: 支持下拉菜单

- **WHEN** 导航项包含子项
- **THEN** 应当显示为下拉菜单

### Requirement: 侧边栏导航

系统 SHALL 根据文档内容自动生成或手动配置侧边栏导航。

#### Scenario: 自动生成侧边栏

- **WHEN** 开发者未手动配置侧边栏
- **THEN** Docus 应当根据 `content/` 目录结构自动生成侧边栏

#### Scenario: 手动配置侧边栏

- **WHEN** 开发者在 `app.config.ts` 中配置 `aside.navigation`
- **THEN** 应当使用手动配置的侧边栏结构

#### Scenario: 高亮当前页面

- **WHEN** 用户访问某个文档页面
- **THEN** 侧边栏应当高亮显示当前页面

#### Scenario: 支持多级导航

- **WHEN** 文档有多级目录结构
- **THEN** 侧边栏应当支持展开/折叠多级导航

### Requirement: 面包屑导航

系统 SHALL 在文档页面顶部显示面包屑导航。

#### Scenario: 显示当前路径

- **WHEN** 用户访问文档页面
- **THEN** 面包屑应当显示从首页到当前页面的完整路径

#### Scenario: 支持点击跳转

- **WHEN** 用户点击面包屑中的某一级
- **THEN** 应当跳转到对应的页面

### Requirement: 目录（Table of Contents）

系统 SHALL 在文档页面右侧显示当前页面的目录。

#### Scenario: 自动提取标题

- **WHEN** 文档包含 Markdown 标题
- **THEN** 目录应当自动提取 h2 和 h3 标题

#### Scenario: 高亮当前阅读位置

- **WHEN** 用户滚动页面
- **THEN** 目录应当高亮显示当前阅读的标题

#### Scenario: 点击跳转到标题

- **WHEN** 用户点击目录中的标题
- **THEN** 页面应当平滑滚动到对应标题位置

### Requirement: 页脚配置

系统 SHALL 在 `app.config.ts` 中配置页脚信息。

#### Scenario: 显示版权信息

- **WHEN** 开发者配置 `footer.copyright`
- **THEN** 页脚应当显示版权信息

#### Scenario: 显示社交链接

- **WHEN** 开发者配置 `footer.socials`
- **THEN** 页脚应当显示社交媒体链接图标
