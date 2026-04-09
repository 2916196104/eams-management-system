# <!-- 已完成 --> 使用 shadcn-docs-nuxt 重构重做 vue-element-cui-nuxt 组件库文档

针对现在的 `packages\vue-element-cui-nuxt\package.json` ，针对 vue-element-cui-nuxt 这款组件库文档内，我要求你做出重大改造。

## 明确清楚 vue-element-cui-nuxt 的核心定位

该 vue-element-cui-nuxt 是为了给 vue-element-cui 充当组件库文档的。

## 深刻调研 `shadcn-docs-nuxt` 技术方案

这份报告 `docs\reports\2026-3-12-use-shadcn-docs-nuxt.md` 说明了你需要重点调研的 `shadcn-docs-nuxt` 的文件。重点学会如何使用 `shadcn-docs-nuxt` 来为 vue-element-cui 搭建组件库。

## 深刻阅读本地的代码仓库

该报告要求你阅读的仓库，我已经克隆到本地了，请你直接访问这些目录来直接学习代码写法：

- ZTL-UwU/shadcn-docs-nuxt `D:\code\github-desktop-store\shadcn-docs-nuxt__ZTL-UwU`
- ZTL-UwU/shadcn-docs-nuxt-starter `D:\code\github-desktop-store\shadcn-docs-nuxt-starter__ZTL-UwU`
- ijkml/nuxt-umami-docs `D:\code\github-desktop-store\nuxt-umami-docs__ijkml`
- isbrandonw/shadcn-docs-ui-thing `D:\code\github-desktop-store\shadcn-docs-ui-thing__isbrandonw`

## 根据报告的要求完成针对性探索和学习

报告 `docs\reports\2026-3-12-use-shadcn-docs-nuxt.md` 同时还说明了如何完成针对性的探索和学习，请务必认真学习。

## 不需要保留之前的写法

我允许你大胆的，批量删除现有的 vue-element-cui-nuxt 目录，允许你推重新来，

## 形成一份计划

注意使用全局技能`brainstorming`生成计划，在 `docs\plans` 形成一个计划。

## 生成一份完整完善的 openspec 任务

要求认真遵循 openspec 这款技能的要求，完成长任务的新建。新建的规格必须要用中文说明清楚。

## 01 <!-- 暂时不考虑继续执行，疑似出现误区 --> 执行 `rebuild-vue-element-cui-nuxt-shadcn-docs` openspec 任务

务必认真遵循 `docs\plans\2026-03-13-vue-element-cui-nuxt-shadcn-docs-rebuild-plan.md` 和 `openspec\changes\rebuild-vue-element-cui-nuxt-shadcn-docs` 内全部的规范。

## 02 <!-- 个人认定基本完成了对 shadcn-docs-nuxt 框架的转录 --> 阅读参考性质的 tailwind.css 和其他基于 shadcn-docs-nuxt

我注意到你在上一次文档构建任务内，出现了很多卡点，为了避免你绕圈子犯错，我需要你重新按照我给的路径来认真实现基于 `shadcn-docs-nuxt` 模板的组件库文档制作。

### 需要重点阅读，学习，甚至是照搬的核心配置文件

为了避免你出现故障，我需要你重点去阅读以下项目提供的这些文件：

- `nuxt.config.ts`
- `app.config.ts`
- `assets/css`
- `tailwind.config.js`

其中，关于样式我希望你重点去阅读 `tailwind.config.js` 和 `assets/css` 相关的文件。我不希望你在样式上面出现严重的问题。按理说你应该一次性的就完成配置了，直接照抄样式就可以了，基本上不会出错。我不希望你在样式上面，出现弯路。因为你在之前的任务内，就经常把已经做好的样式做坏了。把宽屏页面搞成了窄小屏幕的页面。

### 保持现在的 content 目录内容写法和目录架构

我对目前的 `packages\vue-element-cui-nuxt\content` 目录很满意。你不应该被参考项目带偏，不需要你乱改文档的目录层级。

