# 2026-03-12 P0 核心组件 API 分析报告

## CuiForm API 分析

### Props

| 属性名 | 类型 | 默认值 | 必需 | 说明 |
|--------|------|--------|------|------|
| fields | `CuiFormField<T>[]` | - | ✓ | 表单字段配置数组 |
| modelValue | `T` | - | ✓ | 表单数据（支持 v-model） |
| labelWidth | `string \| number` | `'100px'` | ✗ | 标签宽度 |
| inline | `boolean` | `false` | ✗ | 是否行内表单 |
| disabled | `boolean` | `false` | ✗ | 是否禁用整个表单 |
| labelPosition | `'left' \| 'right' \| 'top'` | `'right'` | ✗ | 标签位置 |

### Events

| 事件名 | 参数类型 | 说明 |
|--------|----------|------|
| update:modelValue | `T` | 表单数据更新事件 |
| submit | `T` | 表单提交事件 |
| reset | `void` | 表单重置事件 |

### Slots

| 插槽名 | 参数 | 说明 |
|--------|------|------|
| `[field.slot]` | `{ field: CuiFormField<T>, value: any, updateValue: (val: any) => void }` | 自定义字段渲染插槽（动态名称） |

### 暴露方法

| 方法名 | 参数 | 返回值 | 说明 |
|--------|------|--------|------|
| validate | - | `Promise<CuiFormValidateResult>` | 验证整个表单 |
| validateField | `prop: keyof T` | `Promise<boolean>` | 验证指定字段 |
| resetFields | - | `void` | 重置表单字段 |
| clearValidate | `props?: string \| string[]` | `void` | 清除验证状态 |
| submit | - | `Promise<CuiFormValidateResult>` | 提交表单 |

### 字段配置接口 (CuiFormField)

| 属性 | 类型 | 必需 | 说明 |
|------|------|------|------|
| prop | `keyof T & string` | ✓ | 字段属性名 |
| label | `string` | ✓ | 字段标签 |
| type | `'input' \| 'select' \| 'date' \| 'textarea' \| 'number'` | ✓ | 字段类型 |
| placeholder | `string` | ✗ | 占位符文本 |
| required | `boolean` | ✗ | 是否必填 |
| rules | `FormItemRule[]` | ✗ | 验证规则 |
| options | `CuiFormSelectOption[]` | ✗ | 选择框选项（type 为 select 时） |
| disabled | `boolean` | ✗ | 是否禁用 |
| defaultValue | `any` | ✗ | 默认值 |
| slot | `string` | ✗ | 自定义插槽名称 |

---

## CuiSearch API 分析

### Props

| 属性名 | 类型 | 默认值 | 必需 | 说明 |
|--------|------|--------|------|------|
| fields | `CuiSearchField[]` | - | ✓ | 搜索字段配置数组 |
| modelValue | `Record<string, any>` | - | ✓ | 表单值（支持 v-model） |
| inline | `boolean` | `true` | ✗ | 是否内联布局 |
| collapsible | `boolean` | `true` | ✗ | 是否可折叠高级搜索 |

### Events

| 事件名 | 参数类型 | 说明 |
|--------|----------|------|
| update:modelValue | `Record<string, any>` | 表单值更新事件 |
| search | `Record<string, any>` | 搜索按钮点击事件 |
| reset | `Record<string, any>` | 重置按钮点击事件 |

### Slots

无自定义插槽

### 字段配置接口 (CuiSearchField)

| 属性 | 类型 | 必需 | 说明 |
|------|------|------|------|
| prop | `string` | ✓ | 字段属性名 |
| label | `string` | ✓ | 字段标签 |
| type | `'input' \| 'select' \| 'date' \| 'daterange'` | ✓ | 字段类型 |
| placeholder | `string` | ✗ | 占位符文本 |
| options | `Array<{ label: string; value: any }>` | ✗ | 选项列表（用于 select 类型） |
| advanced | `boolean` | ✗ | 是否为高级搜索字段 |

---

## CuiTable API 分析

### Props

| 属性名 | 类型 | 默认值 | 必需 | 说明 |
|--------|------|--------|------|------|
| data | `T[]` | - | ✓ | 表格数据 |
| columns | `CuiTableColumn<T>[]` | - | ✓ | 列配置数组 |
| loading | `boolean` | `false` | ✗ | 是否显示加载状态 |
| showIndex | `boolean` | `false` | ✗ | 是否显示索引列 |
| showSelection | `boolean` | `false` | ✗ | 是否显示选择列 |
| stripe | `boolean` | `false` | ✗ | 是否显示斑马纹 |
| border | `boolean` | `true` | ✗ | 是否显示边框 |
| height | `string \| number` | - | ✗ | 表格高度 |
| maxHeight | `string \| number` | - | ✗ | 表格最大高度 |

