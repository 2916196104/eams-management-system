import type { MyFormBaseProps } from './formbase'
/**
 * 单选框属性,注意：这里将v-model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/radio.html#radio-attributes
 */
export interface MyFormRadioBoxProps extends MyFormBaseProps {
  /** 单选框的值 */
  value?: string | number | boolean
  /** 单选框的标签值 */
  label?: string | number | boolean
  /** 是否显示边框 */
  border?: boolean
}

/**
 * 单选框组属性，注意：这里将v-model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/radio.html#radiogroup-attributes
 */
export interface MyFormRadioBoxGroupProps extends MyFormBaseProps {
  /** 组下面的单选框属性 */
  radioboxes?: Array<MyFormRadioBoxProps>
  /** 按钮形式的Radio激活时的文本颜色 */
  'text-color'?: string
  /** 按钮形式的Radio激活时的填充色和边框色 */
  fill?: string
}
