# 搜索栏组件使用说明

常规业务的搜索栏组件主要包括下面的元素

- 标题栏
- 搜索按钮
- 重置按钮
- 常规表单组件：文本输入框、数字输入框、下拉列表框、日期选择器
- 输入条件比较多支持部分条件折叠

**封装的主要思路就是数据来驱动搜索栏的渲染，不需要再编写复杂的界面代码，以及繁琐的交互处理逻辑**，组件演示代码在sample中已经书写，可以自己运行观察效果。

## 1 整体使用步骤

### 1.1 导入组件

导入组件关键代码如下

```html
<script setup lang="ts">
  // 导入组件和类型
  import MySearch from '@/components/mysearch/MySearch.vue'
  import type { MyFormItemAttr } from '@/components/myform/type'
</script>
```

### 1.2 定义属性

必须定义的属性包括：表单数据（model）与表单域数据（items），其他属性属于可选属性，具体属性模型定义如下：

```js
/**
 * 自定义搜索组件属性模型
 */
export interface MySearchProps<T extends Record<string, any>> {
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
}
```

表单数据定义示例如下所示

```html
<script setup lang="ts">
  import { reactive } from 'vue'

  // 业务数据模型，表单数据的模型根据业务自定义数据模型
  import type { SampleFormData } from '@/views/sample/type'

  // 导入组件和类型
  import MySearch from '@/components/mysearch/MySearch.vue'
  import type { MyFormItemAttr } from '@/components/myform/type'

  // 定义表单数据，定义数据的时候根据实际情况给默认值即可，也可以不给
  const formdata = reactive<SampleFormData>({
    zip: 610000
  })
</script>
```

表单域数据模型定义在`src\components\myform\type.ts`，下面列举一些部分代码

```js
/**
 * 自定义表单域属性模型
 */
export interface MyFormItemAttr {
  /** 表单域组件类型 */
  type: 'input' | 'number' | 'select' | 'date'
  /** 表单组件属性 */
  fprops?: MyFormBaseProps
  /** 对应model的键名，对应表单数据中的字段名称 */
  prop: string
  /** 表单域的标签 */
  label?: string
  /** 是否为必填项，如不设置，则会根据校验规则确认 */
  required?: boolean
  /** 表单域的提示信息 */
  rules?: Arrayable<FormItemRule>
  /** 用于控制该表单域下组件的默认尺寸 */
  size?: 'large' | 'default' | 'small' | ''
  /** 表单域标签的位置， 当设置为left或right时，则也需要设置label-width属性 */
  'label-position'?: 'left' | 'right' | 'top'
  /** 标签的长度,例如 '50px'，可以使用 auto */
  'label-width'?: string | number
}
// 组件的属性这里就省略了到对应的文件里面查看即可
```

其中比较重要的几个字段

- `type`：这个是用来指定表单组件类型，是一个枚举值，未来如果新增了表单类型，需要补充类型名称
  - `input`：输入框
  - `number`：数字输入框
  - `select`：下拉选择框
  - `date`：日期选择器
- `fprops`：这个是用来指定表单组件的属性数据，使用的是父类类型，其子类包括下面类型：
  - `MyFormInputProps`：输入框属性模型
  - `MyFormInputNumberProps`：数字输入框属性模型
  - `MyFormSelectProps`：下拉选择框属性模型
  - `MyFormDatePickerProps`：日期选择器属性模型
  - .........
- `prop`：这个用于表单组件和表单数据进行绑定，所以一定要和表单数据中的字段名称匹配
- `label`：表单域提示信息，就是表单组件前面的提示文本，如果没有提示文本，那么可以不传

基于表单域数据模型可以定义表单域数据了，示例如下

```html
<script setup lang="ts">
  import { reactive } from 'vue'
  // 导入组件和类型
  import MySearch from '@/components/mysearch/MySearch.vue'
  import type {
    MyFormItemAttr,
    MyFormInputProps,
    MyFormSelectProps,
    MyFormInputNumberProps,
    MyFormDatePickerProps
  } from '@/components/myform/type'

  // 定义表单域数据
  const formitemdata = reactive<MyFormItemAttr[]>([
    {
      type: 'input',
      prop: 'name',
      label: '姓名',
      rules: [{ required: true, message: '请输入姓名', trigger: 'change' }],
      fprops: {
        placeholder: '请输入姓名',
        clearable: true
      } as MyFormInputProps
    },
    {
      type: 'select',
      prop: 'country',
      label: '国家',
      rules: [{ required: true, message: '请选择国家', trigger: 'change' }],
      fprops: {
        placeholder: '请选择国家',
        options: [
          {
            label: '中国',
            value: 'CN'
          },
          {
            label: '美国',
            value: 'US'
          },
          {
            label: '日本',
            value: 'JP',
            disabled: true
          }
        ]
      } as MyFormSelectProps
    },
    {
      type: 'input',
      prop: 'state',
      label: '省份',
      required: true,
      fprops: {
        placeholder: '请输入省份'
      }
    },
    {
      type: 'input',
      prop: 'city',
      label: '城市',
      fprops: {
        placeholder: '请输入城市'
      }
    },
    {
      type: 'number',
      prop: 'zip',
      label: '邮编',
      fprops: {
        readonly: true,
        placeholder: '请输入邮编',
        max: 999999,
        min: 100000,
        step: 100
      } as MyFormInputNumberProps
    },
    {
      type: 'date',
      prop: 'date',
      label: '生日',
      fprops: {
        placeholder: '请选择生日',
        type: 'date',
        'value-format': 'YYYY-MM-DD'
      } as MyFormDatePickerProps
    }
  ])
</script>
```