### Events

| 事件名 | 参数类型 | 说明 |
|--------|----------|------|
| sort-change | `SortChangeEvent` | 排序变化事件 |
| selection-change | `SelectionChangeEvent<T>` | 选择变化事件 |
| row-click | `(row: T, column: any, event: Event)` | 行点击事件 |
| cell-click | `(row: T, column: any, cell: any, event: Event)` | 单元格点击事件 |

### Slots

| 插槽名 | 参数 | 说明 |
|--------|------|------|
| `[column.slot]` | `{ row: T, column: CuiTableColumn<T>, $index: number }` | 自定义列渲染插槽（动态名称） |

### 列配置接口 (CuiTableColumn)

| 属性 | 类型 | 必需 | 说明 |
|------|------|------|------|
| prop | `string` | ✗ | 列属性名 |
| label | `string` | ✓ | 列标题 |
| width | `string \| number` | ✗ | 列宽度 |
| minWidth | `string \| number` | ✗ | 最小列宽度 |
| sortable | `boolean \| 'custom'` | ✗ | 是否可排序 |
| fixed | `boolean \| 'left' \| 'right'` | ✗ | 列是否固定 |
| align | `'left' \| 'center' \| 'right'` | ✗ | 对齐方式 |
| formatter | `(row: T, column: any, cellValue: any, index: number) => any` | ✗ | 格式化函数 |
| slot | `string` | ✗ | 自定义插槽名称 |

---

## CuiDialogForm API 分析

### Props

| 属性名 | 类型 | 默认值 | 必需 | 说明 |
|--------|------|--------|------|------|
| visible | `boolean` | - | ✓ | 对话框是否显示 |
| modelValue | `T` | - | ✓ | 表单数据 |
| title | `string` | `'表单对话框'` | ✗ | 对话框标题 |
| width | `string \| number` | `'50%'` | ✗ | 对话框宽度 |
| showClose | `boolean` | `true` | ✗ | 是否显示关闭按钮 |
| closeOnClickModal | `boolean` | `false` | ✗ | 点击遮罩层是否关闭对话框 |
| fields | `CuiFormField<T>[]` | - | ✓ | 表单字段配置 |
| labelWidth | `string \| number` | `'100px'` | ✗ | 标签宽度 |
| inline | `boolean` | `false` | ✗ | 是否行内表单 |
| disabled | `boolean` | `false` | ✗ | 是否禁用整个表单 |
| labelPosition | `'left' \| 'right' \| 'top'` | `'right'` | ✗ | 标签位置 |
| confirmText | `string` | `'确认'` | ✗ | 确认按钮文本 |
| cancelText | `string` | `'取消'` | ✗ | 取消按钮文本 |
| confirmDisabled | `boolean` | `false` | ✗ | 是否禁用确认按钮 |
| loading | `boolean` | `false` | ✗ | 是否显示加载状态 |

### Events

| 事件名 | 参数类型 | 说明 |
|--------|----------|------|
| update:visible | `boolean` | 对话框显示状态更新事件 |
| update:modelValue | `T` | 表单数据更新事件 |
| submit | `T` | 表单提交事件 |
| cancel | `void` | 取消按钮点击事件 |
| open | `void` | 对话框打开事件 |
| close | `void` | 对话框关闭事件 |

### Slots

| 插槽名 | 参数 | 说明 |
|--------|------|------|
| default | - | 对话框顶部内容 |
| `field-[prop]` | `{ field: CuiFormField<T>, value: any, updateValue: (val: any) => void }` | 自定义字段渲染插槽（动态名称） |
| footer-center | - | 底部按钮中间的自定义内容 |

### 暴露方法

| 方法名 | 参数 | 返回值 | 说明 |
|--------|------|--------|------|
| resetForm | - | `void` | 重置表单字段 |
| setFormData | `data: any` | `void` | 设置表单数据 |
| formRef | - | `FormInstance` | 内部表单引用 |

---

## 关键特性总结

### 1. CuiForm
- 支持多种字段类型：input、select、date、textarea、number
- 完整的表单验证机制
- 支持自定义字段渲染插槽
- 暴露验证、重置等方法供父组件调用

### 2. CuiSearch
- 支持基础搜索和高级搜索分离
- 可折叠高级搜索功能
- 支持日期范围选择
- 内置搜索、重置按钮

### 3. CuiTable
- 支持排序、选择、行/单元格点击事件
- 灵活的列配置（宽度、对齐、固定等）
- 支持自定义列渲染插槽
- 支持加载状态、索引列、选择列

### 4. CuiDialogForm
- 组合 CuiDialog 和 CuiForm
- 完整的对话框生命周期事件
- 支持加载状态和按钮禁用
- 支持自定义字段和底部内容插槽
