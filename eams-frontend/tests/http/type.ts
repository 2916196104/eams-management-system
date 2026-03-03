/**
 * 文章数据实体
 */
export interface Article {
  /** 唯一标识 */
  id: string
  /** 标题 */
  title: string
  /** 关键词 */
  keywords: string
  /** 摘要 */
  summary: string
  /** 内容 */
  content: string
  /** 发表日期 */
  date: string
}
