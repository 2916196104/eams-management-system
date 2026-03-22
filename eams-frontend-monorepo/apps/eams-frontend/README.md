# @eams-monorepo/admin

EAMS 后台管理端项目，基于 `Vue 3 + Vite + Element Plus`。

> 本项目属于 `eams-frontend-monorepo` 工作区，包名为 `@eams-monorepo/admin`。

## IDE 设置要求

[VSCode](https://code.visualstudio.com/) + [Volar](https://marketplace.visualstudio.com/items?itemName=Vue.volar)（需要禁用 `Vetur`）。

默认情况下，TypeScript 无法处理 `.vue` 导入的类型信息，因此我们使用 `vue-tsc` 替代 `tsc` 命令行工具进行类型检查。在编辑器环境中，我们需要通过 [Volar](https://marketplace.visualstudio.com/items?itemName=Vue.volar) 插件来让 TypeScript 语言服务识别 `.vue` 文件的类型。

## 自定义配置

详情请参阅：[Vite Configuration Reference](https://vitejs.dev/config/)。

## 快速开始

在 monorepo 根目录执行：

```bash
# 安装依赖
pnpm install

# 开发时：编译并以热加载的方式启动项目
pnpm --filter @eams-monorepo/admin dev

# 发布时：编译并压缩代码
pnpm --filter @eams-monorepo/admin build

# 预览构建产物
pnpm --filter @eams-monorepo/admin preview

# 使用 Vitest 执行单元测试
pnpm --filter @eams-monorepo/admin test:unit

# 类型检查
pnpm --filter @eams-monorepo/admin type-check

# 使用 ESLint 检查代码
pnpm --filter @eams-monorepo/admin lint
```

## 依赖关系

- 业务中可直接消费工作区包 `@eams-monorepo/vue-element-cui`。
- 图标方案建议复用 `src/components/ReIcon` 的既有入口与约定。

## 目录结构说明

下面目录或文件为有效资源，其他目录或文件不要提交到服务端：

- `public`：存放开放资源，比如比较大的图片文件或站点图标
- `src`：存放资源和源码的目录，注意 `.vue` 文件文件名大写字母开头
  - `apis`：存放网络对接 `api` 接口实现
  - `assets`：小资源文件可以放图标文件或全局样式表
  - `components`：存放公用组件
  - `plugins`：存放自定义插件封装
  - `router`：路由配置文件目录
  - `stores`：状态管理文件目录
  - `types`：存放公用类型定义文件目录
  - `utils`：存放公用工具目录
  - `views`：存放页面目录
  - `App.vue`：程序入口 `vue` 文件
  - `main.ts`：程序入口挂载以及插件装配文件
- `tests`：存放单元测试文件目录
- `index.html`：程序入口页面
- `package.json`：第三方 `JS` 库管理配置文件
- `start.sh`：`Linux` 下面的启动脚本
- `README.md`：项目自述文件
- `.editorconfig`：编辑器配置文件
- `.env*`：为环境变量文件
- `.gitignore`：忽略配置文件
- `.prettierrc.json`：代码美化配置文件
- `env.d.ts`：全局类型和环境变量类型配置文件
- `.eslint.config.ts`：为 `eslint` 配置文件
- `tsconfig.*`：`TypeScript` 配置文件
- `vite.config.ts`：`Vite` 构建工具配置文件
- `vitest.config.ts`：单元测试配置文件