### 需要阅读的本地项目代码

以下是你需要重点阅读的本地项目，但是你需要按照顺序，根据权重来阅读。按照权重，根据顺序排布的项目列表如下：

1. ijkml/nuxt-umami-docs `D:\code\github-desktop-store\nuxt-umami-docs__ijkml`
2. ZTL-UwU/shadcn-docs-nuxt-starter `D:\code\github-desktop-store\shadcn-docs-nuxt-starter__ZTL-UwU`
3. ZTL-UwU/shadcn-docs-nuxt `D:\code\github-desktop-store\shadcn-docs-nuxt__ZTL-UwU`
4. isbrandonw/shadcn-docs-ui-thing `D:\code\github-desktop-store\shadcn-docs-ui-thing__isbrandonw`

---

1. 项目 `ijkml/nuxt-umami-docs` 是最重要的，最核心的参考项目。这个项目提供了非常合适的配置。你应该要重点学习。
2. 项目 `shadcn-docs-nuxt-starter` 是最简单的，最基础的文档架构配置。我们的文档项目 `packages\vue-element-cui-nuxt\package.json` ，应该至少全面的包括这个基架的基础项目。
3. 项目 `shadcn-docs-nuxt` 是框架源码。你不应该模仿太多的写法，避免安装过多的依赖和配置。
4. 减少对 `shadcn-docs-ui-thing` 项目的阅读，增加对 `nuxt-umami-docs` 项目的阅读比重。

### 避免出现模块兼容的误区

我们的核心目的是为了模仿 `ijkml/nuxt-umami-docs`，在 `shadcn-docs-nuxt` 组件库文档模板框架的基础上，搭建组件库。所以我们不应该在以下地方出现严重的误区：

- i18n 模块
- icon 模块

重点是 icon 模块。我们不应该去折腾 icon。

### 保持精简

我们的 `nuxt.config.ts` 和 `app.config.ts` 应该保持精简，就像 `ijkml/nuxt-umami-docs` 项目一样精简。避免出现复杂化的误区。`ijkml/nuxt-umami-docs` 实现文档做起来很简单，我们也应该要简单的实现文档。现在我们的做法过于复杂了。陷入误区了。

## 03 <!-- 已处理，本质上是dayjs出现的客户端水和错误 --> 处理 `@eams-monorepo/vue-element-cui-nuxt` 文档出现的问题

1. 使用谷歌浏览器 MCP 运行 dev 命令。
2. 现在的文档无法完成明暗主题的切换。点击暗黑模式按钮，无法切换成暗黑模式。
3. 左侧侧边栏的折叠栏，无法实现点击效果。点击无法实现折叠的基础功能。
4. 认真参考 `D:\code\github-desktop-store\shadcn-docs-nuxt__ZTL-UwU\www` 目录的 `shadcn-docs-nuxt` 框架配置。看看是不是我们那里错配了？
5. 仔细检查是不是样式部分出现问题了。重点查看：
   - `packages\vue-element-cui-nuxt\tailwind.config.js`
   - `packages\vue-element-cui-nuxt\assets\css\tailwind.css`

### 排错结论

- 暗黑模式切换失败、侧边栏折叠点击无效，只是表象。真正的根因不是单纯的 CSS，而是 Nuxt 开发态客户端出现了水和错误（hydration error），导致文档页的交互事件没有正确挂载。
- 这次最先暴露出来的核心依赖是 `dayjs`。浏览器端实际报错是 `dayjs.min.js does not provide an export named 'default'`，说明当前运行链路错误地吃到了不兼容的入口。
- 顺着浏览器 console 继续排查，还会继续出现 `@braintree/sanitize-url`、`debug`、`mermaid` 相关的 ESM/CJS 兼容问题。如果不逐个修掉，前端会一直处于半瘫痪状态，看起来像是“主题没生效”“按钮不能点”。
- 样式并不是唯一根因，但 `tailwind.config.js` 的 `content` 扫描范围如果没有覆盖 `shadcn-docs-nuxt`，会让主题样式更难判断，所以它属于必须补齐的兜底项。

