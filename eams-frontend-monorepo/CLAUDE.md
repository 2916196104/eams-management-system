# EAMS 前端单仓架构项目

本项目是 EAMS（企业资产管理系统）的前端单仓架构项目。

## 本项目的技能表

- `record-bug-fix-memory`
  - 路径：`.claude/skills/fix-bug/record-bug-fix-memory/SKILL.md`
  - 用途：在 bug 已经定位并修复后，记录事故结论、排错经验、AI 记忆更新、复盘摘要和本地 MCP 记忆。
  - 触发时机：当用户要求“记录经验教训”“补充 AI 记忆”“写事故记录”“同步本地 MCP 记忆”时，必须使用；当主代理完成错误处理后，也应主动参考并补充这个技能。
  - 参考作用：后续处理错误时，应先把这个技能作为历史事故模式、稳定基线、验证证据写法的参考来源之一。
  - 约束：这个技能只负责记忆沉淀和经验总结，不承担具体修复职责；解决错误后，应主动把新增的根因、关键误导点、有效修复、验证方式和后续约束补充回这个技能。

## 2. 对话沟通术语表

在我和你沟通时，我会使用以下术语，便于你理解。

### 2.1. 全局术语

在任何沟通下，这些术语都生效。

- `后台项目`： 即 `apps\eams-frontend\package.json` 指代的 vue3 后台项目。
- `教师端项目`： 即 `apps\eams-fronttea\package.json` 指代的 uniapp 移动端项目。
- `学生端项目`： 即 `apps\eams-frontstu\package.json` 指代的 uniapp 移动端项目。
- `组件库`： 即 `packages\vue-element-cui\package.json` 这款二次封装 element-plus 的组件库。目前主要服务于`后台项目`。
- `组件库文档`： 即 `packages\vue-element-cui-nuxt\package.json` 这款使用 `shadcn-docs-nuxt` 模板封装的组件库文档站点。
- `旧组件库`： 即 `old\vue-element-cui\package.json` 这款用 vue-cli 制作的老旧组件库。在本 monorepo 内只作为被迁移的对象，不实际参与使用。

## 主动问询实施细节

在我与你沟通并要求你具体实施更改时，难免会遇到很多模糊不清的事情。

请你**深度思考**这些`遗漏点`，`缺漏点`，和`冲突相悖点`，**并主动的向我问询这些你不清楚的实施细节**。请主动使用 claude code 内置的 `AskUserQuestion` 工具，将你不清楚的内容设计成一些列问题，并询问我，向我索要细节，或着与我协作沟通。

我会与你共同补充细化实现细节。我们会先迭代出一轮完整完善的实施清单，然后再由你亲自落实实施下去。

## 编写测试用例规范

1. 请你使用 vitest 的 `import { test, describe } from "vitest";` 来编写。我希望测试用例格式为 describe 和 test。
2. 测试用例的文件格式为 `*.test.ts` 。
3. 测试用例的目录一般情况下为 `**/tests/` ，`**/src/tests/` 格式。
4. 在对应 monorepo 的 tests 目录内，编写测试用例。如果你无法独立识别清楚到底在那个具体的 monorepo 子包内编写测试用例，请直接咨询我应该在那个目录下编写测试用例。

## 报告编写规范

在大多数情况下，你的更改是**不需要**编写任何说明报告的。但是每当你需要编写报告时，请你首先遵循以下要求：

- 报告地址： 默认在 `docs\reports` 文件夹内编写报告。
- 报告文件格式： `*.md` 通常是 markdown 文件格式。
- 报告文件名称命名要求：
  1. 前缀以日期命名。包括年月日。日期格式 `YYYY-MM-DD` 。
  2. 用小写英文加短横杠的方式命名。
- 报告的一级标题： 必须是日期`YYYY-MM-DD`+报告名的格式。
  - 好的例子： `2025-12-09 修复 @ruan-cat/commitlint-config 包的 negation pattern 处理错误` 。前缀包含有 `YYYY-MM-DD` 日期。
  - 糟糕的例子： `构建与 fdir/Vite 事件复盘报告` 。前缀缺少 `YYYY-MM-DD` 日期。
- 报告日志信息的代码块语言： 一律用 `log` 作为日志信息的代码块语言。如下例子：

  ````markdown
  日志如下：

  ```log
  日志信息……
  ```
  ````

- 报告语言： 默认用简体中文。

## 生成发版日志的操作规范

在你生成发版日志时，按照以下规范来完成：

