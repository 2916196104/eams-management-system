import type { MyFormBaseProps } from './formbase'
/**
 * 输入框属性，注意：这里将v-model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/input.html#attributes
 */
export interface MyFormInputProps extends MyFormBaseProps {
  /** 原生input类型设置，如：'text' | 'textarea' | 'password' | 'button' | 'checkbox' | 'file' | 'number' | 'radio' 等等*/
  type?: string
  /** 是否显示切换密码图标 */
  'show-password'?: boolean
}

/**
 * 数字输入框属性，注意：这里将v-model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/input-number.html#attributes
 */
export interface MyFormInputNumberProps extends MyFormBaseProps {
  /** 设置计数器允许的最小值 */
  min?: number
  /** 设置计数器允许的最大值 */
  max?: number
  /** 计数器步长 */
  step?: number
  /** 是否只能输入step的倍数 */
  'step-strictly'?: boolean
}
