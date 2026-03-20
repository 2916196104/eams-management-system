# @eams-monorepo/vue-element-cui

EAMS Vue Element Component UI Library，基于 Element Plus 的业务组件库。

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

```ts
import Components from "unplugin-vue-components/vite";
import { VueElementCuiResolver } from "@eams-monorepo/vue-element-cui/resolver";

Components({
	resolvers: [VueElementCuiResolver()],
});
```

## unplugin-auto-import

```ts
import AutoImport from "unplugin-auto-import/vite";
import { vueElementCuiImports, vueElementCuiTypeImports } from "@eams-monorepo/vue-element-cui/resolver";

AutoImport({
	imports: [vueElementCuiImports, ...vueElementCuiTypeImports],
});
```

## 开发

```bash
pnpm install
pnpm build
pnpm test
```

## License

MIT
