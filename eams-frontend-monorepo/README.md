# EAMS Frontend Monorepo

EAMS 前端单仓项目，基于 `pnpm workspace + Turbo` 组织多个应用与共享包。

## 项目结构

```plain
eams-frontend-monorepo/
├─ apps/
│  ├─ eams-frontend      # 后台管理端（Vue 3 + Vite）
│  ├─ eams-fronttea      # 教师端（uni-app）
│  └─ eams-frontstu      # 学生端（uni-app）
├─ packages/
│  ├─ vue-element-cui        # Element Plus 二次封装组件库
│  └─ vue-element-cui-nuxt   # 组件库文档站（Nuxt 3 + shadcn-docs-nuxt）
├─ old/
│  └─ vue-element-cui     # 历史 Vue2 组件库，仅迁移参考
├─ docs/                  # 计划、报告、文档沉淀
├─ openspec/              # OpenSpec 变更工件
├─ pnpm-workspace.yaml
└─ turbo.json
```

## 环境要求

- Node.js: `>=20.19.0`（或 `>=22.12.0`、`>=24.0.0`）
- pnpm: `10.32.1`（见根 `package.json` 的 `packageManager`）
- 系统：推荐 Windows PowerShell / macOS / Linux

## 快速开始

```bash
# 1) 安装依赖（请在 monorepo 根目录执行）
pnpm install

# 2) 启动所有可开发子项目（turbo pipeline）
pnpm dev
```

> 若只想启动某个子包，使用 `pnpm --filter <package-name> <script>`，例如：
>
> - `pnpm --filter @eams-monorepo/admin dev`
> - `pnpm --filter @eams-monorepo/vue-element-cui-nuxt dev`

## 常用命令（根目录）

- `pnpm dev`：运行开发任务（Turbo）
- `pnpm build`：构建工作区（Turbo）
- `pnpm lint`：执行 ESLint
- `pnpm format`：执行 Prettier 写入
- `pnpm format:check`：检查格式
- `pnpm clean`：清理构建缓存目录
- `pnpm clean:deps`：清理所有 `node_modules`
- `pnpm release`：构建并执行 changeset 发布流程

## 工作区子包

### 应用

- `apps/eams-frontend`（`@eams-monorepo/admin`）：后台管理端
- `apps/eams-fronttea`（`@eams-monorepo/tea-app`）：教师移动端
- `apps/eams-frontstu`（`@eams-monorepo/stu-app`）：学生移动端

### 共享包

- `packages/vue-element-cui`（`@eams-monorepo/vue-element-cui`）：组件库
- `packages/vue-element-cui-nuxt`（`@eams-monorepo/vue-element-cui-nuxt`）：组件库文档站

### 历史包

- `old/vue-element-cui`：Vue2 历史实现，仅做迁移参考，不参与当前主链路开发

## README 约定

本仓库采用“根 README + 子包 README”双层文档模式：

- 根 README 负责说明单仓全局信息与协作入口
- 各子包 README 负责说明该包的用途、脚本和本地开发方式

请优先阅读你要修改的目标子包 README。
