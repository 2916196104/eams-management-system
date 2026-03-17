<template>
  <section class="root-container">
    <!-- 基础使用 -->
    <my-search
      formtitle="搜索组件示例"
      :model="formdata"
      :items="formitemdata"
      :formattr="formattr"
      :rules="rules"
      @model-change="(prop, val) => (formdata[prop] = val)"
      @do-search="doSearch"
    />
    <!-- 插槽使用 -->
    <my-search
      :model="formdata"
      :items="formitemdata"
      @model-change="(prop, val) => (formdata[prop] = val)"
      @do-search="doSearch"
    >
      <template #header>
        <h3>插槽使用示例</h3>
      </template>
      <template #footer>
        <el-text>带*的条件属于必填哦~道友要认真填写哦~</el-text>
      </template>
    </my-search>
    <!-- 用表格显示搜索结果 -->
    <my-table
      tabtitle="搜索结果"
      :istabseq="true"
      :istabpage="false"
      :tabdatacolumns="tabdatacolumns"
      :tabdata="tabdata"
    />
  </section>
</template>
<script setup lang="ts">
// #region 公用导入
import { ref, reactive } from 'vue'
import type { FormRules } from 'element-plus'
// #endregion

// #region 测试表格需要定义的属性
// 引入示例后端接口
import { listall } from '@/apis/sample/index'

// 用表格来显示搜索结果
import MyTable from '@/components/mytable/MyTable.vue'
import { createPageDTO, type PageDTO, type MyTableColumn } from '@/components/mytable/type'

// 业务数据模型
import type { SampleFormData } from '@/apis/sample/type'

// 定义表格列数据
const tabdatacolumns: MyTableColumn[] = [
  {
    prop: 'name',
    label: '姓名'
  },
  {
    prop: 'state',
    label: '省份',
    'min-width': 150
  },
  {
    prop: 'city',
    label: '城市',
    'min-width': 150
  },
  {
    prop: 'address',
    label: '详细地址',
    'min-width': 150,
    'show-overflow-tooltip': true
  },
  {
    prop: 'zip',
    label: '邮编'
  }
]
// 定义表格数据
const tabdata = ref<PageDTO<SampleFormData>>(createPageDTO())
// #endregion

// 导入组件和类型
import MySearch from '@/components/mysearch/MySearch.vue'
import type {
  MyFormItemAttr,
  MyFormAttr,
  MyFormInputProps,
  MyFormSelectProps,
  MyFormInputNumberProps,
  MyFormDatePickerProps
} from '@/components/myform/type'

// 定义表单数据
const formdata = reactive<SampleFormData>({
  zip: 610000
})

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

// 定义表单属性数据
const formattr: MyFormAttr = {
  'label-suffix': ':',
  'show-count': 2
}

// 定义表单校验规则
const rules = reactive<FormRules<SampleFormData>>({
  name: [{ min: 2, max: 5, message: '长度在 2 到 5 个字符', trigger: 'change' }],
  country: [{ required: true, message: '请选择国家', trigger: 'change' }],
  state: [{ required: true, message: '请输入省份', trigger: 'blur' }]
})

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
      tabdata.value = data
    },
    (error: any) => {
      console.log(error)
    }
  )
}
</script>
<style scoped>
.root-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 5px;
}
</style>
