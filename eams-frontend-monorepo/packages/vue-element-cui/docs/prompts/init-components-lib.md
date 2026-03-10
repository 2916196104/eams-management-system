# <!-- TODO: 长任务 未完成 --> 迁移 `old\vue-element-cui` 旧项目的组件库，迁移改造全新的组件库

我需要初始化一个现代化的组件库。

在 `packages\vue-element-cui` 目录内，对 `old\vue-element-cui` 完成现代化改造迁移。

## 迁移技术栈说明表

- 构建工具： tsdown
- 开发语言： typescript
- vue 版本： vue3
- 测试工具： vitest

## 组件库架构上需要实现的功能

- 样式导入路径。
- 全局导入类型提示。适配 volar 插件的类型识别导出路径。
- playground 在线演示的子项目。
- 可以实现交互的 docs 文档，使用 nuxt 风格的 doc 文档。
- 适配 unplugin-vue-components 和 unplugin-auto-import，实现组件库的 resolver 按需导入工具。（暂不实现）
- 适配 nuxt 项目，实现按需导入的 nuxt 模块。（暂不实现）

## 重点参考项目代码

- https://github.com/plus-pro-components/plus-pro-components
