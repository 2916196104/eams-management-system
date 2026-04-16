# EamsNav

`EamsNav` 是一个给教务系统页面使用的左侧动态导航组件，支持：

- 一级菜单
- 展开的二级菜单
- 菜单数据动态传入
- 折叠/展开
- 路由模式和内容区插槽

## 使用示例

```vue
<template>
	<EamsNav :menus="menus" app-name="教务系统" user-text="欢迎使用">
		<router-view />
	</EamsNav>
</template>

<script setup lang="ts">
import { ref } from "vue";
import type { EamsNavMenuItem } from "./type";

const menus = ref<EamsNavMenuItem[]>([
	{
		id: "system",
		text: "系统管理",
		icon: "IconSetting",
		children: [
			{ id: "user", text: "用户管理", path: "/system/user", icon: "IconUser" },
			{ id: "role", text: "角色管理", path: "/system/role", icon: "IconTickets" },
		],
	},
	{
		id: "course",
		text: "教学管理",
		icon: "IconMenu",
		children: [
			{ id: "course-list", text: "课程信息", path: "/course/list" },
			{ id: "schedule", text: "课表管理", path: "/course/schedule" },
		],
	},
]);
</script>
```

后续如果菜单来自接口，只需要替换 `menus` 数据即可，不需要改组件结构。
