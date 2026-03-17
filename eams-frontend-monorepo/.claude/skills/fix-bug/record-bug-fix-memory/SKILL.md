---
name: record-bug-fix-memory
description: 当用户要求在 bug 已经定位并修复后，记录排错经验、事故结论、AI 记忆更新、复盘摘要或本地 MCP 记忆时使用。这个技能只负责沉淀“发生了什么、为什么会发生、如何修好、以后要记住什么”，不要把它用于实际修复 bug。
---

# 记录 Bug 修复记忆

## 概述

使用这个技能，把已经完成的排错结果沉淀成可复用的长期记忆。

目标是保存根因、有效修复路径、错误假设和验证证据，让后续 agent 不再重复同样的弯路。

核心原则：记录决策链，不记录流水账。

## 何时使用

在以下场景使用这个技能：

- 用户要求更新 AI 记忆文档、记录经验教训、补充事故记录、编写复盘摘要。
- bug 已经完成复现，且有效修复路径已经明确。
- 这条经验是仓库特有知识，应该对未来 agent 可见。
- 需要把结论同步到本地 MCP 记忆，例如 Memorix。

以下情况不要使用这个技能：

- bug 还在调查中，根因没有确认。
- 用户要求的是修复实现，而不是经验沉淀。
- 你手里只有猜测、片段证据或临时绕过方案。

## 前置输入

开始写记忆前，必须能回答下面六个问题：

1. 对用户来说，表面现象是什么？
2. 实际根因是什么？
3. 哪个错误假设或误导信号浪费了时间？
4. 最终是哪一个具体改动修好了问题？
5. 用什么验证证明修复成立？
6. 这条记忆应该写到哪里？

如果有任何一个问题答不上来，先完成排错，不要提前写记忆。

## 写到哪里

- 仓库级、可复用的规则：写到根级 `CLAUDE.md`、`AGENTS.md`、`GEMINI.md`
- 跨会话的本地记忆：写到 Memorix，类型用 `gotcha`、`decision` 或 `problem-solution`
- 包级 prompts、plans、reports：只有用户明确要求时才写进去

默认规则：只要这条经验会影响整个仓库里的未来 agent，就优先写入三个根级 AI 记忆文档，不要埋进包级备注里。

## 记录什么

每条记忆至少要覆盖这六件事：

1. 问题现象：从用户视角看，哪里坏了
2. 根因：真正出错的地方
3. 关键线索：哪条信号把问题从假象拉回真实根因
4. 有效修复：真正解决问题的改动
5. 验证方式：证明修复成功的证据
6. 后续约束：未来 agent 必须先检查什么、避免什么

## 记忆模板

使用简洁、面向未来复用的结构：

- `问题现象：...`
- `根因：...`
- `关键误导点：...`
- `有效修复：...`
- `验证方式：...`
- `后续约束：...`

这些句子应该帮助未来 agent 快速做对事，而不是复述完整排错过程。

## 仓库级经验库

当用户要求“补充 AI 记忆”时，不要只写当次 bug 的表面结论。先检查这次问题是否落在仓库已有事故模式里，再把对应经验合并写入记忆。

### `packages/vue-element-cui` 的 `vite@8` 构建事故

- 问题现象：构建阶段抛出 `vite:css-post` 的 `path` 类型错误，通常发生在 CSS 资源产物处理时。
- 实际根因：`rollupOptions.output.assetFileNames` 直接返回 `assetInfo.name`，当 CSS 资源名缺失时会返回 `undefined`。
- 有效修复：不要降级依赖、不要改依赖版本，优先给构建配置补齐回退值，例如 `assetInfo.name ?? "assets/[name][extname]"`。
- 记忆重点：未来写事故记录时，必须明确这是“构建配置缺少回退值”的问题，而不是简单写成“vite 版本不兼容”。
- 后续约束：再次遇到同类问题时，先检查构建配置的兜底返回值，不要第一反应去降级工具链。

### `packages/vue-element-cui-nuxt` 的 `nuxt dev` 启动事故

- 问题现象：文档站开发态无法直接启动，报缺失 `.nuxt` 产物、缺失组件库样式产物，或出现 `#app-manifest` 相关错误。
- 实际根因：错误地假设 workspace 依赖已经预构建完成，也错误地假设 `.nuxt` 目录事先存在。
- 有效修复：为 `dev/build` 加 `nuxt prepare` 前置；给 `@eams-monorepo/vue-element-cui` 和 `@eams-monorepo/vue-element-cui/styles` 配源码别名；显式关闭当前模板链不稳定的 `experimental.appManifest`。
- 记忆重点：未来写记忆时，必须点明“文档站开发态直接消费源码”这一约束，而不是只记一条“加个 prepare 就好了”。
- 后续约束：不要把文档站启动建立在组件库 `dist` 已存在这个前提上。

