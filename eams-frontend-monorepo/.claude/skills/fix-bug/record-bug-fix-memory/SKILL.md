---
name: record-bug-fix-memory
description: 当用户要求在 bug 已经定位并修复后，记录排错经验、事故结论、AI 记忆更新、复盘摘要或本地 MCP 记忆时使用。这个技能只负责沉淀“发生了什么、为什么会发生、如何修好、以后要记住什么”，不要把它用于实际修复 bug。
---

# 记录 Bug 修复记忆

---

## 概述

使用这个技能，把已经完成的排错结果沉淀成可复用的长期记忆。

目标是保存根因、有效修复路径、错误假设和验证证据，让后续 agent 不再重复同样的弯路。

核心原则：记录决策链，不记录流水账。

---

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

---

## 前置输入

开始写记忆前，必须能回答下面六个问题：

1. 对用户来说，表面现象是什么？
2. 实际根因是什么？
3. 哪个错误假设或误导信号浪费了时间？
4. 最终是哪一个具体改动修好了问题？
5. 用什么验证证明修复成立？
6. 这条记忆应该写到哪里？

如果有任何一个问题答不上来，先完成排错，不要提前写记忆。

---

## 写到哪里

- 仓库级、可复用的规则：写到根级 `CLAUDE.md`、`AGENTS.md`、`GEMINI.md`
- 跨会话的本地记忆：写到 Memorix，类型用 `gotcha`、`decision` 或 `problem-solution`
- 包级 prompts、plans、reports：只有用户明确要求时才写进去

默认规则：只要这条经验会影响整个仓库里的未来 agent，就优先写入三个根级 AI 记忆文档，不要埋进包级备注里。

---

## 记录什么

每条记忆至少要覆盖这六件事：

1. 问题现象：从用户视角看，哪里坏了
2. 根因：真正出错的地方
3. 关键线索：哪条信号把问题从假象拉回真实根因
4. 有效修复：真正解决问题的改动
5. 验证方式：证明修复成功的证据
6. 后续约束：未来 agent 必须先检查什么、避免什么

---

## 记忆模板

使用简洁、面向未来复用的结构：

- `问题现象：...`
- `根因：...`
- `关键误导点：...`
- `有效修复：...`
- `验证方式：...`
- `后续约束：...`

这些句子应该帮助未来 agent 快速做对事，而不是复述完整排错过程。

---

## 仓库级经验库

当用户要求“补充 AI 记忆”时，不要只写当次 bug 的表面结论。先检查这次问题是否落在仓库已有事故模式里，再把对应经验合并写入记忆。

> **阅读提示**：下面每条事故以 **加粗维度标题 + 独立段落** 排版，便于扫读；同类问题请在对应条目下**增补**，避免重复开新段落。

---

### `packages/vue-element-cui` 的 `vite@8` 构建事故

**问题现象**

- 构建阶段抛出 `vite:css-post` 的 `path` 类型错误，通常发生在 CSS 资源产物处理时。

**实际根因**

- `rollupOptions.output.assetFileNames` 直接返回 `assetInfo.name`，当 CSS 资源名缺失时会返回 `undefined`。

**有效修复**

- 不要降级依赖、不要改依赖版本，优先给构建配置补齐回退值，例如 `assetInfo.name ?? "assets/[name][extname]"`。

**记忆重点**

- 未来写事故记录时，必须明确这是“构建配置缺少回退值”的问题，而不是简单写成“vite 版本不兼容”。

**后续约束**

- 再次遇到同类问题时，先检查构建配置的兜底返回值，不要第一反应去降级工具链。

---

### `packages/vue-element-cui-nuxt` 的 `nuxt dev` 启动事故

**问题现象**

- 文档站开发态无法直接启动，报缺失 `.nuxt` 产物、缺失组件库样式产物，或出现 `#app-manifest` 相关错误。

**实际根因**

