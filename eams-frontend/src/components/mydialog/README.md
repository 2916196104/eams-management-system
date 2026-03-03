# 对话框组件使用说明

主要将对话框显示状态控制封装到组件中，以及集成表单到对话框中，方便实现常规列表数据查看、新增、修改。

对话框组件会暴露如下函数给对话框实例使用

- `openDialog`：用了打开对话框
- `closeDialog`：用来关闭对话框

**封装的主要思路就是数据来驱动对话框的渲染，不需要再编写复杂的界面代码，以及繁琐的交互处理逻辑**，组件演示代码在sample中已经书写，可以自己运行观察效果。

## 1 表单对话框

### 1.1 导入组件

导入组件关键代码如下

```html
<script setup lang="ts">
// 导入组件和类型
import MyFormDialog from '@/components/mydialog/MyFormDialog.vue'
// 对话框属性
import type { MyFormDialogProps } from '@/components/mydialog/type'
// 表单相关属性，按需导入即可
import type {
  MyFormItemAttr,
  MyFormInputProps,
  MyFormSelectProps,
  MyFormInputNumberProps,
  MyFormDatePickerProps
} from '@/components/myform/type'
</script>
```

### 1.2 定义属性

必须定义的属性包括：渲染数据（`data`）与表单域数据（`formitemdata`），其他属性属于可选属性，具体属性模型定义如下：

```js
/**
 * 对话框属性模型，注意：这里将model-value/v-model、before-close属性剥离出去，方便操作
 */
export interface MyDialogProps<T> {
  /** 渲染需要用到的数据 */
  data: T
  /** 对话框的标题 */
  title?: string
  /** 对话框的宽度，默认值为50% */
  width?: string | number
  /** 是否为全屏 */
  fullscreen?: boolean
  /** 为Dialog启用可拖拽功能 */
  draggable?: boolean
  /** 是否可以通过点击modal关闭Dialog */
  'close-on-click-modal'?: boolean
  /** 是否可以通过按下ESC关闭Dialog */
  'close-on-press-escape'?: boolean
  /** 是否显示关闭按钮 */
  'show-close'?: boolean
  /** 是否让Dialog的header和footer部分居中排列 */
  center?: boolean
  /** 是否水平垂直对齐对话框 */
  'align-center'?: boolean
}

/**
 * 表单对话框属性，基于对话框扩展属性
 */
export interface MyFormDialogProps<T extends Record<string, any>> extends MyDialogProps<T> {
  /** 提交按钮文字 */
  submitText?: string
  /** 取消按钮文字 */
  cancelText?: string
  /** 提交按钮是否为危险按钮 */
  danger?: boolean
  /** 是否开启重置按钮 */
  reset?: boolean
  /** 是否禁用默认before-close逻辑 */
  disableBeforeClose?: boolean
  /** 表单校验规则数据 */
  rules?: FormRules<T>
  /** 表单属性数据 */
  formattr?: MyFormAttr
  /** 表单域数据 */
  formitemdata: Array<MyFormItemAttr>
}
```

下面是定义对话框属性的示例代码

```html
<script setup lang="ts">
// 定义对话框属性
// eslint-disable-next-line @typescript-eslint/no-unused-vars
const formDialogProps = reactive<MyFormDialogProps<SampleFormData>>({
  // 表单数据
  data: reactive<SampleFormData>({}),
  // 表单域数据
  formitemdata: reactive<MyFormItemAttr[]>([
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
        width: '100%',
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
        width: '100%',
        placeholder: '请选择生日',
        type: 'date',
        'value-format': 'YYYY-MM-DD'
      } as MyFormDatePickerProps
    },
    {
      type: 'file',
      prop: 'avatar',
      label: '头像'
    }
  ]),
  // 表单属性
  formattr: {
    // 当这个值为true时表单元素全部禁止修改,对话框也不在显示提交和重置按钮
    disabled: false,
    'label-width': '80px'
  },
  title: '新增数据',
  width: '35vw',
  reset: true
})
</script>
```

关于组件上数据绑定直接用`:`绑定就行了，如`:="formDialogProps"`

***TIPS：对话框属性大部分是可选属性，根据你实际需求指定属性即可***

### 1.3 定义事件

定义的事件包括：

