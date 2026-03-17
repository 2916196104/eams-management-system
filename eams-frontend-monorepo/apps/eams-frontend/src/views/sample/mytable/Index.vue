<template>
  <section class="root-container">
    <!-- 简单表格演示 -->
    <my-table
      tabtitle="简单表格"
      :tabdatacolumns="tabdatacolumns"
      :tabdata="tabdata"
      @page-change="handlePageChange"
    />
    <!-- 序号表格演示 -->
    <my-table
      tabtitle="序号表格"
      :istabseq="true"
      :tabattr="tabattr"
      :tabdatacolumns="tabdatacolumns"
      :tabdata="tabdata"
      @page-change="handlePageChange"
    />
    <!-- 复选框表格演示 -->
    <section class="two-tab-container">
      <my-table
        style="width: 50%"
        tabtitle="复选表格"
        :istabmultiple="true"
        :istabpage="false"
        :tabattr="tabattr"
        :tabdatacolumns="tabdatacolumns"
        :tabdata="tabdata"
        @selection-change="handleSelectionChange"
      />
      <my-table
        style="width: 49%"
        tabtitle="选中数据"
        :istabpage="false"
        :tabattr="tabattr"
        :tabdatacolumns="tabdatacolumns"
        :tabdata="tabSelectData"
      />
    </section>
    <!-- 行双击事件演示 -->
    <my-table
      tabtitle="行双击表格"
      :istabpage="false"
      :tabattr="tabattr"
      :tabdatacolumns="tabdatacolumns"
      :tabdata="tabdata"
      @row-dbclick="handleRowDbclick"
    />
    <!-- 自定义列 -->
    <my-table
      tabtitle="自定义列"
      :tabattr="tabattr"
      :tabdatacolumns="tabdatacolumns"
      :tabdata="tabdata"
      :istabexpand="true"
      @page-change="handlePageChange"
    >
      <!-- 自定义展开行插槽 -->
      <template #customerexpand="{ row }">
        <div>
          <el-tag>{{ row.name }}</el-tag>
        </div>
      </template>
      <!-- 单元格插槽 -->
      <template #customercell="{ prop, row }">
        <!--对姓名列特殊显示处理-->
        <template v-if="prop === 'name'">
          <el-link type="primary" @click="handleRowDbclick(row)">
            {{ row[prop] }}-({{ row.id }})
          </el-link>
        </template>
        <!-- 对标签列特殊显示处理 -->
        <template v-if="prop === 'tag'">
          <el-tag>{{ row[prop] }}</el-tag>
        </template>
      </template>
    </my-table>
    <!-- 表格操作列演示 -->
    <my-table
      tabtitle="操作栏表格"
      :tabattr="tabattr"
      :tabdatacolumns="tabopercolumns"
      :tabdata="tabdata"
      :taboperbtns="taboperbtns"
      @taboper-click="handleOperation"
      @page-change="handlePageChange"
    />
    <!-- 自定义页眉页脚 -->
    <my-table
      tabtitle="自定义页眉页脚"
      :istabmultiple="true"
      :tabattr="tabattr"
      :tabdatacolumns="tabdatacolumns"
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
        <el-button type="primary" icon="IconSearch" @click="loadData()">搜索</el-button>
        <el-button type="primary" icon="IconPlus" @click="formDialogAdd.openDialog(true)">
          新增
        </el-button>
      </template>
      <!-- 表格底部插槽 -->
      <template #footer="{ table }">
        <el-button type="primary" @click="handleSelectAll(table)">
          <template v-if="isSelectAll">反选</template>
          <template v-else>全选</template>
        </el-button>
        <section>*提示:注册用户默认是密码是123456</section>
      </template>
    </my-table>
  </section>
  <!-- 查看数据表单对话框 -->
  <my-form-dialog ref="formDialogView" :="formDialogViewProps" />
  <!-- 编辑数据表单对话框 -->
  <my-form-dialog ref="formDialogEdit" :="formDialogEditProps" @confirm="onEditSubmit" />
  <!-- 新增数据表单对话框 -->
  <my-form-dialog ref="formDialogAdd" :="formDialogAddProps" @confirm="onAddSubmit" />
</template>
<script setup lang="ts">
// #region 公用部分
import { ref, reactive, onMounted } from 'vue'
import { cloneDeep } from 'lodash-es'
import { ElMessageBox } from 'element-plus'

// 引入示例后端接口
import { listall } from '@/apis/sample/index'

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

// 定义表格属性
const tabattr: MyTableAttr = {
  height: 200,
  'max-height': 400,
  'row-key': 'id'
}