- 错误地假设 workspace 依赖已经预构建完成，也错误地假设 `.nuxt` 目录事先存在。

**有效修复**

- 为 `dev/build` 加 `nuxt prepare` 前置；给 `@eams-monorepo/vue-element-cui` 和 `@eams-monorepo/vue-element-cui/styles` 配源码别名；显式关闭当前模板链不稳定的 `experimental.appManifest`。

**记忆重点**

- 未来写记忆时，必须点明“文档站开发态直接消费源码”这一约束，而不是只记一条“加个 prepare 就好了”。

**后续约束**

- 不要把文档站启动建立在组件库 `dist` 已存在这个前提上。

---

### `packages/vue-element-cui-nuxt` 的文档站客户端 hydration 事故

**问题现象**

- 暗黑模式无法切换、侧边栏折叠点击无效，这类交互失效不要先入为主归因为样式。

**实际根因**

- Nuxt 客户端 hydration 被依赖入口兼容问题打断。首个可信信号是浏览器 console 报错 `dayjs.min.js does not provide an export named 'default'`，后续还会串出 `@braintree/sanitize-url`、`debug`、`mermaid` 的 ESM/CJS 兼容问题。

**有效修复**

- 保持 `extends: ["shadcn-docs-nuxt"]` 不变；优先在 `nuxt.config.ts` 的 Vite 层做兼容修正，例如 `dayjs -> dayjs/esm/index.js`、`mermaid -> mermaid/dist/mermaid.esm.mjs`、`debug -> ./shims/debug.ts`，并补齐 `vite.optimizeDeps.include`、`vite.resolve.dedupe = ["dayjs"]`、`vite.ssr.noExternal = ["debug"]`；`tailwind.config.js` 只做内容扫描兜底，不把样式当根因。

**记忆重点**

- 未来写记忆时，要明确“首个可信线索来自 Chrome MCP console，而不是视觉症状本身”。

**后续约束**

- 排错顺序固定为“先 console 模块错误，再依赖入口，再样式层”。

---

### `packages/vue-element-cui-nuxt` 的稳定启动基线

**问题现象**

- 项目明明曾经能跑，后续修改后又被改到无法启动。

**实际根因**

- 稳定配置被随意改动，尤其是在用户已经确认“当前可运行”之后继续扩散式修改。

**有效修复**

- 把用户确认过的稳定启动状态记录为基线，包括精简依赖集合、`extends: ["shadcn-docs-nuxt"]`、单语 `zh-CN` i18n、`ogImage.enabled = false`、`icon.clientBundle.scan = true`、`vite.ssr.noExternal` 等最小可用组合。

**记忆重点**

- 未来写记忆时，除了写“怎么修”，还必须写“哪些配置不要乱动”。

**后续约束**

- 任何后续排错和优化都要以稳定基线为前提，避免把项目重新改坏。

---

### `packages/vue-element-cui-nuxt` 的单语文档与 i18n 误用问题

**历史现象**

- 模板继承链里的 i18n 逻辑曾让 `/components` 页面出现 `Cannot read properties of undefined (reading children)` 之类的 500 错误，也带来过多余的 locale 路径处理。

**共通根因**

- 单语文档站不该无条件继承真实多语言运行路径。

**记忆重点**

- 未来写记忆时，要明确区分当次采用的是“compat 覆盖路径”还是“显式单语 `defaultLocale/locales` 路线”，不要把历史上的不同修法混写成一个结论。

**后续约束**

- 如果文档站本质上是单语站点，记录时必须强调“不要把多语言运行路径当默认前提”。

---

### `simple-git-hooks` 钩子安装到假 `.git` 目录导致 lint-staged 从未触发

**问题现象**

- 每次 `git commit` 时 `lint-staged` 和 `commitlint` 均未触发，暂存区文件未被格式化，提交信息未被校验。

**实际根因**