1. 新建文件： 运行命令 `pnpm dlx @changesets/cli add --empty` ，该命令会在 `.changeset` 目录下，新建一个空的 markdown 文件，这个文件就是你要写入的发版日志。
2. 发版日志文件重命名： 这个命令会新建一个随机名称的发版日志文件，请你按照报告的规格，换成日期加语义化更新内容的名称。比如 `2025-12-15-add-pnpm-workspace-yaml.md` 就是有意义的命名。
3. yaml 区域写入 changeset 规格的发版信息： 写入发版包名，和`发版标签`的等级。
4. 写入更新日志： 在正文内编写更新日志。
5. 编写更新日志正文的行文规范：
   - 禁止使用任何等级的 markdown 标题： 编写任何`发版标签`的更新日志时，不允许使用任何等级的 markdown 标题，比如一级标题、二级标题等。这会影响自动合并的 `CHANGELOG.md` 文档的美观度。必须使用 markdown 的序号语法。
   - major： 详细，清晰。说明清楚 major 版本的重大变更。
   - minor： 用有序序号，简明扼要的说明清楚更新日志即可。
   - patch： 用有序序号，简明扼要的说明清楚更新日志即可。

## 术语说明

在我和你沟通时，我会使用以下术语，便于你理解。

### 发版日志相关术语

- `生成更新日志` ： 指的是在 `.changeset` 目录内，编写面向 changeset 的更新日志文件。其`发版标签`分为 `major` `minor` `patch` 这三个档次。如果我在要求你生成更新日志时，没有说明清楚`发版标签`具体发版到那个等级，请及时询问我。要求我给你说明清楚。
- `生成发版日志` ： `生成更新日志` 的别名，是同一个意思。

## 沟通协作要求

### `计划模式`

在`计划模式`下，请你按照以下方式与我协作：

1. 你不需要考虑任何向后兼容的设计，允许你做出破坏性的写法。请先设计一个合适的方案，和我沟通后再修改实施。
2. 如果有疑惑，请询问我。
3. 完成任务后，请告知我你做了那些破坏性变更。

请注意，在绝大多数情况下，我不会要求你以这种 `计划模式` 来和我协作。

## 终端操作注意事项（防卡住）

在 Windows PowerShell 环境下执行终端命令时，必须遵循以下规则，避免命令卡住浪费时间：

### 1. 避免超长单行命令

命令行参数过多（超过 200 字符）时，PowerShell 可能会挂起无响应。

- **拆分命令**：每次传入 2~3 个文件路径，不要一次传入 5 个以上。
- **使用通配符**：优先用 `git add scripts/.../src/*.ts` 替代逐个列举文件路径。

### 2. 优先使用 `pnpm run` 而非 `npx`

`npx` 在 Windows 上被终止时，会触发 `Terminate batch job (Y/N)?` 交互提示导致卡住。

- **优先使用** `pnpm run build` 替代 `npx tsdown`。
- **优先使用** `pnpm run test` 替代 `npx vitest run`。

### 3. 及时止损，不要反复轮询

当命令可能卡住时：

1. 第 1 次状态检查等待 10~15 秒。
2. 如果无输出且仍在运行 → **立即终止**，用新命令重试。
3. **不要超过 2 次**状态检查仍无进展还继续等待。

### 4. 合理的等待超时设置

|         命令类型         | 建议等待时长 |
| :----------------------: | :----------: |
| `git add / status / log` |   5~10 秒    |
|       `git commit`       |    10 秒     |
| `pnpm run build / test`  |    30 秒     |
|      `pnpm install`      |    60 秒     |

### 5. 清理残留子进程，避免“假卡死”

在 Windows PowerShell 下，`pnpm build/test` 被超时终止、手动中断，或通过 `Start-Process`/重定向日志后台运行时，外层命令结束并不代表内层 `cmd.exe`、`node.exe` 子进程树也结束。

- 症状：同一个构建命令看起来“越来越卡”，日志停在某一行不动，但任务管理器里其实残留了多条旧的 `pnpm -> cmd -> node` 构建链。
- 处理原则：重跑前先按命令行特征清理旧进程，只保留一条新的单独构建链；优先记录 PID 并围绕单个 PID 观察，不要并发开多轮复现。
- 验证方式：确认只剩一条目标构建进程链，再看日志、CPU 和产物目录，避免把旧进程噪音误判成当前命令卡死。

## 简单任务的高效执行原则

当用户交代的任务范围明确清晰时，必须**直接行动**，禁止进行不必要的大范围侦察。

### 1. 判断任务规模，选择正确的行动姿态

| 任务信号                         | 正确行动               |
| :------------------------------- | :--------------------- |
| 用户通过 `@文件` 明确了操作范围  | 直接读该文件，立即动手 |
| 用户说"帮我改这个"、"写个日志"   | 行动优先，缺什么补什么 |
| 用户涉及多包架构改动、新功能设计 | 先侦察，再行动         |