### `packages/vue-element-cui-nuxt` 的文档站客户端 hydration 事故

- 问题现象：暗黑模式无法切换、侧边栏折叠点击无效，这类交互失效不要先入为主归因为样式。
- 实际根因：Nuxt 客户端 hydration 被依赖入口兼容问题打断。首个可信信号是浏览器 console 报错 `dayjs.min.js does not provide an export named 'default'`，后续还会串出 `@braintree/sanitize-url`、`debug`、`mermaid` 的 ESM/CJS 兼容问题。
- 有效修复：保持 `extends: ["shadcn-docs-nuxt"]` 不变；优先在 `nuxt.config.ts` 的 Vite 层做兼容修正，例如 `dayjs -> dayjs/esm/index.js`、`mermaid -> mermaid/dist/mermaid.esm.mjs`、`debug -> ./shims/debug.ts`，并补齐 `vite.optimizeDeps.include`、`vite.resolve.dedupe = ["dayjs"]`、`vite.ssr.noExternal = ["debug"]`；`tailwind.config.js` 只做内容扫描兜底，不把样式当根因。
- 记忆重点：未来写记忆时，要明确“首个可信线索来自 Chrome MCP console，而不是视觉症状本身”。
- 后续约束：排错顺序固定为“先 console 模块错误，再依赖入口，再样式层”。

### `packages/vue-element-cui-nuxt` 的稳定启动基线

- 问题现象：项目明明曾经能跑，后续修改后又被改到无法启动。
- 实际根因：稳定配置被随意改动，尤其是在用户已经确认“当前可运行”之后继续扩散式修改。
- 有效修复：把用户确认过的稳定启动状态记录为基线，包括精简依赖集合、`extends: ["shadcn-docs-nuxt"]`、单语 `zh-CN` i18n、`ogImage.enabled = false`、`icon.clientBundle.scan = true`、`vite.ssr.noExternal` 等最小可用组合。
- 记忆重点：未来写记忆时，除了写“怎么修”，还必须写“哪些配置不要乱动”。
- 后续约束：任何后续排错和优化都要以稳定基线为前提，避免把项目重新改坏。

### `packages/vue-element-cui-nuxt` 的单语文档与 i18n 误用问题

- 历史现象：模板继承链里的 i18n 逻辑曾让 `/components` 页面出现 `Cannot read properties of undefined (reading children)` 之类的 500 错误，也带来过多余的 locale 路径处理。
- 共通根因：单语文档站不该无条件继承真实多语言运行路径。
- 记忆重点：未来写记忆时，要明确区分当次采用的是“compat 覆盖路径”还是“显式单语 `defaultLocale/locales` 路线”，不要把历史上的不同修法混写成一个结论。
- 后续约束：如果文档站本质上是单语站点，记录时必须强调“不要把多语言运行路径当默认前提”。

### `simple-git-hooks` 钩子安装到假 `.git` 目录导致 lint-staged 从未触发

- 问题现象：每次 `git commit` 时 `lint-staged` 和 `commitlint` 均未触发，暂存区文件未被格式化，提交信息未被校验。
- 实际根因：Git 仓库根目录在 `01s-2603-13eams/`（`.git` 在这一层），而 pnpm monorepo 工作区在其子目录 `eams-frontend-monorepo/`。`eams-frontend-monorepo/` 内存在一个假的 `.git` 目录（仅含 `hooks/` 子目录，无 HEAD、config 等），`simple-git-hooks` 在 `postinstall` 时从 monorepo 目录向上查找 `.git`，先命中了这个假目录，于是把钩子安装到了 `eams-frontend-monorepo/.git/hooks/`。但 Git 执行提交时查找的是真正的 `01s-2603-13eams/.git/hooks/`（里面只有 `.sample` 文件），钩子从未被执行。
- 关键线索：`git rev-parse --git-dir` 返回 `01s-2603-13eams/.git`，而 `ls eams-frontend-monorepo/.git/` 只有一个 `hooks/` 子目录且无任何 git 元数据文件，证实这是 `simple-git-hooks` 自行创建的假 `.git`。对比真正的 `.git/hooks/` 目录——里面没有任何非 `.sample` 钩子文件，直接确认钩子装错了位置。
- 有效修复：三步组合修复：(1) 设置 `git config core.hooksPath eams-frontend-monorepo/.git/hooks`，让 Git 从 monorepo 的钩子目录读取钩子；(2) 更新 `simple-git-hooks.mjs`，钩子命令加 `cd eams-frontend-monorepo` 前缀，使 `npx` 能在 monorepo 目录下找到依赖和配置；(3) `commit-msg` 钩子用 `ROOT=$(pwd)` 先保存仓库根绝对路径，cd 后用 `"$ROOT/$1"` 拼出提交信息文件的完整路径（因为 `$1` 是相对于仓库根的路径，cd 后会失效）。
- 验证方式：`git commit --allow-empty -m "test: hook trigger test"` 后看到 lint-staged 输出 `→ No staged files found.`，commitlint 也未拒绝合法信息，确认两个钩子均正常触发。
- 后续约束：当 Git 仓库根与 monorepo 工作区不在同一层级时，必须检查 `git rev-parse --git-dir` 与 `simple-git-hooks` 实际写入钩子的位置是否一致。不要假设 `.git` 目录和 `package.json` 在同一层。删除假 `.git` 无效——`simple-git-hooks` 会重新创建，必须配合 `core.hooksPath` 使用。

