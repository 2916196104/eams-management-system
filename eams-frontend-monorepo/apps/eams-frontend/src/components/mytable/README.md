# 表格组件使用说明

此表格组件主要实现了分页插件与某些常规操作的封装，**封装的主要思路就是数据来驱动表格的渲染，不需要再编写复杂的界面代码，以及繁琐的交互处理逻辑**，组件演示代码在sample中已经书写，可以自己运行观察效果。

## 1 整体使用步骤

### 1.1 导入组件

导入组件关键代码如下

```html
<script setup lang="ts">
  // 引入组件和类型
  import MyTable from '@/components/mytable/MyTable.vue'
  import { createPageDTO, type PageDTO, type MyTableColumn } from '@/components/mytable/type'
</script>
```

### 1.2 定义必须属性

使用表格必须定义的属性包括：表格列数据与表格数据

表格列数据模型，定义了如下字段

```js
/**
 * 自定义表格列数据模型
 */
export interface MyTableColumn {
  /** 列标题 */
  label: string
  /** 列字段名 */
  prop: string
  /** 列宽度，不指定自适应宽度 */
  width?: string
  /** 最小列宽度 */
  'min-width'?: number
  /** 是否固定列 */
  fixed?: 'left' | 'right'
  /** 当内容过长被隐藏时显示tooltip */
  'show-overflow-tooltip'?: boolean
  /** 列对齐方式 */
  align?: 'left' | 'center' | 'right'
}
```

表格数据模型，定义了如下字段

```js
/**
 * 分页数据模型
 */
export interface PageDTO<T> {
  /** 页码 */
  pageIndex: number
  /** 每页数据条数 */
  pageSize: number
  /** 数据总条数 */
  total: number
  /** 数据总页数 */
  pages?: number
  /** 当前页数据 */
  rows?: Array<T>
}
```

基于这两个模型，我们需要给表格组件定义类似下面的数据

```js
/**
 * 定义示例表单数据模型
 */
export interface SampleFormData extends Record<string, any> {
  /** 数据唯一标识 */
  id?: number
  /** 姓名 */
  name?: string
  /** 国家 */
  country?: string
  /** 省份 */
  state?: string
  /** 城市 */
  city?: string
  /** 地址 */
  address?: string
  /** 邮编 */
  zip?: number
  /** 生日 */
  date?: string
}
```

```html
<script setup lang="ts">
  import { ref } from 'vue'

  // 引入组件和类型
  import MyTable from '@/components/mytable/MyTable.vue'
  import { createPageDTO, type PageDTO, type MyTableColumn } from '@/components/mytable/type'

  // 业务数据模型
  import type { SampleFormData } from '@/apis/sample/type'

  // 定义列数据
  const tabdatacolumns: MyTableColumn[] = [
    {
      prop: 'name',
      label: '姓名',
      width: '80px',
      fixed: 'left'
    },
    {
      prop: 'date',
      label: '生日',
      width: '200px',
      fixed: 'left',
      align: 'center'
    },
    {
      prop: 'state',
      label: '省份',
      width: '150px'
    },
    {
      prop: 'city',
      label: '城市',
      width: '200px'
    },
    {
      prop: 'address',
      label: '详细地址',
      width: '600px',
      'show-overflow-tooltip': true
    },
    {
      prop: 'zip',
      label: '邮编',
      width: '200px'
    },
    {
      prop: 'tag',
      label: '标签'
    }
  ]

  // 定义表格数据
  const tabdata = ref<PageDTO<SampleFormData>>(createPageDTO())
</script>
```

关于组件上数据绑定：

- 通过`:tabdatacolumns`绑定表格列数据，如：`:tabdatacolumns="tabdatacolumns"`
- 通过`:tabdata`绑定表格数据，如：`:tabdata="tabdata"`

### 1.3 定义必须事件

使用表格必须定义的事件是分页组件事件，这个事件用于处理分页组件上点击后执行表格数据刷新显示

下面是一个事件处理逻辑函数示例，这里演示使用网络加载数据