**核心原则**：用户提供的上下文（@文件引用、对话内容、当前打开文件）就是最直接的线索，优先使用，不要用命令重新发现已知信息。

### 2. 禁止行为清单

以下行为在**简单任务**（单文件改动、写 changeset、写提交信息等）中是被禁止的：

- 禁止连续执行超过 3 次 `git log` 来"了解全貌"
- 禁止在明确知道目标文件的情况下，仍去扫描整个项目目录
- 禁止把"读遍所有相关文档"当作行动前置条件
- 禁止在用户已给出 @文件 的情况下，用命令重新搜索文件位置

### 3. 对用户纠偏提示立即响应

当用户发出以下信号时，必须**立即停止对当前路径的死磕**，回归最小行动路径：

- "太复杂了"
- "不要反复查询"
- "直接做就行"
- "按要求做即可"

正确反应：停止当前侦察行为 → 明确当前已知信息 → 直接执行最核心的操作步骤。

### 4. 简单任务的标准执行路径

以"为某文件修改编写更新日志"为例，正确路径只有 3 步：

1. 读目标文件，理解改了什么
2. 执行 `pnpm dlx @changesets/cli add --empty`，重命名文件，写入内容
3. 提交

不需要查 git log，不需要扫描全部 tags，不需要对比所有包的版本号。

## 获取技术栈对应的上下文

在处理特定技术栈相关的问题时，你应该主动获取对应的上下文文档和最佳实践。

### claude code skill

- 编写语法与格式： https://code.claude.com/docs/zh-CN/skills
- 最佳实践： https://platform.claude.com/docs/zh-CN/agents-and-tools/agent-skills/best-practices
- 规范文档： https://agentskills.io/home

## 项目概述

这是一个基于 pnpm workspace 的 monorepo 项目，包含多个前端应用和共享包。

## AI 记忆补充

