# system 视图目录说明

这个目录目前只保留两个系统管理页面：

- 数据字典
- 通知设置

## 目录结构

- `DataDictionary.vue`
- `NotificationSetting.vue`
- `menu.ts`
- `shared.ts`
- `components/`

`components/` 当前主要包含：

- `SystemSectionLayout.vue`
- `SystemDictionaryPage.vue`
- `SystemNotificationPage.vue`

## 各文件作用

### DataDictionary.vue

数据字典页面入口。

作用：

- 引入 `SystemDictionaryPage.vue`
- 引入 `dataDictionaryConfig`
- 完成页面与配置绑定

### NotificationSetting.vue

通知设置页面入口。

作用：

- 引入 `SystemNotificationPage.vue`
- 引入 `notificationSettingConfig`
- 完成页面与配置绑定

### shared.ts

这个文件是当前 system 目录的配置中心。

负责：

- 定义页面组件需要的配置类型
- 把 `src/apis/system` 的接口方法装配成页面配置对象

当前主要导出：

- `dataDictionaryConfig`
- `notificationSettingConfig`

### menu.ts

负责 system 模块的菜单项定义。

当前保留菜单：

- 数据字典
- 通知设置

### SystemSectionLayout.vue

页面统一外层布局组件。

负责：

- 公共页面容器
- 统一的间距与外层样式

### SystemDictionaryPage.vue

数据字典页面的主组件。

负责：

- 左侧字典类型列表
- 右侧字典项表格
- 新增 / 编辑字典项
- 批量删除字典项

### SystemNotificationPage.vue

通知设置页面的主组件。

负责：

- 通知设置表单展示
- 开关、模板 ID、提示信息编辑
- 保存通知设置

## 页面是怎么串起来的

以数据字典页为例：

1. 路由进入 `DataDictionary.vue`
2. `DataDictionary.vue` 把 `dataDictionaryConfig` 传给 `SystemDictionaryPage.vue`
3. `SystemDictionaryPage.vue` 通过 `config` 调用 `src/apis/system/index.ts` 中的接口

通知设置页同理。

## 现在已经删除的页面

下面这些页面和对应配置已经从当前目录清理掉：

- 内部公告
- 系统参数
- 角色权限

如果后续又要恢复，不建议直接从 README 改起，应该先补：

1. 路由
2. 页面入口
3. `shared.ts` 配置
4. 组件
5. `src/apis/system` 接口

## 快速定位规则

- 改页面布局和交互：
  看 `components/`
- 改页面文案和接口绑定：
  看 `shared.ts`
- 改菜单：
  看 `menu.ts`
- 改接口：
  看 `src/apis/system`