### `packages/vue-element-cui-nuxt` 的 dev warning 清理经验

- 历史现象：即使页面可打开，`nuxt dev` 里仍可能残留 i18n、OG Image、Icon、Sass 等 warning。
- 实际根因：这通常不是单点问题，而是多个小兼容问题叠加，例如缺失 `defaultLocale`、同名 composables 与自动导入叠加、未启用却仍调用 `defineOgImageComponent()`、缺失本地 `lucide` 集合、样式仍使用全局 `mix()`。
- 有效修复：显式补齐单语 i18n 配置；避免同名 helper 重复自动导入；`ogImage.enabled = false` 时应通过页面覆盖去掉 `defineOgImageComponent()` 调用，而不是硬开模块；安装 `@iconify-json/lucide`；把 Sass 的 `mix()` 迁移到 `color.mix()`。
- 记忆重点：未来写记忆时，要说明 warning 清理必须基于“单一 fresh dev 进程”的新日志，而不是基于旧日志拼接猜测。
- 后续约束：验证结论时，应优先记录 `fresh dev.stderr` 是否为空、页面 HTTP 是否 200、Chrome console 是否无新增 `warn/error`。

## 写入经验时必须保留的额外信息

如果这次 bug 与仓库已有事故模式相似，写记忆时不要遗漏下面这些额外信息：

- 这次问题是否打破了某个“用户已确认稳定”的基线
- 是否存在“不要乱改”的配置，例如 `extends: ["shadcn-docs-nuxt"]`
- 首个可信信号来自哪里，是终端日志、浏览器 console、网络请求，还是构建输出
- 这次修复属于哪一类：构建配置兜底、依赖入口兼容、模板层覆盖、样式层补齐、还是启动前置准备
- 这次是否存在误导性很强的假象，例如“看起来像样式问题，实际是 hydration”
- 最终验证是否基于 fresh 进程、fresh 日志和 fresh 页面，而不是历史缓存

## 验证证据写法

未来写事故记录时，优先记录可重复验证的证据，而不是模糊措辞。

- 好的写法：`fresh dev.stderr 为空`
- 好的写法：`/components 返回 200`
- 好的写法：`Chrome console 无新的 warn/error`
- 好的写法：`暗黑模式切换恢复，侧边栏折叠恢复`
- 不好的写法：`应该没问题了`
- 不好的写法：`看起来像是好了`

## 不要写成什么

把根级 AI 记忆经验吸收到技能里，不等于把技能写成修复手册。下面这些内容不应该成为这个技能的主体：

- 大段命令执行流水
- 与当前仓库无关的泛化 debug 理论
- 逐条罗列所有试错过程
- 把某一次临时绕过方案包装成永久规则
- 用“必须执行这些命令”代替“应该记录哪些结论”

## 记录流程

1. 先确认 bug 已经理解清楚并且修复完成。
2. 把结果压缩成 4 到 6 条高信号事实。
3. 选对记忆落点。
4. 如果是仓库级经验，就更新根级 AI 记忆文档。
5. 用同样的结论更新 Memorix，并选对记忆类型。
6. 回读一遍文本，删掉瞬时噪音、猜测和低价值命令历史。
7. 如果用户还要求提交 commit，把提交动作交给单独的 git 工作流处理。

## 好记忆的特征

- 解释清楚“为什么会坏”，而不是只写跑了什么命令
- 明确指出第一条可信线索，说明它如何打破错误假设
- 用可复用的方式描述最终修复
- 写出未来 agent 可以重复执行的验证动作
- 让下一次排错明显更短

## 常见错误

- 根因还没确认，就开始写猜测性结论
- 写成很长的 debug 日记，而不是可复用结论
- 仓库级经验写到了错误的位置
- 没把导致绕路的错误假设写出来
- 把修复说明和记忆沉淀混在一起
- 忘了同步本地 MCP 记忆

## 边界

这个技能只负责记忆沉淀和总结。

它不能替代调试、实现、测试和修复工作流。如果 bug 还没修好，先使用合适的调试或实现技能，等结果稳定后再回到这个技能做经验沉淀。