- @confirm：提交按钮执行事件，如果是查看方式打开表单，那么不需要绑定此事件
- @model-change：某个表单组件值发生改变时会触发此事件，如果你需要在某些表单值发生变化后做一些特殊处理，可以绑定该事件

下面是事件处理逻辑函数示例

```html
<script setup lang="ts">
// 定义对话框引用
const formDialog = ref()
/**
 * 提交修改
 * @param data 表单数据
 */
function onSubmit(data: SampleFormData) {
  // 执行提交逻辑
  console.log(data)
  // 提交完了后关闭对话框
  formDialog.value.closeDialog()
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

- 通过`@confirm`绑定提交事件，如：`@confirm="onSubmit"`
- 通过`@model-change`绑定数据改变事件，如：`@model-change="modelChange"`

### 1.4 编写组件标签

在template中编写组件标签，并绑定数据和事件，示例代码如下

```html
<template>
  <my-form-dialog ref="formDialog" :="formDialogProps" @confirm="onSubmit" />
</template>
```

***TIPS：以上是表单对话框的基本使用步骤，前面的的操作基本上可以完成大部分业务需求了***

### 1.5 插槽支持

表单对话框也提供了插槽支持，用于特殊场景下自定义一些内容，

包含如下插槽

- `header`：标题栏插槽，输入数据包括 `close, titleClass, titleId, 所有定义属性`
- 表单项插槽，输入数据包括 `item、model（组件本地数据模型）`
  - `itemahead`：前置插槽，扩充默认表单组件，里面的内容将渲染到默认表单组件的前面
  - `itemdefault`：默认插槽，默认实现根据表单类型使用`my-form-render`组件渲染表单组件，如果要定制特殊表单（如：文件组件），覆盖它即可
  - `itemtail`：后置插槽，扩充默认表单组件，里面的内容将渲染到默认表单组件的后面

- `footer`：底部栏插槽，输入数据包括 `dialog（对话框实例）、form（el-form组件实例）、所有定义属性`，用于定义底部工具按钮

下面是一个简单的示例

```html
<template>
  <my-form-dialog ref="formDialog" :="formDialogProps" @confirm="onSubmit">
    <template #itemdefault="{ item }">
      <!-- 处理头像使用文件上传组件 -->
      <el-upload
        v-if="item.prop === 'avatar'"
        class="avatar-uploader"
        action="https://jsonplaceholder.typicode.com/posts/"
        :show-file-list="false"
        :on-success="handleAvatarSuccess"
        :before-upload="beforeAvatarUpload">
        <img v-if="imageUrl" :src="imageUrl" class="avatar" />
        <el-icon v-else class="avatar-uploader-icon"><IconPlus/></el-icon>
      </el-upload>
    </template>
  </my-form-dialog>
</template>
<script setup lang="ts">
import type { UploadProps } from 'element-plus'

// 图片地址
const imageUrl = ref('')
/**
 * 上传成功逻辑
 * @param response 响应数据
 * @param uploadFile 上传的文件
 */
const handleAvatarSuccess: UploadProps['onSuccess'] = (response, uploadFile) => {
  imageUrl.value = URL.createObjectURL(uploadFile.raw!)
  console.log(response)
}

/**
 * 上传前执行逻辑
 * @param rawFile 选择的文件
 */
