# ReIcon 图标组件说明

`ReIcon` 为后台项目补充了一套兼容现有 `IconXxx` 写法的 iconify 方案，目标是让老页面继续可用，同时让新页面可以直接使用 iconify 的离线图标、在线图标和渲染 hook。

## 1. 目录结构

```plain
src/components/ReIcon/
├── README.md
├── index.ts
├── type.ts
└── src/
    ├── hooks.ts
    ├── iconifyIconOffline.ts
    ├── iconifyIconOnline.ts
    └── offlineIcon.ts
```

## 2. 支持的使用方式

### 2.1 继续使用旧的全局别名

入口插件仍会注册 `IconMenu`、`IconSearch`、`IconHomeFilled` 这类全局组件名称，老页面不用改动。

```vue
<template>
	<el-button icon="IconSearch">搜索</el-button>
	<el-icon><IconMenu /></el-icon>
</template>
```

### 2.2 使用离线字符串图标

离线图标使用 `图标集/图标名` 的格式，例如 `ep/menu`、`ep/home-filled`。

```vue
<template>
	<IconifyIconOffline icon="ep/menu" width="18" height="18" />
</template>
```

### 2.3 使用在线字符串图标

在线图标使用 `图标集:图标名` 的格式，例如 `ri:home-4-line`。

```vue
<template>
	<IconifyIconOnline icon="ri:home-4-line" width="18" height="18" />
</template>
```

### 2.4 使用 `useRenderIcon`

当菜单、表格列或其他配置项需要动态返回组件时，推荐使用 `useRenderIcon`。

```ts
import { useRenderIcon } from "@/components/ReIcon";

const menuIcon = useRenderIcon("ep/menu", { width: "18px", height: "18px" });
```

## 3. 与 `mynav` 的集成

`mynav` 现在同时支持以下三种图标值：

1. 旧的全局别名字符串，如 `IconMenu`
2. 离线字符串，如 `ep/menu`
3. 在线字符串，如 `ri:home-4-line`

这样后台菜单既可以保持兼容，也可以逐步迁移到 iconify。

## 4. 示例页面

运行示例后，可在 `sample -> ReIcon 图标方案` 页面查看完整演示，路径为 `/sample/reicon`。