- Git 仓库根目录在 `01s-2603-13eams/`（`.git` 在这一层），而 pnpm monorepo 工作区在其子目录 `eams-frontend-monorepo/`。`eams-frontend-monorepo/` 内存在一个假的 `.git` 目录（仅含 `hooks/` 子目录，无 HEAD、config 等），`simple-git-hooks` 在 `postinstall` 时从 monorepo 目录向上查找 `.git`，先命中了这个假目录，于是把钩子安装到了 `eams-frontend-monorepo/.git/hooks/`。但 Git 执行提交时查找的是真正的 `01s-2603-13eams/.git/hooks/`（里面只有 `.sample` 文件），钩子从未被执行。

**关键线索**

- `git rev-parse --git-dir` 返回 `01s-2603-13eams/.git`，而 `ls eams-frontend-monorepo/.git/` 只有一个 `hooks/` 子目录且无任何 git 元数据文件，证实这是 `simple-git-hooks` 自行创建的假 `.git`。对比真正的 `.git/hooks/` 目录——里面没有任何非 `.sample` 钩子文件，直接确认钩子装错了位置。

**有效修复**

- 三步组合修复：(1) 设置 `git config core.hooksPath eams-frontend-monorepo/.git/hooks`，让 Git 从 monorepo 的钩子目录读取钩子；(2) 更新 `simple-git-hooks.mjs`，钩子命令加 `cd eams-frontend-monorepo` 前缀，使 `npx` 能在 monorepo 目录下找到依赖和配置；(3) `commit-msg` 钩子用 `ROOT=$(pwd)` 先保存仓库根绝对路径，cd 后用 `"$ROOT/$1"` 拼出提交信息文件的完整路径（因为 `$1` 是相对于仓库根的路径，cd 后会失效）。

**验证方式**

- `git commit --allow-empty -m "test: hook trigger test"` 后看到 lint-staged 输出 `→ No staged files found.`，commitlint 也未拒绝合法信息，确认两个钩子均正常触发。

**后续约束**

- 当 Git 仓库根与 monorepo 工作区不在同一层级时，必须检查 `git rev-parse --git-dir` 与 `simple-git-hooks` 实际写入钩子的位置是否一致。不要假设 `.git` 目录和 `package.json` 在同一层。删除假 `.git` 无效——`simple-git-hooks` 会重新创建，必须配合 `core.hooksPath` 使用。

---

### `packages/vue-element-cui-nuxt` 的 MDC 文档图标丢失事故（prettier 误格式化）

**问题现象**

- 文档站 `/getting-started`、`/components`、`/guidelines`、`/updates` 页面卡片中的图标全部消失，`title:`、`icon:`、`to:` 等 props 变成了纯文本直接渲染在页面上。

**实际根因**

- `prettier` 在格式化 `.md` 文件时，会在 MDC 组件声明行（如 `::card`）与 YAML frontmatter 起始标记（`---`）之间自动插入一个空行。MDC 解析器要求两者紧贴、不得有空行，一旦有空行，`---` 被解析为 `<hr>` 标签，所有 YAML 内容变成段落文本，props 全部失效。

**关键误导点**

- 最初以为是 icon bundle 没有包含对应图标名，或 `SmartIcon` 组件缺失，花时间检查 icon 库配置。应该先看 HTML 源码——HTML 中根本没有 icon 元素，说明 props 从未被解析。

**有效修复**

- (1) 新建 `.prettierignore`，添加 `packages/vue-element-cui-nuxt/content/**/*.md`；(2) 在 `prettier.config.mjs` 的 `overrides` 中为该路径添加 `requirePragma: true` 双重保险；(3) 手动还原被格式化破坏的所有 `::card\n---`（去掉中间空行）。

**验证方式**

- `Invoke-WebRequest http://localhost:3001/getting-started` 返回的 HTML 中包含 `i-lucide:download`、`i-lucide:rocket`、`i-lucide:life-buoy`、`i-lucide:arrow-left-right` 四个 icon class。

**后续约束**