```html
<script setup lang="ts">
  import { ref, onMounted } from 'vue'
  // 引入示例后端接口
  import { listall } from '@/apis/sample/index'

  // 引入组件和类型
  import MyTable from '@/components/mytable/MyTable.vue'
  import { createPageDTO, type PageDTO, type MyTableColumn } from '@/components/mytable/type'

  // 业务数据模型
  import type { SampleFormData } from '@/apis/sample/type'

  // 这里省略必须属性数据定义的代码

  /**
   * 加载数据
   */
  function loadData() {
    listall(
      {
        pageIndex: tabdata.value.pageIndex,
        pageSize: tabdata.value.pageSize
      },
      (data) => {
        tabdata.value = data
      },
      (error: any) => {
        console.log(error)
      }
    )
  }

  /**
   * 分页组件改变触发数据刷新
   * @param data 请求数据
   */
  function handlePageChange(data: PageDTO<SampleFormData>) {
    tabdata.value.pageIndex = data.pageIndex
    tabdata.value.pageSize = data.pageSize
    loadData()
  }

  /**
   * 组件挂载钩子函数
   */
  onMounted(() => {
    loadData()
  })
</script>
```

组件上通过`@page-change`绑定分页组件事件处理函数，如：`@page-change="handlePageChange"`

### 1.4 编写组件标签

在template中编写组件标签，并绑定数据和事件，示例代码如下

```html
<template>
  <my-table :tabdatacolumns="tabdatacolumns" :tabdata="tabdata" @page-change="handlePageChange" />
</template>
```

**TIPS：通过这几步你已经可以完成表格查询的基础查询功能了，后面的说明都属于扩展操作，根据实际业务场景提供更为复杂的功能**

### 1.5 扩展属性

扩展属性主要包括表格标题、表格属性以及功能属性

表格标题属性，直接通过`tabtitle`指定即可，如：`tabtitle="表格标题"`

表格属性数据模型，定义了如下字段

```js
/**
 * 自定义表格属性模型
 */
export interface MyTableAttr {
  /** 分页组件大小, 默认default */
  psize?: 'large' | 'default' | 'small'
  /** 表格高度，不指定自动适配表格高度*/
  height?: number
  /** 表格最大高度*/
  'max-height'?: number
  /** 是否显示斑马纹, 默认显示 */
  stripe?: boolean
  /** 是否显示纵向边框, 默认不显示 */
  border?: boolean
  /** 是否高亮当前选择行, 默认高亮 */
  'highlight-current-row'?: boolean
}
```

在你的代码中可以选择性的给表格指定一些属性，如下示例

```html
<script setup lang="ts">
  import type { MyTableAttr } from '@/components/mytable/type'
  // 定义表格属性
  const tabattr: MyTableAttr = {
    height: 200,
    'max-height': 400
  }
</script>
```

组件上通过`:tabattr`绑定表格属性数据，如：`:tabattr="tabattr"`

功能属性主要包括如下字段

```js
/** 是否显示序号列，默认不显示 */
istabseq: {
  type: Boolean,
  default: false
},
/** 是否开启多选，默认不开启 */
istabmultiple: {
  type: Boolean,
  default: false
},
/** 是否开启分页，默认开启 */
istabpage: {
  type: Boolean,
  default: true
},
```

完整的绑定示例如下

```html
<template>
  <my-table
    tabtitle="表格标题"
    :istabseq="true"
    :istabpage="false"
    :tabattr="tabattr"
    :tabdatacolumns="tabdatacolumns"
    :tabdata="tabdata"
    @page-change="handlePageChange"
  />
</template>
```

## 2 扩展功能

### 2.1 自定义列

有时候需要对特定单元格进行自定义操作，如：修改显示样式、将多个后端字段列合并到一个单元格显示，自定义操作栏、自定义某个单元格点击事件等等，此时就需要使用自定义列模板来完成

自定义列，需要通过插槽来实现，组件里面提供了一个名为`customercell`的具名插槽，通过此插槽来重新定义你需要调整的单元格，插槽输如属性值包括

- `column`：当前列的列数据定义
- `prop`：当前列的列数据对应prop值
- `index`: 当前行索引值
- `row`： 当前行的数据

