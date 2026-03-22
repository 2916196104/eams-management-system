---
name: use-iconify
description: "Use when 开发者需要在后台项目 `apps/eams-frontend` 中显示图标，尤其是要在 Vue 页面、配置驱动菜单、组合式函数、或兼容旧 `IconXxx` 写法之间选择合适方案时使用。适用于 `ReIcon`、`IconifyIconOffline`、`IconifyIconOnline`、`useRenderIcon`、离线图标扩展和 iconify 接入排错。"
---

# 后台项目使用 Iconify

## 概述

后台项目已经有一套可用的 iconify 集成，不要重复发明入口，也不要在业务页面里绕开 `ReIcon` 体系直接各写各的。

现有能力以 [`apps/eams-frontend/src/components/ReIcon`](../../../../apps/eams-frontend/src/components/ReIcon) 为单一出口，覆盖这几类场景：

- 兼容旧全局别名组件，如 `IconMenu`
- 使用离线 iconify 图标，如 `ep/menu`
- 使用在线 iconify 图标，如 `ri:home-4-line`
- 在配置驱动场景里用 `useRenderIcon` 返回可渲染组件

## 先看现成基线

开始接入前，优先回读这些文件，而不是凭印象写：

- [`apps/eams-frontend/src/components/ReIcon/index.ts`](../../../../apps/eams-frontend/src/components/ReIcon/index.ts)
- [`apps/eams-frontend/src/components/ReIcon/src/hooks.ts`](../../../../apps/eams-frontend/src/components/ReIcon/src/hooks.ts)
- [`apps/eams-frontend/src/components/ReIcon/src/offlineIcon.ts`](../../../../apps/eams-frontend/src/components/ReIcon/src/offlineIcon.ts)
- [`apps/eams-frontend/src/plugins/icon.ts`](../../../../apps/eams-frontend/src/plugins/icon.ts)
- [`apps/eams-frontend/src/views/sample/reicon/Index.vue`](../../../../apps/eams-frontend/src/views/sample/reicon/Index.vue)
- [`apps/eams-frontend/src/components/mynav/EamsNav.vue`](../../../../apps/eams-frontend/src/components/mynav/EamsNav.vue)

## 选型规则

按下面的顺序选，不要混用得没有边界。

1. 旧页面已经在用 `IconMenu`、`IconSearch` 这类旧别名时：先保持兼容，不要为了“统一风格”强行批量重写。
2. 新页面里的常用后台图标：优先用 `IconifyIconOffline`，图标名优先写成 `ep/menu` 这类离线字符串。
3. 长尾图标、本地没有映射、且接受在线依赖时：用 `IconifyIconOnline`，图标名写成 `ri:home-4-line` 这类 iconify 在线格式。
4. 菜单、表格列、配置项、函数返回值这类“不能直接写模板组件”的场景：用 `useRenderIcon`。
5. 已经直接导入了 `~icons/...` 组件，且图标只在当前文件使用：可以直接把组件传给 `useRenderIcon`，或直接在模板里渲染该组件。

## 现有接口

`ReIcon` 目前暴露这些项目内标准入口：

- `IconifyIconOffline`
- `IconifyIconOnline`
- `useRenderIcon`
- `pickIconRenderer`
- `resolveOfflineIcon`
- `registerOfflineIcons`

其中真正给业务开发者常用的，通常只有前三个。

## 标准写法

### 1. 模板里直接渲染离线图标

```vue
<template>
	<IconifyIconOffline icon="ep/menu" width="18" height="18" />
</template>
```

适用：

- 表单按钮
- 卡片标题
- 页面局部说明
- 后台常用固定图标

说明：

- 当前仓库的离线图标主约定是 `ep/menu` 这种斜杠写法
- `offlineIcon.ts` 内部会归一化 `:` 和 `/`，但新代码优先跟随仓库现有写法

### 2. 模板里直接渲染在线图标

```vue
<template>
	<IconifyIconOnline icon="ri:home-4-line" width="18" height="18" />
</template>
```

适用：

- 只偶尔出现的长尾图标
- 不值得加入离线映射的图标

约束：

- 在线图标依赖网络或运行时可用资源
- 如果同一个图标会在后台大量重复出现，优先考虑补到离线映射里

### 3. 配置驱动场景统一用 `useRenderIcon`

```ts
import { useRenderIcon } from "@/components/ReIcon";

const menuIcon = useRenderIcon("ep/menu", {
	width: "18px",
	height: "18px",
});
```

适用：

- 菜单配置
- 表格列配置
- 动态卡片配置
- 需要 `Component` 类型返回值的组合式函数