- `packages/vue-element-cui` 在 `vite@8` 下出现过构建事故：`rollupOptions.output.assetFileNames` 直接返回 `assetInfo.name`，当 CSS 资源名缺失时会返回 `undefined`，进而触发 `vite:css-post` 的 `path` 类型错误。处理原则：不降级依赖，不改依赖版本，优先补齐构建配置回退值，例如返回 `assetInfo.name ?? "assets/[name][extname]"`。
- `packages/vue-element-cui-nuxt` 在 `nuxt dev` 下出现过启动事故：不能假设 workspace 依赖包已经先构建完，也不能假设 `.nuxt` 目录已提前存在。处理原则：为 `dev/build` 增加 `nuxt prepare` 前置，给 `@eams-monorepo/vue-element-cui` 和 `@eams-monorepo/vue-element-cui/styles` 配源码别名，并显式关闭当前模板链不稳定的 `experimental.appManifest`。这样做是为了让文档站开发态直接消费源码，避免因缺失 `.nuxt` 产物、缺失组件库 `dist` 样式或 `#app-manifest` 解析失败而再次启动报错。
- `packages/vue-element-cui-nuxt` 在文档站交互上出现过一次客户端事故：暗黑模式无法切换、侧边栏折叠按钮点击无效，不要先入为主地归因为样式问题。根因是 Nuxt 开发态客户端 hydration 被依赖入口兼容问题打断，首个明确信号是浏览器报错 `dayjs.min.js does not provide an export named 'default'`，后续还会串出 `@braintree/sanitize-url`、`debug`、`mermaid` 的 ESM/CJS 兼容错误。处理原则：保持 `extends: ["shadcn-docs-nuxt"]` 不变，优先在 `packages/vue-element-cui-nuxt/nuxt.config.ts` 的 Vite 层做兼容修正，包括将 `dayjs` 指向 `dayjs/esm/index.js`、将 `mermaid` 指向 `mermaid/dist/mermaid.esm.mjs`、将 `debug` 指向本地 `./shims/debug.ts`，并补齐 `vite.optimizeDeps.include`、`vite.resolve.dedupe = ["dayjs"]`、`vite.ssr.noExternal = ["debug"]`；样式层只做兜底，`tailwind.config.js` 必须覆盖 `shadcn-docs-nuxt` 的内容扫描路径。排错顺序固定为：先用 Chrome MCP 看 console 模块错误，再修依赖入口，最后再看 Tailwind 或主题样式。
- `simple-git-hooks` 钩子安装位置事故：Git 仓库根在 `01s-2603-13eams/`，monorepo 工作区在其子目录 `eams-frontend-monorepo/`。`simple-git-hooks` 在 `postinstall` 时向上查找 `.git`，会命中 monorepo 内的假 `.git` 目录（仅含 `hooks/`），把钩子装到错误位置，导致 lint-staged 和 commitlint 从未触发。处理原则：(1) 设置 `git config core.hooksPath eams-frontend-monorepo/.git/hooks`；(2) `simple-git-hooks.mjs` 钩子命令加 `cd eams-frontend-monorepo` 前缀；(3) `commit-msg` 钩子用 `ROOT=$(pwd)` 先保存绝对路径再 cd。删除假 `.git` 无效，`simple-git-hooks` 会重建。排查时先用 `git rev-parse --git-dir` 确认真正的 `.git` 位置。
- `packages/vue-element-cui-nuxt` 文档站 MDC 图标丢失事故（2026-03）：prettier 格式化 `.md` 文件时，在 `::card` 和 `---` 之间插入空行，导致 YAML frontmatter 解析失败，`icon`/`title`/`to` 等 props 变成纯文本。处理原则：在 `.prettierignore` 中排除 `packages/vue-element-cui-nuxt/content/**/*.md`；`prettier.config.mjs` 的 `overrides` 中添加 `requirePragma: true` 双重保险。排查时先看 HTML 源码有无 icon 元素，而不是先查图标库配置。
- `packages/vue-element-cui-nuxt` 文档站 `::demo-playground` 渲染事故（2026-03）：把容器写成 `## ::demo-playground`（误当标题），或把 frontmatter 写成“`title/description` 在前、`---` 在后”，会导致 demo props 失效并触发 hydration mismatch，页面出现 `::demo-playground`、`#preview`、`#code`、`title:` 裸文本。处理原则：统一使用 `::demo-playground` + 紧跟 `---` frontmatter + 对应 `::` 闭合；批量修复后必须用 Chrome MCP 同时检查 console（无 hydration 报错）和页面正文（无裸 marker 文本）。
- `packages/vue-element-cui-nuxt` Nuxt SSR `registerMessageResolver is not a function` 事故（2026-03）：`@intlify/core-base` 多版本共存（9.1.9 与 11.x）+ `shamefully-hoist=false` 导致 Vite SSR 命中旧版。处理原则：先用 `pnpm why` 确认多版本，再在 `pnpm-workspace.yaml` 的 `overrides` 中强制单一版本（`@intlify/core-base`、`@intlify/shared`、`sass`）；不要第一反应改 nuxt.config.ts 的 Vite 层配置。
- Cursor IDE 内置终端 `pnpm install` 失败事故（EPERM，2026-03）：Cursor tsserver 持有 `@oxc-parser` 等原生 `.node` 文件锁，pnpm 无法删除文件，安装回滚。处理原则：涉及原生 addon 的依赖更新（`@oxc-parser`、`esbuild`、`@swc/*`），必须在 Cursor 外的外部终端运行 `pnpm install`。
- 仓库根 `.gitattributes` 已设 `eol=lf` 时，若索引中仍是历史 CRLF（如 `eams-frontend-monorepo/README.md`），会在多分支上反复出现「幽灵」修改、阻塞合并。处理原则：用 `git add --renormalize <path>` 提交以统一对象库；`eams-frontend-monorepo/.editorconfig` 补 `end_of_line = lf`；合并子分支进 `f1` 时合并说明须符合 commitlint（例如 `chore: merge <branch> into f1`）。详见 `.claude/skills/fix-bug/record-bug-fix-memory/SKILL.md` 对应条目。
- `packages/vue-element-cui-nuxt` 在 Windows PowerShell 下的 `nuxt build` 卡死事故（2026-03）：表面现象是构建长期停在 `Building Nuxt Nitro server (preset: node-server)`，而且多次重跑越看越像“彻底卡死”。实际根因分两层：(1) Nitro node-server 出包阶段默认的 `externals.trace` 会触发 `nodeFileTrace`，在当前文档站 + pnpm workspace + Windows 环境下长期占用高 CPU/高内存，导致构建长时间卡在 Nitro 收尾；(2) PowerShell 下超时终止或手动中断 `pnpm -> cmd -> node -> nuxt build` 时，旧子进程树不会自动清干净，叠加出多条残留构建链，进一步放大“卡死”错觉。处理原则：先按命令行特征清理旧构建进程，只保留一条单独进程复现；确认 `.nuxt/dist/server/server.mjs` 已生成后，把排查焦点收缩到 Nitro 收尾；在 `packages/vue-element-cui-nuxt/nuxt.config.ts` 中显式设置 `nitro.externals.trace = false`，绕开当前环境下的 tracing 卡点。验证方式：单进程执行 `pnpm --filter @eams-monorepo/vue-element-cui-nuxt exec nuxi build --logLevel=verbose`，应产出 `.output/server/index.mjs` 并打印 `Build complete!`；不要再把“日志停住”直接等同于“进程空转无进展”。
- `.claude/skills/fix-bug/record-bug-fix-memory/SKILL.md` 是本项目专用的错误经验沉淀技能。后续处理 bug、warning、启动事故或 hydration 问题时，可以先把这个技能作为历史经验参考；一旦确认问题已经修复，应主动把新增的根因、关键误导点、有效修复、验证方式和后续约束补充回这个技能，并在需要时同步回根级 AI 记忆文档与 Memorix。不要把这个技能写成具体修复步骤清单。

