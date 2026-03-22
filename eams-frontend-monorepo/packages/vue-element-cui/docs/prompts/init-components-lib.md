<!-- 初步认定为已经完成迁移了 -->

# 迁移 `old\vue-element-cui` 旧项目的组件库，迁移改造全新的组件库

核心需求：

我需要初始化一个现代化的组件库。

在 `packages\vue-element-cui` 目录内，对 `old\vue-element-cui` 完成现代化改造迁移。

---

目前，我的任务是要求你新建一个 openspec 任务，先认真的罗列清楚要做的内容，明确编写目标，探索必要的文件，最后再开始编写非常详尽详细的 openspec 任务。新建的 openspec 任务名称为： `make-new-vue-element-cui` 。

## 迁移技术栈说明表

- 构建工具： Vite library mode
- 开发语言： typescript
- vue 版本： vue3
- 测试工具： vitest

## 组件库架构上需要实现的功能

- 样式导入路径。
- 全局导入类型提示。适配 volar 插件的类型识别导出路径。
- playground 在线演示的子项目。
- 可以实现交互的 docs 文档，使用 nuxt 风格的 doc 文档。
- 适配 unplugin-vue-components 和 unplugin-auto-import，实现组件库的 resolver 按需导入工具。
- 适配 nuxt 项目，实现按需导入的 nuxt 模块。（暂不实现）

## 新建 openspec 任务时的注意事项

1. 主动使用 openspec 这款技能。确保你新建的 openspec 任务满足这款技能的要求。
2. 本次任务需要你深度的探索很多代码库，和现代化的构建工具（Vite library mode）。请你务必使用 agent team 创建多个并行的子代理，完成探索任务。充分使用 context7 等 MCP 和你说具有的网络搜索工具，查询这些工具的使用用法。

## 重点参考项目代码

- https://github.com/plus-pro-components/plus-pro-components
- https://github.com/qddidi/easyest

## 01 <!-- 已完成 --> 执行 `make-new-vue-element-cui` 这款 openspec 任务

## 02 <!-- 该任务已关闭 --> 执行 `improve-vue-element-cui-nuxt-docs-with-docus` 这款 openspec 任务

## 03 <!-- 效果很差，打算用 shadcn-docs-nuxt 来重构一次文档 --> 重点迭代 `@eams-monorepo/vue-element-cui-nuxt` 文档页的效果

使用 vunix 的效果很差，打算直接用 shadcn-docs-nuxt 来完成开发了。 https://github.com/ZTL-UwU/shadcn-docs-nuxt 。

---

我对 `@eams-monorepo/vue-element-cui-nuxt` 文档页的效果很不满。其生成效果根本不是我期望的 nuxt content 风格的页面。请你针对性的学习并修改。

参考资料：

- docus 模板仓库： https://github.com/nuxt-content/docus
- docus 模板文档： https://docus.dev/en

参考项目：

- https://vue-final-modal.org/
- https://github.com/vue-final/vue-final-modal

- https://vunix.dewib.com/
- https://github.com/gaetansenn/vunix

我要求你重点学习 docus 这个框架如何使用。

你应该重点去学习 https://vunix.dewib.com/ 和 https://github.com/vue-final/vue-final-modal 仓库是怎么使用 docus 模板并且实现交互式组件库文档站点的。

我的核心目的是希望 `@eams-monorepo/vue-element-cui-nuxt` 文档项目使用 docus 来完成组件库文档站点的开发，就像 vunix 一样。vunix 做的非常好，我就是想要这种的文档站点。

去更新 `make-new-vue-element-cui` 这款 openspec 任务，这款任务没有记录详细的 `@eams-monorepo/vue-element-cui-nuxt` 组件库文档项目该如何制作。

## 04 处理 vue-element-cui 组件库出现的类型故障

我不希望在迁移组件库的时候，在新迁移的组件库内，出现类型错误。请你使用 vue-tsc 的最佳实践，在 vue-element-cui 包内安装该 vue-tsc 工具，并拓展 vue-element-cui 的类型检查能力。

在确保其满足 `openspec\changes\make-new-vue-element-cui\specs` 全部设计要求，和 `openspec\changes\make-new-vue-element-cui` 全部设计理念，和具体的迁移任务的前提下，完成类型检查能力的拓展，并修复其出现的组件库类型报错。
