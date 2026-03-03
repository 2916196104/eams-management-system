import type { MyFormAttr, MyFormItemAttr } from '@/components/myform/type'
import type { FormRules } from 'element-plus'

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
