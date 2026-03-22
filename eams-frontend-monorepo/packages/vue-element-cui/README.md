# @eams-monorepo/vue-element-cui

EAMS Vue Element Component UI Library，基于 Element Plus 的业务组件库。

> 本包属于 `eams-frontend-monorepo` 工作区，当前主要服务于 `apps/eams-frontend`（后台项目）。
> 文档站请查看 `packages/vue-element-cui-nuxt`。

## 安装

```bash
pnpm add @eams-monorepo/vue-element-cui element-plus
```

## 全量注册

```ts
import { createApp } from "vue";
import VueElementCui from "@eams-monorepo/vue-element-cui";
import "@eams-monorepo/vue-element-cui/styles";

const app = createApp(App);
app.use(VueElementCui);
```

## unplugin-vue-components

使用 `VueElementCuiResolver()` 时，组件样式会通过 sideEffects 自动带入，通常无需再单独引入 `@eams-monorepo/vue-element-cui/styles`。

```ts
import Components from "unplugin-vue-components/vite";
import { VueElementCuiResolver } from "@eams-monorepo/vue-element-cui/resolver";

Components({
	resolvers: [VueElementCuiResolver()],
});
```

## unplugin-auto-import

推荐使用组件库提供的 imports 配置（运行时与类型一并自动导入）：

```ts
import AutoImport from "unplugin-auto-import/vite";
import { vueElementCuiImports, vueElementCuiTypeImports } from "@eams-monorepo/vue-element-cui/resolver";

AutoImport({
	imports: [vueElementCuiImports, ...vueElementCuiTypeImports],
});
```

若更偏好 resolvers 形式，可使用 `VueElementCuiAutoImportResolver`，并配合类型导入：

```ts
import AutoImport from "unplugin-auto-import/vite";
import { VueElementCuiAutoImportResolver, vueElementCuiTypeImports } from "@eams-monorepo/vue-element-cui/resolver";

AutoImport({
	resolvers: [VueElementCuiAutoImportResolver()],
	imports: [...vueElementCuiTypeImports],
});
```

## Volar 类型提示

若通过 `app.use(VueElementCui)` 做全局注册，并希望在模板中获得 `Cui*` 组件的类型提示，可在项目的 `tsconfig.json` 中补充：

```json
{
	"compilerOptions": {
		"types": ["@eams-monorepo/vue-element-cui/global"]
	}
}
```

使用 `unplugin-vue-components` 自动生成 `components.d.ts` 时，通常无需再额外配置 `@eams-monorepo/vue-element-cui/global`。

## 包导出

- `@eams-monorepo/vue-element-cui` — 主入口
- `@eams-monorepo/vue-element-cui/resolver` — Resolver & Auto-Import
- `@eams-monorepo/vue-element-cui/global` — Volar 全局类型
- `@eams-monorepo/vue-element-cui/styles` — 样式入口

## 本地开发

在 monorepo 根目录执行：

```bash
# 构建（JS + 样式）
pnpm --filter @eams-monorepo/vue-element-cui build

# 监听构建
pnpm --filter @eams-monorepo/vue-element-cui dev

# 单元测试
pnpm --filter @eams-monorepo/vue-element-cui test

# 类型检查
pnpm --filter @eams-monorepo/vue-element-cui typecheck
```

## License

MIT