关于组件上数据绑定：

- 通过`:model`绑定表单数据，如：`:model="formdata"`
- 通过`:items`绑定表单域数据，如：`:items="formitemdata"`

### 1.3 定义事件

定义的事件包括：

- @model-change【必须定义】：数据模型改变事件，用于处理子表单组件发生数据改变后，更新表单数据（因为组件数据流向是单向的，子组件不能改父组件数据），也可以在此事件中，根据改变的数据，做其他特殊操作（如：级联下拉选择框）
- @do-search【必须定义】：执行搜索事件，点击搜索按钮执行的事件，在这里完成发起后端网络请求

下面是一个事件处理逻辑函数示例

```html
<script setup lang="ts">
  // 引入示例后端接口
  import { listall } from '@/apis/sample/index'

  // 这里省略属性数据定义的代码

  /**
   * 模型数据改变事件回调
   * @param prop 字段名
   * @param val 字段值
   */
  function modelChange(prop: string, val: any) {
    formdata[prop] = val
    // 其他特殊处理
  }

  /**
   * 执行搜索事件回调
   */
  function doSearch() {
    listall(
      {
        pageIndex: 1,
        pageSize: 10,
        ...formdata
      },
      (data) => {
        // 这里将数据更新到你的显示组件数据模型上面
      },
      (error: any) => {
        console.log(error)
      }
    )
  }
</script>
```

关于组件上事件绑定：

- 通过`@model-change`绑定模型改变事件，如：` @model-change="modelChange"`
- 通过`@do-search`绑定搜索事件，如：`@do-search="doSearch"`

### 1.4 编写组件标签

在template中编写组件标签，并绑定数据和事件，示例代码如下

```html
<template>
  <my-search
    :model="formdata"
    :items="formitemdata"
    @model-change="modelChange"
    @do-search="doSearch"
  />
</template>
```

**TIPS：通过这几步你已经可以完成搜索栏的基础查询功能了，后面的说明都属于扩展操作，根据实际业务场景提供更为复杂的功能**

### 1.5 扩展属性

表单标题属性，直接通过`formtitle`指定即可，如：`formtitle="表单标题"`

表单属性数据模型，定义了如下字段

```js
/**
 * 自定义表单属性模型，注意：这里将rule和model属性剥离出去，方便操作
 */
export interface MyFormAttr {
  /** 显示表单域个数 */
  'show-count'?: number
  /** 行内表单模式 */
  inline?: boolean
  /** 是否禁用表单内所有组件 */
  disabled?: boolean
  /** 用于控制该表单内组件的尺寸 */
  size?: 'large' | 'default' | 'small' | ''
  /** 表单域标签的位置， 当设置为left或right时，则也需要设置label-width属性 */
  'label-position'?: 'left' | 'right' | 'top'
  /** 标签的长度,例如 '50px'，可以使用 auto */
  'label-width'?: string | number
  /** 表单域标签的后缀 */
  'label-suffix'?: string
}
```

在你的代码中可以选择性的给表单指定一些属性，如下示例

```html
<script setup lang="ts">
  import type { MyFormAttr } from '@/components/myform/type'
  // 定义表单属性数据
  const formattr: MyFormAttr = {
    'label-suffix': ':',
    'show-count': 2
  }
</script>
```

组件上通过`:formattr`绑定表单属性数据，如：`:formattr="formattr"`

表单验证规则属性，这个属于整体统一的定义验证规则，当然你也可以在表单域中单独定义，下面是定义示例

```js
import type { FormRules } from 'element-plus'

// 定义表单校验规则
const rules = reactive<FormRules<SampleFormData>>({
  name: [{ min: 2, max: 5, message: '长度在 2 到 5 个字符', trigger: 'change' }],
  country: [{ required: true, message: '请选择国家', trigger: 'change' }],
  state: [{ required: true, message: '请输入省份', trigger: 'blur' }]
})
```

组件上通过`:rules`绑定表单验证规则数据，如：`:rules="rules"`

完整绑定示例如下

```html
<template>
  <my-search
    formtitle="搜索组件示例"
    :model="formdata"
    :items="formitemdata"
    :formattr="formattr"
    :rules="rules"
    @model-change="modelChange"
    @do-search="doSearch"
  />
</template>
```

## 2 扩展功能

### 2.1 自定义页眉页脚

组件还支持自定义页眉页脚，分别对应`header`和`footer`两个插槽，两个插槽都可以输入`props`（组件的数据属性）和`table`（el-table实例），使用示例如下：

```html
<template>
  <my-search
    :model="formdata"
    :items="formitemdata"
    :formattr="formattr"
    :rules="rules"
    @model-change="modelChange"
    @do-search="doSearch"
  >
    <template #header>
      <h3>插槽使用示例</h3>
    </template>
    <template #footer>
      <el-text>带*的条件属于必填哦~道友要认真填写哦~</el-text>
    </template>
  </my-search>
</template>
```
