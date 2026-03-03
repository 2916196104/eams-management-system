import type { PageQuery } from '../type'

/**
 * 示例表单数据模型
 */
export interface SampleFormData extends Record<string, any> {
  /** 数据唯一标识 */
  id?: number
  /** 姓名 */
  name?: string
  /** 国家 */
  country?: string
  /** 省份 */
  state?: string
  /** 城市 */
  city?: string
  /** 地址 */
  address?: string
  /** 邮编 */
  zip?: number
  /** 生日 */
  date?: string
  /** 标签 */
  tags?: string
  /** 头像 */
  avatar?: string
}

/**
 * 示例表单查询模型
 */
export interface SampleFormQuery extends PageQuery {
  /** 姓名 */
  name?: string
}
