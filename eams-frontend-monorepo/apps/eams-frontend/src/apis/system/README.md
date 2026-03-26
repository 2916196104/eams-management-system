# system API 说明

这个目录负责 `eams-frontend` 中“系统管理”相关页面的前端接口封装。

当前目录下主要有两个文件：

- `index.ts`
  负责具体接口调用、数据转换、失败兜底
- `type.ts`
  负责声明系统模块使用到的类型

---

## 1. 整体职责

`src/apis/system` 的目标不是只“发请求”，而是把下面几件事一起做好：

1. 调用后端真实接口
2. 把后端返回结构转换成页面组件更好用的前端结构
3. 在接口暂时不可用时，用本地 mock 数据兜底，保证页面还能开发和联调
4. 把系统管理几个子模块的接口统一收口，方便维护

---

## 2. index.ts 结构说明

`index.ts` 大体可以分成 4 个区域。

### 2.1 通用工具区

文件最前面这几个函数是公共辅助方法：

- `cloneValue`
  深拷贝本地 mock 数据，避免页面直接改到源数据
- `delay`
  mock 兜底时模拟异步请求延迟

这部分是给后面的 mock fallback 用的。

### 2.2 本地 mock 数据区

中间有很多变量，例如：

- `announcements`
- `settingGroups`
- `roles`
- `permissionTree`
- `dictCategories`
- `dictItems`
- `notificationTemplates`

这些都是“后端失败时的备用数据源”。

也就是说，现在这个文件不是纯接口文件，而是：

- 优先走真实后端
- 请求失败时回退到本地数据

这样做的好处是联调阶段更稳，不会因为单个接口没通导致整个页面完全不可用。

### 2.3 业务接口区

这一段是最核心的区域，按业务模块分组。

#### 内部公告

- `listInternalAnnouncements`
- `saveInternalAnnouncement`
- `deleteInternalAnnouncements`

作用：

- 获取公告分页
- 新增 / 编辑公告
- 删除公告

#### 系统参数

- `listSystemSettingGroups`
- `updateSystemSetting`

作用：

- 先取设置组，再取每个组下的配置项
- 保存单个配置项

这里还有一个缓存：

- `systemSettingOptionMap`

作用：

- 把“设置项 id -> 后端原始 DTO”缓存起来
- 保存时可以带上后端要求的完整字段

#### 角色权限

- `listRoles`
- `saveRole`
- `deleteRole`
- `listRoleMembers`
- `addRoleMember`
- `removeRoleMember`
- `getPermissionTree`
- `updateRolePermissions`

作用：

- 角色列表、角色保存、角色删除
- 查询某角色下员工
- 给角色加员工
- 从角色移除员工
- 查询权限树
- 保存角色权限

这里的特点是：

- 角色列表和员工列表是分开的
- 权限树也会做一层转换，变成页面树组件直接可用的数据

#### 数据字典

- `listDictionaryCategories`
- `listDictionaryItems`
- `saveDictionaryItem`
- `deleteDictionaryItems`
- `saveDictionaryCategory`
- `deleteDictionaryCategories`

作用：

- 获取字典类型
- 获取某个类型下的字典项
- 新增 / 编辑字典项
- 批量删除字典项
- 新增 / 编辑字典类型
- 删除字典类型

#### 通知设置

- `listNotificationTemplates`
- `updateNotificationTemplate`

虽然函数名还保留了早期的 `Template` 命名，但现在实际已经是：

- 获取单个通知设置对象
- 保存单个通知设置对象

也就是说这里名字偏旧，语义已经是“通知设置”，不是多模板表格那套了。

### 2.4 数据转换函数区

后面一大段 `normalize / map / infer` 函数，属于“适配层”。

常见用途：

- 把后端 DTO 转成页面组件要的结构
- 把页面值转回后端要求的结构
- 根据字段内容推断组件类型

例如：

- `normalizeRoleRecords`
  把角色接口返回数据转成页面用的 `RoleRecord`
- `normalizeRoleMembers`
  规范化员工列表
- `buildPermissionTreeData`
  把权限接口返回值转成树组件可直接使用的数据
- `mapSystemSettingItem`
  把系统参数详情转成页面设置项
- `inferSettingValueType`
  自动判断配置项应该用开关、输入框、数字框还是时间选择器
- `mapDictionaryItem`
  把字典项 DTO 转成页面表格结构
- `mapFallbackNoticeSetting`
  通知设置接口失败时，把旧 mock 数据映射成当前页面能吃的结构

这一块的作用非常重要：

- 页面尽量少关心后端原始结构
- 后端字段变化时，优先改这里，不要让变化扩散到整个页面

---

## 3. type.ts 结构说明

`type.ts` 主要存放两类类型。

### 3.1 页面使用的前端模型

这些类型更偏“页面直接消费”：

