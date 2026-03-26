# system API 说明

这个目录目前只保留了两个系统管理子模块的接口封装：

- 数据字典
- 通知设置

目录下文件说明：

- `index.ts`
  具体接口调用与数据转换
- `type.ts`
  类型定义

## index.ts 分区

### 通用工具

- `cloneValue`
  本地 mock 兜底时做深拷贝
- `delay`
  模拟异步延迟

### 本地 mock 数据

目前保留两组兜底数据：

- `dictCategories`、`dictItems`
  数据字典接口失败时使用
- `noticeSetting`
  通知设置接口失败时使用

### 数据字典接口

- `listDictionaryCategories`
  获取字典类型列表
- `listDictionaryItems`
  获取某个字典类型下的字典项
- `saveDictionaryItem`
  新增 / 编辑字典项
- `deleteDictionaryItems`
  批量删除字典项
- `saveDictionaryCategory`
  新增 / 编辑字典类型
- `deleteDictionaryCategories`
  删除字典类型

### 通知设置接口

- `listNotificationTemplates`
  获取通知设置对象
- `updateNotificationTemplate`
  保存通知设置对象

说明：

- 这里函数名还沿用了早期命名 `listNotificationTemplates`
- 但现在实际语义已经是“单个通知设置”

### 数据转换函数

- `mapDictionaryItem`
  把后端字典项 DTO 转成页面可直接使用的结构

## type.ts 分区

### 数据字典相关

- `DictionaryCategory`
- `DictionaryItem`
- `DictTypeDTO`
- `DatadictVO`

### 通知设置相关

- `NoticeSettingDTO`

## 当前真实接口

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

## 维护建议

- 改接口地址、参数、返回结构：
  优先看 `index.ts`
- 改类型：
  优先看 `type.ts`
- 如果某个接口已经稳定且不再需要兜底：
  可以考虑删除对应 mock 数据
