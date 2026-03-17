import type { MyFormBaseProps } from './formbase'
/**
 * 日期选择器属性，注意：这里将v-model属性剥离出去，方便操作
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/date-picker.html#%E5%B1%9E%E6%80%A7
 */
export interface MyFormDatePickerProps extends MyFormBaseProps {
  /** 显示类型 */
  type?:
    | 'year'
    | 'years'
    | 'month'
    | 'months'
    | 'date'
    | 'dates'
    | 'datetime'
    | 'week'
    | 'datetimerange'
    | 'daterange'
    | 'monthrange'
    | 'yearrange'
  /** 文本框可输入 */
  editable?: boolean
  /** 范围选择时开始日期的占位内容 */
  'start-placeholder'?: string
  /** 范围选择时结束日期的占位内容 */
  'end-placeholder'?: string
  /** 显示在输入框中的格式，注意大小写不要写错了，如：YYYY-MM-DD ,支持格式：https://day.js.org/docs/en/display/format#list-of-all-available-formats*/
  format?: string
  /** 绑定值的格式，不指定则绑定值为Date对象，注意大小写不要写错了，如：YYYY-MM-DD */
  'value-format'?: string
}
