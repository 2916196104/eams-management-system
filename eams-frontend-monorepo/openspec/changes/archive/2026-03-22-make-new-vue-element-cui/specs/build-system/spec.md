## 新增需求

### 需求：tsdown 配置

构建系统必须使用 tsdown 将 TypeScript 源代码编译为带有类型声明的 JavaScript。

#### 场景：构建配置

- **当** 开发者运行构建命令
- **则** tsdown 必须将源代码从 `src/` 编译到 `dist/`

#### 场景：多种输出格式

- **当** 构建完成
- **则** 必须生成 ESM (`dist/index.js`) 和 CommonJS (`dist/index.cjs`) 两种格式

### 需求：类型声明生成

构建系统必须为所有导出的组件和类型生成完整的 TypeScript 类型声明。

#### 场景：类型声明输出

- **当** 构建完成
- **则** 必须生成包含所有类型声明的 `dist/index.d.ts`

#### 场景：类型解析

- **当** 用户在 TypeScript 项目中从库导入
- **则** IDE 必须提供准确的类型提示和自动完成

### 需求：外部依赖

构建系统必须将 Vue 和 Element Plus 标记为外部依赖，以避免打包它们。

#### 场景：外部配置

- **当** tsdown 构建库
- **则** `vue` 和 `element-plus` 必须不被包含在输出包中

#### 场景：对等依赖声明

- **当** 包发布
- **则** `vue` 和 `element-plus` 必须在 package.json 中声明为 peerDependencies

### 需求：样式编译

构建系统必须将 SCSS 文件编译为 CSS 并输出到 `dist/styles/`。

#### 场景：主样式编译

- **当** 构建运行
- **则** 必须将 `src/styles/index.scss` 编译为 `dist/styles/index.css`

#### 场景：组件样式编译

- **当** 构建运行
- **则** 必须将各个组件的 SCSS 文件编译为 `dist/styles/` 中的独立 CSS 文件

### 需求：构建脚本

包必须提供用于开发和生产构建的 npm 脚本。

#### 场景：开发构建

- **当** 开发者运行 `pnpm dev`
- **则** tsdown 必须在监听模式下运行并支持热重载

#### 场景：生产构建

- **当** 开发者运行 `pnpm build`
- **则** 必须清理 dist 目录并构建所有输出

### 需求：包导出

package.json 必须为主入口、样式和类型定义适当的导出。

#### 场景：主入口导出

- **当** 用户从包根目录导入
- **则** 必须根据环境解析到正确的 ESM 或 CommonJS 格式

#### 场景：样式导出

- **当** 用户导入样式 `import 'vue-element-cui/styles'`
- **则** 必须解析到 `dist/styles/index.css`

#### 场景：单独样式导出

- **当** 用户导入组件样式 `import 'vue-element-cui/styles/cui-table.css'`
- **则** 必须解析到特定的组件 CSS 文件
