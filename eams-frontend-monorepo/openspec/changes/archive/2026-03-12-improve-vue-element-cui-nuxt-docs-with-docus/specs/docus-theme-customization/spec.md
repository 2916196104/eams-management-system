## ADDED Requirements

### Requirement: 深色模式支持

系统 SHALL 支持深色模式和浅色模式切换。

#### Scenario: 显示主题切换按钮

- **WHEN** 用户访问文档站点
- **THEN** 顶部导航栏应当显示主题切换按钮

#### Scenario: 切换到深色模式

- **WHEN** 用户点击主题切换按钮选择深色模式
- **THEN** 整个站点应当切换到深色主题

#### Scenario: 切换到浅色模式

- **WHEN** 用户点击主题切换按钮选择浅色模式
- **THEN** 整个站点应当切换到浅色主题

#### Scenario: 记住用户偏好

- **WHEN** 用户选择了某个主题
- **THEN** 下次访问时应当自动应用用户上次选择的主题

#### Scenario: 跟随系统主题

- **WHEN** 用户未手动选择主题
- **THEN** 应当自动跟随操作系统的主题设置

### Requirement: 自定义品牌颜色

系统 SHALL 支持在 `app.config.ts` 或 `tokens.config.ts` 中自定义品牌颜色。

#### Scenario: 配置主色调

- **WHEN** 开发者在配置文件中定义 `primary` 颜色
- **THEN** 站点的主色调（链接、按钮等）应当使用该颜色

#### Scenario: 配置强调色

- **WHEN** 开发者在配置文件中定义 `accent` 颜色
- **THEN** 站点的强调元素应当使用该颜色

#### Scenario: 深色模式颜色适配

- **WHEN** 用户切换到深色模式
- **THEN** 自定义颜色应当自动调整亮度以适配深色背景

### Requirement: 自定义字体

系统 MAY 支持在 `tokens.config.ts` 中自定义字体。

#### Scenario: 配置正文字体

- **WHEN** 开发者在配置文件中定义 `font.body`
- **THEN** 文档正文应当使用该字体

#### Scenario: 配置标题字体

- **WHEN** 开发者在配置文件中定义 `font.heading`
- **THEN** 文档标题应当使用该字体

#### Scenario: 配置代码字体

- **WHEN** 开发者在配置文件中定义 `font.mono`
- **THEN** 代码块应当使用该等宽字体

### Requirement: 自定义布局

系统 MAY 支持通过配置调整布局参数。

#### Scenario: 配置内容宽度

- **WHEN** 开发者在配置文件中定义 `layout.maxWidth`
- **THEN** 文档内容区域的最大宽度应当使用该值

#### Scenario: 配置侧边栏宽度

- **WHEN** 开发者在配置文件中定义 `layout.asideWidth`
- **THEN** 侧边栏的宽度应当使用该值

### Requirement: 自定义 Logo

系统 SHALL 支持在 `app.config.ts` 中配置自定义 Logo。

#### Scenario: 配置浅色模式 Logo

- **WHEN** 开发者在配置文件中定义 `header.logo.light`
- **THEN** 浅色模式下应当显示该 Logo

#### Scenario: 配置深色模式 Logo

- **WHEN** 开发者在配置文件中定义 `header.logo.dark`
- **THEN** 深色模式下应当显示该 Logo

#### Scenario: Logo 链接到首页

- **WHEN** 用户点击 Logo
- **THEN** 应当跳转到文档站点首页
