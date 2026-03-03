# 数据渲染表单

为了简化操作，这里做一些常规表单的数据渲染封装，方便动态生成表单相关自定义组件的动态创建表单

主要封装如下表单：

- `MyForm`：自定义动态表单组件
- `MyFormRender.vue`：表单组件渲染器，根据类型渲染不同`elment`表单组件
- `type.ts`：表单属性模型定义与统一导出表单组件模型定义
- `props`：组件属性模型定义文件存储目录
  - `formbase.ts`：表单组件公有属性
  - `input.ts`：输入框组件属性
  - `select.ts`：下拉选择框组件属性
  - `date.ts`：日期选择器组件属性
  - `radio.ts`：单选框组件属性
  - `checkbox.ts`：复选框组件属性
  - ..........

***TIPS：要加入新表单组件请自己封装对应的属性文件和组件渲染逻辑***

# 自定义表单组件

该组件主要实现动态渲染一个表单，然后支持返回、重置、提交功能植入，下面是使用它的关键步骤

## 1 导入组件

导入组件关键代码如下

```html
<script setup lang="ts">
// 导入组件和类型
import MyForm from '@/components/myform/MyForm.vue'
// 表单相关属性，按需导入即可
import type {
  MyFormItemAttr,
  MyFormInputProps,
  MyFormSelectProps,
  MyFormInputNumberProps,
  MyFormDatePickerProps,
  MyFormCheckBoxProps,
  MyFormCheckBoxGroupProps,
  MyFormRadioBoxGroupProps
} from '@/components/myform/type'
</script>
```

## 2 定义属性

必须定义的属性包括：表单数据（model）与表单域数据（items），其他属性属于可选属性，具体属性模型定义如下：

```js
/**
 * 自定义表单组件属性模型
 * 用于自定义表单组件（MyForm）传递属性和数据的模型
 */
export interface MyFormProps<T> {
  /** 表单数据 */
  model: T
  /** 表单域数据 */
  items: MyFormItemAttr[]
  /** 组件标题 */
  formtitle?: string
  /** 表单属性 */
  formattr?: MyFormAttr
  /** 表单验证规则 */
  rules?: FormRules
  /** 是否显示返回按钮，默认显示 */
  showback?: boolean
  /** 是否显示重置按钮，默认显示 */
  showreset?: boolean
  /** 提交按钮显示文字, 默认为 提交 */
  submittext?: string
  /** 是否禁用默认before-close逻辑，默认不禁用 */
  disableBeforeClose?: boolean
}
```

在定义表单数据前需要先定义表单数据模型，根据你业务需求来，示例如下

```html
<script setup lang="ts">
// 定义FormData的模型
interface FormData extends Record<string, any> {
  name?: string
  zero?: string
  count?: number
  time?: string
  type?: string[]
  support?: string
  describe?: string
}
</script>
```

然后再定义表单数据与表单域数据，注意：表单数据使用reactive包裹，示例如下

```html
<script setup lang="ts">
// 定义表单数据，表单数据也可以来自其他组件，如：表格组件选中了某条数据，传递过来也可
const formdata = reactive<FormData>({
  count: 1,
  support: 'wechat'
})

// 定义表单域数据，表单域属性去查看对应的属性ts文件定义即可
const formitemdata = reactive<MyFormItemAttr[]>([
  {
    type: 'input',
    prop: 'name',
    label: '活动名称',
    rules: [{ required: true, message: '请输入活动名称', trigger: 'change' }],
    fprops: {
      placeholder: '请输入活动名称',
      clearable: true
    } as MyFormInputProps
  },
  {
    type: 'select',
    prop: 'zero',
    label: '活动地点',
    rules: [{ required: true, message: '请选择国家', trigger: 'change' }],
    fprops: {
      placeholder: '请选择地点',
      options: [
        { label: '广场', value: '1', disabled: true },
        { label: '活动室', value: '2' },
        { label: '游泳馆', value: '3' }
      ]
    } as MyFormSelectProps
  },
  {
    type: 'number',
    prop: 'count',
    label: '活动数量',
    required: true,
    fprops: {
      width: '100%',
      placeholder: '请输入活动数量',
      max: 10,
      min: 1
    } as MyFormInputNumberProps
  },
  {
    type: 'date',
    prop: 'time',
    label: '活动时间',
    required: true,
    fprops: {
      placeholder: '请选择活动时间',
      type: 'datetimerange',
      'value-format': 'YYYY-MM-DD'
    } as MyFormDatePickerProps
  },
  {
    type: 'checkbox-group',
    prop: 'type',
    label: '活动类型',
    fprops: {
      checkboxes: [
        {
          label: '美食/餐厅线上活动',
          value: 'food',
          checked: true
        },
        {
          label: '地推活动',
          value: 'sale'
        },
        {
          label: '线下主题活动',
          value: 'theme'
        }
      ]
    } as MyFormCheckBoxGroupProps
  },
  {
    type: 'radio-group',
    prop: 'support',
    label: '活动支持',
    fprops: {
      radioboxes: [
        {
          label: '微信朋友圈',
          value: 'wechat'
        },
        {
          label: 'QQ群',
          value: 'qq'
        },
        {
          label: '微博',
          value: 'weibo'
        }
      ]
    } as MyFormRadioBoxGroupProps
  },
  {
    type: 'input',
    prop: 'describe',
    label: '活动描述',
    fprops: {
      placeholder: '请输入活动描述',
      type: 'textarea'
    } as MyFormInputProps
  }
])
</script>
```