- MDC 内容文件永远不能被 prettier 格式化；`.prettierignore` 中必须覆盖所有 nuxt content 目录；排查图标消失时，先看 HTML 源码中是否存在 icon 元素，而不是先查图标库配置。

---

### `packages/vue-element-cui-nuxt` 的 `::demo-playground` 渲染失败事故（MDC 容器语法错误，2026-03）

**问题现象**

- 多个组件文档页出现 `::demo-playground`、`title:`、`#preview`、`#code` 等原始文本直接渲染；浏览器 console 出现 `Hydration completed but contains mismatches` 与大量 hydration node mismatch 警告。

**实际根因**

- `demo-playground` 容器不是按 MDC 语法书写，典型错误包括：(1) 写成 `## ::demo-playground`（被当成标题）；(2) frontmatter 顺序错误（`title/description` 在前，`---` 在后）；(3) 容器开闭符不匹配。

**关键误导点**

- 容易先怀疑 `DemoPlayground` 组件实现或 Nuxt 依赖兼容问题。实际上首个高价值线索是“正文出现 marker 裸文本 + hydration mismatch 同时出现”，应优先回查 markdown 容器语法。

**有效修复**

- 将所有示例块统一为 `::demo-playground` + 紧跟 `---` frontmatter + `::` 闭合，并保持 `#preview` 与 `#code` 在容器内部；批量修改后抽样回归多个路由。

**验证方式**

- Chrome MCP 中满足三点即通过：(1) console 无 hydration mismatch 报错；(2) 页面正文不再出现 `::demo-playground/#preview/#code/title:` 裸文本；(3) demo 标题和描述（来自 frontmatter）正常渲染。

**后续约束**

- 后续新增 demo 文档时，禁止使用 `## ::demo-playground`；禁止打乱 frontmatter 顺序；批量替换脚本只允许改目标容器片段，必须先抽样再全量，避免误改其他 `:::` 容器。

---

### `packages/vue-element-cui-nuxt` 的 Nuxt SSR i18n 版本冲突事故（pnpm 依赖提升）

**问题现象**

- `nuxt dev` 启动后所有页面返回 500 错误，错误信息为 `Error: (0, __vite_ssr_import_0__.registerMessageResolver) is not a function`。

**实际根因**

- `@intlify/core-base` 存在多个版本（9.1.9 和 11.x）同时存在于依赖树中。`shamefully-hoist=false` 使 pnpm 按隔离模式管理依赖，Vite SSR 解析时命中了旧版 9.1.9（缺少 `registerMessageResolver`），而非 `vue-i18n@11.x` 所需的 11.x 版本。升级 `shamefully-hoist=true` 后，又出现旧版 `sass@1.26.8` 被提升，导致 `sass.initAsyncCompiler is not a function`。

**关键误导点**

- 多次尝试 `vite.ssr.noExternal`、`vite.resolve.alias`、`vite.resolve.dedupe` 等 nuxt.config.ts 配置，全部是无效方向；正确方向是强制 pnpm 在整个 workspace 中使用单一版本，而不是在 Vite 层绕过。

**有效修复**

- (1) 在 `.npmrc` 中改为 `shamefully-hoist=true`；(2) 在 `pnpm-workspace.yaml` 的 `overrides` 中添加 `"@intlify/core-base": "11.3.0"`、`"@intlify/shared": "11.3.0"`、`"sass": "^1.98.0"`；(3) 根 `package.json` 中升级 `vue-i18n` 到 `"11.3.0"`；(4) 在 Cursor 外部的终端运行 `pnpm install` 使 overrides 生效。

**验证方式**

- Nuxt dev server 启动无 500 错误，全部页面返回 200 OK；`node_modules/@intlify/core-base/package.json` 中 `version` 字段为 `11.3.0`。

**后续约束**

