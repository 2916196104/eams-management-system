# `eams-stu`

> **Monorepo 包名**：`@eams-monorepo/stu-app`
>
> EAMS 学生端移动应用，属于 `eams-frontend-monorepo` 工作区。

<p align="center">基于<a href="https://github.com/uni-helper/vitesse-uni-app">vitesse-uni-app</a>的深度整合 Wot UI 组件库，现代化的 uni-app 快速起手项目</p>

<p align="center">
  <a href="https://starter.wot-ui.cn/demo/#/">📱 在线预览</a>
  <a href="https://starter.wot-ui.cn/">📖 在线文档</a>
</p>

## 特性

- ⚡️ [Vue 3](https://github.com/vuejs/core), [Vite](https://github.com/vitejs/vite), [pnpm](https://pnpm.io/), [esbuild](https://github.com/evanw/esbuild) - 就是快！

- 🗂 [基于文件的路由](./src/pages)

- 📦 [组件自动化加载](./src/components)

- 📑 [布局系统](./src/layouts)

- 🐂 [Wot UI](https://github.com/Moonofweisheng/wot-design-uni) - 基于 Vue3 + TypeScript 的 uni-app 组件库，提供 70+ 高质量组件，支持国际化（内置多语言包）、暗黑模式与通过 CSS 变量进行主题定制

- 🚦 [@wot-ui/router](https://github.com/wot-ui/my-uni) - 适用于 uni-app&vue3 的轻量级路由库

- 🔄 [Uni Mini CI](https://github.com/Moonofweisheng/uni-mini-ci) - 一个小程序端持续集成的插件

- 🌐 [Alova](https://alova.js.org/zh-CN/) - 极致高效的请求工具集

- 🆒 [Uni Ku](https://uni-ku.js.org/) - 非常酷的 uni-app 插件库

- 📊 [Uni Echarts](https://uni-echarts.xiaohe.ink/) - 适用于 uni-app 的 Apache ECharts 组件

- 🎨 [UnoCSS](https://github.com/unocss/unocss) - 高性能且极具灵活性的即时原子化 CSS 引擎

- 😃 [各种图标集为你所用](https://github.com/antfu/unocss/tree/main/packages/preset-icons)

- 🔥 使用 [新的 `<script setup>` 语法](https://github.com/vuejs/rfcs/pull/227)

- 📥 [API 自动加载](https://github.com/antfu/unplugin-auto-import) - 直接使用 Composition API 无需引入

- 🦾 [TypeScript](https://www.typescriptlang.org/) & [ESLint](https://eslint.org/) - 保证代码质量

## 在 Monorepo 中开发

在 monorepo 根目录执行：

```bash
# 默认开发（h5）
pnpm --filter @eams-monorepo/stu-app dev

# 微信小程序开发
pnpm --filter @eams-monorepo/stu-app dev:mp-weixin

# App 开发
pnpm --filter @eams-monorepo/stu-app dev:app

# 构建
pnpm --filter @eams-monorepo/stu-app build

# 类型检查
pnpm --filter @eams-monorepo/stu-app type-check

# ESLint
pnpm --filter @eams-monorepo/stu-app lint
pnpm --filter @eams-monorepo/stu-app lint:fix
```

常见平台命令示例：

- 小程序：`dev:mp-weixin` / `build:mp-weixin`
- H5：`dev:h5` / `build:h5`
- App：`dev:app` / `build:app`

## 快速上手

详细说明见 [快速上手](https://starter.wot-ui.cn/guide/installation.html)。

## 更新日志

详细日志见 [更新日志](https://starter.wot-ui.cn/guide/changelog.html)。

## 社区

[加群沟通](https://wot-ui.cn/guide/join-group.html)

## 周边生态

| 项目                                                                        | 描述                                                 |
| --------------------------------------------------------------------------- | ---------------------------------------------------- |
| [wot-ui-intellisense](https://github.com/wot-ui/wot-ui-intellisense)        | wot-ui vscode 代码提示插件                           |
| [awesome-uni-app](https://github.com/uni-helper/awesome-uni-app)            | 多端统一开发框架 uni-app 优秀开发资源汇总            |
| [create-uni](https://github.com/uni-helper/create-uni)                      | 快速创建 uni-app 项目                                |
| [wot-starter-retail](https://github.com/Moonofweisheng/wot-starter-retail)  | 基于 wot-ui 的 uni-app 零售行业模板                  |
| [uni-mini-ci](https://github.com/Moonofweisheng/uni-mini-ci)                | 一个 uni-app 小程序端构建后支持 CI（持续集成）的插件 |
| [@wot-ui/router](https://github.com/wot-ui/my-uni)                          | 一个基于 vue3 和 Typescript 的轻量级 uni-app 路由库  |
| [wot-design-uni AI 助手](https://www.coze.cn/store/bot/7347916532258701363) | 一个能回答你关于 wot-ui 组件库问题的智能助手         |
| [uni-ku-root](https://github.com/uni-ku/root)                               | 一个模拟 App.vue 原有能力的根组件插件                |
| [uni-echarts](https://uni-echarts.xiaohe.ink/)                              | 适用于 uni-app 的 Apache ECharts 组件                |

## 贡献者们

感谢以下所有给 Wot Starter 贡献过代码的 [开发者](https://github.com/wot-ui/wot-starter/graphs/contributors)。

<a href="https://github.com/wot-ui/wot-starter/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=wot-ui/wot-starter" />
</a>

## 鸣谢

- [uni-helper](https://github.com/uni-helper) - 感谢 uni-helper 团队为 uni-app 开发体验优化做出的贡献。
- [vitesse-uni-app](https://github.com/uni-helper/vitesse-uni-app) - 感谢 vitesse-uni-app 提供的快速起手项目。
- [uni-ku](https://uni-ku.js.org/) - 感谢 uni-ku 团队为 uni-app 插件生态做出的贡献。

## 开源协议

本项目基于 [MIT](https://zh.wikipedia.org/wiki/MIT%E8%A8%B1%E5%8F%AF%E8%AD%89) 协议，请自由地享受和参与开源。

[![Star History Chart](https://api.star-history.com/svg?repos=wot-ui/wot-starter&type=Date)](https://star-history.com/#wot-ui/wot-starter&Date)
