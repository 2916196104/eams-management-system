## ADDED Requirements

### Requirement: 启用 Docus 内置搜索

系统 SHALL 启用 Docus 内置的本地搜索功能。

#### Scenario: 配置搜索功能

- **WHEN** 开发者在 `app.config.ts` 中配置搜索
- **THEN** 应当启用 `search` 选项

#### Scenario: 显示搜索按钮

- **WHEN** 用户访问文档站点
- **THEN** 顶部导航栏应当显示搜索按钮或搜索框

#### Scenario: 支持键盘快捷键

- **WHEN** 用户按下 `Ctrl+K` 或 `Cmd+K`
- **THEN** 应当打开搜索对话框

### Requirement: 搜索文档内容

系统 SHALL 支持搜索文档标题和内容。

#### Scenario: 搜索标题

- **WHEN** 用户输入搜索关键词
- **THEN** 应当返回标题匹配的文档页面

#### Scenario: 搜索正文内容

- **WHEN** 用户输入搜索关键词
- **THEN** 应当返回正文内容匹配的文档页面

#### Scenario: 支持中文搜索

- **WHEN** 用户输入中文关键词
- **THEN** 应当正确返回中文内容匹配的结果

#### Scenario: 高亮搜索结果

- **WHEN** 用户点击搜索结果
- **THEN** 跳转到对应页面后应当高亮显示匹配的关键词

### Requirement: 搜索结果展示

系统 SHALL 以清晰的方式展示搜索结果。

#### Scenario: 显示结果标题和摘要

- **WHEN** 搜索返回结果
- **THEN** 每个结果应当显示页面标题和匹配内容的摘要

#### Scenario: 按相关性排序

- **WHEN** 搜索返回多个结果
- **THEN** 结果应当按相关性从高到低排序

#### Scenario: 支持键盘导航

- **WHEN** 搜索对话框打开
- **THEN** 用户应当可以使用上下箭头键导航结果，使用回车键打开选中的结果

### Requirement: Algolia DocSearch 集成（可选）

系统 MAY 集成 Algolia DocSearch 以提供更强大的搜索功能。

#### Scenario: 配置 Algolia 应用

- **WHEN** 开发者申请了 Algolia DocSearch
- **THEN** 可以在 `app.config.ts` 中配置 Algolia 的 `appId`、`apiKey`、`indexName`

#### Scenario: 使用 Algolia 搜索

- **WHEN** 配置了 Algolia DocSearch
- **THEN** 搜索功能应当使用 Algolia 的搜索服务而非本地搜索

#### Scenario: 自动索引更新

- **WHEN** 文档内容更新并部署
- **THEN** Algolia 爬虫应当自动更新搜索索引