***TIP：其他可选属性自己按需定义即可***

关于组件上数据绑定直接用 `:属性名` 绑定就行了，如`:model="formdata"`

## 3 定义事件

定义的事件包括：

- @do-submit：提交按钮执行事件，如果是查看方式打开表单组件，那么不需要绑定此事件
- @model-change：某个表单组件值发生改变时会触发此事件，如果你需要在某些表单值发生变化后做一些特殊处理，可以绑定该事件

下面是事件处理逻辑函数示例

```html
<script setup lang="ts">
/**
 * 提交修改
 * @param data 表单数据
 */
function doSubmit(data: FormData) {
  // 执行提交逻辑
  console.log(data)
}
/**
 * 表单组件属性值更新回调
 * @param prop 属性名
 * @param val 属性值
 */
function modelChange(prop: string, val: any) {
  // TIPS 你可以在这里更新父组件数据，当然也可以不更新父组件数据，根据实际业务来
  // 事件逻辑
}
</script>
```

关于组件上事件绑定：

- 通过`@do-submit`绑定提交事件，如：`@do-submit="doSubmit"`
- 通过`@model-change`绑定数据改变事件，如：`@model-change="modelChange"`

## 4 编写组件标签

在template中编写组件标签，并绑定数据和事件，示例代码如下

```html
<template>
  <my-form :items="formitemdata" :model="formdata" @do-submit="doSubmit" />
</template>
```

***TIPS：以上是表单组件的基本使用步骤，前面的的操作基本上可以完成大部分业务需求了***

## 5 插槽支持

表单组件也提供了插槽支持，用于特殊场景下自定义一些内容，

包含如下插槽

- `header`：头部栏插槽，输入数据包括 `form（el-form组件实例）, 所有定义属性`，用于定义头部工具按钮
- 表单项插槽，输入数据包括 `item、model`
  - `itemahead`：前置插槽，扩充默认表单组件，里面的内容将渲染到默认表单组件的前面
  - `itemdefault`：默认插槽，默认实现根据表单类型使用`my-form-render`组件渲染表单组件，如果要定制特殊表单（如：文件组件），覆盖它即可
  - `itemtail`：后置插槽，扩充默认表单组件，里面的内容将渲染到默认表单组件的后面

- `footer`：底部栏插槽，输入数据包括 `form（el-form组件实例）,所有定义属性`，用于扩充底部定义

下面是一个简单的示例

```html
<template>
    <my-form
      formtitle="插槽使用效果"
      :items="formitemdata"
      :model="formdata"
      @do-submit="doSubmit"
      @model-change="modelChange">
      <!-- 组件项后置插槽 -->
      <template #itemtail="{ item, model }">
        <!-- 渲染全选复选框 -->
        <template v-if="item.prop === 'type'">
          <el-text style="margin-left: 25px" class="hidden-xs-only"></el-text>
          <my-form-render
            :model="ckAllModel"
            :item="ckAllItem"
            @update:model="ckAllChange($event, model)"/>
        </template>
      </template>
    </my-form>
</template>
<script setup lang="ts">
import 'element-plus/theme-chalk/display.css'
import { reactive, ref } from 'vue'

import MyForm from '@/components/myform/MyForm.vue'
import MyFormRender from '@/components/myform/MyFormRender.vue'
// 表单相关属性
import type {
  MyFormItemAttr,
  MyFormInputProps,
  MyFormSelectProps,
  MyFormInputNumberProps,
  MyFormDatePickerProps,
  MyFormCheckBoxProps,
  MyFormCheckBoxGroupProps,
  MyFormRadioBoxGroupProps
} from '@/components/myform/type'

// 省略表单属性定义代码

// 定义一个全选复选框表单域
const ckAllItem = reactive<MyFormItemAttr>({
  type: 'checkbox',
  prop: 'ckall',
  fprops: {
    label: '全选',
    value: false,
    indeterminate: true
  } as MyFormCheckBoxProps
})
// 定义一个全选后复选框组应包含的值数组
const ckAllVal = ['food', 'sale', 'theme']
// 定义全选复选框对应表单数据模型
const ckAllModel = ref(false)
/**
 * 全选复选框改变事件处理
 * @param val 值
 * @param model 自定义表单组件本地数据模型
 */
function ckAllChange(val: any, model: FormData) {
  // 设置全选反选效果
  model.type = val ? ckAllVal : []
  const ckall = ckAllItem.fprops as MyFormCheckBoxProps
  ckall.indeterminate = false
}
/**
 * 表单组件属性值更新回调
 * @param prop 属性名
 * @param val 属性值
 */
function modelChange(prop: string, val: any) {
  // 如果是活动类型复选框
  if (prop === 'type') {
    // 获取选择数量
    const checkedCount = val.length
    // 更新全选复选框属性
    const ckall = ckAllItem.fprops as MyFormCheckBoxProps
    ckall.indeterminate = checkedCount > 0 && checkedCount < ckAllVal.length
    ckAllModel.value = checkedCount === ckAllVal.length
  }
}
</script>
```

