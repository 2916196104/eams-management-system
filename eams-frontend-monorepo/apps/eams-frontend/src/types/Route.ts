import type { RouteRecordRaw } from 'vue-router'

/**
 * 路由模块导出的RouteRecordRaw数组
 */
export interface RouteRecordRawArray {
  default: Array<RouteRecordRaw>
}

/**
 * 标签页路由数据
 */
export interface TabRoute {
  /**
   * 显示名称
   */
  label: string
  /**
   * 路由地址
   */
  path: string
  /**
   * 路由名称
   */
  name?: string
}
