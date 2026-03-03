/**
 * 表单组件基础属性定义，定义所有表单几乎都有的属性
 */
export interface MyFormBaseProps {
  /** 组件大小 */
  size?: 'large' | 'default' | 'small'
  /** 是否禁用 */
  disabled?: boolean
  /** 原生readonly属性，是否只读 */
  readonly?: boolean
  /** 占位文本 */
  placeholder?: string
  /** 是否可以清空选项 */
  clearable?: boolean
  /** 设置组件宽度，不指定自适应宽度，如：188px */
  width?: string
  /** 原生name属性 */
  name?: string
  /** 原生id属性 */
  id?: string
}