- 遇到 Nuxt SSR `is not a function` 错误，先用 `pnpm why <package>` 排查是否存在多版本实例，再通过 `pnpm-workspace.yaml` 的 `overrides` 强制单一版本；不要第一反应去改 `nuxt.config.ts` 的 Vite 层配置。

---

### Cursor IDE 持有 `.node` 原生文件锁导致 `pnpm install` 失败

**问题现象**

- 在 Cursor 内置终端运行 `pnpm install` 时，报 `EPERM: operation not permitted, unlink 'node_modules/@oxc-parser/binding-win32-x64-msvc/parser.win32-x64-msvc.node'`，安装回滚，依赖变更无法生效。

**实际根因**

- Cursor IDE 的 TypeScript 语言服务进程（tsserver）持有 `@oxc-parser` 原生 `.node` 文件的 Windows 文件锁，pnpm 无法删除该文件来完成依赖更新，导致整个安装事务回滚。

**有效修复**

- 在 Cursor 外部的终端（如 PowerShell、系统 CMD）中运行 `pnpm install`，绕开 IDE 文件锁。

**验证方式**

- 外部终端 `pnpm install` 结束后无 EPERM 错误，`pnpm-lock.yaml` 正确更新。

**后续约束**

- 在该 monorepo 中更新任何涉及原生 Node.js addon 的依赖（如 `@oxc-parser`、`esbuild`、`@swc/*`）时，必须在 Cursor 外的终端运行 `pnpm install`；Cursor 内置终端只用于读取日志，不用于执行 install。

---

### 仓库根 `.gitattributes` 与 `eol=lf` 导致的 CRLF/LF「幽灵」差异（2026-03）

**问题现象**

- 例如 `eams-frontend-monorepo/README.md` 在多个 `f1-*` 子分支上**永远显示已修改（M）**，切换分支也不消失，阻塞合并；`git diff` 往往只显示整文件「换行符变化」而无实质内容差异。

**实际根因**

- 根目录 `.gitattributes` 已规定文本文件 `eol=lf`，Git 检出时把工作区写成 LF，但**各分支索引里该文件的历史 blob 仍是 CRLF**；索引与工作区行尾策略不一致，形成持续脏状态。

**关键误导点**

- 误当成「单个分支未保存」或「IDE 捣乱」；只在一条分支上改文件不够，**每个仍含 CRLF 索引的分支都要 `git add --renormalize` 后提交**，否则切回即复现。

**有效修复**

- 对路径执行 `git add --renormalize <path>`（或按需全库 `git add --renormalize .`）并提交，使对象库与 `.gitattributes` 一致；在 monorepo `eams-frontend-monorepo/.editorconfig` 的 `[*]` 下增加 `end_of_line = lf`，减少 Windows 下新文件默认 CRLF。将各子分支改动收拢到 `f1` 时，合并提交说明须过 commitlint，使用 **`chore: merge <branch> into f1`** 等形式，避免使用非法 type（如 `merge:`）导致合并不完成。

**验证方式**

- 在多条 `f1-*` 分支上 `git checkout` 后 `git status` 无该文件；`git diff` 对该路径为空。

**后续约束**

- 引入或收紧 `eol=lf` 后出现「永远 M 的文本文件」，优先核对 **`git diff` 是否仅为 CRLF↔LF** 与 **`git add --renormalize`**，不要先大范围改业务代码；批量合并子分支进主干前确认提交信息符合本仓库 Conventional Commits 规则。

---

### `packages/vue-element-cui-nuxt` 的 dev warning 清理经验

**历史现象**

- 即使页面可打开，`nuxt dev` 里仍可能残留 i18n、OG Image、Icon、Sass 等 warning。

**实际根因**

- 这通常不是单点问题，而是多个小兼容问题叠加，例如缺失 `defaultLocale`、同名 composables 与自动导入叠加、未启用却仍调用 `defineOgImageComponent()`、缺失本地 `lucide` 集合、样式仍使用全局 `mix()`。

**有效修复**