- `InternalAnnouncement`
- `SystemSettingItem`
- `SystemSettingGroup`
- `RoleRecord`
- `PermissionNode`
- `DictionaryCategory`
- `DictionaryItem`
- `NoticeSettingDTO`

特点：

- 字段名更接近页面组件
- 可能已经不是后端原始结构

### 3.2 后端 DTO / VO 类型

这些类型更偏“接口原始数据”：

- `SettingDTO`
- `SettingOptionDTO`
- `RolepermDTO`
- `RolepermStaffDTO`
- `PermissionDTO`
- `PermissionGroupVO`
- `DictTypeDTO`
- `DatadictVO`

特点：

- 字段名与后端文档基本一致
- 用于接口入参 / 出参建模

### 3.3 中间适配类型

例如：

- `RolePermissionTreeData`

这个类型不是纯后端 DTO，也不是纯页面原子字段，而是“接口结果经过整理后的复合结构”。

它的作用是：

- 一次性返回权限树
- 已勾选节点
- 权限映射表

方便角色权限页直接使用。

---

## 4. 当前代码里各模块的真实接口大意

这里不写完整文档，只写代码里已经接入的方向，便于快速定位。

### 内部公告

- 公告查询
- 公告保存
- 公告删除

### 系统参数

- `GET /sys/sysparam`
- `GET /sys/sysparam/{id}`
- `PUT /sys/sysparam`

### 角色权限

- `GET /sys/roleperm/nameList`
- `POST /sys/roleperm/save`
- `DELETE /sys/roleperm/delete/role/{id}`
- `GET /sys/roleperm`
- `POST /sys/roleperm?roleId=...`
- `DELETE /sys/roleperm/{staffId}?roleId=...`
- `GET /sys/roleperm/query/list/permission`
- `GET /sys/roleperm/query/list/select/{roleId}`
- `POST /sys/roleperm/modify/{roleId}`

### 数据字典

- `GET /sys/dict/type-name-list`
- `GET /sys/dict/list-by-dict-id`
- `POST /sys/dict/save-dict`
- `PUT /sys/dict/update-dict`
- `DELETE /sys/dict/delete-dict`
- `POST /sys/dict/save-dict-type`
- `DELETE /sys/dict/remove-dict-type`

### 通知设置

- `GET /noticesetting`
- `POST /noticesetting/savesetting`

说明：

- 这里的通知设置 `GET` 路径是当前前端按现有确认先接的
- 如果后端最终路径不同，优先改 `index.ts` 中这两处函数即可

---

## 5. mock 兜底机制怎么理解

这个文件里很多接口都是这种写法：

1. 先 `try` 请求真实后端
2. 如果失败，进入 `catch`
3. 回退到本地 mock 数据

这意味着：

- 页面开发阶段更稳定
- 后端偶发失败时还能继续看界面
- 但也要注意：如果你看到页面正常显示，不一定代表真实接口没问题，也可能是走了 fallback

如果某次联调需要强制暴露真实接口问题，可以把对应接口的 fallback 临时去掉。

---

## 6. 后续维护建议

### 新增接口时建议怎么写

建议保持现在这个顺序：

1. 先在 `type.ts` 加 DTO 类型
2. 在 `index.ts` 写真实接口调用
3. 如果页面结构和后端结构不同，补一个 `map / normalize` 函数
4. 如果当前阶段需要保底，再加 mock fallback

### 什么时候改 type.ts

下面几种情况优先改 `type.ts`：

- 后端字段新增
- 后端字段类型变化
- 页面需要新的中间结构

### 什么时候改转换函数

下面几种情况优先改 `map / normalize`：

- 页面展示字段和后端字段不一致
- 后端返回结构变了，但页面不想跟着大改
- 某些值需要推断控件类型或格式

### 什么时候改页面，不改接口层

如果只是：

- 文案变化
- 排版变化
- 交互形式变化

通常先改 `views/system/components`，不要先动 `apis/system`。

---

## 7. 你后面最常用的定位方式

如果你想快速找某个功能该改哪里，可以按下面找：

- 改接口地址 / 请求参数 / 返回映射：
  看 `index.ts`
- 改类型：
  看 `type.ts`
- 改系统页面展示：
  看 `src/views/system/components`
- 改页面和接口的配置绑定：
  看 `src/views/system/shared.ts`

---

## 8. 当前已知注意点

- `index.ts` 里还保留了一些早期 mock 数据和旧命名，这是为了 fallback，不代表页面一定还在走旧逻辑
- `NotificationTemplate` 现在主要用于旧通知 mock 兼容，真实通知页已经转成 `NoticeSettingDTO`
- 如果后端接口最终全部稳定，可以考虑逐步删掉本地 mock 区，让文件更干净

---

## 9. 一句话理解这个目录

`src/apis/system` 是“系统管理模块的接口适配层”：  
它负责把后端接口、前端页面、mock 兜底、数据转换这几件事连接起来。