// 定义列数据
const tabdatacolumns: MyTableColumn[] = [
  {
    prop: 'name',
    label: '姓名',
    'min-width': 70,
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

/**
 * 加载数据
 */
function loadData() {
  listall(
    {
      pageIndex: tabdata.value.pageIndex,
      pageSize: tabdata.value.pageSize,
      name: keywords.value
    },
    (data) => {
      // 添加测试数据，用于展示树形效果
      data.rows[0].children = [
        {
          id: 1001,
          name: '子节点1',
          date: '1976-05-23',
          city: '日照市',
          state: '北京',
          address: '广东省 湛江市 霞山区',
          zip: 410578,
          tag: '贵宾'
        },
        {
          id: 1002,
          name: '子节点2',
          date: '1976-05-23',
          city: '日照市',
          state: '北京',
          address: '广东省 湛江市 霞山区',
          zip: 410578,
          tag: '贵宾'
        }
      ]
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
// #endregion

// #region 复选框表格需要处理的逻辑代码
// 定义选中数据
const tabSelectData = ref<PageDTO<SampleFormData>>(createPageDTO())
/**
 * 选择行数据发生变化事件处理
 * @param rows 选中行数据
 */
function handleSelectionChange(rows: SampleFormData[]) {
  tabSelectData.value.rows = rows
}
// #endregion

// #region 表格行双击需要处理的逻辑代码
// 导入表单对话框组件和类型
import MyFormDialog from '@/components/mydialog/MyFormDialog.vue'
import type { MyFormDialogProps } from '@/components/mydialog/type'
import type {
  MyFormItemAttr,
  MyFormInputProps,
  MyFormInputNumberProps,
  MyFormDatePickerProps
} from '@/components/myform/type'

// 定义对话框引用
const formDialogView = ref()
// 定义对话框属性
const formDialogViewProps = reactive<MyFormDialogProps<SampleFormData>>({
  title: '数据详情',
  cancelText: '知道了',
  // 对话框表单数据
  data: reactive<SampleFormData>({}),
  // 对话框表单属性
  formattr: {
    // 当这个值为true时表单元素全部禁止修改,对话框也不在显示提交和重置按钮
    disabled: true,
    'label-width': '80px'
  },
  // 对话框表单域数据
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
    }
  ])
})

/**
 * 表格行双击事件处理
 * @param row 当前选中行数据
 */
function handleRowDbclick(row: SampleFormData) {
  // 更新数据
  Object.assign(formDialogViewProps.data, row)
  // 打开对话框
  formDialogView.value.openDialog(true)
}
// #endregion

// #region 表格操作栏需要处理的逻辑代码

// 定义列数据
const tabopercolumns: MyTableOperationsColumn[] = [
  // 操作列
  createMyTableOperationsColumn({
    'min-width': 250,
    align: 'center'
  }),
  // 其他列
  ...tabdatacolumns
]
// 定义对话框引用
const formDialogEdit = ref()
// 定义对话框属性
const formDialogEditProps = reactive<MyFormDialogProps<SampleFormData>>({
  title: '编辑数据',
  submitText: '保存',
  cancelText: '取消',
  // 对话框表单数据
  data: reactive<SampleFormData>({}),
  // 对话框表单属性
  formattr: {
    ...formDialogViewProps.formattr,
    disabled: false
  },
  // 对话框表单域数据
  formitemdata: formDialogViewProps.formitemdata
})
// 定义一个编辑项索引，用于编辑回调处理数据更新
const editIndex = ref<number>(-1)
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
  },
  {
    evtname: 'delete',
    text: '删除',
    attr: {
      type: 'danger',
      icon: 'icon-delete'
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
  switch (evtname) {
    case 'info':
      handleRowDbclick(row)
      break
    case 'edit':
      editIndex.value = index
      Object.assign(formDialogEditProps.data, row)
      formDialogEdit.value.openDialog(true)
      break
    case 'delete':
      ElMessageBox.confirm('你确认删除这条数据吗？', '提示', {
        confirmButtonText: '确认删除',
        cancelButtonText: '点错了',
        type: 'warning'
      })
        .then(() => {
          // 执行网络请求删除数据
          console.log('delete' + index, row)
          // 删除数据
          tabdata.value?.rows?.splice(index, 1)
        })
        .catch(() => {})
      break
    default:
      break
  }
}
/**
 * 提交修改
 * @param data 表单数据
 */
function onEditSubmit(data: SampleFormData) {
  // 提交数据
  console.log(data)
  if (tabdata.value?.rows) Object.assign(tabdata.value?.rows[editIndex.value], data)
  // 关闭对话框
  formDialogEdit.value.closeDialog()
}
// #endregion

// #region 自定义页眉页脚逻辑代码
// 搜索框绑定数据
const keywords = ref('')
// 是否全选
const isSelectAll = ref(false)
// 定义对话框引用
const formDialogAdd = ref()
// 定义对话框属性
// eslint-disable-next-line @typescript-eslint/no-unused-vars
const formDialogAddProps = reactive<MyFormDialogProps<SampleFormData>>({
  title: '新增数据',
  submitText: '保存',
  cancelText: '取消',
  reset: true,
  disableBeforeClose: true,
  // 对话框表单数据
  data: reactive<SampleFormData>({}),
  // 对话框表单属性
  formattr: {
    ...formDialogViewProps.formattr,
    disabled: false
  },
  // 对话框表单域数据
  formitemdata: formDialogViewProps.formitemdata
})
/**
 * 全选反选按钮点击事件处理
 */
function handleSelectAll(table: any) {
  table?.toggleAllSelection()
  isSelectAll.value = !isSelectAll.value
}
/**
 * 提交修改
 * @param data 表单数据
 */
function onAddSubmit(data: SampleFormData) {
  // 提交数据
  console.log(data)

  // 将数据添加到表格测试效果
  tabdata.value.rows?.unshift(cloneDeep(data))

  // 关闭对话框
  formDialogAdd.value.closeDialog()
}
// #endregion
</script>
<style scoped>
.root-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 15px;
}
.two-tab-container {
  max-width: 100%;
  display: flex;
  flex-direction: row;
  justify-content: space-between;
}
</style>