- 显式补齐单语 i18n 配置；避免同名 helper 重复自动导入；`ogImage.enabled = false` 时应通过页面覆盖去掉 `defineOgImageComponent()` 调用，而不是硬开模块；安装 `@iconify-json/lucide`；把 Sass 的 `mix()` 迁移到 `color.mix()`。

**记忆重点**

- 未来写记忆时，要说明 warning 清理必须基于“单一 fresh dev 进程”的新日志，而不是基于旧日志拼接猜测。

**后续约束**

- 验证结论时，应优先记录 `fresh dev.stderr` 是否为空、页面 HTTP 是否 200、Chrome console 是否无新增 `warn/error`。

---

### `packages/vue-element-cui-nuxt` 的 Windows PowerShell 构建假卡死与 Nitro trace 事故（2026-03）

**问题现象**

- `pnpm --filter @eams-monorepo/vue-element-cui-nuxt build` 长期停在 `Building Nuxt Nitro server (preset: node-server)`；多次超时重跑后，看起来像是“越跑越卡、彻底卡死”。

**实际根因**

- 有两层原因叠加。第一层是真卡点：Nitro node-server 出包阶段默认 `externals.trace` 会触发 `nodeFileTrace`，在当前文档站 + pnpm workspace + Windows 环境下持续消耗高 CPU 和高内存，构建长时间卡在 Nitro 收尾。第二层是假象放大：PowerShell 下超时终止、手动中断，或 `Start-Process` 后台运行 `pnpm -> cmd -> node -> nuxt build` 时，外层命令结束不代表内层子进程树退出，旧构建链会残留并和新构建叠加。

**关键误导点**

- 日志停在同一行，不等于进程已经空转；如果不先清理残留子进程，后续 `Get-Process`、日志和产物观察会把旧进程噪音误判成当前命令的状态。

**关键线索**

- 单进程复现时，`.nuxt/dist/server/server.mjs` 已生成，但 `.output/server` 仍为空，说明 Vite SSR 已完成、卡点在 Nitro 收尾；同时 `nuxt.mjs build` 的工作集可涨到 2GB 以上，CPU 仍持续增加，符合 `nitropack` 的 `nodeFileTrace` tracing 阶段特征。

**有效修复**

- 先按命令行特征清理旧的 `pnpm -> cmd -> node` 构建链，只保留一条单独进程复现；然后在 `packages/vue-element-cui-nuxt/nuxt.config.ts` 中显式设置 `nitro.externals.trace = false`，绕开当前环境下的 tracing 卡点。

**验证方式**

- 单进程执行 `pnpm --filter @eams-monorepo/vue-element-cui-nuxt exec nuxi build --logLevel=verbose`，应生成 `.output/server/index.mjs` 并打印 `Build complete!`；同时确认不再残留目标构建进程链。

**后续约束**

- 以后在 Windows PowerShell 下复现“构建卡死”时，先确认是否有旧子进程残留，再判断当前命令是否真的卡住；不要把多条残留构建链叠加后的现象直接归因到当前修改。

---

### PowerShell Git 批量合并脚本事故

**范围**：`eams-frontend-monorepo/scripts`  
**时间**：2026-03  
**关键词**：UTF-8 BOM、管道误用、git 钩子、`stderr`、`$LASTEXITCODE`、`--no-ff`

#### 问题现象

**假语法错误**

- 含中文的 `.ps1` 在 Windows PowerShell 5 下报「字符串缺少终止符」「意外标记 `}`」等，实为编码解析问题，非逻辑写错。

**误报「冲突」与 `merge --abort` 失败**

- `git merge origin/f1` 实际已成功，脚本却进入 `catch`，提示「冲突或失败」。
- 消息里夹杂钩子输出，例如 `ℹ 输出 N 个暂存区文件路径`、ANSI 颜色码。
- 随后执行 `git merge --abort` 报 `fatal: There is no merge to abort`，因 `MERGE_HEAD` 已不存在。

**推送节奏误解**