const beforeAvatarUpload: UploadProps['beforeUpload'] = (rawFile) => {
  if (rawFile.type !== 'image/jpeg') {
    ElMessage.error('Avatar picture must be JPG format!')
    return false
  } else if (rawFile.size / 1024 / 1024 > 2) {
    ElMessage.error('Avatar picture size can not exceed 2MB!')
    return false
  }
  return true
}
</script>
```

## 2 自定义插槽

有时候需要自定义对话框内容，封装组件支持与原生对话框组件一样的插槽。

包含如下插槽

- `header`：标题栏插槽，输入数据包括 `close, titleClass, titleId, 所有定义属性`
- `default`：内容插槽，输入数据包括 `data（渲染数据对象）`，用于定义对话框主体内容
- `footer`：底部栏插槽，用于定义底部工具按钮

下面是一个简单的自定义插槽的示例

```html
<template>
  <!-- 自定义对话框 -->
  <my-dialog ref="cusdialog" :="cusprops">
    <!-- 定义标题栏 -->
    <template #header="{ close, fullscreen, title }">
      <section class="cus-dialog-title">
        <section>{{ title }}</section>
        <section>
          <el-button
            link
            type="primary"
            :icon="fullscreen ? 'IconMinus' : 'IconFullScreen'"
            @click="cusprops.fullscreen = !fullscreen"
          />
          <el-button link type="danger" icon="IconClose" @click="close()" />
        </section>
      </section>
    </template>
    <!-- 定义内容区 -->
    <template #default>
      <el-table :data="gridData" :height="cusprops?.fullscreen ? '85vh' : '100%'">
        <el-table-column property="name" label="Name" />
        <el-table-column property="date" label="Date" />
        <el-table-column property="address" label="Address" />
      </el-table>
    </template>
    <!-- 定义底部栏 -->
    <template #footer>
      <el-text class="cus-dialog-footer" type="success" tag="i">
        Self element set width 100px Squeezed by parent element The -webkit-line-clamp CSS property
        allows limiting of the contents of a block to the specified number of lines.
      </el-text>
    </template>
  </my-dialog>
</template>

<script setup lang="ts">
// 导入组件和类型
import MyDialog from '@/components/mydialog/MyDialog.vue'
import type { MyDialogProps } from '@/components/mydialog/type'
// 定义对话框引用
const cusdialog = ref()
// 定义对话框属性
const cusprops = reactive<MyDialogProps<string>>({
  data: '',
  title: '自定义对话框',
  draggable: true
})
// 定义测试表格数据
const gridData = [
  {
    name: 'John Smith',
    date: '2016-05-02',
    address: 'No.1518,  Jinshajiang Road, Putuo District'
  },
  {
    name: 'John Smith',
    date: '2016-05-04',
    address: 'No.1518,  Jinshajiang Road, Putuo District'
  },
  {
    name: 'John Smith',
    date: '2016-05-01',
    address: 'No.1518,  Jinshajiang Road, Putuo District'
  },
  {
    name: 'John Smith',
    date: '2016-05-03',
    address: 'No.1518,  Jinshajiang Road, Putuo District'
  }
]
</script>
```

## 3 对话框事件

有时候需要在对话框执行某个事件时执行一些特殊逻辑，封装组件支持与原生对话框组件一样的事件。

包含如下事件：

- open：对话框打开的回调
- open-auto-focus：输入焦点聚焦在对话框内容时的回调
- opened：对话框打开动画结束时的回调
- close：对话框关闭的回调
- close-auto-focus：输入焦点从对话框内容失焦时的回调
- closed：对话框关闭动画结束时的回调

还有一个特殊属性`before-close`这个属性值要也是一个函数`(done: DoneFn) => void`，它的官方说法是（关闭前的回调，会暂停对话框的关闭，回调函数内执行done参数方法的时候才是真正关闭对话框的时候）。***注意：这个函数只会在点击它对话框提供的x按钮时候才会触发***。这个属性根据你的需要来设置吧，在表单对话框中内部默认实现是关闭的时候检查表单是否有内容变化，有内容变化就提示用户是否确定退出，没有变化正常关闭。

下面是一个简单的使用示例

```html
<template>
  <!-- 自定义对话框事件支持 -->
  <my-dialog
    ref="dialog"
    :="props"
    :before-close="handleClose"
    @open="console.log('open')"
    @open-auto-focus="console.log('open-auto-focus')"
    @opened="console.log('opened')"
    @close="console.log('close')"
    @close-auto-focus="console.log('close-auto-focus')"
    @closed="console.log('closed')"
  />
</template>
<script setup lang="ts">
import { ElMessage } from 'element-plus'
// 导入组件和类型
import MyDialog from '@/components/mydialog/MyDialog.vue'
import type { MyDialogProps } from '@/components/mydialog/type'
// 定义对话框引用
const dialog = ref()
// 定义对话框属性
// eslint-disable-next-line @typescript-eslint/no-unused-vars
const props = reactive<MyDialogProps<string>>({
  data: '',
  title: '对话框事件支持演示',
  'show-close': true
})
/**
 * 模拟操作失败阻止关闭
 */
let i = 0
function handleClose(done: () => void) {
  i++
  if (i % 2 === 0) done()
  else ElMessage.warning('操作失败，请重试')
}
</script>
```