比如下面的示例代码

```html
<template>
  <my-table
    tabtitle="自定义列"
    :tabattr="tabattr"
    :tabdatacolumns="tabdatacolumns"
    :tabdata="tabdata"
    @page-change="handlePageChange"
  >
    <template #customercell="{ prop, row }">
      <!-- 对标签列特殊显示处理 -->
      <template v-if="prop === 'tag'">
        <el-tag>{{ row[prop] }}</el-tag>
      </template>
    </template>
  </my-table>
</template>
```

### 2.2 复选功能

当业务有批量操作需求时，需要组件支持多选功能，支持多选很简单，只需要开启复选功能（`:istabmultiple`）和绑定选择项改变事件（`@selection-change`）即可。

示例代码如下：

```html
<template>
  <my-table
    tabtitle="复选表格"
    :istabmultiple="true"
    :tabattr="tabattr"
    :tabdatacolumns="tabdatacolumns"
    :tabdata="tabdata"
    @selection-change="handleSelectionChange"
  />
</template>
<script setup lang="ts">
  // 引入组件和类型
  import MyTable from '@/components/mytable/MyTable.vue'
  import {
    createPageDTO,
    type PageDTO,
    type MyTableAttr,
    type MyTableColumn
  } from '@/components/mytable/type'

  // 业务数据模型
  import type { SampleFormData } from '@/apis/sample/type'

  // 这里省略必须属性数据定义的代码

  /**
   * 选择行数据发生变化事件处理
   * @param rows 选中行数据
   */
  function handleSelectionChange(rows: SampleFormData[]) {
    // 这里逻辑根据自己的实际需求来完成
  }
</script>
```

### 2.3 行双击事件

有时候需要实现，双击某行的时候执行一些操作（如：打开详细查看界面），要实现此功能很简单只需要绑定行双击事件（`@row-dbclick`）即可。

示例代码如下：

```html
<template>
  <my-table
    tabtitle="行双击表格"
    :tabattr="tabattr"
    :tabdatacolumns="tabdatacolumns"
    :tabdata="tabdata"
    @row-dbclick="handleRowDbclick"
  />
</template>
<script setup lang="ts">
  // 引入组件和类型
  import MyTable from '@/components/mytable/MyTable.vue'
  import {
    createPageDTO,
    type PageDTO,
    type MyTableAttr,
    type MyTableColumn
  } from '@/components/mytable/type'

  // 业务数据模型
  import type { SampleFormData } from '@/apis/sample/type'

  // 这里省略必须属性数据定义的代码

  /**
   * 表格行双击事件处理
   * @param row 当前选中行数据
   */
  function handleRowDbclick(row: any) {
    // 这里逻辑根据自己的实际需求来完成
  }
</script>
```

### 2.4 操作栏支持

组件支持通过数据方式渲染操作栏，如果你的操作栏是其他显示方式，那么请使用自定义列模板来完成操作栏。

要使用操作栏支持需要定义操作栏按钮数据（`:taboperbtns`通过这个属性绑定）和列数据（`:tabdatacolumns`还是它来绑定）里面添加操作栏数据，然后绑定操作按钮点击事件（`@taboper-click`）即可。

在开始前，先来看看几个数据模型的定义。

```javascript
/** 自定义表格操作列数据模型 */
export interface MyTableOperationsColumn extends MyTableColumn {
  /** 按钮尺寸 */
  size?: 'large' | 'default' | 'small'
}

/**
 * 自定义表格操作列按钮属性模型
 */
export interface MyTableOperationsBtnAttr {
  /** 按钮类型 */
  type: 'primary' | 'success' | 'info' | 'warning' | 'danger' | ''
  /** 按钮尺寸 */
  size?: 'large' | 'default' | 'small'
  /** 图标名称 ，图标需要在el-icon插件中加载，如：icon-edit */
  icon?: string
  /** 是否为朴素按钮 */
  plain?: boolean
  /** 是否为圆角按钮 */
  round?: boolean
  /** 是否为圆形按钮 */
  circle?: boolean
  /** 是否为链接按钮 */
  link?: boolean
  /** 是否禁用 */
  disabled?: boolean
}

/**
 * 自定义表格操作列按钮数据模型
 * TIPS: 表格封装的操作列是用按钮实现显示效果的，如果这不是你想要的效果，那么请用自定义列（插槽）实现
 */
export interface MyTableOperationsBtn {
  /** 点击事件标识名称，如：info | edit | delete */
  evtname: string
  /** 按钮提示文本 */
  text?: string
  /** 按钮属性 */
  attr?: MyTableOperationsBtnAttr
}

```