`useRenderIcon` 的分流规则已经写在 [`apps/eams-frontend/src/components/ReIcon/src/hooks.ts`](../../../../apps/eams-frontend/src/components/ReIcon/src/hooks.ts)：

- 传入 Vue 组件：走离线组件渲染器
- 传入已命中离线映射的字符串：走离线组件渲染器
- 传入带 `:` 且未命中离线映射的字符串：走在线组件渲染器
- 传入不带 `:` 的字符串：按离线字符串处理

### 4. 菜单配置直接写字符串，不要自己手搓渲染逻辑

[`apps/eams-frontend/src/components/mynav/EamsNav.vue`](../../../../apps/eams-frontend/src/components/mynav/EamsNav.vue) 已经内部调用 `useRenderIcon`，所以菜单项可以直接写：

```ts
const navMenus = [
	{
		id: "system",
		text: "系统管理",
		icon: "ep/setting",
		children: [
			{ id: "users", text: "用户管理", path: "users", icon: "IconUser" },
			{ id: "roles", text: "角色权限", path: "roles", icon: "ri:shield-user-line" },
		],
	},
];
```

这三种值都已经被当前后台项目支持：

- 旧别名：`IconUser`
- 离线字符串：`ep/setting`
- 在线字符串：`ri:shield-user-line`

## 何时扩充离线图标

出现下面任一情况，再去改 [`apps/eams-frontend/src/components/ReIcon/src/offlineIcon.ts`](../../../../apps/eams-frontend/src/components/ReIcon/src/offlineIcon.ts)：

- 同一个在线图标在后台多处重复使用
- 图标属于后台高频入口，应该脱离在线依赖
- 你需要让字符串图标也能命中 `useRenderIcon` 的离线路径

扩充步骤：

1. 从 `~icons/<collection>/<name>` 导入图标组件。
2. 加到 `offlineIcons` 中，键名使用仓库约定的字符串，如 `ep/menu`。
3. 只有在必须兼容旧 `IconXxx` 写法时，才补 `aliasIcons`。
4. 不要为了新页面方便就无上限新增 `IconXxx` 别名；旧别名主要是兼容层，不是新代码首选接口。

## 推荐工作流

1. 先判断当前场景是模板渲染还是配置驱动。
2. 优先复用 `@/components/ReIcon` 暴露的入口。
3. 如果图标是后台常用图标，优先走离线方案。
4. 如果是长尾图标，临时走在线方案。
5. 如果在线方案变成高频使用，再回收为离线映射。
6. 改完后到 `/sample/reicon` 对照现有示例确认表现一致。

## 示例基线

完整示例页位于：

- [`apps/eams-frontend/src/views/sample/reicon/Index.vue`](../../../../apps/eams-frontend/src/views/sample/reicon/Index.vue)

这个示例页已经覆盖：

- 旧别名兼容
- 离线字符串图标
- 在线字符串图标
- 直接导入图标组件
- `useRenderIcon` hook
- `mynav` 配置驱动接入

如果你新增了一种后台图标用法，优先补到这个示例页里，而不是只在某个业务页偷偷生效。

## 常见误区

### 不要绕开 `ReIcon` 体系

除非你在做底层基础设施，否则不要在业务代码里直接重新封装 `@iconify/vue`，也不要重新发明另一套 `renderIcon` 工具。后台项目已经有统一出口。

### 不要把旧别名当成新规范

`IconMenu` 这类旧别名要保留，但新代码优先写 `ep/menu`、`ri:...` 或 `useRenderIcon(...)`。

### 不要在集成改动里删掉原注释和说明

历史上已经出现过为了接入 iconify 而覆盖式重写入口文件，顺手删掉原注释和说明文案的问题。接入 iconify 时优先做最小补丁，保留现有注释、说明文字和组件语义。

### 不要在示例页里使用宽泛类名

`/sample/reicon` 历史上出现过 `.icon-title` 这类宽泛类名命中外部样式，导致标题前出现多余 `::before` 图标。示例页优先使用局部、语义明确的类名，例如 `.item-title`、`.item-text`，并保持 `scss`。

## 验证清单

完成 iconify 相关改动后，至少自查这些点：

- 页面图标是否正常显示
- 配置驱动场景是否仍能渲染图标
- 旧 `IconXxx` 页面是否没有被你意外改坏
- 新增的离线图标是否真的命中了 `offlineIcon.ts`
- `/sample/reicon` 示例是否仍覆盖并展示正确

## 边界

这个技能只服务于后台项目 `apps/eams-frontend`。

不要把这里的 `ReIcon` 用法直接套到：

- `apps/eams-fronttea`
- `apps/eams-frontstu`
- 组件库或文档站

这些项目没有承诺与后台项目共享同一套 iconify 接入面。