- 误以为「合并成功却未推远程」；需与产品对齐：末尾一次 `push` 还是每步 `push`。

**历史图异常膨胀**

- 批量合并脚本长期使用 `git merge --no-ff`，即使能快进也会强制新增合并节点。
- 结果是分支图出现大量额外 merge commit，阅读和追溯变困难，且掩盖真实冲突点。

#### 实际根因

**编码与 PS5**

- **无 BOM 的 UTF-8** 被 PS5 按系统代码页读，中文字节破坏引号闭合。

**`$ErrorActionPreference`、管道与钩子 `stderr`**

- 脚本顶部 **`$ErrorActionPreference = "Stop"`** 与 **`git merge ... 2>&1 | ForEach-Object { ... }`** 叠加使用。
- 合并完成后 **post-merge** 等钩子仍可能向 **stderr** 写信息。
- 管道把 `stderr` 并入后，PowerShell 易将 native 的 `stderr` 当成**终止错误**，直接进入 `catch`；此时合并已结束，`MERGE_HEAD` 已清除，`merge --abort` 无合并可中止。

**管道与退出码**

- **`$LASTEXITCODE`** 在管道后不能可靠代表 `git merge` 本身，与 `git push` 同理。

**合并策略配置不当**

- 在批量同步场景默认启用 `--no-ff`，属于策略滥用。
- 该配置把「保留显式 merge 节点」从例外变成常态，导致提交图噪音过高。

#### 关键误导点

- 把 `catch` 里的文字当成真实合并冲突。
- 把 `merge --abort` 的 fatal 当成仓库损坏。
- 应先核对 **`MERGE_HEAD` 是否存在**、是否已产生合并提交；若合并已成功，多为误报。

#### 有效修复

**脚本编码**

- 保存为 **UTF-8 with BOM**；编辑器保存后若 BOM 丢失，需重新写入。

**调用 git 的方式**

- **不要**用管道包裹 `git merge` / `git push`。
- 直接执行 `git ...`，再用 **`if ($LASTEXITCODE -ne 0)`** 判断成败。

**远程更新节奏**

- 若要求远程 **每步** 可见：在 `merge-all-branches-to-f1.ps1` 里**每次**合并成功后执行 `git push origin f1`。
- 与 `merge-f1-to-all-branches.ps1`「每子分支合并后即 push」的策略对齐。

**合并策略回归默认**

- 从脚本中移除 `--no-ff`，恢复 `git merge --no-edit` 默认行为。
- 让 Git 在可快进时直接快进，只有确实分叉时才产生合并节点。

#### 验证方式

- `Parser::ParseFile` 对 `.ps1` 无语法错误。
- 实际跑通：合并成功分支能正常 `git push`。
- 不再出现「合并成功却执行 abort」。
- 子分支上 `git status` 无意外冲突状态。

#### 后续约束

**编码与 git 调用**

- 本仓库 **PowerShell + git** 自动化默认 **UTF-8 BOM**。
- **禁止**对 `git merge` / `git push` 使用 `2>&1 |` 管道；与脚本内「push 无管道」注释一致。
- 排错时若见钩子相关 `stderr` 文案，优先怀疑 **Stop + 管道**，而非真实合并失败。
- 批量同步脚本默认使用普通 merge 行为，**禁止滥用 `--no-ff`**；若业务明确要求「绝不新增合并节点」，应改为 `--ff-only` 并接受失败即中止。

**经验落点**

- 新增同类说明时**不要**在 `.cursor/skills` 另立平行 SKILL，应把事故模式**合并进本技能**的仓库级经验库。

---

## 写入经验时必须保留的额外信息

如果这次 bug 与仓库已有事故模式相似，写记忆时不要遗漏下面这些额外信息：