然后再看一个完整的示例

```html
<template>
  <my-table
    tabtitle="操作栏表格"
    :tabattr="tabattr"
    :tabdatacolumns="tabopercolumns"
    :tabdata="tabdata"
    :taboperbtns="taboperbtns"
    @taboper-click="handleOperation"
    @page-change="handlePageChange"
  />
</template>
<script setup lang="ts">
  // 引入组件和类型
  import MyTable from '@/components/mytable/MyTable.vue'
  import {
    createPageDTO,
    type PageDTO,
    type MyTableAttr,
    type MyTableColumn,
    type MyTableOperationsColumn,
    type MyTableOperationsBtn,
    createMyTableOperationsColumn
  } from '@/components/mytable/type'

  // 业务数据模型
  import type { SampleFormData } from '@/apis/sample/type'

  // 这里省略部分必须属性数据定义的代码

  // 定义列数据
  const tabopercolumns: MyTableOperationsColumn[] = [
    // 操作列
    createMyTableOperationsColumn({
      'min-width': 200,
      fixed: 'right',
      align: 'center'
    })
    // 省略其他列数据定义
  ]

  // 定义操作列按钮数据
  const taboperbtns = ref<MyTableOperationsBtn[]>([
    {
      evtname: 'info',
      text: '详情',
      attr: {
        type: 'primary'
      }
    },
    {
      evtname: 'edit',
      text: '编辑',
      attr: {
        type: 'success',
        icon: 'icon-edit'
      }
    }
  ])

  /**
   * 表格操作栏事件处理
   * @param index 当前操作行索引
   * @param row 当前操作行数据
   * @param evtname 当前操作名称
   */
  function handleOperation(index: number, row: SampleFormData, evtname: string) {
    // 这里逻辑根据自己的实际需求来完成
    switch (evtname) {
      case 'info':
        console.log('info' + index, row)
        break
      case 'edit':
        console.log('edit' + index, row)
        break
      case 'delete':
        console.log('delete' + index, row)
        break
      default:
        break
    }
  }
</script>
```

### 2.5 自定义页眉页脚

组件还支持自定义页眉页脚，分别对应`header`和`footer`两个插槽，两个插槽都可以输入`props`（组件的数据属性）和`table`（el-table实例），使用示例如下：

```html
<template>
  <my-table
    tabtitle="自定义页眉页脚"
    :istabmultiple="true"
    :tabattr="tabattr"
    :tabdatacolumns="tabopercolumns"
    :tabdata="tabdata"
    @page-change="handlePageChange"
  >
    <!-- 表格头部插槽 -->
    <template #header>
      <el-input
        style="width: 200px"
        prefix-icon="icon-search"
        size="default"
        placeholder="输入搜索关键词"
        v-model="keywords"
      />
      <el-button type="primary">搜索</el-button>
    </template>
    <!-- 表格底部插槽 -->
    <template #footer="{ table }">
      <el-button type="primary" @click="handleSelectAll(table)">
        <template v-if="isSelectAll">反选</template>
        <template v-else>全选</template>
      </el-button>
    </template>
  </my-table>
</template>
<script setup lang="ts">
  // 省略表格属性定义代码

  // 搜索框绑定数据
  const keywords = ref('')
  // 是否全选
  const isSelectAll = ref(false)
  /**
   * 全选反选按钮点击事件处理
   */
  function handleSelectAll(table: any) {
    table?.toggleAllSelection()
    isSelectAll.value = !isSelectAll.value
  }
</script>
```
