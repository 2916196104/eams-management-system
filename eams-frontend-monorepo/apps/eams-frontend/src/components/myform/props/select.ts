import type { MyFormBaseProps } from './formbase'
import type { CascaderProps } from 'element-plus'
/**
 * 下拉选择框选项值属性
 */
export interface MyFormSelectOption {
  /** 选项值 */
  value: string | number | boolean | object
  /** 选项显示文本 */
  label: string | number
  /** 是否禁用 */
  disabled?: boolean
  /** 子选项，用于支持级联选择器 */
  children?: MyFormSelectOption[]
}

/**
 * 下拉选择框属性，注意：这里将v-model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/select.html#select-attributes
 */
export interface MyFormSelectProps extends MyFormBaseProps {
  /** 选项值 */
  options: MyFormSelectOption[]
  /** 是否多选 */
  multiple?: boolean
  /** 多选场景下用户最多可以选择的项目数，为0则不限制 */
  'multiple-limit'?: number
  /** Select组件是否可筛选 */
  filterable?: boolean
}

/**
 * 级联选择器属性，注意：这里将v-model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/cascader.html#cascaderprops
 */
export interface MyFormCascaderProps extends MyFormBaseProps {
  /** 选项的数据源 */
  options: MyFormSelectOption[]
  /** 配置选项 */
  props?: CascaderProps
  /** 输入框中是否显示选中值的完整路径 */
  'show-all-levels'?: boolean
  /** 多选模式下是否折叠Tag */
  'collapse-tags'?: boolean
  /** 当鼠标悬停于折叠标签的文本时，是否显示所有选中的标签。 要使用此属性，collapse-tags属性必须设定为true */
  'collapse-tags-tooltip'?: boolean
  /** 用于分隔选项的字符 */
  separator?: string
  /** 该选项是否可以被搜索 */
  filterable?: boolean
}

/**
 * 级联面板属性，注意：这里将v-model属性剥离出去，方便操作
 */
export interface MyFormCascaderPanelProps extends MyFormBaseProps {
  /** 选项的数据源 */
  options: MyFormSelectOption[]
  /** 配置选项 */
  props?: CascaderProps
}