### 解决方案记忆

- 不要修改 `extends: ["shadcn-docs-nuxt"]`。这不是问题根因，错误方向的改动只会继续制造噪音。
- 要优先在 `packages\vue-element-cui-nuxt\nuxt.config.ts` 里做 Vite 层面的客户端兼容处理，避免 Nuxt 再次出现客户端水和错误。
- 当前已经验证有效的处理方式如下：
  - 使用 `createRequire(import.meta.url)` 明确解析依赖入口。
  - 将 `dayjs` 别名到 `dayjs/esm/index.js`，避免浏览器端再落到错误入口。
  - 将 `mermaid` 别名到 `mermaid/dist/mermaid.esm.mjs`，强制使用 ESM 入口。
  - 将 `debug` 别名到本地 `./shims/debug.ts`，规避其浏览器端默认导出兼容问题。
  - 在 `vite.optimizeDeps.include` 中显式包含 `debug`、`dayjs`、`@braintree/sanitize-url`、`mermaid`。
  - 在 `vite.resolve.dedupe` 中加入 `dayjs`，避免重复解析造成前后端入口不一致。
  - 在 `vite.ssr.noExternal` 中加入 `debug`，避免 SSR/客户端走出不同解析结果。
- 在 `packages\vue-element-cui-nuxt\tailwind.config.js` 中，必须补上 `../../node_modules/shadcn-docs-nuxt/**/*.{vue,js,ts,mjs}` 的扫描路径，避免 shadcn 文档层的暗黑样式类被裁剪。

### Debug 复用步骤

1. 先用 Chrome MCP 打开 dev 页面，不要一上来就只盯着样式。
2. 第一时间看浏览器 console，确认是否有客户端模块导入错误。
3. 按错误链逐个修复依赖入口，不要只修第一个 `dayjs` 报错就停下。
4. 每修完一项都重新刷新并复测暗黑模式按钮、侧边栏折叠按钮。
5. 只有当 console 不再出现阻断 hydration 的模块错误后，再去判断 Tailwind 或主题样式问题。

## 04 <!-- 已处理 --> 解决文档渲染问题

认真阅读 `packages\vue-element-cui-nuxt\content` 目录下面的 markdown 文档， 对于很多的 `::demo-playground` 页面，出现了明显的渲染失败的问题。请你检查一下是不是 mdc 格式出错，导致渲染失败？或者是你使用了 shadcn-docs-nuxt 提供的错误的组件？

注意阅读之前的错误经验教训，看看是不是要增加 prettier 的忽略注释。

如下图所示：

![2026-03-22-04-05-15](https://gh-img-store.ruan-cat.com/img/2026-03-22-04-05-15.png)

## 05 <!-- 已完成 --> 将使用 shadcn-docs-nuxt 制作组件库的知识制作成通用的，可以跨项目复用的技能

认真阅读以下内容：

1. openspec\changes\rebuild-vue-element-cui-nuxt-shadcn-docs 目录的实施规范。
2. packages\vue-element-cui-nuxt\package.json ，即整个 `vue-element-cui-nuxt` 项目。
3. docs\plans\2026-03-13-vue-element-cui-nuxt-shadcn-docs-rebuild-plan.md 实施计划。
4. docs\reports\2026-3-12-use-shadcn-docs-nuxt.md 探索报告。

我需要你根据本地的记忆，和历史的经验教训，编写一个跨项目的，通用的技能。用来实现快速给其他组件库或项目初始化一个基于 `shadcn-docs-nuxt` 的组件库文档。

### 编写地址

在 `D:\code\github-desktop-store\gh.ruancat.monorepo\ai-plugins\dev-skills\skills\init-shadcn-docs-nuxt` 内编写 `init-shadcn-docs-nuxt` 这款技能。
