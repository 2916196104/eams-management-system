<template>
  <section class="root-container">
    <!-- 基础使用 -->
    <my-form
      formtitle="基础使用效果"
      :items="formitemdata"
      :model="formdata"
      @do-submit="doSubmit"
    />
    <!-- 插槽使用 -->
    <my-form :="myformprops" @do-submit="doSubmit" @model-change="modelChange">
      <!-- 组件项后置插槽 -->
      <template #itemtail="{ item, model }">
        <!-- 渲染全选复选框 -->
        <template v-if="item.prop === 'type'">
          <el-text style="margin-left: 25px" class="hidden-xs-only"></el-text>
          <my-form-render
            :model="ckAllModel"
            :item="ckAllItem"
            @update:model="ckAllChange($event, model)"
          />
        </template>
      </template>
    </my-form>
  </section>
</template>
<script setup lang="ts">
import 'element-plus/theme-chalk/display.css'
import { reactive, ref, onMounted } from 'vue'
import { useCommonStore } from '@/stores/common'

// 导入组件和类型
import MyForm from '@/components/myform/MyForm.vue'
import MyFormRender from '@/components/myform/MyFormRender.vue'
// 表单相关属性
import type {
  MyFormItemAttr,
  MyFormInputProps,
  MyFormCascaderProps,
  MyFormSelectProps,
  MyFormSelectOption,
  MyFormInputNumberProps,
  MyFormDatePickerProps,
  MyFormCheckBoxProps,
  MyFormCheckBoxGroupProps,
  MyFormRadioBoxGroupProps,
  MyFormProps
} from '@/components/myform/type'
import { getAddress } from '@/apis/sample'

// 定义FormData的模型
interface FormData extends Record<string, any> {
  name?: string
  address?: string
  zero?: string
  count?: number
  time?: string
  type?: string[]
  support?: string
  describe?: string
}

// 定义表单数据
const formdata = reactive<FormData>({
  count: 1,
  support: 'wechat'
})
// 定义活动地址下拉列表数据
const addressOptions = ref<MyFormSelectOption[]>([])
// 定义活动地点下拉列表数据
const zeroOptions = ref<MyFormSelectOption[]>([])
// 定义表单域数据
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
    type: 'cascader',
    prop: 'address',
    label: '活动地址',
    rules: [{ required: true, message: '请选择活动地址', trigger: 'change' }],
    fprops: {
      width: '100%',
      placeholder: '请选择活动地址',
      clearable: true,
      options: addressOptions as unknown,
      props: {
        lazy: true,
        lazyLoad: (node, resolve) => {
          const { level } = node
          // 加载数据
          const type = level === 0 ? 'province' : level === 1 ? 'city' : 'county'
          getAddress(type).then((data) => {
            const nodes = data.data?.map((item) => {
              return {
                value: item.value,
                label: item.label,
                leaf: level >= 2
              }
            })
            resolve(nodes)
          })
        }
      }
    } as MyFormCascaderProps
  },
  {
    type: 'select',
    prop: 'zero',
    label: '活动地点',
    rules: [{ required: true, message: '请选择活动地点', trigger: 'change' }],
    fprops: {
      placeholder: '请选择地点',
      options: zeroOptions as unknown
    } as MyFormSelectProps
  },
  {
    type: 'number',
    prop: 'count',
    label: '活动数量',
    rules: [{ required: true, message: '请输入活动数量', trigger: 'change' }],
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
    rules: [{ required: true, message: '请输入活动时间', trigger: 'change' }],
    fprops: {
      placeholder: '请选择活动时间',
      type: 'datetimerange',
      'value-format': 'YYYY-MM-DD HH-mm-ss'
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

// 附加其他属性定义，将所有属性组合到一个对象传递给组件即可
// eslint-disable-next-line @typescript-eslint/no-unused-vars
const myformprops = reactive<MyFormProps<FormData>>({
  formtitle: '插槽使用效果',
  model: formdata,
  items: formitemdata,
  // 表单属性
  formattr: {
    size: 'large'
  },
  submittext: '保存',
  rules: {
    name: [{ min: 2, max: 5, message: '长度在 2 到 5 个字符', trigger: 'change' }]
  }
})

// 使用通用数据状态
const commonStore = useCommonStore()

/**
 * 加载数据
 */
onMounted(async () => {
  // 加载活动地点字典
  await commonStore.loadDict('active-zero')
  // 更新组件显示的地点字典
  const zerodict = commonStore.getDicts('active-zero')
  zerodict.items.forEach((item) => {
    zeroOptions.value.push({
      label: item.label,
      value: item.id
    })
  })
})

/**
 * 提交事件
 * @param data 表单数据
 */
function doSubmit(data: FormData) {
  console.log(data)
}

// #region 表单组件项后置插槽
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
  // TIPS 你可以在这里更新父组件数据，当然也可以不更新父组件数据，根据实际业务来
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
// #endregion
</script>
<style scoped>
.root-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 15px;
}
</style>