# Memorix — Automatic Memory Rules

You have access to Memorix memory tools. Follow these rules to maintain persistent context across sessions.

## RULE 1: Session Start — Load Context

At the **beginning of every conversation**, BEFORE responding to the user:

1. Call `memorix_session_start` to get the previous session summary and key memories (this is a direct read, not a search — no fragmentation risk)
2. Then call `memorix_search` with a query related to the user's first message for additional context
3. If search results are found, use `memorix_detail` to fetch the most relevant ones
4. Reference relevant memories naturally — the user should feel you "remember" them

## RULE 2: Store Important Context

**Proactively** call `memorix_store` when any of the following happen:

### What MUST be recorded

- Architecture/design decisions → type: `decision`
- Bug identified and fixed → type: `problem-solution`
- Unexpected behavior or gotcha → type: `gotcha`
- Config changed (env vars, ports, deps) → type: `what-changed`
- Feature completed or milestone → type: `what-changed`
- Trade-off discussed with conclusion → type: `trade-off`

### What should NOT be recorded

- Simple file reads, greetings, trivial commands (ls, pwd, git status)

### Use topicKey for evolving topics

For decisions, architecture docs, or any topic that evolves over time, ALWAYS use `topicKey` parameter.
This ensures the memory is UPDATED instead of creating duplicates.
Use `memorix_suggest_topic_key` to generate a stable key.

Example: `topicKey: "architecture/auth-model"` — subsequent stores with the same key update the existing memory.

### Track progress with the progress parameter

When working on features or tasks, include the `progress` parameter:

```json
{
	"progress": {
		"feature": "user authentication",
		"status": "in-progress",
		"completion": 60
	}
}
```

Status values: `in-progress`, `completed`, `blocked`

## RULE 3: Resolve Completed Memories

When a task is completed, a bug is fixed, or information becomes outdated:

1. Call `memorix_resolve` with the observation IDs to mark them as resolved
2. Resolved memories are hidden from default search, preventing context pollution

This is critical — without resolving, old bug reports and completed tasks will keep appearing in future searches.

## RULE 4: Session End — Store Decision Chain Summary

When the conversation is ending, create a **decision chain summary** (not just a checklist):

1. Call `memorix_store` with type `session-request` and `topicKey: "session/latest-summary"`:

   **Required structure:**

   ```plain
   ## Goal
   [What we were working on — specific, not vague]

   ## Key Decisions & Reasoning
   - Chose X because Y. Rejected Z because [reason].
   - [Every architectural/design decision with WHY]

   ## What Changed
   - [File path] — [what changed and why]

   ## Current State
   - [What works now, what's pending]
   - [Any blockers or risks]

   ## Next Steps
   - [Concrete next actions, in priority order]
   ```

   **Critical: Include the "Key Decisions & Reasoning" section.** Without it, the next AI session will lack the context to understand WHY things were done a certain way and may suggest conflicting approaches.

2. Call `memorix_resolve` on any memories for tasks completed in this session

## RULE 5: Compact Awareness

Memorix automatically compacts memories on store:

- **With LLM API configured:** Smart dedup — extracts facts, compares with existing, merges or skips duplicates
- **Without LLM (free mode):** Heuristic dedup — uses similarity scores to detect and merge duplicate memories
- **You don't need to manually deduplicate.** Just store naturally and compact handles the rest.
- If you notice excessive duplicate memories, call `memorix_deduplicate` for batch cleanup.

## Guidelines

- **Use concise titles** (~5-10 words) and structured facts
- **Include file paths** in filesModified when relevant
- **Include related concepts** for better searchability
- **Always use topicKey** for recurring topics to prevent duplicates
- **Always resolve** completed tasks and fixed bugs
- **Always include reasoning** — "chose X because Y" is 10x more valuable than "did X"
- Search defaults to `status="active"` — use `status="all"` to include resolved memories
