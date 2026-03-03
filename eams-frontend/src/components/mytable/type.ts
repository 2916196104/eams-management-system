import type { TreeNode } from 'element-plus'
import type { VNode } from 'vue'

/**
 * 自定义表格属性模型
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/table.html#table-%E5%B1%9E%E6%80%A7
 */
export interface MyTableAttr {
  /** 分页组件大小, 默认default */
  psize?: 'large' | 'default' | 'small'
  /** 表格高度，不指定自动适配表格高度 */
  height?: number
  /** 表格最大高度 */
  'max-height'?: number
  /** 是否显示斑马纹, 默认显示 */
  stripe?: boolean
  /** 是否显示纵向边框, 默认不显示 */
  border?: boolean
  /** 是否高亮当前选择行, 默认高亮 */
  'highlight-current-row'?: boolean
  /** 是否在表尾显示合计行, 默认不显示 */
  'show-summary'?: boolean
  /** 自定义的合计计算方法 */
  'summary-method'?: (data: { columns: any[]; data: any[] }) => (VNode | string)[]
  /** 行数据的Key，用来优化Table的渲染,在使用reserve-selection功能与显示树形数据时，该属性是必填的*/
  'row-key'?: string | ((row: any) => string)
  /** 是否默认展开所有行，当Table包含展开行存在或者为树形表格时有效 */
  'default-expand-all'?: boolean
  /** 是否懒加载子节点数据 */
  lazy?: boolean
  /** 懒加载时用于加载子节点数据的方法 */
  load?: (row: any, treeNode: TreeNode, resolve: (data: any[]) => void) => void
  /** 渲染嵌套数据的配置选项 */
  'tree-props'?: { hasChildren?: string; children?: string; checkStrictly?: boolean }
}

/**
 * 自定义表格列数据模型
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/table.html#table-column-%E5%B1%9E%E6%80%A7
 */
export interface MyTableColumn {
  /** 列标题 */
  label: string
  /** 列字段名 */
  prop: string
  /** 列宽度，不指定自适应宽度 */
  width?: string
  /** 最小列宽度 */
  'min-width'?: number
  /** 是否固定列 */
  fixed?: 'left' | 'right'
  /** 当内容过长被隐藏时显示tooltip */
  'show-overflow-tooltip'?: boolean
  /** 列对齐方式 */
  align?: 'left' | 'center' | 'right'
}

/** 自定义表格操作列数据模型 */
export interface MyTableOperationsColumn extends MyTableColumn {
  /** 按钮尺寸 */
  size?: 'large' | 'default' | 'small'
}

/**
 * 创建自定义表格操作列数据实例，用于指定一些默认值
 * @param init 初始化数据
 * @returns 自定义表格操作列实例
 */
export function createMyTableOperationsColumn(
  init?: Partial<MyTableOperationsColumn>
): MyTableOperationsColumn {
  return {
    label: '操作栏', // 默认值
    prop: 'operate', // 默认值
    fixed: 'right', // 默认值
    'min-width': 120, // 默认值
    size: 'small', // 默认值
    ...init // 覆盖用户传入值
  }
}

/**
 * 自定义表格操作列按钮属性模型
 * //FIXME 可根据需要扩充字段，可扩充字段来源：https://element-plus.org/zh-CN/component/button#button-attributes
 */
export interface MyTableOperationsBtnAttr {
  /** 按钮类型 */
  type: 'primary' | 'success' | 'info' | 'warning' | 'danger' | ''
  /** 按钮尺寸 */
  size?: 'large' | 'default' | 'small'
  /** 图标名称 ，图标需要在el-icon插件中加载，如：icon-edit */
  icon?: string
  /** 是否为朴素按钮 */
  plain?: boolean
  /** 是否为圆角按钮 */
  round?: boolean
  /** 是否为圆形按钮 */
  circle?: boolean
  /** 是否为链接按钮 */
  link?: boolean
  /** 是否禁用 */
  disabled?: boolean
}

/**
 * 自定义表格操作列按钮数据模型
 * TIPS: 表格封装的操作列是用按钮实现显示效果的，如果这不是你想要的效果，那么请用自定义列（插槽）实现
 */
export interface MyTableOperationsBtn {
  /** 点击事件标识名称，如：info | edit | delete */
  evtname: string
  /** 按钮提示文本 */
  text?: string
  /** 按钮属性 */
  attr?: MyTableOperationsBtnAttr
}

/**
 * 分页数据模型
 */
export interface PageDTO<T> {
  /** 页码 */
  pageIndex: number
  /** 每页数据条数 */
  pageSize: number
  /** 数据总条数 */
  total: number
  /** 数据总页数 */
  pages?: number
  /** 当前页数据 */
  rows?: Array<T>
}

/**
 * 创建分页数据模型实例工厂方法
 * @param init 初始化数据
 * @returns 分页数据模型实例
 */
export function createPageDTO<T>(init?: Partial<PageDTO<T>>): PageDTO<T> {
  return {
    pageIndex: 1, // 默认值
    pageSize: 10, // 默认值
    total: 0, // 默认值
    rows: [], // 默认值
    ...init, // 覆盖用户传入值
    // 自动计算总页数（可选）
    pages: init?.pages ?? Math.ceil((init?.total ?? 0) / (init?.pageSize ?? 10))
  }
}
