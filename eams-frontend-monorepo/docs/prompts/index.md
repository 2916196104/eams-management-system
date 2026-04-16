# 杂项提示词

本 monorepo 项目的各种杂项提示词。目前由`糕鸭果`高频使用。不在乎项目是否干净，只在乎是否高效完成任务。

## 001 <!-- 已完成 --> $using-git-worktrees 为 admin 后台项目增加 11comm 项目的 iconify 方案

1. 阅读 https://01s-11comm-doc.ruan-cat.com/docs/reports/2025-11-14-pure-admin-icon-solution-research.md 报告
2. 在 `f1-ruancat` 分支的的基础上，新建一个功能分支，专门实现 admin 内容的集成。集成目标项目提供的 iconify 方案。
3. 务必使用工作树的开发模式，新建一个 git 工作树来完成这个功能开发。

## 002 <!-- 已完成 --> 增加后台项目对 iconify 的使用技能

在 `.claude\skills\use-iconify` 内，根据历史记忆 ， `apps\eams-frontend\src\components\ReIcon` 源码和 `apps\eams-frontend\src\views\sample\reicon` 具体案例。增加一款技能，专门用来指导如何在后台项目内，使用相关的 iconify 组合式函数和组件。

我希望这款 `use-iconify` 技能能够指导本项目的全部开发者，能够正常的集成并使用相关的 iconify 显示功能。

## 003 <!-- 已完成 --> 在别的项目内新增一款名为 `init-pure-admin-iconify` 的开发技能

本项目之前集成了 iconify 能力，效果很好。我经常要对一个 vite+vue3 架构的项目，初始化基于 vue3 的 iconify 图标渲染方案。初始化一揽子的 iconify 使用工具和函数。

1. 深刻阅读该报告 https://01s-11comm-doc.ruan-cat.com/docs/reports/2025-11-14-pure-admin-icon-solution-research.md ，该报告也指导了本项目如何初始化 iconify 使用工具。
2. 认真查看在后台项目内，本项目是如何配置实现 pure-admin 提供的 iconify 方案的。
3. 认真读取 memorix 关于此的记忆。
4. 在 `D:\code\github-desktop-store\gh.ruancat.monorepo\ai-plugins\dev-skills\skills` 目录内，根据其他 `D:\code\github-desktop-store\gh.ruancat.monorepo\ai-plugins\common-tools\skills` 技能的写法，模仿其 yaml 格式数据，编写一个 `init-pure-admin-iconify` 技能。
