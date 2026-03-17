import type { MyFormBaseProps } from './formbase'
/**
 * 复选框属性,注意：这里将v-model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/checkbox.html#checkbox-attributes
 */
export interface MyFormCheckBoxProps extends MyFormBaseProps {
  /** 选中状态的值（只有在checkbox-group或者绑定对象类型为array时有效）*/
  value?: string | number | boolean | object
  /** 选中状态的值，只有在绑定对象类型为array时有效。*/
  label?: string | number | boolean | object
  /** 是否勾选 */
  checked?: boolean
  /** 是否显示边框 */
  border?: boolean
  /** 设置不确定状态，仅负责样式控制 */
  indeterminate?: boolean
}

/**
 * 复选框组属性，注意：这里将v-model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/checkbox.html#checkboxgroup-attributes
 */
export interface MyFormCheckBoxGroupProps extends MyFormBaseProps {
  /** 组下面的复选框属性 */
  checkboxes?: Array<MyFormCheckBoxProps>
  /** 可被勾选的checkbox的最小数量 */
  min?: number
  /** 可被勾选的checkbox的最大数量 */
  max?: number
}
