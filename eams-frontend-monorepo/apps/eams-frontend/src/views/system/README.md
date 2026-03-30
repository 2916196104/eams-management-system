# system 视图目录说明

当前 `src/views/system` 已经按接近 `console` 模块的方式组织：

- 每个页面都有自己的入口 `.vue`
- 页面内容直接渲染在主框架右侧内容区
- 不再依赖 `system` 自己那套内部侧边栏布局

当前保留的系统页面有：

- 数据字典
- 通知设置
- 节假日管理
- 操作日志

## 目录结构

- `DataDictionary.vue`
- `NotificationSetting.vue`
- `HolidayManage.vue`
- `OperationLog.vue`
- `shared.ts`
- `components/`

`components/` 当前主要包含：

- `SystemDictionaryPage.vue`
- `SystemNotificationPage.vue`
- `SystemHolidayPage.vue`
- `SystemOperationLogPage.vue`

## 当前真实运行逻辑

### 1. 路由入口

系统页面路由统一注册在：

- `src/router/main/system/index.ts`

当前路由为：

- `/system/data-dictionary`
- `/system/notification-setting`
- `/system/holiday-manage`
- `/system/operation-log`

### 2. 页面加载方式

每个入口页只做一件事：

- 引入对应的页面组件
- 必要时传入 `shared.ts` 中的配置

例如：

- `DataDictionary.vue` -> `SystemDictionaryPage.vue`
- `NotificationSetting.vue` -> `SystemNotificationPage.vue`
- `HolidayManage.vue` -> `SystemHolidayPage.vue`
- `OperationLog.vue` -> `SystemOperationLogPage.vue`

### 3. 页面展示方式

现在 `system` 页面和 `console` 的风格一致：

- 页面直接显示在主框架 `HomeView.vue` 的右侧内容区
- 页面切换依赖主框架菜单和主路由

## 各文件作用

### DataDictionary.vue

数据字典页面入口。

作用：

- 引入 `SystemDictionaryPage.vue`
- 引入 `dataDictionaryConfig`
- 将页面和配置绑定起来

### NotificationSetting.vue

通知设置页面入口。

作用：

- 引入 `SystemNotificationPage.vue`
- 引入 `notificationSettingConfig`
- 将页面和配置绑定起来

### HolidayManage.vue

节假日管理页面入口。

作用：

- 引入 `SystemHolidayPage.vue`

说明：

- 已接入真实接口查询、新增、删除节日

### OperationLog.vue

操作日志页面入口。

作用：

- 引入 `SystemOperationLogPage.vue`

说明：

- 已接入真实分页查询接口

### shared.ts

这是当前 `system` 页面里“需要复用配置”的中心文件。

当前主要负责：

- 定义页面组件所需配置类型
- 将 `src/apis/system` 的接口函数组装成页面配置对象

当前主要导出：

- `dataDictionaryConfig`
- `notificationSettingConfig`

### SystemDictionaryPage.vue

数据字典主页面组件。

负责：

- 左侧字典类型列表
- 右侧字典项表格
- 新增 / 编辑字典项
- 批量删除字典项

### SystemNotificationPage.vue

通知设置主页面组件。

负责：

- 通知设置表单展示
- 保存通知设置

### SystemHolidayPage.vue

节假日管理主页面组件。

负责：

- 年份切换
- 日历展示
- 节日高亮
- 调用后端接口新增 / 删除节日

### SystemOperationLogPage.vue

操作日志主页面组件。

负责：

- 条件查询
- 表格展示
- 分页切换
- 调用后端接口查询日志

## 页面与 API 的关系

### 已接入真实接口

- 数据字典
- 通知设置
- 节假日管理
- 操作日志

## 维护建议

- 改页面内容和交互：看 `components/`
- 改页面入口：看各入口 `.vue`
- 改可复用配置：看 `shared.ts`
- 改路由：看 `src/router/main/system/index.ts`
- 改接口：看 `src/apis/system`

## 当前和旧逻辑的区别

旧逻辑：

- `system` 自己有一套内部侧边栏
- 页面通过内部布局组件统一包裹

当前逻辑：

- `system` 页面像 `console` 一样直接作为业务页展示
- 页面切换依赖主框架菜单和主路由
