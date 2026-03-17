# 资源目录

这里是源码资源目录，所有的源码都在这里编写，下面分别对各个目录或配置作用详细说明一下

## 目录

### components

组件目录，组件就是在界面的可重用部分，如按钮和菜单等等。

得益于 [`@uni-helper/vite-plugin-uni-components`](https://github.com/uni-helper/vite-plugin-uni-components)，组件会自动注册到全局，你不需要显式导入它们。只需要在 `src/components` 目录下创建组件，然后直接使用即可。

比如你有如下的组件代码，代码保存在`src/components/AppAlert.vue`文件里面

```vue
<template>
	<span>
		<slot />
	</span>
</template>
```

在页面可以直接使用组件，如在`src/pages/test/index.vue`中使用

```vue
<template>
	<div>
		<h1>欢迎使用 vitesse-uni-app</h1>
		<AppAlert>这个组件会自动导入</AppAlert>
	</div>
</template>
```

### `composables`

组合式函数的目录， 利用`Vue`的组合式 `API (Composition API)` 来**封装和复用有状态逻辑**的函数

特点如下

- **复用有状态逻辑：** 与纯函数（无状态）不同，`Composables` 管理着随时间变化的响应式状态（如：鼠标位置跟踪、触摸手势、数据库连接状态等）。
- **命名规范：** 为了清晰，通常以 `use` 开头命名，例如 `useMouse`、`useFetch` 等。
- **组件化逻辑：** 它让逻辑能够像积木一样被组合和复用，解决代码重复问题。

### pages

页面目录，通过组合使用组件，我们可以得到展示给用户的页面。

得益于 [`@uni-helper/vite-plugin-uni-pages`](https://github.com/uni-helper/vite-plugin-uni-pages)，约定式路由（文件路由）的实现轻而易举。`src/pages` 目录下的每个文件都代表着一个路由。要创建新页面，只需要在这个目录里新增 `.vue` 文件。

为保持命名风格一致，一般会为每个页面创建一个目录（目录名称小写），然后再目录下面创建`index.vue`，来编写页面

如下面所示的目录结构

`pages`

​ `about/index.vue`

​ `index/index.vue`

​ `mine/index.vue`

示例代码

```vue
<!--index/index.vue-->
<template>
	<div>
		<h1>欢迎使用vitesse-uni-app</h1>
		<AppAlert>这个组件会自动导入</AppAlert>
	</div>
</template>
```

```vue
<!--about/index.vue-->
<template>
	<section>
		<p>通过 `/pages/about/index` 来访问这个页面</p>
	</section>
</template>
```

`vite-plugin-uni-pages`也支持配置排除指定目录的页面（例如组件目录），相对于 `dir` 和 `subPackages`，在`vite.config.ts`中已经做了相应的配置排除了`components`目录，关键配置如下

```ts
export default defineConfig({
	plugins: [
		// https://github.com/uni-helper/vite-plugin-uni-pages
		UniHelperPages({
			dts: "src/uni-pages.d.ts",
			subPackages: ["src/subPages", "src/subEcharts", "src/subAsyncEcharts"],
			/**
			 * 排除的页面，相对于dir和subPackages
			 * @default []
			 */
			exclude: ["**/components/**/*.*"],
		}),
	],
});
```

### subPages

子页面目录，在此目录下面分门别类的编写各个子页面

### layouts

布局目录，布局可以用来创建通用界面（如页眉和页脚显示）的包装器，不同的页面可能需要不同的布局。布局是使用 `Vue` 的插槽功能实现的。

得益于 [`@uni-helper/vite-plugin-uni-layouts`](https://github.com/uni-helper/vite-plugin-uni-layouts)，你可以轻松地切换不同的布局。

`src/layouts/default.vue` 文件将作为默认布局。

比如如下示例代码

```vue
<!-- src/layouts/default.vue -->
<template>
	<div>
		<AppHeader />
		<!-- src/pages/index/index.vue 和 src/pages/about/index.vue 内容展示 -->
		<slot />
		<AppFooter />
	</div>
</template>
```

在页面文件内设置 `route` 代码块可以指定自定义布局。

```vue
<route lang="json">
{
	"layout": "custom"
}
</route>
```

### router

路由配置目录，[`uni-app`](https://uniapp.dcloud.net.cn/tutorial/page.html#路由) 页面路由为框架统一管理，开发者需要在 [`pages.json`](#page.json) 里配置每个路由页面的路径及页面样式。类似小程序在 `app.json` 中配置页面路由一样。所以 `uni-app` 的路由用法与 `Vue Router` 不同，不过我们可以通过引入类似插件实现类似 `Vue Router` 的开发体验，例如 `@wot-ui/router`。

[`@wot-ui/router`](https://my-uni.wot-ui.cn/guide/router/introduction.html) 是专为`uni-app`设计的轻量级路由库，它提供了类似`Vue Router`的`API`和功能，可以帮助开发者实现在`uni-app`中进行路由跳转、传参、拦截等常用操作。

### store

状态管理目录，得益于组合式方法（`Composition API`），管理状态非常简单，本项目已经集成了 [`Pinia`](https://starter.wot-ui.cn/guide/state-management.html#pinia) ，并提供了简易集成方案，可以直接使用。

本项目添加了一个简易插件实现 `Pinia` 持久化，默认持久化所有 Store 数据，如需排除某些数据，可以在 [persist](https://github.com/wot-ui/wot-starter/blob/main/src/store/persist.ts) 中添加排除名单：

```tsx
// src/store/persist.ts
...
export function persistPlugin(context: PiniaPluginContext) {
  // 传入排除列表(store 名单)
  persist(context, ['temp'])
}
...
```

### static

静态资源存放目录

### fonts

字体资源目录

### utils

工具库目录

### `api`

网络请求相关文件，本项目内置的请求库是 [`alova`](https://starter.wot-ui.cn/guide/request.html#alova)。

我们通过[`@alova/wormhole`](https://alova.js.org/zh-CN/tutorial/getting-started/extension-integration) 完成了编辑器扩展集成，集成`alova`的编辑器扩展可以让它展现出它更强大的力量。

- 自动生成请求代码和响应数据类型，在 `js` 项目中也能体验对接口数据的智能提示。
- 将 `api` 文档嵌入代码中，带你体验边查边用 `API` 的效果。
- 定时更新 `api` 并主动通知前端开发，不再依赖服务端开发人员通知。

这个目录下面的文件，一个通过运行 `pnpm alova-gen`来生成

生成前通过调整`alova.config.ts`配置来执向`api`文档地址

## 配置

### manifest.json

应用的配置文件，用于指定应用的名称、图标、权限等。

每个配置项的作用参考[`uni-app`应用配置](https://uniapp.dcloud.net.cn/collocation/manifest.html)

得益于 [`@uni-helper/vite-plugin-uni-manifest`](https://github.com/uni-helper/vite-plugin-uni-manifest)，你可以使用 `TypeScript` 编写 `uni-app` 的 `manifest.json`。

```ts
// vite.config.ts
import Uni from "@dcloudio/vite-plugin-uni";
import UniManifest from "@uni-helper/vite-plugin-uni-manifest";
import { defineConfig } from "vite";

export default defineConfig({
	plugins: [UniManifest(), Uni()],
});
```

创建 `manifest.config.(ts|mts|cts|js|cjs|mjs|json)`, 然后用 `TypeScript` 编写你的 `manifest.json`。

```tsx
// manifest.config.ts
import { defineManifestConfig } from "@uni-helper/vite-plugin-uni-manifest";

export default defineManifestConfig({
	// code here...
});
```

在 [这里](https://github.com/uni-helper/vite-plugin-uni-manifest/blob/main/playground/manifest.config.ts)，你可以找到 `uni-app` 默认的 Vite-TS 模版的 `manifest.json` 是如何用 `TypeScript` 编写的。

**_TIPS：`manifest.json`文件不需要大家修改，程序会自动根据`manifest.config.ts`自动更新_**

### page.json

在`pages.json`中为页面路由指定`name`字段后，即可以使用`name`跳转

> 注意：此处定义的`name`字段必须全局唯一。

下面是配置示例

```json
{
	"pages": [
		{
			"path": "pages/home/Home",
			"name": "home", // 路由 name 用于命名路由的跳转
			"style": {
				"mp-alipay": {
					"allowsBounceVertical": "NO"
				},
				"navigationBarTitleText": "首页"
			}
		},
		{
			"path": "pages/login/Login",
			"name": "login",
			"style": {
				"mp-alipay": {
					"allowsBounceVertical": "NO"
				},
				"navigationBarTitleText": ""
			}
		},
		{
			"path": "pages/mine/Mine",
			"name": "mine",
			"style": {
				"navigationBarTitleText": "",
				"navigationBarBackgroundColor": "#E7F0FF"
			}
		}
	],
	"tabBar": {
		"color": "#bfbfbf",
		"selectedColor": "#0165FF",
		"backgroundColor": "#ffffff",
		"list": [
			{
				"pagePath": "pages/home/Home",
				"iconPath": "static/icon_home.png",
				"selectedIconPath": "static/icon_home_selected.png",
				"text": "首页"
			},
			{
				"pagePath": "pages/mine/Mine",
				"iconPath": "static/icon_mine.png",
				"selectedIconPath": "static/icon_mine_selected.png",
				"text": "我的"
			}
		]
	},
	"globalStyle": {
		"navigationBarTextStyle": "black",
		"navigationBarBackgroundColor": "#FFF",
		"backgroundColor": "#F8F8F8"
	}
}
```

这个文件不需要大家修改，你再定义页面的时候需要使用`definePage`设置，保存后会自动更新到`json`配置，示意代码如下：

```vue
<script setup lang="ts">
definePage({
	name: "home",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "主页",
		titleNView: false,
	},
});
</script>
```

### theme.json

主题颜色配置

```json
{
	"light": {
		"bgColor": "#F8F8F8",
		"bgColorBottom": "#F8F8F8",
		"bgColorTop": "#F8F8F8",
		"bgTxtStyle": "dark",
		"navBgColor": "#FFF",
		"navTxtStyle": "black",
		"tabBgColor": "#ffffff",
		"tabBorderStyle": "black",
		"tabColor": "#bfbfbf",
		"tabSelectedColor": "#0165FF"
	},
	"dark": {
		"bgColor": "#000",
		"bgColorBottom": "#000",
		"bgColorTop": "#000",
		"bgTxtStyle": "light",
		"navBgColor": "#000000",
		"navTxtStyle": "white",
		"tabBgColor": "#1a1a1a",
		"tabBorderStyle": "white",
		"tabColor": "#bfbfbf",
		"tabSelectedColor": "#0165FF"
	}
}
```

### \*.d.ts

这些都时候是 ts 类型定义文件，根据需求新增或修改内容

### uni.scss

这里是`uni-app`内置的常用样式变量，`uni-app`官方扩展插件及插件市场（https://ext.dcloud.net.cn）上很多三方插件均使用了这些样式变量

如果你是插件开发者，建议你使用 scss 预处理，并在插件代码中直接使用这些变量（无需 import 这个文件），方便用户通过搭积木的方式开发整体风格一致的`App`

## 入口文件

### `App.vue`

应用入口组件

### `App.ku.vue`

虚拟根组件，在传统的 `UniApp` 开发中，由于框架限制，无法像标准 `Vue` 应用那样使用全局根组件来管理公共状态和组件，这给开发带来了诸多不便。

为了解决这个问题，我们引入了 [`@uni-ku/root`](https://github.com/uni-ku/root) 插件，它通过 Vite 模拟出虚拟根组件，让 `UniApp` 项目也能享受到类似 `Vue` 标准应用的开发体验，也可以解决 `@uni-helper/vite-plugin-uni-layouts` 插件无法使用微信小程序 `page-meta` 的问题。

### `main.ts`

应用核心入口文件，负责初始化应用实例、挂载 DOM 节点、注册全局组件/插件以及配置全局属性，是项目启动的起点