- 这次问题是否打破了某个“用户已确认稳定”的基线
- 是否存在“不要乱改”的配置，例如 `extends: ["shadcn-docs-nuxt"]`
- 首个可信信号来自哪里，是终端日志、浏览器 console、网络请求，还是构建输出
- 这次修复属于哪一类：构建配置兜底、依赖入口兼容、模板层覆盖、样式层补齐、还是启动前置准备
- 这次是否存在误导性很强的假象，例如“看起来像样式问题，实际是 hydration”
- 最终验证是否基于 fresh 进程、fresh 日志和 fresh 页面，而不是历史缓存

---

## 验证证据写法

未来写事故记录时，优先记录可重复验证的证据，而不是模糊措辞。

### 推荐的证据表述

- `fresh dev.stderr 为空`
- `/components` 返回 200
- `Chrome console` 无新的 warn/error
- 暗黑模式切换恢复，侧边栏折叠恢复

### 不推荐的模糊表述

- 「应该没问题了」
- 「看起来像是好了」

---

## 不要写成什么

把根级 AI 记忆经验吸收到技能里，不等于把技能写成修复手册。下面这些内容不应该成为这个技能的主体：

- 大段命令执行流水
- 与当前仓库无关的泛化 debug 理论
- 逐条罗列所有试错过程
- 把某一次临时绕过方案包装成永久规则
- 用“必须执行这些命令”代替“应该记录哪些结论”

---

## 记录流程

1. 先确认 bug 已经理解清楚并且修复完成。
2. 把结果压缩成 4 到 6 条高信号事实。
3. 选对记忆落点。
4. 如果是仓库级经验，就更新根级 AI 记忆文档。
5. 用同样的结论更新 Memorix，并选对记忆类型。
6. 回读一遍文本，删掉瞬时噪音、猜测和低价值命令历史。
7. 如果用户还要求提交 commit，把提交动作交给单独的 git 工作流处理。

---

## 好记忆的特征

- 解释清楚“为什么会坏”，而不是只写跑了什么命令
- 明确指出第一条可信线索，说明它如何打破错误假设
- 用可复用的方式描述最终修复
- 写出未来 agent 可以重复执行的验证动作
- 让下一次排错明显更短

---

## 常见错误

- 根因还没确认，就开始写猜测性结论
- 写成很长的 debug 日记，而不是可复用结论
- 仓库级经验写到了错误的位置
- 没把导致绕路的错误假设写出来
- 把修复说明和记忆沉淀混在一起
- 忘了同步本地 MCP 记忆

---

## 边界

这个技能只负责记忆沉淀和总结。

它不能替代调试、实现、测试和修复工作流。如果 bug 还没修好，先使用合适的调试或实现技能，等结果稳定后再回到这个技能做经验沉淀。

---

## 额外易错点：集成改动不要删减原注释和组件说明信息

**问题现象**

- 为了接入新工具或调整初始化顺序，直接整文件重写入口文件或组件文件，导致原有注释、说明文字、命名语义和组件传达的信息被一起抹掉。

**实际根因**

- 把“功能接入”误当成“允许覆盖原文件表达层”，只关注代码是否还能运行，没有把注释、说明文案、结构命名视为现有实现的一部分。

**关键误导点**

- 表面上只是恢复 import 顺序、插件顺序或模板结构，容易误以为“逻辑等价就没问题”；但对本仓库来说，原注释和组件说明本身就是约定和上下文，不是可随手丢弃的噪音。

**有效修复**

- 优先做最小补丁式修改，保留原注释、原有说明文本和原组件表达；如果必须重写整段内容，先回读基线文件，把原注释和说明信息一并迁移回来，再补充新增集成说明。

**验证方式**

- 对比修改前后的目标文件，确认原注释块、原说明文本和原组件语义仍在；不能只验证运行通过，还要验证信息表达没有缩水。

**后续约束**

- 后续在 `main.ts`、sample 页面、组件 README、组件入口文件里接入工具或调整结构时，不要再用覆盖式重写替代局部修改；不要删减掉注释，不要损耗原本的组件传达的信息。
