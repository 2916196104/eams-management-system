# system API 说明

当前 `src/apis/system` 已经覆盖 4 组系统页面接口：

- 数据字典
- 通知设置
- 节假日管理
- 操作日志

## 目录说明

- `index.ts`
  具体接口调用、返回值整理、部分本地兜底逻辑
- `type.ts`
  system 模块使用的类型定义

## index.ts 分区

### 通用工具

- `cloneValue`
  用于本地兜底数据的深拷贝
- `delay`
  用于模拟异步延迟

### 本地兜底数据

当前保留的本地兜底数据有：

- `dictCategories`
- `dictItems`
- `noticeSetting`
- `holidayRecords`
- `operationLogRecords`

说明：

- 当接口请求失败时，这些数据用于页面可用性兜底
- 不代表正式业务数据来源

### 数据字典相关接口

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

### 通知设置相关接口

- `listNotificationTemplates`
  获取通知设置
- `updateNotificationTemplate`
  保存通知设置

说明：

- 函数名 `listNotificationTemplates` 是历史命名
- 当前实际语义已经是“获取单个通知设置”

### 节假日管理相关接口

- `listHolidays`
  获取节日列表
- `addHoliday`
  添加节日
- `deleteHoliday`
  删除节日

### 操作日志相关接口

- `listOperationLogs`
  按条件 + 分页获取操作日志

### 数据转换函数

- `mapDictionaryItem`
  将后端字典项结构转换成页面可直接使用的结构

## type.ts 分区

### 数据字典相关

- `DictionaryCategory`
- `DictionaryItem`
- `DictTypeDTO`
- `DatadictVO`

### 通知设置相关

- `NoticeSettingDTO`

### 节假日管理相关

- `HolidayDTO`

### 操作日志相关

- `OptlogDTO`

## 当前已接真实接口

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

### 节假日管理

- `GET /sys/holiday`
- `POST /sys/holiday`
- `DELETE /sys/holiday/{id}`

### 操作日志

- `GET /sys/optlog`

## 维护建议

- 改接口地址、参数、返回处理：优先看 `index.ts`
- 改类型：优先看 `type.ts`
- 如果某个接口已经稳定且不再需要兜底：
  可以考虑删除对应 mock 数据
