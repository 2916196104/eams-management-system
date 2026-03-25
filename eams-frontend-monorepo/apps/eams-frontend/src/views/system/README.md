# system 视图目录说明

这个目录负责 `系统管理` 模块页面本身的组织与展示。

如果说：

- `src/apis/system` 是接口适配层
- `src/router/main/system` 是路由入口

那么 `src/views/system` 就是页面展示层。

---

## 1. 目录结构

当前目录主要包含三类文件：

- 页面入口文件
- 页面通用配置文件
- 具体页面组件文件

当前结构如下：

- `InternalAnnouncement.vue`
- `SystemParameter.vue`
- `RolePermission.vue`
- `DataDictionary.vue`
- `NotificationSetting.vue`
- `shared.ts`
- `menu.ts`
- `components/`

`components/` 下面主要是：

- `SystemSectionLayout.vue`
- `SystemAnnouncementPage.vue`
- `SystemSettingsPage.vue`
- `SystemRolePermissionPage.vue`
- `SystemDictionaryPage.vue`
- `SystemNotificationPage.vue`

---

## 2. 每类文件分别负责什么

### 2.1 页面入口文件

这些文件都比较薄：

- `InternalAnnouncement.vue`
- `SystemParameter.vue`
- `RolePermission.vue`
- `DataDictionary.vue`
- `NotificationSetting.vue`

它们的作用通常只有一件事：

- 把对应的页面组件和配置对象绑定起来

也就是说，这些文件基本就是“页面壳子”。

这样做的好处是：

- 路由组件很干净
- 页面逻辑集中在 `components`
- 配置集中在 `shared.ts`

如果以后你要换文案、换列、换接口绑定，通常不用先改这些入口文件。

### 2.2 shared.ts

`shared.ts` 是这个目录里最重要的“配置中转站”。

它做两件事：

1. 定义每个页面组件需要的配置类型
2. 把接口层 `src/apis/system` 的方法绑定成页面可直接使用的配置对象

例如这里会集中定义：

- 列定义
- 表单字段定义
- 页面标题文案
- 调用哪个 API 方法

所以它起到的是：

- 页面组件和接口层之间的桥梁

你可以把它理解成“system 页面模块的装配文件”。

### 2.3 menu.ts

`menu.ts` 管的是系统管理左侧菜单项或顶部菜单项的展示信息。

它的作用主要是：

- 定义菜单名称
- 定义每个菜单对应路径
- 标记哪些菜单暂时不可用

这个文件不负责页面逻辑，只负责导航展示。

### 2.4 components 目录

这里放的是实际承担页面逻辑和 UI 渲染的组件。

这些组件通常会：

- 接收一个 `config`
- 根据配置去渲染页面
- 在内部处理交互
- 调用 `config` 传进来的接口方法

这样组件就能保持“通用页面骨架 + 外部配置注入”的结构。

---

## 3. 当前页面是怎么串起来的

以系统参数页为例：

1. 路由进入 `SystemParameter.vue`
2. `SystemParameter.vue` 引入 `SystemSettingsPage.vue`
3. 同时从 `shared.ts` 引入 `systemSettingsConfig`
4. `SystemSettingsPage.vue` 拿到 `config`
5. 组件内部通过 `config.loadGroups()`、`config.updateValue()` 去调用接口
6. 实际接口实现来自 `src/apis/system/index.ts`

其他几个页面基本都是这个模式。

这个模式的核心优点是：

- 页面展示和接口实现解耦
- 后续换接口时，优先改 `apis/system` 或 `shared.ts`
- 页面组件本身能保持稳定

---

## 4. components 下每个文件的作用

### SystemSectionLayout.vue

这是 system 页面统一的外层布局组件。

作用通常是：

- 提供统一页面容器
- 控制内边距、背景、版心等公共样式

如果你发现几个 system 页面长得很像，通常就是这个组件在提供统一外壳。

### SystemAnnouncementPage.vue

内部公告页组件。

负责：

- 搜索
- 表格展示
- 新增/编辑公告弹窗
- 删除公告

### SystemSettingsPage.vue

系统参数页组件。

负责：

- 左侧分组切换
- 右侧配置项展示
- 根据字段类型渲染开关、输入框、数字框、时间选择器
- 保存单项设置

### SystemRolePermissionPage.vue

角色权限页组件。

负责：

- 角色列表展示
- 新增/编辑/删除角色
- 加载角色员工
- 添加/移除员工
- 权限树勾选和保存

这是当前逻辑相对最复杂的页面之一。

### SystemDictionaryPage.vue

数据字典页组件。

负责：

- 左侧字典类型切换
- 右侧字典项表格
- 新增/编辑字典项
- 批量删除字典项

### SystemNotificationPage.vue

通知设置页组件。

负责：

- 展示单个通知设置对象
- 编辑通知开关、模板 ID、提示信息
- 保存通知设置

注意：

这个页面现在已经不是最早那种“多模板分组表格”结构了，而是改成了单对象设置表单。

---

## 5. 为什么入口页很薄，而组件页很厚

这是当前目录一个很明显的设计特点。

### 薄入口页

入口页只做：

- 引入组件
- 引入配置
- 进行一次绑定

优点：

- 简单
- 路由文件清晰
- 不会把业务逻辑散落到很多入口文件里

### 厚组件页

具体组件负责：

- 页面交互
- 表单状态
- 弹窗状态
- 表格操作
- 事件响应

优点：

- 逻辑集中
- 查问题时更容易定位

---

## 6. shared.ts 为什么单独拆出来

如果没有 `shared.ts`，通常会出现两种问题：

1. 组件里写死文案、列、接口绑定，组件越来越重
2. 不同页面的配置分散在多个文件里，不好统一看

把 `shared.ts` 单独拆出来之后：

- 页面组件更像“通用骨架”
- 配置更集中
- 同类页面更容易保持一致风格

所以这里建议你把它当成：

- system 模块的页面配置中心

---

## 7. 你以后想改东西，先改哪里

这里给一个最实用的定位规则。

### 改页面文案、列、按钮名字

优先看：

- `shared.ts`

### 改接口地址、请求参数、返回映射

优先看：

- `src/apis/system/index.ts`
- `src/apis/system/type.ts`

### 改页面交互和布局

优先看：

- `components/` 下对应页面组件

### 改菜单路径和菜单显示

优先看：

- `menu.ts`

### 改路由本身

优先看：

- `src/router/main/system`
- 以及旧兼容入口 `src/router/main/sysmanage`

---

## 8. 当前这个目录的设计思路

这个目录现在采用的是一种比较清晰的分层方式：

- 路由层：决定访问哪个页面
- 入口页：负责绑定组件和配置
- 配置层：`shared.ts`
- 组件层：负责真实页面交互
- 接口层：`src/apis/system`

这样的好处是：

- 你查问题时不容易乱
- 接口变了，不一定要改组件
- 页面改版，不一定要改接口

---

## 9. 一句话理解这个目录

`src/views/system` 是系统管理模块的页面装配层和展示层：  
它负责把菜单、页面入口、通用配置、具体组件和接口层拼成一套可运行的系统管理页面。
